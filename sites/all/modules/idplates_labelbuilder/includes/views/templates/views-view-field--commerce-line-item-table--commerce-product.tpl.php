<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */

$line_item_id = $row->{$field->field_alias};
$line_item = commerce_line_item_load($line_item_id);

$line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);

$label = !empty($line_item->data['idplates_labelbuilder']['label']) ? $line_item->data['idplates_labelbuilder']['label'] : NULL;

$unique_layout = '';

if (!empty($label) && $is_admin) {
  if ($layout = taxonomy_term_load($label->getLayoutTid())) {
    $layout_wrapper = entity_metadata_wrapper('taxonomy_term', $layout);
    $unique_layout = $layout_wrapper->field_layout_form->value();
  }

  $output = theme('idplates_labelbuilder_preview', array(
    'label' => $label,
    'backend' => TRUE,
    'unique_layout' => $unique_layout,
  ));

  print $output;
}
