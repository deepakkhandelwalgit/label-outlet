<?php

/**
 * @file
 */

/**
 * Custom form callback for Label Builder Options section.
 *
 * @param $form
 * @param $form_state
 *
 * @return mixed
 */
function idplates_labelbuilder_options_form($form, &$form_state) {
  $ajax = array(
    'callback' => 'idplates_label_builder_preview_ajax_callback',
    'wrapper' => 'idplates-labelbuilder-preview-ajax-wrapper',
    'method' => 'replace',
    'event' => 'change',
  );

  $options = array(
    'alum' => 'alum',
    'perma' => 'perma',
    'foil' => 'foil',
  );

  $label = $_SESSION['idplates']['label'];

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

  $form['column_left']['material'] = array(
    '#type' => 'fieldset',
    '#title' => t('Material'),
  );

  $form['column_left']['material']['specs'] = array(
    '#type' => 'radios',
    '#default_value' => 'alum',
    '#options' => $options,
    '#ajax' => $ajax,
  );

  $label->specs = !empty($form_state['values']['specs']) ? $form_state['values']['specs'] : $form['column_left']['material']['specs']['#default_value'];
  $form_state['label'] = $label;

  idplates_label_builder_get_label_preview($form, $form_state);

  $form['column_left']['back'] = array(
    '#type' => 'button',
    '#value' => t('PREV: LAYOUT'),
  );

  $form['column_left']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add to Cart'),
  );

  return $form;
}

/**
 * Custom validate callback for Label Builder Layout section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_options_form_validate($form, &$form_state) {

}

/**
 * Custom submit callback for Label Builder Layout section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_options_form_submit($form, &$form_state) {
  global $user;
  $label = $_SESSION['idplates']['label'];
  $product = commerce_product_load($label->getSizeTid());
  $result = idplates_labelbuilder_add_to_cart($product, $label, $user->uid);

  $form_state['redirect'] = 'cart';

  if ($result) {
    unset($_SESSION['idplates']);
  }
}
