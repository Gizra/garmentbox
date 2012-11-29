<?php
/**
 * @file
 * garmentbox_inventory.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function garmentbox_inventory_views_default_views() {
  $export = array();

  $view = new view;
  $view->name = 'inventory_admin';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Inventory admin';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Inventory admin';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer content types';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid_1' => 'nid_1',
    'title' => 'title',
    'nid' => 'nid',
    'field_inventory_type' => 'field_inventory_type',
    'field_quantity_info' => 'field_quantity_info',
    'title_1' => 'title_1',
    'field_include_in_total' => 'field_include_in_total',
    'field_in_warehouse' => 'field_in_warehouse',
    'field_production_order' => 'field_production_order',
    'field_customer' => 'field_customer',
    'field_defective' => 'field_defective',
    'field_origin_entity' => 'field_origin_entity',
    'changed' => 'changed',
    'field_original_revision' => 'field_original_revision',
    'field_missing_inventory_line' => 'field_missing_inventory_line',
  );
  $handler->display->display_options['style_options']['default'] = 'changed';
  $handler->display->display_options['style_options']['info'] = array(
    'nid_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
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
    'nid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_inventory_type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_quantity_info' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_include_in_total' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_in_warehouse' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_production_order' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_customer' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_defective' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_origin_entity' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_original_revision' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_missing_inventory_line' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_inventory_line_inline_node']['id'] = 'reverse_field_inventory_line_inline_node';
  $handler->display->display_options['relationships']['reverse_field_inventory_line_inline_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_inventory_line_inline_node']['field'] = 'reverse_field_inventory_line_inline_node';
  $handler->display->display_options['relationships']['reverse_field_inventory_line_inline_node']['required'] = 0;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_item_variant_target_id']['id'] = 'field_item_variant_target_id';
  $handler->display->display_options['relationships']['field_item_variant_target_id']['table'] = 'field_data_field_item_variant';
  $handler->display->display_options['relationships']['field_item_variant_target_id']['field'] = 'field_item_variant_target_id';
  $handler->display->display_options['relationships']['field_item_variant_target_id']['required'] = 1;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_item_target_id']['id'] = 'field_item_target_id';
  $handler->display->display_options['relationships']['field_item_target_id']['table'] = 'field_data_field_item';
  $handler->display->display_options['relationships']['field_item_target_id']['field'] = 'field_item_target_id';
  $handler->display->display_options['relationships']['field_item_target_id']['relationship'] = 'field_item_variant_target_id';
  $handler->display->display_options['relationships']['field_item_target_id']['required'] = 1;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_season_target_id']['id'] = 'field_season_target_id';
  $handler->display->display_options['relationships']['field_season_target_id']['table'] = 'field_data_field_season';
  $handler->display->display_options['relationships']['field_season_target_id']['field'] = 'field_season_target_id';
  $handler->display->display_options['relationships']['field_season_target_id']['relationship'] = 'field_item_target_id';
  $handler->display->display_options['relationships']['field_season_target_id']['required'] = 1;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_inventory_type_target_id']['id'] = 'field_inventory_type_target_id';
  $handler->display->display_options['relationships']['field_inventory_type_target_id']['table'] = 'field_data_field_inventory_type';
  $handler->display->display_options['relationships']['field_inventory_type_target_id']['field'] = 'field_inventory_type_target_id';
  $handler->display->display_options['relationships']['field_inventory_type_target_id']['required'] = 1;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nid_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nid_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nid_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nid_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nid_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nid_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['nid_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nid_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['nid_1']['link_to_node'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Inventory line title';
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
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'reverse_field_inventory_line_inline_node';
  $handler->display->display_options['fields']['nid']['label'] = 'Order NID';
  $handler->display->display_options['fields']['nid']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['external'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['nid']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['nid']['alter']['html'] = 0;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['nid']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['nid']['hide_empty'] = 0;
  $handler->display->display_options['fields']['nid']['empty_zero'] = 0;
  $handler->display->display_options['fields']['nid']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['nid']['link_to_node'] = 1;
  /* Field: Content: Inventory type */
  $handler->display->display_options['fields']['field_inventory_type']['id'] = 'field_inventory_type';
  $handler->display->display_options['fields']['field_inventory_type']['table'] = 'field_data_field_inventory_type';
  $handler->display->display_options['fields']['field_inventory_type']['field'] = 'field_inventory_type';
  $handler->display->display_options['fields']['field_inventory_type']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_inventory_type']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_inventory_type']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_inventory_type']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_inventory_type']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_inventory_type']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_inventory_type']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_inventory_type']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_inventory_type']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_inventory_type']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_inventory_type']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_inventory_type']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_inventory_type']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_inventory_type']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_inventory_type']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_inventory_type']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_inventory_type']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_inventory_type']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_inventory_type']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_inventory_type']['field_api_classes'] = 0;
  /* Field: Content: Quantity info */
  $handler->display->display_options['fields']['field_quantity_info']['id'] = 'field_quantity_info';
  $handler->display->display_options['fields']['field_quantity_info']['table'] = 'field_data_field_quantity_info';
  $handler->display->display_options['fields']['field_quantity_info']['field'] = 'field_quantity_info';
  $handler->display->display_options['fields']['field_quantity_info']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_quantity_info']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_quantity_info']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_quantity_info']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_quantity_info']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_quantity_info']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_quantity_info']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_quantity_info']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_quantity_info']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_quantity_info']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_quantity_info']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_quantity_info']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_quantity_info']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_quantity_info']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_quantity_info']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_quantity_info']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_quantity_info']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_quantity_info']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_quantity_info']['type'] = 'field_collection_fields';
  $handler->display->display_options['fields']['field_quantity_info']['settings'] = array(
    'view_mode' => 'full',
  );
  $handler->display->display_options['fields']['field_quantity_info']['group_rows'] = 1;
  $handler->display->display_options['fields']['field_quantity_info']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_quantity_info']['delta_reversed'] = 0;
  $handler->display->display_options['fields']['field_quantity_info']['delta_first_last'] = 0;
  $handler->display->display_options['fields']['field_quantity_info']['multi_type'] = 'ul';
  $handler->display->display_options['fields']['field_quantity_info']['field_api_classes'] = 0;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'field_season_target_id';
  $handler->display->display_options['fields']['title_1']['label'] = 'Season';
  $handler->display->display_options['fields']['title_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['title_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['title_1']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['title_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['title_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['title_1']['link_to_node'] = 1;
  /* Field: Taxonomy term: Include in total */
  $handler->display->display_options['fields']['field_include_in_total']['id'] = 'field_include_in_total';
  $handler->display->display_options['fields']['field_include_in_total']['table'] = 'field_data_field_include_in_total';
  $handler->display->display_options['fields']['field_include_in_total']['field'] = 'field_include_in_total';
  $handler->display->display_options['fields']['field_include_in_total']['relationship'] = 'field_inventory_type_target_id';
  $handler->display->display_options['fields']['field_include_in_total']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_include_in_total']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_include_in_total']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_include_in_total']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_include_in_total']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_include_in_total']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_include_in_total']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_include_in_total']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_include_in_total']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_include_in_total']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_include_in_total']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_include_in_total']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_include_in_total']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_include_in_total']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_include_in_total']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_include_in_total']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_include_in_total']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_include_in_total']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_include_in_total']['field_api_classes'] = 0;
  /* Field: Taxonomy term: In warehouse */
  $handler->display->display_options['fields']['field_in_warehouse']['id'] = 'field_in_warehouse';
  $handler->display->display_options['fields']['field_in_warehouse']['table'] = 'field_data_field_in_warehouse';
  $handler->display->display_options['fields']['field_in_warehouse']['field'] = 'field_in_warehouse';
  $handler->display->display_options['fields']['field_in_warehouse']['relationship'] = 'field_inventory_type_target_id';
  $handler->display->display_options['fields']['field_in_warehouse']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_in_warehouse']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_in_warehouse']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_in_warehouse']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_in_warehouse']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_in_warehouse']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_in_warehouse']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_in_warehouse']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_in_warehouse']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_in_warehouse']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_in_warehouse']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_in_warehouse']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_in_warehouse']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_in_warehouse']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_in_warehouse']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_in_warehouse']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_in_warehouse']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_in_warehouse']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_in_warehouse']['field_api_classes'] = 0;
  /* Field: Content: Production order */
  $handler->display->display_options['fields']['field_production_order']['id'] = 'field_production_order';
  $handler->display->display_options['fields']['field_production_order']['table'] = 'field_data_field_production_order';
  $handler->display->display_options['fields']['field_production_order']['field'] = 'field_production_order';
  $handler->display->display_options['fields']['field_production_order']['label'] = 'Production ordered';
  $handler->display->display_options['fields']['field_production_order']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_production_order']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_production_order']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_production_order']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_production_order']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_production_order']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_production_order']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_production_order']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_production_order']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_production_order']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_production_order']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_production_order']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_production_order']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_production_order']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_production_order']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_production_order']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_production_order']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_production_order']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_production_order']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_production_order']['field_api_classes'] = 0;
  /* Field: Content: Customer */
  $handler->display->display_options['fields']['field_customer']['id'] = 'field_customer';
  $handler->display->display_options['fields']['field_customer']['table'] = 'field_data_field_customer';
  $handler->display->display_options['fields']['field_customer']['field'] = 'field_customer';
  $handler->display->display_options['fields']['field_customer']['relationship'] = 'reverse_field_inventory_line_inline_node';
  $handler->display->display_options['fields']['field_customer']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_customer']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_customer']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_customer']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_customer']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_customer']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_customer']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_customer']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_customer']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_customer']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_customer']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_customer']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_customer']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_customer']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_customer']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_customer']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_customer']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_customer']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_customer']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_customer']['field_api_classes'] = 0;
  /* Field: Content: Defective */
  $handler->display->display_options['fields']['field_defective']['id'] = 'field_defective';
  $handler->display->display_options['fields']['field_defective']['table'] = 'field_data_field_defective';
  $handler->display->display_options['fields']['field_defective']['field'] = 'field_defective';
  $handler->display->display_options['fields']['field_defective']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_defective']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_defective']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_defective']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_defective']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_defective']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_defective']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_defective']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_defective']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_defective']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_defective']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_defective']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_defective']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_defective']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_defective']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_defective']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_defective']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_defective']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_defective']['field_api_classes'] = 0;
  /* Field: Content: Origin entity */
  $handler->display->display_options['fields']['field_origin_entity']['id'] = 'field_origin_entity';
  $handler->display->display_options['fields']['field_origin_entity']['table'] = 'field_data_field_origin_entity';
  $handler->display->display_options['fields']['field_origin_entity']['field'] = 'field_origin_entity';
  $handler->display->display_options['fields']['field_origin_entity']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_origin_entity']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_origin_entity']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_origin_entity']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_origin_entity']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_origin_entity']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_origin_entity']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_origin_entity']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_origin_entity']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_origin_entity']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_origin_entity']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_origin_entity']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_origin_entity']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_origin_entity']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_origin_entity']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_origin_entity']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_origin_entity']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_origin_entity']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_origin_entity']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_origin_entity']['field_api_classes'] = 0;
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Updated';
  $handler->display->display_options['fields']['changed']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['external'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['changed']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['changed']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['html'] = 0;
  $handler->display->display_options['fields']['changed']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['changed']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['changed']['hide_empty'] = 0;
  $handler->display->display_options['fields']['changed']['empty_zero'] = 0;
  $handler->display->display_options['fields']['changed']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['changed']['date_format'] = 'time ago';
  /* Field: Content: Original revision */
  $handler->display->display_options['fields']['field_original_revision']['id'] = 'field_original_revision';
  $handler->display->display_options['fields']['field_original_revision']['table'] = 'field_data_field_original_revision';
  $handler->display->display_options['fields']['field_original_revision']['field'] = 'field_original_revision';
  $handler->display->display_options['fields']['field_original_revision']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_original_revision']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_original_revision']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_original_revision']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_original_revision']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_original_revision']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_original_revision']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_original_revision']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_original_revision']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_original_revision']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_original_revision']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_original_revision']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_original_revision']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_original_revision']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_original_revision']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_original_revision']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_original_revision']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_original_revision']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_original_revision']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  $handler->display->display_options['fields']['field_original_revision']['field_api_classes'] = 0;
  /* Field: Content: Missing on inventory line */
  $handler->display->display_options['fields']['field_missing_inventory_line']['id'] = 'field_missing_inventory_line';
  $handler->display->display_options['fields']['field_missing_inventory_line']['table'] = 'field_data_field_missing_inventory_line';
  $handler->display->display_options['fields']['field_missing_inventory_line']['field'] = 'field_missing_inventory_line';
  $handler->display->display_options['fields']['field_missing_inventory_line']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['field_missing_inventory_line']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['field_missing_inventory_line']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['field_missing_inventory_line']['alter']['external'] = 0;
  $handler->display->display_options['fields']['field_missing_inventory_line']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['field_missing_inventory_line']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['field_missing_inventory_line']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['field_missing_inventory_line']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['field_missing_inventory_line']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['field_missing_inventory_line']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['field_missing_inventory_line']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['field_missing_inventory_line']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['field_missing_inventory_line']['alter']['html'] = 0;
  $handler->display->display_options['fields']['field_missing_inventory_line']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['field_missing_inventory_line']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['field_missing_inventory_line']['hide_empty'] = 0;
  $handler->display->display_options['fields']['field_missing_inventory_line']['empty_zero'] = 0;
  $handler->display->display_options['fields']['field_missing_inventory_line']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['field_missing_inventory_line']['type'] = 'entityreference_entity_id';
  $handler->display->display_options['fields']['field_missing_inventory_line']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_missing_inventory_line']['field_api_classes'] = 0;
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
    'inventory_line' => 'inventory_line',
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Inventory line title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['required'] = 0;
  $handler->display->display_options['filters']['title']['expose']['multiple'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/inventory';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Inventory admin';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $export['inventory_admin'] = $view;

  return $export;
}
