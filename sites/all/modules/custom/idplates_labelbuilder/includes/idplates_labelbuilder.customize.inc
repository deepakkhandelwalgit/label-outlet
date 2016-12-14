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
  $ajax = array(
    'callback' => 'idplates_label_builder_preview_ajax_callback',
    'wrapper' => 'idplates-labelbuilder-preview-ajax-wrapper',
    'method' => 'replace',
    'effect' => 'fade',
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
  $form['column_left']['color']['color_options'] = array(
    '#type' => 'radios',
    '#options' => array('red' => 'red', 'blue' => 'blue'),
    '#default_value' => 'red',
    '#title' => t('Pick one'),
    '#ajax' => $ajax,
  );

  $form['column_left']['text'] = array(
    '#type' => 'fieldset',
    '#title' => t('Text'),
  );
  $form['column_left']['text']['title'] = array(
    '#type' => 'textfield',
    '#default_value' => t('Property of'),
    '#ajax' => $ajax,
  );
  $form['column_left']['text']['organization'] = array(
    '#type' => 'textfield',
    '#default_value' => t('Company Name'),
    '#ajax' => $ajax,
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

  $label->text = $form_state['values']['title'];
  $label->text_color = $form_state['values']['color_options'];
  $label->tag_color = $form_state['values']['color_options'];
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
