/**
 * \file tp3_a.c
 * \brief analyseur syntaxique pour le langage JSON
 * \author NM
 * \author Rémy BOUTELOUP
 * \author Pierrick BOBET
 * \version 0.1
 * \date 04/01/2017
 *
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include "pile.h"
#include "json_tree.h"
#include "tp3_a.h"
#include "tp2_a.h"


const char GRAMMAIRE_LETTRE[17] = {'S', 'O', 'O', 'M', 'M', 'P', 'A', 'A', 'E', 'E', 'V', 'V', 'V', 'V', 'V', 'V', 'V'};
const int GRAMMAIRE_NBR_LETTRE[17] = {1, 2, 3, 1, 3, 3, 2, 3, 1, 3, 1, 1, 1, 1, 1, 1, 1};

/**
 * \fn TSynt * initSyntData(char * _data)
 * \brief fonction qui reserve la memoire et initialise les
 * donnees pour l'analyseur syntaxique
 *
 * \param[in] _data chaine a analyser
 * \return pointeur sur la structure de donnees creee
 */
TSynt * initSyntData(char * _data)
{
	TSynt * _syntData = (TSynt*) malloc (sizeof(TSynt));

	if (_syntData == NULL)
	{
		printf("ERREUR : ALLOCATION DYNAMIQUE IMPOSSIBLE DE _syntData");
		exit(EXIT_FAILURE);
	}

	_syntData->symOk = (char*) malloc (sizeof(char));

	if (_syntData->symOk == NULL)
	{
		printf("ERREUR : ALLOCATION DYNAMIQUE IMPOSSIBLE DE _syntData->symOk");
		exit(EXIT_FAILURE);
	}

	_syntData->nbSymboles = strlen(_data);

	_syntData->data = strndup(_data, strlen(_data));
  _syntData->startPos = strndup(_data, strlen(_data));
  _syntData->startPos[_syntData->nbSymboles] = '#';

	_syntData->seqOk = 0;

	return _syntData;
}

/**
 * \fn void deleteSyntData(TSynt ** _syntData)
 * \brief fonction qui supprime de la memoire les donnees pour
 * l'analyseur syntaxique
 *
 * \param _syntData donnees de l'analyseur syntaxique
 * \return neant
 */
void deleteSyntData(TSynt ** _syntData)
{
    free(_syntData[0]->data);
    free(_syntData[0]->startPos);
    free(_syntData[0]);
}



/**
 * \fn char * subStringSynt(TSynt * _syntData, int nbCaracteres)
 * \brief fonction qui rogne une chaine de caracteres
 *
 * \param lex_data donnees de suivi de l'analyse syntaxique
 * \param[in] nbCaracteres le nombre de caracteres a supprimer
 * \return la nouvelle chaine de caracteres
 */
char * subStringSynt(TSynt * _syntData, int nbCaracteres)
{
	char * temp = (char*) malloc(sizeof(char) * strlen(_syntData->startPos) + 1);
	temp = strcpy(temp, _syntData->startPos);
	free(_syntData->startPos);

	_syntData->startPos = strdup(temp + nbCaracteres);

	if (_syntData->startPos == NULL)
	{
		printf("ERREUR : ALLOCATION DYNAMIQUE IMPOSSIBLE DE _syntData->startPos");
		exit(EXIT_FAILURE);
	}
	free(temp);

	return _syntData->startPos;

}


/**
 * \fn void synt(TSynt * _syntData, TIntPile * pileInt)
 * \brief fonction qui effectue l'analyse syntaxique
 *
 * \param _syntData donnees de suivi de l'analyse syntaxique
 * \param pileInt donnees de suivi de la pile INT
 * \param pileVoid donnees de suivi de la pile VOID
 * \return neant
*/
void synt(TSynt * _syntData, TIntPile * pileInt)
{

	while (1)
	{
		while (isSep(_syntData->startPos[0]))
        	_syntData->startPos = subStringSynt(_syntData, 1);

		int etape = sommetInt(pileInt);
		printf("LETTRE : %d\n", etape);

		switch (etape) {
			case 0:
				switch (_syntData->startPos[0]) {
					case '{':
						deplacement(_syntData, pileInt, 2);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 1:
				switch (_syntData->startPos[0]) {
					case '#':
						printf("-- ACCEPTER -- ");
						exit(0);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 2:
				switch (_syntData->startPos[0]) {
					case '}':
						deplacement(_syntData, pileInt, 5);
						break;
					case 'S':
						deplacement(_syntData, pileInt, 6);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 3:
				switch (_syntData->startPos[0]) {
					case '}':
						deplacement(_syntData, pileInt, 7);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 4:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pileInt, 3);
						break;
					case ',':
						deplacement(_syntData, pileInt, 8);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 5:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pileInt, 1);
						break;
					case ']':
						reduction(_syntData, pileInt, 1);
						break;
					case ',':
						reduction(_syntData, pileInt, 1);
						break;
					case '#':
						reduction(_syntData, pileInt, 1);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 6:
				switch (_syntData->startPos[0]) {
					case ':':
						deplacement(_syntData, pileInt, 9);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 7:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pileInt, 2);
						break;
					case ']':
						reduction(_syntData, pileInt, 2);
						break;
					case ',':
						reduction(_syntData, pileInt, 2);
						break;
					case '#':
						reduction(_syntData, pileInt, 2);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 8:
				switch (_syntData->startPos[0]) {
					case 'S':
						deplacement(_syntData, pileInt, 6);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 9:
				switch (_syntData->startPos[0]) {
					case '{':
						deplacement(_syntData, pileInt, 2);
						break;
					case '[':
						deplacement(_syntData, pileInt, 14);
						break;
					case 'S':
						deplacement(_syntData, pileInt, 15);
						break;
					case 'N':
						deplacement(_syntData, pileInt, 16);
						break;
					case 'T':
						deplacement(_syntData, pileInt, 17);
						break;
					case 'F':
						deplacement(_syntData, pileInt, 18);
						break;
					case 'U':
						deplacement(_syntData, pileInt, 19);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 10:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pileInt, 4);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 11:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pileInt, 12);
						break;
					case ']':
						reduction(_syntData, pileInt, 12);
						break;
					case ',':
						reduction(_syntData, pileInt, 12);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 12:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pileInt, 13);
						break;
					case ']':
						reduction(_syntData, pileInt, 13);
						break;
					case ',':
						reduction(_syntData, pileInt, 13);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 13:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pileInt, 5);
						break;
					case ',':
						reduction(_syntData, pileInt, 5);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 14:
				switch (_syntData->startPos[0]) {
					case '{':
						deplacement(_syntData, pileInt, 2);
						break;
					case '[':
						deplacement(_syntData, pileInt, 14);
						break;
					case ']':
						deplacement(_syntData, pileInt, 22);
						break;
					case 'S':
						deplacement(_syntData, pileInt, 15);
						break;
					case 'N':
						deplacement(_syntData, pileInt, 16);
						break;
					case 'T':
						deplacement(_syntData, pileInt, 17);
						break;
					case 'F':
						deplacement(_syntData, pileInt, 18);
						break;
					case 'U':
						deplacement(_syntData, pileInt, 19);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 15:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pileInt, 10);
						break;
					case ']':
						reduction(_syntData, pileInt, 10);
						break;
					case ',':
						reduction(_syntData, pileInt, 10);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 16:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pileInt, 11);
						break;
					case ']':
						reduction(_syntData, pileInt, 11);
						break;
					case ',':
						reduction(_syntData, pileInt, 11);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 17:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pileInt, 14);
						break;
					case ']':
						reduction(_syntData, pileInt, 14);
						break;
					case ',':
						reduction(_syntData, pileInt, 14);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 18:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pileInt, 15);
						break;
					case ']':
						reduction(_syntData, pileInt, 15);
						break;
					case ',':
						reduction(_syntData, pileInt, 15);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 19:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pileInt, 16);
						break;
					case ']':
						reduction(_syntData, pileInt, 16);
						break;
					case ',':
						reduction(_syntData, pileInt, 16);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 20:
				switch (_syntData->startPos[0]) {
					case ']':
						deplacement(_syntData, pileInt, 23);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 21:
				switch (_syntData->startPos[0]) {
					case ']':
						reduction(_syntData, pileInt, 8);
						break;
					case ',':
						deplacement(_syntData, pileInt, 24);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 22:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pileInt, 6);
						break;
					case ']':
						reduction(_syntData, pileInt, 6);
						break;
					case ',':
						reduction(_syntData, pileInt, 6);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 23:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pileInt, 7);
						break;
					case ']':
						reduction(_syntData, pileInt, 7);
						break;
					case ',':
						reduction(_syntData, pileInt, 7);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 24:
				switch (_syntData->startPos[0]) {
					case '{':
						deplacement(_syntData, pileInt, 2);
						break;
					case '[':
						deplacement(_syntData, pileInt, 14);
						break;
					case ']':
						deplacement(_syntData, pileInt, 22);
						break;
					case 'S':
						deplacement(_syntData, pileInt, 15);
						break;
					case 'N':
						deplacement(_syntData, pileInt, 16);
						break;
					case 'T':
						deplacement(_syntData, pileInt, 17);
						break;
					case 'F':
						deplacement(_syntData, pileInt, 18);
						break;
					case 'U':
						deplacement(_syntData, pileInt, 19);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			case 25:
				switch (_syntData->startPos[0]) {
					case ']':
						reduction(_syntData, pileInt, 9);
						break;
					default :
						printf("Element non reconnu !!! ");
						exit(0);
						break;
				}
				break;
			default:
				printf("Element non reconnu !!! ");
				printf("%d", etape);
				exit(0);
				break;
		}
	}
}

/**
 * \fn void deplacement(TSynt * _syntData, TIntPile * pileInt, TVoidPile * pileVoid, int numEtat)
 * \brief fonction qui place le numéro d'un état dans la pile
 *
 * \param _syntData donnees de suivi de l'analyse syntaxique
 * \param pileInt donnees de suivi de la pile INT
 * \param pileVoid donnees de suivi de la pile VOID
 * \param numEtat numero de l'état concerne
 * \return neant
*/
void deplacement(TSynt * _syntData, TIntPile * pileInt, int numEtat){

	printf("\nUN PASSAGE DEPLACEMENT !\nNum état : %d\n", numEtat);

	// Gestion pile INT
	empilerInt(pileInt, numEtat);
	printf("PILE INT : ");
	printIntPile(pileInt);

	_syntData->seqOk += 1;
	printf("seqOk : %d\n", _syntData->seqOk);
	_syntData->symOk = realloc (_syntData->symOk, (sizeof(char) * _syntData->seqOk) + 1);
	_syntData->symOk[_syntData->seqOk - 1] = _syntData->startPos[0];
	_syntData->symOk[_syntData->seqOk] = '\0';
	printf("symOk : %s\n", _syntData->symOk);

	_syntData->startPos = subStringSynt(_syntData, 1);
}


/**
 * \fn void reduction(TSynt * _syntData, TIntPile * pileInt, TVoidPile * pileVoid, int numEtat)
 * \brief fonction qui effectue la reduction syntaxique
 *
 * \param _syntData donnees de suivi de l'analyse syntaxique
 * \param pileInt donnees de suivi de la pile INT
 * \param pileVoid donnees de suivi de la pile VOID
 * \param numEtat numero de l'état concerne
 * \return neant
*/
void reduction(TSynt * _syntData, TIntPile * pileInt, int numEtat){
	printf("\nUN PASSAGE REDUCTION\n");
	int nbr_symb_pile = GRAMMAIRE_NBR_LETTRE[numEtat];

	printf("PILE : ");
	printIntPile(pileInt);
	printf("numEtat : %d\n", numEtat);
	printf("seqOk : %d\n", nbr_symb_pile);

	while (nbr_symb_pile != 0){

		depilerInt(pileInt);
		nbr_symb_pile--;
	}

	nbr_symb_pile = _syntData->seqOk;

	_syntData->symOk[nbr_symb_pile - GRAMMAIRE_NBR_LETTRE[numEtat]] = GRAMMAIRE_LETTRE[numEtat];
	_syntData->seqOk = _syntData->seqOk - GRAMMAIRE_NBR_LETTRE[numEtat] + 1;
	_syntData->symOk[(nbr_symb_pile + 1) - GRAMMAIRE_NBR_LETTRE[numEtat]] = '\0';

	printf("symOk : %s\n", _syntData->symOk);
	int valeur = goTo(_syntData, pileInt);
	printf("goto : %d\n", valeur);
	empilerInt(pileInt, valeur);
	printf("NOUVELLE PILE : ");
	printIntPile(pileInt);
}


/**
 * \fn int goTo(TSynt * _syntData, TIntPile * pileInt)
 * \brief fonction qui effectue la méthode goto
 *
 * \param _syntData donnees de suivi de l'analyse syntaxique
 * \param pileInt donnees de suivi de la pile INT
 * \param pileVoid donnees de suivi de la pile VOID
 * \return le nouveau numero de l'etat a ajouter a la pile
*/
int goTo(TSynt * _syntData, TIntPile * pileInt){

	int etape = sommetInt(pileInt);

	switch (etape) {
		case 0:
			switch (_syntData->symOk[_syntData->seqOk - 1]) {
				case 'O':
					return 1;
					break;
				}
		case 2:
			switch (_syntData->symOk[_syntData->seqOk - 1]) {
				case 'M':
					return 3;
					break;
				case 'P':
					return 4;
					break;
			}
		case 8:
			switch (_syntData->symOk[_syntData->seqOk - 1]) {
				case 'M':
					return 10;
					break;
				case 'P':
					return 4;
					break;
				}
		case 9:
			switch (_syntData->symOk[_syntData->seqOk - 1]) {
				case 'O':
					return 11;
					break;
				case 'A':
					return 12;
					break;
				case 'V':
					return 13;
					break;
				}
		case 14:
			switch (_syntData->symOk[_syntData->seqOk - 1]) {
				case 'O':
					return 11;
					break;
				case 'A':
					return 12;
					break;
				case 'E':
					return 20;
					break;
				case 'V':
					return 21;
					break;
				}
		case 24:
			switch (_syntData->symOk[_syntData->seqOk - 1]) {
				case 'O':
					return 11;
					break;
				case 'A':
					return 12;
					break;
				case 'E':
					return 25;
					break;
				case 'V':
					return 21;
					break;
				}
	}
}


/**
 * \fn int main()
 * \brief fonction principale
 */
int main(int argc, char *argv[])
{
	// ANALYSE LEXICAL //

	char * test;
	char * obj;
	char * fichierChaine;
	TLex * lex_data;
	TIntPile * pileInt;
	FILE* fichier = NULL;
	long tailleFichier = 0;

	if (argv[1] == NULL)
	{
		printf("Aucun argument fourni ! \n");
		exit(EXIT_FAILURE);
	}


	fichier = fopen(argv[1], "r");

	if(fichier == NULL)
	{
			printf("Erreur avec l'ouverture du fichier !");
			exit(EXIT_FAILURE);
	}

	fseek(fichier, 0, SEEK_END);
	tailleFichier = ftell(fichier);
	rewind(fichier);

	fichierChaine = (char*)malloc(tailleFichier + 1);

	if (fichierChaine == NULL)
	{
		printf("ERREUR : ALLOCATION DYNAMIQUE IMPOSSIBLE DE fichierChaine");
		exit(EXIT_FAILURE);
	}

	printf("\n\n\n\n\n--------------------");

	/*fgets(fichierChaine, tailleFichier, fichier);*/
	fread(fichierChaine, (size_t)tailleFichier, 1, fichier);

	/*test = strdup("{\"obj1\": [ {\"obj2\": 12, \"obj3\":\"text1 \\\"and\\\" text2\"},\n {\"obj4\":314.32} ], \"obj5\": true }");*/
	/*test = strdup("{ \"test\" : 3.14, \"a\" : 1 , \"b\" : 2 , \"c\" : 3 }");*/

	test = strndup(fichierChaine, strlen(fichierChaine));

	fclose(fichier);

	printf("\n-- CHAINE DE DEPART -- \n\n%s",test);

	lex_data = initLexData(test);

	printf("\n -- Affichage des léxèmes reconnus par l'analyseur lexical --\n\n");
	obj = formatLex(lex_data);

  	printLexData(lex_data);
	deleteLexData(&lex_data);

	printf("\n -- Affichage de la chaine formatée par l'analyseur lexical -- \n\n");
	printf("%s\n\n", obj);

	free(test);

	// ANALYSE SYNTAXIQUE //
	TSynt * synt_data;
	synt_data = initSyntData(obj);
	pileInt = initIntPile();

	synt(synt_data, pileInt);

	deleteIntPile(&pileInt);
	deleteSyntData(&synt_data);
	free(obj);

	return 0;
	}
