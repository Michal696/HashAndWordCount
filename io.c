// Řešení IJC-DU2, příklad b)
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1


#include "io.h"

//nacita slovo z file a da ho zadanemu retazcu
//ignoruje biele znaky
//ak prekroci maximalnu dlzku tak sa ignoruju hodnoty
int get_word(char *s, int max, FILE *f)
{
    //overenie ci sa da subor otvorit
	int c;
    if (f == NULL)
    	return EOF; 
    //preskocenie prazdnych znakov
	while ((c = fgetc(f)) != EOF && isspace(c));
		;
	if (c == EOF)
		return EOF;
    s[0] = c;
	int i;
	for (i = 1; (isspace(c = fgetc(f))) == 0 ;i++)
	{
		if (c == EOF)
		{
			s[i] = '\0';
			return EOF;
		}
		if (i+1 >= max)
		{
			while (isspace(getc(f)) == 0)
				;//zahodime zvysok slova co sa nam nezmestil do riadku
			fprintf(stderr,"--> Bolo najdene prilis dlhe slovo, bolo orezane");
			break;
		}
		s[i] = c;
	}
	//pridame znak konca retezca
    s[i] = '\0'; 
	//vracime pocet nacitanych znakov slova + znak konca retazca
    return i;
}
