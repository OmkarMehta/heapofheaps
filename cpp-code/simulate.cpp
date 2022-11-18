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
            // Participant P3 = P[ParticipantPosition];
            // // Print P3 
            // cout << "P3: " << P3.participantID << ", " << P3.participantName << ", " << P3.universityName << endl;
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
              A.A[EventPosition].A->insert(0, &P[ParticipantPosition]); // Insert Participant in Event. 
              A.A[EventPosition].A->printArray();
            }
            cout << "Reached 7" << endl;
          }
        }
      } 
      else if (output[0] == "UPDATE") {
        // Create a new event
        int ParticipantPosition = 0;
        cout << "Reached Update" << endl;
        ParticipantPosition = SearchParticipant(output[2], P);
        cout << "Reached Update: ParticipantPosition: " << ParticipantPosition << endl;
        if (ParticipantPosition > 0)
        {
          Event E = Event(output[3]);
          int EventPosition =0;
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
          int EventPosition =0;
          EventPosition = A.SearchInHeap(&E);
          cout << "Reached TOP3: Event Position in Heap: " << EventPosition << endl;
          if (EventPosition > 0)
          {
            cout<<"Top3 in Event: " << output[3] << endl;
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
      else if (output[0]=="DELETE")
      {
        if (output[1]=="PARTICIPANT")
        {
          int ParticipantPosition=0;
          ParticipantPosition = SearchParticipant(output[2], P);
          cout << "Reached 2: ParticipantPosition: " << ParticipantPosition << endl;
          if (ParticipantPosition > 0)
          {
            // Participant participant = P[ParticipantPosition];
            for(int i=1;i<=EventCount;i++)
            {
              int ParticipantPosition1=0;
              ParticipantPosition1=A.A[i].A->SearchInHeap1(&P[ParticipantPosition]);
              cout << "ParticipantPosition in pahije te: "<<ParticipantPosition1<<endl;
              if(ParticipantPosition1>0)
              {
                A.A[i].A->removeparticipant(&P[ParticipantPosition]);
                A.UpdateKey(A.A[i].value);
                A.downHeapBubble(i);
                A.upHeapBubble(i);
						  }
					  }
            P[ParticipantPosition]=P[ParticipantCount];
            cout << "P at ParticipantCount is: "<< P[ParticipantCount].participantID<<endl;
            cout << "P at ParticipantPosition is: "<< P[ParticipantPosition].participantID << endl;
            ParticipantCount--;

          }

        }
        else if (output[1]=="EVENT")
        {
          if (output[2]=="PARTICIPANT")
          {
            int ParticipantPosition=0;
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
  cout << "Heap of Heaps" << endl;
  A.printArray();
  cout << "Events" << endl;
  for (int i = 1; i <= EventCount; i++)
  {
    A.A[i].A->printArray();
    cout << endl;
  }
  return 0;
}
