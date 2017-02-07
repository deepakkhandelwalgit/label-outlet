(function ($) {
  Drupal.behaviors.idplatesLabelBuilder = {
    attach: function (context, settings) {

      var timer;

      $('.idplates-labelbuilder-qty-price-wrapper #edit-qty').on('keyup', function (e) {
        clearTimeout(timer);
        timer = setTimeout(function () {
          $('#' + e.target.id).blur();
          // $(document).ajaxComplete(function (event, xhr, settings) {
          //   $('.idplates-labelbuilder-qty-price-wrapper #edit-qty').focus();
          // });
        }, 800);
      });

      $('#idplates-labelbuilder-customize-form [id^="edit-text"]').on('keyup', function (e) {
        clearTimeout(timer);
        timer = setTimeout(function () {
          $('#' + e.target.id).blur();
          // $(document).ajaxComplete(function (event, xhr, settings) {
          //   console.log($(event));
          //   console.log(event);
          //   console.log(e.target.id);
          //   if (event.target.activeElement.id == e.target.id) {
          //     $('#' + e.target.id).focus();
          //   }
          // });
        }, 800);
      });


      if ($('.idplates-labelbuilder-inline').length) {
        $('.idplates-labelbuilder-inline').parent().addClass('idplates-labelbuilder-inline-wrapper');
        $('.idplates-labelbuilder-inline-wrapper p').wrapAll('<div class="idplates-labelbuilder-wrapped-paragraphs"/>')
      }

      $('.idplates-labelbuilder-inline-wrapper').each(function () {
        var $this = $(this);
        $this.find('p').wrapAll('<div class="idplates-labelbuilder-wrapped-paragraphs"/>')
        var parentHeight = 40;
        $this.height(parentHeight);
        $this.find('img.idplates-labelbuilder-logo').css('max-height', parentHeight);
      });


    }
  }
})
(jQuery);
