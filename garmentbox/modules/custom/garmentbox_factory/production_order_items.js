(function ($) {

/**
 * Expand and contract variant items of specific inventory types.
 */
Drupal.behaviors.GarmentboxOrderItems = {
  attach: function (context) {
    $('.form-item-field-factory-und select').change(function(event) {
      window.location = Drupal.settings.garmentbox_factory.url + '?field_factory=' + $(event.currentTarget).val();
    });

    $('tr.expandable .item-title a').click(function(event) {
      event.preventDefault();

      var id = $(event.currentTarget).parents('tr').attr('id');
      $(event.currentTarget).parents('table').find('tr[ref="' + id + '"]').toggle();
    });

    $('tr.expandable input[type="checkbox"]').change(function(event) {
      var id = $(event.currentTarget).parents('tr').attr('id');
      var checkboxes = $(event.currentTarget).parents('table').find('tr[ref="' + id + '"] input[type="checkbox"]');
      if($(event.currentTarget).attr('checked')) {
        checkboxes.attr('checked', 'checked');
      }
      else {
        checkboxes.removeAttr('checked');
      }
    });
  }
};

})(jQuery);
