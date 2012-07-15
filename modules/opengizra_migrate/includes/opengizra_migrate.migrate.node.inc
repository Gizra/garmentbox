<?php

/**
 * @file
 * Populate distribution with some content.
 */

abstract class openGizraMigration extends Migration {

  public function __construct() {
    parent::__construct();

    // Make sure we can use it for node and term only.
    if (!in_array($this->entityType, array('node', 'taxonomy_term'))) {
      throw new Exception('openGizraMigration supports only nodes and terms.');
    }

    $this->description = t('Import @type nodes from CSV file.', array('@type' => $this->bundle));
    // Create a map object for tracking the relationships between source rows

    $key_name = $this->entityType == 'node' ? 'title' : 'name';

    $key = array(
      $key_name => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
      ),
    );
    $this->map = new MigrateSQLMap($this->machineName, $key, MigrateDestinationEntityAPI::getKeySchema($this->entityType));

    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'opengizra_migrate') . '/csv/' . $this->csvFile . '.csv', $this->csvColumns, array('header_rows' => 1));
    $this->destination = new MigrateDestinationNode('page_element', array('text_format' => 'full_html'));
    $this->addFieldMapping('title', 'title');
  }

  function prepareRow($row) {
    $row->uid = 1;
  }
}
