// Řešení IJC-DU2, příklad b)
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1

#include "hash_function.h"


//hashovacia funkcia z  webu "http://www.cse.yorku.ca/~oz/hash.html"
//+upravena podla zadania
unsigned int hash_function(const char *str) {
          unsigned int h=0;
          const unsigned char *p;
          for(p=(const unsigned char*)str; *p!='\0'; p++)
              h = 65599*h + *p;
          return h;
        }
