<?php

/**
 * @file
 */

/**
 * Custom form callback for Label Builder Layout section.
 *
 * @param $form
 * @param $form_state
 *
 * @return mixed
 */

/**
 *
 */
function idplates_labelbuilder_layout_form($form, &$form_state, $product) {
  $product_wrapper = entity_metadata_wrapper('commerce_product', $product);
  $layouts_wrapper = $product_wrapper->field_layout_options;

  foreach ($layouts_wrapper as $layout_wrapper) {
    $layout = $layout_wrapper->value();
    $image = $layout_wrapper->field_ll_image->value();

    $options[$layout->tid] = theme('image', array(
        'path' => $image['uri'],
        'attributes' => array(),
      )
    );
  }

  $form['layouts'] = array(
    '#type' => 'radios',
    '#title' => t('Select a Layout'),
    '#options' => $options,
  );

  $form['submit'] = array('#type' => 'submit', '#value' => t('Next Step'));

  return $form;
}

/**
 * Custom validate callback for Label Builder Layout section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_layout_form_validate($form, &$form_state) {

}

/**
 * Custom submit callback for Label Builder Layout section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_layout_form_submit($form, &$form_state) {
  $tid = $form_state['values']['layouts'];
  $_SESSION['idplates']['layout'] = $tid;

  $form_state['redirect'] = 'labelbuilder/customize/' . $tid;
}
