
public class Program {

	public static void main(String[] args) {
		//Ball football = new Ball();
		Ball football;
		football = new Ball("black");
		
		System.out.println(football.color);
		System.out.println(football.size);
		System.out.println(football.shape);
		//good practice
		
		football.Set_Ball_Color("Black");
		football.Set_Ball_Shape("somthing");
		
		Ball tennis = new Ball();
		
		tennis.color="yellow";
		tennis.shape="circle";
		tennis.size = 9.12f; 
	}

}
