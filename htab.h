// Řešení IJC-DU2, příklad b)
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1

#ifndef HTAB
#define HTAB

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "hash_function.h"

//struktura hash tabulky
typedef struct htab
{
    unsigned long arr_size;  //velikost pole ukazatelu 
    unsigned long n;	//pocet zaznamov
    struct htab_listitem *htab_data[];          //pole ukazatelov na zaznamy
} htab_t;


//struktura jedneho zaznamu
struct htab_listitem
{
    char *key;       //slovo ktore je ulozene v zazname         
    unsigned int data;      //pocet vyskytu klice
    struct htab_listitem *next;  //ukazatel na dalsi prvok
};

//prototypy funkcii potrebne k praci s hashovacou tabulkou
struct htab_listitem *htab_lookup_add(htab_t *t, const char *key);
htab_t *htab_init(unsigned int size);
bool htab_remove(htab_t *t, const char *key);
void htab_foreach(htab_t *t, void (*func)(const char *, unsigned int));
void htab_clear(htab_t *t);
void htab_free(htab_t *t);

#endif 
