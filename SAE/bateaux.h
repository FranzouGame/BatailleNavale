#ifndef BATEAUX_H
#define BATEAUX_H
#include <iostream>
using namespace std;

const unsigned short int NB_CASES_BATEAU = 4; // Longueur d'un bateau

struct UneCoordonnee
{
    int x = 0; // Abscisse de la coordonnée
    int y = 0; // Ordonnée de la coordonnée
};

struct UnBateau
{
    UneCoordonnee pos[NB_CASES_BATEAU]; // Un bateau aura NB_CASES_BATEAU coordonnées
};

void genererBateau(UnBateau bateau[], int indexBateau, const unsigned short int NB_BATEAUX, const unsigned short int NB_CASES); // Diago a faire, peut être changer la génération des 2 autres pour opti
// But : Générer les bateaux nécessaires pour la partie

void verifBateauToucher(int ligne, int colonne, const unsigned short int NB_BATEAUX, const unsigned short int NB_CASES);
// But : Vérifier si le tir du joueur touche un bateau ou s'il tire dans l'eau

#endif
