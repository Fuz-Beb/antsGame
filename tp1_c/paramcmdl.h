/**
 * \file paramcmdl.h
 * \brief Contient les prototypes des fonctions
 * \author NM
 * \author Pierrick BOBET
 * \author Rémy BOUTELOUP
 * \version 0.1
 * \date 06/12/2016
 *
 */



#ifndef PARAMCMDL_H
#define PARAMCMDL_H

/**
 * \enum TParamType
 * \brief Constantes pour le type des parametres de la ligne de commande
 */
typedef enum {
    PTentier, /**< un nombre entier */
    PTreel, /**< un nombre reel */
    PTchaine /**< une chaine de caracteres */
  } TParamType;

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
char * ValeurParamToString(TParamDef * _tabParam, const int _index);

/**
 * \fn PrintParam(TParamDef * _tabParam, const int _nbParam)
 * \brief fonction qui affiche a l'ecran les parametre, leur type et leur valeur
 *
 * \param[in] _tabParam tableau des parametres de la ligne de commande
 * \param[in] _nbParam taille du tableau
 * \return neant
*/
void PrintParam(TParamDef * _tabParam, const int _nbParam);

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
int ReadParamFromCommandLine(TParamDef * _tabParam, const int _nbParam, const int _argc, const char * _argv[]);

#endif