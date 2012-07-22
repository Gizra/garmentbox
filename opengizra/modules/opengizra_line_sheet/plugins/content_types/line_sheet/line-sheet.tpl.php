<div class="line-sheet-item">
  <?php if ($body): ?>
    <div class="description"><?php print $body; ?></div>
  <?php endif; ?>

  <?php if ($sizes): ?>
    <label><?php print t('Sizes'); ?></label>
    <?php print $sizes; ?>
  <?php endif; ?>

  <?php if ($images): ?>
    <div class="images"><?php print $images; ?></div>
  <?php endif; ?>

  <?php print $links; ?>
</div>


