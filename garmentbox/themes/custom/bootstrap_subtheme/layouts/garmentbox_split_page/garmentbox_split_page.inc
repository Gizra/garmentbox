<?php

// Plugin definition
$plugin = array(
  'title' => t('Garmentbox split page'),
  'category' => t('Garmentbox'),
  'theme' => 'garmentbox_split_page',
  'icon' => 'garmentbox-split-page.png',
  'css' => 'garmentbox_split_page.css',
  'regions' => array(
    'content_first' => t('Content first'),
    'content_last' => t('Content last'),
  ),
);
