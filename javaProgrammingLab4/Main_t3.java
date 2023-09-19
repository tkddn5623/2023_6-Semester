import java.io.*;
import java.util.Random;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));
        Random random = new Random(System.currentTimeMillis());
        String[] feedback = { // Array of feedbacks
                "Try again.",
                "Very bad.",
                "Not Bad.",
                "Good.",
                "Very good!",
                "Excellent!",
        };
        int score = 0;
        for (int i = 1; i <= 5; i++) {
            bw.write("Question " + i + " - Calculate the addition (");
            int a = random.nextInt(50);
            int b = random.nextInt(50);
            int c;
            bw.write(a + " + " + b + "): ");
            bw.flush();                          // BufferedWriter flush
            c = Integer.parseInt(br.readLine()); // Input
            if (a + b == c) score++;             // If a + b == c, count up the score
        }
        System.out.println("Number of correct answer: " + score + '\n' + feedback[score]);

    }
}