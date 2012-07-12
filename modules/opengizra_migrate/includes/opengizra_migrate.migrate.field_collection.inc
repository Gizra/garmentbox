<?php

class openGizraFieldCollectionMigration extends Migration {

  public function __construct() {
    parent::__construct();
    $this->description = t('Import @parent_type field collections from CSV file.', array('@parent_type' => $this->parentType));
    $this->dependencies = array($this->parentClass);

    // Create a map object for tracking the relationships between source rows
    $key = array(
      'id' => array(
        'type' => 'varchar',
        'length' => 255,
        'not null' => TRUE,
      ),
    );
    $this->map = new MigrateSQLMap($this->machineName, $key, MigrateDestinationEntityAPI::getKeySchema('node'));

    // Create a MigrateSource object.
    $this->source = new MigrateSourceCSV(drupal_get_path('module', 'opengizra_migrate') . '/csv/' . $this->type . '.csv', $this->csvColumns, array('header_rows' => 1));
    $this->destination = new openGizraMigrateDestinationFieldCollection('field_features', array('host_entity_type' => 'node'));

    $this->addFieldMapping('host_entity_id', 'ref')->sourceMigration('opengizraHomepageSections');
  }

  function prepareRow($row) {
    $row->uid = 1;
  }
}
