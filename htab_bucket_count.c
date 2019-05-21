// Řešení IJC-DU2, příklad b)
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1

#include "htab.h"


//vrati pocet prvku pole n z dane tabulky
size_t htab_bucket_count(htab_t *t)
{
	return t->arr_size;
}
