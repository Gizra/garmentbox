<?php

/**
 * @file
 * Defines the inline entity form controller for Inventory line node type.
 */

class NodeInventoryLineInlineEntityFormController extends NodeInlineEntityFormController {

  /**
   * Overrides EntityInlineEntityFormController::defaultFields().
   */
  public function defaultFields($bundles) {
    $fields = array();

    $fields['author'] = array(
      'type' => 'property',
      'label' => 'Author',
      'visible' => TRUE,
      'weight' => 2,
    );
    return $fields;
  }
}
