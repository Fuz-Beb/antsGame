/**
 * \file pile.c
 * \brief gestion d'une pile
 * \author NM
 * \author Pierrick BOBET
 * \author Rémy BOUTELOUP
 * \version 0.1
 * \date 03/01/2017
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "pile.h"

/** constante pour la taille par defaut d'une pile (utilise pour
 * la reservation memoire) */
#define _DEFAULT_PILE_SIZE 15



/** pile d'entier ----------------------------------------------------*/
/**
 * \fn TPile * initPile()
 * \brief fonction qui initialise une pile : reservation memoire+initialisation
 * des champs
 *
 * \return pointeur sur TIntPile cree en memoire
 */
TIntPile * initIntPile() {
    TIntPile * pile = (TIntPile*)malloc(_DEFAULT_PILE_SIZE + 1);

    if(pile == NULL)
    {
        printf("Error with the heap");
        exit(-1);
    }

    pile->data = (int*)malloc(sizeof(int) + 1);

    if(pile->data == NULL)
    {
        printf("Error with the heap");
        exit(-1);
    }

    pile->indexSommet = 0;
    pile->size = (int)sizeof(int);
    empilerInt(pile, 0);

    return pile;
}

/**
 * \fn void deleteIntPile(TIntPile ** _pile)
 * \brief efface la memoire occupe par la pile
 *
 * \param[in/out] _pile : l'adresse du pointeur sur la pile
 * \return neant
 */
void deleteIntPile(TIntPile ** _pile) {
    free(_pile[0]->data);
    free(_pile[0]);
}


/**
 * \fn void printIntPile(TIntPile * _pile)
 * \brief affichage du contenu d'une pile
 *
 * \param[in] _pile : la pile a afficher
 * \return neant
 */
void printIntPile(TIntPile * _pile) {

	if (_pile != NULL)
	{
		int nbrInt = _pile->indexSommet, i = 0;

		while (nbrInt > 0)
		{
			printf("%d", _pile->data[i]);
			nbrInt--;
			i++;
		}
	}
	else
		printf("-- Pile non initialisée ! -- \n");

	printf("\n");
}

/**
 * \fn void empilerInt(TIntPile * _pile, int _val)0
 * \brief empiler un entier sur la pile, si la zone memoire reservee
 * n'est pas suffisante, celle-ci est etendue
 *
 * \param[in/out] _pile : la pile a utiliser
 * \param[in] _val : l'entier a empiler
 * \return neant
 */
void empilerInt(TIntPile * _pile, int _val) {

	if (_pile->size == _pile->indexSommet * (sizeof(int)))
	{
		_pile->data = realloc(_pile->data, (_pile->indexSommet + 1) * (sizeof(int)));
	}

    if(_pile->data == NULL)
    {
       	printf("Error with the heap");
       	exit(-1);
    }

	_pile->data[_pile->indexSommet] = _val;
	_pile->indexSommet += 1;
	_pile->size = _pile->indexSommet * (sizeof(int));
	
}

/**
 * \fn int depilerInt(TIntPile * _pile)
 * \brief dépiler un entier
 *
 * \param[in] _pile : la pile a depiler
 * \return l'entier en sommet de pile (0 si la pile est vide)
 */
int depilerInt(TIntPile * _pile) {

	if (_pile != NULL)
	{
		if (_pile->indexSommet == 0)
		{
			printf("-- La pile est vide ! -- \n");
			return 0;
		}
		else
		{
			_pile->indexSommet -= 1;
			return _pile->data[_pile->indexSommet];
		}
	}
	else
		printf("-- Pile non initialisée ! -- \n");
}

/**
 * \fn int sommetInt(TIntPile * _pile)
 * \brief renvoie la valeur du sommet (sans depiler)
 *
 * \param[in] _pile : la pile a utiliser
 * \return l'entier en sommet de pile (0 si la pile est vide)
 */
int sommetInt(TIntPile * _pile) {

	if (_pile != NULL)
	{
		if (_pile->indexSommet == 0)
		{
			printf("-- La pile est vide ! -- \n");
			return 0;
		}
		return _pile->data[_pile->indexSommet - 1];
	}
	else
		printf("-- Pile non initialisée ! -- \n");
}


/** pile de void * ---------------------------------------------------*/

/**
 * \fn TVoidPile * initVoidPile()
 * \brief fonction qui initialise une pile de pointeur void *
 *
 * \return pointeur sur une pile TVoidPile
 */
TVoidPile * initVoidPile() {
    TVoidPile * voidPile = (TVoidPile*)malloc(_DEFAULT_PILE_SIZE + 1);

    if(voidPile == NULL)
    {
        printf("Error with the heap");
        exit(-1);
    }

    voidPile->data = (void**)malloc(sizeof(void *));

    if(voidPile->data == NULL)
    {
        printf("Error with the heap");
        exit(-1);
    }

    voidPile->indexSommet = 0;
    voidPile->size = (int)sizeof(void *);
    return voidPile;
}


/**
 * \fn void deleteVoidPile(TVoidPile ** _pile)
 * \brief libere la memoire occupee par la pile
 *
 * \param[in] _pile : adresse du pointeur sur la pile a liberer
 * \return neant
 */
void deleteVoidPile(TVoidPile ** _pile) {
  free(_pile[0]->data);
  free(_pile[0]);
}


/**
 * \fn void printVoidPile(TVoidPile * _pile)
 * \brief affichage de la pile
 *
 * \param[in] _pile : pile a afficher
 * \return neant
 */
void printVoidPile(TVoidPile * _pile) {

	if (_pile != NULL)
	{
		int nbrObjet = _pile->indexSommet, i = 0;

		while (nbrObjet > 0)
		{
			printf("%p", _pile->data[i]);
			nbrObjet--;
			i++;
		}
	}
	else
		printf("-- Pile non initialisée ! -- \n");

	printf("\n");
}

/**
 * \fn  void empilerVoid(TVoidPile * _pile, void * _val)
 * \brief empile un void *
 *
 * \param[in/out] _pile : pile a utiliser pour empiler
 * \param[in] _val : element de type void * a empiler
 * \return neant
 */
void empilerVoid(TVoidPile * _pile, void * _val) {

	if (_pile->size == _pile->indexSommet * (sizeof(void *)))
		_pile->data = realloc(_pile->data, (_pile->indexSommet + 1) * (sizeof(void *)));

		_pile->data[_pile->indexSommet] = _val;
		_pile->indexSommet += 1;
		_pile->size = _pile->indexSommet * (sizeof(void *));
}


/**
 * \fn void * depilerVoid(TVoidPile * _pile)
 * \brief dépiler un élément de type void *
 *
 * \param[in] _pile : pile a utiliser
 * \return pointeur sur void (0 si la pile est vide)
 */
void * depilerVoid(TVoidPile * _pile) {

	if (_pile != NULL)
	{
		if (_pile->indexSommet == 0)
		{
			printf("-- La pile est vide ! -- \n");
			return 0;
		}
		else
		{
			_pile->indexSommet -= 1;
			return _pile->data[_pile->indexSommet];
		}
	}
	else
		printf("-- Pile non initialisée ! -- \n");
}

/**
 * \fn void * sommetVoid(TVoidPile * _pile)
 * \brief obtenir la valeur du sommet de type void *
 *
 * \param[in] _pile : pile a utiliser pour lire le sommet
 * \return la valeur void * du sommet (0 si la pile est vide)
 */
void * sommetVoid(TVoidPile * _pile) {

	if (_pile != NULL)
	{
		if (_pile->indexSommet == 0)
		{
			printf("-- La pile est vide ! -- \n");
			return 0;
		}
		return _pile->data[_pile->indexSommet - 1];
	}
	else
		printf("-- Pile non initialisée ! -- \n");
}