// Řešení IJC-DU2, příklad b)
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1

#include "htab.h"

//volani funkce func pro kazdy prvek 
void htab_foreach(htab_t * t, void (*func)(const char *, unsigned int))
{
    //ak  je ukazatel NULL, nemam scima pracovat
    if (t == NULL)
    {
        fprintf(stderr, "--> neplatny ukazatel na tabulku\n");
        return;
    }

    //ukazatel na prvok zoznamu
    struct htab_listitem * list = NULL;
    //prejdeme kazdy zaznam v zozname 
    for (unsigned long i=0; i<t->arr_size;i++)   
    {
        list = t->htab_data[i];
	while (list != NULL)   
        {
            func(list->key, list->data);  //aplikace funkce
            list = list->next;
        }
    }
}
