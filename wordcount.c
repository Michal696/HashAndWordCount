// Řešení IJC-DU2, příklad b)
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1

#include <stdio.h>
#include <stdlib.h>
#include "htab.h"
#include "io.h"

#define MAX_LENGTH 127  //maximalna dlzka slov ostatne znaky sa zahodia
const unsigned int HASH_SIZE = 12289;
// hodnota z http://planetmath.org/goodhashtableprimes

//prototyp funkcie na tlac slova a jeho vyskytu 
void print_word(const char *key, unsigned int pocet);

int main(void)
{
    htab_t *hash_table; 
    struct htab_listitem *list;
    hash_table=htab_init(HASH_SIZE);
    //overenie ci sa podarilo vytvorit hashovaciu tabulku
    if (hash_table == NULL)
    {
        fprintf(stderr, "--> Nepodarilo sa inicializovat hashovaciu tabulku\n");
        return EXIT_FAILURE;
    }

    char buffer_word[MAX_LENGTH+1];
    buffer_word[0]='\0';      

    //cyklus nacitava slovo po slove zo vstupu
    while (get_word(buffer_word, MAX_LENGTH, stdin) != EOF)    
    {
        //zavolame funkciu ktora bud  pripocita vyskyt slova alebo ho prida do hash table
        list=htab_lookup_add(hash_table, buffer_word);
        //overenie ci sa podarilo pridat zaznam to hashovacej tabulky
         if (list == NULL)    
         {
             fprintf(stderr, "--> Nebolo mozne pridat zaznam do hashovacej tabulky\n");
             htab_free(hash_table);
             return EXIT_FAILURE;
         }
            hash_table->n++;
    }

    //vyuzijeme funkciu foreach na vypisanie 
    htab_foreach(hash_table, print_word);  
    //uvolnenie celej hashovacej tabulky   
    htab_free(hash_table);   

    return EXIT_SUCCESS;
}

//funkcia ktora vytlaci slovo a jeho vyskyt v nasej tabulke
void print_word(const char *key, unsigned int pocet)
{
    //tlaci na vystup slovo,tabulator,pocet nalezu slova
    printf("%s\t%u\n", key, pocet);
}
