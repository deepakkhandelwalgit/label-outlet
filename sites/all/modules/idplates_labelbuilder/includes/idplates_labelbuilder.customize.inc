<?php

/**
 * Custom form callback for Label Builder Numbering & Barcode section.
 *
 * @param $form
 * @param $form_state
 *
 * @return mixed
 */
function idplates_labelbuilder_customize_form($form, &$form_state, $nid, $tid, $layout_code, $text_a, $text_b, $text_c) {
  if (!empty($nid) && !empty($tid) && !empty($layout_code) && empty($_SESSION['idplates']['label'])) {
    $label = new Label();
    $label->setNid($nid);
    $label->setSizeTid($tid);
    $label->setLayoutTid($layout_code);
    $text = array(
      'text_a' => array('text' => $text_a),
      'text_b' => array('text' => $text_b),
      'text_c' => array('text' => $text_c),
    );
    $label->setText($text);
  }
  else {
    $label = $_SESSION['idplates']['label'];
  }
  drupal_set_title(node_load($label->getNid())->title);
  $label->setSection('customize');
  $layout_code = _idplates_labelbuilder_get_layout_code($label);
  $text_fields = _idplates_labelbuilder_create_text_fields($label);
  $default_text_color = 'FFFFFF';

  $ajax = array(
    'callback' => 'idplates_labelbuilder_preview_ajax_callback',
    'wrapper' => 'idplates-labelbuilder-preview-ajax-wrapper',
    'method' => 'replace',
    'event' => 'change',
    'progress' => array('type' => 'throbber', 'message' => ''),
  );

  $form['breadcrumb'] = array(
    '#type' => 'item',
    '#markup' => theme('idplates_labelbuilder_breadcrumb', array(
      'current_step' => 'customize',
      'label' => $label,
    )),
  );

  $form['column_left'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('column-left'),
    ),
  );

  $form['column_right'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('column-right'),
    ),
  );

  if (_idplates_labelbuilder_needs_color($layout_code)) {
    $form['column_left']['color'] = array(
      '#type' => 'fieldset',
      '#title' => t('Color'),
      '#attributes' => array('class' => array('container-inline')),
    );
  }

  $color_options = array(
    '000000' => 'BLACK',
    'FFFFFF' => 'WHITE',
    'FAE042' => 'GOLD',
    'FFFF00' => 'YELLOW',
    '0085CA' => 'BLUE',
    '00B052' => 'GREEN',
    'EDA04F' => 'COPPER',
    '781496' => 'PURPLE',
    '3342B5' => 'DARK BLUE',
    'D50032' => 'RED',
  );

  foreach ($color_options as $hexcode => $color) {
    $options[$hexcode] =
      theme('idplates_labelbuilder_color', array(
          'color' => $color,
          'hexcode' => $hexcode,
        )
      );
  }
  if (_idplates_labelbuilder_needs_tag_color($layout_code)) {
    $form['column_left']['color']['tag_color'] = array(
      '#type' => 'radios',
      '#title' => t('Background Color'),
      '#default_value' => !empty($label->getTagColor()) ? $label->getTagColor() : 'D50032',
      '#options' => $options,
      '#ajax' => $ajax,
    );
    $form['column_left']['color']['tag_color_hex'] = array(
      '#type' => 'textfield',
      '#ajax' => $ajax,
      '#description' => t('Custom hexcode: #'),
      '#maxlength' => 6,
      '#size' => 8,
    );
    $form['column_left']['color']['tag_color_desc'] = array(
      '#type' => 'item',
      '#prefix' => '<div class="idplates-labelbuilder-tag-color-description description">',
      '#suffix' => '</div>',
      '#markup' => t('* Custom hexcode will always override the color boxes.'),
    );
  }
  else {
    // Background is white, so make the default text colour red.
    $default_text_color = 'D50032';
  }

  if (_idplates_labelbuilder_needs_text_options($layout_code)) {
    $form['column_left']['color']['text_color'] = array(
      '#type' => 'radios',
      '#title' => t('Text Color'),
      '#default_value' => !empty($label->getText()['color']) ? $label->getText()['color'] : $default_text_color,
      '#options' => $options,
      '#ajax' => $ajax,
    );

    $form['column_left']['color']['text_color_hex'] = array(
      '#type' => 'textfield',
      '#ajax' => $ajax,
      '#description' => t('Custom hexcode: #'),
      '#maxlength' => 6,
      '#size' => 8,
    );

    $form['column_left']['color']['text_color_desc'] = array(
      '#type' => 'item',
      '#prefix' => '<div class="idplates-labelbuilder-text-color-description description">',
      '#suffix' => '</div>',
      '#markup' => t('* Custom hexcode will always override the color boxes.'),
    );

    $form['column_left']['color']['pantone_help'] = array(
      '#type' => 'item',
      '#prefix' => '<div class="idplates-labelbuilder-pane-help">',
      '#suffix' => '</div>',
      '#markup' => t('Find your hexcode for pantone or CMYK colors <a href="@pantone" target="_blank">here</a>.', array('@pantone' => url('pantone-to-hex'))),
    );

    $form['column_left']['text_container'] = array(
      '#type' => 'fieldset',
      '#title' => t('Text'),
    );

    $text_input = array();
    foreach ($text_fields as $key => $text_field) {
      $form['column_left']['text_container']['text_container_' . $key] = array(
        '#type' => 'container',
        '#title' => t('Text'),
        '#attributes' => array('class' => array('container-inline')),
      );
      $form['column_left']['text_container']['text_container_' . $key]['text_' . $key] = array(
        '#type' => 'textfield',
        '#ajax' => $ajax,
        '#title' => t('Text ' . strtoupper($key)),
        '#attributes' => array('placeholder' => $text_field['title']),
        '#size' => 32,
        '#required' => TRUE,
        '#default_value' => !empty($label->getText()['text_' . $key]['text']) ? $label->getText()['text_' . $key]['text'] : ${'text_' . $key},
      );

      $form['column_left']['text_container']['text_container_' . $key]['size_' . $key] = array(
        '#type' => 'numberfield',
        '#default_value' => $text_field['size'],
        '#ajax' => $ajax,
        '#maxlength' => 2,
        '#description' => t('pt'),
        '#default_value' => !empty($label->getText()['size_' . $key]) ? $label->getText()['size_' . $key] : 12,
      );

      $text_input['text_' . $key] = array(
        'text' => !empty($form_state['input']['text_' . $key]) ? $form_state['input']['text_' . $key] : (!empty($label->getText()['text_' . $key]['text']) ? $label->getText()['text_' . $key]['text'] : ''),
        'size' => !empty($form_state['input']['size_' . $key]) ? $form_state['input']['size_' . $key] : (!empty($label->getText()['text_' . $key]['size']) ? $label->getText()['text_' . $key]['size'] : 12),
      );
    }
  }

  if (strpos(strtolower($layout_code), 'l') !== FALSE) {
    $form['column_left']['logo'] = array(
      '#type' => 'fieldset',
      '#title' => t('Logo'),
    );
    $form['column_left']['logo']['custom_logo'] = array(
      '#type' => 'managed_file',
      '#upload_location' => 'public://logos/',
      '#required' => TRUE,
      '#description' => 'Allowed file types: <strong>png gif jpg jpeg. Image dimensions less than 200px wide and 80px high will have best results.</strong>',
      '#title' => t('Logo Image File'),
      '#default_value' => !empty($label->getLogo()) ? $label->getLogo() : NULL,
      '#process' => array(
        'file_managed_file_process',
        'filefield_sources_field_process',
        'idplates_labelbuilder_managed_file_ajax_submit',
      ),
      '#upload_validators' => array(
        'file_validate_extensions' => array('gif png jpg jpeg'),
      ),
    );
    if (_idplates_labelbuilder_label_is_metallic($label)) {
      $form['column_left']['logo']['color'] = array(
        '#type' => 'container',
        '#title' => t('Text'),
        '#attributes' => array('class' => array('container-inline')),
      );
      $form['column_left']['logo']['color']['logo_color'] = array(
        '#type' => 'radios',
        '#title' => t('Logo Color'),
        '#default_value' => !empty($label->getTagColor()) ? $label->getTagColor() : 'D50032',
        '#options' => $options,
		'#markup' => t('* Logos on metal and foil are printed in monochrome and limited to one color.'),
      );
      $form['column_left']['logo']['color']['logo_color_hex'] = array(
        '#type' => 'textfield',
        '#description' => t('Custom hexcode: #'),
        '#maxlength' => 6,
        '#size' => 8,
      );
    }
  }

  $style = substr($label->getLayout(), 0, 3);

  if ((strpos(strtolower($layout_code), 's') !== FALSE && $style === 'BAR') || strtolower($layout_code) === 'm') {
    $form['column_left']['numbering'] = array(
      '#type' => 'fieldset',
      '#title' => t('Numbering'),
      '#prefix' => '<div id="idplates-labelbuilder-numbering-ajax-wrapper">',
      '#suffix' => '</div>',
    );
    if ((strpos(strtolower($layout_code), 'm') === FALSE)) {

      $form['column_left']['numbering']['numbering_type'] = array(
        '#type' => 'select',
        '#title' => t('Numbering Type'),
        '#options' => array(
          '39' => 'Code 39',
          '128' => 'Code 128',
        ),
        '#ajax' => array(
          'callback' => 'idplates_labelbuilder_remove_digits',
          'event' => 'change',
          'progress' => array('type' => '', 'message' => ''),
        ),
      );
    }

    $form['column_left']['numbering']['numbering_options'] = array(
      '#type' => 'radios',
      '#options' => array(
        'custom' => t('I will supply custom numbering'),
        'consecutive' => t('Use Consecutive Number/Barcode below'),
      ),
      '#title' => t('Select the options for numbering'),
      '#ajax' => $ajax,
      '#default_value' => !empty($label->numbering['numbering_option']) ? $label->numbering['numbering_option'] : 'consecutive',
    );

    $form['column_left']['numbering']['numbering_options']['custom']['#description'] = t('Orders requiring custom numbering will receive further instructions after order completion on how to submit their numbering values.');

    $form['column_left']['numbering']['consecutive'] = array(
      '#type' => 'fieldset',
      '#title' => 'Consecutive Options',
      '#attributes' => array('class' => array('consecutive-options indent')),
    );

    $hide_consecutive = array(
      'visible' => array(
        ':input[name="numbering_options"]' => array('value' => 'consecutive'),
      ),
    );

    $form['#attached']['js'] = array(
      drupal_get_path('module', 'idplates_labelbuilder') . '/js/idplates_labelbuilder_digits.js',
    );

    $form['column_left']['numbering']['consecutive']['digits'] = array(
      '#type' => 'container',
      '#attributes' => array('class' => array('container-inline')),
    );

    //    if (strpos(strtolower($layout_code), 'm') === FALSE) {

    $form['column_left']['numbering']['consecutive']['digits']['starting_digit'] = array(
      '#type' => 'textfield',
      '#title' => t('Serial Number'),
      '#states' => $hide_consecutive,
      '#size' => 20,
      '#ajax' => $ajax,
      '#default_value' => !empty($label->numbering['starting_digit']) ? $label->numbering['starting_digit'] : '000001',
    );

    $form['column_left']['numbering']['consecutive']['digits_description'] = array(
      '#type' => 'item',
      '#prefix' => '<div class="idplates-labelbuilder-description">',
      '#suffix' => '</div>',
      '#markup' => t('Enter starting serial number exactly as you want them printed. Include leading zeros if required'),
      '#states' => $hide_consecutive,
    );

    $form['column_left']['numbering']['consecutive']['fixes'] = array(
      '#type' => 'container',
      '#attributes' => array('class' => array('container-inline')),
    );

    $form['column_left']['numbering']['consecutive']['fixes']['prefix'] = array(
      '#type' => 'textfield',
      '#title' => t('Prefix'),
      '#default_value' => !empty($label->numbering['prefix']) ? $label->numbering['prefix'] : '',
      '#states' => $hide_consecutive,
      '#size' => 5,
      '#ajax' => $ajax,
    );

    $form['column_left']['numbering']['consecutive']['fixes']['consecutive'] = array(
      '#type' => 'item',
      '#markup' => '<div class="consecutive-placeholder">' . t('Serial <br>Number') . '</div>',
      '#states' => $hide_consecutive,
    );

    $form['column_left']['numbering']['consecutive']['fixes']['suffix'] = array(
      '#type' => 'textfield',
      '#title' => t('Suffix'),
      '#states' => $hide_consecutive,
      '#size' => 5,
      '#ajax' => $ajax,
      '#default_value' => !empty($label->numbering['suffix']) ? $label->numbering['suffix'] : '',
    );

    $form['column_left']['numbering']['consecutive']['fixes']['description'] = array(
      '#type' => 'item',
      '#markup' => t('Enter prefix and exactly as you want them printed.'),
      '#states' => $hide_consecutive,
    );

    $form['column_left']['numbering']['consecutive']['39'] = array(
      '#type' => 'item',
      '#prefix' => '<div class="idplates-labelbuilder-description code39">',
      '#suffix' => '</div>',
      '#markup' => t('Valid Code 3 of 9 characters: 0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ-.$/+%  Only uppercase letters will be accepted.'),
      '#states' => array(
        'visible' => array(
          'select[name="numbering_type"]' => array('value' => '39'),
          ':input[name="numbering_options"]' => array('value' => 'consecutive'),
        ),
      ),
    );

    //    }
    //    else {
    //      $label->numbering['numbering_type'] = '';
    //      $form['column_left']['numbering']['consecutive']['digits']['starting_digit'] = array(
    //        '#type' => 'textarea',
    //        '#title' => t('Data Matrix'),
    //        '#attributes' => array('maxlength' => 200),
    //        '#ajax' => array(
    //          'callback' => 'idplates_labelbuilder_preview_ajax_callback',
    //          'wrapper' => 'idplates-labelbuilder-preview-ajax-wrapper',
    //          'method' => 'replace',
    //          'event' => 'change',
    //          'progress' => array('type' => 'throbber', 'message' => ''),
    //        ),
    //        '#default_value' => !empty($label->numbering['starting_digit']) ? $label->numbering['starting_digit'] : '',
    //      );
    //    }
  }

  $form['column_left']['back'] = array(
    '#type' => 'button',
    '#value' => t('PREV: LAYOUT'),
    '#limit_validation_errors' => array(),
  );

  $form['column_left']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('NEXT: OPTIONS'),
  );

  if (_idplates_labelbuilder_needs_tag_color($layout_code)) {
    if (empty($form_state['input']['tag_color_hex'])) {
      $tag_color = isset($form_state['values']['tag_color']) ? $form_state['values']['tag_color'] : $form['column_left']['color']['tag_color']['#default_value'];
    }
    else {
      $tag_color = $form_state['input']['tag_color_hex'];
    }

    $label->setTagColor($tag_color);
  }

  if (empty($form_state['input']['text_color_hex'])) {
    if (isset($form_state['values']['text_color'])) {
      $text_color = $form_state['values']['text_color'];
    }
    else {
      $text_color = $default_text_color;
    }

  }
  else {
    $text_color = $form_state['input']['text_color_hex'];
  }

  if (!empty($text_color) && !empty($text_input)) {
    $label->setText($text_input + array(
        'color' => $text_color,
      ));
  }

  if (!empty($form_state['values']['custom_logo'])) {
    $label->setLogo($form_state['values']['custom_logo']);
  }

  if (!empty($form_state['values']['numbering_options'])) {
    $label->numbering = idplates_labelbuilder_build_numbering_options($form, $form_state);
  }

  $form_state['label'] = $label;

  idplates_labelbuilder_get_label_preview($form, $form_state);

  return $form;
}

/**
 * Ripping off and altering the #ajax callback function used for managed_file
 * elements.
 *
 * @see file_ajax_upload()
 */
function idplates_labelbuilder_managed_file_ajax() {
  $form_parents = func_get_args();
  $form_build_id = (string) array_pop($form_parents);

  if (empty($_POST['form_build_id']) || $form_build_id != $_POST['form_build_id']) {
    // Invalid request.
    drupal_set_message(t('An unrecoverable error occurred. The uploaded file likely exceeded the maximum file size (@size) that this server supports.', array('@size' => format_size(file_upload_max_size()))), 'error');
    $commands = array();
    $commands[] = ajax_command_replace(NULL, theme('status_messages'));

    return array('#type' => 'ajax', '#commands' => $commands);
  }

  list($form, $form_state, $form_id, $form_build_id, $commands) = ajax_get_form();

  if (!$form) {
    // Invalid form_build_id.
    drupal_set_message(t('An unrecoverable error occurred. Use of this form has expired. Try reloading the page and submitting again.'), 'error');
    $commands = array();
    $commands[] = ajax_command_replace(NULL, theme('status_messages'));

    return array('#type' => 'ajax', '#commands' => $commands);
  }

  // Get the current element and count the number of files.
  $current_element = $form;
  foreach ($form_parents as $parent) {
    $current_element = $current_element[$parent];
  }
  $current_file_count = isset($current_element['#file_upload_delta']) ? $current_element['#file_upload_delta'] : 0;

  // Process user input. $form and $form_state are modified in the process.
  drupal_process_form($form['#form_id'], $form, $form_state);

  // Retrieve the element to be rendered.
  foreach ($form_parents as $parent) {
    $form = $form[$parent];
  }

  // Add the special Ajax class if a new file was added.
  if (isset($form['#file_upload_delta']) && $current_file_count < $form['#file_upload_delta']) {
    $form[$current_file_count]['#attributes']['class'][] = 'ajax-new-content';
  }
  // Otherwise just add the new content class on a placeholder.
  else {
    $form['#suffix'] .= '<span class="ajax-new-content"></span>';
  }

  $output = theme('status_messages') . drupal_render($form);
  $js = drupal_add_js();
  $settings = call_user_func_array('array_merge_recursive', $js['settings']['data']);

  // Update the label preview.
  $label = $form_state['label'];
  $unique_layout = '';

  if (empty($form['fid']['#value'])) {
    $label->setLogo(0);
  }

  if ($layout = taxonomy_term_load($form_state['label']->getLayoutTid())) {
    $layout_wrapper = entity_metadata_wrapper('taxonomy_term', $layout);
    $unique_layout = $layout_wrapper->field_layout_form->value();
  }

  $label_preview = theme('idplates_labelbuilder_preview', array(
    'label' => $label,
    'unique_layout' => $unique_layout,
  ));

  $commands[] = ajax_command_replace('.idplates-labelbuilder-preview', $label_preview);
  $commands[] = ajax_command_replace(NULL, $output, $settings);

  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * Custom validate callback for Label Builder Numbering & Barcode section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_customize_form_validate($form, &$form_state) {

  drupal_set_title(node_load($_SESSION['idplates']['label']->getNid())->title);
  if (!empty($form_state['values']['op']) && strpos($form_state['values']['op'], 'PREV') !== FALSE) {
    drupal_goto('labelbuilder/layout/' . $form_state['label']->getSizeTid());
  }
  $label = $form_state['label'];
  $code_type = $label->numbering['numbering_type'];
  $barcode = $label->numbering['starting_digit'];
  $output = $label->numbering['prefix'] . $barcode . $label->numbering['suffix'];
  $numbering_option = $form_state['values']['numbering_options'];
  $length = (float) str_replace("'", '', explode('x', $label->size)[0]);
  if ($numbering_option === 'consecutive') {
    if ($code_type == '39' && !idplates_labelbuilder_validate_code_39($label, $output)) {
      form_set_error('starting_digit', t('The label size chosen is too small for the barcode entered. Please select a label width size larger than @length" to accommodate the length of your entered barcode.', array('@length' => $length)));
    }

    if ($code_type == '128' && !idplates_labelbuilder_validate_code_128($label, $output)) {
      form_set_error('starting_digit', t('The label size chosen is too small for the barcode entered. Please select a label width size larger than @length" to accommodate the length of your entered barcode.', array('@length' => $length)));
    }
  }

}

/**
 * Custom submit callback for Label Builder Numbering & Barcode section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_customize_form_submit($form, &$form_state) {
  global $user;

  $label = $form_state['label'];

  if (!empty($form_state['values']['custom_logo'])) {
    $label->setLogo($form_state['values']['custom_logo']);
  }

  if (!empty($form_state['values']['logo_color_hex'])) {
    $label->logo_color = $form_state['values']['logo_color_hex'];
  }
  elseif (!empty($form_state['values']['logo_color'])) {
    $label->logo_color = $form_state['values']['logo_color'];
  }

  if (!empty($form_state['values']['custom_logo']) && $file = file_load($form_state['values']['custom_logo'])) {
    // Change status to permanent.
    $file->status = FILE_STATUS_PERMANENT;
    file_save($file);
    // Record that the module (in this example, user module) is using the file.
    file_usage_add($file, 'idplates_labelbuilder', 'commerce_line_item', $user->uid);
  }

  $_SESSION['idplates']['customize'] = $form_state['values'];
  $_SESSION['idplates']['label'] = $form_state['label'];

  $form_state['redirect'] = 'labelbuilder/options';
}

/**
 * A secondary submit handler for managed files
 *
 * Forces the form to update the saved/deleted files currently uploaded to the
 * form and rebuild the form, displaying the current files and a upload-state
 * managed_file
 *
 * @param $element
 * @param $form_state
 * @param $form
 *
 * @return mixed
 */
function idplates_labelbuilder_managed_file_ajax_submit($element, &$form_state, $form) {
  $ajax_path = 'idplates_labelbuilder_managed_file/ajax/' . implode('/', $element['#array_parents']) .
    '/' . $form['form_build_id']['#value'];

  $element['upload_button']['#ajax']['path'] = $ajax_path;
  $element['remove_button']['#ajax']['path'] = $ajax_path;

  return $element;
}

function idplates_label_builder_numbering_ajax_callback($form, &$form_state) {
  return $form['column_left']['numbering'];
}

function idplates_labelbuilder_build_numbering_options($form, $form_state) {
  $label = $form_state['label'];

  return array(
    'numbering_option' => !empty($form_state['values']['numbering_options']) ? $form_state['values']['numbering_options'] : 'consecutive',
    'numbering_type' => !empty($form_state['values']['numbering_type']) ? $form_state['values']['numbering_type'] : '',
    'starting_digit' => !empty($form_state['values']['starting_digit']) ? $form_state['values']['starting_digit'] : '0',
    'number_of_digits' => !empty($form_state['values']['number_of_digits']) ? $form_state['values']['number_of_digits'] : 6,
    'prefix' => !empty($form_state['values']['prefix']) ? $form_state['values']['prefix'] : '',
    'suffix' => !empty($form_state['values']['suffix']) ? $form_state['values']['suffix'] : '',
    'padding' => !empty($form_state['values']['padding']) ? $form_state['values']['padding'] : $label->numbering['padding'],
  );
}

function _idplates_labelbuilder_create_text_fields($label, $text_a = 'Company Name', $text_b = '1-888-555-5555', $text_c = 'Additional Text') {
  $code = _idplates_labelbuilder_get_layout_code($label);

  $text_lines = !empty($code) ? _idplates_labelbuilder_get_textline_count($code) : 3;

  $text_field_defaults = array(
    'a' => array(
      'title' => t($text_a),
      'size' => 12,
    ),
    'b' => array(
      'title' => t($text_b),
      'size' => 8,
    ),
    'c' => array(
      'title' => t($text_c),
      'size' => 10,
    ),
  );

  $text_fields = array();
  $key = 'a';
  while ($text_lines > 0) {
    $text_fields[$key] = $text_field_defaults[$key];
    $key++;
    $text_lines--;
  }

  return $text_fields;
}


function _idplates_labelbuilder_get_layout_code($label) {
  $layout = taxonomy_term_load($label->getLayoutTid());
  if (!empty($layout)) {
    $layout_wrapper = entity_metadata_wrapper('taxonomy_term', $layout);
    $layout_wrapper->field_layout_code->value();

    return $layout_wrapper->field_layout_code->value();
  }

  return FALSE;
}

