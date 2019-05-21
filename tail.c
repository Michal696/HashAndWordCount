// Řešení IJC-DU2, příklad a)
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

//defaultny pocet riadkov pre vypis
#define LINECOUNT 10
//maximalna dlzka riadku
#define LIMITROW 1024


//struktura pre pracu s parametrami
typedef struct param
{
	long rows;
	bool state;
	FILE *file;
}param_t;

//prototypy funkcii
param_t secure_entry(int argc, char **argv);
void tail(FILE *file, long rows);

int main(int argc, char **argv)
{
	param_t parameters;
	parameters = secure_entry(argc,argv);
	
	//nevhodny format viz. secure_entry(argc,argv)
	if (parameters.state == false)
	{
	//	fclose(parameters.file);
		return EXIT_FAILURE;
	}

	tail(parameters.file,parameters.rows);

	if(parameters.file != NULL)
	{
		fclose(parameters.file);
	}

	return EXIT_SUCCESS;
}

void tail(FILE *file, long rows)
{
	int last_char;
	bool alarm = false;

	if (rows == 0)
		return;

	if ( file == NULL )
		file = stdin;

	char buffer[rows][LIMITROW];
	long abacus = 0;
	long rows_count = 0;
	while(fgets(buffer[abacus],LIMITROW,file) != NULL)
	{
		//overenie ze cely riadok ktory sme nacitali neobsahuje koniec riadku
		//nastavenie sa na novy riadok a zahodenie nacitanych znakov
		if (strchr(buffer[abacus],'\n') == NULL)
		{
			if (alarm == false)
			{
				fprintf(stderr, "-->Riadok je dlhsi ako je limita 1024 znakov,dochadza k orezaniu\n");
				alarm = true;
			}
		
			while ((last_char = getc(file)) != '\n' && last_char !=EOF)
				;
		}	
		rows_count++;
		abacus++;
		//nedostatocny pocet riadkov v subore
		//chceme vytlacit viac riadkov ako ma'me
		if(abacus >= rows)
			abacus = 0;

	}
	//plny buffer
	if(rows_count > rows)
	{
		for (long i = abacus; i < rows ; i++)
		{
			if (strchr(buffer[i], '\n') == NULL)
				printf("%s\n",buffer[i]);
			else
				printf("%s",buffer[i]);
		}
	}
	//bez potreby bufferu // menej ako 10 riadkov
	for (long i = 0 ; i < abacus ; i++)
	{
		if (strchr(buffer[i], '\n') == NULL)
			printf("%s\n",buffer[i]);
		else 
			printf("%s",buffer[i]);
	}


}



//osetrenie vstupou
param_t secure_entry(int argc, char **argv)
{
	param_t entry;
	entry.rows = LINECOUNT;
	entry.state = false;
	entry.file = NULL;
	FILE *file;
	char *ptr;
	long overflow = 0;
	//prilis vela argumentov
	if (argc > 4)
	{
		fprintf(stderr,"-->Privela argumentov\n");
		entry.state = false;
		return entry;
	}
	//bez argmentov
	if (argc == 1)
	{
		entry.state = true;
		return entry;
	}	
	// jeden argument // subor
	if (argc == 2)
	{
		file = fopen(argv[1],"rb");
		if (file == NULL)
		{
			fprintf(stderr,"-->Neplatny subor => nejde otvorit\n");
			entry.state = false;
			return entry;  // vracime prioritne entry.state == false //podminka pre vzhodnotenie chyby
		}
		else
		{
			entry.state = true;
			entry.file = file;
		}
	}
	//overenie viacerych poradi argumentov
	if ((argc == 3) || (argc == 4))
	{
		//overenie otvorenia suboru
		if (argc == 4)
		{
			if (strcmp(argv[1],"-n") == 0)
			{
				file = fopen(argv[3],"rb");
				if (file == NULL)
				{
					fprintf(stderr,"-->Neplatny subor => nejde otvorit\n");
					entry.state = false;
					return entry;
				}
				else
					entry.file = file;
			}
			if (strcmp(argv[2],"-n") == 0)
			{
				file = fopen(argv[1],"rb");
				if (file == NULL)
				{
					fprintf(stderr,"-->Neplatny subor => nejde otvorit\n");
					entry.state = false;
					return entry;
				}
				else
					entry.file = file;				
			}
		}
	
		//overenie -n number
		//v pripade zaporneho number sa pouzije jeho absolutna hodnota
		if (strcmp(argv[1],"-n") != 0)  //(strcmp(argv[1],"-n"))
		{		
			if(strcmp(argv[2],"-n") != 0)
			{
				fprintf(stderr,"-->Zle zadane argumenty, skus tail soubor nebo tail -n pocet_radu '<'soubor\n");
				entry.state = false;
				return entry;		
			}
			else
			{
			if ((fabs(strtol(argv[3],&ptr,10)) - LONG_MAX) > 0)
				overflow = 1;
	//		overflow = strtol(argv[3],&ptr,10) / LONG_MAX;
				if (*ptr != 0)
				{
					fprintf(stderr,"-->Po prepinaci -n musi nasledovat cislo\n");
					entry.state = false;
					return entry;
				}
				if (overflow != 0)
				{
					fprintf(stderr,"-->Cislo se nezmesti do long nastal overflow 1\n");
					entry.state = false;
					return entry;
				}
				entry.rows = strtol(argv[3],&ptr,10);
				entry.state = true;
			}
		}
		else
		{
			if ((fabs(strtol(argv[2],&ptr,10)) - LONG_MAX) > 0)
				overflow = 2;
	//		overflow = strtol(argv[2],&ptr,10) / LONG_MAX;
			if (*ptr != 0)
			{
					fprintf(stderr,"-->Po prepinaci -n musi nasledovat cislo\n");
					entry.state = false;
					return entry;
			}
			if (overflow != 0)
			{
				fprintf(stderr,"-->Cislo sa nezmesti do long nastal overflow 2\n");
				entry.state = false;
				return entry;
			}
			entry.rows = strtol(argv[2],&ptr,10);
			entry.state = true;
		}

	}

//absolutna hodnota z poctu riadkou ak boli zaporne
// + mozne vyhodenie chyby ak je to nemozne
		if (entry.rows < 0 )
		{
			if(entry.rows == LONG_MIN)
			{
					fprintf(stderr,"-->Cislo se nezmesti do long, lebo zadane zaporne cislo nema absolutnu hodnotu\n");
					entry.state = false;
					return entry;
			}
		entry.rows = (-1) * entry.rows;			
		}
	

return entry;
}


