import java.io.*;
import java.lang.Integer;
@SuppressWarnings("unused")
class Entry{
	public int key;//This denotes the key of the entry stored at the node
	public Participant value;//This denotes the value of the entry stored at the node 
	public Entry(int k, Participant v){
		key = k;
		value = v;
	}
}
public class EventMaxHeap{
	final int MAX_HEAP_SIZE = (int) 1e6;//This indicates the maximum size the heap can grow into.
	public Entry[] A;//This is the array of references to entries
	public int size;//This is the number of current entries in the heap
	//This is the initialization method for the array based max-heap implementation.
	public EventMaxHeap(){
		size = 0;
		A = new Entry[MAX_HEAP_SIZE+1];
	}
	//This is the initialization method that takes as input an array of entries
	//and performs the bottom up heap construction
	/*    public MinHeapArray(Entry B[], int n){

        size = n;
        A = B;
        bottomUpHeapConstruction();
    }


    //This method implements the bottom-up heap construction.
    public void bottomUpHeapConstruction(){
        //To be written as part of Homework.
    }
	 */
	//This method swaps the key-value pairs stored at given indices in the array A
	public void swapVals(int p, int q){
		Participant temp1 = A[p].value;
		int temp2 = A[p].key;
		A[p].key = A[q].key;
		A[p].value = A[q].value;
		A[q].key = temp2;
		A[q].value = temp1;
	}
	//This is the max() method that returns the maximum element in the heap
	public Participant max(){
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
	//This method implements the down heap bubble
	public void downHeapBubble(int i){
		//To be written as part of homework
		/*while(A[i].key<Math.max(A[Math.min(2*i, size)].key, A[Math.min(2*i+1, size)].key)&&i<=size/2){
			int great;
			if(A[Math.min(2*i, size)].key>A[Math.min(2*i+1, size)].key)great=Math.min(2*i, size);
			else{great=Math.min(2*i+1, size);}
			swapVals(i,great);
			i=great;
		}
		return;*/
		int k=0;
		/*System.out.println(size);*/
		if(2*i<=size){
			if(A[i].key<A[2*i].key)k=1;
		}
		if(2*i+1<=size){
			if(A[i].key<A[2*i+1].key)k=1;
		}
		if(k==1){
			
			int greatestbit;
			if(A[2*i].key>A[2*i+1].key)greatestbit=2*i;
			else greatestbit=2*i+1;
			swapVals(i,greatestbit);
			downHeapBubble(greatestbit);
		}
	}
	//This method is used to insert a new entry into the max heap
	public void insert(int k, Participant v) throws Exception{
		int Position=SearchInHeap1(v);
		if(Position>0){System.out.println("Exception");throw new Exception();}
		//else{
		Entry E = new Entry(k, v);
		A[++size] = E;
		upHeapBubble(size);
		//}
	}
	//This method implements the removeMax() operation
	public Participant removeMax()throws Exception{
		if(size==0){/*System.out.println("Exception")*/;throw new Exception();}
		Participant result = A[1].value;
		if(size==1){A[1].key=(int) 0;size--;return (result);}
		//Copy the entry at index "size" to the root
		A[1].key = A[size].key; A[1].value = A[size].value;
		size--;
		downHeapBubble(1);
		return(result);
	}
	//This method just prints the array storing the heap
	//This may be used for debugging
	public void removeparticipant(Participant P){
		int position=0;
		try {
			position = SearchInHeap(P);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			//e.printStackTrace();
		}
		if(position>0){
			/*A[position].key = A[size].key; A[position].value = A[size].value;
			size--;*/swapVals(position,size);
			size--;
			downHeapBubble(position);
		}
	}
	public int SearchInHeap(Participant P)throws Exception {
		// TODO Auto-generated method stub
		for(int i=1;i<=size;i++){
			if(P.participantID.equals(A[i].value.participantID))return i;
		}
		System.out.println("Exception");
		throw new Exception();
	}
	public int SearchInHeap1(Participant P){
		// TODO Auto-generated method stub
		for(int i=1;i<=size;i++){
			if(P.participantID.equals(A[i].value.participantID))return i;
		}
		return 0;
	}
	public void printArray(){
		for(int i=1;i<=size;++i){
			System.out.print("(" + A[i].key + ", " + A[i].value.participantID + "), ");
		}
		System.out.println("");
	}
	public void UpdateScore(int key, Participant P) throws Exception{
		/*removeparticipant(P);
		insert(key,P);*/
		int Position=SearchInHeap(P);
		//System.out.println(Position);
		//System.out.println(Position);
		A[Position].key=key;
		downHeapBubble(Position);
		upHeapBubble(Position);
	}
	public void TOP3INEVENT(EventMaxHeap temp){
		// TODO Auto-generated method stub
		int first=temp.A[1].key;int PO=0;
		Participant First=new Participant("dummy");
		try {
			First = temp.removeMax();
			if(first!=0){First.Print();System.out.println(first);}
		} catch (Exception e) {
			PO=1;return;
			// TODO Auto-generated catch block
			// e.printStackTrace();
		}
		//First Participant Found
		Participant Second=new Participant("dummy"),Third=new Participant("dummy1");
		int second=0,third=0;
		second=temp.A[1].key;
		try {
			Second=temp.removeMax();
			if(second!=0){Second.Print();System.out.println(second);}
		} catch (Exception e) {
			PO=1;
			try {
				temp.insert(first, First);
			} catch (Exception e1) {
				// TODO Auto-generated catch block
				// e1.printStackTrace();
			}return;
			// TODO Auto-generated catch block
			// e.printStackTrace();
		}
		third=temp.A[1].key;
		try {
			Third=temp.removeMax();
			if(third!=0){Third.Print();System.out.println(third);}
		} catch (Exception e) {
			PO=1;
			try {
				temp.insert(first, First);
				temp.insert(second, Second);return;
			} catch (Exception e1) {
				// TODO Auto-generated catch block
				// e1.printStackTrace();
			}
			// TODO Auto-generated catch block
			// e.printStackTrace();
		}
		if(PO==0){
		try {
			temp.insert(first, First);
			temp.insert(second, Second);
			temp.insert(third, Third);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			// e.printStackTrace();
		}
		}
	}
	/*public static void main(String[] args) throws Exception{
		// TODO Auto-generated method stub
		EventMaxHeap B=new EventMaxHeap();
		Participant P1=new Participant("how","are","you");
		B.insert(5, P1);
		B.printArray();
		Participant P=new Participant("are");
		B.insert(2, P);
		Participant P2=new Participant("arey");
		B.insert(2, P2);
		P=new Participant("arey1");
		B.insert(3, P);
		System.out.println(B.max().participantID);
		B.UpdateScore(0, P1);

		B.removeparticipant(P2);
		B.printArray();
		//System.out.println(B.A[1].key);
	}*/
	/*public Participant removeMax1() {
		// TODO Auto-generated method stub
		Participant result = A[1].value;
		//Copy the entry at index "size" to the root
		A[1].key = A[size].key; A[1].value = A[size].value;
		//size--;
		downHeapBubble(1);
		return(result);
		//return null;
	}*/
/*	private Participant removeMax1() throws Exception {
		// TODO Auto-generated method stub
		if(size==0)throw new Exception();
		Participant result = A[1].value;
		//Copy the entry at index "size" to the root
		A[1].key = A[size].key; A[1].value = A[size].value;
		size--;
		downHeapBubble(1);
		return(result);
	}*/
}