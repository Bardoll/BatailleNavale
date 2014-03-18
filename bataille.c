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
void remplaceGrille(char grille[nligne][ncolonne], int x ,int y, int z); // affiche les x ou o sur la grille


/* CODE *********************************************************************************/
/* champ de bataille */
int main(void)
{
	srand(time(NULL)); // fontion random
	int game; // valeur de victoire
	int row,col; // coordinate opertors
	int counter; // keeps track of how many moves you make
	int trans;// transition value to print correct letter on X/O on screen
	int win; // when  player equals amount of ships on battlefield that have been hit
	char grid[12][12]; // grid that carries initial value and coordinates of ships from computer
	char grid_2[12][12];// "empty" grid that player sees
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
		botBoat( grid_2, "~XO" , 4); // initial character is tilde to
		botBoat( grid_2, "~XO" , 3);  // different values do matter since it is the overlay and only sets
		botBoat( grid_2, "~XO" , 2);

		for(r=0;r<10;r++)
		{
			for(c=0;c<10;c++)
			{
				if( grid[r][c] != '~'){       // if the amount of ships is less than 9 ships the game resets itself
					error++;
				}
			}
		}

		if( error == 8 || error != 9){
			printf(" ERROR: Only 8 ships were generated... Game reset\n\n");  // if the amount of ships is less than 9 ships the game resets itself
			begin = 1;
		}
		else{
			begin = 0;
		}
	}while(begin == 1);



	do{       // les bateaux sont placés

		afficherGrille(grid_2);// "empty grid" is shown
		printf(" Ennemis detectes ! Feu a volonte !!\n\n");
		printf(" Capitaine, entrez les coordonnees des missiles !\n\n"); // coordinates inputed by user
		printf(" - Entrez un chiffre puis appuyez sur 'entree'\n\n\n");
		printf("(ligne): ");
		scanf("%d", &row);
		printf("(colonne): ");
		scanf("%d", &col);
		if( row > 9 || row<0 ||  col > 9 ||  col <0){
			printf("coordonnees non correctes, veuillez les entrez de nouveau\n");
			system("PAUSE");
			continue;
		}
		if(grid[row][col] == 'X' || grid[row][col] == 'O')
		{

			continue;
		}

		feu(grid,row,col);// re-enters coordinate as either hit or miss

		check_2(grid,row, col);// returns integer value for hit or miss calculations and printing 'x' or 'o'
		trans = check_2(grid,row, col); // trans value is input to next function to tell an 'x' or 'o'

		if(trans == 1){ // TRANSintion code to transer coordinate information to player graph.
			win++;   // if X is printed (hit), then win increments until nine coodinates are hit
		}
		remplaceGrille(grid_2,row,col,trans);// prints x or o to grid 2 ( user)
		afficherGrille(grid_2);// displays "current" grid postioning
		verifMissile(grid,row,col); // prints hit or miss
		system("pause");
		counter++;// counts moves made

		if(win == iWIN){
			game = 0;  // end_game
		}

	}while(game == 1 && win <= iWIN);
	if(game == 0){
		system("CLS");
		printf("You win!\n");
		printf("Captain... you saved us!!!\n\n");
		printf("You completed the game in %d move(s)!\n\n",counter);   // } statistics once game ended
	}
	if( game == 2){
		system("PAUSE");
		return 0;
	}

	system("PAUSE");
	return 0;

}/*  ------ End of Battleship --------- */





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

void grilleInitiale(char grille[nligne][ncolonne]) //Sets the grille initially to all open spaces before ships inhabit water.
{
	int i,j;
	for(i=0;i<10;i++)
	{                                            // printing algorithm
		for( j=0;j<10;j++)
		{
			grille[i][j]='~';
		}
	}
} // end function

void afficherGrille(char grille[nligne][ncolonne]) //Displays the entire 10x10 grille.
{
	int i,j;
	system("CLS");
	printf("  0 1 2 3 4 5 6 7 8 9\n\n");      // printing algorithm
	for(i=0;i<10;i++)
	{
		printf("%d",i);
		for(j=0;j<10;j++)
		{
			printf(" %c", grille[i][j]);
		}
		printf("\n");
	}
} // end function

void botBoat(char grille[nligne][ncolonne], char ship[50], int size) // logic that places ships
{                                             // ^^ ship character ( ship[50] to give enough space for any name and avoid error)
	int row=0;
	int col=0;
	int go; // tests integer value if coordinate is true
	go=1;
	char dir;
	int test;// tests direction based on boundaries of matrix
	int ai;// random direction... may overlap


	do
	{
		row = rand()%10;    /* } pseudo random coordinate system */
		col = rand()%10;

		if(row>9 || row<0 || col<0 || col>9)
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

			if(row>9 || row<0 || col<0 || col>9) // just in case there is an error in modulus operator
			{
				go=0;
				continue;
			}
			else if(grille[row][col]!='~') // if tilde is not present the coordinate is not available. Msy not be working
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

		switch(ai){ // psedudo random direction
		case 1:
			dir = 'l'; // left
			break;
		case 2:
			dir = 'u'; // up
			break;
		case 3:
			dir = 'd'; // down
			break;
		case 4:
			dir = 'r'; // right
			break;
		default:
			test = 0; // re-loops if no direction is randomized
			continue;
			break;
		}

		switch(dir)
		{
		int i,x; // i representing row, x representing column (j)

		case 'l':
			if(col-size>=1) // makes sure it is not past the boundary of the grid
			{
				for(i=0;i<=size-1;i++)// increments row
				{
					if(grille[row][col-i]!='~') // tests if present character is there.   ****************May not be working as overlap is possible.
					{
						test=0;
						continue; // reloop
					}
				}
			}
			else
			{
				test=0;
				continue; // reloop
			}
			test = 1;
			if(test==1)
			{
				for(x=0;x<=size-1;x++)  //increments column to print based on direction and value of x coordinate
				{
					grille[row][col-x]=ship[0]; // the ships first letter
				}
			}
			break;

			/* all cases below follow the same algorithm as above */
		case 'r':
			if(col+size<=10)
			{
				for(i=0;i<=size-1;i++)
				{
					if(grille[row][col+i]!= '~') // increments one column if anything not a tilde is present in array memory
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
					grille[row][col+x]=ship[0]; // the ships first letter
				}
			}
			break;

		case 'u':
			if(row-size>=1)
			{
				for(i=0;i<=size-1;i++)
				{
					if(grille[row-i][col]!= '~')  // increments one column if anything not a tilde is present in array memory
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
				for(x=0;x<=size-1;x++) // incrementation by row
				{
					grille[row+x][col]=ship[0]; // the ships first letter
				}
			}
		}

	}while(test==0);
} // end function


void feu(char grille[nligne][ncolonne], int x,int y){ // feu function allow users to input coordinate of attack

	char hit_miss[10];
	int status;
	status = 1;

	do{

		while( x > 9 || x<0 ||  y > 9 || y<0){
			printf("invalid entry... re-enter coordinates\n");   // avoids invalid entry after same coordinates are entered
			printf("(row)y: ");
			scanf("%d", &x);
			printf("(column)x: ");
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
		else {                    // prints respective x or o on background grid (grid 1)
			hit_miss[0] = 'O';
			status = 0;
		}
	}while(status==1);
	grille[x][y]= hit_miss[0];
}

int check_2(char grille[nligne][ncolonne],int x, int y){ // feu function allow users to input coordinate of attack for seconde grid
	if(grille[x][y]=='X'){
		return 1;
	}
	else
		return 0;
}

void remplaceGrille(char grille[nligne][ncolonne], int x,int y, int z){ // prints respective x or o on screen

	if( z == 1 ){
		grille[x][y] = 'X';
	} else
		grille[x][y] = 'O';
}


void verifMissile(char grille[nligne][ncolonne],int x, int y){ // feu function allow users to input coordinate of attack
	if(grille[x][y]=='X'){
		printf("TOUCHE!\n\n");
	}
	else
		printf("RATE!\n\n");
}
