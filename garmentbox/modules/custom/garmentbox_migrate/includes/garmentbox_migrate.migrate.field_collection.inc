<?php

abstract class garmentboxFieldCollectionMigration extends Migration {

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
    $destination_handler = new MigrateDestinationEntityAPI($this->entityType, $this->bundle);
    $this->map = new MigrateSQLMap($this->machineName, $key, $destination_handler->getKeySchema($this->entityType));

    // Rebuild the csv columns array.
    $this->csvColumns = !empty($this->csvColumns) ? $this->csvColumns : array();
    $csv_cols[] = array('id', 'Unique ID');
    $this->csvColumns = array_merge($csv_cols, $this->csvColumns);


    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'garmentbox_migrate') . '/csv/' . $this->entityType . '/' . $this->bundle . '.csv', $this->csvColumns, array('header_rows' => 1));
    $this->destination = new garmentboxMigrateDestinationFieldCollection($this->bundle, array('host_entity_type' => $this->hostEntityType));
  }

  function prepareRow($row) {
    $row->uid = 1;
  }
}
