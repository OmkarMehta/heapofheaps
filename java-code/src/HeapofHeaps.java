class Entry1{
	public int key;
	public Event value;
	public EventMaxHeap A;
	public Entry1(int k, Event v ){
		key = k;
		value = v;
	}}
public class HeapofHeaps{
	public int MAX_HEAP_SIZE1 = 1000;
	public Entry1[] A;
	public int size;
	public HeapofHeaps(){
		size=0;
		A=new Entry1[MAX_HEAP_SIZE1+1];
	}
	public void swapVals(int p, int q){
		Event temp1 = A[p].value;
		int temp2 = A[p].key;
		EventMaxHeap temp3=A[p].A;
		A[p].key = A[q].key;
		A[p].value = A[q].value;
		A[p].A=A[q].A;
		A[q].key = temp2;
		A[q].value = temp1;
		A[q].A=temp3;
	}
	//This is the max() method that returns the maximum element in the heap of heaps
	public Event max(){
		return(A[1].value);
	}
	//This method returns whether the heap is empty or not
	public boolean isEmpty(){
		if(size == 0)return(true);
		else return(false);
	}
	//This method implements the up-heap bubble
	public void upHeapBubble(int i){
		//To be written as part of homework
		if (i==1||i==0){return;}
		while(A[i].key>A[i/2].key&&i>1){
			swapVals(i, i/2);
			i=i/2;
			if (i==1||i==0){return;}
		}
		return;
	}
	public void downHeapBubble(int i){
		int k=0;
		if(2*i<=size){
			if(A[i].key<A[2*i].key)k=1;
		}
		if(2*i+1<=size){
			if(A[i].key<A[2*i+1].key)k=1;
		}
		if(k==1){
			int greatestbit=0;
			if(2*i+1<=size){
				if(A[2*i+1].key>A[2*i].key)greatestbit=2*i+1;
				else greatestbit=2*i;
			}
			else greatestbit=2*i;
			swapVals(i,greatestbit);
			downHeapBubble(greatestbit);
		}
	}
	public void insert(int k, Event v) throws Exception{
		int position=SearchInHeap1(v);
		if(position>0){System.out.println("Exception");throw new Exception();}
		EventMaxHeap O=new EventMaxHeap();
		Participant P=new Participant("Dummy");
		try {
			O.insert(0, P);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		O.removeparticipant(P);
		Entry1 E = new Entry1(k, v);
		A[++size] = E;
		A[size].A=O;
		/*A[size].A.EventMaxHeap();*/
		upHeapBubble(size);
	}
	public void UpdateKey(Event E){
		int Position=0;
		try {
			Position = SearchInHeap(E);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
		}
		A[Position].key=A[Position].A.A[1].key;
	}
	public Event removeMax(){
		Event result = A[1].value;
		if(size==1){A[1].key=(int) 0;size--;return (result);}
		//Copy the entry at index "size" to the root
		A[1].key = A[size].key; A[1].value = A[size].value;
		size--;
		downHeapBubble(1);
		return(result);
	}
	public void removeevent(Event P){
		int position=0;
		try {
			position = SearchInHeap(P);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
		}
		if(position>0){
			if(size==1){A[1].key=0;size--;return;}
			/*A[position].key = A[size].key; A[position].value = A[size].value;*/
			swapVals(position,size);
			size--;
			downHeapBubble(position);
		}
	}
	public int SearchInHeap(Event P)throws Exception {
		// TODO Auto-generated method stub
		for(int i=1;i<=size;i++){
			if(P.eventID.equals(A[i].value.eventID))return i;
		}
		System.out.println("Exception");
		throw new Exception();
	}
	public int SearchInHeap1(Event P){
		// TODO Auto-generated method stub
		for(int i=1;i<=size;i++){
			if(P.eventID.equals(A[i].value.eventID))return i;
		}
		return 0;
	}
	public void DeleteEventParticipant(Event E1,Participant P1){
		//Search for Event in Heap
		int EventPosition=0;
		try {
			EventPosition=SearchInHeap(E1);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
		}
		if(EventPosition>0){
			//EventMaxHeap a2=A[EventPosition].A;
			A[EventPosition].A.removeparticipant(P1);
			UpdateKey(E1);
			downHeapBubble(EventPosition);
		}
	}
	public void RemoveParticipant(Participant P){
		for(int i=1;i<=size;i++){
			/*int position=A[i].A.SearchInHeap(P);*/
			A[i].A.removeparticipant(P);
		}
	}
	public void printArray(){
		for(int i=1;i<=size;++i){
			System.out.println("(" + A[i].key + ", " + A[i].value.eventID + ", "+A[i].value.eventName+", "+A[i].value.eventDescription+"),");
		}
		//System.out.println("");
	}
	public void TOP3(){
		int first=A[1].key,PO=0;
		Participant First=new Participant("dummy");
		Event FEvent=A[1].value;
		try {
			First=A[1].A.removeMax(); UpdateKey(A[1].value);
			if(first!=0){First.Print();System.out.println(A[1].value.eventID+", "+A[1].value.eventName+", "+first);}
		} catch (Exception e) {
			PO=1;return;
			// TODO Auto-generated catch block
			// e.printStackTrace();
		}
		//UpdateKey(A[1].value);
		//System.out.println(A[1].value.eventID);
		downHeapBubble(1);
		int FEventPosition=0;
		Participant Second=new Participant("dummy"),Third=new Participant("dummy1");
		int second=0,third=0;
		second=A[1].key;
		try {
			Second=A[1].A.removeMax();
			if(second!=0){Second.Print();System.out.println(A[1].value.eventID+", "+A[1].value.eventName+", "+second);}
		} catch (Exception e) {
			PO=1;/*System.out.println("OMG Bro!");*/
			try {
				FEventPosition=SearchInHeap(FEvent);
			} catch (Exception e1) {
				// TODO Auto-generated catch block
				//e1.printStackTrace();
			}
			try {
				A[FEventPosition].A.insert(first, First);
			} catch (Exception e1) {
				// TODO Auto-generated catch block
				// e1.printStackTrace();
			}
			UpdateKey(FEvent);
			downHeapBubble(FEventPosition);
			upHeapBubble(FEventPosition);return;
			// TODO Auto-generated catch block
			// e.printStackTrace();
		}
		Event SEvent=A[1].value;
		UpdateKey(A[1].value);
		downHeapBubble(1);
		int SEventPosition=0;
		third=A[1].key;
		Event TEvent=A[1].value;
		try {
			Third=A[1].A.removeMax();
			if(third!=0){Third.Print();System.out.println(A[1].value.eventID+", "+A[1].value.eventName+", "+third);}
		} catch (Exception e) {
			PO=1;
			try {
				FEventPosition=SearchInHeap(FEvent);
				UpdateKey(FEvent);
				downHeapBubble(FEventPosition);
				upHeapBubble(FEventPosition);
			} catch (Exception e1) {
				// TODO Auto-generated catch block
				//e1.printStackTrace();
			}
			try {
				A[FEventPosition].A.insert(first, First);
			} catch (Exception e2) {
				// TODO Auto-generated catch block
				// e2.printStackTrace();
			}
			try {
				SEventPosition=SearchInHeap(SEvent);
			} catch (Exception e1) {
				// TODO Auto-generated catch block
				// e1.printStackTrace();
			}
			try {
				A[SEventPosition].A.insert(second,Second);
			} catch (Exception e1) {
				// TODO Auto-generated catch block
				// e1.printStackTrace();
			}
			UpdateKey(SEvent);
			downHeapBubble(SEventPosition);
			upHeapBubble(SEventPosition);return;
			// TODO Auto-generated catch block
			// e.printStackTrace();
		}
		if(PO==0){
			try {
				A[1].A.insert(third, Third);
			} catch (Exception e1) {
				// TODO Auto-generated catch block
				// e1.printStackTrace();
			}
			UpdateKey(TEvent);
			downHeapBubble(1);
			try {
				FEventPosition=SearchInHeap(FEvent);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				// e.printStackTrace();
			}
			try {
				A[FEventPosition].A.insert(first,First);
			} catch (Exception e1) {
				// TODO Auto-generated catch block
				// e1.printStackTrace();
			}
			UpdateKey(FEvent);
			downHeapBubble(FEventPosition);
			upHeapBubble(FEventPosition);
			try {
				SEventPosition=SearchInHeap(SEvent);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				// e.printStackTrace();
			}
			try {
				A[SEventPosition].A.insert(second,Second);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				// e.printStackTrace();
			}
			UpdateKey(SEvent);
			downHeapBubble(SEventPosition);
			upHeapBubble(SEventPosition);
		}
	}
	/*	public static void main(String[] args) throws Exception{
		// TODO Auto-generated method stub
		HeapofHeaps B=new HeapofHeaps();
		Event P1=new Event("how","are","you");
		B.insert(5, P1);
		B.printArray();
		Event P=new Event("are");
		B.insert(2, P);
		Event P2=new Event("arey");
		B.insert(2, P2);
		//P=new Event("arey1");
		B.insert(3, P);
		B.printArray();
		System.out.println(B.max().eventID);
		B.removeevent(P2);
		B.printArray();
		//System.out.println(B.A[1].key);
	}*/
}