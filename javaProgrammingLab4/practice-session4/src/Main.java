import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        Rectangle rectangle = new Rectangle();
        while (true) {
            int arg;
            double height, width;
            System.out.println("1. Set Height\n" +
                    "2. Set Width\n" +
                    "3. Exit");
            arg = Integer.parseInt(br.readLine());
            if (arg == 1) {
                height = Double.parseDouble(br.readLine());
                rectangle.setHeight(height);
            } else if (arg == 2) {
                width = Double.parseDouble(br.readLine());
                rectangle.setWidth(width);
            } else if (arg == 3) {
                break;
            }

        }
    }
}