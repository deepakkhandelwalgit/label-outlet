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
  $size = $_SESSION['idplates']['size'];

  $layout = $_SESSION['idplates']['layout'];

  //  $results = idplates_labelbuilder_get_label($size, $layout);
  //  $label = commerce_product_load($results['entity_id']);
  $label = taxonomy_term_load($layout);

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
    '#options' => array('red', 'blue'),
    '#default_value' => 0,
    '#title' => t('Pick one'),
    '#ajax' => array(
      'callback' => 'idplates_label_builder_preview_ajax_callback',
      'wrapper' => 'idplates-labelbuilder-preview-ajax-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $form['column_left']['text'] = array(
    '#type' => 'fieldset',
    '#title' => t('Text'),
  );
  $form['column_left']['text']['title'] = array(
    '#type' => 'textfield',
    '#default_value' => t('Property of'),
    '#ajax' => array(
      'callback' => 'idplates_label_builder_preview_ajax_callback',
      'wrapper' => 'idplates-labelbuilder-preview-ajax-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );
  $form['column_left']['text']['organization'] = array(
    '#type' => 'textfield',
    '#default_value' => t('Company Name'),
    '#ajax' => array(
      'callback' => 'idplates_label_builder_preview_ajax_callback',
      'wrapper' => 'idplates-labelbuilder-preview-ajax-wrapper',
      'method' => 'replace',
      'effect' => 'fade',
    ),
  );

  $form['column_left']['numbering'] = array(
    '#type' => 'fieldset',
    '#title' => t('Numbering'),
  );
  $form['column_left']['numbering']['options'] = array(
    '#type' => 'checkboxes',
    '#options' => array('no', 'custom', 'identical', 'consecutive'),
    '#title' => t('	Select the options for numbering.'),
  );
  $form['column_left']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Next Step'),
  );

  $label['idplates_preview']['title'] = !empty($form_state['values']['title']) ? $form_state['values']['title'] : $form['column_left']['text']['title']['#default_value'];
  $label['idplates_preview']['organization'] = !empty($form_state['values']['organization']) ? $form_state['values']['organization'] : $form['column_left']['text']['organization']['#default_value'];
  $label['idplates_preview']['color'] = !empty($form_state['values']['color_options']) ? $form_state['values']['color_options'] : $form['column_left']['color']['color_options']['#default_value'];


  $form['column_right']['preview'] = array(
    '#type' => 'item',
    '#prefix' => '<div id="idplates-labelbuilder-preview-ajax-wrapper">',
    '#suffix' => '</div>',
    '#markup' => theme('idplates_labelbuilder_preview', array(
      'label' => $label,
    )),
  );


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
  $_SESSION['idplates']['customize'] = $form_state['values']['customize'];

  $form_state['redirect'] = 'labelbuilder/size';
}

function idplates_label_builder_preview_ajax_callback($form, $form_state) {
  return $form['column_right']['preview'];
}
