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

$line_item_id = $row->commerce_line_item_field_data_commerce_line_items_line_item_;
$line_item = commerce_line_item_load($line_item_id);
if (!empty($line_item->data['idplates_labelbuilder']['label'])) {
  /** @var Label $label */
  $label = $line_item->data['idplates_labelbuilder']['label'];
  $output = l($output, '/labelbuilder/customize/' . $label->getNid() . '/' . $label->getSizeTid() . '/' . $label->getLayoutTid(), array('html' => TRUE));
}

?>

<?php print $output; ?>