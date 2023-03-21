#include <stdio.h>
#include <stdlib.h>
#include "Echecs.h"
#include <string.h>
#include <math.h>
#include <libTableauNoir.h>


//---------------------------------------------------------------------------------------------------------//


int main(){

  creerTableau();
  fixerModeBufferisation(1);
  fixerTaille(700,700);
  //initialisation de l'état de l'échiquier (board)
  etat_t board={.echiquier={{{ TOUR*N, CAVALIER*N,  FOU*N, DAME*N,  ROI*N,  FOU*N, CAVALIER*N, TOUR*N},
			     { PION*N,     PION*N, PION*N, PION*N, PION*N, PION*N,     PION*N, PION*N},
			     {   VIDE,       VIDE,   VIDE,   VIDE,   VIDE,   VIDE,       VIDE,   VIDE},
			     {   VIDE,       VIDE,   VIDE,   VIDE,   VIDE,   VIDE,       VIDE,   VIDE},
			     {   VIDE,       VIDE,   VIDE,   VIDE,   VIDE,   VIDE,       VIDE,   VIDE},
			     {   VIDE,       VIDE,   VIDE,   VIDE,   VIDE,   VIDE,       VIDE,   VIDE},
			     { PION*B,     PION*B, PION*B, PION*B, PION*B, PION*B,     PION*B, PION*B},
			     { TOUR*B, CAVALIER*B,  FOU*B, DAME*B,  ROI*B,  FOU*B, CAVALIER*B, TOUR*B}}}};
  board.roque.tourN_0_0=0;
  board.roque.tourN_0_7=0;
  board.roque.tourB_7_0=0;
  board.roque.tourB_7_7=0;
  board.roque.roiN_0_4=0;
  board.roque.roiB_7_4=0;
  menu_t image;
  charger_images_menus(&image);
  menu1(&image);
  menu2(&image);
  charger_images(&board);  
  afficher(&board, (position_t) {0, 0}, 0, 2, 0, 0);
  tamponner();
  int couleur_joueur=B;
  int code_mise_a_jour=0;
  int afficher_victoire=0;
  int x, y;
  EtatSourisClavier esc;
  while((couleur_joueur)&&(!fermetureDemandee())){
    afficher_victoire=0;    
    attendreNms(250);
    attendreClicGauche();
    esc=lireEtatSourisClavier();
    x=esc.sourisX;
    y=esc.sourisY;  
    code_mise_a_jour=mise_a_jour(&board, x, y, couleur_joueur);
    //changements de tours si et seulement si le déplacement d'une pièce est effectué et est donc valide
    if((couleur_joueur==B)&&((code_mise_a_jour==1)||(code_mise_a_jour>3)||(code_mise_a_jour<-3))){
      couleur_joueur=N;
    }
    else if((couleur_joueur==N)&&((code_mise_a_jour==1)||(code_mise_a_jour>3)||(code_mise_a_jour<-3))){
      couleur_joueur=B;
    }
    if(code_mise_a_jour==3){
      afficher_victoire=1;
    }    
    afficher(&board, (position_t) {0, 0}, 0, afficher_victoire, code_mise_a_jour, couleur_joueur);
    tamponner();
    effacerTableau();   
    if(afficher_victoire==1){
      couleur_joueur=0;
    }
  }
  liberer_images(&board);
  liberer_images_menus(&image);
  attendreFermeture();
  fermerTableau();
  
  return EXIT_SUCCESS;
}


//---------------------------------------------------------------------------------------------------------//


void charger_images_menus(menu_t *image){
  
  image->fondMenu=chargerImage("Fond_Menu.png");
  image->caseInterrogation=chargerImage("Case_Interrogation.png");
  image->reglesEchecs=chargerImage("Regles_Echecs.png");
  image->boutonClicGauche=chargerImage("Bouton_Clic_Gauche.png");
  image->pieces=chargerImage("Pieces.png");
  
}


//---------------------------------------------------------------------------------------------------------//


void liberer_images_menus(menu_t *image){
  
  libererImage(image->fondMenu);
  libererImage(image->caseInterrogation);
  libererImage(image->reglesEchecs);
  libererImage(image->boutonClicGauche);
  libererImage(image->pieces);

}


//---------------------------------------------------------------------------------------------------------//


void menu1(menu_t *image){

  int fin_boucle=1;
  afficherImage(image->fondMenu, -350, 350);
  afficherImage(image->caseInterrogation, -350, 350);
  afficherImage(image->boutonClicGauche, -350, 350);
  tamponner();
  
  EtatSourisClavier esc=lireEtatSourisClavier();
  while(fin_boucle==1){
    esc=lireEtatSourisClavier();
    if((esc.sourisX>-296)&&(esc.sourisX<-202)&&(esc.sourisY<325)&&(esc.sourisY>225)){
      afficherImage(image->reglesEchecs, -350, 350);
      tamponner();
      while((esc.sourisX>-301)&&(esc.sourisX<311)&&(esc.sourisY<339)&&(esc.sourisY>7)){
	esc=lireEtatSourisClavier();
      }
      effacerTableau();
      afficherImage(image->fondMenu, -350, 350);
      afficherImage(image->caseInterrogation, -350, 350);
      afficherImage(image->boutonClicGauche, -350, 350);
      tamponner();
    }
    if((esc.sourisBoutonGauche)&&(esc.sourisX>258)&&(esc.sourisX<329)&&(esc.sourisY<-264)&&(esc.sourisY>-337)){
      esc=lireEtatSourisClavier();
      fin_boucle=0;
    }
    if(fermetureDemandee()){
      fin_boucle=0;
    }
  }
  attendreNms(100);
  
}


//---------------------------------------------------------------------------------------------------------//


void menu2(menu_t *image){

  afficherImage(image->pieces, -350, 350);
  tamponner();

  EtatSourisClavier esc=lireEtatSourisClavier();
  while((!((esc.sourisBoutonGauche)&&(esc.sourisX>243)&&(esc.sourisX<314)&&(esc.sourisY<326)&&(esc.sourisY>253)))){
    esc=lireEtatSourisClavier();
    if(fermetureDemandee()){
      esc.sourisBoutonGauche=1;
    }
  } 
  
}


//---------------------------------------------------------------------------------------------------------//


void charger_images(etat_t *adresse_board){

  adresse_board->echiquier_Im=chargerImage("MON_echiquier_vide.png");
  
  adresse_board->tableau_Im[PION+6]=chargerImage("Pion_blanc.png");
  adresse_board->tableau_Im[-PION+6]=chargerImage("Pion_noir.png");
  adresse_board->tableau_Im[FOU+6]=chargerImage("Fou_blanc.png");
  adresse_board->tableau_Im[-FOU+6]=chargerImage("Fou_noir.png");
  adresse_board->tableau_Im[CAVALIER+6]=chargerImage("Cavalier_blanc.png");
  adresse_board->tableau_Im[-CAVALIER+6]=chargerImage("Cavalier_noir.png");
  adresse_board->tableau_Im[TOUR+6]=chargerImage("Tour_blanc.png");
  adresse_board->tableau_Im[-TOUR+6]=chargerImage("Tour_noir.png");
  adresse_board->tableau_Im[DAME+6]=chargerImage("Dame_blanc.png");
  adresse_board->tableau_Im[-DAME+6]=chargerImage("Dame_noir.png");
  adresse_board->tableau_Im[ROI+6]=chargerImage("Roi_blanc.png");
  adresse_board->tableau_Im[-ROI+6]=chargerImage("Roi_noir.png");
  adresse_board->pion_blanc_arrivee=chargerImage("pion_blanc_arrivee.png");
  adresse_board->pion_noir_arrivee=chargerImage("pion_noir_arrivee.png");
  adresse_board->rond=chargerImage("Rond.png");
  adresse_board->afficher_victoire=chargerImage("afficher_victoire.png");
  adresse_board->surligner_piece_choisie=chargerImage("surligner_piece_choisie.png");

  //redimensionner les images à la taille d'une case de l'échiquier
  int i;
  for(i=0;i<13;i++){
    if(i!=6){
      adresse_board->tableau_Im[i]=rotozoomImage(adresse_board->tableau_Im[i], 0, 70./tn_largeur(adresse_board->tableau_Im[i]), 70./tn_hauteur(adresse_board->tableau_Im[i]));
    }
  }
  
  adresse_board->rond=rotozoomImage(adresse_board->rond, 0, 70./tn_largeur(adresse_board->rond), 70./tn_hauteur(adresse_board->rond));
  
}


//---------------------------------------------------------------------------------------------------------//


void liberer_images(etat_t *adresse_board){

  libererImage(adresse_board->echiquier_Im);

  libererImage(adresse_board->tableau_Im[-PION+6]);
  libererImage(adresse_board->tableau_Im[-PION+6]);
  libererImage(adresse_board->tableau_Im[FOU+6]);
  libererImage(adresse_board->tableau_Im[-FOU+6]);
  libererImage(adresse_board->tableau_Im[CAVALIER+6]);
  libererImage(adresse_board->tableau_Im[-CAVALIER+6]);
  libererImage(adresse_board->tableau_Im[TOUR+6]);
  libererImage(adresse_board->tableau_Im[-TOUR+6]);
  libererImage(adresse_board->tableau_Im[DAME+6]);
  libererImage(adresse_board->tableau_Im[-DAME+6]);
  libererImage(adresse_board->tableau_Im[ROI+6]);
  libererImage(adresse_board->tableau_Im[-ROI+6]);
  libererImage(adresse_board->pion_blanc_arrivee);
  libererImage(adresse_board->pion_noir_arrivee);
  libererImage(adresse_board->rond);
  libererImage(adresse_board->afficher_victoire);
  libererImage(adresse_board->surligner_piece_choisie);
  
}


//---------------------------------------------------------------------------------------------------------//


void afficher(etat_t *adresse_board, position_t depart, int surligner_piece_choisie, int afficher_victoire, int code_mise_a_jour, int couleur){
  
  int i, j; 
  afficherImage(adresse_board->echiquier_Im, -350, 350);
  
  if(surligner_piece_choisie==1){
    afficherImage(adresse_board->surligner_piece_choisie, DEPARTX + 71*depart.x, DEPARTY - 71*depart.y);
  }
  
  for(i=0;i<8;i++){
    for(j=0;j<8;j++){

      if(adresse_board->tab.t[i][j]!=0){
	afficherImage(adresse_board->rond, DEPARTX + 71*j, DEPARTY - 71*i);
      }   
      if(adresse_board->echiquier.t[i][j]!=VIDE){
	Image p=adresse_board->tableau_Im[adresse_board->echiquier.t[i][j]+6];
	afficherImage(p, DEPARTX + 71*j, DEPARTY - 71*i);
      }    
      
    }
  }

  if(afficher_victoire==1){
    attendreNms(250);
    afficherImage(adresse_board->afficher_victoire, -200, 150);
  }
  
}


//---------------------------------------------------------------------------------------------------------//

 
int mise_a_jour(etat_t *adresse_board, int x, int y, int couleur){

  int result_echec=0;
  int result_echec_mat=0;
  int mouvement_roque=0;
  //calcul de la position du clic de l'utilisateur permettant de "renvoyer" la position de la case
  position_t depart=(position_t) {x, y};
  depart.x=floor((x-DEPARTX)/71);
  depart.y=-floor((y-DEPARTY)/71);
  int piece_acceptee;
  if(couleur==B){
    piece_acceptee=((adresse_board->echiquier.t[depart.y][depart.x]>=PION*couleur)&&(adresse_board->echiquier.t[depart.y][depart.x]<=ROI*couleur));
  }
  else if(couleur==N){
    piece_acceptee=((adresse_board->echiquier.t[depart.y][depart.x]<=PION*couleur)&&(adresse_board->echiquier.t[depart.y][depart.x]>=ROI*couleur));
  }
  else {
    piece_acceptee=0;
  }
  //permet de vérifier sur quel type de pièce l'utilisateur a cliqué et s'il a cliqué ou non sur l'échiquier
  if((adresse_board->echiquier.t[depart.y][depart.x]!=VIDE)&&(piece_acceptee)
     &&(x>DEPARTX)&&(x<FINX)&&(y<DEPARTY)&&(y>FINY)){
    int piece=adresse_board->echiquier.t[depart.y][depart.x];
    etat_t save=*adresse_board;
    EtatSourisClavier new_esc=lireEtatSourisClavier();
    int new_x;
    int new_y;
    effacerTableau();
    echiquier_t tab;
    tab=adresse_board->tab=surlignerCasesPossibles(adresse_board, piece, depart, couleur);
    while(!new_esc.sourisBoutonGauche){   
      new_esc=lireEtatSourisClavier();
      new_x=new_esc.sourisX;
      new_y=new_esc.sourisY;
      afficher(adresse_board, depart, 1, 0, 0, 0);
      tamponner();
      effacerTableau();
    }    
    attendreClicGauche();
    position_t arrivee=(position_t) {new_x, new_y};
    arrivee.x=floor((new_x-DEPARTX)/71);
    arrivee.y=-floor((new_y-DEPARTY)/71);    
    int resultat_dep;
    resultat_dep=deplacements(adresse_board, piece, depart, arrivee, couleur);
    if(((resultat_dep==ANIMATION)||(resultat_dep==2)||(resultat_dep==-2)||(resultat_dep==1))
       &&(new_x>DEPARTX)&&(new_x<FINX)&&(new_y<DEPARTY)&&(new_y>FINY)){
      adresse_board->tab=echiquier_vide();
      adresse_board->echiquier.t[depart.y][depart.x]=VIDE;
      animation(adresse_board, piece, depart, arrivee, (position_t) {0,0}, (position_t) {0,0}, VIDE, couleur);    
      adresse_board->echiquier.t[arrivee.y][arrivee.x]=piece;
      adresse_board->tab=tab;
      result_echec=echec_roi(adresse_board, couleur);
      if(result_echec!=0){
	*adresse_board=save;		
	result_echec_mat=echec_mat(adresse_board, couleur);	
	if(result_echec_mat==3){	  
	  adresse_board->echiquier.t[depart.y][depart.x]=piece;
	  afficher(adresse_board, (position_t) {0, 0}, 0, 1, 0, 0);
	  return 3;
	}
	return 0;
      } 
      valider_roque(adresse_board);   
      if((resultat_dep==2)||(resultat_dep==-2)){

	adresse_board->tab=echiquier_vide();
	choisir_piece_arrivee(adresse_board, arrivee, couleur);
	return 15;
      }
      adresse_board->tab=echiquier_vide(); 
      return 1;      
    }    
    //permet d'afficher la pièce sur son ancienne position si le déplacement n'est pas validé ou si le clic n'a pas été effectué sur l'échiquier
    if(resultat_dep==0){
      adresse_board->echiquier.t[depart.y][depart.x]=piece;
      adresse_board->tab=echiquier_vide();
    }    
    result_echec=echec_roi(adresse_board, couleur);
    mouvement_roque=roque(adresse_board, piece, depart, arrivee, couleur);
    int result_roque=0;
    if(result_echec==0){
      result_roque=effectuer_roque(adresse_board, piece, depart, arrivee, couleur, save, resultat_dep, mouvement_roque, result_echec);
      return result_roque;
    }
    if(result_echec!=0){
      adresse_board->tab=echiquier_vide();
      result_echec_mat=echec_mat(adresse_board, couleur);
      if(result_echec_mat==3){
	adresse_board->echiquier.t[depart.y][depart.x]=piece;
	afficher(adresse_board, (position_t) {0, 0}, 0, 1, 0, 0);
	return 3;
      }
      return 0;
    }  
  }
  adresse_board->tab=echiquier_vide();
  return 0;
}


//---------------------------------------------------------------------------------------------------------//


int depart_pion(int couleur){  
  
  if(couleur==N){
    return 1;
  }
  
  else if(couleur==B){
    return 6;
  } 

  return 0;
}


//---------------------------------------------------------------------------------------------------------//

int pion_arrivee(etat_t *adresse_board, position_t arrivee, int piece, int couleur){
  
  EtatSourisClavier esc=lireEtatSourisClavier();
  int esc_x=esc.sourisX;
  int esc_y=esc.sourisY;
  arrivee.x=floor((esc_x-DEPARTX)/71);
  arrivee.y=-floor((esc_y-DEPARTY)/71);
  
  if(piece==PION*couleur){
    if(arrivee.y==0){
      return 2;
    }
    else if(arrivee.y==7){
      return -2;
    }
  }
  
  return 0;
}

//---------------------------------------------------------------------------------------------------------//


void choisir_piece_arrivee(etat_t *adresse_board, position_t arrivee, int couleur){

  EtatSourisClavier esc=lireEtatSourisClavier();
  position_t souris;
  int fin_boucle=1;
  
  effacerTableau();
  attendreNms(250);
  afficher(adresse_board, (position_t) {0, 0}, 0, 0, 0, couleur);
  
  if(couleur==B){
    afficherImage(adresse_board->pion_blanc_arrivee, 296, 150);
  }
  else if(couleur==N){
    afficherImage(adresse_board->pion_noir_arrivee, 296, 150);
  }

  tamponner();
  
  while(fin_boucle==1){
    
    attendreClicGauche();
    esc=lireEtatSourisClavier();
    souris.x=esc.sourisX;
    souris.y=esc.sourisY;

    if(((souris.x<345)&&(souris.x>296))&&((souris.y<150)&&(souris.y>75))){
      adresse_board->echiquier.t[arrivee.y][arrivee.x]=DAME*couleur;
      fin_boucle=0;
    }
    else if(((souris.x<345)&&(souris.x>296))&&((souris.y<76)&&(souris.y>0))){
      adresse_board->echiquier.t[arrivee.y][arrivee.x]=TOUR*couleur;
      fin_boucle=0;	
    }
    else if(((souris.x<345)&&(souris.x>296))&&((souris.y<0)&&(souris.y>-75))){
      adresse_board->echiquier.t[arrivee.y][arrivee.x]=CAVALIER*couleur;
      fin_boucle=0; 
    }
    else if(((souris.x<345)&&(souris.x>296))&&((souris.y<-75)&&(souris.y>-150))){
      adresse_board->echiquier.t[arrivee.y][arrivee.x]=FOU*couleur;
      fin_boucle=0;
    }
    
  }
}


//---------------------------------------------------------------------------------------------------------//


int isCheminDiagonaleFini(int direction_x, int direction_y, position_t chemin, position_t arrivee){
  
  if((direction_x==-1)&&(direction_y==1)){
    return (chemin.x<=arrivee.x)&&(chemin.y>=arrivee.y);
  }
  else if((direction_x==1)&&(direction_y==-1)){
    return (chemin.x>=arrivee.x)&&(chemin.y<=arrivee.y);
  }  
  else if((direction_x==-1)&&(direction_y==-1)){
    return (chemin.x<=arrivee.x)&&(chemin.y<=arrivee.y);
  }
  else if((direction_x==1)&&(direction_y==1)){
    return (chemin.x>=arrivee.x)&&(chemin.y>=arrivee.y);
  }
  
  return 0;
}


//---------------------------------------------------------------------------------------------------------//


int isCheminLigneFini(int direction_x, int direction_y, position_t chemin, position_t arrivee){

  if((direction_x==0)&&(direction_y==1)){
    return (chemin.y>=arrivee.y);
  }
  else if((direction_x==0)&&(direction_y==-1)){
    return (chemin.y<=arrivee.y);
  }  
  else if((direction_x==-1)&&(direction_y==0)){
    return (chemin.x<=arrivee.x);
  }
  else if((direction_x==1)&&(direction_y==0)){
    return (chemin.x>=arrivee.x);
  }

  return 0;  
}


//---------------------------------------------------------------------------------------------------------//


int isMemePosition(int x1, int x2, int y1, int y2){
  
  return (x1==y1)&&(x2==y2);
}


//---------------------------------------------------------------------------------------------------------//


void valider_roque(etat_t *adresse_board){
  
  if(adresse_board->echiquier.t[7][0]!=TOUR)
    adresse_board->roque.tourB_7_0=1;
  
  if(adresse_board->echiquier.t[7][7]!=TOUR)
    adresse_board->roque.tourB_7_7=1;
  
  if(adresse_board->echiquier.t[7][4]!=ROI)
    adresse_board->roque.roiB_7_4=1;
  
  if(adresse_board->echiquier.t[0][0]!=-TOUR)
    adresse_board->roque.tourN_0_0=1;
  
  if(adresse_board->echiquier.t[0][7]!=-TOUR)
    adresse_board->roque.tourN_0_7=1;
  
  if(adresse_board->echiquier.t[0][4]!=-ROI)
    adresse_board->roque.roiN_0_4=1;
  
}


//---------------------------------------------------------------------------------------------------------//


int roque(etat_t *adresse_board, int piece, position_t depart, position_t arrivee, int couleur){

  //peut-on ecore accéder au conditions if()
  int acceder_B=0;
  int acceder_N=0;

  int cases=0;
  int valeur_return=0;  
  EtatSourisClavier esc=lireEtatSourisClavier();
  int new_x=esc.sourisX;
  int new_y=esc.sourisY;
  arrivee.x=floor((new_x-DEPARTX)/71);
  arrivee.y=-floor((new_y-DEPARTY)/71);

  piece=ROI;
  if(acceder_B==0){
    if((adresse_board->echiquier.t[arrivee.y][arrivee.x]==TOUR)&&((arrivee.y==7)&&(arrivee.x==0))){
      for(int i=1;i<4;i++){
	if(adresse_board->echiquier.t[arrivee.y][i]==VIDE){
	  cases++;
	}
      }
      if(cases==3){
	acceder_B=1;
	valeur_return=11;
	return valeur_return;
      }
    }
    else if((adresse_board->echiquier.t[arrivee.y][arrivee.x]==TOUR)&&((arrivee.y==7)&&(arrivee.x==7))){
      for(int i=6;i>4;i--){
	if(adresse_board->echiquier.t[arrivee.y][i]==VIDE){
	  cases++;
	}
      }
      if(cases==2){
	acceder_B=1;
	valeur_return=12;
	return valeur_return;
      }
    }
  }
  piece=-ROI;
  if(acceder_N==0){
    if((adresse_board->echiquier.t[arrivee.y][arrivee.x]==-TOUR)&&((arrivee.y==0)&&(arrivee.x==0))){
      for(int i=1;i<4;i++){
	if(adresse_board->echiquier.t[arrivee.y][i]==VIDE){
	  cases++;
	}
      }
      if(cases==3){
	acceder_N=1;
	valeur_return=-11;
	return valeur_return;
      }
    }
    else if((adresse_board->echiquier.t[arrivee.y][arrivee.x]==-TOUR)&&((arrivee.y==0)&&(arrivee.x==7))){
      for(int i=6;i>4;i--){
	if(adresse_board->echiquier.t[arrivee.y][i]==VIDE){
	  cases++;
	}
      }
      if(cases==2){
	acceder_N=1;
	valeur_return=-12;
	return valeur_return;
      }
    }
  }
  
  return 0;
}


//---------------------------------------------------------------------------------------------------------//


int effectuer_roque(etat_t *adresse_board, int piece, position_t depart, position_t arrivee, int couleur, etat_t save, int resultat_dep, int mouvement_roque, int result_echec){

  valider_roque(adresse_board); 
  resultat_dep=deplacements(adresse_board, piece, depart, arrivee, couleur);
  if((mouvement_roque==11)&&((adresse_board->roque.tourB_7_0==0)&&(adresse_board->roque.roiB_7_4==0))){	
    adresse_board->echiquier.t[depart.y][depart.x]=VIDE;
    adresse_board->echiquier.t[7][0]=VIDE;
    adresse_board->tab=echiquier_vide();
    animation(adresse_board, piece, depart, arrivee, (position_t) {0,7}, (position_t) {3,7}, 1, couleur);
    adresse_board->echiquier.t[7][3]=TOUR;
    adresse_board->echiquier.t[7][2]=ROI;
    adresse_board->echiquier.t[7][4]=VIDE;
    adresse_board->tab=echiquier_vide();
    result_echec=echec_roi(adresse_board, couleur);
    if(result_echec!=0){
      *adresse_board=save;	  
      return 0;
    }
    return 11;
  }
  else if((mouvement_roque==12)&&((adresse_board->roque.tourB_7_7==0)&&(adresse_board->roque.roiB_7_4==0))){
    adresse_board->echiquier.t[depart.y][depart.x]=VIDE;
    adresse_board->echiquier.t[7][7]=VIDE;
    adresse_board->tab=echiquier_vide();
    animation(adresse_board, piece, depart, arrivee, (position_t) {7,7}, (position_t) {5,7}, 1, couleur);
    adresse_board->echiquier.t[7][5]=TOUR;
    adresse_board->echiquier.t[7][6]=ROI;
    adresse_board->echiquier.t[7][4]=VIDE;
    adresse_board->tab=echiquier_vide();
    result_echec=echec_roi(adresse_board, couleur);
    if(result_echec!=0){
      *adresse_board=save;
      return 0;
    }
    return 12;
  }
  else if((mouvement_roque==-11)&&((adresse_board->roque.tourN_0_0==0)&&(adresse_board->roque.roiN_0_4==0))){
    adresse_board->echiquier.t[depart.y][depart.x]=VIDE;
    adresse_board->echiquier.t[0][0]=VIDE;
    adresse_board->tab=echiquier_vide();
    animation(adresse_board, piece, depart, arrivee, (position_t) {0,0}, (position_t) {3,0}, 1, couleur);
    adresse_board->echiquier.t[0][3]=-TOUR;
    adresse_board->echiquier.t[0][2]=-ROI;
    adresse_board->echiquier.t[0][4]=VIDE;
    adresse_board->tab=echiquier_vide();
    result_echec=echec_roi(adresse_board, couleur);
    if(result_echec!=0){
      *adresse_board=save;
      return 0;
    }
    return -11;
  }
  else if((mouvement_roque==-12)&&((adresse_board->roque.tourN_0_7==0)&&(adresse_board->roque.roiN_0_4==0))){
    adresse_board->echiquier.t[depart.y][depart.x]=VIDE;
    adresse_board->echiquier.t[0][7]=VIDE;
    adresse_board->tab=echiquier_vide();
    animation(adresse_board, piece, depart, arrivee, (position_t) {7,0}, (position_t) {5,0}, 1, couleur);	
    adresse_board->echiquier.t[0][5]=-TOUR;
    adresse_board->echiquier.t[0][6]=-ROI;
    adresse_board->echiquier.t[0][4]=VIDE;
    adresse_board->tab=echiquier_vide();
    result_echec=echec_roi(adresse_board, couleur);
    if(result_echec!=0){
      *adresse_board=save;
      return 0;
    }
    return -12;
  }
  
  return 0;
}


//---------------------------------------------------------------------------------------------------------//


int dep_pion(etat_t *adresse_board, int piece, position_t depart, position_t arrivee, int couleur){

  int result_pion_arrivee=0;
  int isCaseArriveeVide=(adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE);
  
  result_pion_arrivee=pion_arrivee(adresse_board, arrivee, piece, couleur);
  
  //déplacement 2 cases depuis la ligne de départ
  if((arrivee.y==depart.y-2*couleur)&&(arrivee.x==depart.x)){
    if(depart.y==depart_pion(couleur)){
      if(isCaseArriveeVide&&(adresse_board->echiquier.t[arrivee.y+1*couleur][arrivee.x]==VIDE)){
	return 1;
      }
    }
  }
  //déplacement 1 case
  else if(arrivee.y==(depart.y-1*couleur)&&(arrivee.x==depart.x)){
    if(isCaseArriveeVide){
      if(result_pion_arrivee==2){
	return 2;
      }
      else if(result_pion_arrivee==-2){
	return -2;
      }
      return 1;
    }
  }
  //manger diagonales
  else if(((arrivee.y==(depart.y-1*couleur))
	   &&((arrivee.x==(depart.x-1))||(arrivee.x==(depart.x+1))))){
    //test : manger même couleur ?
    if(((couleur==B)&&(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B))
       ||((couleur==N)&&(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N))){
      return 0;
    }
    //test : manger couleur adverse ?
    if((adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B)
       ||(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N)){
      if(result_pion_arrivee==2){
	return 2;
      }
      if(result_pion_arrivee==-2){
	return -2;
      }
      return ANIMATION;
    }
  }
  return 0;
}


//---------------------------------------------------------------------------------------------------------//


int dep_fou(etat_t *adresse_board, position_t depart, position_t arrivee, int couleur){

  int n_x, n_y;
  int abs_n_x, abs_n_y; 
  n_x=arrivee.x-depart.x;
  n_y=arrivee.y-depart.y;
  abs_n_x=abs(n_x);
  abs_n_y=abs(n_y);
  //si le clic est effectué sur la diagonale
  if((n_y==n_x)||(n_y==-n_x)||(-n_y==n_x)||(-n_y==-n_x)){

    int direction_x, direction_y;
    direction_x=(n_x)/(abs_n_x);
    direction_y=(n_y)/(abs_n_y);
    position_t chemin=(position_t) {depart.x+direction_x, depart.y+direction_y};
      
    while(!isCheminDiagonaleFini(direction_x, direction_y, chemin, arrivee)){
      if(adresse_board->echiquier.t[chemin.y][chemin.x]!=VIDE){
	return 0;
      }
      chemin.x=chemin.x+direction_x;
      chemin.y=chemin.y+direction_y;
    }
      
    if((adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N)
       &&(adresse_board->echiquier.t[arrivee.y][arrivee.x]<0)&&(couleur==B)){
      return ANIMATION;
    }
    if((adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B)
       &&(adresse_board->echiquier.t[arrivee.y][arrivee.x]>0)&&(couleur==N)){
      return ANIMATION;
    }
    if(adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE){
      return 1;
    }
  }
  return 0;
}


//---------------------------------------------------------------------------------------------------------//


int dep_cavalier_Blanc(etat_t *adresse_board, position_t depart, position_t arrivee, int couleur){

  int n_x, n_y;
  n_x=arrivee.x-depart.x;
  n_y=arrivee.y-depart.y;
  if(couleur==B){
    if(((n_y==1)&&(n_x==2))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==1)&&(n_x==-2))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==-1)&&(n_x==2))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==-1)&&(n_x==-2))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==2)&&(n_x==1))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==2)&&(n_x==-1))
	    &&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==-2)&&(n_x==1))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==-2)&&(n_x==-1))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N){
	return ANIMATION;
      }
      return 1;
    }
  }
  return 0;
}


//---------------------------------------------------------------------------------------------------------//


int dep_cavalier_Noir(etat_t *adresse_board, position_t depart, position_t arrivee, int couleur){

  int n_x, n_y;
  n_x=arrivee.x-depart.x;
  n_y=arrivee.y-depart.y;
  if(couleur==N){
    if(((n_y==1)&&(n_x==2))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==1)&&(n_x==-2))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==-1)&&(n_x==2))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==-1)&&(n_x==-2))
	    &&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==2)&&(n_x==1))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==2)&&(n_x==-1))
	    &&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==-2)&&(n_x==1))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==-2)&&(n_x==-1))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B){
	return ANIMATION;
      }
      return 1;
    }
  }
  return 0;
}


//---------------------------------------------------------------------------------------------------------//


int dep_tour(etat_t *adresse_board, position_t depart, position_t arrivee, int couleur){

  int n_x, n_y;
  int abs_n_x, abs_n_y; 
  n_x=arrivee.x-depart.x;
  n_y=arrivee.y-depart.y;
  abs_n_x=abs(n_x);
  abs_n_y=abs(n_y);
  position_t chemin;
  int direction_x=0;
  int direction_y=0;
    
  if(!(((n_y==0)&&(n_x!=0))||((n_y!=0)&&(n_x==0)))){
    return 0;
  }

  if(n_x!=0){
    direction_x=(n_x)/(abs_n_x);
    direction_y=0;
  }
  else if(n_y!=0){
    direction_x=0;
    direction_y=(n_y)/(abs_n_y);
  } 
    
  chemin=(position_t) {depart.x+direction_x, depart.y+direction_y};
         
  while(!isCheminLigneFini(direction_x, direction_y, chemin, arrivee)){
    if(adresse_board->echiquier.t[chemin.y][chemin.x]!=VIDE){
      return 0;
    }
    chemin.x=chemin.x+direction_x;
    chemin.y=chemin.y+direction_y;
  }
      
  if((adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N)
     &&(adresse_board->echiquier.t[arrivee.y][arrivee.x]<0)&&(couleur==B)){
    return ANIMATION;
  }
  if((adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B)
     &&(adresse_board->echiquier.t[arrivee.y][arrivee.x]>0)&&(couleur==N)){
    return ANIMATION;
  }
  if(adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE){
    return 1;
  }
  return 0;
}


//---------------------------------------------------------------------------------------------------------//


int dep_dame(etat_t *adresse_board, position_t depart, position_t arrivee, int couleur){

  int n_x, n_y;
  int abs_n_x, abs_n_y; 
  n_x=arrivee.x-depart.x;
  n_y=arrivee.y-depart.y;
  abs_n_x=abs(n_x);
  abs_n_y=abs(n_y);
  int direction_x, direction_y;
  position_t chemin;
  direction_x=0;
  direction_y=0;
  if(!(((n_y==0)&&(n_x!=0))||((n_y!=0)&&(n_x==0))||(n_y==n_x)||(n_y==-n_x)||(-n_y==n_x)||(-n_y==-n_x))){
    return 0;
  }
  else if((n_y==n_x)||(n_y==-n_x)||(-n_y==n_x)||(-n_y==-n_x)){
    direction_x=(n_x)/(abs_n_x);
    direction_y=(n_y)/(abs_n_y);
    chemin=(position_t) {depart.x+direction_x, depart.y+direction_y};    
    while(!isCheminDiagonaleFini(direction_x, direction_y, chemin, arrivee)){
      if(adresse_board->echiquier.t[chemin.y][chemin.x]!=VIDE){
	return 0;
      }
      chemin.x=chemin.x+direction_x;
      chemin.y=chemin.y+direction_y;
    }
    if((adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N)&&(adresse_board->echiquier.t[arrivee.y][arrivee.x]<0)&&(couleur==B)){
      return ANIMATION;
    }
    if((adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B)&&(adresse_board->echiquier.t[arrivee.y][arrivee.x]>0)&&(couleur==N)){
      return ANIMATION;
    }
    if(adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE){
      return 1;
    }
  }
  else if((n_y!=0)||(n_x!=0)){
    if(n_x!=0){
      direction_x=(n_x)/(abs_n_x);
      direction_y=0;
    }
    else if(n_y!=0){
      direction_x=0;
      direction_y=(n_y)/(abs_n_y);
    } 
    chemin=(position_t) {depart.x+direction_x, depart.y+direction_y};    
    while(!isCheminLigneFini(direction_x, direction_y, chemin, arrivee)){
      if(adresse_board->echiquier.t[chemin.y][chemin.x]!=VIDE){
	return 0;
      }
      chemin.x=chemin.x+direction_x;
      chemin.y=chemin.y+direction_y;
    } 
    if((adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N)&&(adresse_board->echiquier.t[arrivee.y][arrivee.x]<0)&&(couleur==B)){
      return ANIMATION;
    }
    if((adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B)&&(adresse_board->echiquier.t[arrivee.y][arrivee.x]>0)&&(couleur==N)){
      return ANIMATION;
    }
    if(adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE){
      return 1;
    }
  }
  return 0;
}


//---------------------------------------------------------------------------------------------------------//


int dep_roi_Blanc(etat_t *adresse_board, position_t depart, position_t arrivee, int couleur){

  int n_x, n_y;
  n_x=arrivee.x-depart.x;
  n_y=arrivee.y-depart.y;
  if(!(((n_y==1)||(n_y==-1)||(n_y==0))&&((n_x==1)||(n_x==-1)||(n_x==0)))){
    return 0;
  }    
  if(couleur==B){
    if(((n_y==1)&&(n_x==1))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==1)&&(n_x==0))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==1)&&(n_x==-1))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==0)&&(n_x==1))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==0)&&(n_x==-1))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==-1)&&(n_x==1))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==-1)&&(n_x==0))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==-1)&&(n_x==-1))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]<=N){
	return ANIMATION;
      }
      return 1;
    }
  }    
  return 0;
}    

    
//---------------------------------------------------------------------------------------------------------//


int dep_roi_Noir(etat_t *adresse_board, position_t depart, position_t arrivee, int couleur){
  
  int n_x, n_y;
  n_x=arrivee.x-depart.x;
  n_y=arrivee.y-depart.y;
  if(!(((n_y==1)||(n_y==-1)||(n_y==0))&&((n_x==1)||(n_x==-1)||(n_x==0)))){
    return 0;
  }
  if(couleur==N){
    if(((n_y==1)&&(n_x==1))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==1)&&(n_x==0))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==1)&&(n_x==-1))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==0)&&(n_x==1))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==0)&&(n_x==-1))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==-1)&&(n_x==1))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==-1)&&(n_x==0))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B){
	return ANIMATION;
      }
      return 1;
    }
    else if(((n_y==-1)&&(n_x==-1))&&((adresse_board->echiquier.t[arrivee.y][arrivee.x]==VIDE)||(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B))){
      if(adresse_board->echiquier.t[arrivee.y][arrivee.x]>=B){
	return ANIMATION;
      }
      return 1;
    }
  }
  return 0;
}


//---------------------------------------------------------------------------------------------------------//



int deplacements(etat_t *adresse_board, int piece, position_t depart, position_t arrivee, int couleur){

  int result_dep=0;

  if(isMemePosition(depart.x, depart.y, arrivee.x, arrivee.y)){
    return 0;
  }

  if(piece==PION*couleur){
    result_dep=dep_pion(adresse_board, piece, depart, arrivee, couleur);
    return result_dep;
  }
  else if(piece==FOU*couleur){
    result_dep=dep_fou(adresse_board, depart, arrivee, couleur);
    return result_dep;
  }
  else if(piece==CAVALIER*B){
    result_dep= dep_cavalier_Blanc(adresse_board, depart, arrivee, couleur);
    return result_dep;
  }
  else if(piece==CAVALIER*N){
    result_dep= dep_cavalier_Noir(adresse_board, depart, arrivee, couleur);
    return result_dep;
  }
  else if(piece==TOUR*couleur){
    result_dep=dep_tour(adresse_board, depart, arrivee, couleur);
    return result_dep;
  }
  else if(piece==DAME*couleur){
    result_dep= dep_dame(adresse_board, depart, arrivee, couleur);
    return result_dep;
  }
  else if(piece==ROI*B){
    result_dep=dep_roi_Blanc(adresse_board, depart, arrivee, couleur);
    return result_dep;
  }
  else if(piece==ROI*N){
    result_dep=dep_roi_Noir(adresse_board, depart, arrivee, couleur);
    return result_dep;
  }
      
  return 0;
}


//---------------------------------------------------------------------------------------------------------//


int echec_roi(etat_t *adresse_board, int couleur){
  
  int i, j;
  position_t pos_roi;
  echiquier_t tab=echiquier_vide();
  
  for(i=0;i<8;i++){
    for(j=0;j<8;j++){
      if(adresse_board->echiquier.t[j][i]==(ROI*couleur)){
	pos_roi.x=i;
	pos_roi.y=j;
      }
    }
  }
  
  for(i=0;i<8;i++){
    for(j=0;j<8;j++){ 

      //si la valeur des pièces de la couleur qui joue est inférieur à 0 alors, 
      if((adresse_board->echiquier.t[j][i]*couleur)<0){
	//on surligne les cases possibles pour les pièces de -couleur (couleur adverse),
	tab=surlignerCasesPossibles(adresse_board, adresse_board->echiquier.t[j][i], (position_t) {i, j}, -couleur);
      }
      //si l'une de ces cases correspondent à la position de celles du roi alors,
      if((adresse_board->echiquier.t[pos_roi.y][pos_roi.x])==(tab.t[pos_roi.y][pos_roi.x])){
	return 1;
      }
    }
  }  
  
  return 0; 
}


//---------------------------------------------------------------------------------------------------------//


int echec_mat(etat_t *adresse_board, int couleur){

  if (echec_roi(adresse_board, couleur)){
    // on teste toutes les défenses possibles :
    // Pour toutes les pièces de couleur
    for(int i=0;i<8;i++)
      for(int j=0;j<8;j++)
	if (adresse_board->echiquier.t[j][i] * couleur > 0)
	  {
	    // on calcule la liste des déplacements possibles
	    echiquier_t possibles = surlignerCasesPossibles(adresse_board, adresse_board->echiquier.t[j][i], (position_t) {i, j}, couleur);
	    for(int k=0;k<8;k++)
	      for(int l=0;l<8;l++)
		if (possibles.t[k][l] != 0)
		  {
		    // on effectue chaque déplacement possible sur un échiquier temporaire
		    etat_t etat_bis = *adresse_board;
		    etat_bis.echiquier.t[j][i] = 0;
		    etat_bis.echiquier.t[k][l] = adresse_board->echiquier.t[j][i];

		    // si le roi n'est plus en échec sur cet échiquier temporaire, il n'est pas mat -> la fonction retourne 0 (roi seulement en échec)
		    if (! echec_roi( &etat_bis, couleur)){
		      return 0;
		    }
		  }
	  }
    // le roi est en échec et aucun coup ne lui permet de ne plus l'être -> la fonction se termine (roi en échec et mat)
    return 3 ;
  }
    
  return 0;
}


//---------------------------------------------------------------------------------------------------------//


echiquier_t surlignerCasesPossibles(etat_t *adresse_board, int piece, position_t depart, int couleur){

  echiquier_t tab=echiquier_vide();
  int i, j;
  int result_dep=0;
  position_t arrivee;
  
  for(i=0;i<8;i++){
    for(j=0;j<8;j++){
      arrivee=(position_t) {arrivee.x, arrivee.y};
      arrivee.x=i;
      arrivee.y=j;
      result_dep=deplacements(adresse_board, piece, depart, arrivee, couleur);
      
      if((result_dep==1)||(result_dep==ANIMATION)){
	tab.t[j][i]=(-couleur*ROI);
      }
    }
  }
  
  return tab;
}


//---------------------------------------------------------------------------------------------------------//


echiquier_t echiquier_vide(){

  echiquier_t tab;
  tab=(echiquier_t) {.t={{0, 0, 0, 0, 0, 0, 0, 0},
			 {0, 0, 0, 0, 0, 0, 0, 0},
			 {0, 0, 0, 0, 0, 0, 0, 0},
			 {0, 0, 0, 0, 0, 0, 0, 0},
			 {0, 0, 0, 0, 0, 0, 0, 0},
			 {0, 0, 0, 0, 0, 0, 0, 0},
			 {0, 0, 0, 0, 0, 0, 0, 0},
			 {0, 0, 0, 0, 0, 0, 0, 0}}};
  
  
  return tab;
}


//---------------------------------------------------------------------------------------------------------//


void animation(etat_t *adresse_board, int piece, position_t depart, position_t arrivee, position_t depart_tour, position_t arrivee_tour, int animation, int couleur){

  int piece_tour;
  position_t pos_actuelle, pos_actuelle_tour, vecteur_distance, vecteur_distance_tour;
  //variation de déplacement
  int dx, dy, dx_tour, dy_tour;
  depart=positionToCoord(depart);
  arrivee=positionToCoord(arrivee);
  depart_tour=positionToCoord(depart_tour);
  arrivee_tour=positionToCoord(arrivee_tour);
  pos_actuelle=depart;
  pos_actuelle_tour=depart_tour; 
  vecteur_distance.x=arrivee.x-depart.x;
  vecteur_distance.y=arrivee.y-depart.y;
  vecteur_distance_tour.x=arrivee_tour.x-depart_tour.x;
  vecteur_distance_tour.y=arrivee_tour.y-depart_tour.y;
  vecteur_distance_tour.x=arrivee_tour.x-depart_tour.x;
  vecteur_distance_tour.y=arrivee_tour.y-depart_tour.y;
  dx=(vecteur_distance.x/20);
  dy=(vecteur_distance.y/20);  
  if(animation==0){
    while((areSignEqual(arrivee.x-pos_actuelle.x, arrivee.x-(pos_actuelle.x+dx)))&&(areSignEqual(arrivee.y-pos_actuelle.y, arrivee.y-(pos_actuelle.y+dy)))){
      pos_actuelle.x+=dx;
      pos_actuelle.y+=dy;
      afficher(adresse_board, (position_t) {0, 0}, 0, 0, 0, 0);
      afficherImage(adresse_board->tableau_Im[piece+6], pos_actuelle.x, pos_actuelle.y);
      tamponner();
      effacerTableau();
      attendreNms(50);
    }
  }
  //animation pour le roque
  dx=(vecteur_distance.x/40);
  dy=(vecteur_distance.y/40);
  dx_tour=(vecteur_distance_tour.x/20);
  dy_tour=(vecteur_distance_tour.y/20);
  if(animation!=0){
    while((areSignEqual(arrivee_tour.x-pos_actuelle_tour.x, arrivee_tour.x-(pos_actuelle_tour.x+dx_tour)))&&(areSignEqual(arrivee_tour.y-pos_actuelle_tour.y, arrivee_tour.y-(pos_actuelle_tour.y+dy_tour)))){
      pos_actuelle.x+=dx;
      pos_actuelle.y+=dy;
      afficher(adresse_board, (position_t) {0, 0}, 0, 0, 0, 0);
      afficherImage(adresse_board->tableau_Im[piece+6], pos_actuelle.x, pos_actuelle.y);
      if(animation!=0){
	piece_tour=TOUR*couleur;
	pos_actuelle_tour.x+=dx_tour;
	pos_actuelle_tour.y+=dy_tour;
	afficherImage(adresse_board->tableau_Im[piece_tour+6], pos_actuelle_tour.x, pos_actuelle_tour.y);
      }
      tamponner();
      effacerTableau();
      attendreNms(50);
    }
  }
}


//---------------------------------------------------------------------------------------------------------//


position_t positionToCoord(position_t position){

  position.x=DEPARTX + 71*position.x;
  position.y=DEPARTY - 71*position.y;
  
  return position;
}


//---------------------------------------------------------------------------------------------------------//


int areSignEqual(int a, int b){

  if((a*b)>=0){
    return 1;
  }
  
  return 0;
}


//---------------------------------------------------------------------------------------------------------//

