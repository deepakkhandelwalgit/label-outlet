<?php

/**
 * @file This template will display the extras buttons.
 */

$attributes = $variables['attributes'];
$attributes['src'] = file_create_url($variables['path']);

foreach (array('width', 'height', 'alt', 'title') as $key) {
  if (isset($variables[$key])) {
    $attributes[$key] = $variables[$key];
  }
}

?>
<div class="idplates-labelbuilder-extras-wrapper">
  <div class="idplates-labelbuilder-extras-table">
    <div class="idplates-labelbuilder-extras-img-wrapper">
      <img <?php print drupal_attributes($attributes); ?>/>
    </div>
  </div>
  <div class="idplates-labelbuilder-extras-info-wrapper">
    <div class="idplates-labelbuilder-extras-info">
      <?php print $intensification->title->value() ?>

      <!--      $intsf_label = str_replace('_', ' ', $intensification->sku);-->
      <!--      $intensification_options[$intensification->product_id] = ucwords($intsf_label);-->
      <!--      --><?php //print $extras->body->value(); ?> <br>
      <span><?php print 'For better outdoor UV durability'; ?></span>
    </div>
  </div>
</div>
