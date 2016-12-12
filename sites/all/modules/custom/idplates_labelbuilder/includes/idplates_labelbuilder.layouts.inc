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
  $style = !empty($form_state['values']['styles']) ? $form_state['values']['styles'] : 'BAR';
  $options = array();

  foreach ($layouts_wrapper as $layout_wrapper) {
    $layout = $layout_wrapper->value();
    $image = $layout_wrapper->field_ll_image->value();
    $sku = $product_wrapper->sku->value();
    if (strpos($layout->name, $style) !== FALSE) {
      $options[$layout->tid] = theme('idplates_labelbuilder_layout', array(
          'path' => $image['uri'],
          'sku' => $sku,
          'attributes' => array(),
        )
      );
    }
  }

  //todo jace - get style option in a better manner and line 22
  $style_options = array(
    'BAR' => 'Barcodes',
    'NUM' => 'Numbering Only',
    'TXT' => 'Text Only',
  );

  $form['styles'] = array(
    '#type' => 'radios',
    '#title' => t('Tags with:'),
    '#options' => $style_options,
    '#default_value' => 'BAR',
    '#ajax' => array(
      'callback' => 'idplates_label_builder_layout_ajax_callback',
      'wrapper' => 'idplates-labelbuilder-layout-ajax-wrapper',
      'method' => 'replace',
      'progress' => array(
        'type' => 'throbber',
        'message' => '',
      ),
    ),
  );

  $form['layouts'] = array(
    '#type' => 'radios',
    '#options' => $options,
    '#prefix' => '<div id="idplates-labelbuilder-layout-ajax-wrapper">',
    '#suffix' => '</div>',
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

function idplates_label_builder_layout_ajax_callback($form, $form_state) {
  return $form['layouts'];
}