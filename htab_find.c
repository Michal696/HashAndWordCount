// Řešení IJC-DU2, příklad b)
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1

#include "htab.h"


struct htab_listitem *htab_find(htab_t *t, const char *key)
{
    if (t == NULL)
    {
        fprintf(stderr,"--> neplatny ukazatel\n");
        return NULL;
    }

    if(key == NULL)
    {
        fprintf(stderr,"--> key nemuze byt prazdny\n");
	 	return NULL;
    }


    struct htab_listitem *list;
    //index nam urci stlpec v ktorom sa nachadza nas key == kluc
    unsigned int index = hash_function(key) % t->arr_size;

    //ziskame ukazatel na stlpec ktory je priradeny nasemu klucu
    list = t->htab_data[index];       

    //zacneme prehladavat stlpec dokial nenajdeme nas kluc
    while (list != NULL)    
    {
        if (strcmp(list->key, key) == 0)    
        {
            //navysi sa najdeny pocet kluca
            list->data++;       
            return  list;        
        }
        //postupne prehladavame tabulku
        list = list->next;
    }
	return NULL;
}
