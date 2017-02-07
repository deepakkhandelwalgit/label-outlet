<?php

/**
 * @file This template will show the user the label preview.
 *
 * Available variables:
 * - $label: the label to preview.
 */

$label = !empty($label) ? $label : new Label();

$product = commerce_product_load($label->getSizeTid());
$layout = taxonomy_term_load($label->getLayoutTid());
$section = $label->getSection();

if (!empty($product)) {
  $product_wrapper = entity_metadata_wrapper('commerce_product', $product);
  $image = $product_wrapper->field_label_size->field_ls_image->value();
  $label->size = $product_wrapper->field_label_size->name->value();
  if (!empty($layout)) {
    $layout_wrapper = entity_metadata_wrapper('taxonomy_term', $layout);
    $label->setLayout($layout->name);
    $image = $layout_wrapper->field_ll_image->value();
    $code = $layout_wrapper->field_layout_code->value();
  }
}

$show_logo = FALSE;
if ($fid = $label->getLogo()) {
  $file = file_load($fid);
  $uri = $file->uri;

  $url = file_create_url($uri);
  $show_logo = TRUE;
}

$no_numbering = $label->numbering === 'no' ? ' hidden' : '';
?>

<div class="idplates-labelbuilder-preview">
  <?php
  if ($section == 'customize' || $section == 'options') :
    print _idplates_labelbuilder_render_label($label, $code, $no_numbering);
  else:
    if (!empty($image)) :
      print render(theme('image', array(
        'path' => $image['uri'],
        'attributes' => array(),
      )));
    else:
      print t('Please select a size.');
    endif;
  endif; ?>


  <table class="idplates-labelbuilder-preview-table">
    <?php foreach ($label as $key => $value): ?>
    <tr>
      <th><?php print str_replace('_', ' ', $key); ?></th>
      <td><?php
        if (is_array($value)) {
          print !empty(reset($value)) ? reset($value) : '--';
        }
        else {
          print !empty($value) ? $value : '--';
        }
        ?></td>
      <?php endforeach; ?>
    </tr>
    <?php if ($show_logo): ?>
      <tr>
        <th>
          Logo
        </th>
        <td><?php print print l('Image', $url, array('query' => array('download' => '1'))); ?></td>
      </tr>
    <?php endif; ?>
  </table>
</div>
