<?php

/**
 * Custom form callback for Label Builder Numbering & Barcode section.
 *
 * @param $form
 * @param $form_state
 * @param $term
 *
 * @return mixed
 */
function idplates_labelbuilder_customize_form($form, &$form_state, $term) {
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
  );
  $form['column_left']['numbering']['options'] = array(
    '#type' => 'radios',
    '#options' => array(
      'no' => 'no',
      'custom' => 'custom',
      'identical' => 'identical',
      'consecutive' => 'consecutive',
    ),
    '#title' => t('Select the options for numbering.'),
    '#ajax' => $ajax,
    '#default_value' => 'no',
  );
  $form['column_left']['back'] = array(
    '#type' => 'button',
    '#value' => t('PREV: LAYOUT'),
  );

  $form['column_left']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('NEXT: OPTIONS'),
  );

  $label->text = $text_input + array(
      'color' => $form_state['values']['text_color'],
    );

  $label->tag_color = $form_state['values']['tag_color'];
  $label->numbering = $form_state['values']['options'];
  $label->barcode = $form_state['values']['title'];
  $label->cost = $form_state['values']['title'];
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
