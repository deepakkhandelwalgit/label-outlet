<?php

/**
 * Implements hook_views_default_views_alter().
 */
function idplates_labelbuilder_views_default_views_alter(&$views) {
  // Alter only the 'view_name_of_interest' view.
  if (array_key_exists('commerce_line_item_table', $views)) {
    dpm($views['commerce_line_item_table']);

  }

}
