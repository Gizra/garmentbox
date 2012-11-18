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
    table.find('tr.received input').change(function(event) {
      self.updateDeliveryData(context);
    });
    table.find('tr.received input').keyup(function(event) {
      self.updateDeliveryData(context);
    });
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
        var original = Drupal.settings.garmentbox_factory.delivery_data[nid].sizes[tid];
        var received = table.find('tr.received[ref="variant-' + nid + '"] td[data-tid="' + tid + '"] input').val();
        var extrasCell = table.find('tr.extras td[data-tid="' + tid + '"]');
        extrasCell.text('');
        if (received > original) {
          extrasCell.text(received - original);
        }
      }
      this.updateVariantPrice(context, nid);
    }
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
        var quantity = parseInt($(element).val());
        if (!isNaN(quantity) && quantity >= 0) {
          items_count += quantity;
        }
      });
      console.log(items_count);
      var price = items_count * item_price;
      row.find('td.price').text('$' + Drupal.formatNumber(price, 2));
    }
  }
};

})(jQuery);
