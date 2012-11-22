<?php
/**
 * @file
 * garmentbox_general.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function garmentbox_general_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_fontyourface_features_default_font().
 */
function garmentbox_general_fontyourface_features_default_font() {
  return array(
    'Dosis normal normal' => array(
      'name' => 'Dosis normal normal',
      'enabled' => '1',
      'url' => 'http://localhost/#87b73e77d81c3e8b986dec610a25d088',
      'provider' => 'local_fonts',
      'css_selector' => '.dosis',
      'css_family' => 'Dosis',
      'css_style' => 'normal',
      'css_weight' => 'normal',
      'css_fallbacks' => '',
      'foundry' => '',
      'foundry_url' => '',
      'license' => '',
      'license_url' => '',
      'designer' => '',
      'designer_url' => '',
      'metadata' => 'a:2:{s:4:"path";s:68:"public://fontyourface/local_fonts/Dosis-normal-normal/stylesheet.css";s:8:"font_uri";a:4:{s:3:"eot";s:70:"public://fontyourface/local_fonts/Dosis-normal-normal/Dosis-Medium.eot";s:8:"truetype";s:70:"public://fontyourface/local_fonts/Dosis-normal-normal/Dosis-Medium.ttf";s:4:"woff";s:71:"public://fontyourface/local_fonts/Dosis-normal-normal/Dosis-Medium.woff";s:3:"svg";s:70:"public://fontyourface/local_fonts/Dosis-normal-normal/Dosis-Medium.svg";}}',
    ),
    'Neo Sans Light normal normal' => array(
      'name' => 'Neo Sans Light normal normal',
      'enabled' => '1',
      'url' => 'http://localhost/#14764856ae5520c3db951bf66bb3c3cc',
      'provider' => 'local_fonts',
      'css_selector' => '.neosanslight',
      'css_family' => 'Neo Sans Light',
      'css_style' => 'normal',
      'css_weight' => 'normal',
      'css_fallbacks' => '',
      'foundry' => '',
      'foundry_url' => '',
      'license' => '',
      'license_url' => '',
      'designer' => '',
      'designer_url' => '',
      'metadata' => 'a:2:{s:4:"path";s:77:"public://fontyourface/local_fonts/Neo_Sans_Light-normal-normal/stylesheet.css";s:8:"font_uri";a:4:{s:3:"eot";s:81:"public://fontyourface/local_fonts/Neo_Sans_Light-normal-normal/Neo Sans Light.eot";s:8:"truetype";s:81:"public://fontyourface/local_fonts/Neo_Sans_Light-normal-normal/Neo Sans Light.ttf";s:4:"woff";s:82:"public://fontyourface/local_fonts/Neo_Sans_Light-normal-normal/Neo Sans Light.woff";s:3:"svg";s:81:"public://fontyourface/local_fonts/Neo_Sans_Light-normal-normal/Neo Sans Light.svg";}}',
    ),
  );
}
