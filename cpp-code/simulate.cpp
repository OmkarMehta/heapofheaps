#include <iostream>
#include <fstream>
#include "simulate.h"

using namespace std;
int main()
{
  ifstream file;
  file.open("Query.txt");
  string line;
  if (file.is_open())
  {

    while (getline(file, line))
    {
      char *array = new char[line.length() + 1];
      strcpy(array, line.c_str());
      // for (int i = 0; i < line.length(); i++)
      // cout << array << endl;
      string *output = Analyze(array);
      for (int i = 0; i < 5; i++)
        cout << output[i] << endl;
      cout << endl;
      // exit(-1);
    }
  }
  file.close();
  return 0;
}
