/**
 * @file
 *   Smoother animation when closing and opening a fieldset on line-sheet page.
 */

(function($) {
Drupal.behaviors.smoothCollapse = {
  attach: function() {
  $('.fieldset-legend .fieldset-title').click(function(event) {
    $this = $(this);
    $this.parents('fieldset.collapsible').find('.jcarousel-container.jcarousel-container-horizontal').toggle('fast', 'swing');
  });
  }
};
})(jQuery);
