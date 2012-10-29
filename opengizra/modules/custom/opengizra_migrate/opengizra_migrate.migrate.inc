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
    array('weight', 'Weight'),
  );

  public $entityType = 'taxonomy_term';
  public $bundle = 'size';

  public function __construct() {
    parent::__construct();
    $this->addFieldMapping('weight', 'weight');
  }
}

/**
 * Migrate Size terms.
 */
class openGizraInventoryTypeTerms extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('name', 'Name'),
    array('field_include_in_total', 'Include in total'),
    array('field_in_warehouse', 'In warehouse'),
    array('field_closed_stock', 'Closed stock'),
  );

  public $entityType = 'taxonomy_term';
  public $bundle = 'inventory_type';

  public function __construct() {
    parent::__construct();
    $this->addFieldMapping('field_include_in_total', 'field_include_in_total');
    $this->addFieldMapping('field_in_warehouse', 'field_in_warehouse');
    $this->addFieldMapping('field_closed_stock', 'field_closed_stock');
  }
}

/**
 * Migrate measurement unit terms.
 */
class openGizraMeasurementUnitTerms extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('name', 'Name'),
    array('field_unit_type', 'Type'),
    array('field_conversion_ratio', 'Conversion'),
  );

  public $entityType = 'taxonomy_term';
  public $bundle = 'measurement_units';

  public function __construct() {
    parent::__construct();
    $this->addFieldMapping('field_unit_type', 'field_unit_type');
    $this->addFieldMapping('field_conversion_ratio', 'field_conversion_ratio');
  }
}

/**
 * Migrate BOL terms.
 */
class openGizraBolTerms extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('name', 'Name'),
  );

  public $entityType = 'taxonomy_term';
  public $bundle = 'bol';
}

/**
 * Migrate order status terms.
 */
class openGizraOrderStatusTerms extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('name', 'Name'),
  );

  public $entityType = 'taxonomy_term';
  public $bundle = 'order_status';
}

///////////////////////////////
// Nodes

/**
 * Migrate Department nodes.
 */
class openGizraDepartments extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('title', 'Title'),
  );

  public $entityType = 'node';
  public $bundle = 'department';

  public function complete($node) {
    if ($node->title == 'Main') {
      variable_set('opengizra_og_main_department', $node->nid);
    }
  }
}

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
    'openGizraDepartments',
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
 * Migrate Address nodes.
 */
class openGizraAddresses extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('title', 'Title'),
    array('profile_address', 'Address'),
    array('profile_city', 'City'),
    array('profile_state', 'State'),
    array('profile_country', 'Country'),
  );

  public $entityType = 'node';
  public $bundle = 'address';

  public $dependencies = array(
    'openGizraDepartments',
  );

  public function __construct() {
    parent::__construct();

    $arguments = array(
      'thoroughfare' => array('source_field' => 'profile_address'),
      'locality' => array('source_field' => 'profile_city'),
      'administrative_area' => array('source_field' => 'profile_state'),
    );
    // The country should be passed in as the primary value.
    $this->addFieldMapping('field_postal_address', 'profile_country')
         ->arguments($arguments)
         ->description('Address field');
    // Since the excerpt is mapped via an argument, add a null mapping so it's
    // not flagged as unmapped.
    $this->addFieldMapping(NULL, 'profile_address');
    $this->addFieldMapping(NULL, 'profile_city');
    $this->addFieldMapping(NULL, 'profile_state');
  }
}

/**
 * Migrate Vendors nodes.
 */
class openGizraVendors extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('title', 'Title'),
    array('field_address_inline', 'Address'),
  );

  public $entityType = 'node';
  public $bundle = 'vendor';

  public $dependencies = array(
    'openGizraDepartments',
    'openGizraAddresses',
  );

  public function __construct() {
    parent::__construct();
    $this->addFieldMapping('body', 'body');

    $this
      ->addFieldMapping('field_address_inline', 'field_address_inline')
      ->sourceMigration('openGizraAddresses');
  }
}

/**
 * Migrate Customers nodes.
 */
class openGizraCustomers extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('title', 'Title'),
    array('field_addresses_inline', 'Address'),
  );

  public $entityType = 'node';
  public $bundle = 'customer';

  public $dependencies = array(
     'openGizraAddresses',
  );

  public function __construct() {
    parent::__construct();

    $this
      ->addFieldMapping('field_addresses_inline', 'field_addresses_inline')
      ->sourceMigration('openGizraAddresses');
  }

  function prepareRow($row) {
    parent::prepareRow($row);
    $row->field_addresses_inline = explode('; ', $row->field_addresses_inline);
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
    'openGizraDepartments',
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
    'openGizraDepartments',
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
    'openGizraDepartments',
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
    array('field_item_status', 'Status'),
    array('field_retail_price', 'Retail price'),
    array('field_wholesale_price', 'Wholesale price'),
  );

  public $entityType = 'node';
  public $bundle = 'item_variant';

  public $dependencies = array(
    'openGizraDepartments',
    'openGizraItems',
    'openGizraItemStatusTerms',
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

    $this
      ->addFieldMapping('field_item_status', 'field_item_status')
      ->sourceMigration('openGizraItemStatusTerms');

    $this->addFieldMapping('field_retail_price', 'field_retail_price');

    $this->addFieldMapping('field_wholesale_price', 'field_wholesale_price');
  }

  function prepareRow($row) {
    parent::prepareRow($row);
    $row->field_images = explode('; ', $row->field_images);
  }
}

/**
 * Migrate inventory line nodes.
 */
class openGizraInventoryLines extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('title', 'Title'),
    array('field_item_variant', 'Item variant'),
    array('field_inventory_type', 'Type'),
    array('field_production_start_date', 'Production date'),
    array('field_delivery_date', 'Delivery date'),
    array('field_inventory_status', 'Status'),
  );

  public $entityType = 'node';
  public $bundle = 'inventory_line';

  public $dependencies = array(
    'openGizraDepartments',
    'openGizraItemVariants',
    'openGizraInventoryTypeTerms',
  );

  public function __construct() {
    parent::__construct();

    $this
      ->addFieldMapping('field_item_variant', 'field_item_variant')
      ->sourceMigration('openGizraItemVariants');

    $this
      ->addFieldMapping('field_inventory_type', 'field_inventory_type')
      ->sourceMigration('openGizraInventoryTypeTerms');

    $this->addFieldMapping('field_production_start_date', 'field_production_start_date');
    $this->addFieldMapping('field_delivery_date', 'field_delivery_date');

    $this->addFieldMapping('field_inventory_status', 'field_inventory_status');
  }
}

/**
 * Migrate order nodes.
 */
class openGizraOrders extends openGizraMigration {

  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('title', 'Title'),
    array('field_season', 'Season'),
    array('field_customer', 'Customer'),
    array('field_address', 'Address'),
    array('field_inventory_line_inline', 'Inventory line'),
    array('field_order_status', 'Status'),
  );

  public $entityType = 'node';
  public $bundle = 'order';

  public $dependencies = array(
    'openGizraSeasons',
    'openGizraCustomers',
    'openGizraAddresses',
    'openGizraInventoryLines',
    'openGizraOrderStatusTerms'
  );

  public function __construct() {
    parent::__construct();

    $this
      ->addFieldMapping('field_season', 'field_season')
      ->sourceMigration('openGizraSeasons');

    $this
      ->addFieldMapping('field_customer', 'field_customer')
      ->sourceMigration('openGizraCustomers');

    $this
      ->addFieldMapping('field_address', 'field_address')
      ->sourceMigration('openGizraAddresses');

    $this
      ->addFieldMapping('field_inventory_line_inline', 'field_inventory_line_inline')
      ->sourceMigration('openGizraInventoryLines')
      ->separator('|');

    $this
      ->addFieldMapping('field_order_status', 'field_order_status')
      ->sourceMigration('openGizraOrderStatusTerms');
  }

  public function prepare($entity, $row) {
    // Fix the field_inventory_line_inline values.
    foreach ($entity->field_inventory_line_inline[LANGUAGE_NONE] as $delta => $values) {
      $target_id = $values['target_id']['destid1'];
      $entity->field_inventory_line_inline[LANGUAGE_NONE][$delta]['target_id'] = $target_id;
    }
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
    array('field_length', 'Length'),
    array('field_length_unit', 'Length unit'),
  );

  public $entityType = 'field_collection_item';
  public $bundle = 'field_source_info';
  public $hostEntityType = 'node';

  public $dependencies = array(
    'openGizraMaterials',
    'openGizraVendors',
    'openGizraMeasurementUnitTerms',
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

    $this
      ->addFieldMapping('field_unit', 'field_unit')
      ->sourceMigration('openGizraMeasurementUnitTerms');

    $this->addFieldMapping('field_length', 'field_length');

    $this
      ->addFieldMapping('field_length_unit', 'field_length_unit')
      ->sourceMigration('openGizraMeasurementUnitTerms');
  }
}

/**
 * Migrate "Bom info" field collection.
 */
class openGizraCollectionsFieldBomInfo extends openGizraFieldCollectionMigration {
  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('host_entity_id', 'Item variant'),
    array('field_material_item', 'Material source'),
    array('field_unit', 'Unit'),
    array('field_quantity', 'Quantity'),
  );

  public $entityType = 'field_collection_item';
  public $bundle = 'field_bom_info';
  public $hostEntityType = 'node';

  public $dependencies = array(
    'openGizraItemVariants',
    'openGizraMaterials',
    'openGizraCollectionsFieldSourceInfo',
    'openGizraMeasurementUnitTerms',
  );

  public function __construct() {
    parent::__construct();
    $this
      ->addFieldMapping('host_entity_id', 'host_entity_id')
      ->sourceMigration('openGizraItemVariants');

    $this
      ->addFieldMapping('field_material_item', 'field_material_item')
      ->sourceMigration('openGizraCollectionsFieldSourceInfo');

    $this
      ->addFieldMapping('field_unit', 'field_unit')
      ->sourceMigration('openGizraMeasurementUnitTerms');

    $this->addFieldMapping('field_quantity', 'field_quantity');
  }
}

/**
 * Migrate "Bol info" field collection.
 */
class openGizraCollectionsFieldBolInfo extends openGizraFieldCollectionMigration {
  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('host_entity_id', 'Item variant'),
    array('field_bol_term', 'Labour'),
    array('field_price', 'Price'),
  );

  public $entityType = 'field_collection_item';
  public $bundle = 'field_bol_info';
  public $hostEntityType = 'node';

  public $dependencies = array(
    'openGizraItemVariants',
    'openGizraBolTerms'
  );

  public function __construct() {
    parent::__construct();
    $this
      ->addFieldMapping('host_entity_id', 'host_entity_id')
      ->sourceMigration('openGizraItemVariants');

    $this
      ->addFieldMapping('field_bol_term', 'field_bol_term')
      ->sourceMigration('openGizraBolTerms');

    $this->addFieldMapping('field_price', 'field_price');
  }
}

/**
 * Migrate "Quantity info" field collection.
 */
class openGizraCollectionsFieldQuantityInfo extends openGizraFieldCollectionMigration {
  public $csvColumns = array(
    array('id', 'Unique ID'),
    array('host_entity_id', 'Inventory line'),
    array('field_size', 'Size'),
    array('field_quantity', 'Quantity'),
  );

  public $entityType = 'field_collection_item';
  public $bundle = 'field_quantity_info';
  public $hostEntityType = 'node';

  public $dependencies = array(
    'openGizraInventoryLines',
    'openGizraSizeTerms',
  );

  public function __construct() {
    parent::__construct();
    $this
      ->addFieldMapping('host_entity_id', 'host_entity_id')
      ->sourceMigration('openGizraInventoryLines');

    $this
      ->addFieldMapping('field_size', 'field_size')
      ->sourceMigration('openGizraSizeTerms');

    $this->addFieldMapping('field_quantity', 'field_quantity');
  }
}
