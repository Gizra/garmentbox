#!/bin/bash
#
# Prepare an installation.

sudo rm -rf /var/www/test/ && drush make /var/www/stub.make /var/www/test  --prepare-install --working-copy && chmod 777 -R /var/www/test/sites/default/ && cp /var/www/test/sites/default/default.settings.php /var/www/test/sites/default/settings.php

# cd /var/www/test && drush si --db-url=mysql://root@localhost/opengizra --profile opengizra -y
