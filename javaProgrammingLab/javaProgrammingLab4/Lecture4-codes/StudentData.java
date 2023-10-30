
public class StudentData {

	private String StudentName;
	private int StudentID;
	private int StudentAge;
	private static String college = "";
	
	public static void SetCollege(String College) {
		college = College;
		
	}
	
	
	public StudentData() {
		StudentName = "None";
		StudentID = 1000;
		StudentAge = 0;
		
	}


	public StudentData(String studentName, int studentID, int studentAge) {
		 
		StudentName = studentName;
		StudentID = studentID;
		StudentAge = studentAge;
	}


	public StudentData(String studentName, int studentAge) {


		StudentName = studentName;
		StudentID = 0;
		StudentAge = studentAge;
	}


	public String getStudentName() {
		return StudentName;
	}


	public void setStudentName(String studentName) {
		StudentName = studentName;
	}


	public int getStudentID() {
		return StudentID;
	}


	public void setStudentID(int studentID) {
		StudentID = studentID;
	}


	public int getStudentAge() {
		return StudentAge;
	}


	public void setStudentAge(int studentAge) {
		StudentAge = studentAge;
	}
	
		
	// create toString method
	
	public String toString() {
		String info = "";
		
		info = info + this.StudentName + "  \n"
				    + this.StudentID + " \n " + 
				    + this.StudentAge + "\n" +
				    college +  "\n" +
				    "This info is from toString() method";
		
		
		return info;
		
	}
	
	
	
	
}
