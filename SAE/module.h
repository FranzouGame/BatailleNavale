#ifndef MODULE_H
#define MODULE_H
#include <iostream>
using namespace std;

const int TAILLE_TAB = 9;                     // Taille de la grille
const unsigned short int NB_CASES_BATEAU = 4; // Longueur d'un bateau

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
    string nom;                    // Nom du joueur
    EtatsPossibles etat = enJeu;   // Etat du joueur dans la partie
    unsigned short int nbTirs = 0; // Nombre de tirs du joueur
};

struct UneCoordonnee
{
    int x = 0; // Abscisse de la coordonnée
    int y = 0; // Ordonnée de la coordonnée
};

struct UnBateau
{
    UneCoordonnee pos[NB_CASES_BATEAU]; // Un bateau aura NB_CASES_BATEAU coordonnées
};

void afficherEnTete(UnJoueur player1, UnJoueur player2, UnBateau boat[], const unsigned short int NB_BATEAUX, const unsigned short int NB_CASES, int turnPlayer);
// But : Afficher l'en-tête lors d'un tir

void afficherTableau(char grille[][TAILLE_TAB], int TAILLE_TAB);
// But : Afficher le tableau de jeu

void afficherBateau(UnBateau boat[], const unsigned short int NB_BATEAUX, const unsigned short int NB_CASES);
// But : Afficher les coordonnées des bateaux à l'écran

void genererBateau(UnBateau bateau[], int indexBateau, const unsigned short int NB_BATEAUX, const unsigned short int NB_CASES); // Diago a faire, peut être changer la génération des 2 autres pour opti
// But : Générer les bateaux nécessaires pour la partie

void verifBateauToucher(UnBateau Bat[], char grille[][TAILLE_TAB], int ligne, int colonne, const unsigned short int NB_BATEAUX, const unsigned short int NB_CASES);
// But : Vérifier si le tir du joueur touche un bateau ou s'il tire dans l'eau

#endif // MODULE_H
