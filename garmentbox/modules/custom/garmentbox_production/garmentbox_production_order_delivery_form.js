(function ($) {

/**
 * Production order delivery table.
 */
Drupal.behaviors.GarmentboxProductionOrderDelivery = {
  attach: function(context) {
    var self = this;
    var table = $(context).find('table#delivery-inventory');

    // Disable the received and IL inputs, to communicate that the received
    // amounts are ignored if "Received" isn't checked.
    // These inputs aren't disabled on the FAPI level because it would make them
    // ignored anyway.
    table.find('tr.received, tr.inventory-line').find('.size-quantity input').attr('disabled', 'disabled');

    // Show and hide rows as "Received" checkbox changes.
    self.showHideRows(context);
    table.find('td.received input[type="checkbox"]').change(function(event) {
      self.showHideRows(context);
    });

    // Recalculate values when the Received / Defective or IL quantity is
    // updated.
    table.find('.size-quantity input')
      .change(function(event) { self.updateDeliveryData(context); })
      .keyup(function(event) { self.updateDeliveryData(context); });

    // Show and hide IL when the original expander is toggled.
    table.find('tr.original a.expander').click(function(event) {
      event.preventDefault();
      var expander = $(event.currentTarget);
      var variantNid = expander.parents('tr').data('variant-nid');

      var tbody = expander.parents('tbody');
      var rows = tbody.find('tr.inventory-line[data-variant-nid="' + variantNid + '"]');
      if (expander.hasClass('collapsed')) {
        rows.show().removeClass('hidden');
      }
      else {
        rows.hide().addClass('hidden');
      }
      expander.toggleClass('collapsed');
    });

    // Block the save button as long as there are errors.
    var form = $(context).find('.pane-production-order-delivery form');
    form.submit(function(event) {
      if (form.find('input.error.custom').length) {
        //TODO: show bubble.
        return false;
      }
    });
  },

  // Show and hide varation sub-rows depending on the "Received" checkbox state.
  showHideRows: function(context) {
    var self = this;
    $(context).find('table#delivery-inventory td.received input[type="checkbox"]').each(function(i, element) {
      var variantNid = $(element).parents('tr').data('variant-nid');
      var tbody = $(element).parents('tbody');
      if($(element).attr('checked')) {
        // When showing, ignore the inventory-line rows.
        tbody.find('tr.subrow[data-variant-nid="' + variantNid + '"]').show().removeClass('hidden');
        // Enable the received textfields.
        tbody.find('tr.received[data-variant-nid="' + variantNid + '"]:not(.disabled) .size-quantity input').removeAttr('disabled');
      }
      else {
        // When hiding, hide all variant rows.
        tbody.find('tr[data-variant-nid="' + variantNid + '"]:not(.received)').hide().addClass('hidden');
        // Re-show the
        // Set the IL rows toggler as collapsed.
        tbody.find('tr.original[data-variant-nid="' + variantNid + '"] a.expander').addClass('collapsed');
        // Disable the received textfields.
        tbody.find('tr.received[data-variant-nid="' + variantNid + '"] .size-quantity input').attr('disabled', 'disabled');
      }
      self.updateDeliveryData(context);
    });
  },

  // Calculate the "Extras" and "Missing" data.
  updateDeliveryData: function(context) {
    var table = $(context).find('table#delivery-inventory');
    for (variantNid in Drupal.settings.garmentbox_production.delivery_data) {
      for (tid in Drupal.settings.garmentbox_production.delivery_data[variantNid]['original'].sizes) {
        var extrasCell = table.find('tr.extras[data-variant-nid="' + variantNid + '"] td[data-tid="' + tid + '"]');
        var missingCell = table.find('tr.missing[data-variant-nid="' + variantNid + '"] td[data-tid="' + tid + '"]');
        extrasCell.text('');
        missingCell.text('');

        var original = Drupal.settings.garmentbox_production.delivery_data[variantNid].original.sizes[tid];
        var received = parseInt(table.find('tr.received[data-variant-nid="' + variantNid + '"] td[data-tid="' + tid + '"] input').val());
        if (isNaN(received) || received < 0) {
          continue;
        }

        var missingCreated = Drupal.settings.garmentbox_production.delivery_data[variantNid].missing_created.sizes[tid];
        var actualReceived = received + missingCreated;

        if (actualReceived > original) {
          extrasCell.text(received - original);
        }

        if (original > actualReceived) {
          this.missingItemsNotice(context, variantNid, tid, false);
          this.updateMissingData(table, variantNid, tid);
        }
        else {
          // Remove the "missing" notice, in case it was already triggered.
          this.missingItemsNotice(context, variantNid, tid, true);
        }
      }
      this.updateVariantPrice(context, variantNid);
    }
    this.updateTotals(context);
  },

  // Update the production price of a specific variant.
  updateVariantPrice: function(context, nid) {
    var self = this;
    var itemPrice = Drupal.settings.garmentbox_production.delivery_data[nid].item_price / 100;
    var table = $(context).find('table#delivery-inventory');
    var types = ['original', 'received', 'defective', 'extras', 'missing-created'];

    for (i in types) {
      var itemsCount = 0;
      table.find('tr.' + types[i] + '[data-variant-nid="' + nid + '"]').each(function(i, row) {
       itemsCount += self.updateRowPrice($(row), itemPrice);
      });

      // Save the variant's items count for the totals calculation.
      var typeName = types[i].replace('-', '_');
      Drupal.settings.garmentbox_production.delivery_data[nid][typeName].items_count = itemsCount;
    }

    // Update the IL and missing rows.
    table.find('tr.inventory-line[data-variant-nid="' + nid + '"],tr.missing[data-variant-nid="' + nid + '"]').each(function(i, row) {
      self.updateRowPrice($(row), itemPrice);
    });
  },

  // Update the production price of a specific row.
  updateRowPrice: function(row, itemPrice) {
    // Select the quantity from the input or from the td.
    var query = 'td.size-quantity';
    if (row.hasClass('received') || row.hasClass('defective') || row.hasClass('inventory-line')) {
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
    for (nid in Drupal.settings.garmentbox_production.delivery_data) {
      var variantReceivedItems = Drupal.settings.garmentbox_production.delivery_data[nid]['received'].items_count;
      receivedItems += variantReceivedItems;
      receivedItemsPrice += variantReceivedItems * (Drupal.settings.garmentbox_production.delivery_data[nid].item_price / 100);
    }

    $(context).find('input#edit-total-items-new').val(receivedItems);
    $(context).find('input#edit-production-cost-new').val('$' + Drupal.formatNumber(receivedItemsPrice, 2));
  },

  // Ask the user to set which items should be declared missing when there are
  // not enough received.
  missingItemsNotice: function(context, nid, tid, removeNotice) {
    var table = $(context).find('table#delivery-inventory');

    // Reveal the IL rows.
    var rows =  table.find('tr.inventory-line[data-variant-nid="' + nid + '"]');
    var inputs = rows.find('td[data-tid="' + tid + '"] input');
    if (!removeNotice) {
      rows.show().removeClass('hidden');
      table.find('tr.original[data-variant-nid="' + nid + '"] a.collapsed').removeClass('collapsed');
      // Set a warning on the inputs of the missing size.
      inputs.removeAttr('disabled').addClass('error custom');
    }
    else {
      // When the missing error is removed, restore the original quantity.
      inputs.each(function(i, input) {
        var lineNid = $(input).data('line-nid');
        var quantity = Drupal.settings.garmentbox_production.delivery_data[nid]['received'].lines[lineNid].quantity[tid];
        $(input).val(quantity).attr('disabled', 'disabled').removeClass('error');
      });
    }
  },

  // When the quantity is amended on an IL with missing quantity, show a row for
  // creating a new IL for the missing quantity.
  updateMissingData: function(table, variantNid, tid) {
    // Sum the quantities on the ILs; When the amount is same as the received
    // the problem is solved.
    var lineTotal = 0;
    // Make sure all the IL inputs have valid values before marking the missing
    // as OK.
    var inputError = false;

    table.find('tr.inventory-line[data-variant-nid="' + variantNid + '"] td[data-tid="' + tid + '"] input').each(function(i, input) {
      var lineNid = $(input).data('line-nid');
      var originalQuantity = Drupal.settings.garmentbox_production.delivery_data[variantNid]['original'].lines[lineNid].quantity[tid];
      var quantity = parseInt($(input).val());
      if (isNaN(quantity) || quantity < 0) {
        inputError = true;
      }
      else if (quantity < originalQuantity) {
        var missingRow = table.find('tr.missing[data-variant-nid="' + variantNid + '"][data-inventory-line-ref="' + lineNid + '"]');
        missingRow.show().removeClass('hidden');
        var missing = $('<span>').text(originalQuantity - quantity);
        missingRow.find('td[data-tid="' + tid + '"]').append(missing);
      }

      lineTotal += quantity;
    });

    if (inputError) {
      return;
    }

    var received = table.find('tr.received[data-variant-nid="' + variantNid + '"] td[data-tid="' + tid + '"] input').val();
    var received = parseInt(received);
    if (!isNaN(received) && received > 0 && received == lineTotal) {
      // The missing quantity was deducted successfuly from the ILs; Mark them
      // as OK.
      table.find('tr.inventory-line[data-variant-nid="' + variantNid + '"] td[data-tid="' + tid + '"] input').removeClass('error');
    }
  }
};

})(jQuery);
