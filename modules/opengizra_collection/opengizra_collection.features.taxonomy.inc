<?php
/**
 * @file
 * opengizra_collection.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function opengizra_collection_taxonomy_default_vocabularies() {
  return array(
    'collection' => array(
      'name' => 'Collection',
      'machine_name' => 'collection',
      'description' => 'The collections (e.g. men-2011)',
      'hierarchy' => '2',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
