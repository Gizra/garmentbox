<div class="line-sheet-item">

  <div class="title"><?php print $title; ?></div>

  <?php if ($body): ?>
    <div class="description"><?php print $body; ?></div>
  <?php endif; ?>

  <?php if ($sizes): ?>
    <label><?php print t('Sizes'); ?></label>
    <?php print $sizes; ?>
  <?php endif; ?>

  <?php if ($materials): ?>
    <label><?php print t('Materials'); ?></label>
    <?php print $materials; ?>
  <?php endif; ?>

  <?php if ($images): ?>
    <div class="images"><?php print $images; ?></div>
  <?php endif; ?>

  <?php //print $links; ?>
</div>


