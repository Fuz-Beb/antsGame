/**
 * \fn int main(int argc, char * argv[])
 * \brief fonction qui affiche les paramètres qu'ils reçoit sur la ligne de commande
 *
 * \param[in] _argc nombre d'arguments passes sur la ligne de commande
 * \param[in] _argv tableau qui contient les chaines de caracteres passees en arguments du programme
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