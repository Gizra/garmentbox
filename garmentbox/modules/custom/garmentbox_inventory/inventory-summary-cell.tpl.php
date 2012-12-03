<div class="inventory-cell clearfix">
  <div class="main-figure">
    <span class="amount <?php if ($quantity_title): ?>with-title<?php endif; ?>"><?php print $quantity; ?></span><?php if ($quantity_title): ?><span class="label"><?php print $quantity_title; ?></span><?php endif; ?>
  </div>

  <div class="sub-figures">
    <?php foreach($subfigure_types as $type => $label): ?>
      <?php if ($$type || $type == 'available' && $$type !== NULL): ?>
        <div class="sub-figure <?php print $type; ?>">
          <span class="amount"><?php print $$type; ?></span><span class="label"><?php print $label; ?></span>
        </div>
      <?php endif; ?>
    <?php endforeach; ?>
  </div>
</div>
