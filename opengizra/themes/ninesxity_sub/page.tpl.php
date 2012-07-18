<div id="header-wrapper"><div id="header" class="container-24">

  <div id="site-header" class="clearfix <?php print $og_message ? 'open' : 'collapsed'; ?>">
    <div id="branding" class="grid-9">
      <?php if ($logo): ?>
        <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
        </a>
      <?php endif; ?>
    </div>

    <?php if ($page['search_box']): ?>
      <div id="search-box" class="grid-7 suffix-1"><?php print render($page['search_box']); ?></div>
    <?php endif; ?>

    <?php if ($secondary_menu_links): ?>
      <div id ="user-links" class="grid-7">
        <?php print $secondary_menu_links; ?>
      </div>
    <?php endif; ?>

    <?php if ($og_message): ?>
      <div class="grid-24">
        <?php print $og_message; ?>
      </div>
    <?php endif; ?>

  </div>

</div></div> <!-- #header, #header-wrapper -->

<?php if ($messages): ?>
  <div id="header-messages">
    <div class="messages-background">
      <div class="messages-wrapper">
        <?php print $messages; ?>
      </div>
    </div>
  </div>
<?php endif; ?>

<div id="container">
  <div id="page-wrapper">
    <div id="page" class="container-24 clearfix">

    <div class="top-main grid-24">
      <?php if ($action_links): ?>
        <ul class="action-links">
          <?php print render($action_links); ?>
        </ul>
      <?php endif; ?>

      <?php print render($page['help']); ?>

      <?php if ($breadcrumb): ?>
        <?php print render($breadcrumb); ?>
      <?php endif; ?>

      <?php print render($title_prefix); ?>
      <?php if ($title): ?>
        <h1 class="title" id="page-title">
          <?php print $title; ?>
        </h1>
      <?php endif; ?>
      <?php print render($title_suffix); ?>
    </div>

    <div id="main" class="column<?php print ns(' grid-24', $page['sidebar_first'], 5, $page['sidebar_second'], 5) . ns(' push-5', !$page['sidebar_first'], 5); ?>">
      <div id="main-content" class="clearfix">
        <?php print render($tabs); ?>
        <?php print render($page['content']); ?>
      </div>
    </div>

    <?php if ($page['sidebar_first']): ?>
      <div id="sidebar-first" class="column sidebar grid-5<?php print ns(' pull-19', $page['sidebar_second'], 5); ?>">
        <?php print render($page['sidebar_first']); ?>
      </div>
    <?php endif; ?>

    <?php if ($page['sidebar_second']): ?>
      <div id="sidebar-second" class="column sidebar grid-5">
        <?php print render($page['sidebar_second']); ?>
      </div>
    <?php endif; ?>
  </div> <!-- #page -->
  </div> <!-- #page-wrapper -->
</div> <!-- #container -->

<div id="footer-wrapper">
  <div id="footer" class="container-24 clearfix">
    <?php if ($page['footer']): ?>
      <div id="footer-region" class="prefix-5 grid-19">
        <?php print render($page['footer']); ?>
      </div>
    <?php endif; ?>
  </div>
</div>
