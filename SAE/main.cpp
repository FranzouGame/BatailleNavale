/*
programme : batailleNavale
But : Jouer à la bataille navale
*/

#include <iostream>
#include "game-tools.h"
using namespace std;

const unsigned short int NB_CASEBATEAU = 4; // Longueur d'un bateau

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

const unsigned short int NB_BATEAU = 2; // Nombre de bateaux pris en compte
Bateau Bateaux[NB_BATEAU];              // Tableau de Bateaux contenant les NB_BATEAUX de bateaux

int tourJoueur = 0;   // Variable stockant à qui est le tour
int partieGagner = 0; // 1 =  Joueur  1 gagne, 2 = Joueur 2 gagne, 3 = Joueur 1 abandonne, 4 = Joueur 2 abandonne
int tirjoueur1 = 0;   // Stockage du nombre du tir du joueur 1
int tirjoueur2 = 0;   // Stockage du nombre de tirs du joeuur 2

string action;  // Stockage du tir du joueur, ou de son abandon
string Joueur1; // Nom du joueur 1
string Joueur2; // Nom du joueur 2

// Déclaration des sous-programmes
void afficherTableau();
// But : Afficher le tableau de jeu
void afficherEnTete();
// But : Afficher l'en-tête lors d'un tir
void genererBateau(int indexBateau); // Diago a faire
// But : Générer les bateaux nécessaires pour la partie
void afficherBateau();
// But : Afficher les coordonnées des bateaux à l'écran
void nouveauTour(); // A completer
// But : Proposer un joueur de tirer et vérifier celui-ci
void verifBateauToucher(int ligne, int colonne);
// But : Vérifier si le tir du joueur touche un bateau ou s'il tire dans l'eau
void verifGagnant();
// But : Vérifier si un des joueurs gagne ou si la partie continue
void afficherResultat();
// But : Afficher le résultat de la partie

int main(void)
{
    // Saisie du nom des joueurs
    cout << "Quel est le nom du joueur 1 : ";
    cin >> Joueur1;
    cout << "Quel est le nom du joueur 2 : ";
    cin >> Joueur2;

    genererBateau(0); // Generation des bateaux

    // Boucle principale
    while (true)
    {
        // Nettoyer le terminal entre les 2 tours
        effacer();

        // Afficher les informations pour les joueurs
        afficherEnTete();

        // Afficher la grille avant le tir du joueur
        afficherTableau();

        // Inviter le joueur concerné à effectuer son tir, et vérifier le résultat de celui ci
        nouveauTour();

        // Vérifier si un des joueurs a gagné la partie
        verifGagnant();

        // Changement du tours entre les deux joueurs
        tourJoueur = (tourJoueur + 1) % 2;

        // On vérifie si la partie est terminée, par abandon ou victoire d'un des joueurs
        if (partieGagner != 0)
        {
            afficherResultat();
            break;
        }
    }

    pause(10);
    return 0;
}

// Définition des sous-programmes
void afficherTableau()
{
    cout << endl;

    // Parcourir et remplir le tableau
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
    // Afficher le nom du jeu
    cout << "B A T A I L L E   N A V A L E" << endl
         << endl;
    // Afficher le but du jeu
    cout << "Chaque joueur doit couler un bateau de 4 cases (vertical, horizontal ou diagonal)" << endl
         << endl;
    // Afficher les 4 coordonnées des 2 bateaux
    afficherBateau();
    cout << endl
         << endl;

    // Afficher le nom du joueur qui doit jouer
    if (tourJoueur == 0)
    {
        // Afficher le nom du joueur 1
        cout << "Joueur 1 = " << Joueur1 << endl
             << endl;
    }
    else
    {
        // Afficher le nom du joueur 2
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
    int X;    // Position horizontable dans le tableau
    int Y;    // Position verticale dans le tableau

    // Génération des indices de la première case du bateau, et du sens de celui-ci
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
    // Variables locales
    int i = 0;

    // Traitements
    // Parcourir les bateaux
    for (const Bateau &bateau : Bateaux)
    {
        // Incrémentation du compteur
        i++;

        // Afficher le message de positions des bateaux et leur représenttion dans la grille
        cout << "Bateau" << i;
        if (i == 1)
        {
            cout << " (O) = ";
        }
        else
        {
            cout << " (X) = ";
        }

        // Afficher les coordonnées de chaque bateau
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

    // Vérifier l'abandon du joueur
    if (action == "@@")
    {
        // Vérifier si le joueur 1 abandonne
        if (tourJoueur == 0)
        {
            partieGagner = 3;
        }
        // Vérifier si le joueur 2 abandonne
        else
        {
            partieGagner = 4;
        }
    }
    // Si le joueur n'abndonne pas, mettre à jour son nombre de tirs
    else
    {
        // Mettre à jour le nombre de tirs du joueur 1
        if (tourJoueur == 0)
        {
            tirjoueur1++;
        }
        // Mettre à jour le nombre de tirs du joueur 2
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
            // Vérifier si le tir du joueur touche un bateau
            verifBateauToucher(ligne, colonne);
        }
        // Afficher le message d'erreur de saisie
        else
        {
            // Vérification de l'erreur en ordonnée
            if ((ligne < 65 || ligne > 73) && (colonne > 0 && colonne < 10))
            {
                // Afficher le message d'erreur
                cout << "### Erreur en Y ###" << endl;
                // Relancer une invitation à la saisie
                nouveauTour();
            }
            else if (colonne < 0 || colonne > 9)
            {
                // Afficher le message d'erreur
                cout << "### Erreur en X ###" << endl;
                // Relancer une invitation à la saisie
                nouveauTour();
            }
        }
    }
    // Afficher la grille
    afficherTableau();
}

void verifGagnant()
{
    // Variables locales
    bool joueur1Gagne = true; // Booléen représentant le résultat du joueur 1
    bool joueur2Gagne = true; // Booléen représentant le résultat du joueur 2
    int toucheJoueur1 = 0;    // Nombre de cases touchées du bateau 1
    int toucheJoueur2 = 0;    // Nombre de cases touchées du bateau 2

    // Traitements
    // Parcours du tableau pour vérifier le nombre de cases touchées par bateaux
    for (int i = 0; i < NB_BATEAU; i++) // Parcourir les 2 bateaux
    {
        for (int j = 0; j < NB_CASEBATEAU; j++) // Parcourir les cases des bateaux
        {
            // Récupérer les coordonnées de chaque position des bateaux
            Coord coord = Bateaux[i].pos[j];

            // Vérifier si la coordonnée du bateau dans le plateau est complétée
            if (plateauJeu[coord.x][coord.y] == 'O') // Bateau 1
            {
                // Mettre à jour le compteur de case touchées du bateau 1
                toucheJoueur1++;
            }
            else if (plateauJeu[coord.x][coord.y] == 'X') // Bateau 2
            {
                // Mettre à jour le compteur de case touchées du bateau 2
                toucheJoueur2++;
            }
        }

        // Mise à jour du gagnant
        joueur1Gagne = joueur1Gagne && (toucheJoueur1 == NB_CASEBATEAU); // On vérifie si le bateau 1 est touché autant de fois qu'il est long
        joueur2Gagne = joueur2Gagne && (toucheJoueur2 == NB_CASEBATEAU); // On vérifie si le bateau 2 est touché autant de fois qu'il est long

        // Sortir de la boucle si aucun des joueurs n'a gagné
        if (!joueur1Gagne && !joueur2Gagne)
        {
            break;
        }
    }

    // Vérifier si un joueur a gagné
    if (joueur1Gagne)
    {
        // Mettre à jour le gagnant
        partieGagner = 1;
    }
    else if (joueur2Gagne)
    {
        // Mettre à jour le gagnant
        partieGagner = 2;
    }
}

void afficherResultat()
{
    // Vérifier qui a gagné
    if (partieGagner == 1)
    {
        // Afficher le message de victoire du joueur 1
        cout << "### Joueur 1 " << Joueur1 << " : GAGNE en " << tirjoueur1 << " tirs ###" << endl;
        cout << "### Joueur 2 " << Joueur2 << " : PERD ###" << endl;
    }
    else if (partieGagner == 2)
    {
        // Afficher le message de victoire du joueur 2
        cout << "### Joueur 1 " << Joueur1 << " : PERD ###" << endl;
        cout << "### Joueur 2 " << Joueur2 << " : GAGNE en " << tirjoueur2 << " tirs ###" << endl;
    }
    else if (partieGagner == 3)
    {
        // Afficher le message d'abandon du joueur 1
        cout << "### Joueur 1 " << Joueur1 << " : ABANDON ###" << endl;
        cout << "### Joueur 2 " << Joueur2 << " : GAGNE en " << tirjoueur2 << " tirs ###" << endl;
    }
    else if (partieGagner == 4)
    {
        // Affficher le message d'abandon du joueur 2
        cout << "### Joueur 1 " << Joueur1 << " : GAGNE en " << tirjoueur1 << " tirs ###" << endl;
        cout << "### Joueur 1 " << Joueur2 << " : ABANDON ###" << endl;
    }
}