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
#include "tp2_a.h"
#include "tp3_a.h"
#include "pile.h"

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

	char * _syntData->symOk = (char*) malloc (sizeof(char));

	if (_syntData->symOk == NULL)
	{
		printf("ERREUR : ALLOCATION DYNAMIQUE IMPOSSIBLE DE _syntData->symOk");
		exit(EXIT_FAILURE);
	}

	_syntData->data = strndup(_data, strlen(_data));
    _syntData->startPos = strndup(_data, strlen(_data));
	_syntData->nbSymboles = 0;
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
 * \fn void synt(TSynt * _syntData)
 * \brief fonction qui effectue l'analyse syntaxique
 *
 * \param _syntData donnees de suivi de l'analyse syntaxique
 * \return neant
*/
void synt(TSynt * _syntData, TIntPile * pile)
{
	int nbSymboles = _syntData->nbSymboles, etape = 0;

	while (nbSymboles > 0)
	{
		while (isSep(_syntData->startPos[0]))
        	_syntData->startPos = subString(_syntData, 1);

		etape = sommetInt(pile);

		switch (etape) {

			case 0:
				switch (_syntData->startPos[0]) {
					case "{":
						deplacement(_syntData, pile, 2);
						break;
				}
			case 1:
				switch (_syntData->startPos[0]) {
					case "#":
						printf("-- ACCEPTER -- ");
						break;
				}
			case 2:
				switch (_syntData->startPos[0]) {
					case "}":
						deplacement(_syntData, pile, 5);
						break;
					case "S":
						deplacement(_syntData, pile, 6);
						break;
				}
			case 3:
				switch (_syntData->startPos[0]) {
					case "}":
						deplacement(_syntData, pile, 7);
						break;
				}
			case 4:
				switch (_syntData->startPos[0]) {
					case "}":
						reduction(_syntData, pile, 3);
						break;
				}




				break;
			default:
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

	empilerInt(numEtat);
	_syntData->seqOk += 1;
	_syntData->symOk = realloc (_syntData->symOk, (sizeof(char) * _syntData->seqOk) + 1)
	_syntData->symOk[_syntData->seqOk - 1] = _syntData[]
}


/**
 * \fn void reduction(TSynt * _syntData, TIntPile * pile, int numEtat){
 * \brief fonction qui effectue l'analyse syntaxique
 *
 * \param _syntData donnees de suivi de l'analyse syntaxique
 * \return neant
*/
void reduction(TSynt * _syntData, TIntPile * pile, int numEtat){
	
	- Regarde la règle qui correspond à l action
	- Récupère le symbole auxilière de la regle correspondante
	- appeler une fonction goTo qui renvoi le numero a ajouter a la pile
}

/**
 * \fn void synt(TSynt * _syntData)
 * \brief fonction qui effectue l'analyse syntaxique
 *
 * \param _syntData donnees de suivi de l'analyse syntaxique
 * \return neant
*/
void goTo(TIntPile * pile, int numEtat){

	empilerInt(numEtat);
	_syntData->startPos = subString(_syntData, 1);
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

	deleteIntPile(&pile);
	deleteSyntData(&synt_data);
	free(obj);

	return 0;
}
