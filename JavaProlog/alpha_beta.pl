/* -*- Mode:Prolog; coding:iso-8859-1; -*- */

:- set_prolog_flag(toplevel_print_options,[max_depth(0)]).
:- use_module(library(lists)).

/********************************************
*       IA Ultimate Tic Tac Toe             *
*   Briland Mathieu & Westermann Thomas     *
*********************************************/

% 1 = Symbole du joueur courant dans le plateau
% -1 = Symbole de l'adversaire courant dans le plateau
% 0 = Case libre

initialise([0,0,0,0,0,0,0,0,0]).

prochainJoueur(x,o).
prochainJoueur(o,x).

% On liste tous les déplacements possibles sur le plateau
deplace([0,B,C,D,E,F,G,H,I], 1, [1,B,C,D,E,F,G,H,I]).
deplace([A,0,C,D,E,F,G,H,I], 2, [A,1,C,D,E,F,G,H,I]).
deplace([A,B,0,D,E,F,G,H,I], 3, [A,B,1,D,E,F,G,H,I]).
deplace([A,B,C,0,E,F,G,H,I], 4, [A,B,C,1,E,F,G,H,I]).
deplace([A,B,C,D,0,F,G,H,I], 5, [A,B,C,D,1,F,G,H,I]).
deplace([A,B,C,D,E,0,G,H,I], 6, [A,B,C,D,E,1,G,H,I]).
deplace([A,B,C,D,E,F,0,H,I], 7, [A,B,C,D,E,F,1,H,I]).
deplace([A,B,C,D,E,F,G,0,I], 8, [A,B,C,D,E,F,G,1,I]).
deplace([A,B,C,D,E,F,G,H,0], 9, [A,B,C,D,E,F,G,H,1]).

% On liste tous les déplacements qui peuvent amener à gagner le plateau
deplacement_gagnant([0,1,1,_,_,_,_,_,_], 1):-!.
deplacement_gagnant([1,0,1,_,_,_,_,_,_], 2):-!.
deplacement_gagnant([1,1,0,_,_,_,_,_,_], 3):-!.
deplacement_gagnant([_,_,_,0,1,1,_,_,_], 4):-!.
deplacement_gagnant([_,_,_,1,0,1,_,_,_], 5):-!.
deplacement_gagnant([_,_,_,1,1,0,_,_,_], 6):-!.
deplacement_gagnant([_,_,_,_,_,_,0,1,1], 7):-!.
deplacement_gagnant([_,_,_,_,_,_,1,0,1], 8):-!.
deplacement_gagnant([_,_,_,_,_,_,1,1,0], 9):-!.
deplacement_gagnant([0,_,_,1,_,_,1,_,_], 1):-!.
deplacement_gagnant([1,_,_,0,_,_,1,_,_], 4):-!.
deplacement_gagnant([1,_,_,1,_,_,0,_,_], 7):-!.
deplacement_gagnant([_,0,_,_,1,_,_,1,_], 2):-!.
deplacement_gagnant([_,1,_,_,0,_,_,1,_], 5):-!.
deplacement_gagnant([_,1,_,_,1,_,_,0,_], 8):-!.
deplacement_gagnant([_,_,0,_,_,1,_,_,1], 3):-!.
deplacement_gagnant([_,_,1,_,_,0,_,_,1], 6):-!.
deplacement_gagnant([_,_,1,_,_,1,_,_,0], 9):-!.
deplacement_gagnant([0,_,_,_,1,_,_,_,1], 1):-!.
deplacement_gagnant([1,_,_,_,0,_,_,_,1], 5):-!.
deplacement_gagnant([1,_,_,_,1,_,_,_,0], 9):-!.
deplacement_gagnant([_,_,0,_,1,_,1,_,_], 3):-!.
deplacement_gagnant([_,_,1,_,0,_,1,_,_], 5):-!.
deplacement_gagnant([_,_,1,_,1,_,0,_,_], 7):-!.

% Prédicat d'appel pour algo minmax
minimax(Profondeur,Joueur,Plateau,Sol):-
        %initialise(Plateau),
        joue(Profondeur, Plateau, Joueur,Sol).

joue(_, Plateau, Joueur,_):-
        etatFinal(Plateau, Resultat),
        !,
        finPartie(Resultat, Joueur).

joue(Profondeur, Plateau, Joueur, Deplacement):-
        write('Joueur: '),
        write(Joueur),nl,        
        chercheCoup(Profondeur, Plateau, Joueur, Deplacement),
        deplace(Plateau, Deplacement, NewPlateau),
        remplace(NewPlateau, Joueur, [], NewPlateauAffiche),
        inverse(NewPlateauAffiche, NewPlateauAfficheInverse),
        write(NewPlateauAfficheInverse),nl,nl,
        !.
        %swap_plateau(NewPlateau, NextPlateau),
        %prochainJoueur(Joueur, J2),
        %joue(Profondeur, NextPlateau, J2).

% On cherche un coup valide avec AlphaBeta
chercheCoup(Profondeur, Plateau, x, Deplacement):-
        alphabeta(Profondeur, Plateau, -32767, 32767, Deplacement, Valeur),
        write('Deplacement|Valeur: '),
        write([Deplacement,Valeur]), nl.

chercheCoup(Profondeur, Plateau, o, Deplacement):-
        alphabeta(Profondeur, Plateau, -32767, 32767, Deplacement, Valeur),
        write('Deplacement|Valeur: '),
        write([Deplacement,Valeur]), nl.

% Notre AlphaBeta
alphabeta(_, Plateau, _, _, 0, -1000):-
        plateauPerdant(Plateau).

alphabeta(Profondeur, Plateau, Alpha, Beta, MeilleurCoup, Valeur):-
        Profondeur > 0,
        cherche_deplacement_gagnant(Plateau, Deplacement),
        Deplacement = [_|_], !,
        NouvelleProfondeur is Profondeur - 1,
        Alpha1 is -Beta,
        Beta1 is -Alpha,
        meilleurDeplacement(Deplacement, Plateau, NouvelleProfondeur, Alpha1, Beta1, 0, MeilleurCoup, Valeur).

alphabeta(_, Plateau, _, _, 0, Valeur):-
        % On évalue la différence une fois la profondeur arrivée à 0
        difference(Plateau, Valeur).

% On cherche un deplacement gagnant
cherche_deplacement_gagnant(Plateau, [Deplacement]):-
        % Si il y a un deplacement possiblement gagnant, on le selectionne
        deplace(Plateau, Deplacement, _),
        deplacement_gagnant(Plateau, Deplacement),
        !.
cherche_deplacement_gagnant(Plateau, [Deplacement]):-
        % Si l'autre joueur a un deplacement gagnant potentiel, on recommande le coup
        % qui le bloque
        deplace(Plateau, Deplacement, _),
        swap_plateau(Plateau, NewPlateau),
        deplacement_gagnant(NewPlateau, Deplacement),
        !.
cherche_deplacement_gagnant(Position, Deplacements):-
        % Sinon, on prend n'importe quel coup valide
        findall(Deplacement, deplace(Position, Deplacement, _), Deplacements).

meilleurDeplacement([], _, _, Alpha, _, Move, Move, Alpha).
meilleurDeplacement([Deplacement|Deplacements], Posn, Profondeur, Alpha, Beta, Deplacement0, Deplacement1, Valeur1):-
        deplace(Posn, Deplacement, NewPosn0), 
        !,
        swap_plateau(NewPosn0, NewPosn),
        alphabeta(Profondeur, NewPosn, Alpha, Beta, _, ValeurMin),
        Valeur is -ValeurMin,
        cutoff(Deplacement, Valeur, Profondeur, Alpha, Beta, Deplacements, Posn, Deplacement0, Deplacement1, Valeur1).

cutoff(_, Valeur, Pronfondeur, Alpha, Beta, Deplacements, Plateau, Deplacement0, Deplacement1, Valeur1):-
        Valeur =< Alpha, 
        !,
        meilleurDeplacement(Deplacements, Plateau, Pronfondeur, Alpha, Beta, Deplacement0, Deplacement1, Valeur1).

cutoff(Deplacement, Valeur, Profondeur, _, Beta, Deplacements, Plateau, _, Deplacement1, Valeur1):-
        Valeur < Beta, 
        !,
        meilleurDeplacement(Deplacements, Plateau, Profondeur, Valeur, Beta, Deplacement, Deplacement1, Valeur1).

cutoff(Move, Value, _, _, _, _, _, _, Move, Value).

difference(Plateau, -1000):-
        plateauPerdant(Plateau), 
        !.

difference(Plateau, Valeur):-
        lignes_gagnantes(Plateau,  2, 0, N1),
        lignes_gagnantes(Plateau, -2, 0, N2),
        Valeur is 2 * N1 - N2.

% Lignes qui peuvent être gagnées

lignes_gagnantes(Plateau, M, Acc, N):-
        lignes(Plateau, Lignes),
        lignes_gagnantes_1(Lignes, M, Acc, N).

lignes_gagnantes_1([], _, N, N).
lignes_gagnantes_1([Ligne|Lignes], M, Acc, N):-
        lignes_gagnantes(Ligne, M), 
        !,
        Acc1 is Acc + 1,
        lignes_gagnantes_1(Lignes, M, Acc1, N)
        ;
        lignes_gagnantes_1(Lignes, M, Acc, N).

lignes_gagnantes([A,B,C], M):-
        % Une ligne gagnante est une ligne qui a soit deux croix soit deux ronds
        M is A + B + C.

lignes([A,B,C,D,E,F,G,H,I],[[A,B,C],[D,E,F],[G,H,I],[A,D,G],[B,E,H],[C,F,I],[A,E,I],[C,E,G]]).

etatFinal(Plateau, perdu):-  plateauPerdant(Plateau), !.
etatFinal(Plateau, egalite):- \+(deplace(Plateau, _, _)).

finPartie(perdu, x):- write('x perde'), nl, nl.
finPartie(perdu, o):- write('o perde'), nl, nl.
finPartie(egalite, _):- write('Egalite'), nl, nl.

% Si un plateau se retrouve dans une de ces positions alors le joueur courant a perdu
plateauPerdant([-1,-1,-1, _, _, _, _, _, _]):-!.
plateauPerdant([ _, _, _,-1,-1,-1, _, _, _]):-!.
plateauPerdant([ _, _, _, _, _, _,-1,-1,-1]):-!.
plateauPerdant([-1, _, _,-1, _, _,-1, _, _]):-!.
plateauPerdant([ _,-1, _, _,-1, _, _,-1, _]):-!.
plateauPerdant([ _, _,-1, _, _,-1, _, _,-1]):-!.
plateauPerdant([-1, _, _, _,-1, _, _, _,-1]):-!.
plateauPerdant([ _, _,-1, _,-1, _,-1, _, _]):-!.

% Permet de renverser le plateau en mettant les 1 a -1 pour l'autre joueur
% Et ainsi de savoir si il se trouve dans un plateauPerdant
swap_plateau([A0,B0,C0,D0,E0,F0,G0,H0,I0], [A,B,C,D,E,F,G,H,I]):-
  A is -A0, B is -B0, C is -C0, 
  D is -D0, E is -E0, F is -F0, 
  G is -G0, H is -H0, I is -I0.


% Remplace les symboles du plateau avec ceux du joueur
remplace([],_,Acc,Acc).
remplace([0|Tail],Joueur,Acc,L):-
        remplace(Tail,Joueur,[0|Acc],L).
remplace([1|T],Joueur,Acc,L):-
        remplace(T,Joueur,[Joueur|Acc],L). 
remplace([-1|T],x,Acc,L):-
        remplace(T,x,[o|Acc],L).
remplace([-1|T],o,Acc,L):-
        remplace(T,o,[x|Acc],L).

% Inverse une liste
inverse(L,S):-
        inverse(L,[],S).
inverse([],Acc,Acc).
inverse([X|L],Acc,S):-
        inverse(L,[X|Acc],S).


% ULTIMATE


