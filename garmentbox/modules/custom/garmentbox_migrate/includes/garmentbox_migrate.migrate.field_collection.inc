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

  public function prepareRow($row) {
    $row->uid = 1;
  }

  public function prepare($entity, $row) {
    if (!empty($this->sizeVocabulary)) {
      $this->prepareSizeVocabulary($entity, $row);
    }
  }

  /**
   * Associate the Size from the correct vocabulary.
   */
  private function prepareSizeVocabulary($entity, $row) {
    $node = $entity->hostEntity();
    // Get the company from the item
    $wrapper = entity_metadata_wrapper('node', $node);
    $company_nid = $wrapper->og_company->getIdentifier();

    $field_name = $this->sizeVocabulary;

    // Convert the term name to term ID.
    $term = taxonomy_get_term_by_name($row->field_size, 'size_' . $company_nid);
    $term = reset($term);
    $entity->field_size['und'][0]['target_id'] = $term->tid;
  }
}
