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
  $add_ons = array();

  foreach ($product_wrapper->field_adhesive_options as $adhesive) {
    $adhesives[] = $adhesive->value();
  }
  foreach ($product_wrapper->field_add_on_options as $add_on) {
    $add_ons[] = $add_on;
  }


  $ajax = array(
    'callback' => 'idplates_labelbuilder_preview_ajax_callback',
    'wrapper' => 'idplates-labelbuilder-preview-ajax-wrapper',
    'method' => 'replace',
    'event' => 'change',
    'progress' => '',
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
    //    $image = $adhesive->field_label_size->field_ls_image->value();
    //    $size = $adhesive->field_label_size->name->value();
    //    $options[$adhesive->product_id->value()] = theme('image', array(
    //        'path' => $image['uri'],
    //        'size' => $size,
    //        'attributes' => array(),
    //      )
    //    );
    $adhesive_options[$adhesive->product_id] = $adhesive->title;
  }

  $add_on_options = array();
  foreach ($add_ons as $add_on) {
    $add_on_options[$add_on->product_id->value()] = $add_on->title->value();
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

  //  $form['column_left']['cleaner'] = array(
  //    '#type' => 'fieldset',
  //    '#title' => t('Cleaner'),
  //  );
  //  $form['column_left']['cleaner']['cleaner_options'] = array(
  //    '#type' => 'checkboxes',
  //    '#options' => array(
  //      'cleaner' => t('Surface Cleaner - 8oz Spray Bottle'),
  //    ),
  //  );

  //  $form['column_left']['application_aid'] = array(
  //    '#type' => 'fieldset',
  //    '#title' => t('Application Aid'),
  //  );
  //  $form['column_left']['application_aid']['roller'] = array(
  //    '#type' => 'checkboxes',
  //    '#options' => array(
  //      'cleaner' => t('Application Roller'),
  //    ),
  //  );

  $form['column_left']['add_ons'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add ons'),
  );
  $form['column_left']['add_ons']['add_on_options'] = array(
    '#type' => 'checkboxes',
    '#options' => $add_on_options,
    '#ajax' => $ajax,
  );
  $form['column_left']['add_ons']['description'] = array(
    '#type' => 'item',
    '#markup' => t('Note: You will receive 1 Spray Bottle and 1 Application roller for FREE with your order..... IDPLATES:PLZ TELL ME WHAT TO SAY HERE!!!'),
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

  $selected_adhesive = !empty($form_state['values']['adhesive_option']) ? $form_state['values']['adhesive_option'] : $form['column_left']['adhesives']['adhesive_option']['#default_value'];
  $selected_add_ons = !empty($form_state['values']['add_on_options']) ? $form_state['values']['add_on_options'] : NULL;
  $extras = array();
  $extras[] = array(
    'product_id' => $selected_adhesive,
    'qty' => $form_state['values']['qty'],
  );
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

  $form['column_left']['back'] = array(
    '#type' => 'button',
    '#value' => t('PREV: CUSTOMIZE'),
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
