<div class="container boxed-slideshow">
    <div id="slideshow" class="bannercontainer main-slider">

        <div class="banner">
            <ul>
            <?php foreach ($rows as $id => $row) { ?>
            
                <?php $view = views_get_current_view();
                $nid = $view->result[$id]->nid; 
                $node = node_load($nid);
                $lang = 'und';
                $nodeurl =  url('node/'. $node->nid);

                $image = image_style_url('mt_slideshow_boxed', $node->field_mt_teaser_image[$lang][0]['uri']); 
                $title = $node->field_mt_teaser_image[$lang][0]['title'];
                $alt = $node->field_mt_teaser_image[$lang][0]['alt'];
                
                if ($node->type=='mt_slideshow_entry') {  ?>
                    <?php if ($node->field_mt_slideshow_entry_path) { ?>
                    <?php $path = $node->field_mt_slideshow_entry_path[$lang][0]['value']; ?>
                    <li data-link="<?php print url($path); ?>">
                    <?php } else { ?>
                    <li >
                    <?php } ?>

                        <img src="<?php print $image; ?>" title="<?php print $title; ?>" alt="<?php print $alt; ?>"/>

                        <div>
                            <div class="title">
                                <?php $title = $node->title; ?>
                                <?php if ($node->field_mt_slideshow_entry_path) { ?>
                                <?php $path = $node->field_mt_slideshow_entry_path[$lang][0]['value']; ?>
                                <a href="<?php print url($path); ?>"><?php print $title; ?></a>
                                <?php } else { ?>
                                <span>
                                <?php print $title; ?>
                                </span>
                                <?php } ?>
                            </div>
                        </div>
                    </li>
                <?php } else { ?>
                    <li data-link="<?php print $nodeurl ?>" >
                        <?php print $row; ?>
                    </li>
                <?php } ?> 

            <?php } ?>
            </ul>
            <div class="tp-bannertimer tp-bottom"></div>
        </div>
    </div>
</div>