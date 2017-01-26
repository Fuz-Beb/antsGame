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
	// Allocation de la structure
	TSynt * _syntData = (TSynt*) malloc (sizeof(TSynt));

	if (_syntData == NULL)
	{
		printf("ERREUR : ALLOCATION DYNAMIQUE IMPOSSIBLE DE _syntData");
		exit(EXIT_FAILURE);
	}

	// Allocation d'une chaine contenant les lettres de la grammaire qui a été reconnue
	_syntData->symOk = (char*) malloc (sizeof(char) * 1);

	if (_syntData->symOk == NULL)
	{
		printf("ERREUR : ALLOCATION DYNAMIQUE IMPOSSIBLE DE _syntData->symOk");
		exit(EXIT_FAILURE);
	}

	_syntData->nbSymboles = strlen(_data);

	// Allocation d'une chaine contenant l'état d'avancement de l'analyseur
	_syntData->startPos = (char*) malloc(sizeof(char) * (strlen(_data) + 2));

	if (_syntData->symOk == NULL)
	{
		printf("ERREUR : ALLOCATION DYNAMIQUE IMPOSSIBLE DE _syntData->symOk");
		exit(EXIT_FAILURE);
	}

	_syntData->startPos = strcpy(_syntData->startPos, _data);
	_syntData->startPos[_syntData->nbSymboles] = '#';
	_syntData->startPos[_syntData->nbSymboles + 1] = '\0';

	_syntData->data = strndup(_data, strlen(_data));
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
    free(_syntData[0]->symOk);
    free(_syntData[0]);
}


/**
 * \fn int analyseurLR(TSynt * _syntData, TIntPile * pileInt)
 * \brief fonction qui effectue l'analyse syntaxique
 *
 * \param _syntData donnees de suivi de l'analyse syntaxique
 * \param pileInt donnees de suivi de la pile INT
 * \param pileVoid donnees de suivi de la pile VOID
 * \return neant
*/
int analyseurLR(TSynt * _syntData, TIntPile * pileInt)
{
	// Valeur de retour
	unsigned int returnValue = 2;

	// Tant qu'une erreur ou une acception ne survient pas, je continue
	while (returnValue == 2)
	{
		// Test si présence de sépérateur
		while (isSep(_syntData->startPos[0]))
        	_syntData->startPos = str_cut(_syntData->startPos, 1);

		int etape = sommetInt(pileInt);

		// Application de la table SLR
		switch (etape) {
			case 0:
				switch (_syntData->startPos[0]) {
					case '{':
						deplacement(_syntData, pileInt, 2);
						break;
					default :
						returnValue = 0;
						break;
				}
				break;
			case 1:
				switch (_syntData->startPos[0]) {
					case '#':
						returnValue = 1;
						break;
					default :
						returnValue = 0;
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
						returnValue = 0;
						break;
				}
				break;
			case 3:
				switch (_syntData->startPos[0]) {
					case '}':
						deplacement(_syntData, pileInt, 7);
						break;
					default :
						returnValue = 0;
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
						returnValue = 0;
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
						returnValue = 0;
						break;
				}
				break;
			case 6:
				switch (_syntData->startPos[0]) {
					case ':':
						deplacement(_syntData, pileInt, 9);
						break;
					default :
						returnValue = 0;
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
						returnValue = 0;
						break;
				}
				break;
			case 8:
				switch (_syntData->startPos[0]) {
					case 'S':
						deplacement(_syntData, pileInt, 6);
						break;
					default :
						returnValue = 0;
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
						returnValue = 0;
						break;
				}
				break;
			case 10:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pileInt, 4);
						break;
					default :
						returnValue = 0;
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
						returnValue = 0;
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
						returnValue = 0;
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
						returnValue = 0;
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
						returnValue = 0;
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
						returnValue = 0;
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
						returnValue = 0;
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
						returnValue = 0;
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
						returnValue = 0;
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
						returnValue = 0;
						break;
				}
				break;
			case 20:
				switch (_syntData->startPos[0]) {
					case ']':
						deplacement(_syntData, pileInt, 23);
						break;
					default :
						returnValue = 0;
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
						returnValue = 0;
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
						returnValue = 0;
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
						returnValue = 0;
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
						returnValue = 0;
						break;
				}
				break;
			case 25:
				switch (_syntData->startPos[0]) {
					case ']':
						reduction(_syntData, pileInt, 9);
						break;
					default :
						returnValue = 0;
						break;
				}
				break;
			default:
				returnValue = 0;
				break;
		}
	}
	return returnValue;
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

	// Gestion pile INT
	empilerInt(pileInt, numEtat);

	// Nous avons reconnu un caractère. Modifier des chaines de la structure TSynt
	_syntData->seqOk += 1;
	_syntData->symOk = realloc (_syntData->symOk, (sizeof(char) * _syntData->seqOk) + 1);
	_syntData->symOk[_syntData->seqOk - 1] = _syntData->startPos[0];
	_syntData->symOk[_syntData->seqOk] = '\0';

	_syntData->startPos = str_cut(_syntData->startPos, 1);
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

	int valeur = 0;

	// Récupération de nombre de lettre à dépiler de la pile
	int nbr_symb_pile = GRAMMAIRE_NBR_LETTRE[numEtat];

	// Dépiler tant que la longueur n'est pas atteinte
	while (nbr_symb_pile != 0)
	{
		depilerInt(pileInt);
		nbr_symb_pile--;
	}

	nbr_symb_pile = _syntData->seqOk;

	_syntData->symOk[nbr_symb_pile - GRAMMAIRE_NBR_LETTRE[numEtat]] = GRAMMAIRE_LETTRE[numEtat];
	_syntData->seqOk = _syntData->seqOk - GRAMMAIRE_NBR_LETTRE[numEtat] + 1;
	_syntData->symOk[(nbr_symb_pile + 1) - GRAMMAIRE_NBR_LETTRE[numEtat]] = '\0';

	// Appel de la table goTo pour trouver le nouvel état
	valeur = goTo(_syntData, pileInt);
	empilerInt(pileInt, valeur);
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
	char * test, * obj, * fichierChaine;
	TLex * lex_data;
	TIntPile * pileInt;
	FILE* fichier = NULL;
	long tailleFichier = 0;
	unsigned int result;

	if (argv[1] == NULL)
	{
		printf("Aucun argument fourni ! \n");
		exit(EXIT_FAILURE);
	}

	// Ouverture du fichier demandé par l'utilisateur
	fichier = fopen(argv[1], "r");

	if(fichier == NULL)
	{
		printf("Erreur avec l'ouverture du fichier !");
		exit(EXIT_FAILURE);
	}

	// Calcul de la taille du fichier pour le malloc
	fseek(fichier, 0, SEEK_END);
	tailleFichier = ftell(fichier);
	rewind(fichier);

	// Le contenu du fichier sera mis dans la chaine fichierChaine
	fichierChaine = (char*)malloc(tailleFichier + 1);

	if (fichierChaine == NULL)
	{
		printf("ERREUR : ALLOCATION DYNAMIQUE IMPOSSIBLE DE fichierChaine");
		exit(EXIT_FAILURE);
	}

	// Ajout du contenu du fichier dans fichierChaine
	fread(fichierChaine, (size_t)tailleFichier, 1, fichier);
	test = strndup(fichierChaine, tailleFichier);
	fclose(fichier);

	// Initialisation de la structure pour l'analyse syntaxique
	lex_data = initLexData(test);

	// Récupére la chaine "formaté" de l'analyseur lexical
	obj = formatLex(lex_data);

	// Libération de mémoire
	deleteLexData(&lex_data);
	free(test);
	free(fichierChaine);


	// ANALYSE SYNTAXIQUE //
	TSynt * synt_data;
	synt_data = initSyntData(obj);
	pileInt = initIntPile();

	// Appel de l'analyseur LR
	result = analyseurLR(synt_data, pileInt);

	// Affichage du resultat de l'analyse
	if (result == 1)
		printf("\nAccepté ! \nValeur renvoyée : 1\n");
	else
		printf("\nRefusé ! \nValeur renvoyée : 0\n");

	// Libération de la mémoire
	deleteIntPile(&pileInt);
	deleteSyntData(&synt_data);
	free(obj);
	
	return 0;
}
