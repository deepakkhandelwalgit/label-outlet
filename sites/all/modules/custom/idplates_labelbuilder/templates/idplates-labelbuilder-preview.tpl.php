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
    $label->layout = $layout->name;
    $image = $layout_wrapper->field_ll_image->value();
  }
}

?>
<div class="idplates-labelbuilder-preview">
  <?php
  if ($section == 'customize' || $section == 'options') :

    $code = 'AB/xs/C';
    $sections = explode('/', $code);
    $section0_height = '';
    $section1_height = '';
    $section2_height = '';
    $size = explode('x', $label->size);
    $realW = (double) $size[0];
    $realH = (double) $size[1];
    $width = 260;
    $height = $width * $realH / $realW;
    $tag_color = !empty($label->tag_color) ? $label->tag_color : 'f00';
    $text_color = !empty($label->text['color']) ? $label->text['color'] : 'fff';
    $font_size_a = !empty($label->text['text_a']['size']) ? $label->text['text_a']['size'] : '12';
    $font_size_b = !empty($label->text['text_b']['size']) ? $label->text['text_b']['size'] : '8';
    $font_size_c = !empty($label->text['text_c']['size']) ? $label->text['text_c']['size'] : '10';
    $font_size_s = !empty($label->text['serial_number']['size']) ? $label->text['serial_number']['size'] : '12';

    $barcode = array();
    $qr_code = array();
    $logo = array();
    $serial_number = '000001';
    $serial_number_height = .5;

    $line_height_a = $font_size_a;
    $line_height_b = $font_size_b;
    $line_height_c = $font_size_c;
    $line_height_s = $font_size_s;

    switch (count($sections)) {
      case 1:
        $section0_height = '100%';
        $line_height_a = $height;
        break;
      case 2:
        $section0_height = '40%';
        $section1_height = '60%';
        break;
      case 3:
        $section0_height = '40%';
        $section1_height = '45%';
        $section2_height = '15%';
        break;
    }
    ?>

    <div class="idplates-labelbuilder-preview-wrapper"
         style="width: <?php print $width; ?>px; height: <?php print $height; ?>px;">
      <?php foreach ($sections as $index => $preview_section):
        $bg_color = 'fff';
        $current_section_height = 'section' . $index . '_height';
        if (ctype_upper($preview_section)) {
          $bg_color = $tag_color;
        }
        ?>
        <div class="idplates-labelbuilder-preview-section"
             style="text-align: center;font-weight: bold;height: <?php print ${$current_section_height}; ?>;color: <?php print '#' . $text_color; ?>; background-color: <?php print '#' . $bg_color; ?>">
          <?php
          $markup = '';
          foreach (str_split($preview_section) as $char) :
            $char = strtolower($char);
            $styles = '';
            $classes = '';
            switch ($char) :
              case 'a' :
              case 'b' :
              case 'c' :
                $font_size = 'font_size_' . $char;
                $line_height = 'line_height_' . $char;
                $styles .= 'font-size:' . ${$font_size} . 'pt;line-height:' . ${$line_height} . 'pt;';
                $content = !empty($label->text['text_' . $char]['text']) ? $label->text['text_' . $char]['text'] : t('Text ') . strtoupper($char);
                break;
              case 'x' :
                $classes = 'idplates-labelbuilder-preview-wrapper-barcode';
                $content = '*' . $serial_number . '*';
                $styles .= 'color: transparent;font-size:14pt;';
                break;
              case 's' :
                $styles .= 'font-size:' . $font_size_s . 'pt;line-height:' . $font_size_s . 'pt;font-weight:bold;color:#000;';
                $content = $serial_number;
                break;
              case 'm' :
                $content = theme('image', array(
                  'path' => drupal_get_path('module', 'idplates_labelbuilder') . '/gfx/qr_code.png',
                  'attributes' => array(),
                ));
                break;
              case 'l' :
                break;
            endswitch;
            $markup .= '<p class="' . $classes . '" style="' . $styles . '">' . $content . '</p>';

          endforeach;
          print $markup; ?>
        </div>
      <?php endforeach; ?>
    </div>

    <?php
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
      <td><?php print !empty($value) ? $value : '--'; ?></td>
      <?php endforeach; ?>
    </tr>
  </table>
</div>
