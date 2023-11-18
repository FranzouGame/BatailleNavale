/*
programme : batailleNavale
But : Jouer à la bataille navale
*/

#include <iostream>
#include "game-tools.h"
using namespace std;

// Déclaration des types
struct UneCoord
{
    int x;
    int y;
};

struct UnBateau
{
    UneCoord pos[4];
};

const unsigned short int NB_CASES = 9; // Taille du tableau horizontalement et verticalement
char plateauJeu[NB_CASES][NB_CASES];   // Tableau contenant le plateau de jeu

int tourJoueur = 0;

// Déclaration des sous-programmes
void afficherEnTete();
void afficherTableau();
void genererBateau(UnBateau bateauUtiliser); // A faire
void afficherBateau(UnBateau bateauAVoir);
void nouveauTour(); // A completer
void genererCoord(int &x, int &y);
void getCoord(int ligne, int colonne); // A complter
int verifBateauToucher(int x, int y);  // A faire

int main(void)
{
    UnBateau bateauJoueur1;
    UnBateau bateauJoueur2;

    genererBateau(bateauJoueur1);
    afficherBateau(bateauJoueur1);
    afficherTableau();
    nouveauTour();
    cin >> tourJoueur;

    return 0;
}

void afficherTableau()
{
    cout << endl;

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

void genererBateau(UnBateau bateauUtiliser)
{
    int sens = random(1, 2); // 1 = Vertical, 2 = Horizontale, 3 = Diagonale
    int X = random(1, 9);
    int Y = random(1, 9);

    // Vérifier si les coordonnées X, Y sont libres avant de générer un bateau
    if (plateauJeu[X][Y] == '\0')
    {
        switch (sens)
        {
        case 1: // Vertical
            if (X > 3 && X < 6)
            {
                // Vérifier si les cases sont libres avant de générer le bateau
                for (int i = 0; i < 4; i++)
                {
                    if (plateauJeu[X + i][Y] != '\0')
                    {
                        genererBateau(bateauUtiliser); // Si une case est occupée, générer un nouveau bateau
                        return;
                    }
                }
                // Si toutes les cases sont libres, générer le bateau
                for (int i = 0; i < 4; i++)
                {
                    bateauUtiliser.pos[i].x = X + i;
                    bateauUtiliser.pos[i].y = Y;
                    getCoord(bateauUtiliser.pos[i].x, bateauUtiliser.pos[i].y);
                }
            }
            else
            {
                genererBateau(bateauUtiliser);
            }
            break;

        case 2: // Horizontal
            if (Y > 3 && Y < 6)
            {
                // Vérifier si les cases sont libres avant de générer le bateau
                for (int i = 0; i < 4; i++)
                {
                    if (plateauJeu[X][Y + i] != '\0')
                    {
                        genererBateau(bateauUtiliser); // Si une case est occupée, générer un nouveau bateau
                        return;
                    }
                }
                // Si toutes les cases sont libres, générer le bateau
                for (int i = 0; i < 4; i++)
                {
                    bateauUtiliser.pos[i].x = X;
                    bateauUtiliser.pos[i].y = Y + i;
                    getCoord(bateauUtiliser.pos[i].x, bateauUtiliser.pos[i].y);
                }
            }
            else
            {
                genererBateau(bateauUtiliser);
            }
            break;

        default:
            break;
        }
    }
}

void afficherBateau(UnBateau bateauAVoir)
{
    for (int i = 0; i < 4; i++)
    {
        cout << "(" << char(bateauAVoir.pos[i].y + 64) << bateauAVoir.pos[i].x << ") ";
    }
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
        getCoord(ligne, colonne);
    }
    else
    {
        if ((ligne < 65 || ligne > 73) && (colonne > 0 && colonne < 10))
        {
            cout << "### Erreur en Y ###" << endl;
            nouveauTour();
        }
        else if (colonne < 0 || colonne > 9)
        {
            cout << "### Erreur en X ###" << endl;
            nouveauTour();
        }
    }

    afficherTableau();
}

void getCoord(int ligne, int colonne)
{
    int bateauToucher = 0;
    // bateauToucher = verifBateauToucher(ligne, colonne);
    // 0 = non, 1 = joueur 1, 2 = joueur2

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
