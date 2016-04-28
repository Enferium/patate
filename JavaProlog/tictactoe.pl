/* -*- Mode:Prolog; coding:iso-8859-1; -*- */
:- set_prolog_flag(toplevel_print_options,[max_depth(0)]).

% On initialise un plateau vide
plateau([v,v,v,v,v,v,v,v,v]).

prochainJoueur(x,o).
prochainJoueur(o,x).

% On gagne un plateau pour les configurations suivantes
gagne([W,W,W,_,_,_,_,_,_],W). % Première ligne
gagne([_,_,_,W,W,W,_,_,_],W). % Deuxième ligne
gagne([_,_,_,_,_,_,W,W,W],W). % Troisième ligne
gagne([W,_,_,W,_,_,W,_,_],W). % Première colonne
gagne([_,W,_,_,W,_,_,W,_],W). % Deuxième colonne
gagne([_,_,W,_,_,W,_,_,W],W). % Troisième colonne
gagne([W,_,_,_,W,_,_,_,W],W). % Première diagonale
gagne([_,_,W,_,W,_,W,_,_],W). % Deuxième diagonale

% Liste de toutes les positions possibles pour lequel on peut gagner un plateau
deplacementGagnant([v,W,W,_,_,_,_,_,_],W,0).
deplacementGagnant([W,v,W,_,_,_,_,_,_],W,1).
deplacementGagnant([W,W,v,_,_,_,_,_,_],W,2).
deplacementGagnant([_,_,_,v,W,W,_,_,_],W,3).
deplacementGagnant([_,_,_,W,v,W,_,_,_],W,4).
deplacementGagnant([_,_,_,W,W,v,_,_,_],W,5).
deplacementGagnant([_,_,_,_,_,_,v,W,W],W,6).
deplacementGagnant([_,_,_,_,_,_,W,v,W],W,7).
deplacementGagnant([_,_,_,_,_,_,W,W,v],W,8).
deplacementGagnant([v,_,_,W,_,_,W,_,_],W,0).
deplacementGagnant([W,_,_,v,_,_,W,_,_],W,3).
deplacementGagnant([W,_,_,W,_,_,v,_,_],W,6).
deplacementGagnant([v,_,_,_,W,_,_,W,_],W,0).
deplacementGagnant([_,W,_,_,v,_,_,W,_],W,4).
deplacementGagnant([_,W,_,_,W,_,_,v,_],W,7).
deplacementGagnant([_,_,v,_,_,W,_,_,W],W,2).
deplacementGagnant([_,_,W,_,_,v,_,_,W],W,5).
deplacementGagnant([_,_,W,_,_,W,_,_,v],W,8).
deplacementGagnant([v,_,_,_,W,_,_,_,W],W,0).
deplacementGagnant([W,_,_,_,v,_,_,_,W],W,4).
deplacementGagnant([W,_,_,_,W,_,_,_,v],W,8).
deplacementGagnant([_,_,v,_,W,_,W,_,_],W,2).
deplacementGagnant([_,_,W,_,v,_,W,_,_],W,4).
deplacementGagnant([_,_,W,_,W,_,v,_,_],W,6).

% Prédicat général de ceux du dessus
deplaceGagnant(Plateau, Joueur, Position):-
        deplacementGagnant(Plateau, Joueur, Position).

% On liste chaque déplacement possible tout en évaluant le plateau
deplace([v,B,C,D,E,F,G,H,I],Joueur,[Joueur,B,C,D,E,F,G,H,I]).
deplace([A,v,C,D,E,F,G,H,I],Joueur,[A,Joueur,C,D,E,F,G,H,I]).
deplace([A,B,v,D,E,F,G,H,I],Joueur,[A,B,Joueur,D,E,F,G,H,I]).
deplace([A,B,C,v,E,F,G,H,I],Joueur,[A,B,C,Joueur,E,F,G,H,I]).
deplace([A,B,C,D,v,F,G,H,I],Joueur,[A,B,C,D,Joueur,F,G,H,I]).
deplace([A,B,C,D,E,v,G,H,I],Joueur,[A,B,C,D,E,Joueur,G,H,I]).
deplace([A,B,C,D,E,F,v,H,I],Joueur,[A,B,C,D,E,F,Joueur,H,I]).
deplace([A,B,C,D,E,F,G,v,I],Joueur,[A,B,C,D,E,F,G,Joueur,I]).
deplace([A,B,C,D,E,F,G,H,v],Joueur,[A,B,C,D,E,F,G,H,Joueur]).

% On cherche à évaluer le plateau
evaluationPlateau(Plateau,Joueur,Cout):-
        evaluePosition(Plateau, Joueur, Cout1),
        prochainJoueur(Joueur, J2),
        evaluePosition(Plateau, J2, Cout2),
        difference(Cout1,Cout2,Joueur, Cout).

% Retourne le cout
difference(Cout1,Cout2,x,Cout):-
        Cout is Cout1 - Cout2.
difference(Cout1,Cout2,o,Cout):-
        Cout is Cout2 - Cout1.

% Remplace les symboles du plateau avec ceux du joueur
positionne([],_,Acc,Acc).
positionne([v|T],Joueur,Acc,L):-
        positionne(T,Joueur,[Joueur|Acc],L).
positionne([o|T],Joueur,Acc,L):-
        positionne(T,Joueur,[o|Acc],L).
positionne([x|T],Joueur,Acc,L):-
        positionne(T,Joueur,[x|Acc],L). 

inverse(L,S):-
        inverse(L,[],S).
inverse([],Acc,Acc).
inverse([X|L],Acc,S):-
        inverse(L,[X|Acc],S).

% Retourne le nombre de deplacement possiblement gagnant pour le joueur
evaluePosition(Plateau,Joueur,Cout):-
        positionne(Plateau,Joueur,[],NewPlateau),
        inverse(NewPlateau, [], NewPlateauInverse),
        findall(Cout, gagne(NewPlateauInverse,Joueur), Res),
        length(Res,Cout).

% Etat final
etatFinal(Plateau,Joueur,_,_) :-
        gagne(Plateau,Joueur).

isGagnant(Plateau,Joueur,_,_):-
        etatFinal(Plateau,Joueur,_,_).

isGagnant(Plateau,Joueur,Cout,LR):-
        prochainJoueur(Joueur, J2),
        profondeur(Plateau,J2,Cout,LR).

profondeur([],_,_,_):-!,fail.

profondeur(Plateau,Joueur,_,_) :-
        etatFinal(Plateau,Joueur,_,_).

profondeur(Plateau,Joueur,_,Sol):-
        deplace(Plateau,Joueur,NewPlateau),
        evaluationPlateau(NewPlateau, Joueur, NewCout),
        isGagnant(NewPlateau,Joueur,NewCout,Sol).

parcoursProfondeur(Joueur,L):-
        plateau(Plateau),
        evaluationPlateau(Plateau,Joueur,Cout),
        profondeur(Plateau,Joueur,Cout,Los),
        inverse(Los,[],L).