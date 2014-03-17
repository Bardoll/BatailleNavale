#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int i,j=0;

void bonjour(){
	printf("Bienvenue dans le jeu Bataille navale !\n\n");
	printf("Le but de ce jeu est de détruire tous les bateaux de l'adversaire en envoyant des missiles à chaque tour\n");
	printf("Pour cela, vous disposez d'un plan de la zone où se cache votre ennemi\n");
	printf("A chaque tour, entrez les coordonnées d'un point et un missile sera envoyé !\n");
	printf("Bon courage soldat !\n\n\n");
}

void initialGrille(char grille[i][j]){
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
				grille[i][j]="~";
		}
	}
}



void afficherGrille(char grille[i][j]){
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			printf("%s", &grille[i][j]);
		}
		printf("\n");
	}
}


int main(void){

	/* VARIABLES *****************************************/
		char grille[10][10]; //plateau de jeu

	/* CODE **********************************************/

	do{
		bonjour();				//dire bonjour (parce qu'on est poli)
		initialGrille(grille); //on initialise le plateau
		afficherGrille(grille); //on affiche le plateau
	}while(jeu==1);
	
}