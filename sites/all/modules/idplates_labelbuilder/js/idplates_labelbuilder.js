(function ($) {
  Drupal.behaviors.idplatesLabelBuilder = {
    attach: function (context, settings) {
      $("#edit-qty").on('pause:typing', setTimeout(function () {
            var e = jQuery.Event('keydown', {which: 13});// # Enter Key
            $(this).trigger(e);
          }, 1000)
      );

      $("#edit-qty").on('keyup', function (e) {
        $(this).trigger('pause:typing');
      });

    }
  };
})
(jQuery);
