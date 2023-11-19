/*
programme : batailleNavale
But : Jouer à la bataille navale
*/

#include <iostream>
#include "game-tools.h"
using namespace std;

const unsigned short int NB_CASEBATEAU = 4;

// Déclaration des types
struct Coord
{
    int x = 0;
    int y = 0;
};

struct Bateau
{
    Coord pos[NB_CASEBATEAU];
};

const unsigned short int NB_CASES = 9; // Taille du tableau horizontalement et verticalement
char plateauJeu[NB_CASES][NB_CASES];   // Tableau contenant le plateau de jeu

const unsigned short int NB_BATEAU = 2;
Bateau Bateaux[NB_BATEAU];

int tourJoueur = 0;
int partieGagner = 0; // 1 =  Joueur  1 gagne, 2 = Joueur 2 gagne, 3 = Joueur 1 abandonne, 4 = Joueur 2 abandonne
int tirjoueur1 = 0;
int tirjoueur2 = 0;

string action;
string Joueur1;
string Joueur2;

// Déclaration des sous-programmes
void afficherTableau();
void afficherEnTete();
void genererBateau(int indexBateau); // Diago a faire
void afficherBateau();
void nouveauTour(); // A completer
void verifBateauToucher(int ligne, int colonne);
void verifGagnant();
void afficherResultat();

int main(void)
{
    // Demande du nom des joueurs
    cout << "Quel est le nom du joueur 1 : ";
    cin >> Joueur1;
    cout << "Quel est le nom du joueur 2 : ";
    cin >> Joueur2;

    genererBateau(0); // Generation des bateaux

    // Boucle principale
    while (true)
    {
        effacer();
        afficherEnTete();
        afficherTableau();
        nouveauTour();
        verifGagnant();

        // Changement du tours entre les deux joueurs
        tourJoueur = (tourJoueur + 1) % 2;

        // Verification de fin de partie
        if (partieGagner != 0)
        {
            afficherResultat();
            break;
        }
    }

    pause(10);
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

void afficherEnTete()
{
    cout << "B A T A I L L E   N A V A L E" << endl
         << endl;
    cout << "Chaque joueur doit couler un bateau de 4 cases (vertical, horizontal ou diagonal)" << endl
         << endl;
    afficherBateau();
    cout << endl
         << endl;

    if (tourJoueur == 0)
    {
        cout << "Joueur 1 = " << Joueur1 << endl
             << endl;
    }
    else
    {
        cout << "Joueur 2 = " << Joueur2 << endl
             << endl;
    }
}

void genererBateau(int indexBateau)
{
    if (NB_BATEAU <= indexBateau)
    {
        return;
    }

    int sens; // 1 = Vertical, 2 = Horizontale, 3 = Diagonale
    int X;
    int Y;

    sens = random(1, 2);
    X = random(1, 9);
    Y = random(1, 9);

    // Vérifier si les coordonnées X, Y sont libres avant de générer un bateau
    if (plateauJeu[Y][X] == '\0')
    {
        switch (sens)
        {
        case 1: // Vertical
            if (X < 6)
            {
                // Vérifier si les cases sont libres avant de générer le bateau
                for (int i = 0; i < NB_CASEBATEAU; i++)
                {
                    if (plateauJeu[X + i][Y] != '\0')
                    {
                        genererBateau(indexBateau); // Si une case est occupée, générer un nouveau bateau
                        return;
                    }
                }
                // Si toutes les cases sont libres, générer le bateau
                for (int i = 0; i < NB_CASEBATEAU; i++)
                {
                    Bateaux[indexBateau].pos[i].x = X + i;
                    Bateaux[indexBateau].pos[i].y = Y;
                }
                genererBateau(indexBateau + 1);
            }
            else
            {
                genererBateau(indexBateau);
            }
            break;

        case 2: // Horizontal
            if (Y < 6)
            {
                // Vérifier si les cases sont libres avant de générer le bateau
                for (int i = 0; i < NB_CASEBATEAU; i++)
                {
                    if (plateauJeu[X][Y + i] != '\0')
                    {
                        genererBateau(indexBateau); // Si une case est occupée, générer un nouveau bateau
                        return;
                    }
                }
                // Si toutes les cases sont libres, générer le bateau
                for (int i = 0; i < NB_CASEBATEAU; i++)
                {
                    Bateaux[indexBateau].pos[i].x = X;
                    Bateaux[indexBateau].pos[i].y = Y + i;
                }
                genererBateau(indexBateau + 1);
            }
            else
            {
                genererBateau(indexBateau);
            }
            break;

        default:
            break;
        }
    }
    else
    {
        genererBateau(indexBateau);
    }
}

void verifBateauToucher(int ligne, int colonne)
{
    int bateauToucher = 0; // 0 = non, 1 = joueur 1, 2 = joueur2

    for (int i = 0; i < NB_BATEAU; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (Bateaux[i].pos[j].x == ligne && Bateaux[i].pos[j].y == colonne)
            {
                if (i == 0)
                {
                    bateauToucher = 1;
                }
                else
                {
                    bateauToucher = 2;
                }
                break;
            }
        }
        if (bateauToucher == 1 || bateauToucher == 2)
        {
            break;
        }
    }

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

void afficherBateau()
{
    int i = 0;
    for (const Bateau &bateau : Bateaux)
    {
        i++;
        cout << "Bateau" << i;
        if (i == 1)
        {
            cout << " (O) = ";
        }
        else
        {
            cout << " (X) = ";
        }

        for (const Coord &coord : bateau.pos)
        {
            cout << " (" << char(coord.y + 64) << "," << coord.x << ") ";
        }
        cout << endl;
    }
}

void nouveauTour()
{
    // Traitements
    // Saisie de la cible du tir par l'utilisisateur
    cout << "Votre tir (ex. A3) ou abandonner (@@) ? ";
    cin >> action;

    if (action == "@@") // Condition d'abandon
    {
        if (tourJoueur == 0)
        {
            partieGagner = 3; // Joueur 1 abandonne
        }
        else
        {
            partieGagner = 4; // Joueur 2 abandonne
        }
    }
    else
    {
        if (tourJoueur == 0)
        {
            tirjoueur1++;
        }
        else
        {
            tirjoueur2++;
        }

        // Conversion du retour utilisateur pour pouvoir placer le tir sur la grille
        int ligne = (int)action[1] - 48;
        int colonne = int(action[0]) - 64;

        // Vérification de la validité du tir
        if (action.length() == 2 && colonne > 0 && colonne < 10 && ligne > 0 && ligne < 10)
        {
            verifBateauToucher(ligne, colonne);
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
    }

    afficherTableau();
}

void verifGagnant()
{
    bool joueur1Gagne = true;
    bool joueur2Gagne = true;

    for (int i = 0; i < NB_BATEAU; i++)
    {
        int toucheJoueur1 = 0;
        int toucheJoueur2 = 0;

        for (int j = 0; j < NB_CASEBATEAU; j++)
        {
            Coord coord = Bateaux[i].pos[j];

            if (plateauJeu[coord.x][coord.y] == 'O')
            {
                toucheJoueur1++;
            }
            else if (plateauJeu[coord.x][coord.y] == 'X')
            {
                toucheJoueur2++;
            }
        }

        joueur1Gagne = joueur1Gagne && (toucheJoueur1 == NB_CASEBATEAU);
        joueur2Gagne = joueur2Gagne && (toucheJoueur2 == NB_CASEBATEAU);

        // Break if both players can't win anymore
        if (!joueur1Gagne && !joueur2Gagne)
        {
            break;
        }
    }

    if (joueur1Gagne)
    {
        partieGagner = 1;
    }
    else if (joueur2Gagne)
    {
        partieGagner = 2;
    }
}

void afficherResultat()
{
    if (partieGagner == 1)
    {
        cout << "### Joueur 1 " << Joueur1 << " : GAGNE en " << tirjoueur1 << " tirs ###" << endl;
        cout << "### Joueur 2 " << Joueur2 << " : PERD ###" << endl;
    }
    else if (partieGagner == 2)
    {
        cout << "### Joueur 1 " << Joueur1 << " : PERD ###" << endl;
        cout << "### Joueur 2 " << Joueur2 << " : GAGNE en " << tirjoueur2 << " tirs ###" << endl;
    }
    else if (partieGagner == 3)
    {
        cout << "### Joueur 1 " << Joueur1 << " : ABANDON ###" << endl;
        cout << "### Joueur 2 " << Joueur2 << " : GAGNE en " << tirjoueur2 << " tirs ###" << endl;
    }
    else if (partieGagner == 4)
    {
        cout << "### Joueur 1 " << Joueur1 << " : GAGNE en " << tirjoueur1 << " tirs ###" << endl;
        cout << "### Joueur 1 " << Joueur2 << " : ABANDON ###" << endl;
    }
}