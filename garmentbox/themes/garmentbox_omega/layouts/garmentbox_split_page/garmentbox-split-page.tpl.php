<?php
/**
 * @file garmentbox.tpl.php
 * Template for garmentbox split pages.
 *
 * Variables:
 * - $id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   - $content['content_first']: First content section.
 *   - $content['content_last']: Second content section.
 */

?>

<section class="content clearfix">
  <?php if($content['content_first']): ?>
    <div class="panel-col-first">
      <?php print $content['content_first']; ?>
    </div>
  <?php endif; ?>
  <?php if($content['content_last']): ?>
    <div class="panel-col-last">
      <?php print $content['content_last']; ?>
    </div>
  <?php endif; ?>
</section>
