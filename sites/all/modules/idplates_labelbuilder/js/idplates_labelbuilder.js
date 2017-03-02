(function ($) {
  Drupal.behaviors.idplatesLabelBuilder = {
    attach: function (context, settings) {
      var timer;
      var selectors = '.idplates-labelbuilder-qty-price-wrapper #edit-qty, ' +
          '#idplates-labelbuilder-customize-form [id^="edit-text"], ' +
          '#idplates-labelbuilder-options-form [id^="edit-notes"]';

      $(selectors, context).on('keyup', function (e) {
        // get keycode of current keypress event
        var code = (e.keyCode || e.which);
        // do nothing if it's home, end, arrow keys, shift, ctrl, alt
        if (code == 35 || code == 36 || code == 37 || code == 38 || code == 39 || code == 40 || code == 16 || code == 17 || code == 18) {
          return;
        }

        clearTimeout(timer);
        timer = setTimeout(function () {
          $('#' + e.target.id).change();
          localStorage.inputToFocus = e.target.id;
        }, 800);
      });

      // Get the input just used, and refocus after ajax reloads the preview.
      var $inputToFocus = $('#' + localStorage.inputToFocus);
      if ($inputToFocus.length) {
        $inputToFocus.focus();
        var val = $inputToFocus.val();
        $inputToFocus.val(val);
        localStorage.inputToFocus = '';
      }


      if ($('.idplates-labelbuilder-inline').length) {
        $('.idplates-labelbuilder-inline').parent().addClass('idplates-labelbuilder-inline-wrapper');
      }

      $('.idplates-labelbuilder-inline-wrapper').each(function () {
        var $this = $(this);
        $this.find('img.idplates-labelbuilder-logo').closest('.idplates-labelbuilder-preview-section-wrapper').css('display', 'block');
        if (!$this.find('.idplates-labelbuilder-wrapped-paragraphs').length) {
          $this.find('p').wrapAll('<div class="idplates-labelbuilder-wrapped-paragraphs" />');
        }
        // todo jace this works for qr code
        var parentHeight = $this.parent().height();
        $this.height(parentHeight);
        $this.find('img.idplates-labelbuilder-logo').css('max-height', parentHeight);
        $this.find('img.idplates-labelbuilder-qr-code').css('height', (parentHeight * .7));
        $this.find('img.idplates-labelbuilder-qr-code').css('width', (parentHeight * .7));
      });

      $('#edit-adhesive-option-221', context).once(function () {
        console.log('hey');
        $('#edit-adhesive-option-221').prop("checked", false).trigger("click");
      });
    }
  }
  Drupal.behaviors.idplatesLabelBuilderDisableInputEnter = {
    attach: function (context, settings) {
      $('input', context).once('disable-input-enter', function () {
        $(this).keypress(function (e) {
          if (e.keyCode == 13) {
            e.preventDefault();
          }
        });
      });
    }
  }

  Drupal.behaviors.idplatesLabelBuilderDisableSubmit = {
    attach: function (context, settings) {
      if ($('#idplates-labelbuilder-size-form, #idplates-labelbuilder-layout-form').length) {

        var checked = false;
        $('#idplates-labelbuilder-size-form input, #idplates-labelbuilder-layout-form input').each(function () {
          var $this = $(this);
          if ($this.is(':checked')) {
            checked = true;
            // Break the loop.
            return false;
          }
        });

        if (checked) {
          $('#edit-submit').removeAttr('disabled');
        } else {
          $('#edit-submit').attr('disabled', 'disabled');
        }
      }
    }
  }
})
(jQuery);
