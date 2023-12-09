/*
programme : batailleNavale
But : Jouer à la bataille navale
*/

#include <iostream>
#include "game-tools.h"
#include "module.h"
using namespace std;

// Déclaration des sous-programmes
void nouveauTour(UnJoueur &player1, UnJoueur &player2, int tourJoueur, UnBateau tabBateaux[], char grille[][TAILLE_TAB], int nbBateaux, int nbCases); // A completer
// But : Proposer un joueur de tirer et vérifier celui-ci
void verifierGagnant(UnBateau Bato[], char grille[][TAILLE_TAB], UnJoueur &player1, UnJoueur &player2, const unsigned short int NB_BATEAUX);
// But : Vérifier si un des joueurs gagne ou si la partie continue
void afficherResultat(UnJoueur player1, UnJoueur player2);
// But : Afficher le résultat de la partie

int main(void)
{

    // Variables
    UnJoueur joueur1;     // Informations du joueur 1
    UnJoueur joueur2;     // Informations du joueur 2
    int indexBateau;      // Index du bateau en cours de traitement dans le tableau des bateaux
    int tourJoueur;       // Joueur qui doit jouer
    bool affichageRegles; // Indicateur de la volonté des joueurs à afficher les règles
    string rejouerPartie;
    const unsigned short int NB_CASES = 9; // Taille du tableau horizontalement et verticalement
    char plateauJeu[NB_CASES][NB_CASES];   // Tableau contenant le plateau de jeu

    const unsigned short int NB_BATEAUX = 2; // Nombre de bateaux pris en compte
    UnBateau bateaux[NB_BATEAUX];

    // Initialisation de la partie
    // Initialisation des variables
    indexBateau = 0;
    tourJoueur = 0;
    affichageRegles = true;

    // Réinitialiser le plateau de jeu
    resetPlateau(plateauJeu, NB_CASES);

    // Saisie du nom des joueurs
    saisieInformations(joueur1, joueur2, affichageRegles);

    // Génération des bateaux
    genererBateau(bateaux, indexBateau, NB_BATEAUX, NB_CASES);

    // Jouer la partie
    do
    {
        // Nettoyer le terminal entre les 2 tours
        effacer();

        // Afficher les informations pour les joueurs
        afficherEnTete(joueur1, joueur2, bateaux, NB_BATEAUX, NB_CASES, tourJoueur, affichageRegles);

        // Afficher la grille avant le tir du joueur
        afficherTableau(plateauJeu, NB_CASES);

        // Inviter le joueur concerné à effectuer son tir, et vérifier le résultat de celui ci
        nouveauTour(joueur1, joueur2, tourJoueur, bateaux, plateauJeu, NB_BATEAUX, NB_CASES);

        // Vérifier si un des joueurs a gagné la partie
        verifierGagnant(bateaux, plateauJeu, joueur1, joueur2, NB_BATEAUX);

        // Changement du tours entre les deux joueurs
        tourJoueur = (tourJoueur + 1) % 2;
    } while (!((joueur1.etat != enJeu || joueur2.etat != enJeu) && tourJoueur == 0));

    // Nettoyer le terminal
    effacer();

    // Afficher les informations pour les joueurs
    afficherEnTete(joueur1, joueur2, bateaux, NB_BATEAUX, NB_CASES, tourJoueur, affichageRegles);

    // Afficher la grille avant le tir du joueur
    afficherTableau(plateauJeu, NB_CASES);

    // Si la partie est terminée, afficher le résultat
    afficherResultat(joueur1, joueur2);

    // Demander au joueur s'il veut rejouer
    cout << "Souhaitez-vous en rejouer une ? ";
    cin >> rejouerPartie;

    // Vérifier la saisie
    if (rejouerPartie == "o" || rejouerPartie == "O")
    {
        // Effacer le contenu du terminal puis rejouer la partie
        effacer();
        main();
    }

    return 0;
}

// Définition des sous-programmes

void nouveauTour(UnJoueur &player1, UnJoueur &player2, int tourJoueur, UnBateau tabBateaux[], char grille[][TAILLE_TAB], int nbBateaux, int nbCases)
{
    // Variables locales
    string action;     // Stockage du tir du joueur, ou de son abandon
    bool valideSaisie; // Indicateur de validité de la saisie du joueur

    // Initialisation
    // Initialiser l'indicateur de validité
    valideSaisie = false;

    // Traitements
    // Saisie-verification avec message d'erreur de la cible du tir par l'utilisisateur
    do
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
                valideSaisie = true;
            }
            // Vérifier si le joueur 2 abandonne
            else
            {
                player2.etat = abandonne;
                valideSaisie = true;
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
                // Mettre à jour l'indicateur de validité du tir
                valideSaisie = true;

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
    } while (valideSaisie == false);
}

void verifierGagnant(UnBateau Bato[], char grille[][TAILLE_TAB], UnJoueur &player1, UnJoueur &player2, const unsigned short int NB_BATEAUX)
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
            if (grille[coordEnVerification.x][coordEnVerification.y] == 'O')
            {
                toucheBateau1++;
            }
            // Vérifier si le nombre de cases touchées du bateau 2
            else if (grille[coordEnVerification.x][coordEnVerification.y] == 'X')
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
