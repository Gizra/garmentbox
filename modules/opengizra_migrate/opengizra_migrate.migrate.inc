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
 * Migrate homepage_section field-collections .
 */
class openGizraCollectionsFieldCollections extends openGizraFieldCollectionMigration {
  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('ref', 'Node ID'),
    array('title', 'Title'),
  );

  public $entityType = 'field_collection_item';
  public $bundle = 'field_status_info';
  public $csvFile = 'field_status_info';

  public $parentClass = 'openGizraCollections';
}
