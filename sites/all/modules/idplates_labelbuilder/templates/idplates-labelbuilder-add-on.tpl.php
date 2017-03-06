<?php

/**
 * @file This template will display the add ons buttons.
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
      <?php print $add_on->title->value(); ?>
      <!--      --><?php //print $adhesive->body->value(); ?> <br>
      <span><?php print 'For textured metal surfaces'; ?></span>
    </div>
  </div>
</div>
