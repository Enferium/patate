#!/bin/bash

# /applis/sicstus-4.3.2/lib/sicstus-4.3.2/bin/jasper.jar:/applis/sicstus-4.3.2/lib/sicstus-4.3.2/bin/prologbeans.jar:.
# /usr/local/sicstus4.3.2/lib/sicstus-4.3.2/bin/jasper.jar:/usr/local/sicstus4.3.2/lib/sicstus-4.3.2/bin/prologbeans.jar:.

echo "Lancement java"
cd JavaProlog
java -classpath /applis/sicstus-4.3.2/lib/sicstus-4.3.2/bin/jasper.jar:/applis/sicstus-4.3.2/lib/sicstus-4.3.2/bin/prologbeans.jar:. Main $4&
sleep 1
echo "Lancement Joueur"
cd ..
./ServeurC/joueurTicTacToe $1 $2 $3 $4
