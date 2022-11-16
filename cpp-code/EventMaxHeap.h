#pragma once
#include "Participant.h"

using namespace std;

class Entry
{
public:
  int key;            // This denotes the key of the entry stored at the node
  Participant *value; // This denotes the value of the entry stored at the node
  Entry(int k, Participant *v);
  Entry();
};
Entry::Entry() {}

Entry::Entry(int k, Participant *v)
{
  key = k;
  value = v;
}

class EventMaxHeap
{
public:
  static const int MAX_HEAP_SIZE = (int)1E6; // This indicates the maximum size the heap can grow into.
  Entry *A;                                  // This is the array of references to entries
  int size;                                  // This is the number of current entries in the heap
  // This is the initialization method for the array based max-heap implementation
  EventMaxHeap();
  void swapVals(int p, int q);
  Participant *max();
  bool isEmpty();
  void upHeapBubble(int i);
  void downHeapBubble(int i);
  void insert(int k, Participant *v);
  Participant *removeMax();
  void removeparticipant(Participant *P);
  int SearchInHeap(Participant *P);
  int SearchInHeap1(Participant *P);
  void printArray();
  void UpdateScore(int key, Participant *P);
  void TOP3INEVENT(EventMaxHeap temp);
};

EventMaxHeap::EventMaxHeap()
{
  size = 0;
  A = new Entry[MAX_HEAP_SIZE + 1];
}

// This method swaps the key-value pairs stored at given indices in the array A
void EventMaxHeap::swapVals(int p, int q)
{
  Participant *temp1 = A[p].value;
  int temp2 = A[p].key;
  A[p].key = A[q].key;
  A[p].value = A[q].value;
  A[q].key = temp2;
  A[q].value = temp1;
}

// This is the max() method that returns the maximum element in the heap
Participant *EventMaxHeap::max()
{
  return (A[1].value);
}

// This method returns whether the heap is empty or not
bool EventMaxHeap::isEmpty()
{
  if (size == 0)
    return (true);
  else
    return (false);
}

// This method implements the up-heap bubble
void EventMaxHeap::upHeapBubble(int i)
{
  if (i == 1 || i == 0)
  {
    return;
  }
  while (A[i].key > A[i / 2].key && i > 1)
  {
    swapVals(i, i / 2);
    i = i / 2;
    if (i == 1 || i == 0)
    {
      return;
    }
  }
  return;
}

// This method implements the down heap bubble
void EventMaxHeap::downHeapBubble(int i)
{
  int k = 0;
  if (2 * i <= size)
  {
    if (A[i].key < A[2 * i].key)
      k = 1;
  }
  if (2 * i + 1 <= size)
  {
    if (A[i].key < A[2 * i + 1].key)
      k = 1;
  }
  if (k == 1)
  {

    int greatestbit;
    if (A[2 * i].key > A[2 * i + 1].key)
      greatestbit = 2 * i;
    else
      greatestbit = 2 * i + 1;
    swapVals(i, greatestbit);
    downHeapBubble(greatestbit);
  }
}

void EventMaxHeap::insert(int k, Participant *v)
{
  int Position = SearchInHeap1(v);
  cout << "Position is " << Position << endl;
  if (Position > 0)
  {
    cout << "Exception in " << __FILE__ << " at line " << __LINE__ << endl;
    cout << "Participant already exists in the event" << endl;
    throw "Exception";
  }
  else
  {
    Entry E = Entry(k, v);
    A[++size] = E;
    upHeapBubble(size);
  }
}

// This method implements the removeMax() operation
Participant *EventMaxHeap::removeMax()
{
  if (size == 0)
  {
    cout << "Exception in " << __FILE__ << " at line " << __LINE__ << endl;
    throw exception();
  }
  Participant *result = A[1].value;
  if (size == 1)
  {
    A[1].key = (int)0;
    size--;
    return (result);
  }
  // Copy the entry at index "size" to the root
  A[1].key = A[size].key;
  A[1].value = A[size].value;
  size--;
  downHeapBubble(1);
  return (result);
}

// This method just prints the array storing the heap
void EventMaxHeap::removeparticipant(Participant *P)
{
  int position = 0;
  try
  {
    position = SearchInHeap(P);
  }
  catch (exception e)
  {
    cout << e.what() << endl;
  }
  if (position > 0)
  {
    swapVals(position, size);
    size--;
    downHeapBubble(position);
  }
}

int EventMaxHeap::SearchInHeap(Participant *P)
{
  // cout << "Reached here" << endl;
  // cout << size << endl;
  for (int i = 1; i <= size; i++)
  {

    if (P->participantID.compare(A[i].value->participantID) == 0)
      return i;
  }
  cout << "Exception in " << __FILE__ << " at line " << __LINE__ << endl;
  throw new exception();
}

int EventMaxHeap::SearchInHeap1(Participant *P)
{
  for (int i = 1; i <= size; i++)
  {
    cout << P->participantID << "\t" << A[i].value->participantID << endl;
    if (P->participantID.compare(A[i].value->participantID) == 0)
      return i;
  }
  return 0;
}

void EventMaxHeap::printArray()
{
  for (int i = 1; i <= size; ++i)
  {
    cout << "(" << A[i].key << ", " << A[i].value->participantID << "), ";
  }
  cout << endl;
}

void EventMaxHeap::UpdateScore(int key, Participant *P)
{
  int Position = SearchInHeap(P);
  A[Position].key = key;
  downHeapBubble(Position);
  upHeapBubble(Position);
}

void EventMaxHeap::TOP3INEVENT(EventMaxHeap temp)
{
  int first = temp.A[1].key;
  int PO = 0;
  Participant *First = new Participant("dummy");
  try
  {
    First = temp.removeMax();
    if (first != 0)
    {
      First->Print();
      cout << first << endl;
    }
  }
  catch (exception e)
  {
    PO = 1;
    return;
  }

  // First Participant Found
  Participant *Second = new Participant("dummy");
  Participant *Third = new Participant("dummy1");
  int second = 0, third = 0;
  second = temp.A[1].key;
  try
  {
    Second = temp.removeMax();
    if (second != 0)
    {
      Second->Print();
      cout << second << endl;
    }
  }
  catch (exception e)
  {
    PO = 1;
    try
    {
      temp.insert(first, First);
    }
    catch (exception e1)
    {
    }
    return;
  }

  third = temp.A[1].key;
  try
  {
    Third = temp.removeMax();
    if (third != 0)
    {
      Third->Print();
      cout << third << endl;
    }
  }
  catch (exception e)
  {
    PO = 1;
    try
    {
      temp.insert(first, First);
      temp.insert(second, Second);
      return;
    }
    catch (exception e1)
    {
    }
  }

  if (PO == 0)
  {
    try
    {
      temp.insert(first, First);
      temp.insert(second, Second);
      temp.insert(third, Third);
    }
    catch (exception e)
    {
    }
  }
}