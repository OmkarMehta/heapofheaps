public class Participant {
	String participantID;
	String participantName;
	String universityName;
	public Participant(String x, String y, String z){
		participantID=x;
		participantName=y;
		universityName=z;
	}
	public Participant(String x){
		participantID=x;
		participantName="Default";
		universityName="Default";
	}
	public void Print(){
		System.out.print(participantID+", "+participantName+", "+universityName+", ");
	}
}