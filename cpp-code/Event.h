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

// constructor
Event::Event(string x, string y, string z)
{
  eventID = x;
  eventName = y;
  eventDescription = z;
}

// constructor
Event::Event(string x)
{
  eventID = x;
  eventName = "Default";
  eventDescription = "Default";
}

// constructor
Event::Event() {}
