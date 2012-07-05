<?php
/**
 * @file
 * opengizra_image.features.inc
 */

/**
 * Implementation of hook_views_api().
 */
function opengizra_image_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implementation of hook_image_default_styles().
 */
function opengizra_image_image_default_styles() {
  $styles = array();

  // Exported image style: polaroid
  $styles['polaroid'] = array(
    'name' => 'polaroid',
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
          'width' => '90',
          'height' => '100',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: polaroid_small
  $styles['polaroid_small'] = array(
    'name' => 'polaroid_small',
    'effects' => array(
      4 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '50',
          'height' => '55',
        ),
        'weight' => '1',
      ),
    ),
  );

  return $styles;
}
