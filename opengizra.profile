<?php
/**
 * @file openpublish.profile
 *
 * TODO:
 *  - More general variable handling
 *  - Integrate Content for better block handling
 */

/**
 * Implementation of hook_profile_details()
 */
function opengizra_profile_details() {
  return array(
    'name' => 'Open gizra',
    'description' => st('The power of Drupal for today\'s online publishing from Phase2 Technology.'),
  );
}

/**
 * Implementation of hook_profile_modules().
 */
function opengizra_profile_modules() {
  $core_modules = array(
    // Required core modules
    'block', 'filter', 'node', 'system', 'user',

    // Optional core modules.
    'dblog', 'comment', 'help', 'locale', 'menu', 'openid', 'path',
	  'search', 'statistics', 'taxonomy', 'translation',
  );

  $contributed_modules = array(
    //misc stand-alone, required by others
    'flag',

    //date
    'date_api', 'date', 'date_timezone', 'date_popup',

    //cck
    'nodereference', 'userreference',

    //views
    'views', 'views_ui',

    // ctools, panels
	  'ctools', 'ctools_custom_content', 'views_content', 'page_manager', 'panels',

    // requries ctools
    'strongarm',

    // distribution management
    'features', 'diff',

    // Development
    'admin_menu', 'devel',
  );

  return array_merge($core_modules, $contributed_modules);
}

/**
 * Features module and Open gizra features
 */
function opengizra_feature_modules() {
  $features = array();
  return $features;
}

/**
 * Checks if installation is being done in a language other than English
 */
function _opengizra_language_selected() {
  global $install_locale;
  return !empty($install_locale) && ($install_locale != 'en');
}
