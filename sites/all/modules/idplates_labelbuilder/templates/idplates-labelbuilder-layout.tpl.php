<?php

/**
 * @file This template will display the layout preview.
 */

$attributes = $variables['attributes'];
$attributes['src'] = file_create_url($variables['path']);

foreach (array('width', 'height', 'alt', 'title') as $key) {

  if (isset($variables[$key])) {
    $attributes[$key] = $variables[$key];
  }
}

?>
<div class="idplates-labelbuilder-layout-wrapper">
  <div class="idplates-labelbuilder-layout-table">
    <div class="idplates-labelbuilder-layout-img-wrapper">
      <img <?php print drupal_attributes($attributes); ?>/>
    </div>
  </div>
</div>
