// Řešení IJC-DU2, příklad a)
// Autor: Michal Šajdík, FIT 
// Přeloženo: gcc 6.1.1

#include <iostream>
#include <fstream>
#include <queue> 
#include <string>
#include <sstream>

//defaultny pocet riadkov pre vypis
#define LINE 10   

using namespace std;

void tail(istream &entry, long rows);


int main(int argc,const char *argv[])
{

  long  rows=LINE;
  string parameter;
  bool state=false;
  istream *entry; 
  fstream file;

  if (argc == 1)  
  {
    entry= &cin;
    tail(*entry,rows);
  }
  
  if (argc == 2)
  {
    file.open(argv[1],ios::in);
    if (!file.is_open())
    {
      cerr << "-->Subor nejde otvorit" << endl;
      return EXIT_FAILURE;
    }
    entry=&file;
    tail(*entry,rows);
    file.close();
  }

  if(argc == 3 || argc == 4)
  {
      parameter=argv[1];

      if(!parameter.compare("-n")== 0)
      {
        cerr << "-->Zly format vstupu" << endl;
        return EXIT_FAILURE;
      }

      parameter=argv[2];
      state=parameter.find_first_not_of("+-0123456789") == std::string::npos;
      if(state == false)
      {
        cerr << "-->Zly format vstupu" << endl;
        return EXIT_FAILURE;
      }
     
      std::istringstream ss(parameter);
      ss >> rows;
      if(rows < 0)
      {
        rows=rows * (-1);
      }

  }
  if(argc == 3 )
  {
    entry=&cin;
    tail(*entry,rows);
  }

  if(argc > 4) 
  {
    cerr << "-->Privela argumentov" << endl;
    return EXIT_FAILURE;
  }
  if(argc == 4)
  {
    file.open(argv[3],ios::in);
    //overenie suboru
    if (!file.is_open())
    {
      cerr << "-->Neplatny subor => nejde otvorit" << endl;
      return EXIT_FAILURE;
    }
    entry=&file;
    tail(*entry,rows);
    file.close();
  }

  
  return EXIT_SUCCESS;
}

void tail(istream &entry, long rows)
{

    string row; 
    std::queue<string> container; 
    if(rows == 0)
    {
      return;
    }

    for (long i = 0; getline(entry, row); i++)
	{
      container.push(row);

      if (i >= rows)
      {        
         container.pop();    
      } 
    }

    while (!container.empty())     
    {
      
      row=container.front();
      container.pop();
      cout << row << endl;  
            
    }
    return;
}

