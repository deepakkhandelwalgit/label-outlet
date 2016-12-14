<?php

/**
 * @file This template will display the size preview.
 *
 */

$attributes = $variables['attributes'];
$attributes['src'] = file_create_url($variables['path']);

foreach (array('width', 'height', 'alt', 'title') as $key) {

  if (isset($variables[$key])) {
    $attributes[$key] = $variables[$key];
  }
}

?>
<div class="idplates-labelbuilder-size-wrapper">
  <div class="idplates-labelbuilder-size-table">
    <div class="idplates-labelbuilder-size-img-wrapper">
      <img <?php print drupal_attributes($attributes); ?>/>
    </div>
  </div>
  <div class="idplates-labelbuilder-size-info-wrapper">
    <?php print $size; ?>
  </div>
</div>
