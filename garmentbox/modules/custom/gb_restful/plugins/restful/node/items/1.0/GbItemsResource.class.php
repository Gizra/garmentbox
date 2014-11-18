<?php

/**
 * @file
 * Contains GbItemsResource.
 */

class GbItemsResource extends \GbEntityBaseNode {


  /**
   * Overrides \RestfulEntityBaseNode::publicFieldsInfo().
   */
  public function publicFieldsInfo() {
    $public_fields = parent::publicFieldsInfo();

    $public_fields['company'] = array(
      'property' => OG_AUDIENCE_FIELD,
      'resource' => array(
        'company' => array(
          'resource_name' => 'companies',
          'full_view' => FALSE,
        )
      ),
    );

    return $public_fields;
  }
}
