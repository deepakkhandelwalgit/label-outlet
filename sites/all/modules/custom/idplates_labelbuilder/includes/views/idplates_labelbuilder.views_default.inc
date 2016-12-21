<?php

/**
 * Implements hook_views_default_views_alter().
 */
function idplates_labelbuilder_views_default_views_alter(&$views) {
  // Alter only the 'view_name_of_interest' view.
  if (array_key_exists('commerce_line_item_table', $views)) {
    /* Field: Commerce Line item: Product */
    $views['commerce_line_item_table']->display['default']->display_options['fields']['commerce_product']['id'] = 'commerce_product';
    $views['commerce_line_item_table']->display['default']->display_options['fields']['commerce_product']['table'] = 'field_data_commerce_product';
    $views['commerce_line_item_table']->display['default']->display_options['fields']['commerce_product']['field'] = 'commerce_product';
    $views['commerce_line_item_table']->display['default']->display_options['fields']['commerce_product']['label'] = 'Label';
    $views['commerce_line_item_table']->display['default']->display_options['fields']['commerce_product']['settings'] = array(
      'show_quantity' => 0,
      'default_quantity' => '1',
      'combine' => 1,
      'show_single_product_attributes' => 0,
      'line_item_type' => 'product',
    );
  }

}
