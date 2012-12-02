<?php


/**
 * GarmentBox Company selection handler.
 */
class CompanySelectionHandler extends EntityReference_SelectionHandler_Generic {

  /**
   * Implements EntityReferenceHandler::getInstance().
   */
  public static function getInstance($field, $instance = NULL, $entity_type = NULL, $entity = NULL) {
    return new CompanySelectionHandler($field, $instance, $entity_type, $entity);
  }


  /**
   * Build an EntityFieldQuery to get referencable entities.
   */
  public function buildEntityFieldQuery($match = NULL, $match_operator = 'CONTAINS') {
    global $user;

    // Get the query from the base selection handler.
    $handler = EntityReference_SelectionHandler_Generic::getInstance($this->field, $this->instance, $this->entity_type, $this->entity);
    $query = $handler->buildEntityFieldQuery($match, $match_operator);

    // Set the correct selection handler to point to our class.
    $query->addMetaData('entityreference_selection_handler', $this);

    if (!$og_context = og_context()) {
      return $query;
    }

    if ($query->entityConditions['entity_type']['value'] != 'node') {
      return $query;
    }

    $query->fieldCondition('og_company', 'target_id', $og_context['gid']);
    return $query;
  }
}
