#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max_champs 25// Nombre maximum de champs d'une table
#define lgMot 30// Longueur maximale d'une chaine de caractères
#define lgMax 80// Longueur maximale d'une ligne de commande
#define max_enregistrement 25
#pragma warning (disable:4996)


typedef struct {
	char motdat[lgMot + 1];
}Data;


typedef struct {
	Data data[max_champs];
}Enregistrement;

typedef struct {
	char nom[lgMot + 1];// nom du champ
	char type[lgMot + 1];// type du champ
}Champ;

typedef struct {
	char nom[lgMot + 1];// nom de la table
	Champ schema[max_champs];//schema tableau statique sur-dimensionné à max_champs
	unsigned char nbChamps;// nombre de champs de la table
	unsigned int nbEnregistrement;
	Enregistrement enregistre[max_enregistrement];
}Table;




void afficher_schema(Table* t);// Fonction afficher_schema
void create_table(Table* t);// Fonction create_table
void insert_enregistrement(Table* t);
void afficher_enregistrement(Table* t);

int main() {

	char mot[lgMot + 1];// +1 pour stocker le caractère '\0'
	Table t;
	t.nbEnregistrement = 0;

	while (1) {
		//printf("Entrer une commande");
		scanf("%s", mot);// Récuperation de la commande

		if (strcmp(mot, "Create_table") == 0) {
			create_table(&t);//appel de la fonction create_table
		}
		else if (strcmp(mot, "Afficher_schema") == 0) {
			afficher_schema(&t);//appel de la fonction afficher_schema
		}
		else if (strcmp(mot, "Insert_enregistrement") == 0) {
			insert_enregistrement(&t);
		}
		else if (strcmp(mot, "Afficher_enregistrements") == 0) {
			afficher_enregistrement(&t);
		}
		else if (strcmp(mot, "Exit") == 0) {
			exit(0); // sortie du programme principal
		}
	}
}
void create_table(Table* t) {
	char temp[lgMot + 1];
	scanf("%s", &temp);// Récupération nom de la table
	if (strcmp(temp, t->nom) != 0) {
		strcpy(t->nom, temp);
		scanf("%s", temp);// Récuperation nombre de champs
		t->nbChamps = atoi(temp);
		for (unsigned int i = 0; i < t->nbChamps; ++i)
			scanf("%s %s", t->schema[i].nom, t->schema[i].type);// Récupération de chaque champ
	}
	else
		printf("table existante\n");
}
void afficher_schema(Table* t) {
	char mot[lgMot + 1];
	scanf("%s", mot);// Récupération nom de la table
	if (strcmp(mot, t->nom) == 0) {
		printf("%s %s\n", &t->nom, &t->nbChamps);
		for (unsigned int i = 0; i < atoi(&(t->nbChamps)); ++i)
			printf("%s %s\n", t->schema[i].nom, t->schema[i].type);// Affichage champs

	}
	else
		printf("table inconnue\n");
}
void insert_enregistrement(Table* t) {
	char mot[lgMot + 1];
	scanf("%s", mot);
	if (strcmp(mot, t->nom) == 0) {
		for (int i = 0; i < t->nbChamps; ++i) {
			scanf("%s", t->enregistre[t->nbEnregistrement].data[i].motdat);

		}
		t->nbEnregistrement++;
	}
	else {
		printf("Table Inconnue\n");
	}
}


void afficher_enregistrement(Table* t) {
	char mot[lgMot + 1];
	scanf("%s", mot);
	if (strcmp(mot, t->nom) == 0) {
		for (int i = 0; i < t->nbEnregistrement; ++i) {
			printf("%d", i + 1);
			for (int r = 0; r < t->nbChamps; ++r) {
				printf("%s %s", t->schema[r].type, t->enregistre[i].data[r].motdat);

			}

		}
	}
	else {
		printf("Enregistrement Inconnue");
	}







}