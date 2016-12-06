/**
 * \fn int ReadParamFromCommandLine(TParamDef * _tabParam, const int _nbParam, const int _argc, const char * _argv[])
 * \brief fonction qui affiche les paramètres qu'ils reçoit sur la ligne de commande
 *
 * \param[in] _argc nombre d'arguments passes sur la ligne de commande
 * \param[in] _argv tableau qui contient les chaines de caracteres passees en arguments du programme
 * \return >=0 : nombre de parametres mis a jour, <0 : erreur
*/
#include <stdio.h>

int main(int argc, char * argv[])
{
    int i = 0;
    
    while (argc > 0)
    {
        printf("<%s>", argv[i]);
        argc--;
        i++;
    }
}