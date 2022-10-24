public class Event {
	String eventID;
	String eventName;
	String eventDescription;
	//Participant[] X;
	public Event(String x,String y,String z){
		//Create a new event
		eventID=x;
		eventName=y;
		eventDescription=z;
	}
	public Event(String x){
		eventID=x;
		eventName="Default";
		eventDescription="Default";
	}
}