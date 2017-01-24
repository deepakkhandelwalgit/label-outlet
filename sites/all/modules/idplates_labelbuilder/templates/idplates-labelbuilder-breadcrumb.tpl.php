<?php

/**
 * @file This template will build the breadcrumb for the label builder.
 *
 * Available variables:
 * - $current_step: The current step in the label builder form.
 * - $label: The label.
 */

$steps = array(
  'size' => array(
    'title' => t('Size'),
    'arg' => $label->getNid(),
  ),
  'layout' => array(
    'title' => t('Layout'),
    'arg' => $label->getSizeTid(),
  ),
  'customize' => array(
    'title' => t('Customize'),
    'arg' => '',
  ),
  'options' => array(
    'title' => t('Options'),
    'arg' => '',
  ),
);

$disabled = FALSE;
?>
<div class="idplates-labelbuilder-breadcrumb-wrapper">
  <div class="idplates-labelbuilder-breadcrumb">
    <?php
    foreach ($steps as $key => $step):?>
      <?php
      $classes = '';
      if ($key == $current_step) {
        $classes .= ' current-step';
        $disabled = TRUE;
      }
      if ($disabled) {
        $classes .= ' disabled';
      }
      ?>
      <a class="<?php print $classes; ?>"
         href="/labelbuilder/<?php print $key . '/' . $step['arg']; ?>">
        <?php print $step['title']; ?>
      </a>
      <span class="step-arrow">
         <?php
         // Don't print ">" after last step.
         if ($step != end($steps)) {
           print ' > ';
         }
         ?>
       </span>
    <?php endforeach; ?>
  </div>
</div>
