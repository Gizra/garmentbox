<?php

///////////////////////////////
// Terms

/**
 * Migrate Season status terms.
 */
class openGizraSeasonStatusTerms extends openGizraMigration {

  /**
   * Map the field and properties to the CSV header.
   */
  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('name', 'Name'),
  );

  public $entityType = 'taxonomy_term';
  public $bundle = 'season_status';
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
class openGizraSeasons extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('title', 'Title'),
    array('body', 'Body'),
    array('field_season_status', 'Status'),
  );

  public $entityType = 'node';
  public $bundle = 'season';

  public $dependencies = array(
    'openGizraSeasonStatusTerms',
  );

  public function __construct() {
    parent::__construct();
    $this->addFieldMapping('body', 'body');
    $this
      ->addFieldMapping('field_season_status', 'field_season_status')
      ->sourceMigration('openGizraSeasonStatusTerms');
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
    array('body', 'Body'),
    array('field_nick_name', 'Nick name'),
    array('field_images', 'Images'),
  );

  public $entityType = 'node';
  public $bundle = 'material';

  public $dependencies = array(
    'openGizraVendors',
  );

  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('field_nick_name', 'field_nick_name');

    $this->addFieldMapping('field_images', 'field_images');
    $this
      ->addFieldMapping('field_images:file_replace')
      ->defaultValue(FILE_EXISTS_REPLACE);
    $this
      ->addFieldMapping('field_images:source_dir')
      ->defaultValue(drupal_get_path('module', 'opengizra_migrate') . '/images');
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
    array('field_season', 'Season'),
    array('field_item_status', 'Status'),
    array('field_image', 'Image'),
  );

  public $entityType = 'node';
  public $bundle = 'item';

  public $dependencies = array(
    'openGizraItemStatusTerms',
    'openGizraSeasons',
  );

  public function __construct() {
    parent::__construct();
    $this->addFieldMapping('body', 'body');
    $this
      ->addFieldMapping('field_season', 'field_season')
      ->sourceMigration('openGizraSeasons');

    $this
      ->addFieldMapping('field_item_status', 'field_item_status')
      ->sourceMigration('openGizraItemStatusTerms');

    $this->addFieldMapping('field_image', 'field_image');
    $this
      ->addFieldMapping('field_image:file_replace')
      ->defaultValue(FILE_EXISTS_REPLACE);
    $this
      ->addFieldMapping('field_image:source_dir')
      ->defaultValue(drupal_get_path('module', 'opengizra_migrate') . '/images');
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
    'openGizraSeasons',
    'openGizraItems',
    'openGizraItemVariants',
  );

  public function __construct() {
    parent::__construct();
    $this->addFieldMapping('body', 'body');
    $this
      ->addFieldMapping('field_entity_reference', 'field_entity_reference')
      ->sourceMigration(array('openGizraSeasons', 'openGizraItems','openGizraItemVariants'));

    $this
      ->addFieldMapping('field_task_status', 'field_task_status')
      ->sourceMigration('openGizraTaskStatusTerms');
  }
}

/**
 * Migrate Item variants nodes.
 */
class openGizraItemVariants extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('title', 'Title'),
    array('field_item', 'Item'),
    array('field_images', 'Images'),
  );

  public $entityType = 'node';
  public $bundle = 'item_variant';

  public $dependencies = array(
    'openGizraItems',
  );

  public function __construct() {
    parent::__construct();
    $this->addFieldMapping('body', 'body');
    $this
      ->addFieldMapping('field_item', 'field_item')
      ->sourceMigration('openGizraItems');


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
 * Migrate "Status info" field collection.
 */
class openGizraCollectionsFieldStatusInfo extends openGizraFieldCollectionMigration {
  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('host_entity_id', 'Season'),
    array('field_season_status', 'Status'),
    array('field_date', 'Deadline'),
  );

  public $entityType = 'field_collection_item';
  public $bundle = 'field_status_info';
  public $hostEntityType = 'node';

  public $dependencies = array(
    'openGizraSeasonStatusTerms',
    'openGizraSeasons',
  );

  public function __construct() {
    parent::__construct();
    $this
      ->addFieldMapping('host_entity_id', 'host_entity_id')
      ->sourceMigration('openGizraSeasons');

    $this
      ->addFieldMapping('field_season_status', 'field_season_status')
      ->sourceMigration('openGizraSeasonStatusTerms');

    $this->addFieldMapping('field_date', 'field_date');
  }
}


/**
 * Migrate "Size info" field collection.
 */
class openGizraCollectionsFieldSizeInfo extends openGizraFieldCollectionMigration {
  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('host_entity_id', 'Item variant'),
    array('field_size', 'Size'),
    array('field_sku', 'SKU'),
  );

  public $entityType = 'field_collection_item';
  public $bundle = 'field_size_info';
  public $hostEntityType = 'node';

  public $dependencies = array(
    'openGizraSizeTerms',
    'openGizraItemVariants',
  );

  public function __construct() {
    parent::__construct();
    $this
      ->addFieldMapping('host_entity_id', 'host_entity_id')
      ->sourceMigration('openGizraItemVariants');

    $this
      ->addFieldMapping('field_size', 'field_size')
      ->sourceMigration('openGizraSizeTerms');

    $this->addFieldMapping('field_sku', 'field_sku');
  }
}


/**
 * Migrate "Source info" field collection.
 */
class openGizraCollectionsFieldSourceInfo extends openGizraFieldCollectionMigration {
  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('host_entity_id', 'Material'),
    array('field_vendor', 'Vendor'),
    array('field_price', 'Price'),
    array('field_unit', 'Unit'),
  );

  public $entityType = 'field_collection_item';
  public $bundle = 'field_source_info';
  public $hostEntityType = 'node';

  public $dependencies = array(
    'openGizraMaterials',
    'openGizraVendors',
  );

  public function __construct() {
    parent::__construct();
    $this
      ->addFieldMapping('host_entity_id', 'host_entity_id')
      ->sourceMigration('openGizraMaterials');

    $this
      ->addFieldMapping('field_vendor', 'field_vendor')
      ->sourceMigration('openGizraVendors');

    $this->addFieldMapping('field_price', 'field_price');
    $this->addFieldMapping('field_unit', 'field_unit');
  }
}


/**
 * Migrate "Bom info" field collection.
 */
class openGizraCollectionsFieldBomInfo extends openGizraFieldCollectionMigration {
  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('host_entity_id', 'Item variant'),
    array('field_material', 'Material'),
    array('field_unit', 'Unit'),
    array('field_quantity', 'Quantity'),
  );

  public $entityType = 'field_collection_item';
  public $bundle = 'field_bom_info';
  public $hostEntityType = 'node';

  public $dependencies = array(
    'openGizraItemVariants',
    'openGizraMaterials',
  );

  public function __construct() {
    parent::__construct();
    $this
      ->addFieldMapping('host_entity_id', 'host_entity_id')
      ->sourceMigration('openGizraItemVariants');

    $this
      ->addFieldMapping('field_material', 'field_material')
      ->sourceMigration('openGizraMaterials');

    $this->addFieldMapping('field_unit', 'field_unit');
    $this->addFieldMapping('field_quantity', 'field_quantity');
  }
}
