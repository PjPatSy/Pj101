#!/bin/bash

# Ce script ne fonctionne pas s'il y a des espaces dans les noms de
# fichier / de répertoires.

SOLVEUR=minisat
# Décommenter la ligne suivante pour utiliser votre propre solveur
# SOLVEUR=$(dirname $0)/sat

EDT=$(dirname $0)/edt

if [ -z "$1" ] ; then
    echo "Usage: resout-edt.sh toto/pb-titi.txt"
else
    PB=$1
    CNF=$(dirname $1)/$(basename $1 .txt).cnf
    MODELE=$(dirname $1)/$(basename $1 .txt).model
    HTML=$(dirname $1)/$(basename $1 .txt).html
    $EDT $PB -o $CNF
    $SOLVEUR $CNF $MODELE
    $EDT --solution $PB -i $MODELE -o $HTML
fi

