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
  $ajax = array(
    'callback' => 'idplates_labelbuilder_preview_ajax_callback',
    'wrapper' => 'idplates-labelbuilder-preview-ajax-wrapper',
    'method' => 'replace',
    'progress' => array(),
  );

  if (!empty($_SESSION['idplates']['label'])) {
    $label = $_SESSION['idplates']['label'];
  }
  $label->setSection('layouts');

  $product_wrapper = entity_metadata_wrapper('commerce_product', $product);
  $layouts = $product_wrapper->field_layout_options->value();
  drupal_set_title(node_load($label->getNid())->title);

  $options = array();
  foreach ($layouts as $layout) {
    $layout_wrapper = entity_metadata_wrapper('taxonomy_term', $layout);
    if (!empty($layout_wrapper->field_ll_image)) {
      $image = $layout_wrapper->field_ll_image->value();
    }
    $style_layout = substr($layout->name, 0, 3);
    $options[$style_layout][$layout->tid] = theme('idplates_labelbuilder_layout', array(
        'path' => $image['uri'],
        'layout' => $layout->name,
        'attributes' => array(),
      )
    );
  }

  // Creates array of styles with available layouts.
  $style_options = array(
    'BAR' => 'Barcodes',
    'NUM' => 'Numbering Only',
    'TXT' => 'Text Only',
  );
  $style_options = array_intersect_key($style_options, $options);

  if (!empty($form_state['input']['styles'])) {
    $style = $form_state['input']['styles'];
  }
  else {
    reset($options);
    $style = key($options);
  }

  $default_layout = key($options[$style]);
  $layout_tid = $label->getLayoutTid();
  if (array_key_exists($layout_tid, $options)) {
    $default_layout = $layout_tid;
  }

  $form['breadcrumb'] = array(
    '#type' => 'item',
    '#markup' => theme('idplates_labelbuilder_breadcrumb', array(
      'current_step' => 'layout',
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
  $form['column_left']['styles'] = array(
    '#type' => 'radios',
    '#title' => t('Tags with:'),
    '#options' => $style_options,
    '#default_value' => $style,
    '#ajax' => array(
      'callback' => 'idplates_label_builder_layout_ajax_callback',
      'wrapper' => 'idplates-labelbuilder-layout-ajax-wrapper',
      'method' => 'replace',
      'progress' => array(),
    ),
  );

  $form['column_left']['layouts'] = array(
    '#type' => 'radios',
    '#title' => t('Layouts'),
    '#options' => $options[$style],
    '#default_value' => $default_layout,
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

  $selected_layout = !empty($form_state['values']['layouts']) ? $form_state['values']['layouts'] : $default_layout;
  $label->setLayoutTid($selected_layout);
  $form_state['label'] = $label;
  idplates_labelbuilder_get_label_preview($form, $form_state);

  return $form;
}

/**
 * Custom validate callback for Label Builder Layout section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_layout_form_validate($form, &$form_state) {
  if (!empty($form_state['values']['op']) && strpos($form_state['values']['op'], 'PREV') !== FALSE) {
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
