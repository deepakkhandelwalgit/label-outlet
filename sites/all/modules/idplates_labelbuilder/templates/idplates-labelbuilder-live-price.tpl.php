<?php

/**
 * @file This template will show the user the live price preview.
 *
 * Available variables:
 * - $label: The label to preview.
 * - $quantity: The amount of labels to add to cart.
 */

$free_colors = array('000000');
$label = !empty($label) ? $label : new Label();
$quantity = !empty($quantity) ? $quantity : 100;
$tid = $label->getSizeTid();

if (!empty($tid)) {
  $product = commerce_product_load($label->getSizeTid());
  $product_wrapper = entity_metadata_wrapper('commerce_product', $product);
  $price_table_breakpoints = $product_wrapper->field_price_table->value();
  if (_idplates_labelbuilder_use_metal_price($label) && !empty($product_wrapper->field_metal_color_price_table)) {
    $price_table_breakpoints = $product_wrapper->field_metal_color_price_table->value();
  }
  foreach ($price_table_breakpoints as $breakpoint) {
    if ($breakpoint['min_qty'] <= $quantity && $breakpoint['max_qty'] >= $quantity) {
      $price_table = $breakpoint;
      break;
    }
  }
  ?>

  <div id="idplates-labelbuilder-live-price-ajax-wrapper">
    <div class="idplates-labelbuilder-live-price-wrapper">
      <div class="idplates-labelbuilder-live-price">
        <table class="idplates-labelbuilder-preview-table">
          <tr>
            <th><?php print t('COST'); ?></th>
            <td>
              <?php print commerce_currency_format($price_table['amount'] * $quantity); ?>
              <br>
              <?php print commerce_currency_format($price_table['amount']); ?> /
              label
            </td>
          </tr>
        </table>
      </div>
    </div>
  </div>
  <?php
}
?>
