/*
programme : batailleNavale
But : Jouer à la bataille navale
*/

#include "game-tools.h"
#include <iostream>
using namespace std;

const unsigned short int NB_CASES = 9; // Taille du tableau horizontalement et verticalement
char plateauJeu[NB_CASES][NB_CASES];   // Tableau contenant le plateau de jeu

// Déclaration des sous-programmes
/* void generePlateau(char tab[][], unsigned short int lgTab); */
void afficherTableau();
// But : Générer un plateau de jeu à 2 dimensions tab de taille lgTab

int main(void)
{
    afficherTableau();
}

void afficherTableau()
{
    for (int i = 0; i <= NB_CASES + 1; i++) // LIGNES
    {
        for (int j = 0; j <= NB_CASES + 1; j++) // COLLONES
        {
            if (i == 0 || i == NB_CASES + 1)
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
            else
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