(function ($) {

// Open bubbles that are marked as "Open".
Drupal.behaviors.garmentBoxBubbleOpen = {
  attach: function(context) {
    for (var i in Drupal.settings.garmentbox_bubble.opened_selectors) {
      $(Drupal.settings.garmentbox_bubble.opened_selectors[i]).btOn();
    }
  }
};

// Hide all bubbles when overlay is opened and reveal them when it's closed.
Drupal.behaviors.garmentBoxBubbleOverlay = {
  attach: function (context) {
    $(document)
      .bind('drupalOverlayOpen', function() {
        $(context).find('.bt-wrapper').hide();
      })
      .bind('drupalOverlayClose', function() {
        $(context).find('.bt-wrapper').show();
      })
  }
}

})(jQuery);
