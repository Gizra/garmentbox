<?php
/**
 * @file
 * opengizra_main.features.inc
 */

/**
 * Implementation of hook_ctools_plugin_api().
 */
function opengizra_main_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "panels_mini" && $api == "panels_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implementation of hook_views_api().
 */
function opengizra_main_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => "3.0");
  }
}

/**
 * Implementation of hook_flag_default_flags().
 */
function opengizra_main_flag_default_flags() {
  $flags = array();
  // Exported flag: "Watch".
  $flags['watch'] = array(
    'content_type' => 'node',
    'title' => 'Watch',
    'global' => '0',
    'types' => array(
      0 => 'collection',
      1 => 'department',
      2 => 'event',
      3 => 'image',
      4 => 'item',
      5 => 'order',
      6 => 'pattern',
    ),
    'flag_short' => 'Watch',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Unwatch',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '2',
      ),
      'unflag' => array(
        0 => '2',
      ),
    ),
    'show_on_page' => 1,
    'show_on_teaser' => 1,
    'show_on_form' => 0,
    'access_author' => '',
    'i18n' => 0,
    'module' => 'opengizra_main',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 2,
  );
  return $flags;
}

/**
 * Implementation of hook_image_default_styles().
 */
function opengizra_main_image_default_styles() {
  $styles = array();

  // Exported image style: mini_gallery_big_thumb
  $styles['mini_gallery_big_thumb'] = array(
    'name' => 'mini_gallery_big_thumb',
    'effects' => array(
      2 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '550',
          'height' => '',
          'upscale' => 1,
        ),
        'weight' => '2',
      ),
    ),
  );

  // Exported image style: mini_gallery_small_thumb
  $styles['mini_gallery_small_thumb'] = array(
    'name' => 'mini_gallery_small_thumb',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '40',
          'height' => '120',
        ),
        'weight' => '1',
      ),
    ),
  );

  return $styles;
}

/**
 * Implementation of hook_node_info().
 */
function opengizra_main_node_info() {
  $items = array(
    'department' => array(
      'name' => t('Department'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
