<?php

/**
 * Migrate Collection nodes.
 */
class openGizraCollectionStatusTerms extends openGizraMigration {

  /**
   * Map the field and properties to the CSV header.
   */
  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('name', 'Name'),
  );

  /**
   * The node type name.
   */
  public $entityType = 'taxonomy_term';
  public $bundle = 'collection_status';
  public $csvFile = 'collection_status';
}

/**
 * Migrate Collection nodes.
 */
class openGizraCollections extends openGizraMigration {

  /**
   * Map the field and properties to the CSV header.
   */
  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('title', 'Title'),
    array('body', 'Body'),
  );

  /**
   * The node type name.
   */
  public $entityType = 'node';
  public $bundle = 'collection';
  public $csvFile = 'collections';

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('body', 'body');
  }
}

/**
 * Migrate "status info" field collection.
 */
class openGizraCollectionsFieldCollections extends openGizraFieldCollectionMigration {
  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('host_entity_id', 'Node ID'),
    array('field_collection_status', 'Term ID'),
  );

  public $entityType = 'field_collection_item';
  public $bundle = 'field_status_info';
  public $hostEntityType = 'node';

  public $csvFile = 'field_status_info';

  public $dependencies = array(
    'openGizraCollectionStatusTerms',
    'openGizraCollections',
  );

  public function __construct() {
    parent::__construct();
    $this
      ->addFieldMapping('host_entity_id', 'host_entity_id')
      ->sourceMigration('openGizraCollections');

    $this
      ->addFieldMapping('field_collection_status', 'field_collection_status')
      ->sourceMigration('openGizraCollectionStatusTerms');
  }
}
