/*
programme : batailleNavale
But : Jouer à la bataille navale
*/

#include "game-tools.h"
#include <iostream>
using namespace std;

// Déclaration des sous-programmes
/* void generePlateau(char tab[][], unsigned short int lgTab); */
// But : Générer un plateau de jeu à 2 dimensions tab de taille lgTab

int main(void)
{
    // VARIABLES
    const unsigned short int NB_CASES = 11;                                                 // Taille du tableau horizontalement et verticalement
    char plateauJeu[NB_CASES][NB_CASES];                                                    // Tableau contenant le plateau de jeu
    int ligne;                                                                              // Numéro de la ligne courante
    int colonne;                                                                            // Numéro de la colonne courante
    const unsigned short int INDICE_CONVERSION_CHAR = 48;                                   // Indice pour convertir un int en char grace a la table ASCII                                                                      // Indice à mettre dans les index de colonnes
    const char tabChar[NB_CASES] = {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', ' '}; // Tableau de caractères index

    // Générer le plateau
    for (ligne = 0; ligne < NB_CASES; ligne++)
    {
        for (colonne = 0; colonne < NB_CASES; colonne++)
        {
            // Remplir les index horizontaux
            if ((ligne == 0 || ligne == 10) && (colonne != 0 || colonne != 10))
            {
                plateauJeu[ligne][colonne] = tabChar[colonne];
            }
            // Remplir les index verticaux
            else if ((ligne != 0 || ligne != 10) && (colonne == 0 || colonne == 10))
            {
                plateauJeu[ligne][colonne] = char(ligne + INDICE_CONVERSION_CHAR);
            }
            // Remplir de cases vides
            else
            {
                plateauJeu[ligne][colonne] = ' ';
            }
        }
    }

    // Affichage du plateau
    for (ligne = 0; ligne < NB_CASES; ligne++)
    {
        for (colonne = 0; colonne < NB_CASES; colonne++)
        {
            cout << plateauJeu[ligne][colonne] << " ";
        }
        cout << endl;
    }

    return 0;
}
