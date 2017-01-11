/**
 * \file tp2_a.c
 * \brief analyseur lexical pour le langage JSON
 * \author NM
 * \author Rémy BOUTELOUP
 * \author Pierrick BOBET
 * \version 0.1
 * \date 02/01/2017
 *
 */

#ifndef TP3_A_H
#define TP3_A_H

#define JSON_LEX_ERROR -1 /**< code d'erreur lexicale */
#define JSON_TRUE 1 /**< entite lexicale true */
#define JSON_FALSE 2 /**< entite lexicale false */
#define JSON_NULL 3 /**< entite lexicale null */
#define JSON_LCB 4 /**< entite lexicale { */
#define JSON_RCB 5 /**< entite lexicale } */
#define JSON_LB 6 /**< entite lexicale [ */
#define JSON_RB 7 /**< entite lexicale ] */
#define JSON_COMMA 8 /**< entite lexicale , */
#define JSON_COLON 9 /**< entite lexicale : */
#define JSON_STRING 10 /**<entite lexicale chaine de caracteres */
#define JSON_INT_NUMBER 11 /**< entite lexicale nombre entier */
#define JSON_REAL_NUMBER 12 /**< entite lexicale nombre reel */

/**
 * \struct TSynt
 * \brief structure contenant tous les parametres/donnees pour
 * l'analyse syntaxique
 */
typedef struct{
	char * data; /**< chaine a parcourir */
	char * startPos; /**< position de depart pour la prochaine analyse */
	char * symOk; /**< contient l'alphabet et les symboles auxilieres reconnus */
	int seqOk; /**< nombre de caractère reconnu par l'analyseur */
	int nbSymboles; /**< taille du tableau tableSymboles */
} TSynt;

/**
 * \fn TSynt * initSyntData(char * _data)
 * \brief fonction qui reserve la memoire et initialise les
 * donnees pour l'analyseur syntaxique
 *
 * \param[in] _data chaine a analyser
 * \return pointeur sur la structure de donnees creee
 */
TSynt * initSyntData(char * _data);

/**
 * \fn void deleteSyntData(TSynt ** _syntData)
 * \brief fonction qui supprime de la memoire les donnees pour
 * l'analyseur syntaxique
 *
 * \param _syntData donnees de l'analyseur syntaxique
 * \return neant
 */
void deleteSyntData(TSynt ** _syntData);

/**
 * \fn void synt(TSynt * _syntData, TIntPile * pileInt, TVoidPile * pileVoid)
 * \brief fonction qui effectue l'analyse syntaxique
 *
 * \param _syntData donnees de suivi de l'analyse syntaxique
 * \param pileInt donnees de suivi de la pile INT
 * \param pileVoid donnees de suivi de la pile VOID
 * \return neant
*/
void synt(TSynt * _syntData, TIntPile * pileInt, TVoidPile * pileVoid);

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
void deplacement(TSynt * _syntData, TIntPile * pileInt, TVoidPile * pileVoid, int numEtat);


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
void reduction(TSynt * _syntData, TIntPile * pileInt, TVoidPile * pileVoid, int numEtat);


/**
 * \fn void gestion_arbre(TSynt * _syntData, TVoidPile * pileVoid)
 * \brief fonction qui construit l'arbre
 *
 * \param _syntData donnees de suivi de l'analyse syntaxique
 * \param pileVoid donnees de suivi de la pile VOID
 * \return neant
*/
void gestion_arbre(TSynt * _syntData, TVoidPile * pileVoid);


/**
 * \fn int goTo(TSynt * _syntData, TIntPile * pileInt)
 * \brief fonction qui effectue la méthode goto
 *
 * \param _syntData donnees de suivi de l'analyse syntaxique
 * \param pileInt donnees de suivi de la pile INT
 * \param pileVoid donnees de suivi de la pile VOID
 * \return le nouveau numero de l'etat a ajouter a la pile
*/
int goTo(TSynt * _syntData, TIntPile * pileInt);
#endif
