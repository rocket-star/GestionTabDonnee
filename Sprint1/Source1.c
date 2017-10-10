#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max_champs 25
#define lgMot 30
#define lgMax 80
#pragma warning (disable:4996)



typedef struct {
	char nom[lgMot + 1];
	char type[lgMot + 1];
}Champ;


typedef struct {
	char nom[lgMot + 1];
	Champ schema[max_champs];
	unsigned char nbChamps;// nombre de champs de la table
}Table;








void create_table(Table* t) {
	char mot[lgMot + 1];
	if (strcmp(t->nom, "") == 0) {
		scanf("%s", &mot);
		strcpy(t->nom, &mot);
		printf("Entrez un nombre de champs");
		scanf("%s", mot);
		t->nbChamps = atoi(mot);
		for (unsigned int i = 0; i < t->nbChamps; ++i) {
			printf("Nom du champs n°%d", i);
			scanf("%s", &mot);
			strcpy(t->schema[i].nom, &mot);
			printf("Type du champs n°%d", i);
			scanf("%s", &mot);
			strcpy(t->schema[i].type, &mot);
		}
	}
	else {
		printf("Table Existante\n");
	}
	return;

}

void afficher_schema(Table*t) {
	char mot[lgMot + 1];
	scanf("%s", mot);

	if (strcmp(mot, t->nom) == 0) {
		printf("%s %d\n", t->nom, t->nbChamps);
		for (unsigned int i = 0; i < t->nbChamps; ++i) {
			printf("%s %s", t->schema[i].nom, t->schema[i].type);
		}
	}
	else {
		printf("Table Inconnu\n");
	}
	return;
}

int main() {

	char mot[lgMot + 1];
	Table t;
	strcpy(t.nom, "");
	Champ c;
	while (1) {
		printf("Entrer une commande");
		scanf("%s", &mot);

		if (strcmp(mot, "Create_table") == 0) {
			create_table(&t);
		}
		if (strcmp(mot, "Afficher_schema") == 0) {
			afficher_schema(&t);

		}
	}
	system("pause");
}