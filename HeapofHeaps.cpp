using namespace std;

class Entry1{
public:
    int key;
    Event *value;
    EventMaxHeap *A;
    Entry1(int k, Event *v){
        key = k;
        value = v;
    }
};

class HeapofHeaps{
    public:
        int MAX_HEAP_SIZE1 = 1000;
        Entry1[] A;
        int size;
        HeapofHeaps(){
            A = new Entry1[MAX_HEAP_SIZE1+1];
            size = 0;
        }

        void swapVals(int p, int q) {
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
        Event max() {
            return A[1].value;
        }

        //This method returns whether the heap is empty or not
        bool isEmpty() {
            return size == 0;
        }

        // This method implements the up-heap bubble
        void upHeapBubble(int i) {
            if (i==1 || i==0) return;
            while(A[i].key > A[i/2].key && i>1) {
                swapVals(i, i/2);
                i = i/2;
                if (i==1 || i==0) return;
            }
            return;
        }

        // This method implements the down-heap bubble
        void downHeapBubble(int i) {
            int k=0;
            if(2*i <= size){
                if (A[i].key<A[2*i].key) {k=1;}
            }
            if(2*i+1 <= size){
                if (A[i].key<A[2*i+1].key) {k=1;}
            }
            if(k==1){
                int greatestbit=0;
                if(2*i+1<=size){
                    if(A[2*i+1].key>A[2*i].key){
                        greatestbit=2*i+1;
                    }
                    else{
                        greatestbit=2*i;
                    }
                } else {
                    greatestbit=2*i;
                }
                swapVals(i, greatestbit);
                downHeapBubble(greatestbit);
            }
        }

        // This method inserts a new element into the heap of heaps with exception handling
        void insert(int k, Event *v) {
            int position = SearchInHeap1(v);
            if(position>0){
                // throw exception
                cout << "Event already exists in the heap of heaps" << endl;
            }
            EventMaxHeap *O = new EventMaxHeap();
            Participant * P = new Participant("Dummy");
            try{
                O -> insert(k, P);
            } catch (const char* msg) {
                cout << msg << endl;
            }
            O.removeparticipant(P);
            Entry1 *E = new Entry1(k, v);
            A[++size] = E;
            A[size].A = O;
            upHeapBubble(size);
        }

        // This method updates the key of an element in the heap of heaps
        void UpdateKey(Event *E) {
            int Position=0;
            try {
                Position = SearchInHeap(E);
            } catch (const char* msg) {
                cout << msg << endl;
            }
            A[Position].key = A[Position].A.A[1].key;
        }

        // This method removes the maximum element from the heap of heaps
        Event *removeMax() {
            Event *result = A[1].value;
            if(size==1){
                A[1].key = (int) 0;
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
        void removeevent(Event *P){
            int position = 0;
            try {
                position = SearchInHeap(P);
            } catch (const char* msg) {
                cout << msg << endl;
            }
            if(position>0){
                if(size==1){
                    A[1].key = (int) 0;
                    size--;
                    return;
                }
                swapVals(position, size);
                size--;
                downHeapBubble(position);
            }
        }

        int SearchInHeap(Event *P){
            for(int i=1; i<=size; i++){
                if(A[i].value.eventID == P.eventID){
                    return i;
                }

            }
            throw "Event not found in the heap of heaps";
            return -1;
        }

        int SearchInHeap1(Event *P){
            for(int i=1; i<=size; i++){
                if(A[i].value.eventID == P.eventID){
                    return i;
                }

            }
            return -1;
        }

        
}
