<?php
/**
 * @file
 * opengizra_image.features.inc
 */

/**
 * Implementation of hook_image_default_styles().
 */
function opengizra_user_image_default_styles() {
  $styles = array();

  // Exported image style: user_thumb
  $styles['user_thumb'] = array(
    'name' => 'user_thumb',
    'effects' => array(
      3 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '24',
          'height' => '24',
        ),
        'weight' => '1',
      ),
    ),
  );

  return $styles;
}
