<?php

/**
 * @file This template will show the user the label preview.
 *
 * Available variables:
 * - $label: the label to preview.
 */


$product = commerce_product_load($label->getSizeTid());
$layout = taxonomy_term_load($label->getLayoutTid());
$section = $label->getSection();

if (!empty($product)) {
  $product_wrapper = entity_metadata_wrapper('commerce_product', $product);
  $image = $product_wrapper->field_label_size->field_ls_image->value();
  $label->size = $product_wrapper->field_label_size->name->value();
  if (!empty($layout)) {
    $layout_wrapper = entity_metadata_wrapper('taxonomy_term', $layout);
    $label->layout = $layout->name;
    $image = $layout_wrapper->field_ll_image->value();
  }
}

?>
<div class="idplates-labelbuilder-preview">
  <?php
  if ($section == 'customize') {

    $code = 'T-P-b-s-A';
    $size = explode('x', $label->size);
    $realW = (double) $size[0];
    $realH = (double) $size[1];
    $width = 260;
    $height = $width * $realH / $realW;
    $tag_color = $label->tag_color ?: 'f00';
    $text_color = $label->text['color'] ?? 'fff';
    $font_size_t = $label->text['text']['size'] ?: '12';
    $font_size_p = $label->text['phone']['size'] ?: '8';
    $font_size_a = $label->text['additional']['size'] ?: '10';
    $font_size_s = $label->text['serial_number']['size'] ?: '14';

    $barcode = array();
    $qr_code = array();
    $logo = array();
    $serial_number = '1000101';
    $serial_number_height = .5;

    $classes = 'idplates-labelbuilder-preview-section ';
    ?>

    <div class="idplates-labelbuilder-preview-wrapper"
         style="width: <?php print $width; ?>px; height: <?php print $height; ?>px;">
      <?php foreach (explode('-', $code) as $char) {
        $styles = '';
        $markup = '';
        if (ctype_upper($char)) {
          $styles .= 'background-color:#' . $tag_color . ';';
        }
        ?>
        <?php
        switch (strtolower($char)) {
          case 't' :
            $styles .= 'font-size:' . $font_size_t . 'pt;padding-top:8px;line-height:' . $font_size_t / 2 . 'pt;text-align: center; color:#' . $text_color . ';height:' . $height * .30 . 'px';
            $markup = $label->text['text']['text'] ?: t('Company Name');
            break;
          case 'b' :
            $styles .= 'font-family: barcode, Arial;font-size: 30px';
            $markup = '*' . $serial_number . '*';
            break;
          case 's' :
            //          $styles .= 'font-size:' . $font_size_s . 'pt;text-align: center; color:#000;height:' . $height * $serial_number_height . 'px';
            //          $markup = $serial_number;
            break;
          case 'p' :
            $styles .= 'font-size:' . $font_size_p . 'pt;line-height:' . $font_size_p / 2 . 'pt;text-align: center; color:#' . $text_color . ';height:' . $height * .10 . 'px';
            $markup = $label->text['phone']['text'] ?: '1-888-555-5555';
            break;
          case 'a' :
            $styles .= 'font-size:' . $font_size_a . 'pt;text-align: center; color:#' . $text_color . ';height:' . $height * .2 . 'px';
            $markup = $label->text['additional']['text'] ?: t('Additional Text');
            break;
          case 'q' :
            break;
          case 'l' :
            break;
        }

        ?>

        <div style="<?php print $styles; ?>">
          <?php print $markup; ?>
        </div>
      <?php }; ?>
    </div>

    <?php
  }
  else {

    if (!empty($image)) {
      print render(theme('image', array(
        'path' => $image['uri'],
        'attributes' => array(),
      )));
    }
    else {
      print t('Please select a size.');
    }
  } ?>


  <table class="idplates-labelbuilder-preview-table">
    <?php foreach ($label as $key => $value): ?>
    <tr>
      <th><?php print str_replace('_', ' ', $key); ?></th>
      <td><?php print !empty($value) ? $value : '--'; ?></td>
      <?php endforeach; ?>
    </tr>
  </table>
</div>
