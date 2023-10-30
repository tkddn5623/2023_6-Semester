import java.io.*;

public class Main {
    public static long solveB(int a) {
        int quo = a / 7, rem = a % 7;
        return (((long)quo * (quo + 1)) / 2 * 7) + (quo + 1) * rem;
    }
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Enter the number of days: ");
        int day = Integer.parseInt(br.readLine()); // Input
        long answer = solveB(day);                 // Solve taskB
        System.out.println("Total Frank's saving (after " + day + "): " + answer); // Output
    }
}