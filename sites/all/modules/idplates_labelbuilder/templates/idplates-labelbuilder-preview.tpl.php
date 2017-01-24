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

$no_numbering = $label->numbering === 'no' ? ' hidden' : '';
?>
<div class="idplates-labelbuilder-preview">
  <?php
  if ($section == 'customize' || $section == 'options') :
    $sections = explode('/', $code);
    $size = explode('x', $label->size);
    $realW = (double) $size[0];
    $realH = (double) $size[1];
    $width = 260;
    $height = $width * $realH / $realW;
    $tag_color = !empty($label->getTagColor()) ? $label->getTagColor() : 'f00';
    $text_color = !empty($label->getText()['color']) ? $label->getText()['color'] : 'fff';
    $font_size_a = !empty($label->getText()['text_a']['size']) ? $label->getText()['text_a']['size'] : '12';
    $font_size_b = !empty($label->getText()['text_b']['size']) ? $label->getText()['text_b']['size'] : '8';
    $font_size_c = !empty($label->getText()['text_c']['size']) ? $label->getText()['text_c']['size'] : '10';

    $qr_code = array();
    $logo = array();
    $serial_number = '000001';

    $section_height = get_section_heights($code, $height);

    if (count($section_height) == 1) {
      $line_height_a = $height;
    }
    ?>

    <div class="idplates-labelbuilder-preview-wrapper"
         style="width: <?php print $width; ?>px; height: <?php print $height; ?>px;">
      <?php foreach ($sections as $index => $preview_section):
        $bg_color = 'fff';
        $current_section_height = $section_height[$index];
        if (ctype_upper($preview_section)) {
          $bg_color = $tag_color;
        }
        ?>
        <div class="idplates-labelbuilder-preview-section-wrapper"
             style="height: <?php print $current_section_height; ?>;color: <?php print '#' . $text_color; ?>; background-color: <?php print '#' . $bg_color; ?>">
          <div class="idplates-labelbuilder-preview-section">
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
                  $styles .= 'font-size:' . ${$font_size} . 'pt';
                  $content = !empty($label->getText()['text_' . $char]['text']) ? $label->getText()['text_' . $char]['text'] : t('Text ') . strtoupper($char);
                  break;
                case 'x' :
                  $classes = 'idplates-labelbuilder-preview-wrapper-barcode' . $no_numbering;
                  $content = '*' . $serial_number . '*';
                  $styles .= 'color: transparent;height:' . $section_height['barcode_height'] . 'px;margin-top:' . $section_height['barcode_margin'] . 'px;';
                  break;
                case 's' :
                  $classes = $no_numbering;
                  $styles .= 'font-size:' . $section_height['serial_height'] . 'pt;font-weight:bold;color:#000;';
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

<?php

function get_textline_count($code) {
  $count = 0;
  $textline_codes = 'ABCabc';
  foreach (str_split($textline_codes) as $char) {
    if (substr_count($code, $char)) {
      $count++;
    }
  }

  return $count;
}

function get_section_heights($code, $height) {
  $section_height = array();

  switch (get_textline_count($code)) {
    case 1:
      $section_height[0] = '28%';
      $section_height[1] = '72%';
      $section_height['barcode_height'] = $height * .72 * .6;
      $section_height['serial_height'] = $height * .72 * .33 * .5;
      $section_height['barcode_margin'] = -4;
      break;
    case 2:
      $section_height[0] = '42%';
      $section_height[1] = '58%';
      $section_height['barcode_height'] = $height * .58 * .5;
      $section_height['serial_height'] = $height * .58 * .4 * .5;
      $section_height['barcode_margin'] = -5;
      break;
    case 3:
      $section_height[0] = '37%';
      $section_height[1] = '42%';
      $section_height[2] = '21%';
      $section_height['barcode_height'] = $height * .42 * .65;
      $section_height['serial_height'] = $height * .42 * .3 * .8;
      $section_height['barcode_margin'] = 3;
      break;
    default:
      $section_height[0] = '100%';
      $section_height['barcode_height'] = $height * .5;
      $section_height['serial_height'] = $height * .25 * .8;
      $section_height['barcode_margin'] = 10;

  }

  return $section_height;
}

?>
