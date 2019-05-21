// Řešení IJC-DU2, příklad b)
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1

#include "htab.h"


struct htab_listitem *htab_lookup_add(htab_t *t, const char *key)
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
	//ak sme nenasli kluc, tak ho pridame
    list = malloc(sizeof(*list));
    if (list == NULL)
    {
        fprintf(stderr,"--> nepodarilo sa nam allokovat potrebnu pamet pre rozsirenie listu");
        return NULL;
    }

    //ziskame pamet pre kluc    
    list->key = malloc((strlen(key)+1) * sizeof(char)); //+1 kvoli ukoncovaci nule v ;stringu;


    if(list->key == NULL)    
    {
		fprintf(stderr,"--> nepodarilo sa nam allokovat potrebnu pamet pre pridanie kluca");
        //uvolnenie ukazatela na strukturu, ktora bola alokovana
        free(list);
        return NULL;
    }
	//prekopirujeme zadany kluc do tabulky
    strcpy(list->key, key);  
    list->data =1;

    // si ulozime sucasny zaznam ako nasledujuci zaznam pre nas
    list->next=t->htab_data[index];

    //nastavime novy zaznam na poziciu nahradeneho a nahradeny bude nasledovat za nim v poli
    t->htab_data[index]=list;
    t->n++; //pridali sme jeden zoznam

    return list;
}
