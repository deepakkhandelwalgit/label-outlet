<?php

/**
 * @file This template will show the user the label preview.
 *
 * Available variables:
 * - $label: the label to preview.
 */

$layout_wrapper = entity_metadata_wrapper('taxonomy_term', $label['layout']);
$image = $layout_wrapper->field_ll_image->value();
?>
<div class="idplates-labelbuilder-preview">
  <?php print render(theme('image', array(
    'path' => $image['uri'],
    'attributes' => array(),
  ))); ?>
  <?php print $label['idplates_preview']['color']; ?>
  <?php print $label['idplates_preview']['title']; ?>
  <?php print $label['idplates_preview']['organization']; ?>
  <?php print $label['idplates_preview']['extra']; ?>
  <?php print $label['idplates_preview']['numbering_options']; ?>
  <?php print $label['idplates_preview']['specs']; ?>
</div>
