<?php
/**
 * @file
 * garmentbox_og.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function garmentbox_og_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:department:create address content'
  $permissions['node:department:create address content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:create article content'
  $permissions['node:department:create article content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:create customer content'
  $permissions['node:department:create customer content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:create event content'
  $permissions['node:department:create event content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:create factory content'
  $permissions['node:department:create factory content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:create inventory_line content'
  $permissions['node:department:create inventory_line content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:create item content'
  $permissions['node:department:create item content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:create item_variant content'
  $permissions['node:department:create item_variant content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:create material content'
  $permissions['node:department:create material content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:create order content'
  $permissions['node:department:create order content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:create page content'
  $permissions['node:department:create page content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:create pattern content'
  $permissions['node:department:create pattern content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:create pattern_task content'
  $permissions['node:department:create pattern_task content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:create production_order content'
  $permissions['node:department:create production_order content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:create season content'
  $permissions['node:department:create season content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:create task content'
  $permissions['node:department:create task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:create vendor content'
  $permissions['node:department:create vendor content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:update any address content'
  $permissions['node:department:update any address content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:update any article content'
  $permissions['node:department:update any article content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:update any customer content'
  $permissions['node:department:update any customer content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:update any event content'
  $permissions['node:department:update any event content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:update any factory content'
  $permissions['node:department:update any factory content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:update any inventory_line content'
  $permissions['node:department:update any inventory_line content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:update any item content'
  $permissions['node:department:update any item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:update any item_variant content'
  $permissions['node:department:update any item_variant content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:update any material content'
  $permissions['node:department:update any material content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:update any order content'
  $permissions['node:department:update any order content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:update any page content'
  $permissions['node:department:update any page content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:update any pattern content'
  $permissions['node:department:update any pattern content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:update any pattern_task content'
  $permissions['node:department:update any pattern_task content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:update any production_order content'
  $permissions['node:department:update any production_order content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:update any season content'
  $permissions['node:department:update any season content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:update any task content'
  $permissions['node:department:update any task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:update any vendor content'
  $permissions['node:department:update any vendor content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:update own address content'
  $permissions['node:department:update own address content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:update own article content'
  $permissions['node:department:update own article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:update own customer content'
  $permissions['node:department:update own customer content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:update own event content'
  $permissions['node:department:update own event content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:update own factory content'
  $permissions['node:department:update own factory content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:update own inventory_line content'
  $permissions['node:department:update own inventory_line content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:update own item content'
  $permissions['node:department:update own item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:update own item_variant content'
  $permissions['node:department:update own item_variant content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:update own material content'
  $permissions['node:department:update own material content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:update own order content'
  $permissions['node:department:update own order content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:update own page content'
  $permissions['node:department:update own page content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:update own pattern content'
  $permissions['node:department:update own pattern content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:update own pattern_task content'
  $permissions['node:department:update own pattern_task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:update own production_order content'
  $permissions['node:department:update own production_order content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:update own season content'
  $permissions['node:department:update own season content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:department:update own task content'
  $permissions['node:department:update own task content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:department:update own vendor content'
  $permissions['node:department:update own vendor content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  return $permissions;
}
