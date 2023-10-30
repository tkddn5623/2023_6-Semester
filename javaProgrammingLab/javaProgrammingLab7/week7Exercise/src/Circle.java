public class Circle extends TwoDimensionalShape {
    private static final String CLASS_NAME = "Circle";

    Circle(String name, double r) {
        super(name, r, r);
    }

    public static String getClassName() {
        return CLASS_NAME;
    }

    public double getRadius() {
        return getDimension1();
    }

    public void setRadius(double radius) {
        setDimension1(radius);
        setDimension2(radius);
    }

    public double getDiameter() {
        return getDimension1() * 2;
    }

    public void setDiameter(double diameter) {
        setDimension1(diameter / 2);
        setDimension2(diameter / 2);
    }

    public double getArea() {
        return 3.141592653589793 * getDimension1() * getDimension1();
    }
}
