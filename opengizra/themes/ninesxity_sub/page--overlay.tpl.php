
<div id="content" class="clearfix">

  <?php if ($messages): ?>
    <div id="header-messages">
      <div class="messages-background">
        <div class="messages-wrapper">
          <?php print $messages; ?>
        </div>
      </div>
    </div>
  <?php endif; ?>


  <div id="main">
    <?php if (isset($tabs['#primary'])  ): ?>
      <div class="tabs">
        <?php print render($tabs); ?>
      </div>
    <?php endif; ?>

    <?php if ($action_links): ?>
      <ul class="action-links">
        <?php print render($action_links); ?>
      </ul>
    <?php endif; ?>

    <?php print render($page['help']); ?>

    <?php print render($title_prefix); ?>
    <?php if ($title): ?>
      <h1 class="title" id="page-title">
        <?php print $title; ?>
      </h1>
    <?php endif; ?>
    <?php print render($title_suffix); ?>

    <div id="main-content" class="clearfix">
      <?php print render($page['content']); ?>
    </div>

    <?php print $feed_icons; ?>
  </div>

</div>