#!/bin/bash


echo "lancement java"
cd JavaProlog
java -classpath /usr/local/sicstus4.3.2/lib/sicstus-4.3.2/bin/jasper.jar:/usr/local/sicstus4.3.2/lib/sicstus-4.3.2/bin/prologbeans.jar:. Main 5555&
sleep 1
echo "lancement Joueur "
cd ..
./ServeurC/joueurTicTacToe 127.0.0.1 5000 mathieu 5555
