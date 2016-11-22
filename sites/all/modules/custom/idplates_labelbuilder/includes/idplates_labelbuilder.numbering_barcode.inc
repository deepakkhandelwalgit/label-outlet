<?php

/**
 * Custom form callback for Label Builder Numbering & Barcode section.
 *
 * @param $form
 * @param $form_state
 *
 * @return mixed
 */
function idplates_labelbuilder_numbering_barcode_form($form, &$form_state) {
  $size = $_SESSION['idplates']['size'];

  $layout = $_SESSION['idplates']['layout'];

  $labels = idplates_labelbuilder_get_labels($size, $layout);

  $options = array();
  foreach ($labels as $label) {
    $product = commerce_product_load($label->product_id);
    $options[$product->product_id] = t($product->title);
  }

  $form['numbering_barcodes'] = array(
    '#type' => 'radios',
    '#title' => t('Select a Numbering & Barcode'),
    '#options' => $options,
    '#description' => t('Desc'),
  );

  $form['submit'] = array('#type' => 'submit', '#value' => t('Next Step'));

  return $form;
}

/**
 * Custom validate callback for Label Builder Numbering & Barcode section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_numbering_barcode_form_validate($form, &$form_state) {

}

/**
 * Custom submit callback for Label Builder Numbering & Barcode section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_numbering_barcode_form_submit($form, &$form_state) {
  $_SESSION['idplates']['numbering_barcode'] = $form_state['values']['numbering_barcodes'];

  $form_state['redirect'] = 'labelbuilder/size';
}
