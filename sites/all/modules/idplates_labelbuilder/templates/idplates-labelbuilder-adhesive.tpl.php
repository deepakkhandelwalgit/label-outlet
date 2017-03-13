<?php

/**
 * @file This template will display the adhesive buttons.
 */

$attributes = $variables['attributes'];
$attributes['src'] = file_create_url($variables['path']);

foreach (array('width', 'height', 'alt', 'title') as $key) {
  if (isset($variables[$key])) {
    $attributes[$key] = $variables[$key];
  }
}

?>
<div class="idplates-labelbuilder-adhesive-wrapper">
  <div class="idplates-labelbuilder-adhesive-table">
    <div class="idplates-labelbuilder-adhesive-img-wrapper">
      <img <?php print drupal_attributes($attributes); ?>/>
    </div>
  </div>
  <div class="idplates-labelbuilder-adhesive-info-wrapper">
    <div class="idplates-labelbuilder-adhesive-info">
      <p><?php print $adhesive->title->value(); ?></p>
      <p class="description"><?php print $adhesive->field_product_description->value(); ?></p>
    </div>
  </div>
</div>
