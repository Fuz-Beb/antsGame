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
#include "tp3_a.h"
#include "tp2_a.h"

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

	_syntData->data = strndup(_data, strlen(_data));
    _syntData->startPos = strndup(_data, strlen(_data));
	_syntData->nbSymboles = 0;

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
		etape = sommetInt(pile);
	}
}



/**
 * \fn int main()
 * \brief fonction principale
 */
int main(int argc, char *argv[], char * file)
{
	// ANALYSE LEXICAL //

	char * test;
	char * obj;
	char fichierChaine[1024];

	FILE* fichier = NULL;

	fichier = fopen(file, "r");

	if(fichier == NULL)
	{
			printf("Erreur avec l'ouverture du fichier !");
	}

	fgets(fichierChaine, 1024, fichier);

	TLex * lex_data;
	TIntPile * pile;

	test = strdup("test");

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
