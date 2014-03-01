<?php
/**
 * @file
 * Display a single Drupal page inside an overlay.
 */
?>

<div id="main">
  <div id="main-content" role="main" class="container">

    <div id="content" class="clearfix">

      <?php print render($page['highlighted']); ?>
      <a id="main-content-anchor"></a>

      <?php print $messages; ?>

      <?php print render($page['help']); ?>
      <?php if ($action_links): ?>
        <ul class="action-links"><?php print render($action_links); ?></ul>
      <?php endif; ?>


      <?php print render($page['content']); ?>
    </div>
  </div>
</div>
