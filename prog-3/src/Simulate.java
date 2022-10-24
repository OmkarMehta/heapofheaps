import java.io.*;
public class Simulate {
	public static Event[] E= new Event[1000];
	public static Participant[] P=new Participant[(int) 1e6];
	public static HeapofHeaps A=new HeapofHeaps();
	public static int EventCount=0;
	public static int ParticipantCount=0;
	public static void main(String[] args) throws NumberFormatException, Exception {
		// TODO Auto-generated method stub	
		BufferedReader BR = new BufferedReader(new FileReader("Query.txt"));
		String S = BR.readLine();
		while(S!=null){
			String[] L = S.split(" ");
			//L[0]="Hii";
			//System.out.println(L[0]);
			Analyze(L,S);
			/*System.out.println("Done");*/
			S = BR.readLine();
		}
		BR.close();
/*		System.out.println("After Performing All Queries");
		for(int i=1;i<=EventCount;i++){
			for(int j=1;j<=A.A[i].A.size;j++){
				System.out.println("Participants in Event:"+A.A[i].value.eventID+", "+A.A[i].A.A[j].value.participantID+" With Score: "+A.A[i].A.A[j].key);
			}
		}
		for(int i=1;i<=EventCount;i++){
			System.out.println("Keys are: "+"Event:"+A.A[i].value.eventID+" , "+A.A[i].key);
		}*/
	}public Simulate() {
		// TODO Auto-generated constructor stub
	}
	
	private static void Analyze(String[] L,String S){
		// TODO Auto-generated method stub
		if(L[0].equals("ADD")){
			if(L[1].equals("PARTICIPANT")==true){
				String Rest=S.substring("ADD PARTICIPANT ".length());
				String[] Parameters=Rest.split(", ");
				//Participant ID,Participant Name, Participant Description
				P[++ParticipantCount]=new Participant(Parameters[0],Parameters[1],Parameters[2]);
				/*ParticipantCount++;*/
			}//Add Participant Working, Checked
			else if(L[1].equals("EVENT")){
				String Rest=S.substring("ADD EVENT ".length());
				String[] Parameters=Rest.split(", ");
				//Event ID, Event Name, Event Description
				Event event=new Event(Parameters[0],Parameters[1],Parameters[2]);
				try {
					A.insert(0, event);
					//System.out.println("Ban gaya");
				} catch (Exception e) {
					EventCount--;
					// TODO Auto-generated catch block
					//e.printStackTrace();System.out.println("Problem In Insert Event");
				}
				EventCount++;
			}//Add Event Working, Checked
			else{
				String Rest=S.substring("ADD ".length());
				String[] Parameters=Rest.split(", ");
				//Participant ID,Event ID
				int ParticipantPosition=0;
				try {
					ParticipantPosition = SearchParticipant(Parameters[0]);
				} catch (Exception e1) {
					// TODO Auto-generated catch block
					//e1.printStackTrace();
				}
				if(ParticipantPosition>0){
					Participant P3=P[ParticipantPosition];
					Event E=new Event(Parameters[1]);
					int EventPosition=0;
					try {
						EventPosition = A.SearchInHeap(E);
					} catch (Exception e1) {
						// TODO Auto-generated catch block
						//e1.printStackTrace();
					}
					if(EventPosition>0){
						try {
							A.A[EventPosition].A.insert(0, P3);
						} catch (Exception e) {
							// TODO Auto-generated catch block
							//e.printStackTrace();System.out.println("Participent or Event Not Registered with System");System.exit(0);
						}
					}
				}
			}//ADD Working, Checked
		}
		//Working till ADD
		/*System.out.println("After Adding All Participants");
		for(int i=1;i<=EventCount;i++){
			for(int j=1;j<=A.A[i].A.size;j++){
				System.out.println("Participants in Event:"+A.A[i].value.eventID+", "+A.A[i].A.A[j].value.participantID+" With Score: "+A.A[i].A.A[j].key);
			}
		}*/
		if(L[0].equals("DELETE")){
			if(L[1].equals("PARTICIPANT")){
				String Rest=S.substring("DELETE PARTICIPANT ".length());
				String[] Parameters=Rest.split(", ");
				//System.out.println("Banana Hai");
				//Participant ID
				int ParticipantPosition=0;
				try {
					ParticipantPosition=SearchParticipant(Parameters[0]);
					//System.out.println(ParticipantPosition);
				} catch (Exception e) {
					// TODO Auto-generated catch block
					// e.printStackTrace();
				}
				if(ParticipantPosition>0){
					Participant P1=P[ParticipantPosition];
					P[ParticipantPosition]=P[ParticipantCount];
					ParticipantCount--;
					for(int i=1;i<=EventCount;i++){
						int ParticipantPosition1=0;
						ParticipantPosition1=A.A[i].A.SearchInHeap1(P1);
						if(ParticipantPosition1>0){
							A.A[i].A.removeparticipant(P1);
							A.UpdateKey(A.A[i].value);
							A.downHeapBubble(i);
							A.upHeapBubble(i);
						}
					}
				}
			}
			else if(L[1].equals("EVENT")){
				if(L[2].equals("PARTICIPANT")){
					String Rest=S.substring("DELETE EVENT PARTICIPANT ".length());
					String[] Parameters=Rest.split(", ");
					//System.out.println("Banana Hai");
					//Participant ID, Event ID
					int ParticipantPosition=0;
					try {
						ParticipantPosition = SearchParticipant(Parameters[0]);
					} catch (Exception e) {
						// TODO Auto-generated catch block
						//e.printStackTrace();
					}
					if(ParticipantPosition>0){
						Participant P1=P[ParticipantPosition];
						Event E1=new Event(Parameters[1]);
						A.DeleteEventParticipant(E1, P1);	
					}
				}
				else{
					String Rest=S.substring("DELETE EVENT ".length());
					String[] Parameters=Rest.split(", ");
					//System.out.println("Banana Hai");
					//Event ID
					Event E3=new Event(Parameters[0]);
					A.removeevent(E3);
					EventCount--;
				}
			}
		}
		else if(L[0].equals("TOP3")){
			if(L.length>1){
				if(L[1].equals("IN")&&L[2].equals("EVENT")){
					String Rest=S.substring("TOP3 IN EVENT ".length());
					String[] Parameters=Rest.split(", ");
					Event E=new Event(Parameters[0]);
					int EventPosition=0;
					try {
						EventPosition = A.SearchInHeap(E);
					} catch (Exception e) {
						// TODO Auto-generated catch block
						//e.printStackTrace();
					}
					//EventMaxHeap temp=A.A[EventPosition].A;
					try {
						A.A[EventPosition].A.TOP3INEVENT(A.A[EventPosition].A);
					} catch (Exception e) {
						// TODO Auto-generated catch block
						// e.printStackTrace();
					}
				}
			}
			else{
				//System.out.println("Banana Hai");
				//Give Top 3 from Heap of Heaps
				A.TOP3();
			}
		}
		else if(L[0].equals("UPDATE")){
			String Rest=S.substring("UPDATE SCORE ".length());
			String[] Parameters=Rest.split(", ");
			//System.out.println("Banana Hai");
			//Participant ID, Event ID, Updated Score
			//System.out.println(Parameters[0]+", "+Parameters[1]+", "+Parameters[2]);
			Event E=new Event(Parameters[1]);
			int EventPosition=0;
			try {
				EventPosition = A.SearchInHeap(E);
			} catch (Exception e) {
				// TODO Auto-generated catch block
				//e.printStackTrace();
			}
			if(EventPosition>0){
				// ("EventFound!! At Position; "+EventPosition);
				Participant P4=new Participant(Parameters[0]);
				try {
					A.A[EventPosition].A.UpdateScore((Integer.parseInt(Parameters[2])), P4);
				} catch (NumberFormatException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (Exception e) {
					// TODO Auto-generated catch block
					//e.printStackTrace();
				}
				A.UpdateKey(E);
				A.downHeapBubble(EventPosition);
				A.upHeapBubble(EventPosition);
			}
		}
		
		return ;
	}
	private static int SearchParticipant(String string) throws Exception {
		// TODO Auto-generated method stub
		for(int i=1;i<=ParticipantCount;i++){
			if(P[i].participantID.equals(string)){
				return i;
			}
		}
		System.out.println("Exception");
		throw new Exception();
	}
}