(function ($) {

/**
 * Expand and contract variant items of specific inventory types.
 */
Drupal.behaviors.GarmentboxInventorySummary = {
  attach: function (context) {
    $('tr.expandable td a.expander:not(.expander-processed)')
    .addClass('expander-processed')
    .click(function(event) {
      event.preventDefault();
      var $totalRow = $(this).parents('tr');

      $totalRow.parentsUntil('table').find('tr#' + $totalRow.attr('ref')).toggle('fast');
      $totalRow.find('.expander').toggleClass('collapsed');
    });
  }
};

})(jQuery);
