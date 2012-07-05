<?php
// $Id: zen-ninesixty-threecol-stacked.tpl.php,v 1.1 2010/04/11 08:42:36 amitaibu Exp $
/**
 * @file
 * Template for a 2 column panel layout.
 *
 * This template provides a two column panel display layout, with
 * additional areas for the top and the bottom.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['top']: Content in the top row.
 *   - $content['left']: Content in the left column.
 *   - $content['middle']: Content in the middle column.
 *   - $content['right']: Content in the right column.
 *   - $content['bottom']: Content in the bottom row.
 */
?>

<?php
  // Define the grid for each panel column.
  $grid = array(
    'top'    => 'grid-24 alpha omega',
    'first'   => 'grid-16 suffix-1 alpha',
    'last' => 'grid-7 omega',
    'bottom' => 'grid-24 alpha omega',
  );

?>

<div class="panel-grid-17-7 clear-block panel-display" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <div class="panel-col-top panel-panel <?php print $grid['top']; ?>">
    <div class="inside"><?php print $content['top']; ?></div>
  </div>

  <div class="panel-col-first panel-panel <?php print $grid['first']; ?>">
    <div class="inside"><?php print $content['first']; ?></div>
  </div>

  <div class="panel-col-last sound-sample-files panel-panel <?php print $grid['last']; ?>">
    <div class="inside"><?php print $content['last']; ?></div>
  </div>


  <div class="panel-col-bottom panel-panel <?php print $grid['bottom']; ?>">
    <div class="inside"><?php print $content['bottom']; ?></div>
  </div>
</div>