
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

#ifndef TP2_A_H
#define TP2_A_H

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
 * \union TSymbole
 * \brief union permettant de  manipuler un entier/reel/chaine pour la table
 * des symboles
 */
typedef struct {
	int type; /**< l'un des 3 types suivants : JSON_STRING/JSON_INT_NUMBER/JSON_REAL_NUMBER */
	union {
        int entier;
        float reel;
        char * chaine;
    } val; /**< valeur associer a un element de la table des symboles */
} TSymbole;

/**
 * \struct TLex
 * \brief structure contenant tous les parametres/donnees pour
 * l'analyse lexicale
 */
typedef struct{
	char * data; /**< chaine a parcourir */
	char * startPos; /**< position de depart pour la prochaine analyse */
	int nbLignes; /**< nb de lignes analysees */
	TSymbole * tableSymboles; /**< tableau des symboles : chaines/entier/reel */
	int nbSymboles; /**< taille du tableau tableSymboles */
} TLex;


/**
 * \fn char * str_cut(char * startPos, int nbCaracteres)
 * \brief fonction qui rogne une chaine de caracteres
 *
 * \param lex_data donnees de suivi de l'analyse lexicale
 * \param[in] nbCaracteres le nombre de caracteres a supprimer
 * \return la nouvelle chaine de caracteres
 */
char * str_cut(char * startPos, int nbCaracteres);

/**
 * \fn int isSep(const char _symb)
 * \brief fonction qui teste si un symbole fait partie des separateurs
 *
 * \param[in] _symb symbole a analyser
 * \return 1 (vrai) si _symb est un separateur, 0 (faux) sinon
 */
int isSep(const char _symb);

/**
 * \fn TLex * initLexData(char * _data)
 * \brief fonction qui reserve la memoire et initialise les
 * donnees pour l'analyseur lexical
 *
 * \param[in] _data chaine a analyser
 * \return pointeur sur la structure de donnees creee
 */
TLex * initLexData(char * _data);

/**
 * \fn void deleteLexData(TLex ** _lexData)
 * \brief fonction qui supprime de la memoire les donnees pour
 * l'analyseur lexical
 *
 * \param _lexData donnees de l'analyseur lexical
 * \return neant
 */
void deleteLexData(TLex ** _lexData);

/**
 * \fn void printLexData(TLex * _lexData)
 * \brief fonction qui affiche les donnees pour
 * l'analyseur lexical
 *
 * \param _lexData donnees de l'analyseur lexical
 * \return neant
 */
void printLexData(TLex * _lexData);


/**
 * \fn void addIntSymbolToLexData(TLex * _lexData, const int _val)
 * \brief fonction qui ajoute un symbole entier a la table des symboles
 *
 * \param _lexData donnees de l'analyseur lexical
 * \param[in] _val valeur entiere a ajouter
 * \return neant
 */
void addIntSymbolToLexData(TLex * _lexData, const int _val);


/**
 * \fn void addRealSymbolToLexData(TLex * _lexData, const float _val)
 * \brief fonction qui ajoute un symbole reel a la table des symboles
 *
 * \param _lexData donnees de l'analyseur lexical
 * \param[in] _val valeur reelle a ajouter
 */
void addRealSymbolToLexData(TLex * _lexData, const float _val);


 /**
 * \fn void addStringSymbolToLexData(TLex * _lexData, char * _val)
 * \brief fonction qui ajoute une chaine de caracteres a la table des symboles
 *
 * \param _lexData donnees de l'analyseur lexical
 * \param[in] _val chaine a ajouter
 */
void addStringSymbolToLexData(TLex * _lexData, char * _val);


/**
 * \fn int lex(TLex * _lexData)
 * \brief fonction qui effectue l'analyse lexicale (contient le code l'automate fini)
 *
 * \param _lexData donnees de suivi de l'analyse lexicale
 * \return code d'identification de l'entite lexicale trouvee
*/
int lex(TLex * _lexData);


/**
 * \fn char * formatLex (TLex * _lexData)
 * \brief fonction qui alloue dans un tableau de caractère le résultat de l'analyse lexicale
 *
 * \param _lexData donnees de suivi de l'analyse lexicale
 * \return le nouveau tableau de caractères
*/
char * formatLex (TLex * _lexData);

#endif