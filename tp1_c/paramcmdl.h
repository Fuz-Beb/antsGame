#ifndef PARAMCMDL_H
#define PARAMCMDL_H

#include "paramcmdl.c"

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