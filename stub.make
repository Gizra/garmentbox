; rm -rf /Applications/MAMP/htdocs/test && drush make stub.make /Applications/MAMP/htdocs/test/  --prepare-install --working-copy

api = 2

core = "7.x"
projects[] = drupal

; TODO: Make stub make, call the profile.

; Contrib projects 
;=================

projects[backup_migrate][subdir] = "contrib"
projects[backup_migrate][download][type] = "git"
projects[backup_migrate][download][branch] = "7.x-2.x"

projects[calendar][subdir] = "contrib"
projects[calendar][download][type] = "git"
projects[calendar][download][branch] = "7.x-1.x"

projects[chained_selects][type] = "module"
projects[chained_selects][subdir] = "contrib"
projects[chained_selects][download][type] = "git"
projects[chained_selects][download][url] = "http://git.drupal.org/project/chained_selects.git"
projects[chained_selects][download][branch] = "7.x-1.x"
  
projects[ctools][subdir] = "contrib"
projects[ctools][download][type] = "git"
projects[ctools][download][branch] = "7.x-1.x"

projects[date][subdir] = "contrib"
projects[date][download][type] = "git"
projects[date][download][branch] = "7.x-1.x"

projects[entity][subdir] = "contrib"
projects[entity][download][type] = "git"
projects[entity][download][branch] = "7.x-1.x"

projects[features][subdir] = "contrib"
projects[features][download][type] = "git"
projects[features][download][branch] = "7.x-1.x"

projects[field_collection][subdir] = "contrib"
projects[field_collection][download][type] = "git"
projects[field_collection][download][branch] = "7.x-1.x"

projects[field_slideshow][subdir] = "contrib"
projects[field_slideshow][download][type] = "git"
projects[field_slideshow][download][branch] = "7.x-1.x"

projects[flag][subdir] = "contrib"
projects[flag][download][type] = "git"
; Flag 7.x-2.x is master
projects[flag][download][branch] = "master"

projects[fullcalendar][subdir] = "contrib"
projects[fullcalendar][download][type] = "git"
projects[fullcalendar][download][branch] = "7.x-2.x"

projects[hs_js][type] = "module"
projects[hs_js][subdir] = "contrib"
projects[hs_js][download][type] = "git"
projects[hs_js][download][url] = "http://git.drupal.org/sandbox/amitaibu/1186934.git"
projects[hs_js][download][branch] = "7.x-1.x"

projects[jcarousel][subdir] = "contrib"
projects[jcarousel][download][type] = "git"
projects[jcarousel][download][branch] = "7.x-2.x"

projects[jscrollpane][type] = "module"
projects[jscrollpane][subdir] = "contrib"
projects[jscrollpane][download][type] = "git"
projects[jscrollpane][download][url] = "https://github.com/amitaibu/jscrollpane.git"
projects[jscrollpane][download][branch] = "7.x-1.x"

projects[less][subdir] = "contrib"
projects[less][download][type] = "git"
projects[less][download][branch] = "7.x-2.x"

projects[libraries][subdir] = "contrib"
projects[libraries][download][type] = "git"
; Libraries calls 7.x-2.x "master".
projects[libraries][download][branch] = "master"

projects[message][subdir] = "contrib"
projects[message][download][type] = "git"
projects[message][download][branch] = "7.x-1.x"

projects[og][subdir] = "contrib"
projects[og][download][type] = "git"
projects[og][download][branch] = "7.x-1.x"

projects[og_membership_expire][type] = "module"
projects[og_membership_expire][subdir] = "contrib"
projects[og_membership_expire][download][type] = "git"
projects[og_membership_expire][download][url] = "http://git.drupal.org/sandbox/amitaibu/1106596.git"
projects[og_membership_expire][download][branch] = "7.x-1.x"

projects[og_subgroups][subdir] = "contrib"
projects[og_subgroups][download][type] = "git"
projects[og_subgroups][download][branch] = "7.x-1.x"

projects[panels][subdir] = "contrib"
projects[panels][download][type] = "git"
projects[panels][download][branch] = "7.x-3.x"

projects[strongarm][subdir] = "contrib"
projects[strongarm][download][type] = "git"
projects[strongarm][download][branch] = "7.x-2.x"

projects[subform][subdir] = "contrib"
projects[subform][download][type] = "git"
projects[subform][download][branch] = "7.x-1.x"

projects[references][subdir] = "contrib"
projects[references][download][type] = "git"
projects[references][download][branch] = "7.x-2.x"

projects[user_modal][subdir] = "contrib"
projects[user_modal][download][type] = "git"
projects[user_modal][download][branch] = "7.x-1.x"

projects[views][subdir] = "contrib"
projects[views][download][type] = "git"
projects[views][download][branch] = "7.x-3.x"

; Features
;=========
projects[opengizra_features][type] = "module"
projects[opengizra_features][subdir] = "features"
projects[opengizra_features][download][type] = "git"
projects[opengizra_features][download][url] = "git@gizra-labs.com:/opengizra.git"
projects[opengizra_features][download][branch] = "features"

; Development modules
;====================

projects[devel][subdir] = "developer"
projects[devel][download][type] = "git"
projects[devel][download][branch] = "7.x-1.x"

; Themes
;=======
projects[ninesixty][version] = "1.x-dev"
projects[ninesixty][download][type] = "git"
projects[ninesixty][download][branch] = "7.x-1.x"

projects[ninesixty_sub][type] = "theme"
projects[ninesixty_sub][download][type] = "git"
; TODO: Change to public git.
projects[ninesixty_sub][download][url] = "git@gizra-labs.com:/opengizra.git"
projects[ninesixty_sub][download][branch] = "ninesixty_sub"

; Libraries
;==========

libraries[expander][download][type] = "file"
libraries[expander][download][url] = "http://plugins.learningjquery.com/expander/jquery.expander.js"

libraries[fullcalendar][download][type] = "file"
libraries[fullcalendar][download][url] = "http://arshaw.com/fullcalendar/downloads/fullcalendar-1.5.1.zip"

libraries[jquery_chained][download][type] = "file"
libraries[jquery_chained][download][url] = "http://www.appelsiini.net/download/jquery.chained.js"


; Patches
;========

; TODO: Add this in git.
; Flag Ctools integration
; http://drupal.org/node/332956#comment-4327834
; http://drupal.org/files/issues/ctools-plugin-flag-77-d7.patch
http://drupal.org/files/issues/ctools-plugin-flag-77-d7.patch