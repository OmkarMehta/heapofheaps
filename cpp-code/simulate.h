#pragma once
#include <cstring>
#include <sstream>
#include <vector>
#include "Event.h"

using namespace std;

string *Analyze(char *input)
{
  string *out = new string[5];
  for (size_t i = 0; i < 5; i++)
  {
    out[i] = "YYYYY";
  }

  char *split1 = strtok(input, " \n");
  out[0] = split1;

  if (split1 != NULL)
  {
    char *split2 = strtok(NULL, ", ");

    if (strcmp(split1, "TOP3") == 0 && split2 == NULL)
    {
      return out;
    }
    out[1] = split2;
    while (split2 != NULL)
    {
      if (strcmp(split1, "ADD") == 0 &&
          (strcmp(split2, "EVENT") == 0 ||
           strcmp(split2, "PARTICIPANT") == 0))
      {
        out[2] = strtok(NULL, ", ");
        out[3] = strtok(NULL, ", ");
        out[4] = strtok(NULL, ", ");
        return out;
      }
      else if (strcmp(split1, "ADD") == 0)
      {
        out[2] = strtok(NULL, ", ");
        return out;
      }
      else if (strcmp(split1, "UPDATE") == 0 && strcmp(split2, "SCORE") == 0)
      {

        out[2] = strtok(NULL, ", ");
        out[3] = strtok(NULL, ", ");
        out[4] = strtok(NULL, ", ");
        return out;
      }
      else if (strcmp(split1, "TOP3") == 0 && strcmp(split2, "IN") == 0)
      {
        out[2] = strtok(NULL, ", ");
        out[3] = strtok(NULL, ", ");
        // cout << out[2] << " XXXX " << out[3] << endl;
        return out;
      }
      else if (strcmp(split1, "DELETE") == 0 && strcmp(split2, "PARTICIPANT") == 0)
      {
        out[2] = strtok(NULL, ", ");
        return out;
      }
      split2 = strtok(NULL, ", ");
    }
  }
  cout << "Ohh!" << endl;
  return out;
}