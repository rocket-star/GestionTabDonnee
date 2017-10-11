#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max_champs 25// Nombre maximum de champs d'une table
#define lgMot 30// Longueur maximale d'une chaine de caract�res
#define lgMax 80// Longueur maximale d'une ligne de commande
#pragma warning (disable:4996)

typedef struct {
	char nom[lgMot + 1];// nom du champ
	char type[lgMot + 1];// type du champ
}Champ;

typedef struct {
	char nom[lgMot + 1];// nom de la table
	Champ schema[max_champs];//schema tableau statique sur-dimensionn� � max_champs
	unsigned char nbChamps;// nombre de champs de la table
}Table;

void afficher_schema(Table* t);// Fonction afficher_schema
void create_table(Table* t);// Fonction create_table

int main() {

	char mot[lgMot + 1];// +1 pour stocker le caract�re '\0'
	Table t;
	while (1) {
		//printf("Entrer une commande");
		scanf("%s", mot);// R�cuperation de la commande

		if (strcmp(mot, "Create_table") == 0) {
			create_table(&t);//appel de la fonction create_table
		}
		else if (strcmp(mot, "Afficher_schema") == 0) {
			afficher_schema(&t);//appel de la fonction afficher_schema
		}
		else if (strcmp(mot, "Exit") == 0) {
			exit(0); // sortie du programme principal 
		}
	}
}
void create_table(Table* t) {
	char temp[lgMot + 1];
	scanf("%s", &temp);// R�cup�ration nom de la table
	if (strcmp(temp,t->nom)!=0){	
		strcpy(t->nom, temp);
		scanf("%s", &(t->nbChamps));// R�cuperation nombre de champs 
		for (unsigned int i = 0; i < atoi(&(t->nbChamps)); ++i)
			scanf("%s %s", t->schema[i].nom, t->schema[i].type);// R�cup�ration de chaque champ
	}
	else
		printf("table existante\n");
}
void afficher_schema(Table* t) {
	char mot[lgMot + 1];
	scanf("%s", mot);// R�cup�ration nom de la table
	if (strcmp(mot, t->nom) == 0) {
		printf("%s %s\n", &t->nom, &t->nbChamps);
		for (unsigned int i = 0; i < atoi(&(t->nbChamps)); ++i)
			printf("%s %s\n", t->schema[i].nom, t->schema[i].type);// Affichage champs
	}
	else 
		printf("table inconnue\n");
}