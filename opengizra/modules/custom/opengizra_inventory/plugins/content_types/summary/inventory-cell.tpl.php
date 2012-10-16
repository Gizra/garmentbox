<div class="quantity"><?php print $quantity; ?></div>
<?php if ($availability): ?>
  <div class="availability <?php print $class; ?>">
    <span class="amount"><?php print $availability; ?></span><span class="label"><?php print $label; ?></span>
  </div>
<?php endif; ?>
