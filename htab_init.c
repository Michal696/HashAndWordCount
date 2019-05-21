// Řešení IJC-DU2, příklad b)
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1

#include "htab.h"

//inicializuje hashovaciu tabulku
htab_t *htab_init(unsigned int size)
{
   

    //zaberieme pamet  o velkosti struktury  htab_t + size* velkost struktury "htab_lisitem"
    //vyuzijeme flexible array member
    htab_t *table = malloc(sizeof(htab_t) + size * sizeof( struct htab_listitem *));
    //zistime ci sa nam podarilo allocovat dostatok pamete
    if (table == NULL)
        return NULL;
    //vycistime obsah lebo by tam mohlo byt cokoliv
    for (unsigned int i = 0;i<size; i++)
        table->htab_data[i] = NULL;
    //nastavime hlavicku hashovacej tabulky
    table->arr_size = size;   

    //nastavymi pocet zaznamu na 0
    table->n=0;

    //vratime ukazatel na vytvorenu tabulku
    return table;
}
