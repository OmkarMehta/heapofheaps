#include <iostream>
#include <fstream>
#include "simulate.h"

using namespace std;
int main()
{
  Event *E = new Event[1000];
  Participant *P = new Participant[(uint)1E6];
  HeapofHeaps A = HeapofHeaps();

  ifstream file;
  file.open("Query.txt");
  string line;
  if (file.is_open())
  {
    while (getline(file, line))
    {
      char *array = new char[line.length() + 1];
      strcpy(array, line.c_str());
      string *output = Analyze(array);
      if (output[0] == "ADD")
      {
        if (output[1] == "PARTICIPANT")
        {
          P[++ParticipantCount] = Participant(output[2], output[3], output[4]);
          cout << "ParticipantCount: " << ParticipantCount << endl;
          // Print P array
          for (int i = 1; i <= ParticipantCount; i++)
          {
            cout << "P[" << i << "]: ";
            P[i].Print();
          }
        }
        else if (output[1] == "EVENT")
        {
          Event *event = new Event(output[2], output[3], output[4]);
          E[++EventCount] = event[0];
          cout << "EventCount: " << EventCount << endl;
          A.insert(0, event);
        }
        else
        {
          int ParticipantPosition = 0;
          cout << "Reached 1" << endl;
          ParticipantPosition = SearchParticipant(output[1], P);
          cout << "Reached 2: ParticipantPosition: " << ParticipantPosition << endl;
          if (ParticipantPosition > 0)
          {
            Participant P3 = P[ParticipantPosition];
            // Print P3 
            cout << "P3: " << P3.participantID << ", " << P3.participantName << ", " << P3.universityName << endl;
            cout << "Reached 3" << endl;
            Event E = Event(output[2]);
            cout << "Reached 4" << endl;
            int EventPosition = 0;
            EventPosition = A.SearchInHeap(&E);
            cout << "Reached 5 Event Position in Heap: " << EventPosition << endl;
            if (EventPosition > 0)
            {
              cout << "Reached 6" << endl;
              // Print the participants in the event of maxofmaxheap
              A.A[EventPosition].A->printArray();
              A.A[EventPosition].A->insert(0, &P3); // Insert Participant in Event. 
              A.A[EventPosition].A->printArray();
            }
            cout << "Reached 7" << endl;
          }
        }
      }

      delete[] array;
    }
  }
  file.close();
  cout << "Heap of Heaps" << endl;
  A.printArray();
  cout << "Events" << endl;
  for (int i = 1; i < EventCount; i++)
  {
    A.A[i].A->printArray();
    cout << endl;
  }
  return 0;
}
