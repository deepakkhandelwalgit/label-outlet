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

  $ajax = array(
    'callback' => 'idplates_label_builder_preview_ajax_callback',
    'wrapper' => 'idplates-labelbuilder-preview-ajax-wrapper',
    'method' => 'replace',
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
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['column_left']['text_container']['text'] = array(
    '#type' => 'textfield',
    '#ajax' => $ajax,
    '#attributes' => array('placeholder' => 'Company Name'),
  );
  $form['column_left']['text_container']['text_size'] = array(
    '#type' => 'numberfield',
    '#default_value' => 12,
    '#size' => 2,
    '#maxlength' => 2,
    '#ajax' => $ajax += array('event' => 'change'),
  );
  $form['column_left']['phone_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Phone'),
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['column_left']['phone_container']['phone'] = array(
    '#type' => 'textfield',
    '#attributes' => array('placeholder' => '1-888-555-5555'),
    '#ajax' => $ajax,
  );
  $form['column_left']['phone_container']['phone_size'] = array(
    '#type' => 'numberfield',
    '#default_value' => 8,
    '#size' => 2,
    '#maxlength' => 2,
    '#ajax' => $ajax += array('event' => 'change'),
  );
  $form['column_left']['additional_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Additional Text'),
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['column_left']['additional_container']['additional'] = array(
    '#type' => 'textfield',
    '#attributes' => array('placeholder' => 'Additional Text'),
    '#ajax' => $ajax,
  );
  $form['column_left']['additional_container']['additional_size'] = array(
    '#type' => 'numberfield',
    '#default_value' => 10,
    '#size' => 2,
    '#maxlength' => 2,
    '#ajax' => $ajax += array('event' => 'change'),
  );

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

  $label->text = array(
    'color' => $form_state['values']['text_color'],
    'text' => array(
      'text' => $form_state['values']['text'],
      'size' => $form_state['values']['text_size'],
    ),
    'phone' => array(
      'text' => $form_state['values']['phone'],
      'size' => $form_state['values']['phone_size'],
    ),
    'additional' => array(
      'text' => $form_state['values']['additional'],
      'size' => $form_state['values']['additional_size'],
    ),
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
