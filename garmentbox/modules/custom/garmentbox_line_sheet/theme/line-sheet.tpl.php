<fieldset class="collapsible">
  <legend><span class="fieldset-legend"><?php if (!empty($title)) : ?><?php print $title; ?><?php endif; ?></span></legend>
  <hr class="fieldset-hr">
  <div class="fieldset-wrapper line-sheet-item clearfix">

    <div class="col-first">
      <?php if ($images): ?>
        <div class="images"><?php print $images; ?></div>
      <?php endif; ?>
    </div>

    <div class="col-last">
      <?php if ($prices): ?>
        <?php print $prices; ?>
      <?php endif; ?>

      <?php if ($variants): ?>
        <?php print $variants; ?>
      <?php endif; ?>
    </div>
  </div>
</fieldset>



