<?php

/**
 * Implementation of hook_node_info().
 */
function pattern_making_node_info() {
  $items = array(
    'style' => array(
      'name' => t('Style'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
