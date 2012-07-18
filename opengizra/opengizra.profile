<?php
/**
 * @file
 * Opengizra profile.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
function opengizra_profile_form_install_configure_form_alter(&$form, $form_state) {
  // Pre-populate the site name with the server name.
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
}

/**
 * Implements hook_install_tasks().
 */
function opengizra_profile_install_tasks() {
  $tasks = array();

  $tasks['opengizra_profile_import_data'] = array(
    'display_name' => st('Import content'),
    'display' => TRUE,
    'type' => 'batch',
    'run' => INSTALL_TASK_RUN_IF_NOT_COMPLETED,
  );
  return $tasks;
}

/**
 * Task callback: return a batch API array, for importing content and creating
 * menues.
 */
function opengizra_profile_import_data() {
  drupal_set_title(st('Import content'));

  // Fixes problems when the CSV files used for importing have been created
  // on a Mac, by forcing PHP to detect the appropriate line endings.
  ini_set('auto_detect_line_endings', TRUE);

  $migrations = migrate_migrations();
  foreach ($migrations as $machine_name => $migration) {
    $operations[] =  array('_opengizra_profile_import_data', array($machine_name, t('Importing content.')));
  }

  $batch = array(
    'title' => t('Importing content'),
    'operations' => $operations,
  );

  return $batch;
}

/**
 * BatchAPI callback.
 *
 * @see opengizra_profile_import_data().
 */
function _opengizra_profile_import_data($operation, $type, &$context) {
  $context['message'] = t('@operation', array('@operation' => $type));
  $migration =  Migration::getInstance($operation);
  $migration->processImport();
}
