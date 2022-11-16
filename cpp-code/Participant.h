#pragma once
#include <string>
#include <iostream>

using namespace std;
class Participant
{
public:
  string participantID;
  string participantName;
  string universityName;
  Participant(string x, string y, string z);
  Participant(string x);
  Participant();
  void Print();
  void PrintForTOP3();
};

Participant::Participant() {}

Participant::Participant(string x, string y, string z)
{
  participantID = x;
  participantName = y;
  universityName = z;
}

Participant::Participant(string x)
{
  participantID = x;
  participantName = "Default";
  universityName = "Default";
}

void Participant::Print()
{
  cout << participantID << ", " << participantName << ", " << universityName << ", " << endl;
}

void Participant::PrintForTOP3()
{
  cout << participantID << ", " << participantName << ", " << universityName << ", ";
}
