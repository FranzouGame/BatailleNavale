/*
programme : batailleNavale
But : Jouer à la bataille navale
*/

#include <iostream>
#include "game-tools.h"
using namespace std;

const unsigned short int NB_CASEBATEAU = 4; // Longueur d'un bateau

// Type énuméré direction
enum UneDirection
{
    Horizontale,
    Verticale,
    Diagonale
};

// Type énuméré servant pour gérer l'état de la partie
enum EtatsPossibles
{
    enCours,
    victoireJoueur1,
    victoireJoueur2,
    abandonJoueur1,
    abandonJoueur2
};

// Déclaration des types
struct Coord
{
    int x = 0; // Abscisse de la coordonnée
    int y = 0; // Ordonnée de la coordonnée
};

struct Bateau
{
    Coord pos[NB_CASEBATEAU]; // Un bateau aura NB_CASEBATEAU coordonnées
};

const unsigned short int NB_CASES = 9; // Taille du tableau horizontalement et verticalement
char plateauJeu[NB_CASES][NB_CASES];   // Tableau contenant le plateau de jeu

int tourJoueur = 0;        // Variable stockant à qui est le tour
EtatsPossibles etatPartie; // Décrit l'état de la partie
int nbTirsJoueurs1 = 0;    // Stockage du nombre du tir du joueur 1
int nbTirsJoueur2 = 0;     // Stockage du nombre de tirs du joeuur 2

// Déclaration des sous-programmes
void afficherTableau();
// But : Afficher le tableau de jeu
void afficherEnTete(string pseudo1, string pseudo2);
// But : Afficher l'en-tête lors d'un tir
void genererBateau(int indexBateau); // Diago a faire, peut être changer la génération des 2 autres pour opti
// But : Générer les bateaux nécessaires pour la partie
void afficherBateau();
// But : Afficher les coordonnées des bateaux à l'écran
void nouveauTour(); // A completer
// But : Proposer un joueur de tirer et vérifier celui-ci
void verifBateauToucher(int ligne, int colonne);
// But : Vérifier si le tir du joueur touche un bateau ou s'il tire dans l'eau
void verifierGagnant();
// But : Vérifier si un des joueurs gagne ou si la partie continue
void afficherResultat(string pseudo1, string pseudo2);
// But : Afficher le résultat de la partie

int main(void)
{

    // Variables
    string nomJoueur1;                      // Nom du joueur 1
    string nomJoueur2;                      // Nom du joueur 2
    int indexBateau;                        // Index du bateau en cours de traitement dans le tableau des bateaux
    const unsigned short int NB_BATEAU = 2; // Nombre de bateaux pris en compte
    Bateau Bateaux[NB_BATEAU];              // Tableau de Bateaux contenant les NB_BATEAUX de bateaux

    // Saisie du nom des joueurs
    cout << "Quel est le nom du joueur 1 : ";
    cin >> nomJoueur1;
    cout << "Quel est le nom du joueur 2 : ";
    cin >> nomJoueur2;

    // Initialisation de la partie
    // Initialisation des variables
    indexBateau = 0;

    // Génération des bateaux
    genererBateau(indexBateau);

    // Jouer la partie
    while (true)
    {
        // Nettoyer le terminal entre les 2 tours
        effacer();

        // Afficher les informations pour les joueurs
        afficherEnTete(nomJoueur1, nomJoueur2);

        // Afficher la grille avant le tir du joueur
        afficherTableau();

        // Inviter le joueur concerné à effectuer son tir, et vérifier le résultat de celui ci
        nouveauTour();

        // Vérifier si un des joueurs a gagné la partie
        verifierGagnant();

        // Changement du tours entre les deux joueurs
        tourJoueur = (tourJoueur + 1) % 2;

        // On vérifie si la partie est terminée, par abandon ou victoire d'un des joueurs
        if (!(etatPartie == enCours))
        {
            afficherResultat(nomJoueur1, nomJoueur2);
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

void afficherEnTete(string pseudo1, string pseudo2)
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
        cout << "Joueur 1 = " << pseudo1 << endl
             << endl;
    }
    else
    {
        // Afficher le nom du joueur 2
        cout << "Joueur 2 = " << pseudo2 << endl
             << endl;
    }
}

void genererBateau(int indexBateau, int NB_BATEAU, Bateau Bateaux[])
{
    // Vérifier
    if (NB_BATEAU <= indexBateau)
    {
        return;
    }

    int indiceDirection;        // Indice permettant de générer la direction dui bateau
    int X;                      // Position horizontable dans le tableau
    int Y;                      // Position verticale dans le tableau
    UneDirection directionElue; // Direction choisie aléatoirement

    // Génération des indices de la première case du bateau, et du sens de celui-ci
    indiceDirection = random(1, 3);
    X = random(1, NB_CASES);
    Y = random(1, NB_CASES);

    // Assignation de la direction
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

    // Vérifier si les coordonnées X, Y sont libres avant de générer un bateau
    if (plateauJeu[Y][X] == '\0')
    {
        switch (directionElue)
        {
        // Cas dans lequel le bateau est vertical
        case Verticale:
            if (X > 6)
            {
                // Convertir Y au besoin
                X = X - (X - 6);
            }
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
            break;

        case Horizontale:
            if (Y > 6)
            {
                Y = Y - (Y - 6);
            }
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
            break;

        default:
            // Vérifier la disponibilité de la potentielle dernière case de la génération
            if ((X - 3 > 0 && Y + 3 < 10) && plateauJeu[X - 3][Y + 3] == '\0') // Génération vers en haut à droite
            {
                // Vérifier que les cases comprises entre la première et la dernière soient vides
                if (plateauJeu[X - 2][Y + 2] == '\0')
                {
                    if (plateauJeu[X - 1][Y + 1] == '\0')
                    {
                        for (int i = 0; i < NB_CASEBATEAU; i++)
                        {
                            Bateaux[indexBateau].pos[i].x = X - i;
                            Bateaux[indexBateau].pos[i].y = Y + i;
                        }
                        // Si un bateau est généré, en générer un deuxième
                        genererBateau(indexBateau + 1);
                    }
                }
            }
            else if ((X + 3 < 10 && Y + 3 < 10) && plateauJeu[X + 3][Y + 3] == '\0') // Génération vers en bas à droite
            {
                // Vérifier que les cases comprises entre la première et la dernière soient vides
                if (plateauJeu[X + 2][Y + 2] == '\0')
                {
                    if (plateauJeu[X + 1][Y + 1] == '\0')
                    {
                        for (int i = 0; i < NB_CASEBATEAU; i++)
                        {
                            Bateaux[indexBateau].pos[i].x = X + i;
                            Bateaux[indexBateau].pos[i].y = Y + i;
                        }
                        // Si un bateau est généré, en générer un deuxième
                        genererBateau(indexBateau + 1);
                    }
                }
            }
            else if ((X + 3 < 10 && Y - 3 > 0) && plateauJeu[X + 3][Y - 3] == '\0') // Génération vers en bas à gauche
            {
                // Vérifier que les cases comprises entre la première et la dernière soient vides
                if (plateauJeu[X + 2][Y - 2] == '\0')
                {
                    if (plateauJeu[X + 1][Y - 1] == '\0')
                    {
                        // Remplir le tableau de bateaux
                        for (int i = 0; i < NB_CASEBATEAU; i++)
                        {
                            Bateaux[indexBateau].pos[i].x = X + i;
                            Bateaux[indexBateau].pos[i].y = Y - i;
                        }
                        // Si un bateau est généré, en générer un deuxième
                        genererBateau(indexBateau + 1);
                    }
                }
            }
            else if ((X - 3 > 0 && Y - 3 > 0) && plateauJeu[X - 3][Y - 3] == '\0') // Génération vers en haut en gauche
            {
                // Vérifier que les cases comprises entre la première et la dernière soient vides
                if (plateauJeu[X - 2][Y - 2] == '\0')
                {
                    if (plateauJeu[X - 1][Y - 1] == '\0')
                    {
                        // Remplir Le tableau des bateaux
                        for (int i = 0; i < NB_CASEBATEAU; i++)
                        {
                            Bateaux[indexBateau].pos[i].x = X - i;
                            Bateaux[indexBateau].pos[i].y = Y - i;
                        }
                        // Si un bateau est généré, en générer un deuxième
                        genererBateau(indexBateau + 1);
                    }
                }
            }
            else
            {
                genererBateau(indexBateau);
            }
            break;
        }
    }
    else
    {
        genererBateau(indexBateau);
    }
}

void verifBateauToucher(int ligne, int colonne, int NB_BATEAU, Bateau Bateaux[])
{
    // Variables Locales
    int bateauToucher = 0; // 0 = non, 1 = joueur 1, 2 = joueur2

    // Parcourir les bateaux
    for (int indiceBateau = 0; indiceBateau < NB_BATEAU; indiceBateau++)
    {
        // Parcourir les coordonnées de chaque bateau
        for (int indiceCaseBateau = 0; indiceCaseBateau < NB_CASEBATEAU; indiceCaseBateau++)
        {
            // Vérifier si le tir du joueur touche un bateau
            if (Bateaux[indiceBateau].pos[indiceCaseBateau].x == ligne && Bateaux[indiceBateau].pos[indiceCaseBateau].y == colonne)
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
        plateauJeu[ligne][colonne] = '.';
    }
    // Afficher un O si le joueur touche le bateau 1
    else if (bateauToucher == 1)
    {
        plateauJeu[ligne][colonne] = 'O';
    }
    // Afficher un X si le joueur touche le bateau 2
    else if (bateauToucher == 2)
    {
        plateauJeu[ligne][colonne] = 'X';
    }
}

void afficherBateau(Bateau Bateaux[], int NB_BATEAU)
{
    // Parcours des 2 bateaux du tableau Bateaux
    for (int indiceBateau = 0; indiceBateau < NB_BATEAU; indiceBateau++)
    {
        // Afficher l'en-tête de la ligne
        cout << "Bateau " << (indiceBateau + 1) << (indiceBateau == 0 ? " (O) " : " (X) ") << " = ";
        // Afficher les coordonnées de tous les points du bateau
        for (int coordBateau = 0; coordBateau < NB_CASEBATEAU; coordBateau++)
        {
            cout << " (" << char(Bateaux[indiceBateau].pos[coordBateau].y + 64) << "," << Bateaux[indiceBateau].pos[coordBateau].x << ")";
        }
        cout << endl;
    }
}

void nouveauTour()
{
    // Variables locales
    string action; // Stockage du tir du joueur, ou de son abandon

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
            etatPartie = abandonJoueur1;
        }
        // Vérifier si le joueur 2 abandonne
        else
        {
            etatPartie = abandonJoueur2;
        }
    }
    // Si le joueur n'abndonne pas, mettre à jour son nombre de tirs
    else
    {
        // Mettre à jour le nombre de tirs du joueur 1
        if (tourJoueur == 0)
        {
            nbTirsJoueurs1++;
        }
        // Mettre à jour le nombre de tirs du joueur 2
        else
        {
            nbTirsJoueur2++;
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
}

void verifierGagnant(int NB_BATEAU, Bateau Bateaux[], char plateauJeu[NB_CASES][NB_CASES])
{
    // Variables locales
    int toucheBateau1 = 0;     // Nombre de tirs touchant le bateau 1
    int toucheBateau2 = 0;     // Nombre de tirs touchant le bateau 2
    Coord coordEnVerification; // Coordonée en cours d'analyse

    // Parcours des 2 bateaux
    for (int indiceBateau = 0; indiceBateau < NB_BATEAU; indiceBateau++)
    {
        // Parcours des coordonnées des 2 bateaux
        for (int indiceCaseBateau = 0; indiceCaseBateau < NB_CASEBATEAU; indiceCaseBateau++)
        {
            // Récupérer la coordonnée du bateau en cours
            Coord coordEnVerification = Bateaux[indiceBateau].pos[indiceCaseBateau];

            // Vérifier si le nombre de cases touchées du bateau 1
            if (plateauJeu[coordEnVerification.x][coordEnVerification.y] == 'O')
            {
                toucheBateau1++;
            }
            // Vérifier si le nombre de cases touchées du bateau 2
            else if (plateauJeu[coordEnVerification.x][coordEnVerification.y] == 'X')
            {
                toucheBateau2++;
            }
        }

        // Vérifier si le bateau 1 est coulé entièrement
        if (toucheBateau1 == 4)
        {
            etatPartie = victoireJoueur1;
        }
        // Vérifier si le bateau 2 est coulé entièrement
        else if (toucheBateau2 == 4)
        {
            etatPartie = victoireJoueur2;
        }
    }
}

void afficherResultat(string pseudo1, string pseudo2)
{
    // Vérifier qui a gagné
    if (etatPartie == victoireJoueur1)
    {
        // Afficher le message de victoire du joueur 1
        cout << "### Joueur 1 " << pseudo1 << " : GAGNE en " << nbTirsJoueurs1 << " tirs ###" << endl;
        cout << "### Joueur 2 " << pseudo2 << " : PERD ###" << endl;
    }
    else if (etatPartie == victoireJoueur2)
    {
        // Afficher le message de victoire du joueur 2
        cout << "### Joueur 1 " << pseudo1 << " : PERD ###" << endl;
        cout << "### Joueur 2 " << pseudo2 << " : GAGNE en " << nbTirsJoueur2 << " tirs ###" << endl;
    }
    else if (etatPartie == abandonJoueur1)
    {
        // Afficher le message d'abandon du joueur 1
        cout << "### Joueur 1 " << pseudo1 << " : ABANDON ###" << endl;
        cout << "### Joueur 2 " << pseudo2 << " : GAGNE en " << nbTirsJoueur2 << " tirs ###" << endl;
    }
    else if (etatPartie == abandonJoueur2)
    {
        // Affficher le message d'abandon du joueur 2
        cout << "### Joueur 1 " << pseudo1 << " : GAGNE en " << nbTirsJoueurs1 << " tirs ###" << endl;
        cout << "### Joueur 1 " << pseudo2 << " : ABANDON ###" << endl;
    }
}
