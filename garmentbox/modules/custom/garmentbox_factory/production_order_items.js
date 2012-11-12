(function ($) {

/**
 * Production order inventory lines widget behaviors.
 */
Drupal.behaviors.GarmentboxOrderItems = {
  attach: function (context) {
    var object = this;

    $(context).find('.form-item-field-factory-und select').change(function(event) {
      // The URL already has "?field_season=x" attached to it.
      window.location = Drupal.settings.garmentbox_factory.url + '&field_factory=' + $(event.currentTarget).val();
    });

    // Toggle inventory lines rows.
    $(context).find('tr.expandable .item-title a').click(function(event) {
      event.preventDefault();

      var id = $(event.currentTarget).parents('tr').attr('id');
      $(event.currentTarget).parents('table').find('tr.inventory-line[ref="' + id + '"]').toggle().toggleClass('hidden');
    });

    // Handle item variant checkbox.
    $(context).find('tr.expandable input[type="checkbox"]').change(function(event) {
      var checkbox = $(event.currentTarget);
      var id = checkbox.parents('tr').attr('id');
      var checkboxes = checkbox.parents('table').find('tr[ref="' + id + '"] input[type="checkbox"]');

      checkbox.removeClass('checked partially-checked not-checked');

      if($(event.currentTarget).attr('checked')) {
        checkboxes.attr('checked', 'checked');
        checkbox.addClass('checked');
      }
      else {
        checkboxes.removeAttr('checked');
      }

      object.updateVariantCost(checkbox.parents('table'), id);
    });

    // Determine the class of the variants' checkboxes.
    $(context).find('tr.inventory-line input[type="checkbox"]').change(function(event) {
      var table = $(event.currentTarget).parents('table');
      var id = $(event.currentTarget).parents('tr').attr('ref');

      object.updateVariantCheckbox(table.find('#' + id + ' input[type="checkbox"]'));
      object.updateVariantCost(table, id);
    });

    // Update the variant checkboxes on load.
    $(context).find('.triple-checkbox').each(function(index, checkbox) {
      object.updateVariantCheckbox($(checkbox));
      var id = $(checkbox).parents('tr').attr('id');
      object.updateVariantCost($(checkbox).parents('table'), id);
    });

    // Show the "Add more items" row.
    $(context).find('.add-inventory-line a').click(function(event) {
      event.preventDefault();
      var id = $(event.currentTarget).parents('tr').attr('id');
      var table = $(event.currentTarget).parents('table');
      var newLine = table.find('tr.new-inventory-line[ref="' + id + '"]');
      $(event.currentTarget).toggleClass('opened');

      if ($(event.currentTarget).hasClass('opened')) {
        // TODO: Enable the inputs.
        newLine.show().removeClass('hidden');
        $(event.currentTarget).text(Drupal.t('Cancel'));
      }
      else {
        // TODO: Disable the inputs.
        newLine.hide().addClass('hidden');;
        $(event.currentTarget).text(Drupal.t('Add more items'));
      }
    });
  },

  // Update the "triple checkbox" on item-variant rows when thier inevntory
  // lines change.
  updateVariantCheckbox: function(variantCheckbox) {
    var id = variantCheckbox.parents('tr').attr('id');
    var table = variantCheckbox.parents('table');
    var checked = table.find('tr[ref="' + id + '"] input[type="checkbox"]:checked').length;
    var total = table.find('tr[ref="' + id + '"] input[type="checkbox"]').length;

    variantCheckbox.removeClass('checked partially-checked not-checked');

    if (total - checked == 0) {
      // All are checked.
      variantCheckbox.attr('checked', 'checked');
      variantCheckbox.addClass('checked');
    }
    else if (checked == 0) {
      // None are checked.
      variantCheckbox.removeAttr('checked');
      variantCheckbox.addClass('not-checked');
    }
    else {
      // Some are checked.
      variantCheckbox.attr('checked', 'checked');
      variantCheckbox.addClass('partially-checked');
    }
  },

  // Re-calculate variant production cost as inventory lines change.
  updateVariantCost: function(table, id) {
    var variant_nid = id.substring(8);
    var item_price = Drupal.settings.garmentbox_factory.inventory_lines_data[variant_nid].item_price / 100;
    var items_count = 0;

    // Count the items on checked inventory lines.
    table.find('tr.inventory-line[ref="' + id + '"] td:first-child input[type="checkbox"]:checked').each(function(i, element) {
      items_count += Drupal.settings.garmentbox_factory.inventory_lines_data[variant_nid].lines[$(element).val()].items_count;
    });

    var total_price = items_count * item_price;
    table.find('tr#' + id + ' .item-price').text('$' + total_price.toFixed(2));
  }
};

})(jQuery);
