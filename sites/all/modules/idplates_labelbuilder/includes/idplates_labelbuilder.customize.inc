<?php

/**
 * Custom form callback for Label Builder Numbering & Barcode section.
 *
 * @param $form
 * @param $form_state
 *
 * @return mixed
 */
function idplates_labelbuilder_customize_form($form, &$form_state) {
  $label = $_SESSION['idplates']['label'];
  $label->setSection('customize');
  $text_fields = array(
    'a' => array(
      'title' => t('Company Name'),
      'size' => 12,
    ),
    'b' => array(
      'title' => t('1-888-555-5555'),
      'size' => 8,
    ),
    'c' => array(
      'title' => t('Additional Text'),
      'size' => 10,
    ),
  );

  $ajax = array(
    'callback' => 'idplates_label_builder_preview_ajax_callback',
    'wrapper' => 'idplates-labelbuilder-preview-ajax-wrapper',
    'method' => 'replace',
    'event' => 'change',
    'progress' => array(),
  );

  $form['breadcrumb'] = array(
    '#type' => 'item',
    '#markup' => theme('idplates_labelbuilder_breadcrumb', array(
      'current_step' => 'customize',
      'label' => $label,
    ))
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
  $form['column_left']['color'] = array(
    '#type' => 'fieldset',
    '#title' => t('Color'),
    '#attributes' => array('class' => array('container-inline')),
  );

  $form['column_left']['color']['tag_color'] = array(
    '#type' => 'jquery_colorpicker',
    '#title' => t('Tag Color'),
    '#default_value' => 'FF0000',
    '#ajax' => $ajax,
  );

  $form['column_left']['color']['text_color'] = array(
    '#type' => 'jquery_colorpicker',
    '#title' => t('Text Color'),
    '#default_value' => 'FFFFFF',
    '#ajax' => $ajax,
  );

  $form['column_left']['text_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Text'),
  );

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
    );
    $form['column_left']['text_container']['text_container_' . $key]['size_' . $key] = array(
      '#type' => 'numberfield',
      '#default_value' => $text_field['size'],
      '#ajax' => $ajax,
      '#maxlength' => 2,
      '#description' => t('pt'),
    );
    $text_input['text_' . $key] = array(
      'text' => $form_state['values']['text_' . $key],
      'size' => $form_state['values']['size_' . $key],
    );
  }

  $form['column_left']['numbering'] = array(
    '#type' => 'fieldset',
    '#title' => t('Numbering'),
    '#prefix' => '<div id="idplates-labelbuilder-numbering-ajax-wrapper">',
    '#suffix' => '</div>',
  );
  $form['column_left']['numbering']['numbering_options'] = array(
    '#type' => 'radios',
    '#options' => array(
      'no' => t('No Numbering (Blank Pad only)'),
      'custom' => t('I will supply custom numbering'),
      'consecutive' => t('Use Consecutive Number/Barcode below'),
    ),
    '#title' => t('Select the options for numbering.'),
    '#ajax' => $ajax,
    '#default_value' => 'no',
  );

  $form['column_left']['numbering']['consecutive']['digits'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline')),
  );

  $form['column_left']['numbering']['consecutive']['fixes'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('container-inline')),
  );

  //  $form['column_left']['numbering']['consecutive']['numbering_type'] = array(
  //    '#type' => 'select',
  //    '#title' => t('Starting #'),
  //    '#options' => array(
  //      'test',
  //      'test2',
  //    ),
  //  );

  $form['column_left']['numbering']['consecutive']['digits']['starting_digit'] = array(
    '#type' => 'textfield',
    '#title' => t('Starting #'),
    '#states' => array(
      'visible' => array(
        ':input[name="numbering_options"]' => array('value' => 'consecutive'),
      ),
    ),
    '#maxlength' => !empty($form_state['values']['number_of_digits']) ? $form_state['values']['number_of_digits'] : 3,
    '#size' => 3,
    '#default_value' => !empty($form_state['values']['starting_digit']) ? $form_state['values']['starting_digit'] : '001',
  );

  $form['column_left']['numbering']['consecutive']['digits']['number_of_digits'] = array(
    '#type' => 'textfield',
    '#title' => t('Digits'),
    '#states' => array(
      'visible' => array(
        ':input[name="numbering_options"]' => array('value' => 'consecutive'),
      ),
    ),
    '#default_value' => !empty($form_state['values']['number_of_digits']) ? $form_state['values']['number_of_digits'] : 3,
    '#maxlength' => 3,
    '#size' => 3,
    '#ajax' => array(
      'callback' => 'idplates_label_builder_numbering_ajax_callback',
      'wrapper' => 'idplates-labelbuilder-numbering-ajax-wrapper',
      'method' => 'replace',
      'progress' => array(
        'type' => '',
        'message' => '',
      ),
    ),
  );

  $form['column_left']['numbering']['consecutive']['fixes']['prefix'] = array(
    '#type' => 'textfield',
    '#title' => t('Prefix'),
    '#states' => array(
      'visible' => array(
        ':input[name="numbering_options"]' => array('value' => 'consecutive'),
      ),
    ),
    '#maxlength' => 3,
    '#size' => 3,
  );

  $form['column_left']['numbering']['consecutive']['fixes']['suffix'] = array(
    '#type' => 'textfield',
    '#title' => t('Suffix'),
    '#states' => array(
      'visible' => array(
        ':input[name="numbering_options"]' => array('value' => 'consecutive'),
      ),
    ),
    '#description' => t('Prefix and Suffix text does not change. Only the Consecutive number will change for each tag.'),
    '#maxlength' => 3,
    '#size' => 3,
  );

  $form['column_left']['numbering']['consecutive']['padding'] = array(
    '#type' => 'radios',
    '#title' => t('Padding'),
    '#states' => array(
      'visible' => array(
        ':input[name="numbering_options"]' => array('value' => 'consecutive'),
      ),
    ),
    '#options' => array(t('Zeros'), t('None')),
    '#default_value' => '0',
    '#ajax' => $ajax,
  );

  $form['column_left']['back'] = array(
    '#type' => 'button',
    '#value' => t('PREV: LAYOUT'),
  );

  $form['column_left']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('NEXT: OPTIONS'),
  );

  $label->setText($text_input + array(
      'color' => $form_state['values']['text_color'],
    ));

  $label->setTagColor($form_state['values']['tag_color']);
  $label->numbering = $form_state['values']['numbering_options'];
  $form_state['label'] = $label;

  idplates_label_builder_get_label_preview($form, $form_state);

  return $form;
}

/**
 * Custom validate callback for Label Builder Numbering & Barcode section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_customize_form_validate($form, &$form_state) {
  if (strpos($form_state['values']['op'], 'PREV') !== FALSE) {
    drupal_goto('labelbuilder/layout/' . $form_state['label']->getSizeTid());
  }
}

/**
 * Custom submit callback for Label Builder Numbering & Barcode section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_customize_form_submit($form, &$form_state) {
  $_SESSION['idplates']['customize'] = $form_state['values'];
  $_SESSION['idplates']['label'] = $form_state['label'];

  $form_state['redirect'] = 'labelbuilder/options';
}

function idplates_label_builder_numbering_ajax_callback($form, &$form_state) {
  return $form['column_left']['numbering'];
}
