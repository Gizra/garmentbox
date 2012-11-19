(function ($) {

/**
 * Production order delivery table.
 */
Drupal.behaviors.GarmentboxOrderItems = {
  attach: function(context) {
    var self = this;
    var table = $(context).find('table#delivery-details');
    // Show and hide rows as "Received" checkbox changes.
    self.showHideRows(context);
    table.find('td.received input[type="checkbox"]').change(function(event) {
      self.showHideRows(context);
    });

    // Recalculate values when the received quantity is updated.
    table.find('tr.received input, tr.defective input')
      .change(function(event) { self.updateDeliveryData(context); })
      .keyup(function(event) { self.updateDeliveryData(context); });
  },

  // Show and hide varation sub-rows depending on the "Received" checkbox state.
  showHideRows: function(context) {
    var self = this;
    $(context).find('table#delivery-details td.received input[type="checkbox"]').each(function(i, element) {
      var rowId = $(element).parents('tr').attr('id');
      var rows = $(element).parents('tbody').find('tr[ref="' + rowId + '"]');
      if($(element).attr('checked')) {
        rows.show().removeClass('hidden');
      }
      else {
        rows.hide().addClass('hidden');
      }
      self.updateDeliveryData(context);
    });
  },

  // Calculate the "Extras" and "Missing" data.
  updateDeliveryData: function(context) {
    var table = $(context).find('table#delivery-details');
    for (nid in Drupal.settings.garmentbox_factory.delivery_data) {
      for (tid in Drupal.settings.garmentbox_factory.delivery_data[nid].sizes) {
        var extrasCell = table.find('tr.extras td[data-tid="' + tid + '"]');
        var missingCell = table.find('tr.missing td[data-tid="' + tid + '"]');
        extrasCell.text('');
        missingCell.text('');

        var original = Drupal.settings.garmentbox_factory.delivery_data[nid].sizes[tid];
        var received = parseInt(table.find('tr.received[ref="variant-' + nid + '"] td[data-tid="' + tid + '"] input').val());
        if (isNaN(received) || received < 0) {
          continue;
        }

        if (received > original) {
          extrasCell.text(received - original);
        }

        if (original > received) {
          missingCell.text(original - received);
        }
      }
      this.updateVariantPrice(context, nid);
    }
    this.updateTotals(context);
  },

  // Update the production price of a specific variant.
  updateVariantPrice: function(context, nid) {
    var item_price = Drupal.settings.garmentbox_factory.delivery_data[nid].item_price / 100;
    var table = $(context).find('table#delivery-details');
    var types = ['received', 'defective', 'extras', 'missing'];

    for (i in types) {
      var row = table.find('tr.' + types[i] + '[ref="variant-' + nid + '"]');
      // Select the quantity from the input or from the td.
      var query = 'td.size-quantity';
      if (types[i] == 'received' || types[i] == 'defective') {
        query += ' input';
      }
      // Sum the row quantity.
      var items_count = 0;
      row.find(query).each(function(i, element) {
        var quantity = $(element).is('input') ? $(element).val() : $(element).text();
        quantity = parseInt(quantity);
        if (!isNaN(quantity) && quantity >= 0) {
          items_count += quantity;
        }
      });
      var price = items_count * item_price;
      row.find('td.price').text('$' + Drupal.formatNumber(price, 2));
      // Save the variant's items count for the totals calculation.
      Drupal.settings.garmentbox_factory.delivery_data[nid].items_count[types[i]] = items_count;
    }
  },

  // Update the "Total items" and "Production cost" elements.
  updateTotals: function(context) {
    var receivedItems = 0;
    var receivedItemsPrice = 0;
    for (nid in Drupal.settings.garmentbox_factory.delivery_data) {
      var variantReceivedItems = Drupal.settings.garmentbox_factory.delivery_data[nid].items_count.received;
      receivedItems += variantReceivedItems;
      receivedItemsPrice += variantReceivedItems * (Drupal.settings.garmentbox_factory.delivery_data[nid].item_price / 100);
    }

    $(context).find('input#edit-total-items-new').val(receivedItems);
    $(context).find('input#edit-production-cost-new').val('$' + Drupal.formatNumber(receivedItemsPrice, 2));
  }
};

})(jQuery);
