<?php

/**
 * @file
 */

/**
 * Custom form callback for Label Builder Size section.
 *
 * @param $form
 * @param $form_state
 *
 * @return mixed
 */

/**
 *
 */
function idplates_labelbuilder_size_form($form, &$form_state, $node) {
  $display_wrapper = entity_metadata_wrapper('node', $node);
  $variations_wrapper = $display_wrapper->field_mt_product;
  $options = array();

  foreach ($variations_wrapper as $variation_wrapper) {
    $image = $variation_wrapper->field_label_size->field_ls_image->value();
    $variation = $variation_wrapper->value();
    $options[$variation->product_id] = theme('image', array(
        'path' => $image['uri'],
        'attributes' => array(),
      )
    );
  }

  $form['sizes'] = array(
    '#type' => 'radios',
    '#title' => t('Select a Size'),
    '#options' => $options,
  );

  $form['submit'] = array('#type' => 'submit', '#value' => t('Next Step'));

  return $form;
}

/**
 * Custom validate callback for Label Builder Size section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_size_form_validate($form, &$form_state) {

}

/**
 * Custom submit callback for Label Builder Layout section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_size_form_submit($form, &$form_state) {
  $product_id = $form_state['values']['sizes'];
  $_SESSION['idplates']['product_id'] = $product_id;

  $form_state['redirect'] = 'labelbuilder/layout/' . $product_id;
}
