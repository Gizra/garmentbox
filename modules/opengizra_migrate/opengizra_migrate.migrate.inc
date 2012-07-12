<?php


/**
 * Migrate Collection nodes.
 */
class openGizraCollections extends openGizraMigration {

  /**
   * Map the field and properties to the CSV header.
   */
  private $csvColumns = array(
    array('title', 'Title'),
    array('body', 'Body'),
  );

  /**
   * The node type name.
   */
  private $type = 'collections';

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('body', 'body');
  }
}

/**
 * Migrate homepage_section field-collections .
 */
class openGizraCollectionsFieldCollections extends Migration {
  private $csvColumns = array(
    array('id', 'Unique ID'),
    array('ref', 'Reference ID'),
    array('title', 'Title'),
  );

  private $type = 'field_status_info';
  private $parentType = 'collections';
  public $parentClass = 'openGizraCollections';
}
