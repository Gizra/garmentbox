PROFILE=/Applications/MAMP/htdocs/opengizra
NEWDIR=/Applications/MAMP/htdocs/opengizra_build
PROFILENAME=opengizra
DB=opengizra_build

cd $PROFILE
bash scripts/build.sh -y $NEWDIR

cd $NEWDIR
drush sql-drop -y
drush si -y $PROFILENAME --account-pass=admin --db-url=mysql://root:root@localhost/$DB
