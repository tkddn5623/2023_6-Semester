public class Rectangle extends TwoDimensionalShape {
    private static final String CLASS_NAME = "Rectangle";

    Rectangle(String name, double width, double height) {
        super(name, width, height);
    }

    public static String getClassName() {
        return CLASS_NAME;
    }

    public double getWidth() {
        return getDimension1();
    }

    public void setWidth(double width) {
        setDimension1(width);
    }

    public double getHeight() {
        return getDimension2();
    }

    public void setHeight(double height) {
        setDimension2(height);
    }

    public double getArea() {
        return getDimension1() * getDimension2();
    }
}
