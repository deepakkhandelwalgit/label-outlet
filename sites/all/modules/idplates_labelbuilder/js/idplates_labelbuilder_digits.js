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
})
(jQuery);
