(function ($) {

/**
 * Production order delivery table.
 */
Drupal.behaviors.GarmentboxOrderItems = {
  attach: function(context) {
    var self = this;
    var table = $(context).find('table#delivery-details');

    // Disable the received and IL inputs, to communicate that the received
    // amounts are ignored if "Received" isn't checked.
    // These inputs aren't disabled on the FAPI level because it would make them
    // ignored anyway.
    table.find('tr.received, tr.line').find('.size-quantity input').attr('disabled', 'disabled');

    // Show and hide rows as "Received" checkbox changes.
    self.showHideRows(context);
    table.find('td.received input[type="checkbox"]').change(function(event) {
      self.showHideRows(context);
    });

    // Recalculate values when the received quantity is updated.
    table.find('tr.received input, tr.defective input')
      .change(function(event) { self.updateDeliveryData(context); })
      .keyup(function(event) { self.updateDeliveryData(context); });

    // Show and hide IL when the original expander is toggled.
    table.find('tr.original a.expander').click(function(event) {
      event.preventDefault();
      var expander = $(event.currentTarget);
      var rowId = expander.parents('tr').attr('ref');
      var rows = expander.parents('tbody').find('tr.line[ref="' + rowId + '"]');
      if (expander.hasClass('collapsed')) {
        rows.show().removeClass('hidden');
      }
      else {
        rows.hide().addClass('hidden');
      }
      expander.toggleClass('collapsed');
    });
  },

  // Show and hide varation sub-rows depending on the "Received" checkbox state.
  showHideRows: function(context) {
    var self = this;
    $(context).find('table#delivery-details td.received input[type="checkbox"]').each(function(i, element) {
      var rowId = $(element).parents('tr').attr('id');
      var tbody = $(element).parents('tbody');
      if($(element).attr('checked')) {
        // When showing, ignore the inventory-line rows.
        tbody.find('tr.subrow[ref="' + rowId + '"]').show().removeClass('hidden');
        // Enable the received textfields.
        tbody.find('tr.received[id="' + rowId + '"] .size-quantity input').removeAttr('disabled');
      }
      else {
        // When hiding, hide all variant rows.
        tbody.find('tr[ref="' + rowId + '"]').hide().addClass('hidden');
      }
      self.updateDeliveryData(context);
    });
  },

  // Calculate the "Extras" and "Missing" data.
  updateDeliveryData: function(context) {
    var table = $(context).find('table#delivery-details');
    for (nid in Drupal.settings.garmentbox_factory.delivery_data) {
      var rowId = 'variant-' + nid;
      for (tid in Drupal.settings.garmentbox_factory.delivery_data[nid].sizes) {
        var extrasCell = table.find('tr.extras[ref="' + rowId + '"] td[data-tid="' + tid + '"]');
        var missingCell = table.find('tr.missing[ref="' + rowId + '"] td[data-tid="' + tid + '"]');
        extrasCell.text('');
        missingCell.text('');

        var original = Drupal.settings.garmentbox_factory.delivery_data[nid].sizes[tid];
        var received = parseInt(table.find('tr.received[id="' + rowId + '"] td[data-tid="' + tid + '"] input').val());
        if (isNaN(received) || received < 0) {
          continue;
        }

        if (received > original) {
          extrasCell.text(received - original);
        }

        if (original > received) {
          missingCell.text(original - received);
          this.missingItemsNotice(context, nid, tid, false);
        }
        else {
          // Remove the "missing" notice, in case it was already triggered.
          this.missingItemsNotice(context, nid, tid, true);
        }
      }
      this.updateVariantPrice(context, nid);
    }
    this.updateTotals(context);
  },

  // Update the production price of a specific variant.
  updateVariantPrice: function(context, nid) {
    var self = this;
    var itemPrice = Drupal.settings.garmentbox_factory.delivery_data[nid].item_price / 100;
    var table = $(context).find('table#delivery-details');
    var types = ['original', 'received', 'defective', 'extras', 'missing'];
    var rowId = 'variant-' + nid;

    for (i in types) {
      var ref = 'ref';
      if (types[i] == 'received') {
        ref = 'id';
      }
      var row = table.find('tr.' + types[i] + '[' + ref + '="' + rowId + '"]');
      var itemsCount = this.updateRowPrice(row, itemPrice);

      // Save the variant's items count for the totals calculation.
      Drupal.settings.garmentbox_factory.delivery_data[nid].items_count[types[i]] = itemsCount;
    }

    // Update the IL rows.
    table.find('tr.line[ref="' + rowId + '"]').each(function(i, row) {
      self.updateRowPrice($(row), itemPrice);
    });
  },

  // Update the production price of a specific row.
  updateRowPrice: function(row, itemPrice) {
    // Select the quantity from the input or from the td.
    var query = 'td.size-quantity';
    if (row.hasClass('received') || row.hasClass('defective') || row.hasClass('line')) {
      query += ' input';
    }

    // Sum the row quantity.
    var itemsCount = 0;
    row.find(query).each(function(i, element) {
      var quantity = $(element).is('input') ? $(element).val() : $(element).text();
      quantity = parseInt(quantity);
      if (!isNaN(quantity) && quantity >= 0) {
        itemsCount += quantity;
      }
    });
    var price = itemsCount * itemPrice;
    row.find('td.price').text('$' + Drupal.formatNumber(price, 2));
    return itemsCount;
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
  },

  // Ask the user to set which items should be declared missing when there are
  // not enough received.
  missingItemsNotice: function(context, nid, tid, removeNotice) {
    var table = $(context).find('table#delivery-details');
    var rowId = 'variant-' + nid;
    // Reveal the IL rows.
    var rows =  table.find('tr.line[ref="' + rowId + '"]');
    var inputs = rows.find('td[data-tid="' + tid + '"] input');
    if (!removeNotice) {
      rows.show().removeClass('hidden');
      table.find('tr.original[ref="' + rowId + '"] a.collapsed').removeClass('collapsed');
      // Set a warning on the inputs of the missing size.
      inputs.removeAttr('disabled').addClass('error');
    }
    else {
      // When the missing error is removed, restore the original quantity.
      inputs.each(function(i, input) {
        var ilNid = $(input).data('il-nid');
        var quantity = Drupal.settings.garmentbox_factory.delivery_data[nid].lines[ilNid].quantity[tid]
        $(input).val(quantity).attr('disabled', 'disabled').removeClass('error');
      });
    }
  }
};

})(jQuery);
