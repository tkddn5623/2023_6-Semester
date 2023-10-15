import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    static private final String[] productName = {"MacBook", "iPhone", "AirPods"};

    public static void main(String[] args) throws IOException {
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        Scanner scn = new Scanner(System.in);
        List<Product> products = new ArrayList<Product>();
        int choice = -1;
        do {
            bw.write("==== Welcome Apple Korea ====\n");
            bw.write("What do you want to buy?\n");
            for (int i = 0; i < productName.length; i++) {
                bw.write("Choose " + (i + 1) + " for " + productName[i] + "\n");
            }
            bw.write("Choose 0 for Exit\n");
            bw.write("Please enter your choice: ");
            bw.flush();
            do {
                choice = scn.nextInt();
            } while (choice < 0 || choice > 3);
            bw.write("=============================\n");
            bw.flush();
            if (choice == 0) {
                break;
            } else if (choice == 1) {
                products.add(new MacBook(scn));
            } else if (choice == 2) {
                products.add(new iPhone(scn));
            } else if (choice == 3) {
                products.add(new AirPods(scn));
            }
            bw.write("Do you want to purchase something else (Yes: 1, No: 0)");
            bw.flush();
            do {
                choice = scn.nextInt();
            } while (choice < 0 || choice > 1);
        } while (choice != 0);
        bw.write("Thank you for your purchase!\n");
        bw.close();
        scn.close();
    }
}