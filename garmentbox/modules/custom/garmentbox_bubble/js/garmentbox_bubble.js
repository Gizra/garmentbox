(function ($) {

Drupal.behaviors.garmentBoxBubble = {
  attach: function(context) {
    // Open bubbles that are marked as "Open".
    for (var i in Drupal.settings.garmentbox_bubble.opened_selectors) {
      $(Drupal.settings.garmentbox_bubble.opened_selectors[i]).btOn();
    }
  }
};

})(jQuery);
