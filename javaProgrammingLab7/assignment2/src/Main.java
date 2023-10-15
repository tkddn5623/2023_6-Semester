import java.io.*;
import java.util.Scanner;

public class Main {
    static private String[] productName = {"MacBook", "iPhone", "AirPods"};

    public static void main(String[] args) throws IOException {
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        Scanner scn = new Scanner(System.in);
        while (true) {
            bw.write("==== Welcome Apple Korea ====\n");
            bw.write("What do you want to buy?\n");
            for (int i = 0; i < productName.length; i++) {
                bw.write("Choose " + (i + 1) + " for " + productName[i] + "\n");
            }
            bw.write("Choose 0 for Exit\n");
            bw.write("Please enter your choice: ");
            bw.flush();
            int choice = scn.nextInt();
            bw.write("=============================\n");
            if (choice == 0) break;
        }
        scn.close();
    }
}