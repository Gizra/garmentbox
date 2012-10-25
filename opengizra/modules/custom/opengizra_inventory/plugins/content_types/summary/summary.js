(function ($) {

/**
 * Expand and contract variant items of specific inventory types.
 */
Drupal.behaviors.OpenGizraInventorySummary = {
  attach: function (context) {
    $('tr.expandable td').click(function(event) {
      event.preventDefault();
      var totalRow = $(event.currentTarget).parentsUntil('tbody');
      totalRow.parentsUntil('table').find('tr.variant-nid-' + totalRow.attr('variant-nid')).toggle('fast');
      totalRow.find('.expander').toggleClass('collapsed');
    });

    $('tr.expandable').hover(function(event) {
      var nid = $(event.currentTarget).attr('variant-nid');
      $(event.currentTarget).parentsUntil('table').find('tr.in-total.variant-nid-' + nid).toggleClass('emphasized');
    });

  }
};

})(jQuery);
