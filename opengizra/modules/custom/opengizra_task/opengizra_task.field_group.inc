<?php
/**
 * @file
 * opengizra_task.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function opengizra_task_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_properties|comment|comment_node_task|form';
  $field_group->group_name = 'group_properties';
  $field_group->entity_type = 'comment';
  $field_group->bundle = 'comment_node_task';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Change properties',
    'weight' => '0',
    'children' => array(
      0 => 'field_entity_reference',
      1 => 'field_task_assignee',
      2 => 'field_task_status',
      3 => 'subject_field',
      4 => 'field_date',
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
  $export['group_properties|comment|comment_node_task|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_properties|node|task|form';
  $field_group->group_name = 'group_properties';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'task';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Properties',
    'weight' => '2',
    'children' => array(
      0 => 'field_entity_reference',
      1 => 'field_task_assignee',
      2 => 'field_task_status',
      3 => 'field_date',
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
  $export['group_properties|node|task|form'] = $field_group;

  return $export;
}
