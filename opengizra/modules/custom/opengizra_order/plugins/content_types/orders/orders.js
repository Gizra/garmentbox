(function ($) {

/**
 * Expand and contract variant items of specific inventory types.
 */
Drupal.behaviors.OpenGizraInventorySummary = {
  attach: function (context) {
    $('tr.expandable td').click(function(event) {
      event.preventDefault();
      var totalRow = $(event.currentTarget).parentsUntil('tbody');

      totalRow.parentsUntil('table').find('tr#' + totalRow.attr('ref')).toggle('fast');
      totalRow.find('.expander').toggleClass('collapsed');
    });
  }
};

})(jQuery);
