// Řešení IJC-DU2, příklad b)
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1

#include "htab.h"

htab_t *htab_move(unsigned long new_size,htab_t *t2)
{
    htab_t *t1 = htab_init(new_size);
    struct htab_listitem *list;
    struct htab_listitem *list_help = NULL;
    for (unsigned long i = 0; i < t2->arr_size; i++)
    {
        list_help = t2->htab_data[i];
        if (list_help == NULL)
            continue;

        do
        {
            list = htab_lookup_add(t1, list_help->key);
            list->data = list_help->data;
            list_help = list_help->next;

        } while (list_help != NULL);
    }
    htab_clear(t2);

    return t1;
}
