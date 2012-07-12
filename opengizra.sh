NEWDIR=/Applications/MAMP/htdocs/opengizra_build
PROFILE=opengizra
DB=opengizra_build
URI=http://local:8888/opengizra_build

bash scripts/build.sh -y $NEWDIR

cd $NEWDIR
drush sql-drop -y
drush si -y $PROFILE --account-pass=admin --db-url=mysql://root:root@localhost/$DB --uri=$URI
