/**
 * \file tp2_a.c
 * \brief analyseur lexical pour le langage JSON
 * \author NM
 * \version 0.1
 * \date 25/11/2015
 *
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

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


/* Prototypes de fonctions */
void addIntSymbolToLexData(TLex * _lexData, const int _val);
void addRealSymbolToLexData(TLex * _lexData, const float _val);
void addStringSymbolToLexData(TLex * _lexData, char * _val);
int insertStringLexData(TLex * _lex_data, char * _data, char * buffer, int i, int nbLignes);
int insertNombreLexData(TLex * _lex_data, char * _data, char * buffer, int i, int nbLignes);

/**
 * \fn int isSep(char _symb)
 * \brief fonction qui teste si un symbole fait partie des separateurs
 *
 * \param[in] _symb symbole a analyser
 * \return 1 (vrai) si _symb est un separateur, 0 (faux) sinon
 */
int isSep(const char _symb)
{
	if (_symb == ' ')
		return 1;
	else
		return 0;
}

/**
 * \fn TLex * initLexData(char * _data)
 * \brief fonction qui reserve la memoire et initialise les
 * donnees pour l'analyseur lexical
 *
 * \param[in] _data chaine a analyser
 * \return pointeur sur la structure de donnees creee
 */
TLex * initLexData(char * _data)
{
	TLex * _lex_data = (TLex*) malloc (sizeof(TLex));
	_lex_data->tableSymboles = (TSymbole*) malloc (sizeof(TSymbole));
    char buffer[32];

	memset(buffer, '\0', 32);
	int i = 0, nbLignes = 0;

	if (_lex_data == NULL)
		exit(0);

	while (strlen(_data) != i)
	{
		_lex_data->tableSymboles = realloc(_lex_data->tableSymboles, sizeof(TSymbole) * ((size_t)_lex_data->nbSymboles + 1));

		if (_lex_data == NULL)
			exit(0);

        if (_data[i] == '\n')
            nbLignes++;

		/* SI CE N'EST PAS UN ESPACE */
		if (isSep(_data[i]) == 0)
		{	/* TRAITEMENT CHAINE */
            if (_data[i] == '"')
                i = insertStringLexData(_lex_data, _data, buffer, i, nbLignes);

			/* TRAITEMENT NOMBRE */
			else if (_data[i] >= '0' && _data[i] <= '9')
            {
                i = insertNombreLexData(_lex_data, _data, buffer, i, nbLignes);
            }/* TRAITEMENT CARACTERE */
			else
			{
                _lex_data->startPos = _data + i;
                _lex_data->nbLignes = nbLignes;
                addStringSymbolToLexData(_lex_data, buffer);
                i++;
            }
		}
		else
			i++;

		memset(buffer, '\0', 32);
	}
	return _lex_data;
}

/* Mettre des commentaires Doxygen */
int insertStringLexData(TLex * _lex_data, char * _data, char * buffer, int i, int nbLignes)
{
    int z = 0;

    buffer[z] = '"';
    i++;
    z++;

    while (_data[i] != '"')
    {
        buffer[z] = _data[i];
        z++;
        i++;
    }

    buffer[z] = '"';
    i++;

    _lex_data->startPos = _data + i;
    _lex_data->nbLignes = nbLignes;
    addStringSymbolToLexData(_lex_data, buffer);

    return i;
}

/* Mettre des commentaires Doxygen */
int insertNombreLexData(TLex * _lex_data, char * _data, char * buffer, int i, int nbLignes)
{
    int z = 0;

    while ((_data[i] >= '0' && _data[i] <= '9' ) || _data[i] == '.')
    {
        buffer[z] = _data[i];
        z++;
        i++;
    }

    if (strchr(buffer, '.'))
    {
        _lex_data->startPos = _data + i;
        _lex_data->nbLignes = nbLignes;
        addRealSymbolToLexData(_lex_data, atof(buffer));
    }
    else
    {
        _lex_data->startPos = _data + i;
        _lex_data->nbLignes = nbLignes;
        addIntSymbolToLexData(_lex_data, atoi(buffer));
    }
    return i;
}






/**
 * \fn void deleteLexData(TLex ** _lexData)
 * \brief fonction qui supprime de la memoire les donnees pour
 * l'analyseur lexical
 *
 * \param[in/out] _lexData donnees de l'analyseur lexical
 * \return neant
 */
void deleteLexData(TLex ** _lexData)
{
	int i = 0, j = 0;

	while(_lexData[i+1] != NULL)
	{
		while(_lexData[i]->tableSymboles[j].val.chaine != NULL && _lexData[i]->tableSymboles[j].type == JSON_STRING)
		{
			free(_lexData[i]->tableSymboles[j].val.chaine);

			j++;
		}

    free(_lexData[i]->data);
    free(_lexData[i]->startPos);
    free(_lexData[i]->tableSymboles);
		free(_lexData[i]);

		i++;
		j = 0;
	}

	if(_lexData[i] != NULL)
	{
		while(_lexData[i]->tableSymboles[j].val.chaine != NULL && _lexData[i]->tableSymboles[j].type == JSON_STRING)
		{
			free(_lexData[i]->tableSymboles[j].val.chaine);

			j++;
		}

		free(_lexData[i]->data);
		free(_lexData[i]->startPos);
		free(_lexData[i]->tableSymboles);
		free(_lexData[i]);

		i++;
		j = 0;
	}
}

/**
 * \fn void printLexData(TLex * _lexData)
 * \brief fonction qui affiche les donnees pour
 * l'analyseur lexical
 *
 * \param[in] _lexData donn�es de l'analyseur lexical
 * \return neant
 */
void printLexData(TLex * _lexData) {
/****** A ECRIRE *******/
}


/**
 * \fn void addIntSymbolToLexData(TLex * _lexData, const int _val)
 * \brief fonction qui ajoute un symbole entier a la table des symboles
 *
 * \param[in/out] _lexData donnees de l'analyseur lexical
 * \param[in] _val valeur entiere e ajouter
 * \return neant
 */
void addIntSymbolToLexData(TLex * _lexData, const int _val)
{
	if (_lexData != NULL)
	{
	    _lexData->nbSymboles += 1;
	    int nbrSymbole = _lexData->nbSymboles;
		_lexData->tableSymboles[nbrSymbole - 1].type = JSON_INT_NUMBER;
		_lexData->tableSymboles[nbrSymbole - 1].val.entier = _val;
	}
}

/**
 * \fn void addRealSymbolToLexData(TLex * _lexData, const float _val)
 * \brief fonction qui ajoute un symbole reel a la table des symboles
 *
 * \param[in/out] _lexData donnees de l'analyseur lexical
 * \param[in] _val valeur reelle a ajouter
 */
void addRealSymbolToLexData(TLex * _lexData, const float _val)
{
	if (_lexData != NULL)
	{
	    _lexData->nbSymboles += 1;
	    int nbrSymbole = _lexData->nbSymboles;
		_lexData->tableSymboles[nbrSymbole - 1].type = JSON_REAL_NUMBER;
		_lexData->tableSymboles[nbrSymbole - 1].val.reel = _val;
	}
}

 /**
 * \fn void addStringSymbolToLexData(TLex * _lexData, char * _val)
 * \brief fonction qui ajoute une chaine de caracteres a la table des symboles
 *
 * \param[in/out] _lexData donnees de l'analyseur lexical
 * \param[in] _val chaine a ajouter
 */
void addStringSymbolToLexData(TLex * _lexData, char * _val)
{
    if (_lexData != NULL)
    {
        _lexData->nbSymboles += 1;
        int nbrSymbole = _lexData->nbSymboles;
        _lexData->tableSymboles[nbrSymbole - 1].type = JSON_STRING;
        _lexData->tableSymboles[nbrSymbole - 1].val.chaine = strdup(_val); // Bebo - Possibilite de fuite car si on met juste = val et qu'on le libere...
    }
}

/**
 * \fn int lex(const char * _entree, TLex * _lexData)
 * \brief fonction qui effectue l'analyse lexicale (contient le code l'automate fini)
 *
 * \param[in/out] _lexData donn�es de suivi de l'analyse lexicale
 * \return code d'identification de l'entite lexicale trouvee
*/
int lex(TLex * _lexData) {
/****** A ECRIRE *******/
}


/**
 * \fn int main()
 * \brief fonction principale
 */
int main() {
	char * test;
	/*int i;*/
	TLex * lex_data;

	test = strdup("{\"obj1\": [ {\"obj2\": 12, \"obj3\":\"text1 \\\"and\\\" text2\"},\n {\"obj4\":314.32} ], \"obj5\": true }");
	printf("%s",test);
	printf("\n");

	lex_data = initLexData(test);
	/*i = lex(lex_data);
	while (i!=JSON_LEX_ERROR) {
		printf("lex()=%d\n",i);
		i = lex(lex_data);
	}
  	printLexData(lex_data);*/
	deleteLexData(&lex_data);
	free(test);
	return 0;
}
