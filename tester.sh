#!/bin/bash

make re

YELLOW="\e[33m"
GREEN="\e[32m"
BLUE="\e[34m"
RED="\e[31m"
NC="\e[0m"

# Fichier de log
LOGFILE=".philo_tests.log"
echo "" > $LOGFILE
# Vérifie les arguments passés au script
if [[ "$1" == "--quiet" ]]; then
	LOG= >> $LOGFILE
else
	LOG= | tee -a $LOGFILE
fi


echo -e "\n=============== my philo tester ===============\n" $LOG
echo -e "$GREEN Should be good $NC" $LOG
# Tableau d'entrées à tester normalement bonnes
inputs=(
	"1 2 3 4 5"
)

for args in "${inputs[@]}"
do
	echo "----- Test: ./philo $args -----" $LOG
	./philo $args $LOG 2>&1
	echo "" $LOG
done

echo -e "$RED Should occured errors $NC" $LOG
# Tableau d'entrées à tester normalement mauvaises
inputs=(
	"1 2 3 4 2147483647"
	"1 2 3 4 5 6"
	"a b c d e"
	"0 2 3 4 5"
	"-1 2 3 4 5"
	"-2147483648 2 3 4 5"
	"  "
	"0 0 0 0 0"
	"0 0 0 0"
	"5 -6 4 3 9"
)

for args in "${inputs[@]}"
do
	echo "----- Test: ./philo $args -----" $LOG
	./philo $args $LOG 2>&1
	echo "" $LOG
done

echo "($LOGFILE created)"