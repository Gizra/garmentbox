<?php
/**
 * @file
 * Migrate class to create Garmentbox content.
 */

/**
 * Class GarmentboxDemoCreateGarmentboxContent
 */
class GarmentboxDemoCreateContent extends GarmentboxDemoCreateEntity {
  public $entityType = 'node';
  public $bundle = 'garmentbox_content';

  /**
   * CSV Column mapping.
   *
   * @var array
   */
  public $csvColumns = array(
    array('id', 'ID'),
    array('title', 'Title'),
    array('body', 'Body'),
  );

  /**
   * Configure the object during creation.
   */
  public function __construct() {
    parent::__construct();

    $this->addFieldMapping('body', 'body');
  }
}
