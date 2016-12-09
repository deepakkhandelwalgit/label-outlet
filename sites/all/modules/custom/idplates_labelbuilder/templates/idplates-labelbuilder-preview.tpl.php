<?php
/**
 * @file This template will show the user the label preview.
 *
 * Available variables:
 * - $label: the label to preview.
 */

?>
<div class="idplates-labelbuilder-preview">
  <?php print $label->name; ?>
  <?php print $label['idplates_preview']['color']; ?>
  <?php print $label['idplates_preview']['title']; ?>
  <?php print $label['idplates_preview']['organization']; ?>
</div>