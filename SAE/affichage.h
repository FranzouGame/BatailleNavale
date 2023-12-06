#ifndef AFFICHAGE_H
#define AFFICHAGE_H
#include <iostream>
#include "bateaux.h"
using namespace std;

// Type énuméré servant pour gérer l'état de la partie
enum EtatsPossibles
{
    enJeu,
    gagne,
    abandonne
};

// Déclaration des types

struct UnJoueur
{
    string nom;                  // Nom du joueur
    EtatsPossibles etat = enJeu; // Etat du joueur dans la partie
};

int tourJoueur = 0; // Variable stockant à qui est le tour
const int TAILLE_TAB = 9; // Taille de la grille

void afficherEnTete(UnJoueur player1, UnJoueur player2, UnBateau boat[] , const unsigned short int NB_BATEAUX, const unsigned short int NB_CASES);  
// But : Afficher l'en-tête lors d'un tir

void afficherTableau(char grille[][TAILLE_TAB], int TAILLE_TAB);
// But : Afficher le tableau de jeu

void afficherBateau(UnBateau boat[] , const unsigned short int NB_BATEAUX, const unsigned short int NB_CASES);
// But : Afficher les coordonnées des bateaux à l'écran

#endif
