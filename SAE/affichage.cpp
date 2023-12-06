#include <iostream>
#include "game-tools.h"
#include "bateaux.h"
#include "affichage.h"
using namespace std;




void afficherEnTete(UnJoueur player1, UnJoueur player2, UnBateau boat[] , const unsigned short int NB_BATEAUX, const unsigned short int NB_CASES)
{
    // Afficher le nom du jeu
    cout << "B A T A I L L E   N A V A L E" << endl
         << endl;
    // Afficher le but du jeu
    cout << "Chaque joueur doit couler un bateau de 4 cases (vertical, horizontal ou diagonal)" << endl
         << endl;
    // Afficher les 4 coordonnées des 2 bateaux
    afficherBateau(boat, NB_BATEAUX, NB_CASES);
    cout << endl
         << endl;

    // Afficher le nom du joueur qui doit jouer
    if (tourJoueur == 0)
    {
        // Afficher le nom du joueur 1
        cout << "Joueur 1 = " << player1.nom << endl
             << endl;
    }
    else
    {
        // Afficher le nom du joueur 2
        cout << "Joueur 2 = " << player2.nom << endl
             << endl;
    }
}

void afficherTableau(char grille[][TAILLE_TAB], int TAILLE_TAB)
{
    cout << endl;

    // Parcourir et remplir le tableau
    for (int i = 0; i <= TAILLE_TAB + 1; i++) // Parcours des différentes lignes
    {
        for (int j = 0; j <= TAILLE_TAB + 1; j++) // parcours des différentes colonnes
        {
            if (i == 0 || i == TAILLE_TAB + 1) // Afficher les index lettrés du haut et du bas de la grille, sans en afficher aucun dans les 4 coins
            {
                // Afficher les cases des coins vides
                if (j == 0 || j == TAILLE_TAB + 1)
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
                if (j == 0 || j == TAILLE_TAB + 1)
                {
                    cout << i;
                }
                // Remplir les cases non utilisées, qui contiennent un caractère vide en attendant que le jeu se déroule
                else
                {
                    cout << grille[i][j] << " ";
                }
            }
        }
        cout << endl;
    }
}

void afficherBateau(UnBateau boat[] , const unsigned short int NB_BATEAUX, const unsigned short int NB_CASES)
{
    // Parcours des 2 bateaux du tableau Bateaux
    for (int indiceBateau = 0; indiceBateau < NB_BATEAUX; indiceBateau++)
    {
        // Afficher l'en-tête de la ligne
        cout << "Bateau " << (indiceBateau + 1) << (indiceBateau == 0 ? " (O) " : " (X) ") << " = ";
        // Afficher les coordonnées de tous les points du bateau
        for (int coordBateau = 0; coordBateau < NB_CASES_BATEAU; coordBateau++)
        {
            cout << " (" << char(boat[indiceBateau].pos[coordBateau].y + 64) << "," << boat[indiceBateau].pos[coordBateau].x << ")";
        }
        cout << endl;
    }
}
