(function ($) {

/**
 *
 */
Drupal.behaviors.GarmentboxOrderItems = {
  attach: function (context) {
    $(context).find('.form-item-field-factory-und select').change(function(event) {
      window.location = Drupal.settings.garmentbox_factory.url + '?field_factory=' + $(event.currentTarget).val();
    });

    $(context).find('tr.expandable .item-title a').click(function(event) {
      event.preventDefault();

      var id = $(event.currentTarget).parents('tr').attr('id');
      $(event.currentTarget).parents('table').find('tr[ref="' + id + '"]').toggle();
    });

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
    });

    // Determine the class of the variants' checkboxes.
    $(context).find('tr.inventory-line input[type="checkbox"]').change(function(event) {
      var table = $(event.currentTarget).parents('table');
      var id = $(event.currentTarget).parents('tr').attr('ref');

      updateVariantCheckbox(table.find('#' + id + ' input[type="checkbox"]'));
    });

    // Update the variant checkboxes on load.
    $(context).find('.triple-checkbox').each(function(index, checkbox) {
      updateVariantCheckbox($(checkbox));
    });
  },
};

function updateVariantCheckbox(variantCheckbox) {
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
}

})(jQuery);
