/*Nom de fichier: Interpr�teur de commandes sur une table de donn�es
*Nom et groupe des auteurs: Rudy Fernando Groupe 105 et Romain Madi Groupe 105
*Date de cr�ation:02/10/2017
*/
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



/*
 Commande d'affichage du sch�ma d'une table de donn�es
 [in] t, Table � afficher
*/
void afficher_schema(const Table* t);

/*
 Commande de cr�ation d'une table de donn�es
 [in] t, Table avant la cr�ation d'une table de donn�es
 [out] t, Table apr�s la cr�ation d'une table de donn�es
*/
void create_table(Table* t);

/*
 Commande d'insertion d'une ligne de donn�es
 [in] t, Table avant enregistrement
 [out] t, Table apr�s enregistrement
*/
void insert_enregistrement(Table* t);

/*
 Commande d'affichage de toutes les lignes de donn�es
 [in] t, Table � afficher
*/
void afficher_enregistrements(const Table* t);

/*
 Commande de destruction d'une ligne de donn�es
 [in] t, Table avant destruction d'une ligne de donn�es
 [out] t, Table apr�s destruction d'une ligne de donn�es
*/
void delete_enregistrement(Table* t);

/*
 Commande d'affichage d'une ligne de donn�es
 [in] t, Table contenant la ligne de donn�es � afficher
*/
void afficher_enregistrement(const Table* t);

/*
 Commande de destruction d'une table de donn�es
 [in] t, Table avant destruction d'une table de donn�es
 [out] t, Table apr�s destruction d'une table de donn�es
*/
void delete_table(Table* t);


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
	for (unsigned int i = 0; i < t->nbChamps; ++i) {// permet d'initialiser les champs � chaine vide
		strcpy(t->schema[i].nom, "");
		strcpy(t->schema[i].type, "");
		for (unsigned int r = 0; r < t->nbEnregistrement; ++r)// pour initialiser les enregistrements � chaine vide
			strcpy(t->enregistre[r].data[i].motdat, "");
	}
	strcpy(t->nom, "");// initialise le nom de la table � chaine vide
	t->nbChamps = 0;// initialise le nombre de champ � 0
	t->nbEnregistrement = 0;// initialise le nombre d'enregistrement � 0
}

