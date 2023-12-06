#include <iostream>
#include "game-tools.h"
#include "bateaux.h"
#include "affichage.h"
using namespace std;

// Type énuméré direction
enum UneDirection
{
    Horizontale,
    Verticale,
    Diagonale
};

bool positionEstVide(UnBateau tabBateaux[], int indexBateau, int X, int Y)
{
    for (int i = 0; i < NB_CASES_BATEAU; i++)
    {
        if (tabBateaux[indexBateau].pos[i].x == X && tabBateaux[indexBateau].pos[i].y == Y)
        {
            return false;
        }
    }
    return true;
}

void genererBateauPosition(UnBateau tabBoats[], int indexBateau, int X, int Y, int incrementX, int incrementY)
{
    for (int indiceCaseBateau = 0; indiceCaseBateau < NB_CASES_BATEAU; indiceCaseBateau++)
    {
        tabBoats[indexBateau].pos[indiceCaseBateau].x = X + incrementX * indiceCaseBateau;
        tabBoats[indexBateau].pos[indiceCaseBateau].y = Y + incrementY * indiceCaseBateau;
    }
}

void genererBateau(UnBateau bateau[], int indexBateau, const unsigned short int NB_BATEAUX, const unsigned short int NB_CASES)
{
    // Vérifier quel bateau on génère
    if (NB_BATEAUX <= indexBateau)
    {
        return;
    }

    int indiceDirection;        // Indice permettant de générer la direction du bateau
    int X;                      // Position horizontale dans le tableau
    int Y;                      // Position verticale dans le tableau
    UneDirection directionElue; // Direction choisie aléatoirement
    bool bateauValide;

    do
    {
        // Générer des coordonnées
        X = random(1, NB_CASES);
        Y = random(1, NB_CASES);

        // Générer une direction pour le bateau
        indiceDirection = random(1, 3);
        // Assigner la direction à la variable concernée
        switch (indiceDirection)
        {
        case 1:
            directionElue = Verticale;
            break;
        case 2:
            directionElue = Horizontale;
            break;
        default:
            directionElue = Diagonale;
            break;
        }

        // Initialiser l'indicateur de validité de la génération du bateau
        bateauValide = true;

        // Générer un bateau
        switch (directionElue)
        {
        case Verticale:
            if (X + NB_CASES_BATEAU - 1 > NB_CASES)
            {
                X = NB_CASES - NB_CASES_BATEAU + 1;
            }
            // Vérifier si les coordonnées X, Y sont libres avant de générer un bateau
            if (indexBateau != 0)
            {
                for (int i = 0; i < NB_CASES_BATEAU; i++)
                {
                    if (!positionEstVide(bateau, indexBateau - 1, X, Y + i))
                    {
                        bateauValide = false;
                        break;
                    }
                }
            }

            // Génération des positions du bateau
            if (bateauValide)
            {
                genererBateauPosition(bateau, indexBateau, X, Y, 1, 0);
            }
            else
            {
                genererBateau(bateau, indexBateau, NB_BATEAUX, NB_CASES);
            }
            break;
        case Horizontale:
            if (Y + NB_CASES_BATEAU - 1 > NB_CASES)
            {
                Y = NB_CASES - NB_CASES_BATEAU + 1;
            }
            // Vérifier si les coordonnées X, Y sont libres avant de générer un bateau
            if (indexBateau != 0)
            {
                for (int i = 0; i < NB_CASES_BATEAU; i++)
                {
                    if (!positionEstVide(bateau, indexBateau - 1, X + i, Y) || !positionEstVide(bateau, indexBateau - 1, X + i, Y + 1) || !positionEstVide(bateau, indexBateau - 1, X + i, Y - 1))
                    {
                        bateauValide = false;
                        break;
                    }
                }
            }

            // Génération des positions du bateau
            if (bateauValide)
            {
                genererBateauPosition(bateau, indexBateau, X, Y, 0, 1);
            }
            else
            {
                genererBateau(bateau, indexBateau, NB_BATEAUX, NB_CASES);
            }
            break;

        case Diagonale:
            // Vérifier si les coordonnées X, Y sont libres avant de générer un bateau
            bool bateauValideHaut = true;
            bool bateauValideBas = true;

            if (X + NB_CASES_BATEAU - 1 > NB_CASES || Y + NB_CASES_BATEAU - 1 > NB_CASES) // En bas droite
            {
                bateauValideBas = false;
            }
            if (X - NB_CASES_BATEAU + 1 <= 0 || Y + NB_CASES_BATEAU - 1 > NB_CASES) // En haut droite
            {
                bateauValideHaut = false;
            }
            if (bateauValideBas || bateauValideHaut)
            {
                for (int i = 0; i < NB_CASES_BATEAU; i++)
                {
                    // vérifier s'il est possible de générer un bateau dans une des directions
                    if (!positionEstVide(bateau, indexBateau - 1, X - i, Y + i) || !positionEstVide(bateau, indexBateau - 1, X - i, Y + i + 1) || !positionEstVide(bateau, indexBateau - 1, X - i, Y + i - 1)) // En haut à droite
                    {
                        bateauValideHaut = false;
                    }
                    if (!positionEstVide(bateau, indexBateau - 1, X + i, Y + i) || !positionEstVide(bateau, indexBateau - 1, X + i, Y + i + 1) || !positionEstVide(bateau, indexBateau - 1, X + i, Y + i - 1)) // En bas à droite
                    {
                        bateauValideBas = false;
                    }
                }
            }

            // Générer un bateau en focntion des possibilités
            if (bateauValideHaut || bateauValideBas)
            {
                // Vérifier la/les générations possibles
                if (bateauValideHaut && bateauValideBas)
                {
                    // Choisir aléatoirement entre haut et bas
                    int choixDirection = random(0, 1);
                    if (choixDirection == 0)
                    {
                        // Génération des positions du bateau en haut à droite
                        genererBateauPosition(bateau, indexBateau, X, Y, -1, 1);
                    }
                    else
                    {
                        // Génération des positions du bateau en bas à droite
                        genererBateauPosition(bateau, indexBateau, X, Y, 1, 1);
                    }
                }
                else if (bateauValideHaut)
                {
                    // Génération des positions du bateau en haut à droite
                    genererBateauPosition(bateau, indexBateau, X, Y, -1, 1);
                }
                else
                {
                    // Génération des positions du bateau en bas à droite
                    genererBateauPosition(bateau, indexBateau, X, Y, 1, 1);
                }
            }
            else
            {
                bateauValide = false;
            }
            break;
        }

    } while (!bateauValide);

    // Générer le bateau suivant
    genererBateau(bateau, indexBateau + 1, NB_BATEAUX, NB_CASES);
}

void verifBateauToucher(UnBateau Bat[], char grille[][TAILLE_TAB], int ligne, int colonne, const unsigned short int NB_BATEAUX, const unsigned short int NB_CASES)
{
    // Variables Locales
    int bateauToucher = 0; // 0 = non, 1 = joueur 1, 2 = joueur2

    // Parcourir les bateaux
    for (int indiceBateau = 0; indiceBateau < NB_BATEAUX; indiceBateau++)
    {
        // Parcourir les coordonnées de chaque bateau
        for (int indiceCaseBateau = 0; indiceCaseBateau < NB_CASES_BATEAU; indiceCaseBateau++)
        {
            // Vérifier si le tir du joueur touche un bateau
            if (Bat[indiceBateau].pos[indiceCaseBateau].x == ligne && Bat[indiceBateau].pos[indiceCaseBateau].y == colonne)
            {
                // Vérifier si le bateau touché est le bateau 1
                if (indiceBateau == 0)
                {
                    bateauToucher = 1;
                }
                // Vérifier si le bateau touché est le bateau 2
                else
                {
                    bateauToucher = 2;
                }
                break;
            }
        }
        // Sortir de la boucle si un bateau est touché avant la fin de celle ci
        if (bateauToucher == 1 || bateauToucher == 2)
        {
            break;
        }
    }

    // Mettre à jour la grille en fonction du tir du joueur
    // Afficher un point si le joueur tire dans l'eau
    if (bateauToucher == 0)
    {
        grille[ligne][colonne] = '.';
    }
    // Afficher un O si le joueur touche le bateau 1
    else if (bateauToucher == 1)
    {
        grille[ligne][colonne] = 'O';
    }
    // Afficher un X si le joueur touche le bateau 2
    else if (bateauToucher == 2)
    {
        grille[ligne][colonne] = 'X';
    }
}
