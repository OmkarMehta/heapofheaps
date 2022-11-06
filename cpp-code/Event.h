#pragma once
#include <string>
using namespace std;

class Event
{
public:
  string eventID, eventName, eventDescription;
  Event(string x, string y, string z);
  Event(string x);
  Event();
};

Event::Event(string x, string y, string z)
{
  eventID = x;
  eventName = y;
  eventDescription = z;
}

Event::Event(string x)
{
  eventID = x;
  eventName = "Default";
  eventDescription = "Default";
}

Event::Event() {}
