<?php

/**
 * Implements hook_views_data().
 */
function idplates_labelbuilder_views_data() {
  $data['idplates_labelbuilder']['table']['group'] = t('IDPlates Label Builder');
  $data['idplates_labelbuilder']['table']['join'] = array(
    // Exist in all views.
    '#global' => array(),
  );

  $data['idplates_labelbuilder']['idplates_labelbuilder_level'] = array(
    'title' => t('IDPlates Label Builder Preview'),
    'help' => t('Shows the label preview on each label line item.'),
    'field' => array(
      'handler' => 'views_handler_idplates_labelbuilder_level',
      'click sortable' => TRUE,
    ),
  );

  return $data;
}
