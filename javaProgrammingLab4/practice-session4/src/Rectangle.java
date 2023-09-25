public class Rectangle {
    private double height;
    private double width;

    Rectangle() {
        setHeight(1d);
        setWidth(1d);
    }

    Rectangle(double height, double width) {
        if (verify(height)) setHeight(height);
        else setHeight(1d);
        if (verify(width)) setWidth(width);
        else setWidth(1d);
    }

    private boolean verify(double length) {
        if (length < 0d || length > 20d) {
            System.err.println("Invalid input");
            return false;
        } else return true;
    }

    public void setHeight(double height) {
        if (!verify(height)) return;
        this.height = height;
    }

    public void setWidth(double width) {
        if (!verify(width)) return;
        this.width = width;
    }
    public double getPerimeter() {
        return (height + width) * 2d;
    }

    public double getArea() {
        return height * width;
    }
}
