<?php
/**
 * @file
 * garmentbox_company.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function garmentbox_company_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:company:create address content'
  $permissions['node:company:create address content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:create article content'
  $permissions['node:company:create article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:create customer content'
  $permissions['node:company:create customer content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:create event content'
  $permissions['node:company:create event content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:create factory content'
  $permissions['node:company:create factory content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:create inventory_line content'
  $permissions['node:company:create inventory_line content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:create item content'
  $permissions['node:company:create item content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:create item_variant content'
  $permissions['node:company:create item_variant content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:create material content'
  $permissions['node:company:create material content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:create order content'
  $permissions['node:company:create order content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:create page content'
  $permissions['node:company:create page content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:create pattern content'
  $permissions['node:company:create pattern content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:create pattern_task content'
  $permissions['node:company:create pattern_task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:create production_order content'
  $permissions['node:company:create production_order content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:create season content'
  $permissions['node:company:create season content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:create task content'
  $permissions['node:company:create task content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:create vendor content'
  $permissions['node:company:create vendor content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:update any address content'
  $permissions['node:company:update any address content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:update any article content'
  $permissions['node:company:update any article content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:update any customer content'
  $permissions['node:company:update any customer content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:update any event content'
  $permissions['node:company:update any event content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:update any factory content'
  $permissions['node:company:update any factory content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:update any inventory_line content'
  $permissions['node:company:update any inventory_line content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:update any item content'
  $permissions['node:company:update any item content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:update any item_variant content'
  $permissions['node:company:update any item_variant content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:update any material content'
  $permissions['node:company:update any material content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:update any order content'
  $permissions['node:company:update any order content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:update any page content'
  $permissions['node:company:update any page content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:update any pattern content'
  $permissions['node:company:update any pattern content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:update any pattern_task content'
  $permissions['node:company:update any pattern_task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:update any production_order content'
  $permissions['node:company:update any production_order content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:update any season content'
  $permissions['node:company:update any season content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:update any task content'
  $permissions['node:company:update any task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:update any vendor content'
  $permissions['node:company:update any vendor content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:update own address content'
  $permissions['node:company:update own address content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:update own article content'
  $permissions['node:company:update own article content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:update own customer content'
  $permissions['node:company:update own customer content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:update own event content'
  $permissions['node:company:update own event content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:update own factory content'
  $permissions['node:company:update own factory content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:update own inventory_line content'
  $permissions['node:company:update own inventory_line content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:update own item content'
  $permissions['node:company:update own item content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:update own item_variant content'
  $permissions['node:company:update own item_variant content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:update own material content'
  $permissions['node:company:update own material content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:update own order content'
  $permissions['node:company:update own order content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:update own page content'
  $permissions['node:company:update own page content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:update own pattern content'
  $permissions['node:company:update own pattern content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:update own pattern_task content'
  $permissions['node:company:update own pattern_task content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:update own production_order content'
  $permissions['node:company:update own production_order content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:update own season content'
  $permissions['node:company:update own season content'] = array(
    'roles' => array(
      'member' => 'member',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:company:update own task content'
  $permissions['node:company:update own task content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:company:update own vendor content'
  $permissions['node:company:update own vendor content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  return $permissions;
}
