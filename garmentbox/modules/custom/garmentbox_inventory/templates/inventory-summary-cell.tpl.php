<div class="inventory-cell clearfix">
  <div class="main-figure">
    <span class="amount"><?php print $available; ?> </span>
    <div class="label"><?php print t('available'); ?></div>
  </div>

  <?php if ($has_subfigures): ?>
    <div class="sub-figures">
      <?php foreach($subfigure_types as $type => $label): ?>
          <div class="sub-figure <?php print $type; ?>">
            <?php if ($$type): ?>
              <span class="amount"><?php print $$type; ?></span><span class="label"><?php print $label; ?></span>
            <?php else: ?>
              <span class="sub-figure-placeholder"></span>
            <?php endif; ?>
          </div>
      <?php endforeach; ?>
    </div>
  <?php endif; ?>
</div>
