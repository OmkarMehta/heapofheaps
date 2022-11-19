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
  file.open("../Query_Final/Query.txt");
  string line;
  if (file.is_open())
  {
    uint linecount = 0;
    while (getline(file, line))
    {
      linecount++;
      if (linecount % 500 == 0)
        Log(critical, "Processed %u lines!", linecount);
      char *array = new char[line.length() + 1];
      strcpy(array, line.c_str());
      string *output = Analyze(array);
      if (output[0] == "ADD")
      {
        if (output[1] == "PARTICIPANT")
        {
          P[++ParticipantCount] = Participant(output[2], output[3], output[4]);
          // cout << "ParticipantCount: " << ParticipantCount << endl;
          // Print P array
          // for (int i = 1; i <= ParticipantCount; i++)
          // {
          //   cout << "P[" << i << "]: ";
          //   P[i].Print();
          // }
        }
        else if (output[1] == "EVENT")
        {
          Event *event = new Event(output[2], output[3], output[4]);
          E[++EventCount] = event[0];
          // cout << "EventCount: " << EventCount << endl;
          A.insert(0, event);
        }
        else
        {
          int ParticipantPosition = 0;
          Log(debug, "Reached 1\n");
          ParticipantPosition = SearchParticipant(output[1], P);
          Log(debug, "Reached 2: ParticipantPosition: %d\n", ParticipantPosition);
          // cout << "Reached 2: ParticipantPosition: " << ParticipantPosition << endl;
          if (ParticipantPosition > 0)
          {
            // Participant P3 = P[ParticipantPosition];
            // // Print P3
            // cout << "P3: " << P3.participantID << ", " << P3.participantName << ", " << P3.universityName << endl;
            Log(debug, "Reached 3\n");
            Event E = Event(output[2]);
            Log(debug, "Reached 4\n");
            int EventPosition = 0;
            EventPosition = A.SearchInHeap(&E);
            Log(debug, "Reached 5 Event Position in Heap: %d\n", EventPosition);
            // cout << "Reached 5 Event Position in Heap: " << EventPosition << endl;
            if (EventPosition > 0)
            {
              Log(debug, "Reached 6\n");
              // Print the participants in the event of maxofmaxheap
              // A.A[EventPosition].A->printArray();
              A.A[EventPosition].A->insert(0, &P[ParticipantPosition]); // Insert Participant in Event.
              // A.A[EventPosition].A->printArray();
            }
            Log(debug, "Reached 7\n");
          }
        }
      }
      else if (output[0] == "UPDATE")
      {
        // Create a new event
        int ParticipantPosition = 0;
        Log(debug, "Reached Update\n");
        ParticipantPosition = SearchParticipant(output[2], P);
        Log(debug, "Reached Update; ParticipantPosition: %d\n", ParticipantPosition);
        // cout << "Reached Update: ParticipantPosition: " << ParticipantPosition << endl;
        if (ParticipantPosition > 0)
        {
          Event E = Event(output[3]);
          int EventPosition = 0;
          EventPosition = A.SearchInHeap(&E);
          // cout << "Reached Update: Event Position in Heap: " << EventPosition << endl;
          if (EventPosition > 0)
          {
            A.A[EventPosition].A->UpdateScore(stoi(output[4]), &P[ParticipantPosition]);
          }
          A.UpdateKey(&E);
          A.downHeapBubble(EventPosition);
          A.upHeapBubble(EventPosition);
        }
      }
      else if (output[0] == "TOP3")
      {
        // check if IN and EVENT exists
        if (output[1] == "IN" && output[2] == "EVENT")
        {
          Event E = Event(output[3]);
          int EventPosition = 0;
          EventPosition = A.SearchInHeap(&E);
          Log(debug, "Reached TOP3: Event Position in Heap: %d\n", EventPosition);
          // cout << "Reached TOP3: Event Position in Heap: " << EventPosition << endl;
          if (EventPosition > 0)
          {
            Log<false>(info, "TOP3 in Event: ");
            cout << output[3] << endl;
            A.A[EventPosition].A->TOP3INEVENT(*(A.A[EventPosition].A));
            cout << endl;
          }
        }
        else
        {
          A.TOP3();
          // cout << endl;
          // cout << "Heap of Heaps" << endl;
          // A.printArray();
          // cout << "Events" << endl;
          // for (int i = 1; i <= EventCount; i++)
          // {
          //   A.A[i].A->printArray();
          //   cout << endl;
          // }
        }
      }
      else if (output[0] == "DELETE")
      {
        if (output[1] == "PARTICIPANT")
        {
          int ParticipantPosition = 0;
          ParticipantPosition = SearchParticipant(output[2], P);
          Log(debug, "Reached 2: ParticipantPosition: %d\n", ParticipantPosition);
          // cout << "Reached 2: ParticipantPosition: " << ParticipantPosition << endl;
          if (ParticipantPosition > 0)
          {
            // Participant participant = P[ParticipantPosition];
            for (int i = 1; i <= EventCount; i++)
            {
              int ParticipantPosition1 = 0;
              ParticipantPosition1 = A.A[i].A->SearchInHeap1(&P[ParticipantPosition]);
              Log(debug, "ParticipantPosition in pahijet te: %d\n", ParticipantPosition1);
              if (ParticipantPosition1 > 0)
              {
                A.A[i].A->removeparticipant(&P[ParticipantPosition]);
                A.UpdateKey(A.A[i].value);
                A.downHeapBubble(i);
                A.upHeapBubble(i);
              }
            }
            P[ParticipantPosition] = P[ParticipantCount];
            // cout << "P at ParticipantCount is: " << P[ParticipantCount].participantID << endl;
            // cout << "P at ParticipantPosition is: " << P[ParticipantPosition].participantID << endl;
            ParticipantCount--;
          }
        }
        else if (output[1] == "EVENT")
        {
          if (output[2] == "PARTICIPANT")
          {
            int ParticipantPosition = 0;
            ParticipantPosition = SearchParticipant(output[3], P);
            if (ParticipantPosition > 0)
            {
              Event E = Event(output[4]);
              A.DeleteEventParticipant(&E, &P[ParticipantPosition]);
            }
          }
          else
          {
            Event E = Event(output[2]);
            A.removeevent(&E);
          }
        }
      }

      delete[] array;
    }
  }
  file.close();
  // Log(debug, "Heap of Heaps");
  // << "Heap of Heaps" << endl;
  // A.printArray();
  // cout << "Events" << endl;
  // for (int i = 1; i <= EventCount; i++)
  // {
  //   A.A[i].A->printArray();
  //   cout << endl;
  // }
  return 0;
}
