<?php

/**
 * Custom form callback for Label Builder Layout section.
 *
 * @param $form
 * @param $form_state
 *
 * @return mixed
 */
function idplates_labelbuilder_layout_form($form, &$form_state) {
  $vocab = taxonomy_vocabulary_machine_name_load(IDPLATES_LABELBUILDER_LAYOUTS_VOCAB);
  $layouts = taxonomy_get_tree($vocab->vid);

  foreach ($layouts as $layout) {
    $options[$layout->name] = t($layout->description);
  }

  $form['layouts'] = array(
    '#type' => 'radios',
    '#title' => t('Select a Layout'),
    '#options' => $options,
    '#description' => t('Desc'),
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
  $_SESSION['idplates']['layout'] = $form_state['values']['layouts'];

  $form_state['redirect'] = 'labelbuilder/numbering_barcode';
}
