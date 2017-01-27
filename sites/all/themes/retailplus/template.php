<?php

/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return
 *   A string containing the breadcrumb output.
 */
function retailplus_breadcrumb($variables) {

	$breadcrumb = $variables['breadcrumb'];
	$breadcrumb_separator = theme_get_setting('breadcrumb_separator','retailplus');

	if (!empty($breadcrumb)) {
	$breadcrumb[] = drupal_get_title();
	return '<div>' . implode(' <span class="breadcrumb-separator">' . $breadcrumb_separator . '</span>', $breadcrumb) . '</div>';
	}

}

/**
 * Add classes to block.
 */
function retailplus_preprocess_block(&$variables) {

	$variables['title_attributes_array']['class'][] = 'title';
	$variables['classes_array'][]='clearfix';

}

/**
 * Override or insert variables into the html template.
 */
function retailplus_preprocess_html(&$variables) {

	$color_scheme = theme_get_setting('color_scheme');

	if ($color_scheme != 'default') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/style-' .$color_scheme. '.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-1'  ||
		theme_get_setting('slogan_font_family')=='slff-1' ||
		theme_get_setting('headings_font_family')=='hff-1' ||
		theme_get_setting('paragraph_font_family')=='pff-1') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/merriweather-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-2'  ||
		theme_get_setting('slogan_font_family')=='slff-2' ||
		theme_get_setting('headings_font_family')=='hff-2' ||
		theme_get_setting('paragraph_font_family')=='pff-2') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/sourcesanspro-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-3'  ||
		theme_get_setting('slogan_font_family')=='slff-3' ||
		theme_get_setting('headings_font_family')=='hff-3' ||
		theme_get_setting('paragraph_font_family')=='pff-3') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/ubuntu-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-4'  ||
		theme_get_setting('slogan_font_family')=='slff-4' ||
		theme_get_setting('headings_font_family')=='hff-4' ||
		theme_get_setting('paragraph_font_family')=='pff-4') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/ptsans-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-5'  ||
		theme_get_setting('slogan_font_family')=='slff-5' ||
		theme_get_setting('headings_font_family')=='hff-5' ||
		theme_get_setting('paragraph_font_family')=='pff-5') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/roboto-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-6'  ||
		theme_get_setting('slogan_font_family')=='slff-6' ||
		theme_get_setting('headings_font_family')=='hff-6' ||
		theme_get_setting('paragraph_font_family')=='pff-6') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/opensans-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-7'  ||
		theme_get_setting('slogan_font_family')=='slff-7' ||
		theme_get_setting('headings_font_family')=='hff-7' ||
		theme_get_setting('paragraph_font_family')=='pff-7') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/lato-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-8'  ||
		theme_get_setting('slogan_font_family')=='slff-8' ||
		theme_get_setting('headings_font_family')=='hff-8' ||
		theme_get_setting('paragraph_font_family')=='pff-8') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/roboto-condensed-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-9'  ||
		theme_get_setting('slogan_font_family')=='slff-9' ||
		theme_get_setting('headings_font_family')=='hff-9' ||
		theme_get_setting('paragraph_font_family')=='pff-9') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/exo-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-10'  ||
		theme_get_setting('slogan_font_family')=='slff-10' ||
		theme_get_setting('headings_font_family')=='hff-10' ||
		theme_get_setting('paragraph_font_family')=='pff-10') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/roboto-slab-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-11'  ||
		theme_get_setting('slogan_font_family')=='slff-11' ||
		theme_get_setting('headings_font_family')=='hff-11' ||
		theme_get_setting('paragraph_font_family')=='pff-11') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/raleway-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-12'  ||
		theme_get_setting('slogan_font_family')=='slff-12' ||
		theme_get_setting('headings_font_family')=='hff-12' ||
		theme_get_setting('paragraph_font_family')=='pff-12') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/josefin-sans-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-14'  ||
		theme_get_setting('slogan_font_family')=='slff-14' ||
		theme_get_setting('headings_font_family')=='hff-14' ||
		theme_get_setting('paragraph_font_family')=='pff-14') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/playfair-display-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-15'  ||
		theme_get_setting('slogan_font_family')=='slff-15' ||
		theme_get_setting('headings_font_family')=='hff-15' ||
		theme_get_setting('paragraph_font_family')=='pff-15') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/philosopher-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-16'  ||
		theme_get_setting('slogan_font_family')=='slff-16' ||
		theme_get_setting('headings_font_family')=='hff-16' ||
		theme_get_setting('paragraph_font_family')=='pff-16') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/cinzel-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-17'  ||
		theme_get_setting('slogan_font_family')=='slff-17' ||
		theme_get_setting('headings_font_family')=='hff-17' ||
		theme_get_setting('paragraph_font_family')=='pff-17') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/oswald-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-18'  ||
		theme_get_setting('slogan_font_family')=='slff-18' ||
		theme_get_setting('headings_font_family')=='hff-18' ||
		theme_get_setting('paragraph_font_family')=='pff-18') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/playfairdisplaysc-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-19'  ||
		theme_get_setting('slogan_font_family')=='slff-19' ||
		theme_get_setting('headings_font_family')=='hff-19' ||
		theme_get_setting('paragraph_font_family')=='pff-19') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/cabin-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-20'  ||
		theme_get_setting('slogan_font_family')=='slff-20' ||
		theme_get_setting('headings_font_family')=='hff-20' ||
		theme_get_setting('paragraph_font_family')=='pff-20') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/notosans-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-22'  ||
		theme_get_setting('slogan_font_family')=='slff-22' ||
		theme_get_setting('headings_font_family')=='hff-22' ||
		theme_get_setting('paragraph_font_family')=='pff-22') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/droidserif-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-23'  ||
		theme_get_setting('slogan_font_family')=='slff-23' ||
		theme_get_setting('headings_font_family')=='hff-23' ||
		theme_get_setting('paragraph_font_family')=='pff-23') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/ptserif-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-24'  ||
		theme_get_setting('slogan_font_family')=='slff-24' ||
		theme_get_setting('headings_font_family')=='hff-24' ||
		theme_get_setting('paragraph_font_family')=='pff-24') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/vollkorn-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-25'  ||
		theme_get_setting('slogan_font_family')=='slff-25' ||
		theme_get_setting('headings_font_family')=='hff-25' ||
		theme_get_setting('paragraph_font_family')=='pff-25') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/alegreya-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-26'  ||
		theme_get_setting('slogan_font_family')=='slff-26' ||
		theme_get_setting('headings_font_family')=='hff-26' ||
		theme_get_setting('paragraph_font_family')=='pff-26') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/notoserif-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-27'  ||
		theme_get_setting('slogan_font_family')=='slff-27' ||
		theme_get_setting('headings_font_family')=='hff-27' ||
		theme_get_setting('paragraph_font_family')=='pff-27') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/crimsontext-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-28'  ||
		theme_get_setting('slogan_font_family')=='slff-28' ||
		theme_get_setting('headings_font_family')=='hff-28' ||
		theme_get_setting('paragraph_font_family')=='pff-28') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/gentiumbookbasic-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-29'  ||
		theme_get_setting('slogan_font_family')=='slff-29' ||
		theme_get_setting('headings_font_family')=='hff-29' ||
		theme_get_setting('paragraph_font_family')=='pff-29') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/volkhov-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-31'  ||
		theme_get_setting('slogan_font_family')=='slff-31' ||
		theme_get_setting('headings_font_family')=='hff-31' ||
		theme_get_setting('paragraph_font_family')=='pff-31') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/alegreyasc-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-32'  ||
		theme_get_setting('slogan_font_family')=='slff-32' ||
		theme_get_setting('headings_font_family')=='hff-32' ||
		theme_get_setting('paragraph_font_family')=='pff-32') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/montserrat-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-33'  ||
		theme_get_setting('slogan_font_family')=='slff-33' ||
		theme_get_setting('headings_font_family')=='hff-33' ||
		theme_get_setting('paragraph_font_family')=='pff-33') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/firasans-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	if (theme_get_setting('sitename_font_family')=='sff-34'  ||
		theme_get_setting('slogan_font_family')=='slff-34' ||
		theme_get_setting('headings_font_family')=='hff-34' ||
		theme_get_setting('paragraph_font_family')=='pff-34') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/roboto-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	drupal_add_css(path_to_theme() . '/fonts/sourcecodepro-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));

	drupal_add_css(path_to_theme() . '/fonts/playfair-display-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));

	if (isset($_SERVER['HTTPS']) && strtolower($_SERVER['HTTPS']) == 'on') {
		drupal_add_css('https://netdna.bootstrapcdn.com/font-awesome/4.2.0/css/font-awesome.css', array('type' => 'external'));
	} else {
		drupal_add_css('http://netdna.bootstrapcdn.com/font-awesome/4.2.0/css/font-awesome.css', array('type' => 'external'));
	}

	drupal_add_css(path_to_theme() . '/ie9.css', array('group' => CSS_THEME, 'browsers' => array('IE' => '(IE 9)&(!IEMobile)', '!IE' => FALSE), 'preprocess' => FALSE));

	/**
	 * Add local.css file for CSS overrides.
	 */
	drupal_add_css(drupal_get_path('theme', 'retailplus') . '/local.css', array('group' => CSS_THEME, 'type' => 'file'));

	/**
	* Add Javascript - Enable/disable Bootstrap 3 Javascript.
	*/
	if (theme_get_setting('bootstrap_js_include', 'retailplus')) {
		drupal_add_js(drupal_get_path('theme', 'retailplus') . '/bootstrap/js/bootstrap.min.js');
	}
	//EOF:Javascript

	/**
	 * Add Javascript - Enable/disable scrollTop action.
	 */
	if (theme_get_setting('scrolltop_display')) {

		drupal_add_js('jQuery(document).ready(function($) {
		$(window).scroll(function() {
			if($(this).scrollTop() != 0) {
				$("#toTop").fadeIn();
			} else {
				$("#toTop").fadeOut();
			}
		});

		$("#toTop").click(function() {
			$("body,html").animate({scrollTop:0},800);
		});

		});',
		array('type' => 'inline', 'scope' => 'header'));

	}
	//EOF:Javascript

	/**
	 * Add Javascript - Google Maps
	 */
	if (theme_get_setting('google_map_js', 'retailplus')) {

		drupal_add_js('jQuery(document).ready(function($) {

	    var map;
	    var myLatlng;
	    var myZoom;
	    var marker;

		});',
		array('type' => 'inline', 'scope' => 'header')
		);

		$google_map_latitude = theme_get_setting('google_map_latitude','retailplus');
		$google_map_longitude = theme_get_setting('google_map_longitude','retailplus');
		$google_map_zoom = (int) theme_get_setting('google_map_zoom','retailplus');
		$google_map_canvas = theme_get_setting('google_map_canvas','retailplus');
        drupal_add_js(array('retailplus' => array('google_map_latitude' => $google_map_latitude)), 'setting');
        drupal_add_js(array('retailplus' => array('google_map_longitude' => $google_map_longitude)), 'setting');
        drupal_add_js(array('retailplus' => array('google_map_canvas' => $google_map_canvas)), 'setting');
		drupal_add_js('jQuery(document).ready(function($) {

		if ($("#'.$google_map_canvas.'").length>0) {

			myLatlng = new google.maps.LatLng(Drupal.settings.retailplus[\'google_map_latitude\'], Drupal.settings.retailplus[\'google_map_longitude\']);
			myZoom = '.$google_map_zoom.';

			function initialize() {

				var mapOptions = {
				zoom: myZoom,
				mapTypeId: google.maps.MapTypeId.ROADMAP,
				center: myLatlng,
				scrollwheel: false
				};

				map = new google.maps.Map(document.getElementById(Drupal.settings.retailplus[\'google_map_canvas\']),mapOptions);

				marker = new google.maps.Marker({
				map:map,
				draggable:true,
				position: myLatlng,
                url: "https://www.google.com/maps/dir//'.$google_map_latitude.','.$google_map_longitude.'/@'.$google_map_latitude.','.$google_map_longitude.'"
				});

                google.maps.event.addListener(marker, "click", function() {
                window.open(this.url, "_blank");
                });

				google.maps.event.addDomListener(window, "resize", function() {
				map.setCenter(myLatlng);
				});

			}

			google.maps.event.addDomListener(window, "load", initialize);

		}

		});',
		array('type' => 'inline', 'scope' => 'header')
		);

	}
	//EOF:Javascript

	/**
	 * Add Javascript - Fixed header
	 */
	$fixed_header = theme_get_setting('fixed_header');
	if ($fixed_header) {

		drupal_add_js('jQuery(document).ready(function($) {

			var	headerTopHeight = $("#header-top").outerHeight(),
			headerHeight = $("#header").outerHeight();

			$(window).load(function() {
				if(($(window).width() > 767)) {
					$("body").addClass("fixed-header-enabled");
				} else {
					$("body").removeClass("fixed-header-enabled");
				}
			});

			$(window).resize(function() {
				if(($(window).width() > 767)) {
					$("body").addClass("fixed-header-enabled");
				} else {
					$("body").removeClass("fixed-header-enabled");
				}
			});

			$(window).scroll(function() {
			if(($(this).scrollTop() > headerTopHeight+headerHeight) && ($(window).width() > 767)) {
				$("body").addClass("onscroll");

				if ($("#page-container").length > 0) {
 					$("#page-container").css("paddingTop", (headerHeight)+"px");
				} else {
					$("#page").css("paddingTop", (headerHeight)+"px");
				}

			} else {
				$("body").removeClass("onscroll");
				$("#page,#page-container").css("paddingTop", (0)+"px");
			}
			});

		});',
		array('type' => 'inline', 'scope' => 'header'));

	}
	//EOF:Javascript

	/**
	 * Add Javascript - Mobile mean menu
	 */
	$responsive_meanmenu = theme_get_setting('responsive_multilevelmenu_state');
	if ($responsive_meanmenu) {
	drupal_add_css(drupal_get_path('theme', 'retailplus') . '/js/meanmenu/meanmenu.css');
	drupal_add_js(drupal_get_path('theme', 'retailplus') .'/js/meanmenu/jquery.meanmenu.fork.js', array('preprocess' => false));
		drupal_add_js('jQuery(document).ready(function($) {
			$("#main-navigation .sf-menu, #main-navigation .content>ul.menu, #main-navigation ul.main-menu").wrap("<div class=\'meanmenu-wrapper\'></div>");
			$("#main-navigation .meanmenu-wrapper").meanmenu({
				meanScreenWidth: "767",
				meanRemoveAttrs: true,
				meanMenuContainer: "#header-inside",
				meanMenuClose: ""
			});

			if ($("#header-top .sf-menu").length>0 || $("#header-top .content>ul.menu").length>0) {
			$("#header-top .sf-menu, #header-top .content>ul.menu").wrap("<div class=\'header-top-meanmenu-wrapper\'></div>");
			$("#header-top .header-top-meanmenu-wrapper").meanmenu({
				meanScreenWidth: "767",
				meanRemoveAttrs: true,
				meanMenuContainer: "#header-top-inside",
				meanMenuClose: ""
			});
			}

		});',
		array('type' => 'inline', 'scope' => 'header'));
	}
	//EOF:Javascript

	/**
	* Add Javascript for testimonial slider.
	*/
	$testimonial_effect = theme_get_setting('testimonial_slideshow_effect','retailplus');
	$testimonial_effect_time = (int) theme_get_setting('testimonial_slideshow_effect_time','retailplus')*1000;

	drupal_add_js('
	jQuery(document).ready(function($) {
		if ($(".view-testimonials .flexslider").length > 0) {
			$(window).load(function() {
			$(".view-testimonials .flexslider").fadeIn("slow");
			$(".view-testimonials .flexslider").flexslider({
				animation: "'.$testimonial_effect.'",
				slideshowSpeed: '.$testimonial_effect_time.',
				useCSS: false,
				controlNav: false,
				prevText: "",
				nextText: ""
			});
			});
		}
	});',array('type' => 'inline', 'scope' => 'footer', 'weight' => 2)
	);
	//EOF:Javascript

	/**
	* Add Javascript - Affix
	*/

	$affix_admin_height = (int)  theme_get_setting('affix_admin_height','retailplus');
	$affix_fixedHeader_height = (int) theme_get_setting('affix_fixedHeader_height','retailplus');

	drupal_add_js('jQuery(document).ready(function($) {
		if ($("#affix").length>0) {
			$(window).load(function() {

				//The #affix distance from top of the page
				var affixTop = $("#affix").offset().top;

				//We calculate the affix distance from bottom of the page
				var affixBottom = $("#footer").outerHeight(true)
				+ $("#subfooter").outerHeight(true)
				+ $("#main .region-content").outerHeight(true)
				- $("#block-system-main").outerHeight(true);

				if ($("#bottom").length>0) {
					affixBottom = affixBottom + $("#bottom").outerHeight(true);
				}

				if ($("#bottom-highlighted").length>0) {
					affixBottom = affixBottom + $("#bottom-highlighted").outerHeight(true);
				}

				if ($("#footer-top").length>0) {
					affixBottom = affixBottom + $("#footer-top").outerHeight(true);
				}

				//The #header height
				var staticHeaderHeight = $("#header").outerHeight(true);

				//The #header height onscroll while fixed (it is usually smaller than staticHeaderHeight)
				//We can not calculate it because we need to scroll first
				var fixedheaderHeight = '.$affix_fixedHeader_height.'+15;

				//The admin overlay menu height
				var adminHeight = '.$affix_admin_height.'+15;

				//We select the highest of the 2 adminHeight OR fixedheaderHeight to use
				if (fixedheaderHeight > adminHeight) {
					fixedAffixTop = fixedheaderHeight;
				} else {
					fixedAffixTop = adminHeight;
				}

				if ($(".fixed-header-enabled").length>0) {
					if ($(".logged-in").length>0) {
						affixBottom = affixBottom+staticHeaderHeight-fixedAffixTop-adminHeight+15;
						initAffixTop = affixTop-fixedAffixTop; //The fixedAffixTop is added as padding on the page so we need to remove it from affixTop
					} else {
						affixBottom = affixBottom+staticHeaderHeight-fixedheaderHeight;
						initAffixTop = affixTop-fixedheaderHeight;  //The fixedheaderHeight is added as padding on the page so we need to remove it from affixTop
					}
				} else {
					if ($(".logged-in").length>0) {
						affixBottom = affixBottom;
						initAffixTop = affixTop-adminHeight; // The adminHeight is added as padding on the page so we need to remove it from affixTop
					} else {
						affixBottom = affixBottom+adminHeight;
						initAffixTop = affixTop-15; //We reduce by 15 to make a little space between the window top and the #affix element
					}
				}

				$("#affix").affix({
		        offset: {
		          top: initAffixTop,
		          bottom: affixBottom
		        }
		    });

				$("#affix").on("affixed.bs.affix", function () {
			    	//We set through JS the inline style top position
			    	if ($(".fixed-header-enabled").length>0) {
			    		if ($(".logged-in").length>0) {
				    		$("#affix").css("top", (fixedAffixTop)+"px");
			    		} else {
			    			$("#affix").css("top", (fixedheaderHeight)+"px");
			    		}
			    	} else {
			    		if ($(".logged-in").length>0) {
			    			$("#affix").css("top", (adminHeight)+"px");
			    		} else {
			    			$("#affix").css("top", (15)+"px");
			    		}
			    	}

				});

				//We remove the inline style top position once resized bellow 991px
				$(window).resize(function() {
					if(($(window).width() <= 991)) {
						$("#affix").css("top","0");
					}
				});

			});


		}
	});',
	array('type' => 'inline', 'scope' => 'footer'));

	/**
	* Add Javascript - Node progress bar
	*/
	drupal_add_js('jQuery(document).ready(function($) {

        $(window).load(function () {
       		if ($(".post-progress").length>0){
	            var s = $(window).scrollTop(),
	            c = $(window).height(),
	            d = $(".node-main-content").outerHeight(),
	            e = $("#comments").outerHeight(true),
	            f = $(".node-footer").outerHeight(true),
	            g = $(".node-main-content").offset().top;

	            var scrollPercent = (s / (d+g-c-e-f)) * 100;
                scrollPercent = Math.round(scrollPercent);

	            if (c >= (d+g-e-f)) { scrollPercent = 100; } else if (scrollPercent < 0) { scrollPercent = 0; } else if (scrollPercent > 100) { scrollPercent = 100; }

	            $(".post-progressbar").css("width", scrollPercent + "%");
	            $(".post-progress-value").html(scrollPercent + "%");
	        }
        });

        $(window).scroll(function () {
            if ($(".post-progress").length>0){
	            var s = $(window).scrollTop(),
	            c = $(window).height(),
	            d = $(".node-main-content").outerHeight(true),
	            e = $("#comments").outerHeight(true),
	            f = $(".node-footer").outerHeight(true),
	            g = $(".node-main-content").offset().top;

                var scrollPercent = (s / (d+g-c-e-f)) * 100;
                scrollPercent = Math.round(scrollPercent);

                if (c >= (d+g-e-f)) { scrollPercent = 100; }  else if (scrollPercent < 0) { scrollPercent = 0; } else if (scrollPercent > 100) { scrollPercent = 100; }

                $(".post-progressbar").css("width", scrollPercent + "%");
                $(".post-progress-value").html(scrollPercent + "%");
            }
        });

	});',
	array('type' => 'inline', 'scope' => 'header'));

}


/**
 * Override or insert variables into the node template.
 */
function retailplus_process_node(&$vars) {

}

/**
 * Override or insert variables into the html template.
 */
function retailplus_process_html(&$vars) {
	$classes = explode(' ', $vars['classes']);
	$classes[] = theme_get_setting('sitename_font_family');
	$classes[] = theme_get_setting('slogan_font_family');
	$classes[] = theme_get_setting('headings_font_family');
	$classes[] = theme_get_setting('paragraph_font_family');
	$classes[] = theme_get_setting('layout_mode');
	$vars['classes'] = trim(implode(' ', $classes));
}

/**
 * Preprocess variables for page template.
 */
function retailplus_preprocess_page(&$variables) {

	$sidebar_first = $variables['page']['sidebar_first'];
	$sidebar_first_desktop = $variables['page']['sidebar_first_desktop'];
	$sidebar_second_mobile = $variables['page']['sidebar_second_mobile'];
	$sidebar_second = $variables['page']['sidebar_second'];
	$footer_first = $variables['page']['footer_first'];
	$footer_second = $variables['page']['footer_second'];
	$footer_third = $variables['page']['footer_third'];
	$footer_fourth = $variables['page']['footer_fourth'];
	$header_top_left = $variables['page']['header_top_left'];
	$header_top_right = $variables['page']['header_top_right'];

	/**
	 * Insert variables into the page template.
	 */
	if(($sidebar_first || $sidebar_first_desktop) && ($sidebar_second || $sidebar_second_mobile)) {
		$variables['main_grid_class'] = 'col-md-6';
		$variables['sidebar_first_grid_class'] = 'col-md-3';
		$variables['sidebar_second_grid_class'] = 'col-md-3';
	} elseif (($sidebar_first || $sidebar_first_desktop) && !($sidebar_second || $sidebar_second_mobile)) {
		$variables['main_grid_class'] = 'col-md-9';
		$variables['sidebar_first_grid_class'] = 'col-md-3 fix-first-sidebar';
	} elseif (!($sidebar_first || $sidebar_first_desktop) && ($sidebar_second || $sidebar_second_mobile)) {
		$variables['main_grid_class'] = 'col-md-8';
		$variables['sidebar_second_grid_class'] = 'col-md-4 fix-second-sidebar';
	} else {
		$variables['main_grid_class'] = 'col-md-12';
		$variables['sidebar_first_grid_class'] = '';
		$variables['sidebar_second_grid_class'] = '';
	}

	if ($header_top_left && $header_top_right) {
		$variables['header_top_left_grid_class'] = 'col-md-9';
		$variables['header_top_right_grid_class'] = 'col-md-3';
	} else {
		$variables['header_top_left_grid_class'] = 'col-md-12';
		$variables['header_top_right_grid_class'] = 'col-md-12';
	}

	if ($footer_first && $footer_second && $footer_third && $footer_fourth) {
		$variables['footer_grid_class'] = 'col-sm-3';
	} elseif ((!$footer_first && $footer_second && $footer_third && $footer_fourth) || ($footer_first && !$footer_second && $footer_third && $footer_fourth)
	|| ($footer_first && $footer_second && !$footer_third && $footer_fourth) || ($footer_first && $footer_second && $footer_third && !$footer_fourth)) {
		$variables['footer_grid_class'] = 'col-sm-4';
	} elseif ((!$footer_first && !$footer_second && $footer_third && $footer_fourth) || (!$footer_first && $footer_second && !$footer_third && $footer_fourth)
	|| (!$footer_first && $footer_second && $footer_third && !$footer_fourth) || ($footer_first && !$footer_second && !$footer_third && $footer_fourth)
	|| ($footer_first && !$footer_second && $footer_third && !$footer_fourth) || ($footer_first && $footer_second && !$footer_third && !$footer_fourth)) {
		$variables['footer_grid_class'] = 'col-sm-6';
	} else {
		$variables['footer_grid_class'] = 'col-sm-12';
	}

}

/**
* Implements hook_preprocess_maintenance_page().
*/
function retailplus_preprocess_maintenance_page(&$variables) {

	$color_scheme = theme_get_setting('color_scheme');
	if ($color_scheme != 'default') {
		drupal_add_css(drupal_get_path('theme', 'retailplus') . '/style-' .$color_scheme. '.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	}

	drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/playfair-display-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/roboto-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));
	drupal_add_css(drupal_get_path('theme', 'retailplus') . '/fonts/raleway-font.css', array('group' => CSS_THEME, 'type' => 'file', 'preprocess' => FALSE));

}

function retailplus_page_alter($page) {

	$mobileoptimized = array(
		'#type' => 'html_tag',
		'#tag' => 'meta',
		'#attributes' => array(
		'name' =>  'MobileOptimized',
		'content' =>  'width'
		)
	);
	$handheldfriendly = array(
		'#type' => 'html_tag',
		'#tag' => 'meta',
		'#attributes' => array(
		'name' =>  'HandheldFriendly',
		'content' =>  'true'
		)
	);
	$viewport = array(
		'#type' => 'html_tag',
		'#tag' => 'meta',
		'#attributes' => array(
		'name' =>  'viewport',
		'content' =>  'width=device-width, initial-scale=1'
		)
	);
	drupal_add_html_head($mobileoptimized, 'MobileOptimized');
	drupal_add_html_head($handheldfriendly, 'HandheldFriendly');
	drupal_add_html_head($viewport, 'viewport');

}

function retailplus_form_alter(&$form, &$form_state, $form_id) {

	if ($form_id == 'search_block_form') {
	unset($form['search_block_form']['#title']);
	$form['search_block_form']['#title_display'] = 'invisible';
	$form_default = t('Enter terms then hit Enter...');
	$form['search_block_form']['#default_value'] = $form_default;

	$form['search_block_form']['#attributes'] = array('onblur' => "if (this.value == '') {this.value = '{$form_default}';}", 'onfocus' => "if (this.value == '{$form_default}') {this.value = '';}" );
	}

	if (stristr($form_id,"add_to_cart_form")) {
    $form['add_to_wishlist']['#weight'] = 99;
  }

}
?>
