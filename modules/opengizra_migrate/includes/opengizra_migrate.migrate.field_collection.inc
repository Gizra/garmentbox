<?php

abstract class openGizraFieldCollectionMigration extends Migration {

  public function __construct() {
    parent::__construct();
    $this->description = t('Import @bundle field collections from CSV file.', array('@bundle' => $this->bundle));

    // Create a map object for tracking the relationships between source rows
    $key = array(
      'id' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
      ),
    );
    $this->map = new MigrateSQLMap($this->machineName, $key, MigrateDestinationEntityAPI::getKeySchema($this->entityType));

    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'opengizra_migrate') . '/csv/' . $this->entityType . '/' . $this->bundle . '.csv', $this->csvColumns, array('header_rows' => 1));
    $this->destination = new openGizraMigrateDestinationFieldCollection($this->bundle, array('host_entity_type' => $this->hostEntityType));
  }

  function prepareRow($row) {
    $row->uid = 1;
  }
}
