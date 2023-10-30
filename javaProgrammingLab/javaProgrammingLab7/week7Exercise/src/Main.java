// 2023 10 12 Thu
public class Main {
    public static void main(String[] args) {
        Circle cir1 = new Circle("Cir One", 3.0);
        Rectangle rec1 = new Rectangle("Rec One", 3.0, 4.0);
        Square sq1 = new Square("Square One", 6.0);

        System.out.printf("1.Circle [Radius = %.2f]\n", cir1.getRadius());
        System.out.printf("%s's area is %.2f, radius is %.2f, diameter is %.2f\n", cir1.getName(), cir1.getArea(), cir1.getRadius(), cir1.getDiameter());
        System.out.printf("2.Rectangle [Width = %.2f, Height]\n", rec1.getWidth(), rec1.getHeight());
        System.out.printf("%s's area is %.2f, width is %.2f, height is %.2f\n", rec1.getName(), rec1.getArea(), rec1.getWidth(), rec1.getHeight());
        System.out.printf("3.Square [Side= %.2f]\n", sq1.getSide());
        System.out.printf("%s's area is %.2f, side is %.2f\n", sq1.getName(), sq1.getArea(), sq1.getSide());

    }
}