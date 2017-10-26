#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max_champs 25// Nombre maximum de champs d'une table
#define lgMot 30// Longueur maximale d'une chaine de caract�res
#define lgMax 80// Longueur maximale d'une ligne de commande
#define max_enregistrement 25//Nombre maximum d'enregistrement
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
	Champ schema[max_champs];//schema tableau statique sur-dimensionn� � max_champs
	unsigned int nbChamps;// nombre de champs de la table
	unsigned int nbEnregistrement;
	Enregistrement enregistre[max_enregistrement];
}Table;




void afficher_schema(const Table* t);// Fonction afficher_schema
void create_table(Table* t);// Fonction create_table
void insert_enregistrement(Table* t);// Fonction insert_enregistrement
void afficher_enregistrements(const Table* t);// Fonction afficher_enregistrements
void delete_enregistrement(Table* t);// Fonction delete_enregistrement
void afficher_enregistrement(const Table* t);// Fonction afficher_enregistrement
void delete_table(Table* t);// Fonction delete_table
int main() {
	char mot[lgMot + 1];// +1 pour stocker le caract�re '\0'
	Table t;
	t.nbEnregistrement = 0;
	strcpy(t.nom, "");
	while (1) {
		scanf("%s", mot);// R�cuperation de la commande

		if (strcmp(mot, "Create_table") == 0) {
			create_table(&t);//appel de la fonction create_table
		}
		else if (strcmp(mot, "Afficher_schema") == 0) {
			afficher_schema(&t);//appel de la fonction afficher_schema
		}
		else if (strcmp(mot, "Insert_enregistrement") == 0) {
			insert_enregistrement(&t);//appel de la fonction insert_enregistrement
		}
		else if (strcmp(mot, "Afficher_enregistrements") == 0) {
			afficher_enregistrements(&t);//appel de la fonction afficher_enregistrements
		}
		else if (strcmp(mot, "Delete_enregistrement") == 0) {
			delete_enregistrement(&t);//appel de la fonction delete_enregistrement
		}
		else if (strcmp(mot, "Afficher_enregistrement") == 0) {
			afficher_enregistrement(&t);//appel de la fonction afficher_enregistrement
		}
		else if (strcmp(mot, "Delete_table") == 0) {
			delete_table(&t);// appel de la fonction delete_table
		}
		else if (strcmp(mot, "Exit") == 0) {
			exit(0); // sortie du programme principal
		}
	}
}
void create_table(Table* t) {
	char temp[lgMot + 1];
	scanf("%s", temp);// R�cup�ration nom de la table
	if (strcmp(t->nom, "") == 0) {// V�rifie si une table est active
		strcpy(t->nom, temp);
		scanf("%u", &(t->nbChamps));// R�cuperation nombre de champs
		for (unsigned int i = 0; i < t->nbChamps; ++i) {
			scanf("%s %s", t->schema[i].nom, t->schema[i].type);// R�cup�ration de chaque champ
		}
	}
	else {
		printf("table existante\n");
	}
}
void afficher_schema(const Table* t) {
	char mot[lgMot + 1];
	scanf("%s", mot);// R�cup�ration nom de la table
	if (strcmp(mot, t->nom) == 0) {// V�rifie si table existe
		printf("%s %u\n", t->nom, t->nbChamps);
		for (unsigned int i = 0; i < t->nbChamps; ++i)
			printf("%s %s\n", t->schema[i].nom, t->schema[i].type);// Affichage champs

	}
	else
		printf("table inconnue\n");
}
void insert_enregistrement(Table* t) {
	char mot[lgMot + 1];
	scanf("%s", mot);// R�cup�ration nom de la table
	if (strcmp(mot, t->nom) == 0) {// V�rifie si table existe
		for (int i = 0; i < t->nbChamps; ++i) {
			scanf("%s", t->enregistre[t->nbEnregistrement].data[i].motdat);//R�cup�ration enregistrement
		}
		++t->nbEnregistrement;//incr�mentation du nombre d'enregistrement
	}
	else {
		printf("table inconnue\n");
	}
}

void afficher_enregistrements(const Table* t) {
	char mot[lgMot + 1];
	scanf("%s", mot);// R�cup�ration nom de la table
	if (strcmp(mot, t->nom) == 0) {// V�rifie si table existe
		for (int i = 0; i < t->nbEnregistrement; ++i) {
			printf("%d", i + 1);// Affichage du num�ro de chaque enregistrement
			for (int r = 0; r < t->nbChamps; ++r) {
				printf(" %s %s", t->schema[r].type, t->enregistre[i].data[r].motdat);//Affichage enregistrement
			}
			printf("\n");
		}
	}
	else {
		printf("table inconnue\n");
	}
}
void delete_enregistrement(Table* t) {
	unsigned int i, r;
	char mot[lgMot + 1];
	scanf("%s", mot);// R�cup�ration nom de la table
	if (strcmp(mot, t->nom) == 0) {// V�rifie si table existe
		scanf("%s", mot);// R�cup�ration du num�ro d'enregistrement
		unsigned int moti = atoi(mot);// Convertie la chaine de caract�res en entier
		for (r = moti; r < t->nbEnregistrement; ++r) {
			for (i = 0; i < t->nbChamps; ++i)
				strcpy(t->enregistre[r - 1].data[i].motdat, t->enregistre[r].data[i].motdat);//permet le d�calage des num�ros des enregistrements
		}
		for (i = 0; i < t->nbChamps; ++i)
			strcpy(t->enregistre[t->nbEnregistrement - 1].data[i].motdat, "");//initialise le dernier enregistrement � chaine vide
		t->nbEnregistrement--;//permet d'�liminer le num�ros du dernier enregistrement
	}
}
void afficher_enregistrement(const Table* t) {
	char mot[lgMot + 1];
	scanf("%s", mot);// R�cup�ration nom de la table
	if (strcmp(mot, t->nom) == 0) {// V�rifie si table existe
		unsigned int numLigne;
		scanf("%u", &numLigne);// R�cup�ration du num�ro d'enregistrement
		printf("%u", numLigne);// Affichage du num�ro d'enregistrement
		if (numLigne <= t->nbEnregistrement && numLigne > 0) {
			for (int r = 0; r < t->nbChamps; r++) {
				printf(" %s %s", t->schema[r].type, t->enregistre[numLigne - 1].data[r].motdat);//Affichage de l'enregistrement
			}
			printf("\n");// Pour aller � la ligne
		}
		else {
			printf("enregistrement inconnu\n");
		}
	}
	else {
		printf("table inconnue\n");
	}
}

void delete_table(Table* t) {
	char mot[lgMot + 1];
	scanf("%s", mot);// R�cup�ration nom de la table
	if (strcmp(mot, t->nom) != 0) {
		printf("table inconnue\n");
		return;
	}
	for (unsigned int i = 0; i < t->nbChamps; ++i) {
		strcpy(t->schema[i].nom, "");
		strcpy(t->schema[i].type, "");
		for (unsigned int r = 0; r < t->nbEnregistrement; ++r)
			strcpy(t->enregistre[r].data[i].motdat, "");
	}
	strcpy(t->nom, "");
	t->nbChamps = 0;
	t->nbEnregistrement = 0;
}

