/*
programme : batailleNavale
But : Jouer à la bataille navale
*/

#include <iostream>
#include "game-tools.h"
#include "module.h"
using namespace std;

// Déclaration des sous-programmes


int main(void)
{

    // Variables
    UnJoueur joueur1;     // Informations du joueur 1
    UnJoueur joueur2;     // Informations du joueur 2
    int indexBateau;      // Index du bateau en cours de traitement dans le tableau des bateaux
    int tourJoueur;       // Joueur qui doit jouer
    bool affichageRegles; // Indicateur de la volonté des joueurs à afficher les règles
    char rejouerPartie;
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
    cout << "Souhaitez-vous en rejouer une ? (O/N) ";
    cin >> rejouerPartie;

    // Vérifier la saisie
    if (rejouerPartie == 'o' || rejouerPartie == 'O')
    {
        // Effacer le contenu du terminal puis rejouer la partie
        effacer();
        main();
    }

    return 0;
}

// Définition des sous-programmes


