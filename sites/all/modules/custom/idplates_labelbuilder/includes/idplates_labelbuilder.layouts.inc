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
  $styles = taxonomy_get_tree($vocab->vid);

  $layouts = array();

  foreach ($styles as $style) {
    $children = taxonomy_get_children($style->tid);
    if (!empty($children)) {
      foreach ($children as $child) {
        $layouts[$style->name][$child->tid] = $child->name;
      }
    }
  }

  foreach ($layouts as $style => $layout) {
    foreach ($layout as $key => $term) {
      $options[$key] = t($term);
    }
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

  $form_state['redirect'] = 'labelbuilder/customize';
}
