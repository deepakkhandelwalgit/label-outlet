<?php

/**
 * @file This template will render the hanging tag loop.
 * - $label: The label to preview.
 * - $code: The layout code.
 */

?>
<canvas id="idplates-labelbuilder-hanging-tag-canvas"
        style="background-color: #<?php print _idplates_labelbuilder_get_hanging_tag_color($label, $code); ?>"></canvas>
<script type="application/javascript">
  var canvas = document.getElementById('idplates-labelbuilder-hanging-tag-canvas');
  if (canvas.getContext) {
    var ctx = canvas.getContext('2d');
    // resize the canvas to fill browser window dynamically
    window.addEventListener('resize', resizeCanvas, false);

    function resizeCanvas() {
      //todo jace: get height for responsive
      canvas.width = 259;
      canvas.height = 120;
      ctx.fillStyle = '#000000';
      ctx.moveTo(259, 120);
      ctx.lineTo(259, 85);
      ctx.arcTo(259, 75, 250, 75, 10);
      ctx.lineTo(160, 75);
      ctx.arcTo(152, 75, 152, 87, 5);
      ctx.arc(123, 62, 35, .20 * Math.PI, 1.95 * Math.PI);
      ctx.arcTo(160, 60, 180, 60, 10);
      ctx.lineTo(250, 60);
      ctx.arcTo(259, 60, 259, 50, 10);
      ctx.lineTo(259, 10);
      ctx.stroke();
      ctx.fillStyle = '#FFFFFF';
      ctx.fill();
    }
  }
  resizeCanvas();
</script>
