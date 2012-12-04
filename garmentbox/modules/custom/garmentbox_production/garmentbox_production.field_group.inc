<?php
/**
 * @file
 * garmentbox_production.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function garmentbox_production_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_contact_person|node|factory|form';
  $field_group->group_name = 'group_contact_person';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'factory';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Contact person',
    'weight' => '38',
    'children' => array(
      0 => 'field_contact_name',
      1 => 'field_email',
      2 => 'field_phone',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_contact_person|node|factory|form'] = $field_group;

  return $export;
}
