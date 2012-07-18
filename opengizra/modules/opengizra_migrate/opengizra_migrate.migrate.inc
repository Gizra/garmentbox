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
 * Migrate Task status terms.
 */
class openGizraTaskStatusTerms extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('name', 'Name'),
    array('field_status_closed', 'Closed'),
  );

  public $entityType = 'taxonomy_term';
  public $bundle = 'task_status';

  public function __construct() {
    parent::__construct();
    $this->addFieldMapping('field_status_closed', 'field_status_closed');
  }
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
    array('flag', 'Flag'),
  );

  public $entityType = 'node';
  public $bundle = 'collection';

  public function __construct() {
    parent::__construct();
    $this->addFieldMapping('body', 'body');
  }

  public function complete($entity, stdClass $row) {
    if ($row->flag) {
      // Mark collection is "Active collection".
      flag('flag', 'active_collection', $entity->nid);
    }
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
 * Migrate Task nodes.
 */
class openGizraTasks extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('title', 'Title'),
    array('body', 'Body'),
    array('field_entity_reference', 'Reference'),
    array('field_task_status', 'Status'),
  );

  public $entityType = 'node';
  public $bundle = 'task';

  public $dependencies = array(
    'openGizraTaskStatusTerms',
    'openGizraCollections',
  );

  public function __construct() {
    parent::__construct();
    $this->addFieldMapping('body', 'body');
    $this
      ->addFieldMapping('field_entity_reference', 'field_entity_reference')
      ->sourceMigration('openGizraCollections');

    $this
      ->addFieldMapping('field_task_status', 'field_task_status')
      ->sourceMigration('openGizraTaskStatusTerms');
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
    array('field_images', 'Images'),
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
      ->addFieldMapping('field_item', 'field_item')
      ->sourceMigration('openGizraItems');

    $this
      ->addFieldMapping('field_material', 'field_material')
      ->sourceMigration('openGizraMaterials');


    $this->addFieldMapping('field_images', 'field_images');
    $this
      ->addFieldMapping('field_images:file_replace')
      ->defaultValue(FILE_EXISTS_REPLACE);
    $this
      ->addFieldMapping('field_images:source_dir')
      ->defaultValue(drupal_get_path('module', 'opengizra_migrate') . '/images');
  }

  function prepareRow($row) {
    parent::prepareRow($row);
    $row->field_images = explode('; ', $row->field_images);
  }
}


///////////////////////////////
// Field collections

/**
 * Migrate "status info" field collection.
 */
class openGizraCollectionsFieldStatusInfo extends openGizraFieldCollectionMigration {
  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('host_entity_id', 'Collection'),
    array('field_collection_status', 'Status'),
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


/**
 * Migrate "size info" field collection.
 */
class openGizraCollectionsFieldSizeInfo extends openGizraFieldCollectionMigration {
  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('host_entity_id', 'Item instance'),
    array('field_size', 'Size'),
    array('field_sku', 'SKU'),
  );

  public $entityType = 'field_collection_item';
  public $bundle = 'field_size_info';
  public $hostEntityType = 'node';

  public $dependencies = array(
    'openGizraSizeTerms',
    'openGizraItemInstances',
  );

  public function __construct() {
    parent::__construct();
    $this
      ->addFieldMapping('host_entity_id', 'host_entity_id')
      ->sourceMigration('openGizraItemInstances');

    $this
      ->addFieldMapping('field_size', 'field_size')
      ->sourceMigration('openGizraSizeTerms');

    $this->addFieldMapping('field_sku', 'field_sku');
  }
}
