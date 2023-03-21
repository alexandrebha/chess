#pragma once
#include <libTableauNoir.h>

#define DEPARTX -285
#define DEPARTY 285
#define FINX 285
#define FINY -285


//---------------------------------------------------------------------------------------------------------//


typedef enum {VIDE = 0 ,PION = 1, FOU = 2, CAVALIER = 3, TOUR = 4, DAME = 5, ROI = 6} piece_t;

typedef enum {B = 1, N=-1} couleur_t;

typedef enum {ANIMATION=27} animation_t;


//---------------------------------------------------------------------------------------------------------//


//structure qui permet de stocker des images pour le menu
typedef struct menu_s{

  Image fondMenu;
  Image caseInterrogation;
  Image reglesEchecs;
  Image boutonClicGauche;
  Image pieces;
  
  
} menu_t;


// structure qui permet de stocker les variables afin d'effectuer ou non le roque
typedef struct roque_s{

  int tourN_0_0;
  int tourN_0_7;
  int tourB_7_7;
  int tourB_7_0;
  int roiN_0_4;
  int roiB_7_4;

} roque_t;


// structure qui permet de définir une position à partir de coordonnées
typedef struct position_s{
  
  int x;
  int y;
  
} position_t;


// structure qui contient un tableau structuré 
typedef struct echiquier_s{
  
  int t[8][8];
  
} echiquier_t;


// structure qui permet de définir l'état de l'échiquier, et d'initialiser les images
typedef struct etat_s{
  
  echiquier_t echiquier;
  echiquier_t tab;
  roque_t roque;
  Image tableau_Im[13];
  Image echiquier_Im;
  Image rond;
  Image afficher_victoire;
  Image pion_blanc_arrivee;
  Image pion_noir_arrivee;
  Image surligner_piece_choisie;
  
} etat_t;


//---------------------------------------------------------------------------------------------------------//


//déclaration des fonctions et de leurs arguments



void charger_images_menus(menu_t *image);



void liberer_images_menus(menu_t *image);



void menu1(menu_t *image);



void menu2(menu_t *image);



void charger_images(etat_t *adresse_board);



void liberer_images(etat_t *adresse_board);



//fonction qui permet d'afficher l'échiquier et les différentes pièces/images
void afficher(etat_t *adresse_board, position_t depart, int surligner_piece_choisie, int afficher_victoire, int code_mise_a_jour, int couleur);



//fonction qui contrôle la mise à jour des différentes informations qui permettent de déplacer, repérer et afficher les pièces/images sur l'échiquier
int mise_a_jour(etat_t *adresse_board, int x, int y, int game);



//regarde si le pion est sur sa ligne de départ
int depart_pion(int couleur);



//regarde si le pion est sur la ligne d'arrivée en fonction de sa couleur
int pion_arrivee(etat_t *adresse_board, position_t arrivee, int piece, int couleur);



//regarde la pièce voulue (FOU/CAVALIER/TOUR/DAME) lorsque le pion est arrivée sur la ligne d'arrivée
void choisir_piece_arrivee(etat_t *adresse_board, position_t arrivee, int couleur);



int isCheminDiagonaleFini(int direction_x, int direction_y, position_t chemin, position_t arrivee);



int isCheminLigneFini(int direction_x, int direction_y, position_t chemin, position_t arrivee);



int isMemePosition(int x1, int x2, int y1, int y2);



//regarde si les tours et les rois ont déjà bougé
void valider_roque(etat_t *adresse_board);



//regarde si les cases entre le roi et la tour choisie pour effectuer le roque sont libres
int roque(etat_t *adresse_board, int piece, position_t depart, position_t arrivee, int couleur);



//permet d'effectuer le roque(echange les positions des pièces impliquées)
int effectuer_roque(etat_t *adresse_board, int piece, position_t depart, position_t arrivee, int couleur, etat_t save, int resultat_dep, int mouvement_roque, int result_echec);



//deplacement des différentes pièces
int dep_pion(etat_t *adresse_board, int piece, position_t depart, position_t arrivee, int couleur);

int dep_fou(etat_t *adresse_board, position_t depart, position_t arrivee, int couleur);

int dep_cavalier_Blanc(etat_t *adresse_board, position_t depart, position_t arrivee, int couleur);

int dep_cavalier_Noir(etat_t *adresse_board, position_t depart, position_t arrivee, int couleur);

int dep_tour(etat_t *adresse_board, position_t depart, position_t arrivee, int couleur);

int dep_dame(etat_t *adresse_board, position_t depart, position_t arrivee, int couleur);

int dep_roi_Blanc(etat_t *adresse_board, position_t depart, position_t arrivee, int couleur);

int dep_roi_Noir(etat_t *adresse_board, position_t depart, position_t arrivee, int couleur);



//fonction qui permet de vérifier si le déplacement d'une pièce est valide à partir du type de la pièce choisie, de sa position de départ, de sa position d'arrivée ainsi que de sa couleur
int deplacements(etat_t *adresse_board, int piece, position_t depart, position_t arrivee, int couleur);



//regarde si le roi est en échec
int echec_roi(etat_t *adresse_board, int couleur);



//si le roi est en échec : regarder si le roi peut bouger
int echec_mat(etat_t *adresse_board, int couleur);



//surligne les cases potentielles 
echiquier_t surlignerCasesPossibles(etat_t *board, int piece, position_t depart, int couleur);



//renvoie un echiquier vide
echiquier_t echiquier_vide();



//fonction qui créer les animations pour le déplacement d'une pièce ainsi que le déplacement du roque
void animation(etat_t *adresse_board, int piece, position_t depart, position_t arrivee, position_t depart_tour, position_t arrivee_tour, int animation, int couleur);



//renvoie les coordonées à partir de la position
position_t positionToCoord(position_t position);



//regarde si les signes de a et de b sont égaux
int areSignEqual(int a, int b);


//---------------------------------------------------------------------------------------------------------//
