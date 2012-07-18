
This "framework" theme is based on the 960 Grid System created by Nathan Smith.
The CSS framework is licenced under GPL and MIT. This Drupal theme is licensed
under GPL.

Homepage and download for 960:
  http://960.gs/

Background information on 960:
  http://sonspring.com/journal/960-grid-system

Write-up from DivitoDesign:
  http://www.divitodesign.com/2008/12/960-css-framework-learn-basics/

Write-up from Nettus:
  http://nettuts.com/videos/screencasts/a-detailed-look-at-the-960-css-framework/
  http://nettuts.com/tutorials/html-css-techniques/prototyping-with-the-grid-960-css-framework/

General idea behind a CSS framework:
  http://www.alistapart.com/articles/frameworksfordesigners

Extensive overview on working within grids:
  http://www.smashingmagazine.com/2007/04/14/designing-with-grid-based-approach/

==============================================================================
Modifications:

- The 960 Grid System package has been modified so it conforms to Drupal's
  coding standards. Tabs were removed for double spaces and underscores
  changed to hyphens.

- Additional .push-x and .pull-x classes have been added.
  update: The push and pull classes have been incorporated into 960.gs source.

- Right-to-left languages are supported. It does not use the RTL styles
  included with 960.gs source due to the way Drupal core handles RTL styles.

- The ".clear" class from 960.css repurposed to clear blocks with content. The
  br.clear method can be used in its place while .clear can be applied to
  elements that contain content. 

- Removed the "outline:0;" rule from reset.css. Adding it back manually
  prevents OS specific outline styles from being used. Specifically Webkit and
  possibly others. Also removed the "a:focus {outline: 1px dotted invert;}"
  from text.css where it's reapplied.

- Removed the large left margin for list items inside text.css. It interferes
  in many places.

- From this point forward, any modifications to the source 960.gs files will
  will be noted at the top of each file.

==============================================================================
Notes and rules to play nice with the grids:

- The class .container-[N] ([N] being a numeric value) is a subdivision of the
  overall width (960 pixels). It can be .container-12, .container-16 or
  .container-24. Depending on which is used, each grid unit (.grid-[N] class)
  will be a certain width:

  .container-12
    .grid-1 =  80px [ 10px margin |  60px width  | 10px margin ]
    .grid-2 = 160px [ 10px margin | 140px width  | 10px margin ]
    .grid-3 = 240px [ 10px margin | 220px width  | 10px margin ]

  .container-16
    .grid-1 =  60px [ 10px margin |  40px width  | 10px margin ]
    .grid-2 = 120px [ 10px margin | 100px width  | 10px margin ]
    .grid-3 = 180px [ 10px margin | 160px width  | 10px margin ]

  .container-24
    .grid-1 =  40px [  5px margin |  30px width  |  5px margin ]
    .grid-2 =  80px [  5px margin |  70px width  |  5px margin ]
    .grid-3 = 120px [  5px margin | 110px width  |  5px margin ]

  Note the progression of the inner width and the constant margins of the 12
  and 16 versions vs. what's used for the 24 column version.

- 12 and 16 columns can be used in tandem on a single page given that they
  stay within their own containers. The 24 column version encompasses both the
  12, 16 and beyond in terms of its ability to subdivide the layout so mixing
  .container-24 with the other two is not recommended. The margins also differ
  which will throw off your layout be 5 pixels.

- The default 960 style includes both 12 and 16 column containers. You can
  tell your theme to pick an alternate version with a simple .info entry in
  your theme.

  settings[ns_columns_select] = 12
  settings[ns_columns_select] = 16
  settings[ns_columns_select] = 24
  settings[ns_columns_select] = 12+16 ; the default set by ninesixty base

- Use the .push-[N] and .pull-[N] classes so the order the layout is presented
  does not depend on source order. For example, if the source order was this:
  [content][side-1][side-2], and the desired presentation order was this:
  [side-1][content][side-2]. Adding a .pull-[N] class to #side-1 with the same
  numeric grid value as #content and adding a .push-[N] class to #content with
  the same numeric grid value of #side-1 will swap their positions. These
  classes can also be used for the general shifting of content when needed.

  <div class="container-16">
    <div id="content" class="grid-9 push-4">
      ...                         \  /
    </div>                         \/ Match numeric values to swap.
                                   /\
    <div id="side-1"  class="grid-4 pull-9">
      ...
    </div>

    <div id="side-2" class="grid-3">
      ...
    </div>
  </div>

- Use the .prefix-[N] and .suffix-[N] classes to pad an empty space. Do not
  confuse this with the push/pull classes which are for positioning.

- When embedding a grid within a grid, use .alpha and .omega classes. The
  first block must be assigned .alpha and the last, .omega. This will chop off
  the margin so it fits neatly into the grid.

- When using push/pull in combination with the alpha/omega classes, Which
  element you apply the alpha/omega classes depends more on the
  presentation order than the source order.

As long as you stay within the framework, any positioning quirks especially
from Internet Explorer 6 and 7 should be minimal. 

==============================================================================
Adding classes based on context:

The function "ns()" can be used to add classes contextually. The first argument
should be the default class with the highest possible unit. The rest of the
arguments are paired by a variable and its unit used in an adjacent block of
markup.


<div class="container-16">
  <div id="main" class="<?php print ns('grid-16', $neighbor_a, 3, $neighbor_b, 4); ?>">
    <?php print $main; ?>              [default]      |        |      |        |
  </div>                                              |- pair -|      |- pair -|
                                                      |        |      |        |
  <?php if ($neighbor_a): ?> <!-----------------------/        |      |        |
  <div id="neighbor-a" class="grid-3"> <!----------------------/      |        |
    <?php print $neighbor_a; ?>                                       |        |
  </div>                                                              |        |
  <?php endif; ?>                                                     |        |
                                                                      |        |
  <?php if ($neighbor_b)?> <!-----------------------------------------/        |
  <div id="neighbor-b" class="grid-4"> <!--------------------------------------/
    <?php print $neighbor_b; ?>
  </div>
  <?php endif; ?>
</div>

  |------------ .container-16 -----------------------|
  |---------------------------|---------|------------|
  |                           |         |            |
  |              #main.grid-9 <.grid-12 <.grid-16    |
  |                        -7 |      -4 |[default]   |
  |---------------------------|---------|------------|


Note that the *default class* (first parameter) is the largest possible of
"grid-16" since it's the immediate child of "container-16". The variables
$neighbor_a and $neighbor_b can be any variable that exists inside a template.
The number arguments immediately after the variable argument is it's default
grid value placed in their own markup.

The function only checks if the variable contains anything and subtracts the
next numeric parameter from the default class. With the above example, if
$neighbor_a contains anything it will subtract "3" from "grid-16". Same with
$neighbor_b which will subtract "4". If both variables exists, "grid-9" will
output to make space for the adjacent areas.

There are no limits to the number of parameters but it must always be done in
pairs. The first part of the pair being the variable and second, the number to
subtract from the default class. This pairing excludes the first parameter.

If needed, subtraction can take place when the variable *is empty* by using
an exclamation mark before it. This is useful for pull/push and prefix/suffix
classes in some contexts.


<div class="container-16">
  <div id="main" class="grid-10 <?php print ns('suffix-6', !$neighbor_c, 6); ?>">
    ...                                        [default]        |        |
  </div>                                                        |- pair -|
                                                                |        |
  <?php if ($neighbor_c): ?> <!---------------------------------/        |
  <div id="neighbor-c" class="grid-6"> <!--------------------------------/
    <?php print $neighbor_c; ?>
  </div>
  <?php endif; ?>
</div>

  |--------------- .container-16 --------------------|
  |------------------------------|-------------------|
  |                              |                   |
  |                #main.grid-10 >.suffix-6          |
  |                              |[padding fill]     |
  |------------------------------|-------------------|


The main points to remember are these:
  - The first parameter (default class) starts at the largest value. The latter
    parameters always work to subtract from the first.
  - The first parameter can be any type of class. As long as it's delimited by
    a hyphen "-" and ends in a numeric. (grid-[N], pull-[N], suffix-[N], etc.)
  - Starting from the second parameter, variables and numeric parameters must
    be set in pairs.
  - If the variable contains a value, subtraction will occur by default. Use an
    exclamation mark before the variable to subtract when it *does not* contain
    a value.

==============================================================================
Other notes:

- If you need to include a style above all others add this to your themes
  .info file.

  ; first include it normally with the stylesheets key.
  stylesheets[all][] = STYLENAME.css

  ; Now direct it to "float" or include it before other styles.
  settings[css_float][] = STYLENAME.css

  The base NineSixty theme does this for reset.css and text.css. Setting your
  own floats will ignore what was set from NineSixty so be sure to include them
  too.

- Problem with .clearfix and .clear-block in IE:

  The .clearfix (aka .clear-block) method of clearing divs does not always play
  well with 960.gs in IE6 (haven't tried IE7). The problem is twofold:

    1. If a div is assigned a container-X class, you must add the clearfix class
       after it, like so:

       <div class="container-12 clearfix">

    2. If a div is assigned a grid-X class, adding clearfix will break your
       layout. You must used an "inner" div instead, like so:

       <div class="grid-8"><div class="clearfix">My content</div></div>

  This problem has been seen in IE6. IE7 has not yet been tested. Please see
  this issue for more information: http://drupal.org/node/422240

==============================================================================

If you have any questions, suggestions, bug report or fixes, please post it in
the issue queue. http://drupal.org/project/issues/ninesixty

