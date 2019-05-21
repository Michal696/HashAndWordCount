// Řešení IJC-DU2, příklad b)
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1

#include "htab.h"


//zrusi hash tabulku
void htab_free(htab_t *t)
{
    htab_clear(t);//uvolnenie obsahu tabulky
    free(t); //uvolnenie samostatnej tabulky
    t = NULL; 
}
