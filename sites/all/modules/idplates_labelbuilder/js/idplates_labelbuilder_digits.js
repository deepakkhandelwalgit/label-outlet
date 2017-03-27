(function ($) {

  Drupal.ajax.prototype.commands.idplates_labelbuilder_remove_code_chars = function (ajax, response, status) {
    if (response.code == 39) {
      var serial = $('#edit-starting-digit').val();
      var prefix = $('#edit-prefix').val();
      var suffix = $('#edit-suffix').val();
      serial = serial.replace(/[a-z]/g, '');
      prefix = prefix.replace(/[a-z]/g, '');
      suffix = suffix.replace(/[a-z]/g, '');
      $('#edit-starting-digit').val(serial);
      $('#edit-prefix').val(serial);
      $('#edit-suffix').val(serial);
    }
  }
})
(jQuery);
