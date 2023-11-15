/*
programme : batailleNavale
But : Jouer à la bataille navale
*/

#include "game-tools.h"
#include <iostream>
#include <tuple>
#include <string>
using namespace std;

const unsigned short int NB_CASES = 9; // Taille du tableau horizontalement et verticalement
char plateauJeu[NB_CASES][NB_CASES];   // Tableau contenant le plateau de jeu

int tourJoueur = 0;
tuple<int, int> bateauJoueur[2][4];

// Déclaration des sous-programmes
void afficherTableau();                 // A commenter
void genererBateau();                   // A faire
void nouveauTour();                     // A completer
void tirJoueur(int ligne, int colonne); // A complter
void verifBateauToucher();              // A faire

int main(void)
{
    genererBateau();
    nouveauTour();
    cin >> tourJoueur;
}

void afficherTableau()
{
    for (int i = 0; i <= NB_CASES + 1; i++) // LIGNES
    {
        for (int j = 0; j <= NB_CASES + 1; j++) // COLLONES
        {
            if (i == 0 || i == NB_CASES + 1) // Afficher lettres haut et bas
            {
                if (j == 0 || j == NB_CASES + 1)
                {
                    cout << " ";
                }
                else
                {
                    cout << char('A' + (j - 1)) << " ";
                }
            }
            else // Afficher les chiffres gauches et droite
            {
                if (j == 0 || j == NB_CASES + 1)
                {
                    cout << i;
                }
                else
                {
                    cout << plateauJeu[i][j] << " ";
                }
            }
        }
        cout << endl;
    }
}

void genererBateau()
{
}

void nouveauTour()
{
    string action;
    cout << "Votre tir : ";
    cin >> action;
    int ligne = (int)action[1] - 48;
    int colonne = int(action[0]) - 64;

    if (action.length() == 2 && colonne > 0 && colonne < 10 && ligne > 0 && ligne < 10)
    {
        tirJoueur(ligne, colonne);
    }
    else
    {
        cout << "tir par valide" << endl;
        nouveauTour();
        return;
        // A faire les vérification derreur
    }

    afficherTableau();
}

void tirJoueur(int ligne, int colonne)
{
    int bateauToucher = 0;
    // 0 = non, 1=joueur 1, 2=joueur2

    if (bateauToucher == 0)
    {
        plateauJeu[ligne][colonne] = '.';
    }
    else if (bateauToucher == 1)
    {
        plateauJeu[ligne][colonne] = 'O';
    }
    else if (bateauToucher == 1)
    {
        plateauJeu[ligne][colonne] = 'X';
    }
}

void verifBateauToucher()
{
}