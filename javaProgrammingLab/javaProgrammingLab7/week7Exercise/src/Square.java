public class Square extends Rectangle {
    private static final String CLASS_NAME = "Square";

    Square(String name, double side) {
        super(name, side, side);
    }

    public static String getClassName() {
        return CLASS_NAME;
    }

    public double getSide() {
        return getDimension1();
    }

    public void setSide(double side) {
        setDimension1(side);
        setDimension2(side);
    }

}
