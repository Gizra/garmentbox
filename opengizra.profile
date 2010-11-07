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
  $features = array(
  );
  return $features;
}

/**
 * Return a list of tasks that this profile supports.
 *
 * @return
 *   A keyed array of tasks the profile will perform during
 *   the final stage. The keys of the array will be used internally,
 *   while the values will be displayed to the user in the installer
 *   task list.
 */
function opengizra_profile_task_list() {
  global $conf;
  $conf['site_name'] = 'Open gizra';
  $conf['site_footer'] = 'Open gizra by <a href="http://phase2technology.com">Phase2 Technology</a>';
  $conf['theme_settings'] = array(
    'default_logo' => 0,
    'logo_path' => 'sites/all/themes/opengizra_theme/images/opengizra-logo.png',
  );

  $tasks['op-configure-batch'] = st('Configure Open gizra');

  if (_opengizra_language_selected()) {
    $tasks['op-translation-import-batch'] = st('Importing translations');
  }

  return $tasks;
}

/**
 * Implementation of hook_profile_tasks().
 */
function opengizra_profile_tasks(&$task, $url) {
  global $install_locale;
  $output = "";

  install_include(opengizra_profile_modules());

  if($task == 'profile') {
    drupal_set_title(t('Open gizra installation'));
    _opengizra_log(t('Starting installation'));
    _opengizra_base_settings();
    $task = "op-configure";
  }

  if($task == 'op-configure') {
    $batch['title'] = st('Configuring @drupal', array('@drupal' => drupal_install_profile_name()));
    $files = module_rebuild_cache();
    foreach ( opengizra_feature_modules() as $feature ) {
      $batch['operations'][] = array('_install_module_batch', array($feature, $files[$feature]->info['name']));
      //-- Initialize each feature individually rather then all together in the end, to avoid execution timeout.
      $batch['operations'][] = array('features_flush_caches', array());
    }
    $batch['operations'][] = array('_opengizra_cleanup', array());
    $batch['error_message'] = st('There was an error configuring @drupal.', array('@drupal' => drupal_install_profile_name()));
    $batch['finished'] = '_opengizra_configure_finished';
    variable_set('install_task', 'op-configure-batch');
    batch_set($batch);
    batch_process($url, $url);
  }

  if ($task == 'op-translation-import') {
    if (_opengizra_language_selected() && module_exists('l10n_update')) {
      module_load_install('l10n_update');
      module_load_include('batch.inc', 'l10n_update');

      $history = l10n_update_get_history();
      $available = l10n_update_available_releases();
      $updates = l10n_update_build_updates($history, $available);

      // Filter out updates in other languages. If no languages, all of them will be updated
      $updates = _l10n_update_prepare_updates($updates, NULL, array($install_locale));

      // Edited strings are kept, only default ones (previously imported)
      // are overwritten and new strings are added
      $mode = 1;

      if ($batch = l10n_update_batch_multiple($updates, $mode)) {
        $batch['finished'] = '_opengizra_import_translations_finished';
        variable_set('install_task', 'op-translation-import-batch');
        batch_set($batch);
        batch_process($url, $url);
      }
    }
  }

  // Land here until the batches are done
  if (in_array($task, array('op-translation-import-batch', 'op-configure-batch'))) {
    include_once 'includes/batch.inc';
    $output = _batch_page();
  }

  return $output;
}

/**
 * Translation import process is finished, move on to the next step
 */
function _opengizra_import_translations_finished($success, $results) {
  _opengizra_log(t('Translations have been imported.'));
  /**
   * Necessary as the opengizra_theme's status gets reset to 0
   * by a part of the automated batch translation in l10n_update
   */
  install_default_theme('opengizra_theme');
  variable_set('install_task', 'profile-finished');
}

/**
 * Import process is finished, move on to the next step
 */
function _opengizra_configure_finished($success, $results) {
  _opengizra_log(t('Open gizra has been installed.'));
  if (_opengizra_language_selected()) {
    // Other language, different part of the process
    variable_set('install_task', 'op-translation-import');
  }
  else {
    // English installation
    variable_set('install_task', 'profile-finished');
  }
}

/**
 * Do some basic setup
 */
function _opengizra_base_settings() {
  global $base_url;

  // create pictures dir
  $pictures_path = file_create_path('pictures');
  file_check_directory($pictures_path, TRUE);

  variable_set('opengizra_version', '2.3');


  // Theme related.
  install_default_theme('opengizra_theme');

  $theme_settings = variable_get('theme_settings', array());
  $theme_settings['toggle_node_info_page'] = FALSE;
  $theme_settings['default_logo'] = FALSE;
  $theme_settings['logo_path'] = 'sites/all/themes/opengizra_theme/images/logo.gif';
  variable_set('theme_settings', $theme_settings);

  // Basic Drupal settings.
  variable_set('site_frontpage', 'node');
  variable_set('user_register', 1);
  variable_set('user_pictures', '1');
  variable_set('statistics_count_content_views', 1);
  variable_set('filter_default_format', '1');

  // Set the default timezone name from the offset
  $offset = variable_get('date_default_timezone', '');
  $tzname = timezone_name_from_abbr("", $offset, 0);
  variable_set('date_default_timezone_name', $tzname);

  _opengizra_log(st('Configured basic settings'));
}


/**
 * Cleanup after the install
 */
function _opengizra_cleanup() {
  // DO NOT call drupal_flush_all_caches(), it disables all themes
  $functions = array(
    'drupal_rebuild_theme_registry',
    'menu_rebuild',
    'install_init_blocks',
    'views_invalidate_cache',
    'node_types_rebuild',
  );

  foreach ($functions as $func) {
    //$start = time();
    $func();
    //$elapsed = time() - $start;
    //error_log("####  $func took $elapsed seconds ###");
  }

  ctools_flush_caches();
  cache_clear_all('*', 'cache', TRUE);
  cache_clear_all('*', 'cache_content', TRUE);
}

/**
 * Set Open gizra as the default install profile
 */
function system_form_install_select_profile_form_alter(&$form, $form_state) {
  foreach($form['profile'] as $key => $element) {
    $form['profile'][$key]['#value'] = 'opengizra';
  }
}


/**
 * Consolidate logging.
 */
function _opengizra_log($msg) {
  error_log($msg);
  drupal_set_message($msg);
}

/**
 * Checks if installation is being done in a language other than English
 */
function _opengizra_language_selected() {
  global $install_locale;
  return !empty($install_locale) && ($install_locale != 'en');
}
