#!/bin/bash
#
# Prepare an installation.

rm -rf /var/www/test/ && drush make /var/www/stub.make /var/www/test  --prepare-install && chmod 777 -R /var/www/test/sites/default/ && cp /var/www/test/sites/default/default.settings.php /var/www/test/sites/default/settings.php
