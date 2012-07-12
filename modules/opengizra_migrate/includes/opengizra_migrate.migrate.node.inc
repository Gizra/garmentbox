<?php

/**
 * @file
 * Populate distribution with some content.
 */

class openGizraMigrationNode extends Migration {

  public function __construct() {
    parent::__construct();
    $this->description = t('Import @type nodes from CSV file.', array('@type' => $this->type));
    // Create a map object for tracking the relationships between source rows
    $key = array(
      'title' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
      ),
    );
    $this->map = new MigrateSQLMap($this->machineName, $key, MigrateDestinationEntityAPI::getKeySchema('node'));

    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'opengizra_migrate') . '/csv/' . $this->type . '.csv', $this->csvColumns, array('header_rows' => 1));
    $this->destination = new MigrateDestinationNode('page_element', array('text_format' => 'full_html'));
    $this->addFieldMapping('title', 'title');
  }

  function prepareRow($row) {
    $row->uid = 1;
  }
}
