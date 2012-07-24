<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <?php print $picture; ?>
  <?php print $changed_fields; ?>
  <div class="content"<?php print $content_attributes; ?>>
    <div class="submitted">
      <?php print $author; ?>
    </div>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['links']);
      print render($content);
    ?>
  </div>
</div>
