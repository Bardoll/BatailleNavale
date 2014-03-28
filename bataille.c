#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define iWIN 9 // Valeur de victoie lorsque tous les bateaux ont été détruits
#define nligne 12 // matrix must be higher than ten to instill boundary test
#define ncolonne 12 // matrix must be higher than ten to instill boundary test


/* LES FONCTIONS ****************************************************************/
void bonjour();// Fonction d'accueil

void grilleInitiale(char grille[nligne][ncolonne]); // créer le plateau initial
void botBoat(char grille[nligne][ncolonne], char ship[50], int size);// placement pseudo-aléatoire des bateaux par l'ordi
void afficherGrille(char grille[nligne][ncolonne]); // afficher le plateau actuel
void feu(char grille[nligne][ncolonne],int x, int y); // permet au joueur de rentrer les coordonnées de ses missiles
void verifMissile(char grille[nligne][ncolonne],int x, int y); // Vérifie si les missiles envoyés ont touchés
int check_2(char grille[nligne][ncolonne],int x, int y); // Vérifie la grille que le joueur voit
void remplaceGrille(char grille[nligne][ncolonne], int x ,int y, int z); // affiche les x ou o sur la grilleà 


/* CODE *********************************************************************************/
/* champ de bataille */
int main(void)
{
	srand(time(NULL)); // fontion random
	int game; // valeur de victoire
	int row,col; // opérateurs pour les coordonnées
	int counter; // compteur
	int trans;
	int win; // varaibel définissant si le joueur a gagné
	char grid[12][12]; // grille contenant les bateaux placées par l'ordinateur
	char grid_2[12][12];// grille vide que le joueur voit
	int r,c,error;
	int begin;


	do{
		counter = 0;
		grid[nligne][ncolonne] = '~'; //rempli les deux grilles avec des ~
		grid_2[nligne][ncolonne] = '~'; //idem
		r = 0;
		c = 0;
		error = 0;
		bonjour(); //Donne les instructions
		win = 0;// mets à 0 la valeur de victoire
		system("PAUSE");
		game = 1; // Initialise la valeur de victoire
		grilleInitiale(grid);// place le plateau en mémoire
		grilleInitiale(grid_2);// idem 
		system("CLS");// vide l'écran
		botBoat( grid, "destroyer" , 4);
		botBoat( grid, "cruiser" , 3);
		botBoat( grid, "vessel" , 2);
		botBoat( grid_2, "~XO" , 4); 
		botBoat( grid_2, "~XO" , 3); 
		botBoat( grid_2, "~XO" , 2);

		for(r=0;r<10;r++)
		{
			for(c=0;c<10;c++)
			{
				if( grid[r][c] != '~'){       // Vérification que tous les bateaux soient bien placés
					error++;
				}
			}
		}

		if( error == 8 || error != 9){
			printf(" ERROR: Only 8 ships were generated... Game reset\n\n");  
			begin = 1;
		}
		else{
			begin = 0;				//si tout va bien, la partie commence
		}
	}while(begin == 1);



	do{       

		afficherGrille(grid_2);// on affiche la grille vide
		printf(" Ennemis detectes ! Feu a volonte !!\n\n");
		printf(" Capitaine, entrez les coordonnees des missiles !\n\n"); 
		printf(" - Entrez un chiffre puis appuyez sur 'entree'\n\n\n");
		printf("(ligne): ");
		scanf("%d", &row);				//entrée des coordonnées par le joueur
		printf("(colonne): ");
		scanf("%d", &col);
		if( row > 9 || row<0 ||  col > 9 ||  col <0){				//vérif des coordonnées
			printf("coordonnees non correctes, veuillez les entrez de nouveau\n");
			system("PAUSE");
			continue;
		}
		if(grid[row][col] == 'X' || grid[row][col] == 'O')
		{

			continue;
		}

		feu(grid,row,col);

		check_2(grid,row, col); //retourne la valeur de retour et affiche 'x' ou 'o'
		trans = check_2(grid,row, col); 

		if(trans == 1){
			win++;   // Si le missile touche, la valeur win s'incrémente jusqu'à 9
		}
		remplaceGrille(grid_2,row,col,trans);// remplace la cellule visé par le joueur
		afficherGrille(grid_2);// affiche la nouvelle grille
		verifMissile(grid,row,col); 
		system("pause");
		counter++;// compte le coup effectué

		if(win == iWIN){
			game = 0;  // fin de la partie
		}

	}while(game == 1 && win <= iWIN);
	if(game == 0){
		system("CLS");
		printf("You win!\n");
		printf("Captain... you saved us!!!\n\n");
		printf("You completed the game in %d move(s)!\n\n",counter);  
	}
	if( game == 2){
		system("PAUSE");
		return 0;
	}

	system("PAUSE");
	return 0;

}/* Fin du champ de bataille */





/* FONCTIONS ****************************************************************************/

void bonjour() // fonction d'accueil
{
	system("CLS");
	printf(" ----------------------------------------------------- \n\n");
	printf("     ***** Bienvenue sur le champ de bataille ********       \n\n");
	printf(" ----------------------------------------------------- \n\n\n\n");


	printf("Soldat: \n\nVotre mission, si vous l'acceptez, est de detruire tous les bateaux ennemis\n\n\n");
	printf("Vous tirerez des missiles en rentrant les coordonnees (x,y), jusqu'a ce que \ntous les bateaux ");
	printf("ennemis soient detruits \n\n X = Touche!, O = Rate!,  ~ = Zone non exploree (mer)\n\n ");

} // end function

void grilleInitiale(char grille[nligne][ncolonne]) //Initialise la grille de départ
{
	int i,j;
	for(i=0;i<10;i++)
	{                                           
		for( j=0;j<10;j++)
		{
			grille[i][j]='~';
		}
	}
} 

void afficherGrille(char grille[nligne][ncolonne]) //affiche la grille
{
	int i,j;
	system("CLS");
	printf("  0 1 2 3 4 5 6 7 8 9\n\n");      
	for(i=0;i<10;i++)
	{
		printf("%d",i);
		for(j=0;j<10;j++)
		{
			printf(" %c", grille[i][j]);
		}
		printf("\n");
	}
} 

void botBoat(char grille[nligne][ncolonne], char ship[50], int size) // algo qui place les bateaux de l'ordinateur
{                                            
	int row=0;
	int col=0;
	int go; 
	go=1;
	char dir;
	int test;
	int ai;


	do
	{
		row = rand()%10;    /* } pseudo random système de coordonées */
		col = rand()%10;

		if(row>9 || row<0 || col<0 || col>9)    //on vérifie qu'il n'y a pas d'erreurs
		{
			go=0;
		}
		else if(grille[row][col]!='~')
		{
			go=0;
		}
		else
			go = 1;

		if(go==0){
			row = rand()%10;
			col = rand()%10;

			if(row>9 || row<0 || col<0 || col>9) 
			{
				go=0;
				continue;
			}
			else if(grille[row][col]!='~') 
			{
				go=0;
				continue;
			}
			else
				go = 1;
		}



	}while(go==0);



	do
	{

		if(test==0){
			test=1;
		}
		ai = rand()%4+1;

		switch(ai){ // pseudo random direction
		case 1:
			dir = 'l'; // gauche
			break;
		case 2:
			dir = 'u'; // haut
			break;
		case 3:
			dir = 'd'; //  bas
			break;
		case 4:
			dir = 'r'; // droite
			break;
		default:
			test = 0;
			continue;
			break;
		}

		switch(dir)
		{
		int i,x; // i=ligne, x=colonne (j)

		case 'l':
			if(col-size>=1) 
			{
				for(i=0;i<=size-1;i++)
				{
					if(grille[row][col-i]!='~') // test si il y a déja un bateau ou pas
					{
						test=0;
						continue; // reloop
					}
				}
			}
			else
			{
				test=0;
				continue; 
			}
			test = 1;
			if(test==1)
			{
				for(x=0;x<=size-1;x++)  //incrémente la colonne en fonction de la direction et valeur de x
				{
					grille[row][col-x]=ship[0]; // la première lettre du bateau
				}
			}
			break;

			
		case 'r':
			if(col+size<=10)
			{
				for(i=0;i<=size-1;i++)
				{
					if(grille[row][col+i]!= '~')
					{
						test=0;
						continue;
					}
				}
			}
			else
			{
				test=0;
				continue;
			}
			test = 1;
			if(test==1)
			{
				for(x=0;x<=size-1;x++)
				{
					grille[row][col+x]=ship[0]; 
				}
			}
			break;

		case 'u':
			if(row-size>=1)
			{
				for(i=0;i<=size-1;i++)
				{
					if(grille[row-i][col]!= '~') 
					{
						test=0;
						continue;
					}
				}
			}
			else
			{
				test=0;
				continue;
			}
			test = 1;
			if(test==1)
			{
				for(x=0;x<=size-1;x++)
				{
					grille[row-x][col]=ship[0]; // the ships first letter
				}
			}
			break;

		case 'd':
			if(row+size<=10)
			{
				for(i=0;i<=size-1;i++)
				{
					if(grille[row+i][col]!='~')
					{
						test=0;
						continue;
					}
				}
			}
			else
			{
				test=0;
				continue;
			}
			test = 1;
			if(test==1)
			{
				for(x=0;x<=size-1;x++) 
				{
					grille[row+x][col]=ship[0]; 
				}
			}
		}

	}while(test==0);
} 


void feu(char grille[nligne][ncolonne], int x,int y){  //permet à l'utilisateur d'entrer les coordonnées de ses attaques

	char hit_miss[10];
	int status;
	status = 1;

	do{

		while( x > 9 || x<0 ||  y > 9 || y<0){
			printf("entree non valide... Entrez les a nouveau !\n");   // on vérifie les coordonnées
			printf("(ligne)y: ");
			scanf("%d", &x);
			printf("(colonne)x: ");
			scanf("%d", &y);
			continue;
		}

		if(grille[x][y]  == 'O' || grille[x][y]  == 'X'){

			status = 1;


		}
		if(grille[x][y] == 'c' || grille[x][y]== 'v' || grille[x][y]== 'd'){
			hit_miss[0] = 'X';
			status = 0;
		}
		else {                    
			hit_miss[0] = 'O';
			status = 0;
		}
	}while(status==1);
	grille[x][y]= hit_miss[0];
}

int check_2(char grille[nligne][ncolonne],int x, int y){
	if(grille[x][y]=='X'){
		return 1;
	}
	else
		return 0;
}

void remplaceGrille(char grille[nligne][ncolonne], int x,int y, int z){ //on affiche X ou O à l'écran

	if( z == 1 ){
		grille[x][y] = 'X';
	} else
		grille[x][y] = 'O';
}


void verifMissile(char grille[nligne][ncolonne],int x, int y){ 
	if(grille[x][y]=='X'){
		printf("TOUCHE!\n\n");
	}
	else
		printf("RATE!\n\n");
}
