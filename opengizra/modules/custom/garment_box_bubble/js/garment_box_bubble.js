(function ($) {

Drupal.behaviors.garmentBoxBubble = {
  attach: function(context) {
    // Open bubbles that are marked as "Open".
    for (var i in Drupal.settings.garment_box_bubble.opened_selectors) {
      $(Drupal.settings.garment_box_bubble.opened_selectors[i]).btOn();
    }
  }
};

})(jQuery);
