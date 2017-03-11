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

  $adhesives = array();
  $intensifications = array();
  $add_ons = array();

  if (!empty($product_wrapper->field_adhesive_options)) {
    foreach ($product_wrapper->field_adhesive_options as $adhesive) {
      $adhesives[] = $adhesive;
    }
  }
  if (!empty($product_wrapper->field_intensification_options)) {
    foreach ($product_wrapper->field_intensification_options as $intensification) {
      $intensifications[] = $intensification;
    }
  }
  if (!empty($product_wrapper->field_add_on_options)) {
    foreach ($product_wrapper->field_add_on_options as $add_on) {
      $add_ons[] = $add_on;
    }
  }

  $ajax = array(
    'callback' => 'idplates_labelbuilder_preview_ajax_callback',
    'wrapper' => 'idplates-labelbuilder-preview-ajax-wrapper',
    'method' => 'replace',
    'event' => 'change',
    'progress' => array('type' => 'throbber', 'message' => ''),
  );

  $form['breadcrumb'] = array(
    '#type' => 'item',
    '#markup' => theme('idplates_labelbuilder_breadcrumb', array(
      'current_step' => 'options',
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

  $adhesive_options = array();

  foreach ($adhesives as $adhesive) {
    $image = $adhesive->field_product_image->value();
    $adhesive_options[$adhesive->product_id->value()] = theme('idplates_labelbuilder_adhesive', array(
        'path' => $image[0]['uri'],
        'adhesive' => $adhesive,
        'attributes' => array(),
      )
    );
  }
  $intensification_options = array();

  foreach ($intensifications as $intensification) {
    $image = $intensification->field_product_image->value();
    $intensification_options[$intensification->product_id->value()] = theme('idplates_labelbuilder_intensification', array(
        'path' => $image[0]['uri'],
        'intensification' => $intensification,
        'attributes' => array(),
      )
    );
  }

  $add_on_options = array();
  foreach ($add_ons as $add_on) {
    $image = $add_on->field_product_image->value();
    $add_on_options[$add_on->product_id->value()] = theme('idplates_labelbuilder_add_on', array(
        'path' => $image[0]['uri'],
        'add_on' => $add_on,
        'attributes' => array(),
      )
    );
  }

  $form['column_left']['adhesives'] = array(
    '#type' => 'fieldset',
    '#title' => t('Adhesives'),
  );
  reset($adhesive_options);
  $first_adh = key($adhesive_options);
  $form['column_left']['adhesives']['adhesive_option'] = array(
    '#type' => 'radios',
    '#default_value' => $first_adh,
    '#options' => $adhesive_options,
    '#required' => TRUE,
    '#ajax' => $ajax,
  );
  $form['column_left']['adhesives']['adhesive_option']['#ajax']['progress'] = array();

  if (!empty($intensification_options)) {
    $form['column_left']['intensifications'] = array(
      '#type' => 'fieldset',
      '#title' => t('Intensifications'),
    );
    $form['column_left']['intensifications']['intensification_option'] = array(
      '#type' => 'checkboxes',
      '#options' => $intensification_options,
      '#required' => TRUE,
      '#ajax' => $ajax,
    );
  }
  $form['column_left']['intensifications']['intensification_option']['#ajax']['progress'] = array();


  $form['column_left']['add_ons'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add ons'),
  );
  $form['column_left']['add_ons']['add_on_options'] = array(
    '#type' => 'checkboxes',
    '#options' => $add_on_options,
    '#ajax' => $ajax,
  );
  $form['column_left']['add_ons']['add_on_options']['#ajax']['progress'] = array();

  $form['column_left']['add_ons']['description'] = array(
    '#type' => 'item',
    '#markup' => t('Note: You will receive 1 Surface Cleaner and 1 Application Roller for FREE with your order. For additional supplies, select the product needed from the above options.'),
    '#prefix' => '<div class="idplates-labelbuilder-description">',
    '#suffix' => '</div>',
  );

  $form['column_left']['instructions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Instructions to the printer'),
  );

  $form['column_left']['instructions']['review'] = array(
    '#type' => 'radios',
    '#title' => t('Design Review'),
    '#options' => array(
      'pro' => t('I\'d like a professional to tweak my design at no extra charge. Use my text and graphics, but make layout adjustments for the best appearance.'),
      'exact' => t('Use my design exactly.'),
    ),
    '#default_value' => 'pro',
    '#ajax' => $ajax,
  );

  $form['column_left']['instructions']['notes'] = array(
    '#type' => 'textarea',
    '#title' => t('Anything else? Let us know.'),
    '#attributes' => array('placeholder' => 'Start typing here...'),
    '#default_value' => '',
    '#ajax' => $ajax,
  );

  $selected_adhesive = !empty($form_state['values']['adhesive_option']) ? $form_state['values']['adhesive_option'] : $first_adh;
  $selected_intensification = !empty($form_state['values']['intensification_option']) ? $form_state['values']['intensification_option'] : array();
  $selected_add_ons = !empty($form_state['values']['add_on_options']) ? $form_state['values']['add_on_options'] : array();
  $qty = !empty($form_state['values']['qty']) ? $form_state['values']['qty'] : 100;
  $extras = array();
  $extras[] = array(
    'product_id' => $selected_adhesive,
    'qty' => $qty,
  );
  foreach ($selected_intensification as $intensification) {
    if (!empty($intensification)) {
      $extras[] = array(
        'product_id' => $intensification,
        'qty' => $qty,
      );
    }
  }
  foreach ($selected_add_ons as $selected_add_on) {
    if (!empty($selected_add_on)) {
      $extras[] = array(
        'product_id' => $selected_add_on,
        'qty' => '1',
      );
    }
  }
  $label->setExtras($extras);
  $label->review = !empty($form_state['values']['review']) ? $form_state['values']['review'] : $form['column_left']['instructions']['review']['#default_value'];
  $label->notes = !empty($form_state['values']['notes']) ? $form_state['values']['notes'] : '';

  $form_state['label'] = $label;

  idplates_labelbuilder_get_label_preview($form, $form_state);
  drupal_set_title(node_load($label->getNid())->title);

  $form['column_left']['back'] = array(
    '#type' => 'button',
    '#value' => t('PREV: CUSTOMIZE'),
    '#limit_validation_errors' => array(),
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
  if (!empty($form_state['values']['op']) && strpos($form_state['values']['op'], 'PREV') !== FALSE) {
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
