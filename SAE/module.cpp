#include <iostream>
#include "game-tools.h"
#include "module.h"
using namespace std;

// Type énuméré direction
enum UneDirection
{
    Horizontale,
    Verticale,
    Diagonale
};

void afficherEnTete(UnJoueur player1, UnJoueur player2, UnBateau boat[], const unsigned short int NB_BATEAUX, const unsigned short int NB_CASES, int turnPlayer, bool afficheBateaux)
{
    // Afficher le nom du jeu
    cout << "B A T A I L L E   N A V A L E" << endl
         << endl;
    // Afficher le but du jeu
    cout << "Chaque joueur doit couler un bateau de 4 cases (vertical, horizontal ou diagonal)" << endl
         << endl;
    // Afficher les 4 coordonnées des 2 bateaux si les joueurs le souhaitent

    afficherBateau(boat, NB_BATEAUX, afficheBateaux);
    cout << endl
         << endl;

    // Afficher le nom du joueur qui doit jouer
    if (turnPlayer == 0)
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

void afficherTableau(UneCase grille[][TAILLE_TAB], int TAILLE_TAB)
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
                    afficherTexteEnCouleur(grille[i][j].representation, grille[i][j].couleur, false);
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
}

void afficherBateau(UnBateau boats[], const unsigned short int NB_BATEAUX, bool afficheBateaux)
{
    // Parcours des 2 bateaux du tableau Bateaux
    for (int indiceBateau = 0; indiceBateau < NB_BATEAUX; indiceBateau++)
    {
        // Afficher l'en-tête de la ligne
        cout << "Bateau " << (indiceBateau + 1) << (indiceBateau == 0 ? " (O) " : " (X) ") << (afficheBateaux ? " = " : " ");
        // Afficher les coordonnées de tous les points du bateau
        if (afficheBateaux)
        {
            for (int coordBateau = 0; coordBateau < NB_CASES_BATEAU; coordBateau++)
            {
                cout << " (" << char(boats[indiceBateau].pos[coordBateau].y + 64) << "," << boats[indiceBateau].pos[coordBateau].x << ")";
            }
        }
        cout << endl;
    }
}

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
    // Variables locales
    int indiceDirection;        // Indice permettant de générer la direction du bateau
    int X;                      // Position horizontale dans le tableau
    int Y;                      // Position verticale dans le tableau
    UneDirection directionElue; // Direction choisie aléatoirement
    bool bateauValide;          // Indicateur de validité d'un bateau
    const unsigned short int INDICE_MIN_BATEAU = 1;

    // Vérifier quel bateau on génère
    if (NB_BATEAUX <= indexBateau)
    {
        return;
    }

    do
    {
        // Générer des coordonnées
        X = random(INDICE_MIN_BATEAU, NB_CASES);
        Y = random(INDICE_MIN_BATEAU, NB_CASES);

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
            if (X + NB_CASES_BATEAU - INDICE_MIN_BATEAU > NB_CASES)
            {
                X = NB_CASES - NB_CASES_BATEAU + INDICE_MIN_BATEAU;
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

void verifBateauToucher(UnBateau Bat[], UneCase grille[][TAILLE_TAB], int ligne, int colonne, const unsigned short int NB_BATEAUX, const unsigned short int NB_CASES, int turnPlayer, UnJoueur &player1, UnJoueur &player2)
{
    // Variables Locales
    int bateauToucher = 0;                        // 0 = non, 1 = joueur 1, 2 = joueur2
    const unsigned short int INDICE_BATEAU_1 = 1; // Indice du bateau 1
    const unsigned short int INDICE_BATEAU_2 = 2; // Indice du bateau 1
    const unsigned short int INDICE_0 = 0;        // Indice 0

    // Parcourir les bateaux
    for (int indiceBateau = INDICE_0; indiceBateau < NB_BATEAUX; indiceBateau++)
    {
        // Parcourir les coordonnées de chaque bateau
        for (int indiceCaseBateau = INDICE_0; indiceCaseBateau < NB_CASES_BATEAU; indiceCaseBateau++)
        {
            // Vérifier si le tir du joueur touche un bateau
            if (Bat[indiceBateau].pos[indiceCaseBateau].x == ligne && Bat[indiceBateau].pos[indiceCaseBateau].y == colonne)
            {
                // Vérifier si le bateau touché est le bateau 1
                if (indiceBateau == INDICE_0)
                {
                    bateauToucher = INDICE_BATEAU_1;
                }
                // Vérifier si le bateau touché est le bateau 2
                else
                {
                    bateauToucher = INDICE_BATEAU_2;
                }
                break;
            }
        }
        // Sortir de la boucle si un bateau est touché avant la fin de celle ci
        if (bateauToucher == INDICE_BATEAU_1 || bateauToucher == INDICE_BATEAU_2)
        {
            break;
        }
    }

    // Mettre à jour la grille en fonction du tir du joueur
    // Afficher un point si le joueur tire dans l'eau
    if (bateauToucher == INDICE_0)
    {
        grille[ligne][colonne].representation = '.';
        if (turnPlayer == 0)
        {
            grille[ligne][colonne].couleur = player1.couleurChoisie;
        }
        else
        {
            grille[ligne][colonne].couleur = player2.couleurChoisie;
        }
    }
    // Afficher un O si le joueur touche le bateau 1
    else if (bateauToucher == INDICE_BATEAU_1)
    {
        grille[ligne][colonne].representation = 'O';
        if (turnPlayer == 0)
        {
            grille[ligne][colonne].couleur = player1.couleurChoisie;
            player1.toucheBateau2++;
        }
        else
        {
            grille[ligne][colonne].couleur = player2.couleurChoisie;
            player2.toucheBateau2++;
        }
    }
    // Afficher un X si le joueur touche le bateau 2
    else if (bateauToucher == INDICE_BATEAU_2)
    {
        grille[ligne][colonne].representation = 'X';
        if (turnPlayer == 0)
        {
            grille[ligne][colonne].couleur = player1.couleurChoisie;
            player1.toucheBateau2++;
        }
        else
        {
            grille[ligne][colonne].couleur = player2.couleurChoisie;
            player2.toucheBateau2++;
        }
    }
}

void saisieInformations(UnJoueur &player1, UnJoueur &player2, bool &afficheBateaux)
{
    // Variable locale
    char retourJoueur; // Retour du joueur quant à l'affichage des règles
    bool valideSaisie; // indicateur de validité de la saisie

    // Traitements
    // Initialisation de l'indicateur
    valideSaisie = true;

    // Saisie du nom des joueurs
    cout << "Quel est le nom du joueur 1 : ";
    cin >> player1.nom;
    cout << "Quel est le nom du joueur 2 : ";
    cin >> player2.nom;

    for (int i = 0; i < 2; i++)
    {
        string couleurChoisie;

        cout << "Quelle couleur pour le joueur " << i + 1 << " ? ";
        cin >> couleurChoisie;

        if (couleurChoisie == "R" || couleurChoisie == "Rouge" || couleurChoisie == "rouge")
        {
            if (i == 0)
            {
                player1.couleurChoisie = rouge;
            }
            else
            {
                player2.couleurChoisie = rouge;
            }
        }
        if (couleurChoisie == "B" || couleurChoisie == "Bleu" || couleurChoisie == "bleu")
        {
            if (i == 0)
            {
                player1.couleurChoisie = bleu;
            }
            else
            {
                player2.couleurChoisie = bleu;
            }
        }
        if (couleurChoisie == "V" || couleurChoisie == "Vert" || couleurChoisie == "vert")
        {
            if (i == 0)
            {
                player1.couleurChoisie = vert;
            }
            else
            {
                player2.couleurChoisie = vert;
            }
        }
        if (couleurChoisie == "C" || couleurChoisie == "Cyan" || couleurChoisie == "cyan")
        {
            if (i == 0)
            {
                player1.couleurChoisie = cyan;
            }
            else
            {
                player2.couleurChoisie = cyan;
            }
        }
        if (couleurChoisie == "V" || couleurChoisie == "Violet" || couleurChoisie == "violet")
        {
            if (i == 0)
            {
                player1.couleurChoisie = violet;
            }
            else
            {
                player2.couleurChoisie = violet;
            }
        }
    }

    // Saisie-vérif de la volonté d'afficher les bateaux
    while (true)
    {
        // Saisie de la volonté
        cout << "Voulez-vous que les coordonnées des bateaux soient affichées ? ('O'/'N')";
        cin >> retourJoueur;

        if (retourJoueur == 'n' || retourJoueur == 'o' || retourJoueur == 'N' || retourJoueur == 'O')
        {
            // Attribution de la volonté à un indicateur
            if (retourJoueur == 'n' || retourJoueur == 'N')
            {
                afficheBateaux = false;
            }
            break;
        }
        else
        {
            // Afficher le message d'erreur
            afficherTexteEnCouleur("Saisie incorrecte, Recommencez !", rouge, true);
        }
    }
}

void resetPlateau(UneCase grille[][TAILLE_TAB], unsigned short int NB_CASES)
{
    // Réinitialiser toutes les cases du tableau
    for (unsigned short int ligne = 0; ligne < NB_CASES + 1; ligne++)
    {
        for (unsigned short int colonne = 0; colonne < NB_CASES + 1; colonne++)
        {
            grille[ligne][colonne].representation = '\0';
        }
    }
}

void nouveauTour(UnJoueur &player1, UnJoueur &player2, int tourJoueur, UnBateau tabBateaux[], UneCase grille[][TAILLE_TAB], int nbBateaux, int nbCases)
{
    // Variables locales
    string action;     // Stockage du tir du joueur, ou de son abandon
    bool valideSaisie; // Indicateur de validité de la saisie du joueur

    // Initialisation
    // Initialiser l'indicateur de validité
    valideSaisie = false;

    // Traitements
    // Saisie-verification avec message d'erreur de la cible du tir par l'utilisisateur
    while (true)
    {
        if (player2.nbTirs < 1)
        {
            cout << "Votre 1er tir (ex. A3) ou abandonner (@@) ? ";
        }
        else
        {
            cout << "Votre " << player2.nbTirs + 1 << "eme tir (ex. A3) ou abandonner (@@) ? ";
        }
        cin >> action;

        // Vérifier l'abandon du joueur
        if (action == "@@")
        {
            // Vérifier si le joueur 1 abandonne
            if (tourJoueur == 0)
            {
                player1.etat = abandonne;
                break;
            }
            // Vérifier si le joueur 2 abandonne
            else
            {
                player2.etat = abandonne;
                break;
            }
        }
        else
        {
            // Variables
            int ligne = (int)action[1] - 48;
            int colonne = int(action[0]) - 64;

            // Vérifier que le tir est valide
            if (action.length() == 2 && colonne > 0 && colonne < 10 && ligne > 0 && ligne < 10)
            {
                // Vérifier si le tir du joueur touche un bateau
                verifBateauToucher(tabBateaux, grille, ligne, colonne, nbBateaux, nbCases, tourJoueur, player1, player2);

                // Mettre à jour le nombre de tirs du joueur 1
                if (tourJoueur == 0)
                {
                    player1.nbTirs++;
                }
                // Mettre à jour le nombre de tirs du joueur 2
                else
                {
                    player2.nbTirs++;
                }

                // Sortir de la boucle
                break;
            }
            else
            {
                if ((ligne < 65 || ligne > 73) && (colonne > 0 && colonne < 10))
                {
                    // Afficher le message d'erreur
                    cout << "### Erreur en Y ###" << endl;
                }
                else if (colonne < 0 || colonne > 9)
                {
                    // Afficher le message d'erreur
                    cout << "### Erreur en X ###" << endl;
                }
            }
        }
    }
}

void verifierGagnant(UnBateau Bato[], UneCase grille[][TAILLE_TAB], UnJoueur &player1, UnJoueur &player2, const unsigned short int NB_BATEAUX)
{
    // Variables locales
    int toucheBateau1 = 0;             // Nombre de tirs touchant le bateau 1
    int toucheBateau2 = 0;             // Nombre de tirs touchant le bateau 2
    UneCoordonnee coordEnVerification; // Coordonée en cours d'analyse

    // Parcours des 2 bateaux
    for (int indiceBateau = 0; indiceBateau < NB_BATEAUX; indiceBateau++)
    {
        // Parcours des coordonnées des 2 bateaux
        for (int indiceCaseBateau = 0; indiceCaseBateau < NB_CASES_BATEAU; indiceCaseBateau++)
        {
            // Récupérer la coordonnée du bateau en cours
            UneCoordonnee coordEnVerification = Bato[indiceBateau].pos[indiceCaseBateau];

            // Vérifier si le nombre de cases touchées du bateau 1
            if (grille[coordEnVerification.x][coordEnVerification.y].representation == 'O')
            {
                toucheBateau1++;
            }
            // Vérifier si le nombre de cases touchées du bateau 2
            else if (grille[coordEnVerification.x][coordEnVerification.y].representation == 'X')
            {
                toucheBateau2++;
            }
        }

        // Vérifier si le bateau 1 est coulé entièrement
        if (toucheBateau1 == NB_CASES_BATEAU)
        {
            player1.etat = gagne;
        }
        // Vérifier si le bateau 2 est coulé entièrement
        if (toucheBateau2 == NB_CASES_BATEAU)
        {
            player2.etat = gagne;
        }
    }
}

void afficherResultat(UnJoueur player1, UnJoueur player2)
{
    // Vérifier qui a gagné
    switch (player1.etat)
    {
    case gagne:
        // Vérifier si les joueurs ont une égalité
        if (player1.etat == player2.etat)
        {
            cout << "Les deux bateaux sont coules, on a donc une egalite";
        }
        else
        {
            // Afficher le message de victoire du joueur 1
            cout << "### Joueur 1 " << player1.nom << " : GAGNE en " << player1.nbTirs << " tirs, dont " << player1.toucheBateau1 << (player1.toucheBateau1 == 1 ? " tir" : " tirs") << " sur le bateau 1 ###" << endl;
            cout << "### Joueur 2 " << player2.nom << " : PERD ###" << endl;
        }
        break;
    case abandonne:
        // Vérifier si les 2 joueurs ont une égalité
        if (player1.etat == player2.etat)
        {
            cout << "Les 2 joueurs abandonnent, on a donc une egalite";
        }
        // Afficher le message d'abandon du joueur 1
        else
        {
            cout << "### Joueur 1 " << player1.nom << " : ABANDON ###" << endl;
            cout << "### Joueur 2 " << player2.nom << " : GAGNE en " << player2.nbTirs << "tirs, dont " << player2.toucheBateau2 << (player2.toucheBateau2 == 1 ? " tir" : " tirs") << " sur le bateau 2 ###" << endl;
        }
        break;
    case enJeu:
        // Afficher le message de victoire du joueur 2
        if (player2.etat == gagne)
        {
            cout << "### Joueur 1 " << player1.nom << " : PERD ###" << endl;
            cout << "### Joueur 2 " << player2.nom << " : GAGNE en " << player2.nbTirs << " tirs, dont " << player2.toucheBateau2 << (player2.toucheBateau2 == 1 ? " tir" : " tirs") << " sur le bateau 2 ###" << endl;
        }
        // Afficher l'abandon du joueur 2
        if (player2.etat == abandonne)
        {
            cout << "### Joueur 1 " << player1.nom << " : GAGNE en " << player1.nbTirs << " tirs, dont " << player1.toucheBateau1 << (player1.toucheBateau1 == 1 ? " tir" : " tirs") << " sur le bateau 1 ###" << endl;
            cout << "### Joueur 2 " << player2.nom << " : ABANDON ###" << endl;
        }
    }
}