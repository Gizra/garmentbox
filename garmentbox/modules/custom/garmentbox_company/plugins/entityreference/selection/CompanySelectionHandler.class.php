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
    // Get the query from the base selection handler.
    $handler = EntityReference_SelectionHandler_Generic::getInstance($this->field, $this->instance, $this->entity_type, $this->entity);
    $query = $handler->buildEntityFieldQuery($match, $match_operator);
    // TODO: Check which vocabularies should include the og_company condition.
    if ($query->entityConditions['entity_type']['value'] == 'taxonomy_term') {
      return $query;
    }

    if (!$og_context = og_context()) {
      return $query;
    }

    $field_name = $this->field['settings']['target_type'] == 'user' ? 'og_user_company' : 'og_company';
    $query->fieldCondition($field_name, 'target_id', $og_context['gid']);
    return $query;
  }
}
