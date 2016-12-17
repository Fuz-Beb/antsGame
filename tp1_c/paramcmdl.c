/**
 * \file paramcmdl.c
 * \brief Contient le code des fonctions
 * \author NM
 * \author Pierrick BOBET
 * \author Rémy BOUTELOUP
 * \version 0.1
 * \date 06/12/2016
 *
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "paramcmdl.h"

/** constante chaine de caracteres pour l'affichage des types */
char * ParamTypeChaine[] = {"entier","reel","chaine"};


/**
 * \fn char * ValeurParamToString(TParamDef * _tabParam, const int _index)
 * \brief fonction qui transforme la valeur d'un parametre en chaine de caractere
 *
 * \param[in] _tabParam tableau des parametres de la ligne de commande
 * \param[in] _index indice du parametre a considerer dans le tableau
 * \return une nouvelle chaine (qu'il faudra libérer par la suite)
*/
char * ValeurParamToString(TParamDef * _tabParam, const int _index) {

	char * strResult = NULL;
    
	/* Traitement selon le type à l'index _index */
    if(_tabParam[_index].type == PTentier)
    {
    	strResult = (char*) malloc ((sizeof(char) * sprintf(NULL, "%d", _tabParam[_index].valeur.entier)) + 1);

    	if (strResult == NULL)
    	{
    		printf("Erreur d'allocation dynamique de la mémoire");
    		exit(EXIT_FAILURE);
    	}

        sprintf(strResult, "%d", _tabParam[_index].valeur.entier);
    }
    else if(_tabParam[_index].type == PTreel)
    {
    	strResult = (char*) malloc ((sizeof(char) * sprintf(NULL, "%.2f", _tabParam[_index].valeur.reel)) + 1);

    	if (strResult == NULL)
    	{
    		printf("Erreur d'allocation dynamique de la mémoire");
    		exit(EXIT_FAILURE);
    	}

        sprintf(strResult, "%.2f", _tabParam[_index].valeur.reel);
    }
    else
    	return strdup(_tabParam[_index].valeur.chaine);
    
    return strResult;
}

/**
 * \fn PrintParam(TParamDef * _tabParam, const int _nbParam)
 * \brief fonction qui affiche a l'ecran les parametre, leur type et leur valeur
 *
 * \param[in] _tabParam tableau des parametres de la ligne de commande
 * \param[in] _nbParam taille du tableau
 * \return neant
*/
void PrintParam(TParamDef * _tabParam, const int _nbParam) {

	int indiceTab = 0;

	while (indiceTab != _nbParam)
	{
		if(_tabParam[indiceTab].type == PTentier)
			printf("-%c %s (%s) [%d] \n", _tabParam[indiceTab].lettre, _tabParam[indiceTab].nom, ParamTypeChaine[0], _tabParam[indiceTab].valeur.entier);
		else if (_tabParam[indiceTab].type == PTreel)
			printf("-%c %s (%s) [%f] \n", _tabParam[indiceTab].lettre, _tabParam[indiceTab].nom, ParamTypeChaine[1], _tabParam[indiceTab].valeur.reel);
		else if (_tabParam[indiceTab].type == PTchaine)
			printf("-%c %s (%s) [%s] \n", _tabParam[indiceTab].lettre, _tabParam[indiceTab].nom, ParamTypeChaine[2], _tabParam[indiceTab].valeur.chaine);
		indiceTab++;
	}
}

/**
 * \fn int ReadParamFromCommandLine(TParamDef * _tabParam, const int _nbParam, const int _argc, const char * _argv[])
 * \brief fonction qui analyse la ligne de commande pour en extraire des valeurs pour les parametres
 *
 * \param[out] _tabParam tableau des parametres de la ligne de commande
 * \param[in] _nbParam taille du tableau
 * \param[in] _argc nombre d'arguments passes sur la ligne de commande
 * \param[in] _argv tableau qui contient les chaines de caracteres passees en arguments du programme
 * \return >=0 : nombre de parametres mis a jour, <0 : erreur
*/
int ReadParamFromCommandLine(TParamDef * _tabParam, const int _nbParam, const int _argc, const char * _argv[]) {

	int indiceArg = 1, indiceTab = 0, countNbParam = 0, returnValue = 0;
	char compaireLettre = '\0';

	while (indiceArg != _argc)
	{
		compaireLettre = _argv[indiceArg][1];

		while (indiceTab < _nbParam && compaireLettre != _tabParam[indiceTab].lettre)
			indiceTab++;

		if (indiceTab < _nbParam)
		{
			countNbParam++;
			if(_tabParam[indiceTab].type == PTentier)
				_tabParam[indiceTab].valeur.entier = atoi(_argv[indiceArg + 1]);
			else if (_tabParam[indiceTab].type == PTreel)
				_tabParam[indiceTab].valeur.reel = atof(_argv[indiceArg + 1]);
			else
				_tabParam[indiceTab].valeur.chaine = _argv[indiceArg + 1];
		}
		else
			printf("Un élement n'a pas été reconnu ! \n");

		indiceArg += 2;
		indiceTab = 0;
	}


	returnValue = countNbParam;

	/*while (_nbParam != countNbParam)
	{
		if(_tabParam[countNbParam].type == PTchaine)
			free(_tabParam[countNbParam].valeur.chaine);

		countNbParam++;
	}*/

	return returnValue;
}
