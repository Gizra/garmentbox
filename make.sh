#!/bin/bash
#
# Prepare an installation.

sudo rm -rf /Applications/MAMP/htdocs/plm && drush make /Applications/MAMP/htdocs/opengizra/stub.make /Applications/MAMP/htdocs/plm  --prepare-install --working-copy && chmod 777 -R /var/www/test/sites/default/ && cp /var/www/test/sites/default/default.settings.php /var/www/test/sites/default/settings.php && cd /var/www/test && drush si --db-url=mysql://root@localhost/opengizra --profile opengizra -y

# cd /var/www/test && drush si --db-url=mysql://root@localhost/opengizra --profile opengizra -y
