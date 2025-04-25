#!/bin/bash

# couleurs
YELLOW="\e[33m"
GREEN="\e[32m"
BLUE="\e[34m"
RED="\e[31m"
NC="\e[0m"

# Fichier de log
LOGFILE=".philo_tests.log"

# pour etre sur que le fichier soit vide
echo "" > $LOGFILE

# Vérifie les arguments passés au script
QUIET="false"
if [ "$1" == "--quiet" ]; then
	QUIET=true
fi

log() {
	if [ "$QUIET" = "true" ]; then
		echo -e "$1" >> $LOGFILE
	else
		echo -e "$1" | tee -a $LOGFILE
	fi
}

log "\n=============== my philo tester ===============\n"
log "$GREEN Should be good $NC"

# Tableau d'entrées à tester normalement bonnes
inputs=(
	"1 2 3 4 5"
)

for args in "${inputs[@]}"
do
	if [ "$QUIET" = "false" ]; then
		echo "----- Test: ./philo $args -----" | tee -a $LOGFILE
		./philo $args | tee -a $LOGFILE 2>&1
		echo "" | tee -a $LOGFILE
	else
		echo "----- Test: ./philo $args -----" >> $LOGFILE
		./philo $args >> $LOGFILE 2>&1
		echo "" >> $LOGFILE
	fi
done

log "$RED Should occured errors $NC"
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
	if [ "$QUIET" = "false" ]; then
		echo "----- Test: ./philo $args -----" | tee -a $LOGFILE
		./philo $args | tee -a $LOGFILE 2>&1
		echo "" | tee -a $LOGFILE
	else
		echo "----- Test: ./philo $args -----" >> $LOGFILE
		./philo $args >> $LOGFILE 2>&1
		echo "" >> $LOGFILE
	fi
done

echo "($LOGFILE created)"