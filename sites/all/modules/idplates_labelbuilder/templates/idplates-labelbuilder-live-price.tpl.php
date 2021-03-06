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
  // Label price table
  $product = commerce_product_load($label->getSizeTid());
  $product_wrapper = entity_metadata_wrapper('commerce_product', $product);
  $price_table_breakpoints = $product_wrapper->field_price_table->value();
  if (_idplates_labelbuilder_use_metal_price($label) && !empty($product_wrapper->field_metal_color_price_table)) {
    $price_table_breakpoints = $product_wrapper->field_metal_color_price_table->value();
  }
  foreach ($price_table_breakpoints as $breakpoint) {
    if ($breakpoint['max_qty'] < 0) {
      $price_table = $breakpoint;
      break;
    }
    if ($breakpoint['min_qty'] <= $quantity && $breakpoint['max_qty'] >= $quantity) {
      $price_table = $breakpoint;
      break;
    }
  }
  // Get Extra price tables
  foreach ($label->getExtras() as $extra) {
    $extra_product = commerce_product_load($extra['product_id']);
    if (!empty($extra_product)) {
      $extra_product_wrapper = entity_metadata_wrapper('commerce_product', $extra_product);
      if (!empty($extra_product_wrapper->field_price_table)) {
        $extras_price_table_breakpoints[$extra_product->type] = $extra_product_wrapper->field_price_table->value();
      }
    }
  }
  // Adhesive price table
  $adhesives_price_table['amount'] = 0;
  if (!empty($extras_price_table_breakpoints['adhesives'])) {
    foreach ($extras_price_table_breakpoints['adhesives'] as $breakpoint) {
      if ($breakpoint['max_qty'] < 0) {
        $adhesives_price_table = $breakpoint;
        break;
      }
      if ($breakpoint['min_qty'] <= $quantity && $breakpoint['max_qty'] >= $quantity) {
        $adhesives_price_table = $breakpoint;
        break;
      }
    }
  }

  // Intensification price table
  $intensifiers_price_table['amount'] = 0;
  if (!empty($extras_price_table_breakpoints['intensifiers'])) {
    foreach ($extras_price_table_breakpoints['intensifiers'] as $breakpoint) {
      if ($breakpoint['max_qty'] < 0) {
        $intensifiers_price_table = $breakpoint;
        break;
      }
      if ($breakpoint['min_qty'] <= $quantity && $breakpoint['max_qty'] >= $quantity) {
        $intensifiers_price_table = $breakpoint;
        break;
      }
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
              <span
                  class="idplates-labelbuilder-preview-price-total"><?php print commerce_currency_format(($price_table['amount'] + $adhesives_price_table['amount'] + $intensifiers_price_table['amount']) * $quantity, 'USD'); ?></span>
              <p
                  class="idplates-labelbuilder-preview-price-per-label"><?php print commerce_currency_format($price_table['amount'], 'USD'); ?>
                /label</p>
              <p
                  class="idplates-labelbuilder-preview-price-per-label"><?php print commerce_currency_format($adhesives_price_table['amount'], 'USD'); ?>
                /adhesive</p>
              <p
                  class="idplates-labelbuilder-preview-price-per-label"><?php print commerce_currency_format($intensifiers_price_table['amount'], 'USD'); ?>
                /intensifier</p>
            </td>
          </tr>
        </table>
      </div>
    </div>
  </div>
  <?php
}
?>
