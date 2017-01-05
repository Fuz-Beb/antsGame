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
#include "tp2_a.h"
#include "tp3_a.h"

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
    _syntData->startPos[_syntData->nbSymboles + 1] = '\0';
	
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
	char buffer[2048];
	memset(buffer, '\0', 2048);
	strncpy(buffer, _syntData->startPos + nbCaracteres, strlen(_syntData->startPos) - nbCaracteres);
	free(_syntData->startPos);
	_syntData->startPos = strndup(buffer, strlen(buffer) + 1);
	return _syntData->startPos;
}


/**
 * \fn void synt(TSynt * _syntData, TIntPile * pile)
 * \brief fonction qui effectue l'analyse syntaxique
 *
 * \param _syntData donnees de suivi de l'analyse syntaxique
 * \return neant
*/
void synt(TSynt * _syntData, TIntPile * pile)
{
	int etape = 0;

	while (1)
	{
		while (isSep(_syntData->startPos[0]))
        	_syntData->startPos = subStringSynt(_syntData, 1);

		int etape = sommetInt(pile);
		printf("LETTRE : %d\n", etape);

		switch (etape) {
			case 0:
				switch (_syntData->startPos[0]) {
					case '{':
						deplacement(_syntData, pile, 2);
						break;
				}
				break;
			case 1:
				switch (_syntData->startPos[0]) {
					case '#':
						printf("-- ACCEPTER -- ");
						exit(0);
						break;
				}
				break;
			case 2:
				switch (_syntData->startPos[0]) {
					case '}':
						deplacement(_syntData, pile, 5);
						break;
					case 'S':
						deplacement(_syntData, pile, 6);
						break;
				}
				break;
			case 3:
				switch (_syntData->startPos[0]) {
					case '}':
						deplacement(_syntData, pile, 7);
						break;
				}
				break;
			case 4:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pile, 3);
						break;
					case ',':
						deplacement(_syntData, pile, 8);
						break;
				}
				break;
			case 5:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pile, 1);
						break;
					case ']':
						reduction(_syntData, pile, 1);
						break;
					case ',':
						reduction(_syntData, pile, 1);
						break;
					case '#':
						reduction(_syntData, pile, 1);
						break;
				}
				break;
			case 6:
				switch (_syntData->startPos[0]) {
					case ':':
						deplacement(_syntData, pile, 9);
						break;
				}
				break;
			case 7:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pile, 2);
						break;
					case ']':
						reduction(_syntData, pile, 2);
						break;
					case ',':
						reduction(_syntData, pile, 2);
						break;
					case '#':
						reduction(_syntData, pile, 2);
						break;
				}
				break;
			case 8:
				switch (_syntData->startPos[0]) {
					case 'S':
						deplacement(_syntData, pile, 6);
						break;
				}
				break;
			case 9:
				switch (_syntData->startPos[0]) {
					case '{':
						deplacement(_syntData, pile, 2);
						break;
					case '[':
						deplacement(_syntData, pile, 14);
						break;
					case 'S':
						deplacement(_syntData, pile, 15);
						break;
					case 'N':
						deplacement(_syntData, pile, 16);
						break;
					case 'T':
						deplacement(_syntData, pile, 17);
						break;
					case 'F':
						deplacement(_syntData, pile, 18);
						break;
					case 'U':
						deplacement(_syntData, pile, 19);
						break;
				}
				break;
			case 10:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pile, 4);
						break;
				}
				break;
			case 11:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pile, 12);
						break;
					case ']':
						reduction(_syntData, pile, 12);
						break;
					case ',':
						reduction(_syntData, pile, 12);
						break;
				}
				break;
			case 12:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pile, 13);
						break;
					case ']':
						reduction(_syntData, pile, 13);
						break;
					case ',':
						reduction(_syntData, pile, 13);
						break;
				}
				break;
			case 13:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pile, 5);
						break;
					case ',':
						reduction(_syntData, pile, 5);
						break;
				}
				break;
			case 14:
				switch (_syntData->startPos[0]) {
					case '{':
						deplacement(_syntData, pile, 2);
						break;
					case '[':
						deplacement(_syntData, pile, 14);
						break;
					case ']':
						deplacement(_syntData, pile, 22);
						break;
					case 'S':
						deplacement(_syntData, pile, 15);
						break;
					case 'N':
						deplacement(_syntData, pile, 16);
						break;
					case 'T':
						deplacement(_syntData, pile, 17);
						break;
					case 'F':
						deplacement(_syntData, pile, 18);
						break;
					case 'U':
						deplacement(_syntData, pile, 19);
						break;
				}
				break;
			case 15:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pile, 10);
						break;
					case ']':
						reduction(_syntData, pile, 10);
						break;
					case ',':
						reduction(_syntData, pile, 10);
						break;
				}
				break;
			case 16:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pile, 11);
						break;
					case ']':
						reduction(_syntData, pile, 11);
						break;
					case ',':
						reduction(_syntData, pile, 11);
						break;
				}
				break;
			case 17:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pile, 14);
						break;
					case ']':
						reduction(_syntData, pile, 14);
						break;
					case ',':
						reduction(_syntData, pile, 14);
						break;
				}
				break;
			case 18:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pile, 15);
						break;
					case ']':
						reduction(_syntData, pile, 15);
						break;
					case ',':
						reduction(_syntData, pile, 15);
						break;
				}
				break;
			case 19:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pile, 16);
						break;
					case ']':
						reduction(_syntData, pile, 16);
						break;
					case ',':
						reduction(_syntData, pile, 16);
						break;
				}
				break;
			case 20:
				switch (_syntData->startPos[0]) {
					case ']':
						deplacement(_syntData, pile, 23);
						break;
				}
				break;
			case 21:
				switch (_syntData->startPos[0]) {
					case ']':
						reduction(_syntData, pile, 8);
						break;
					case ',':
						deplacement(_syntData, pile, 24);
						break;
				}
				break;
			case 22:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pile, 6);
						break;
					case ']':
						reduction(_syntData, pile, 6);
						break;
					case ',':
						reduction(_syntData, pile, 6);
						break;
				}
				break;
			case 23:
				switch (_syntData->startPos[0]) {
					case '}':
						reduction(_syntData, pile, 7);
						break;
					case ']':
						reduction(_syntData, pile, 7);
						break;
					case ',':
						reduction(_syntData, pile, 7);
						break;
				}
				break;
			case 24:
				switch (_syntData->startPos[0]) {
					case '{':
						deplacement(_syntData, pile, 2);
						break;
					case '[':
						deplacement(_syntData, pile, 14);
						break;
					case ']':
						deplacement(_syntData, pile, 22);
						break;
					case 'S':
						deplacement(_syntData, pile, 15);
						break;
					case 'N':
						deplacement(_syntData, pile, 16);
						break;
					case 'T':
						deplacement(_syntData, pile, 17);
						break;
					case 'F':
						deplacement(_syntData, pile, 18);
						break;
					case 'U':
						deplacement(_syntData, pile, 19);
						break;
				}
				break;
			case 25:
				switch (_syntData->startPos[0]) {
					case ']':
						reduction(_syntData, pile, 9);
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
 * \fn void deplacement(TSynt * _syntData, TIntPile * pile, int numEtat)
 * \brief fonction qui place le numéro d'un état dans la pile
 *
 * \param _syntData donnees de suivi de l'analyse syntaxique
 * \param pile donnees de suivi de la pile
 * \param numEtat numero de l'état concerne
 * \return neant
*/
void deplacement(TSynt * _syntData, TIntPile * pile, int numEtat){

	printf("\nUN PASSAGE DEPLACEMENT !\nNum état : %d\n", numEtat);
	empilerInt(pile, numEtat);
	printf("PILE : ");
	printIntPile(pile);
	_syntData->seqOk += 1;
	printf("seqOk : %d\n", _syntData->seqOk);
	_syntData->symOk = realloc (_syntData->symOk, (sizeof(char) * _syntData->seqOk) + 1);
	_syntData->symOk[_syntData->seqOk - 1] = _syntData->startPos[0];
	_syntData->symOk[_syntData->seqOk] = '\0';
	printf("symOk : %s\n", _syntData->symOk);
	_syntData->startPos = subStringSynt(_syntData, 1);
}


/**
 * \fn void reduction(TSynt * _syntData, TIntPile * pile, int numEtat){
 * \brief fonction qui effectue la reduction syntaxique
 *
 * \param _syntData donnees de suivi de l'analyse syntaxique
 * \param pile donnees de suivi de la pile
 * \param numEtat numero de l'état concerne
 * \return neant
*/
void reduction(TSynt * _syntData, TIntPile * pile, int numEtat){
	printf("\nUN PASSAGE REDUCTION\n");
	int nbr_symb_pile = GRAMMAIRE_NBR_LETTRE[numEtat];

	printf("PILE : ");
	printIntPile(pile);
	printf("numEtat : %d\n", numEtat);
	printf("seqOk : %d\n", nbr_symb_pile);

	while (nbr_symb_pile != 0){

		depilerInt(pile);
		nbr_symb_pile--;	
	}

	nbr_symb_pile = _syntData->seqOk;

	_syntData->symOk[nbr_symb_pile - GRAMMAIRE_NBR_LETTRE[numEtat]] = GRAMMAIRE_LETTRE[numEtat];
	_syntData->seqOk = _syntData->seqOk - GRAMMAIRE_NBR_LETTRE[numEtat] + 1;
	_syntData->symOk[(nbr_symb_pile + 1) - GRAMMAIRE_NBR_LETTRE[numEtat]] = '\0';

	printf("symOk : %s\n", _syntData->symOk);
	int valeur = goTo(_syntData, pile);
	printf("goto : %d\n", valeur);
	empilerInt(pile, valeur);
	printf("NOUVELLE PILE : ");
	printIntPile(pile);
}

/**
 * \fn int goTo(TSynt * _syntData, TIntPile * pile)
 * \brief fonction qui effectue la méthode goto
 *
 * \param _syntData donnees de suivi de l'analyse syntaxique
 * \param pile donnees de suivi de la pile
 * \return le nouveau numero de l'etat a ajouter a la pile
*/
int goTo(TSynt * _syntData, TIntPile * pile){

	int etape = sommetInt(pile);

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
int main() {

	// ANALYSE LEXICAL //

	char * test;
	char * obj;
	TLex * lex_data;
	TIntPile * pile;

	test = strdup("{\"obj1\": [ {\"obj2\": 12, \"obj3\":\"text1 \\\"and\\\" text2\"},\n {\"obj4\":314.32} ], \"obj5\": true }");

	printf("\n-- CHAINE DE DEPART -- \n\n%s",test);
	printf("\n");

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
	pile = initIntPile();

	synt(synt_data, pile);

	/*deleteIntPile(&pile);*/
	/*deleteSyntData(&synt_data);*/
	free(obj);

	return 0;
}
