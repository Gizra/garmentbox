<?php

/**
 * Migrate Collection nodes.
 */
class openGizraCollections extends openGizraMigrationNode {

  /**
   * Map the field and properties to the CSV header.
   */
  public $csvColumns = array(
    array('title', 'Title'),
    array('body', 'Body'),
  );

  /**
   * The node type name.
   */
  public $type = 'collections';

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
    array('ref', 'Reference ID'),
    array('title', 'Title'),
  );

  public $type = 'field_status_info';
  public $parentType = 'collections';
  public $parentClass = 'openGizraCollections';
}
