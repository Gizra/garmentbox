<?php

// Plugin definition
$plugin = array(
  'title' => t('Three columns grid (8 - 8 - 5) stacked'),
  'category' => t('Columns: 3'),
  'theme' => 'grid_8_8_5',
  'css' => 'grid_8_8_5.css',
  // The theme that will be used on the panels "content" page.
  'admin theme' => 'grid_8_8_5_admin',
  'regions' => array(
    'top' => t('Top'),
    'first' => t('First'),
    'middle' => t('Middle'),
    'last' => t('Last'),
    'bottom' => t('Bottom'),
  ),
);
