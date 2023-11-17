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
void afficherEnTete( );
void afficherTableau();                 // A commenter
void genererBateau();                   // A faire
void nouveauTour();                     // A completer
void tirJoueur(int ligne, int colonne); // A complter
void verifBateauToucher();              // A faire

// Déclaration des types 
struct UneCoord
{
    int x;
    int y;
};

struct UnBateau
{
    UneCoord pos1;
    UneCoord pos2;
    UneCoord pos3;
    UneCoord pos4;
};

int main(void)
{
    afficherTableau();
    genererBateau();
    nouveauTour();
    cin >> tourJoueur;
}

void afficherTableau()
{
    for (int i = 0; i <= NB_CASES + 1; i++) // Parcours des différentes lignes
    {
        for (int j = 0; j <= NB_CASES + 1; j++) // parcours des différentes colonnes
        {
            if (i == 0 || i == NB_CASES + 1) // Afficher les index lettrés du haut et du bas de la grille, sans en afficher aucun dans les 4 coins
            {
                // Afficher les cases des coins vides
                if (j == 0 || j == NB_CASES + 1)
                {
                    cout << " ";
                }
                // Afficher les index lettrés
                else
                {
                    cout << char('A' + (j - 1)) << " ";
                }
            }
            // Afficher les indices numérotés 
            else 
            {
                // Afficher les chiffres
                if (j == 0 || j == NB_CASES + 1)
                {
                    cout << i;
                }
                // Remplir les cases non utilisées, qui contiennent un caractère vide en attendant que le jeu se déroule
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
    // Variables locales
    string action;

    // Traitements 
    // Saisie de la cible du tir par l'utilisisateur
    cout << "Votre tir : ";
    cin >> action;

    // Conversion du retour utilisateur pour pouvoir placer le tir sur la grille
    int ligne = (int)action[1] - 48;
    int colonne = int(action[0]) - 64;

    // Vérification de la validité du tir
    if (action.length() == 2 && colonne > 0 && colonne < 10 && ligne > 0 && ligne < 10)
    {
        tirJoueur(ligne, colonne);
    }
    else
    {
        if ( (ligne < 65 || ligne > 73) && (colonne > 0 && colonne < 10))
        {
            cout << "### Erreur en Y ###" << endl;
            nouveauTour();
        }
        else if ( colonne < 0 || colonne > 9 )
        {
            cout << "### Erreur en X ###" << endl;
            nouveauTour();
        }        
    }

    afficherTableau();
}

void tirJoueur(int ligne, int colonne)
{
    int bateauToucher;
    bateauToucher = verifBateauToucher(ligne, colonne);
    // 0 = non, 1=joueur 1, 2=joueur2

    if (bateauToucher == 0)
    {
        plateauJeu[ligne][colonne] = '.';
    }
    else if (bateauToucher == 1)
    {
        plateauJeu[ligne][colonne] = 'O';
    }
    else if (bateauToucher == 2)
    {
        plateauJeu[ligne][colonne] = 'X';
    }
}

int verifBateauToucher(int x, int y)
{

}