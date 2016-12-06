/**
 * \file tp1_b.c
 * \brief 2ieme etape du TP IL
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

/**
 * \enum TParamType
 * \brief Constantes pour le type des parametres de la ligne de commande
 */
typedef enum {
    PTentier, /**< un nombre entier */
    PTreel, /**< un nombre reel */
    PTchaine /**< une chaine de caracteres */
  } TParamType;

/** constante chaine de caracteres pour l'affichage des types */
char * ParamTypeChaine[] = {"entier","reel","chaine"};

/**
 * \union TParamValue
 * \brief union permettant de  manipuler un entier/reel/chaine
 */
typedef union {
    int entier;
    float reel;
    const char * chaine;
  } TParamValue;

/**
 * \struct TParamDef
 * \brief represente un parametre de la ligne de commande (nom,type,valeur...)
 */
typedef struct {
    char * nom; /**< nom du parametre */
    TParamType type; /**< type (entier,reel,chaine) */
    char lettre; /**< lettre a utiliser sur la ligne de commande */
    TParamValue valeur; /**< valeur a affecter au parametre */
  } TParamDef;

/**
 * \fn char * ValeurParamToString(TParamDef * _tabParam, const int _index)
 * \brief fonction qui transforme la valeur d'un parametre en chaine de caractere
 *
 * \param[in] _tabParam tableau des parametres de la ligne de commande
 * \param[in] _index indice du parametre a considerer dans le tableau
 * \return une nouvelle chaine (qu'il faudra libérer par la suite)
*/
char * ValeurParamToString(TParamDef * _tabParam, const int _index) {
    char * strResult;
    char buffer[128];
    
    memset(buffer, '\0', 128); /** Initialisation du buffer */
    
    /** Traitement selon le type à l'index _index */
    if(_tabParam[_index].type == PTentier)
        sprintf(buffer, "%d", _tabParam[_index].valeur.entier);
        
    if(_tabParam[_index].type == PTreel)
        sprintf(buffer, "%.2f", _tabParam[_index].valeur.reel);
        
    if(_tabParam[_index].type == PTchaine)
        strncpy(buffer, _tabParam[_index].valeur.chaine, strlen(_tabParam[_index].valeur.chaine));
        
    strResult = strdup(buffer);
    
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

		/** Affichage des valeurs du paramètre serveur */
    printf("-%c serveur (%s) [%s] \n", _tabParam[0].lettre, ParamTypeChaine[2], _tabParam[0].valeur.chaine);

		/** Affichage des valeurs du paramètre appli */
    printf("-%c appli (%s) [%s] \n", _tabParam[1].lettre, ParamTypeChaine[2], _tabParam[1].valeur.chaine);

		/** Affichage des valeurs du paramètre tours */
    printf("-%c tours (%s) [%d] \n", _tabParam[2].lettre, ParamTypeChaine[0], _tabParam[2].valeur.entier);    
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

	int i = 1;

	/** Recherche de la valeur -s dans les paramètres fournis */
	while (i < _argc && strcmp(_argv[i], "-s") != 0)
		i += 2;
	
	/** Si la valeur n'a pas été trouvé, une erreur est renvoyée */
	if (i >= _argc)
		return -1;

	/** Affection des valeurs pour le paramètre serveur */
	_tabParam[0].nom = "serveur";
	_tabParam[0].type = PTchaine;
	_tabParam[0].lettre = 's';
	_tabParam[0].valeur.chaine = _argv[i + 1];
	i = 1;

	/** Recherche de la valeur -a dans les paramètres fournis */
	while (i < _argc && strcmp(_argv[i], "-a") != 0)
		i += 2;

	/** Si la valeur n'a pas été trouvé, une erreur est renvoyée */
	if (i >= _argc)
		return -1;

	/** Affection des valeurs pour le paramètre appli */
	_tabParam[1].nom = "appli";
	_tabParam[1].type = PTchaine;
	_tabParam[1].lettre = 'a';
	_tabParam[1].valeur.chaine = _argv[i + 1];
	i = 1;

	/** Recherche de la valeur -t dans les paramètres fournis */
	while (i < _argc && strcmp(_argv[i], "-t") != 0)
		i += 2;

	/** Si la valeur n'a pas été trouvé, une erreur est renvoyée */
	if (i >= _argc)
		return -1;

	/** Affection des valeurs pour le paramètre tours */
	_tabParam[2].nom = "tours";
	_tabParam[2].type = PTentier;
	_tabParam[2].lettre = 't';
	_tabParam[2].valeur.entier = atoi(_argv[i + 1]);

	return _argc;
}

/**
 * \fn int main (const int _argc, const char * _argv[])
 * \brief fonction principale
 *
 * \param[in] _argc : nombre d'arguments passes sur la ligne de commande
 * \param[in] _argv : tableau qui contient les chaines de caracteres passes en arguments du programme
 * \return 0 si terminaison normale
*/
int main (const int _argc, const char * _argv[]) {
  /* declaration des paramtres avec leur type+valeurs par defaut */
  TParamDef tab_param[] = {
    {"serveur",PTchaine,'s',.valeur.chaine="??"},
    {"appli",PTchaine,'a',.valeur.chaine=""},
    {"tours",PTentier,'t',.valeur.entier=200}};
  int nb_param = 3;
  int result_arg;

  /* affichage des formats de parametre */
  printf("Valeurs par defaut :\n");
  PrintParam(tab_param,nb_param);
  /* analyse de la ligne de commande */
  result_arg = ReadParamFromCommandLine(tab_param,nb_param,_argc,_argv);

	if (result_arg < 0)
	{
		printf("Erreur de syntaxe dans la saisie des paramètres du programme \nLe programme s'est terminée\n");
		exit(1);
	}

  /* affichage des nouveaux parametres */
  printf("Valeurs des parametres :\n");
  PrintParam(tab_param,nb_param);


  return 0;
}
