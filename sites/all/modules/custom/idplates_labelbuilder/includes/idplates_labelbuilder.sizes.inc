<?php

/**
 * Custom form callback for Label Builder Size section.
 *
 * @param $form
 * @param $form_state
 *
 * @return mixed
 */
function idplates_labelbuilder_size_form($form, &$form_state) {
  $vocab = taxonomy_vocabulary_machine_name_load(IDPLATES_LABELBUILDER_SIZES_VOCAB);
  $sizes = taxonomy_get_tree($vocab->vid);

  foreach ($sizes as $size) {
    $options[$size->name] = t($size->description);
  }

  $form['sizes'] = array(
    '#type' => 'radios',
    '#title' => t('Select a Size'),
    '#options' => $options,
    '#description' => t('Desc'),
  );

  $form['submit'] = array('#type' => 'submit', '#value' => t('Next Step'));

  return $form;
}

/**
 * Custom validate callback for Label Builder Size section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_size_form_validate($form, &$form_state) {

}

/**
 * Custom submit callback for Label Builder Layout section.
 *
 * @param $form
 * @param $form_state
 */
function idplates_labelbuilder_size_form_submit($form, &$form_state) {
  $_SESSION['idplates']['size'] = $form_state['values']['sizes'];

  $form_state['redirect'] = 'labelbuilder/layout';
}
