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
  $popup = '<div class="idplates-labelbuilder-cart-info hidden" id="idplates-labelbuilder-cart-label-' . $line_item_id . '"><div class="idplates-labelbuilder-cart-info-header">' . t('Label Info') . '</div>';

  /** @var Label $label */
  $label = $line_item->data['idplates_labelbuilder']['label'];
  if ($layout = taxonomy_term_load($label->getLayoutTid())) {
    $layout_wrapper = entity_metadata_wrapper('taxonomy_term', $layout);
    $unique_layout = $layout_wrapper->field_layout_form->value();
  }

  $popup .= theme('idplates_labelbuilder_preview', array(
    'label' => $label,
    'cart' => 'true',
  ));

  $popup .= '<div class="idplates-labelbuilder-cart-info-close">x</div></div>';
  $text_a = !empty($label->getText()['text_a']['text']) ? $label->getText()['text_a']['text'] : '';
  $text_b = !empty($label->getText()['text_b']['text']) ? $label->getText()['text_b']['text'] : '';
  $text_c = !empty($label->getText()['text_c']['text']) ? $label->getText()['text_c']['text'] : '';

  $info = ' <a class="idplates-labelbuilder-cart-links idplates-labelbuilder-cart-item-info">info</a> - ';
  $duplicate = l('duplicate', '/labelbuilder/customize/' . $label->getNid() . '/' . $label->getSizeTid() . '/' . $label->getLayoutTid() . '/' . $text_a . '/' . $text_b . '/' . $text_c, array('html' => TRUE));
  $output .= $info . $duplicate . $popup;
}

?>

<?php print $output; ?>