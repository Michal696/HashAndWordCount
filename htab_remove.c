// Řešení IJC-DU2, příklad b)
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1

#include "htab.h"


//vymaze z hash tabulky zaznam pre dany key a vrati hodnotu podla toho ci sa mu to podarilo
bool htab_remove(htab_t *t, const char *key)
{
    if (t == NULL)
    {
        fprintf(stderr, "--> neplatny ukazatel\n");
        return false;
    }
    if(key == NULL)
    {
        fprintf(stderr, "--> key nemoze byt prazdny\n");
        return false;
    }


    unsigned int index = hash_function(key) % t->arr_size;
	bool state = false;	

    struct htab_listitem *list = t->htab_data[index];
    struct htab_listitem *list_help = NULL;

	while (list != NULL)//projdeme cely stlpec
	{
		if(strcmp(list->key,key) == 0)
		{
			state = true;
			if (list_help != NULL && list->next != NULL)//ma dva sousedy
				list_help->next = list->next; //nahradime
			else
				if (list_help == NULL && list->next != NULL)//je pvni a ma souseda
					t->htab_data[index] = list->next; //nahradime
				else
					if (list_help != NULL && list->next == NULL)//je posledni
						list_help->next = NULL; 
					else
						t->htab_data[index] = NULL;
			free(list->key);
			list->next = NULL;
			free(list);
			t->n--;
			break;			
		}
		//posuvanie sa v zaznamoch
		list_help = list;
		list = list->next;
	}

	return state;
}
