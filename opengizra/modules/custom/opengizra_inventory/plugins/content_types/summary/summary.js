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

  }
};

})(jQuery);
