; $Id:$
api = "2"
core = "7.x"

; Contrib projects 

projects[admin_menu][subdir] = "contrib"
projects[admin_menu][version] = "3.x-dev"

projects[ctools][subdir] = "contrib"
projects[ctools][version] = "1.x-dev"

projects[cck][subdir] = "contrib"
projects[cck][version] = "2.x-dev"
; Make Node Reference Relationships Work - http://drupal.org/node/962694
projects[cck][patch][] = "http://drupal.org/files/issues/node_ref_views_3_d7.patch"

projects[date][subdir] = "contrib"
projects[date][version] = "1.x-dev"


projects[entity][subdir] = "contrib"
projects[entity][version] = "1.x-dev"

projects[features][subdir] = "contrib"
projects[features][version] = "1.0-alpha3"

projects[flag][subdir] = "contrib"
projects[flag][version] = "2.x-dev"

projects[less][subdir] = "contrib"
projects[less][version] = "2.x-dev"

projects[message][type] = "module"
projects[message][subdir] = "contrib"
projects[message][download][type] = "git"
projects[message][download][url] = "git://github.com/amitaibu/message.git"
projects[message][download][branch] = "DRUPAL-7--1"

projects[panels][subdir] = "contrib"
projects[panels][version] = "3.x-dev"

projects[og][type] = "module"
projects[og][subdir] = "contrib"
projects[og][download][type] = "git"
projects[og][download][url] = "git://github.com/amitaibu/og.git"
projects[og][download][branch] = "master"

projects[views][subdir] = "contrib"
projects[views][version] = "3.x-dev"

; Features
projects[opengizra_features][type] = "module"
projects[opengizra_features][subdir] = "contrib"
projects[opengizra_features][download][type] = "git"
projects[opengizra_features][download][url] = "git@gizra-labs.com:/opengizra.git"
projects[opengizra_features][download][branch] = "features"

; Development modules
projects[coder][subdir] = "developer"
projects[coder][version] = "1.x-dev"

projects[devel][subdir] = "developer"
projects[devel][version] = "1.x-dev"

; Themes
projects[zen_themes][type] = "theme"
projects[zen_themes][download][type] = "get"
projects[zen_themes][download][url] = "https://github.com/downloads/amitaibu/zen_ninesixty/d7-zen-960-base-themes.tar.gz"

projects[zen_ninesixty][type] = "theme"
projects[zen_ninesixty][download][type] = "git"
projects[zen_ninesixty][download][url] = "git@github.com:amitaibu/zen_ninesixty.git"
projects[zen_ninesixty][download][branch] = "7.x-1.x-dev"

; Instead of getting all the themes from Druapl, we get it from github download
; area.
; projects[ninesixty][version] = "1.x-dev"
; http://drupal.org/node/960968#comment-3720030
; projects[ninesixty][patch][] = "http://drupal.org/files/issues/960968-ninesixty-d7-bugfixes.patch"

; projects[zen][version] = "3.x-dev"