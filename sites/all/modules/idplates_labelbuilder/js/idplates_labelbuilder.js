(function ($) {

  Drupal.ajax.prototype.commands.idplates_labelbuilder_remove_code_chars = function (ajax, response, status) {
    if (response.code == 128) {
      var input = $('#edit-starting-digit').val();
      input = input.replace(/[-.$/+%]/gi, '');
      $('#edit-starting-digit').val(input);
    }
    if (response.code == 39) {
      var input = $('#edit-starting-digit').val();
      input = input.replace(/[a-z]/g, '');
      $('#edit-starting-digit').val(input);
    }
  }

  Drupal.behaviors.idplatesLabelBuilder = {
    attach: function (context, settings) {
      var timer;
      var selectors = '.idplates-labelbuilder-qty-price-wrapper #edit-qty, ' +
          '#idplates-labelbuilder-customize-form [id^="edit-text"], ' +
          '#idplates-labelbuilder-customize-form [id^="edit-tag-color-hex"], ' +
          '#idplates-labelbuilder-customize-form [id^="edit-text-color-hex"], ' +
          '#idplates-labelbuilder-customize-form [id^="edit-starting-digit"], ' +
          '#idplates-labelbuilder-customize-form [id^="edit-number-of-digit"], ' +
          '#idplates-labelbuilder-customize-form [id^="edit-prefix"], ' +
          '#idplates-labelbuilder-customize-form [id^="edit-suffix"], ' +
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

      // Hex code digits
      $('#edit-text-hex, #edit-tag-hex', context).on('keypress', function (e) {
        var regex = new RegExp("^[a-fA-F0-9]+$");
        var key = String.fromCharCode(!event.charCode ? event.which : event.charCode);
        if (!regex.test(key)) {
          event.preventDefault();
          return false;
        }
      });


      // Allowed characters: 0-9A-Z-.$/+%
      $('#edit-starting-digit', context).on('keypress', function (event) {
        var code = $('select#edit-numbering-type option:selected').val();
        var key = String.fromCharCode(!event.charCode ? event.which : event.charCode);
        var regex;
        if (code == 39) {
          // Code 39 Digits
          regex = new RegExp("^[A-Z0-9\-\.\$\/\+\%]+$");
        } else {
          regex = new RegExp("^[A-z0-9]+$");
        }
        if (!regex.test(key)) {
          event.preventDefault();
          return false;
        }
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
