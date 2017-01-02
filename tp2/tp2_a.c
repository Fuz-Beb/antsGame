
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
char * subString(TLex * lex_data, int nbCaracteres);

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
	TLex * _lexData = (TLex*) malloc (sizeof(TLex));

	if (_lexData == NULL)
	{
		printf("ERREUR : ALLOCATION DYNAMIQUE IMPOSSIBLE DE _lexData");
		exit(EXIT_FAILURE);
	}

	_lexData->tableSymboles = (TSymbole*) malloc (sizeof(TSymbole));

	if (_lexData->tableSymboles == NULL)
	{
		printf("ERREUR : ALLOCATION DYNAMIQUE IMPOSSIBLE DE _lexData->tableSymboles");
		exit(EXIT_FAILURE);
	}

	_lexData->data = strndup(_data, strlen(_data));
    _lexData->startPos = strndup(_data, strlen(_data));
	_lexData->nbLignes = 0;
	_lexData->nbSymboles = 0;

	return _lexData;
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
	int nbSymboles = _lexData[0]->nbSymboles, i = 0;

	while (nbSymboles != 0)
    {
        if(_lexData[0]->tableSymboles[i].type == JSON_STRING)
        {
        	free(_lexData[0]->tableSymboles[i].val.chaine);
        }
        nbSymboles--;
        i++;
    }

    free(_lexData[0]->data);
    free(_lexData[0]->tableSymboles);
    free(_lexData[0]->startPos);
    free(_lexData[0]);
}

/**
 * \fn void printLexData(TLex * _lexData)
 * \brief fonction qui affiche les donnees pour
 * l'analyseur lexical
 *
 * \param[in] _lexData donn�es de l'analyseur lexical
 * \return neant
 */
void printLexData(TLex * _lexData)
{
	if (_lexData != NULL)
    {
        int nbSymboles = _lexData->nbSymboles, i = 0;
        printf("\nTable des symboles : \n--------------------\n");

        while (nbSymboles != 0)
        {
            if (_lexData->tableSymboles[i].type == JSON_STRING)
                printf("STRING : %s\n", _lexData->tableSymboles[i].val.chaine);
            else if (_lexData->tableSymboles[i].type == JSON_INT_NUMBER)
                printf("INT : %d\n", _lexData->tableSymboles[i].val.entier);
            else if (_lexData->tableSymboles[i].type == JSON_REAL_NUMBER)
                printf("REEL : %f\n", _lexData->tableSymboles[i].val.reel);
            else
            {
                printf("ERREUR DANS LA LECTURE DE LA TABLE DES SYMBOLES");
                exit(EXIT_FAILURE);
            }

            nbSymboles--;
            i++;
        }
    }
    else
    {
        printf("ERREUR DANS LA LECTURE DES DONNEES (Tlex = NULL)");
        exit(EXIT_FAILURE);
    }
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
		_lexData->tableSymboles = realloc(_lexData->tableSymboles, sizeof(TSymbole) * ((size_t)_lexData->nbSymboles + 1));

		if (_lexData == NULL)
			exit(EXIT_FAILURE);

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
		_lexData->tableSymboles = realloc(_lexData->tableSymboles, sizeof(TSymbole) * ((size_t)_lexData->nbSymboles + 1));

		if (_lexData == NULL)
			exit(EXIT_FAILURE);

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
    	_lexData->tableSymboles = realloc(_lexData->tableSymboles, sizeof(TSymbole) * ((size_t)_lexData->nbSymboles + 1));

		if (_lexData == NULL)
			exit(EXIT_FAILURE);

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
int lex(TLex * _lexData)
{
	int i = 1, size = 0, temp = 0;
	char buffer[2048];
	memset(buffer, '\0', 2048);

	while (_lexData->startPos[0] == '\n')
	{
		_lexData->nbLignes += 1;
		_lexData->startPos = subString(_lexData, 1);
	}

	while (isSep(_lexData->startPos[0]))
        _lexData->startPos = subString(_lexData, 1);

    size = strlen(_lexData->startPos);

	switch (_lexData->startPos[0]) {

		case 't' :
			if (_lexData->startPos[1] == 'r' && _lexData->startPos[2] == 'u' && _lexData->startPos[3] == 'e')
			{
				strncpy(buffer, _lexData->startPos, 4);
				addStringSymbolToLexData(_lexData, buffer);
				_lexData->startPos = subString(_lexData, 4);
				return JSON_TRUE;
			}
		case 'f' :
			if (_lexData->startPos[1] == 'a' && _lexData->startPos[2] == 'l' && _lexData->startPos[3] == 's' && _lexData->startPos[4] == 'e')
			{
				strncpy(buffer, _lexData->startPos, 5);
				addStringSymbolToLexData(_lexData, buffer);
				_lexData->startPos = subString(_lexData, 5);
				return JSON_FALSE;
			}
		case 'n' :
			if (_lexData->startPos[1] == 'u' && _lexData->startPos[2] == 'l' && _lexData->startPos[3] == 'l')
			{
				strncpy(buffer, _lexData->startPos, 4);
				addStringSymbolToLexData(_lexData, buffer);
				_lexData->startPos = subString(_lexData, 3);
				return JSON_NULL;
			}
		case '{' :
			_lexData->startPos = subString(_lexData, 1);
			return JSON_LCB;
		case '}' :
			_lexData->startPos = subString(_lexData, 1);
			return JSON_RCB;
		case '[' :
			_lexData->startPos = subString(_lexData, 1);
			return JSON_LB;
		case ']' :
			_lexData->startPos = subString(_lexData, 1);
			return JSON_RB;
		case ':' :
			_lexData->startPos = subString(_lexData, 1);
			return JSON_COLON;
		case ',' :
			_lexData->startPos = subString(_lexData, 1);
			return JSON_COMMA;
		case '"' :
			while (i <= size)
			{
				if (_lexData->startPos[i] == '"')
				{
					strncpy(buffer, _lexData->startPos, i + 1);
					_lexData->startPos = subString(_lexData, i + 1);
					addStringSymbolToLexData(_lexData, buffer);
					return JSON_STRING;
				}


				if (_lexData->startPos[i] == '\\')
				{
					i++;

					switch (_lexData->startPos[i]) {

						case '"' :
							i++;
							break;
						case '\\' :
							i++;
							break;
						case '/' :
							i++;
							break;
						case 'b' :
							i++;
							break;
						case 'f' :
							i++;
							break;
						case 'n' :
							i++;
							break;
						case 'r' :
							i++;
							break;
						case 't' :
							i++;
							break;
						case 'u' :
							i++;
							temp = i;
							while ((int)_lexData->startPos[i] >= '0' && (int)_lexData->startPos[i] <= '9' && _lexData->startPos[i] >= 'A' && (int)_lexData->startPos[i] <= 'F')
								i++;

							if (temp - i != 4)
								return JSON_LEX_ERROR;
                            break;

						default:
							return JSON_LEX_ERROR;
					}
				}
				else
					i++;
			}
			return JSON_LEX_ERROR;


		default:
			i = 0;

			if (_lexData->startPos[i] == '-')
				i++;

			if ((int)_lexData->startPos[i] >= '0' && (int)_lexData->startPos[i] <= '9')
			{
				if ((int)_lexData->startPos[i] == '0' && _lexData->startPos[i+1] != '.')
				{
					addIntSymbolToLexData(_lexData, 0);
					_lexData->startPos = subString(_lexData, 1);
					return JSON_INT_NUMBER;
				}
				else if ((int)_lexData->startPos[i] >= '1' && (int)_lexData->startPos[i] <= '9')
				{
					while ((int)_lexData->startPos[i] >= '0' && (int)_lexData->startPos[i] <= '9')
        					i++;

        			if ((int)_lexData->startPos[i] == '.')
        				i++;
        			else
        			{
        				strncpy(buffer, _lexData->startPos, i);
        				addIntSymbolToLexData(_lexData, atoi(buffer));
        				_lexData->startPos = subString(_lexData, i);
						return JSON_INT_NUMBER;
        			}
				}
				else if ((int)_lexData->startPos[i] == '0' && _lexData->startPos[i] == '.')
					i++;

				if ((int)_lexData->startPos[i] >= '0' && (int)_lexData->startPos[i] <= '9')
				{
					while ((int)_lexData->startPos[i] >= '0' && (int)_lexData->startPos[i] <= '9')
        				i++;

        			if (_lexData->startPos[i] == 'e' || _lexData->startPos[i] == 'E')
    				{
    					i++;

    					if (_lexData->startPos[i] == '+' || _lexData->startPos[i] == '-' || ((int)_lexData->startPos[i] >= '0' && (int)_lexData->startPos[i] <= '9' ))
    					{
    						i++;

    						while ((int)_lexData->startPos[i] >= '0' && (int)_lexData->startPos[i] <= '9')
        						i++;

        					strncpy(buffer, _lexData->startPos, i);
        					addRealSymbolToLexData(_lexData, atof(buffer));
        					_lexData->startPos = subString(_lexData, i);
        					return JSON_REAL_NUMBER;
    					}
    					else
    						return JSON_LEX_ERROR;
    				}
    				else
    				{
    					strncpy(buffer, _lexData->startPos, i);
    					addRealSymbolToLexData(_lexData, atof(buffer));
    					_lexData->startPos = subString(_lexData, i);
						return JSON_REAL_NUMBER;
    				}
				}
				else
					return JSON_LEX_ERROR;
			}
			else
				return JSON_LEX_ERROR;
	}
}



/**
 * \fn TLex * subString(Tlex * lex_data)
 * \brief fonction qui rogne une chaine de caractères
 *
 * \param[in/out] lex_data données de suivi de l'analyse lexicale
  * \param[in/out] nbCaracteres le nombre de caractères à supprimer
 * \return la nouvelle chaine de caractères
*/
char * subString(TLex * lex_data, int nbCaracteres)
{
	char buffer[2048];
	memset(buffer, '\0', 2048);
	strncpy(buffer, lex_data->startPos + nbCaracteres, strlen(lex_data->startPos) - nbCaracteres);
	free(lex_data->startPos);
	lex_data->startPos = strndup(buffer, strlen(buffer) + 1);
	return lex_data->startPos;
}


/**
 * \fn int main()
 * \brief fonction principale
 */
int main() {
	char * test;
	int i;
	TLex * lex_data;

	test = strdup("{\"obj1\": [ {\"obj2\": 12, \"obj3\":\"text1 \\\"and\\\" text2\"},\n {\"obj4\":314.32} ], \"obj5\": true }");

	printf("%s",test);
	printf("\n");

	lex_data = initLexData(test);
	i = lex(lex_data);
	while (i!=JSON_LEX_ERROR) {
		printf("lex()=%d\n",i);
		i = lex(lex_data);
	}
  	printLexData(lex_data);
	deleteLexData(&lex_data);
	free(test);
	return 0;
}
