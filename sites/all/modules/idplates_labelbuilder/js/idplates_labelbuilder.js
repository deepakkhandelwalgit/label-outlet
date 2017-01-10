(function ($) {
  Drupal.behaviors.idplatesLabelBuilder = {
    attach: function (context, settings) {

      var timer;

      $(".idplates-labelbuilder-qty-price-wrapper #edit-qty").on('keyup', function (e) {
        var $this = $(this);
        clearTimeout(timer);
        timer = setTimeout(function () {
          $this.blur();
          $this.focus();
        }, 600);
      });

    }
  }
})
(jQuery);
