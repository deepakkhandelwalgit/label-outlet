<?php

/**
 * @file This template will show the user the label preview.
 *
 * Available variables:
 * - $label: the label to preview.
 */


$product = commerce_product_load($label->getSizeTid());
$layout = taxonomy_term_load($label->getLayoutTid());

if (!empty($product)) {
  $product_wrapper = entity_metadata_wrapper('commerce_product', $product);
  $image = $product_wrapper->field_label_size->field_ls_image->value();
  $label->size = $product_wrapper->field_label_size->name->value();
  if (!empty($layout)) {
    $layout_wrapper = entity_metadata_wrapper('taxonomy_term', $layout);
    $label->layout = $layout->name;
    $image = $layout_wrapper->field_ll_image->value();
  }
}

?>
<div class="idplates-labelbuilder-preview">
  <?php
  if (!empty($image)) {
    print render(theme('image', array(
      'path' => $image['uri'],
      'attributes' => array(),
    )));
  }
  else {
    print t('Please select a size.');
  }
  ?>

  <table class="idplates-labelbuilder-preview-table">

    <?php foreach ($label as $key => $value): ?>
    <tr>
      <th><?php print str_replace('_', ' ', $key); ?></th>
      <td><?php print !empty($value) ? $value : '--'; ?></td>
      <?php endforeach; ?>
    </tr>
  </table>
</div>
