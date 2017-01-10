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
  $label = $_SESSION['idplates']['label'];
  $product = commerce_product_load($label->getSizeTid());
  $product_wrapper = entity_metadata_wrapper('commerce_product', $product);
  $form_state['product'] = $product;

  $extras = array();
  $adhesives = array();

  foreach ($product_wrapper->field_adhesive_options as $adhesive) {
    $adhesives[] = $adhesive->value();
    $adhesives[] = $adhesive;
  }

  $extras[] = $adhesives;

  $ajax = array(
    'callback' => 'idplates_label_builder_preview_ajax_callback',
    'wrapper' => 'idplates-labelbuilder-preview-ajax-wrapper',
    'method' => 'replace',
    'event' => 'change',
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

  $options = array();

  foreach ($adhesives as $adhesive) {
    //    $image = $adhesive->field_label_size->field_ls_image->value();
    //    $size = $adhesive->field_label_size->name->value();
    //    $options[$adhesive->product_id->value()] = theme('image', array(
    //        'path' => $image['uri'],
    //        'size' => $size,
    //        'attributes' => array(),
    //      )
    //    );
    $options[$adhesive->product_id] = $adhesive->title;
  }

  $form['column_left']['adhesives'] = array(
    '#type' => 'fieldset',
    '#title' => t('Adhesives'),
  );
  reset($options);
  $first_adh = key($options);
  $form['column_left']['adhesives']['adhesive_option'] = array(
    '#type' => 'radios',
    '#default_value' => $first_adh,
    '#options' => $options,
    '#required' => TRUE,
    '#ajax' => $ajax,

  );

  $selected_adhesive = !empty($form_state['values']['adhesive_option']) ? $form_state['values']['adhesive_option'] : $form['column_left']['adhesives']['adhesive_option']['#default_value'];

  $extras = array();
  $extras[] = $selected_adhesive;
  $label->extras = $extras;

  $form_state['label'] = $label;

  idplates_label_builder_get_label_preview($form, $form_state);

  $form['column_left']['back'] = array(
    '#type' => 'button',
    '#value' => t('PREV: LAYOUT'),
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
  if (strpos($form_state['values']['op'], 'PREV') !== FALSE) {
    drupal_goto('labelbuilder/customize/' . $form_state['label']->getSizeTid());
  }

}

/**
 * Custom submit callback for Label Builder Layout section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_options_form_submit($form, &$form_state) {
}
