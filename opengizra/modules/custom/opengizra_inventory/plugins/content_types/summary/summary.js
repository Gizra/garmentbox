(function ($) {

/**
 * Expand and contract variant items of specific inventory types.
 */
Drupal.behaviors.OpenGizraInventorySummary = {
  attach: function (context) {
    $('.expander').click(function(event) {
      event.preventDefault();
      var expander = $(event.currentTarget);
      var nid = expander.attr('variant-nid');

      expander.parentsUntil('table').find('tr.variant-nid-' + nid).toggle('fast');
      expander.toggleClass('colapsed');
    });

    $('tr.total').hover(function(event) {
      var nid = $(event.currentTarget).find('.expander').attr('variant-nid');
      $(event.currentTarget).parentsUntil('table').find('tr.in-total.variant-nid-' + nid).toggleClass('emphasized');
    });

  }
};

})(jQuery);
