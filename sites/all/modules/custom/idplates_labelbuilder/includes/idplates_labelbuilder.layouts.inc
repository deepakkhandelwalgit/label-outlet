<?php

/**
 * @file
 */

/**
 * Custom form callback for Label Builder Layout section.
 *
 * @param $form
 * @param $form_state
 * @param $product
 *
 * @return mixed
 */
function idplates_labelbuilder_layout_form($form, &$form_state, $product) {
  $label = new Label();

  if (!empty($_SESSION['idplates']['label'])) {
    $label = $_SESSION['idplates']['label'];
  }

  $product_wrapper = entity_metadata_wrapper('commerce_product', $product);
  $layouts_wrapper = $product_wrapper->field_layout_options;
  $style = !empty($form_state['values']['styles']) ? $form_state['values']['styles'] : 'BAR';
  $options = array();

  $ajax = array(
    'callback' => 'idplates_label_builder_preview_ajax_callback',
    'wrapper' => 'idplates-labelbuilder-preview-ajax-wrapper',
    'method' => 'replace',
    'effect' => 'fade',
    'progress' => array(),
  );

  foreach ($layouts_wrapper as $layout_wrapper) {
    $layout = $layout_wrapper->value();
    $image = $layout_wrapper->field_ll_image->value();
    if (strpos($layout->name, $style) !== FALSE) {
      $options[$layout->tid] = theme('idplates_labelbuilder_layout', array(
          'path' => $image['uri'],
          'layout' => $layout->name,
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
  $form['column_left']['styles'] = array(
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

  $form['column_left']['layouts'] = array(
    '#type' => 'radios',
    '#title' => t('Layouts'),
    '#options' => $options,
    '#required' => TRUE,
    '#prefix' => '<div id="idplates-labelbuilder-layout-ajax-wrapper">',
    '#suffix' => '</div>',
    '#ajax' => $ajax,
  );

  $form['column_left']['back'] = array(
    '#type' => 'button',
    '#value' => t('PREV: SIZE'),
  );
  $form['column_left']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('NEXT: DETAILS'),
  );

  $label->setLayoutTid($form_state['values']['layouts']);
  $form_state['label'] = $label;
  idplates_label_builder_get_label_preview($form, $form_state);

  return $form;
}

/**
 * Custom validate callback for Label Builder Layout section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_layout_form_validate($form, &$form_state) {
  if (strpos($form_state['values']['op'], 'PREV') !== FALSE) {
    drupal_goto('labelbuilder/size/' . $form_state['label']->getNid());
  }
}

/**
 * Custom submit callback for Label Builder Layout section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_layout_form_submit($form, &$form_state) {
  $form_state['label']->setLayoutTid($form_state['values']['layouts']);
  $_SESSION['idplates']['layout'] = $form_state['label']->getLayoutTid();

  $form_state['redirect'] = 'labelbuilder/customize/' . $form_state['label']->getSizeTid();
}

function idplates_label_builder_layout_ajax_callback($form, $form_state) {
  return $form['column_left']['layouts'];
}