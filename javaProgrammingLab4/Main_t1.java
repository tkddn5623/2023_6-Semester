import java.io.*;
import java.util.StringTokenizer;

public class Main {
    public static double solveA(double bal, double per, int year) {
        double weight = 1d + 0.01 * per;
        while (year-- > 0){
            bal *= weight;
        }
        return bal;
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String arg_name;
        double arg_bal, arg_per;
        int arg_year;
		
		// Input
        System.out.print("Please, enter following information:\n" +
                         "Your name: ");
        arg_name = br.readLine();
        System.out.print("Initial Balance: ");
        arg_bal = Double.parseDouble(br.readLine());
        System.out.print("Percentage: ");
        arg_per = Double.parseDouble(br.readLine());
        System.out.print("Number of years: ");
        arg_year = Integer.parseInt(br.readLine());
		
		// Output
        System.out.println("User name: " + arg_name);
        System.out.println("Percentage: " + arg_per);
        System.out.println("Your balance (after " + arg_year + " years): " + solveA(arg_bal, arg_per, arg_year));
    }
}