
#include "Event.h"
#include "EventMaxHeap.h"
#include "logger.h"

using namespace std;
class Entry1
{
public:
    int key;
    Event *value;
    EventMaxHeap *A;
    // constructor
    Entry1(int k, Event *v)
    {
        key = k;
        value = v;
    }
    Entry1()
    {
    }
};

class HeapofHeaps
{
public:
    static const int MAX_HEAP_SIZE1 = 1000;
    Entry1 *A;
    int size;
    // constructor
    HeapofHeaps()
    {
        A = new Entry1[MAX_HEAP_SIZE1 + 1];
        size = 0;
    }

    void swapVals(int p, int q)
    {
        Event *temp1 = A[p].value;
        int temp2 = A[p].key;
        EventMaxHeap *temp3 = A[p].A;
        A[p].key = A[q].key;
        A[p].value = A[q].value;
        A[p].A = A[q].A;
        A[q].key = temp2;
        A[q].value = temp1;
        A[q].A = temp3;
    }

    // This is the max() method that returns the maximum element in the heap of heaps
    Event *max()
    {
        return A[1].value;
    }

    // This method returns whether the heap is empty or not
    bool isEmpty()
    {
        return size == 0;
    }

    // This method implements the up-heap bubble
    void upHeapBubble(int i)
    {
        if (i == 1 || i == 0)
            return;
        while (A[i].key > A[i / 2].key && i > 1)
        {
            swapVals(i, i / 2);
            i = i / 2;
            if (i == 1 || i == 0)
                return;
        }
        return;
    }

    // This method implements the down-heap bubble
    void downHeapBubble(int i)
    {
        int k = 0;
        if (2 * i <= size)
        {
            if (A[i].key < A[2 * i].key)
            {
                k = 1;
            }
        }
        if (2 * i + 1 <= size)
        {
            if (A[i].key < A[2 * i + 1].key)
            {
                k = 1;
            }
        }
        if (k == 1)
        {
            int greatestbit = 0;
            if (2 * i + 1 <= size)
            {
                if (A[2 * i + 1].key > A[2 * i].key)
                {
                    greatestbit = 2 * i + 1;
                }
                else
                {
                    greatestbit = 2 * i;
                }
            }
            else
            {
                greatestbit = 2 * i;
            }
            swapVals(i, greatestbit);
            downHeapBubble(greatestbit);
        }
    }

    // This method inserts a new element into the heap of heaps with exception handling
    void insert(int k, Event *v)
    {
        int position = SearchInHeap1(v);
        // cout << "Position in Heap " << position << endl;
        if (position > 0)
        {
            // throw exception
            Log(warn, "Event already exists in the heap of heaps\n");
        }
        EventMaxHeap *O = new EventMaxHeap();
        Participant *P = new Participant("Dummy");
        try
        {
            O->insert(k, P);
        }
        catch (const char *msg)
        {
            cout << msg << endl;
        }
        O->removeparticipant(P);
        Entry1 E = Entry1(k, v);
        A[++size] = E;
        A[size].A = O;
        upHeapBubble(size);
    }

    // This method updates the key of an element in the heap of heaps
    void UpdateKey(Event *E)
    {
        int Position = 0;

        Position = SearchInHeap(E);
        if (Position > 0)
            A[Position].key = A[Position].A->A[1].key;
    }

    // This method removes the maximum element from the heap of heaps
    Event *removeMax()
    {
        Event *result = A[1].value;
        if (size == 1)
        {
            A[1].key = (int)0;
            size--;
            return result;
        }
        // Copy the entry at index "size" to the root
        A[1].key = A[size].key;
        A[1].value = A[size].value;
        size--;
        downHeapBubble(1);
        return result;
    }

    // this method removes event
    void removeevent(Event *P)
    {
        int position = 0;
        position = SearchInHeap(P);
        if (position > 0)
        {
            if (size == 1)
            {
                A[1].key = (int)0;
                size--;
                return;
            }
            swapVals(position, size);
            size--;
            downHeapBubble(position);
        }
    }

    // This method returns warning
    int SearchInHeap(Event *P)
    {
        for (int i = 1; i <= size; i++)
        {
            if (A[i].value->eventID == P->eventID)
            {
                return i;
            }
        }
        Log(warn, "Event not found in the heap of heaps\n");
        return -1;
    }
    // This method does not returns warning
    int SearchInHeap1(Event *P)
    {
        for (int i = 1; i <= size; i++)
        {
            if (A[i].value->eventID == P->eventID)
            {
                return i;
            }
        }
        return -1;
    }

    // This method deletes event participant
    void DeleteEventParticipant(Event *E1, Participant *P1)
    {
        // Search for Event in Heap
        int EventPosition = 0;

        EventPosition = SearchInHeap(E1);

        if (EventPosition > 0)
        {
            A[EventPosition].A->removeparticipant(P1);
            UpdateKey(E1);

            downHeapBubble(EventPosition);
            // Need not do upHeapBubble because removing participant will always decrease score.
        }
    }

    // This method removes participant
    void RemoveParticipant(Participant *P)
    {
        for (int i = 1; i <= size; i++)
        {
            A[i].A->removeparticipant(P);
        }
    }

    // Used for debugging
    void printArray()
    {
        for (int i = 1; i <= size; i++)
        {
            cout << "(" << A[i].key << ", " << A[i].value->eventID << ", " << A[i].value->eventName << ", " << A[i].value->eventDescription << "), ";
        }
        cout << endl;
    }

    void TOP3()
    {
        // cout << "Top3 of HeapofHeaps:" << endl;
        Log(info, "Top3 of HeapofHeaps:");
        int first = A[1].key;
        int PO = 0; // Signifies if error has been caught
        Participant *First = new Participant("Dummy");
        Event *FEvent = A[1].value;
        try
        {
            First = A[1].A->removeMax();
            UpdateKey(A[1].value);
            if (first != 0)
            {
                First->PrintForTOP3(); // Custom print for legibility
                cout << A[1].value->eventID << ", " << A[1].value->eventName << ", " << first << endl;
            }
        }
        catch (const char *msg)
        {
            PO = 1;
            cout << msg << endl;
            return;
        }
        // Since key of first Event is updated
        downHeapBubble(1);
        int FEventPosition = 0;
        Participant *Second = new Participant("Dummy");
        Participant *Third = new Participant("Dummy1");
        int second = 0, third = 0;
        second = A[1].key;
        try
        {
            Second = A[1].A->removeMax();
            UpdateKey(A[1].value);
            if (second != 0)
            {
                Second->PrintForTOP3();
                cout << A[1].value->eventID << ", " << A[1].value->eventName << ", " << second << endl;
            }
        }
        catch (const char *msg) // If removeMax throws an error
        {
            PO = 1; // Set flag for error thrown

            FEventPosition = SearchInHeap(FEvent);
            if (FEventPosition > 0)
            {
                A[FEventPosition].A->insert(first, First);
                UpdateKey(FEvent);
                downHeapBubble(FEventPosition);
                upHeapBubble(FEventPosition);
            }
            cout << msg << endl;
            return;
        }
        Event *SEvent = A[1].value;
        UpdateKey(A[1].value);
        downHeapBubble(1);

        int SEventPosition = 0;
        third = A[1].key;
        Event *TEvent = A[1].value;
        try
        {
            Third = A[1].A->removeMax();
            if (third != 0)
            {
                Third->PrintForTOP3();
                cout << A[1].value->eventID << ", " << A[1].value->eventName << ", " << third << endl;
            }
        }
        catch (const char *msg) // If removeMax throws an error
        {
            PO = 1;
            FEventPosition = SearchInHeap(FEvent);
            if (FEventPosition > 0)
            {
                UpdateKey(FEvent);
                downHeapBubble(FEventPosition);
                upHeapBubble(FEventPosition);
                A[FEventPosition].A->insert(first, First);
                SEventPosition = SearchInHeap(SEvent);
                if (SEventPosition > 0)
                {
                    A[SEventPosition].A->insert(second, Second);
                    UpdateKey(SEvent);
                    downHeapBubble(SEventPosition);
                    upHeapBubble(SEventPosition);
                }
            }
            cout << msg << endl;
            return;
        }
        if (PO == 0) // Error was never caught (i.e. 3 participants exist)
        {
            try
            {
                A[1].A->insert(third, Third);
            }
            catch (const char *msg)
            {
                cout << msg << endl;
            }
            UpdateKey(TEvent);
            downHeapBubble(1);

            FEventPosition = SearchInHeap(FEvent);
            if (FEventPosition > 0)
            {

                A[FEventPosition].A->insert(first, First);
                UpdateKey(FEvent);
                downHeapBubble(FEventPosition);
                upHeapBubble(FEventPosition);
                SEventPosition = SearchInHeap(SEvent);
                if (SEventPosition > 0)
                {
                    A[SEventPosition].A->insert(second, Second);

                    UpdateKey(SEvent);
                    downHeapBubble(SEventPosition);
                    upHeapBubble(SEventPosition);
                }
            }
        }
    }
};
