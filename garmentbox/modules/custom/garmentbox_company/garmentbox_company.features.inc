<?php
/**
 * @file
 * garmentbox_company.features.inc
 */

/**
 * Implements hook_node_info().
 */
function garmentbox_company_node_info() {
  $items = array(
    'company' => array(
      'name' => t('Company'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
