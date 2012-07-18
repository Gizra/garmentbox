<?php
?>
<div id="page" class="container-16 clearfix">

  <div id="site-header" class="clearfix">
    <div id="branding" class="grid-4">
    <?php if ($logo_img || $site_name): ?>
      <h1 id="brand-id">
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home">
          <?php print $logo_img; ?>
          <?php if ($site_name): ?><span class="site-name"><?php print $site_name; ?></span><?php endif; ?>
        </a>
      </h1>
    <?php endif ?>
    <?php if ($site_slogan): ?>
      <div id="site-slogan"><?php print $site_slogan; ?></div>
    <?php endif; ?>
    </div>

  <?php if ($main_menu_links || $secondary_menu_links): ?>
    <div id="site-menu" class="grid-12">
      <?php print $main_menu_links; ?>
      <?php print $secondary_menu_links; ?>
    </div>
  <?php endif; ?>

  <?php if ($page['search_box']): ?>
    <div id="search-box" class="grid-3 prefix-9"><?php print render($page['search_box']); ?></div>
  <?php endif; ?>
  </div>


<?php if ($messages || $page['highlighted'] || $page['header']): ?>
  <div id="site-subheader" class="clearfix prefix-1 suffix-1">
  <?php if ($messages): ?>
    <div id="header-messages" class="grid-14">
      <?php print $messages; ?>
    </div>
  <?php endif; ?>
  <?php if ($page['highlighted']): ?>
    <div id="highlighted" class="clearfix<?php print ns(' grid-14', $page['header'], 7); ?>">
      <?php print render($page['highlighted']); ?>
    </div>
  <?php endif; ?>

  <?php if ($page['header']): ?>
    <div id="header-region" class="clearfix<?php print ns(' grid-14', $page['highlighted'], 7); ?>">
      <?php print render($page['header']); ?>
    </div>
  <?php endif; ?>
  </div>
<?php endif; ?>


  <div id="main" class="column<?php print ns(' grid-16', $page['sidebar_first'], 4, $page['sidebar_second'], 3) . ns(' push-4', !$page['sidebar_first'], 4); ?>">
    <?php print $breadcrumb; ?>

    <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <h1 class="title" id="page-title">
      <?php print $title; ?>
    </h1>
  <?php endif; ?>
    <?php print render($title_suffix); ?>

  <?php if ($tabs['#primary']): ?>
    <div class="tabs">
      <?php print render($tabs); ?>
    </div>
  <?php endif; ?>

    <?php print render($page['help']); ?>
    <?php if ($action_links): ?>
      <ul class="action-links"><?php print render($action_links); ?></ul>
    <?php endif; ?>

    <div id="main-content" class="clearfix">
      <?php print render($page['content']); ?>
    </div>

    <?php print $feed_icons; ?>
  </div>

<?php if ($page['sidebar_first']): ?>
  <div id="sidebar-first" class="column sidebar grid-4<?php print ns(' pull-12', $page['sidebar_second'], 3); ?>">
    <?php print render($page['sidebar_first']); ?>
  </div>
<?php endif; ?>

<?php if ($page['sidebar_second']): ?>
  <div id="sidebar-second" class="column sidebar grid-3">
    <?php print render($page['sidebar_second']); ?>
  </div>
<?php endif; ?>


  <div id="footer" class="clear clearfix prefix-1 suffix-1">
  <?php if ($page['footer']): ?>
    <div id="footer-region" class="grid-14">
      <?php print render($page['footer']); ?>
    </div>
  <?php endif; ?>
  </div>


</div>
