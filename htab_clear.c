// Řešení IJC-DU2, příklad b)
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1

#include "htab.h"


//vycisti celu hashovaciu tabulku
void htab_clear(htab_t *t)
{
 
    if (t == NULL || t->htab_data == NULL) 
        return;//uz to je ciste

    struct htab_listitem *list = NULL;
    struct htab_listitem *list_next = NULL;

    //prechadzame  celu tabulku
    for (unsigned long i = 0; i < t->arr_size; i++)
    {
        list = t->htab_data[i];
        //ak je list == NULL tak je prazdny a nie je duvod uvolnovat
        //ak obsahuje ukazatel, zacneme uvolnovat zoznam
        while (list != NULL)            
        {
            list_next = list->next;
            free(list->key);  
            free(list);
            list = list_next;     
        } 
        t->htab_data[i] = NULL; 
           
    }
    //nakoniec nastavyme pocitadlo zaznamov na 0, pretoze sme vsetky odstranili
    t->n=0;
}
