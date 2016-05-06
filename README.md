# patate

Pour compiler le C :

make

Pour executer le C :
./joueurTicTacToe [adresse] [port] [nomJoueur] [Port Java]

./serveurTicTacToe [port]


Pour compiler le java : 

javac -classpath /usr/local/sicstus4.3.2/lib/sicstus-4.3.2/bin/jasper.jar:/usr/local/sicstus4.3.2/lib/sicstus-4.3.2/bin/prologbeans.jar *.java

pour executer le java : 

java -classpath /usr/local/sicstus4.3.2/lib/sicstus-4.3.2/bin/jasper.jar:/usr/local/sicstus4.3.2/lib/sicstus-4.3.2/bin/prologbeans.jar:. Main [numero de port]

Pour compiler le java sur les ordis de la fac :

export LD_LIBRARY_PATH=/applis/sicstus-4.3.2/lib/ 

javac -classpath /applis/sicstus-4.3.2/lib/sicstus-4.3.2/bin/jasper.jar:/applis/sicstus-4.3.2/lib/sicstus-4.3.2/bin/prologbeans.jar *.java

Pour executer le java sur les ordis de la fac :

java -classpath /applis/sicstus-4.3.2/lib/sicstus-4.3.2/bin/jasper.jar:/applis/sicstus-4.3.2/lib/sicstus-4.3.2/bin/prologbeans.jar:. Main [numero de port]
