/*
programme : batailleNavale
But : Jouer à la bataille navale
*/

#include "game-tools.h"
#include <iostream>
#include <tuple>
using namespace std;

const unsigned short int NB_CASES = 9; // Taille du tableau horizontalement et verticalement
char plateauJeu[NB_CASES][NB_CASES];   // Tableau contenant le plateau de jeu

int tourJoueur = 0;
tuple<int, int> bateauJoueur[2][4];

// Déclaration des sous-programmes
void afficherEnTete();
void afficherTableau();                         // A commenter
void genererBateau();                           // A faire
void nouveauTour();                             // A completer
void tirJoueur(int ligne, int colonne);         // A complter
int verifBateauToucher(int ligne, int colonne); // A faire

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
    string action;                                          // action du joueur
    int ligne;                                              // ligne du tir du joueur
    int colonne;                                            // colonne du tir du joueur
    const unsigned short int INDICE_LETTRE_MIN = 97;        // Indice minimal de lettre dans la table ASCII
    const unsigned short int INDICE_LETTRE_MAX = 105;       // Indice maximal de lettre dans la table ASCII
    const unsigned short int CONVERSION_LETTRE_MINUSC = 64; // Valeur pour convertir un caractère lettré minuscule en nombre entier
    const unsigned short int CONVERSION_LETTRE_MAJUSC = 96; // Valeur pour convertir un caractère lettré majuscule en nombre entier
    const unsigned short int CONVERSION_ENTIER = 48;        // Valeur pour convertir un nombre fourni dans une chaine de caractères en entier
    const unsigned short int INDICE_VERIF_MIN = 0;          // Indice minimal pour la vérification de la saisie
    const unsigned short int INDICE_VERIF_MAX = 10;         // Indice maximal pour la vérification de la saisie

    // Traitements
    // Saisie de la cible du tir par l'utilisisateur
    cout << "Votre tir : ";
    cin >> action;

    // Conversion du retour utilisateur pour pouvoir placer le tir sur la grille
    if (int(action[0]) >= INDICE_LETTRE_MIN && int(action[0]) < INDICE_LETTRE_MAX)
    {
        colonne = int(action[0]) - CONVERSION_LETTRE_MAJUSC;
    }
    else
    {
        colonne = int(action[0]) - CONVERSION_LETTRE_MINUSC;
    }

    ligne = (int)action[1] - CONVERSION_ENTIER;

    // Vérification de la validité du tir
    if (action.length() == 2 && colonne > INDICE_VERIF_MIN && colonne < INDICE_VERIF_MAX && ligne > INDICE_VERIF_MIN && ligne < INDICE_VERIF_MAX)
    {
        tirJoueur(ligne, colonne);
    }

    // Gestion des erreurs de saisie
    else
    {
        // Vérification d'une éventuelle erreur en Y
        if ((ligne < INDICE_VERIF_MAX || ligne > INDICE_VERIF_MIN + 1) && (colonne > INDICE_VERIF_MIN && colonne < INDICE_VERIF_MAX))
        {
            // Affichage du message d'erreur
            cout << "### Erreur en Y ###" << endl;
            // Nouvelle saisie utilisateur
            nouveauTour();
        }
        // Vérification d'une éventuelle erreur en X
        else if (colonne < INDICE_VERIF_MIN || colonne >= INDICE_VERIF_MAX)
        {
            // Afficher le message d'erreur
            cout << "### Erreur en X ###" << endl;
            // Nouvelle saisie utilisateur
            nouveauTour();
        }
    }
    // Affichage du tableau après tir
    afficherTableau();
}

void tirJoueur(int ligne, int colonne)
{
    int bateauToucher;
    bateauToucher = 0;
    // bateauToucher = verifBateauToucher(ligne, colonne);
    // bateauToucher = verifBateauToucher(ligne, colonne);
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

int verifBateauToucher(int ligne, int colonne)
{
    return 0;
}