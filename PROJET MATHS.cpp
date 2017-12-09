//http://mathfaculty.fullerton.edu/mathews/n2003/PivotingMod.html
/************************************************************************************
Projet Maths
Eleve: Bruno Bernard
Fichier: SystemeLineaire.cpp
ver: 6
************************************************************************************/
#include <iostream>
#include <cmath>
#include <iomanip>
#define size 10000

using namespace std;

 //declaration variable
float precision = 0.00001;
int rows, col,positioni,positionj;
int pivotcolonne[size]; //capture de la colonne
//prototype des fonctions
int taille();
void initialisaition(float a[][size],float b[]);
void substitutionremontee(float a[][size], float b[]);
void pivotTotaletElimination(float a[][size], float b[]);

int main() // programme PRINCIPALE
{
	int n = taille();
	float a[n][size],b[n]; //matrice A et matrice B

	initialisaition(a,b);
	cout << "\n\n***************************************************************\n APRES ELIMINATION: \n\n";
	pivotTotaletElimination(a,b);
	substitutionremontee(a,b);

	return 0;
}
void pivotTotaletElimination(float a[][size], float b[]) //PIVOT TOTAL ET ELIMINATION
{
	float x;
	int pivotligne; // capture de la colonne
	for(int i = 0; i < rows-1; i++)
	{	
		pivotcolonne[i] = i;
		pivotligne = i;
		x = a[i][i];
		for(int z = i; z < rows; z++)
			for(int j = i; j <= col-1; j++)
			{
				
				if(abs(a[z][j]) > abs(x))
				{
					x = a[z][j]; // si le nombre est plus grand, le plus grand est affecter dans x pour etre comparer aux autres
					pivotligne = j; // capturer la position du plus grand pivot
					pivotcolonne[i] = z;
				}
			}
		float temp[size];
		for(int j = 0; j <= rows; j++) //avec la capture de la ligne faire permutation ligne avec matrice augmenter
		{
				temp[j] = a[i][j]; 
				a[i][j]  = a[pivotligne][j];
				a[pivotligne][j] = temp[j];				
		}

		for(int j = 0; j < col; j++) // avec la capture de la colonne faire permutation colonne
		{		
				temp[j] = a[j][i];
				a[j][i] = a[j][pivotcolonne[i]];
				a[j][pivotcolonne[i]] = temp[j];				
		}
		float roundup;
		for(int j = i+1; j <= col; j++) //faire Elimination
		{
			float p = (a[j][i])/(a[i][i]);
			for(int k = i; k <= col; k++){
				a[j][k] = a[j][k] - p* a[i][k];	
				roundup = abs(a[j][k]);
				if(precision > roundup && roundup != 0)
				{
					//PEUT AJOUTER UNE PRECISION
				}
			}	
		}
		for(int i = 1; i <= rows; i++) //apres avoir fait permutation avec la matrice augmenter, changer aussi la valeur de B
		{
			for(int j = col; j <= col; j++)
			{
				b[i-1] = a[i-1][col];
			}
		}
	}
	cout << "\n\nVOTRE MATRICE A TRIANGULAIRE SUPERIEUR EST: \n\n";
	for(int i=0; i <= rows-1; ++i){
		for(int j = 0; j <= col-1; j++)
		{
			if( abs(a[i][j]) < 1e-006)
				cout << setw(9) << 0 << " ";
			else
				cout << setw(9) << a[i][j] << " ";
		}
		cout << endl;
	}
}
void substitutionremontee(float a[][size], float b[]) //SUBSTITUTION REMONTEE
{
	int position[size];
	for(int n = 0; n < size; n++)
		position[n] = n;
	
	float temp;
	for(int p = 0; p < col -1; p++)
	{
			temp = position[p];
			position[p] = position[pivotcolonne[p]];
			position[pivotcolonne[p]] = temp;
	}
	
	
	cout << "\n\nLa reponse de vos inconnus est: \n\n";
	
	float x[size];
	x[position[col-1]] = (b[col-1] / a[rows-1][col-1]);
	
	for(int i = col-2; i >= 0; i--) 
	{
		float somme = 0;
		for(int k = i + 1; k < col; k++ )
		{
			somme = somme + (a[i][k] * x[position[k]]); // calcul de substitution remontee.
		}
		
		b[i] = b[i] - somme;
		x[position[i]] = b[i] / a[i][i];
	}


	for(int i = 0; i < col; i++)
	{
		if( abs(x[i]) < 1e-006)
			cout << "X" << i+1 << " = " << 0 << endl;
		else
			cout <<"X" <<i +1 << " = " <<x[i] << endl;
	}
}
void initialisaition(float a[][size], float b[]) //affectation de la matrice A et B
{
	system("cls");
	cout << "POUR VOTRE MATRICE A:\n\n";
	for(int i=0; i <= rows-1; ++i){
		for(int j = 0; j <= col-1; j++)
		{
			cout <<"Veuillez inserez a"<<i+1<<j+1 << ": ";
			cin >> a[i][j];
			
			if(precision > abs(a[i][j]) && abs(a[i][j] != 0))//si erreur de precision lors de l'initialisation, retourner l'erreur
				{
					do{
						a[i][j] = 0;
						cout << "ERREUR! Veuillez re-entrez un nombre plus grand dans a" << i+1 << j+1 << ", SVP: " ;
						cin >> a[i][j];
					}while(!(precision <= a[i][j]));
				}
		}
	}
	system("cls");
	cout << "VOTRE MATRICE A EST MAINTENANT: \n\n";
	
	for(int i=0; i <= rows-1; ++i){
		for(int j = 0; j <= col-1; j++)
		{
			cout << setw(5) << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\n\nPOUR VOTRE MATRICE B:\n\n";
	for(int i = 1; i <= rows; i++)
		for(int j = col; j <= col; j++)
		{
			cout << "Veuillez inserez b" <<i <<": ";
			cin >> a[i-1][col];
		}
		
		for(int i = 1; i <= rows; i++)
		{
			for(int j = col; j <= col; j++)
			{
				b[i-1] = a[i-1][col];
			}
		
		}
	
	cout << "\n\nVOTRE MATRICE B EST MAINTENANT: \n";
	cout << endl;
	for(int i = 1; i <= rows; i++)
	{
		for(int j = col; j <= col; j++)
		{
			b[i-1] = a[i-1][col];
			cout << b[i-1];
		}
		cout << endl;
	}
	
}
int taille() //definir taille et precision de la matrice.
{
	
	system("cls");
	cout <<"Veuillez entrer la taille de la matrice d'ordre n: ";
	cin >> rows;
	col = rows;
	return rows;
}
