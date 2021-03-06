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
function idplates_labelbuilder_size_form($form, &$form_state, $node) {
  $label = new Label();

  if (!empty($_SESSION['idplates']['label'])) {
    $label = $_SESSION['idplates']['label'];
  }

  $label->setSection('size');

  $ajax = array(
    'callback' => 'idplates_labelbuilder_preview_ajax_callback',
    'wrapper' => 'idplates-labelbuilder-preview-ajax-wrapper',
    'method' => 'replace',
    'progress' => array(),
  );

  $display_wrapper = entity_metadata_wrapper('node', $node);
  $variations_wrapper = $display_wrapper->field_mt_product;
  $options = array();

  foreach ($variations_wrapper as $variation_wrapper) {
    $image = $variation_wrapper->field_label_size->field_ls_image->value();
    $size = $variation_wrapper->field_label_size->name->value();
    $options[$variation_wrapper->product_id->value()] = theme('idplates_labelbuilder_size', array(
        'path' => $image['uri'],
        'size' => $size,
        'attributes' => array(),
      )
    );
  }

  $form['breadcrumb'] = array(
    '#type' => 'item',
    '#markup' => theme('idplates_labelbuilder_breadcrumb', array(
      'current_step' => 'size',
      'label' => $label,
    )),
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
  $form['column_left']['sizes'] = array(
    '#type' => 'radios',
    '#title' => t('Label Size'),
    '#options' => $options,
    '#required' => TRUE,
    '#ajax' => $ajax,
  );

  $form['column_left']['back'] = array(
    '#type' => 'button',
    '#value' => t('PREV: PRODUCTS'),
    '#limit_validation_errors' => array(),
  );
  $form['column_left']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('NEXT: LAYOUTS'),
  );

  $label->setNid($node->nid);
  if (!empty($form_state['values']['sizes'])) {
    $label->setSizeTid($form_state['values']['sizes']);
  }
  $form_state['label'] = $label;

  idplates_labelbuilder_get_label_preview($form, $form_state);
  drupal_set_title($node->title);

  return $form;
}

/**
 * Custom validate callback for Label Builder Size section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_size_form_validate($form, &$form_state) {
  if (!empty($form_state['values']['op']) && strpos($form_state['values']['op'], 'PREV') !== FALSE) {
    drupal_goto('labelbuilder');
  }
}

/**
 * Custom submit callback for Label Builder Layout section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_size_form_submit($form, &$form_state) {
  $form_state['label']->setSizeTid($form_state['values']['sizes']);
  $_SESSION['idplates']['label'] = $form_state['label'];

  $form_state['redirect'] = 'labelbuilder/layout/' . $form_state['label']->getSizeTid();
}
