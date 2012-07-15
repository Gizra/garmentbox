<?php

///////////////////////////////
// Terms

/**
 * Migrate Collection status terms.
 */
class openGizraCollectionStatusTerms extends openGizraMigration {

  /**
   * Map the field and properties to the CSV header.
   */
  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('name', 'Name'),
  );

  public $entityType = 'taxonomy_term';
  public $bundle = 'collection_status';
}

/**
 * Migrate Item status terms.
 */
class openGizraItemStatusTerms extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('name', 'Name'),
  );

  public $entityType = 'taxonomy_term';
  public $bundle = 'item_status';
}

/**
 * Migrate Size terms.
 */
class openGizraSizeTerms extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('name', 'Name'),
  );

  public $entityType = 'taxonomy_term';
  public $bundle = 'size';
}

///////////////////////////////
// Nodes

/**
 * Migrate Collection nodes.
 */
class openGizraCollections extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('title', 'Title'),
    array('body', 'Body'),
  );

  public $entityType = 'node';
  public $bundle = 'collection';

  public function __construct() {
    parent::__construct();
    $this->addFieldMapping('body', 'body');
  }
}

/**
 * Migrate Vendors nodes.
 */
class openGizraVendors extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('title', 'Title'),
    array('body', 'Body'),
  );

  public $entityType = 'node';
  public $bundle = 'vendor';

  public function __construct() {
    parent::__construct();
    $this->addFieldMapping('body', 'body');
  }
}

/**
 * Migrate Materials nodes.
 */
class openGizraMaterials extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('title', 'Title'),
    array('field_vendor', 'Vendor'),
  );

  public $entityType = 'node';
  public $bundle = 'material';

  public $dependencies = array(
    'openGizraVendors',
  );

  public function __construct() {
    parent::__construct();
    $this->addFieldMapping('body', 'body');
    $this
      ->addFieldMapping('field_vendor', 'field_vendor')
      ->sourceMigration('openGizraVendors');
  }
}

/**
 * Migrate Items nodes.
 */
class openGizraItems extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('title', 'Title'),
    array('body', 'Body'),
    array('field_collection', 'Collection'),
    array('field_item_status', 'Status'),
  );

  public $entityType = 'node';
  public $bundle = 'item';

  public $dependencies = array(
    'openGizraItemStatusTerms',
    'openGizraCollections',
  );

  public function __construct() {
    parent::__construct();
    $this->addFieldMapping('body', 'body');
    $this
      ->addFieldMapping('field_collection', 'field_collection')
      ->sourceMigration('openGizraCollections');

    $this
      ->addFieldMapping('field_item_status', 'field_item_status')
      ->sourceMigration('openGizraItemStatusTerms');
  }
}

/**
 * Migrate Item instances nodes.
 */
class openGizraItemInstances extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('title', 'Title'),
    array('field_item', 'Item'),
    array('field_material', 'Material'),
  );

  public $entityType = 'node';
  public $bundle = 'item_instance';

  public $dependencies = array(
    'openGizraMaterials',
    'openGizraItems',
  );

  public function __construct() {
    parent::__construct();
    $this->addFieldMapping('body', 'body');
    $this
      ->addFieldMapping('field_collection', 'field_collection')
      ->sourceMigration('openGizraItems');

    $this
      ->addFieldMapping('field_material', 'field_material')
      ->sourceMigration('openGizraMaterials');
  }
}


///////////////////////////////
// Field collections

/**
 * Migrate "status info" field collection.
 */
class openGizraCollectionsFieldCollections extends openGizraFieldCollectionMigration {
  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('host_entity_id', 'Node ID'),
    array('field_collection_status', 'Term ID'),
    array('field_date', 'Deadline'),
  );

  public $entityType = 'field_collection_item';
  public $bundle = 'field_status_info';
  public $hostEntityType = 'node';

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

    $this->addFieldMapping('field_date', 'field_date');
  }
}
