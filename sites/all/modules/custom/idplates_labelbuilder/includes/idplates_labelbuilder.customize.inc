<?php

/**
 * Custom form callback for Label Builder Numbering & Barcode section.
 *
 * @param $form
 * @param $form_state
 *
 * @return mixed
 */
function idplates_labelbuilder_customize_form($form, &$form_state, $term) {
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
  $form['column_left']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Next Step'),
  );

  $label = array();
  $label['product_id'] = $_SESSION['idplates']['size'];
  $label['layout'] = $term;
  $label['idplates_preview']['title'] = !empty($form_state['values']['title']) ? $form_state['values']['title'] : $form['column_left']['text']['title']['#default_value'];
  $label['idplates_preview']['organization'] = !empty($form_state['values']['organization']) ? $form_state['values']['organization'] : $form['column_left']['text']['organization']['#default_value'];
  $label['idplates_preview']['color'] = !empty($form_state['values']['color_options']) ? $form_state['values']['color_options'] : $form['column_left']['color']['color_options']['#default_value'];
  $label['idplates_preview']['numbering_options'] = !empty($form_state['values']['options']) ? $form_state['values']['options'] : $form['column_left']['numbering']['options']['#default_value'];

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
