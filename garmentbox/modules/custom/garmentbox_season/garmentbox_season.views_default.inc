<?php
/**
 * @file
 * garmentbox_season.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function garmentbox_season_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'item_variants';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Item variants';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Items';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_item',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'field_item' => 'field_item',
    'field_images' => 'field_images',
    'title' => 'title',
    'field_source_info_ref' => 'field_source_info_ref',
    'field_item_status' => 'field_item_status',
    'field_retail_price' => 'field_retail_price',
    'field_wholesale_price' => 'field_wholesale_price',
    'nid' => 'nid',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_item' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_images' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_source_info_ref' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_item_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_retail_price' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_wholesale_price' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No items added yet.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = 0;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_item_target_id']['id'] = 'field_item_target_id';
  $handler->display->display_options['relationships']['field_item_target_id']['table'] = 'field_data_field_item';
  $handler->display->display_options['relationships']['field_item_target_id']['field'] = 'field_item_target_id';
  $handler->display->display_options['relationships']['field_item_target_id']['required'] = 1;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_season_target_id']['id'] = 'field_season_target_id';
  $handler->display->display_options['relationships']['field_season_target_id']['table'] = 'field_data_field_season';
  $handler->display->display_options['relationships']['field_season_target_id']['field'] = 'field_season_target_id';
  $handler->display->display_options['relationships']['field_season_target_id']['relationship'] = 'field_item_target_id';
  $handler->display->display_options['relationships']['field_season_target_id']['required'] = 1;
  /* Relationship: Flags: line_sheet */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['label'] = 'Line sheet flag';
  $handler->display->display_options['relationships']['flag_content_rel']['required'] = 0;
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'line_sheet';
  $handler->display->display_options['relationships']['flag_content_rel']['user_scope'] = 'any';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Variant';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Field: Content: Images */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['label'] = '';
  $handler->display->display_options['fields']['field_images']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_images']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_images']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_images']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_images']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_images']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_images']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_images']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_images']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_images']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_images']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_images']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_images']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_images']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_images']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_images']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_images']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_images']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_images']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_images']['type'] = 'image_delta';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'deltas' => '0',
    'deltas_reversed' => 0,
    'image_style' => 'variant_thumbnail',
    'image_link' => 'content',
  );
  $handler->display->display_options['fields']['field_images']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_images']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_images']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_images']['delta_first_last'] = 0;
  $handler->display->display_options['fields']['field_images']['field_api_classes'] = 0;
  /* Field: Content: Item */
  $handler->display->display_options['fields']['field_item']['id'] = 'field_item';
  $handler->display->display_options['fields']['field_item']['table'] = 'field_data_field_item';
  $handler->display->display_options['fields']['field_item']['field'] = 'field_item';
  $handler->display->display_options['fields']['field_item']['label'] = '';
  $handler->display->display_options['fields']['field_item']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_item']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_item']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_item']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_item']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_item']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_item']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_item']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_item']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_item']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_item']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_item']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_item']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_item']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_item']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_item']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_item']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_item']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_item']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_item']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_item']['field_api_classes'] = 0;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Variant';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="display-cell-image"> [field_images]</div> <div class="display-cell-title"> [title] </div>';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nothing']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nothing']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nothing']['element_class'] = 'display-cell';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nothing']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nothing']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nothing']['hide_alter_empty'] = 0;
  /* Field: Content: Bill of materials */
  $handler->display->display_options['fields']['field_bom_info']['id'] = 'field_bom_info';
  $handler->display->display_options['fields']['field_bom_info']['table'] = 'field_data_field_bom_info';
  $handler->display->display_options['fields']['field_bom_info']['field'] = 'field_bom_info';
  $handler->display->display_options['fields']['field_bom_info']['label'] = 'Main material';
  $handler->display->display_options['fields']['field_bom_info']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_bom_info']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_bom_info']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_bom_info']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_bom_info']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_bom_info']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_bom_info']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_bom_info']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_bom_info']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_bom_info']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_bom_info']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_bom_info']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_bom_info']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_bom_info']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_bom_info']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_bom_info']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_bom_info']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_bom_info']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_bom_info']['type'] = 'garmentbox_bom_main_material_icon';
  $handler->display->display_options['fields']['field_bom_info']['settings'] = array(
    'edit' => 'Edit',
    'delete' => 'Delete',
    'add' => 'Add',
    'description' => 1,
    'view_mode' => 'full',
  );
  $handler->display->display_options['fields']['field_bom_info']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_bom_info']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_bom_info']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_bom_info']['delta_first_last'] = 0;
  $handler->display->display_options['fields']['field_bom_info']['field_api_classes'] = 0;
  /* Field: Content: Status */
  $handler->display->display_options['fields']['field_item_status']['id'] = 'field_item_status';
  $handler->display->display_options['fields']['field_item_status']['table'] = 'field_data_field_item_status';
  $handler->display->display_options['fields']['field_item_status']['field'] = 'field_item_status';
  $handler->display->display_options['fields']['field_item_status']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_item_status']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_item_status']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_item_status']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_item_status']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_item_status']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_item_status']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_item_status']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_item_status']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_item_status']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_item_status']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_item_status']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_item_status']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_item_status']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_item_status']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_item_status']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_item_status']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_item_status']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_item_status']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_item_status']['field_api_classes'] = 0;
  /* Field: Content: Retail price */
  $handler->display->display_options['fields']['field_retail_price']['id'] = 'field_retail_price';
  $handler->display->display_options['fields']['field_retail_price']['table'] = 'field_data_field_retail_price';
  $handler->display->display_options['fields']['field_retail_price']['field'] = 'field_retail_price';
  $handler->display->display_options['fields']['field_retail_price']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_retail_price']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_retail_price']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_retail_price']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_retail_price']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_retail_price']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_retail_price']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_retail_price']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_retail_price']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_retail_price']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_retail_price']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_retail_price']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_retail_price']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_retail_price']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_retail_price']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_retail_price']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_retail_price']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_retail_price']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_retail_price']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['field_retail_price']['type'] = 'commerce_price_formatted_amount';
  $handler->display->display_options['fields']['field_retail_price']['settings'] = array(
    'calculation' => FALSE,
  );
  $handler->display->display_options['fields']['field_retail_price']['field_api_classes'] = 0;
  /* Field: Content: Wholesale price */
  $handler->display->display_options['fields']['field_wholesale_price']['id'] = 'field_wholesale_price';
  $handler->display->display_options['fields']['field_wholesale_price']['table'] = 'field_data_field_wholesale_price';
  $handler->display->display_options['fields']['field_wholesale_price']['field'] = 'field_wholesale_price';
  $handler->display->display_options['fields']['field_wholesale_price']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_wholesale_price']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_wholesale_price']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_wholesale_price']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_wholesale_price']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_wholesale_price']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_wholesale_price']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_wholesale_price']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_wholesale_price']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_wholesale_price']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_wholesale_price']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_wholesale_price']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_wholesale_price']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_wholesale_price']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_wholesale_price']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_wholesale_price']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_wholesale_price']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_wholesale_price']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_wholesale_price']['click_sort_column'] = 'amount';
  $handler->display->display_options['fields']['field_wholesale_price']['type'] = 'commerce_price_formatted_amount';
  $handler->display->display_options['fields']['field_wholesale_price']['settings'] = array(
    'calculation' => FALSE,
  );
  $handler->display->display_options['fields']['field_wholesale_price']['field_api_classes'] = 0;
  /* Field: Flags: Flag link */
  $handler->display->display_options['fields']['ops']['id'] = 'ops';
  $handler->display->display_options['fields']['ops']['table'] = 'flag_content';
  $handler->display->display_options['fields']['ops']['field'] = 'ops';
  $handler->display->display_options['fields']['ops']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['ops']['label'] = 'Line sheet';
  $handler->display->display_options['fields']['ops']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['external'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['ops']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['ops']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['ops']['alter']['html'] = 0;
  $handler->display->display_options['fields']['ops']['element_label_colon'] = 0;
  $handler->display->display_options['fields']['ops']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['ops']['hide_empty'] = 0;
  $handler->display->display_options['fields']['ops']['empty_zero'] = 0;
  $handler->display->display_options['fields']['ops']['hide_alter_empty'] = 1;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'field_season_target_id';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['break_phrase'] = 0;
  $handler->display->display_options['arguments']['nid']['not'] = 0;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'item_variant' => 'item_variant',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'season/%/items';
  $export['item_variants'] = $view;

  return $export;
}
