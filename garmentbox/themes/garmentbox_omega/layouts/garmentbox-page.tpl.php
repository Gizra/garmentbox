<?php
/**
 * @file garmentbox.tpl.php
 * Template for garmentbox pages with tabs section.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['tabs']: Tabs section.
 *   - $content['content']: 'Content section.
 */

?>

<?php if($content['tabs']): ?>
  <section class="tabs clearfix">
    <?php print $content['tabs']; ?>
  </section>
<?php endif; ?>

<?php if($content['content']): ?>
  <section class="content clearfix">
    <?php print $content['content']; ?>
  </section>
<?php endif; ?>
