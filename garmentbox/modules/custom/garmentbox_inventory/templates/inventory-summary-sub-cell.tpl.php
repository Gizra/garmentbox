<div class="inventory-sub-cell clearfix">
  <?php if ($quantity): ?>
    <div class="main-figure <?php print $class; ?>">
      <span class="amount"><?php print $quantity; ?></span>
    </div>

    <?php if ($ordered): ?>
      <div class="sub-figure">
        <div class="ordered"><?php print $ordered; ?> <span class="label"><?php print t('ordered'); ?></span></div>
      </div>
    <?php endif; ?>
  <?php endif; ?>
</div>
