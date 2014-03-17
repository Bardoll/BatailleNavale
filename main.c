#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){

	/* VARIABLES *****************************************/
		char grille[10][10]; //plateau de jeu

	/* CODE **********************************************/

	do{
		bonjour();
		initialGrille(grille); //on initialise le plateau
		afficherGrille(grille); //on affiche le plateau
	}while(jeu==1);
	
}


void initialGrille(char grille[x][y]){
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
				grille[i][j]="~";
		}
	}
}



char afficherGrille(char grille[x][y]){
	for(int i=0; i<9; i++){
		for(int j=0; j<9; j++){
			printf("%s", &grille[i][j]);
		}
		printf("\n");
	}
}
