import java.util.Scanner;

public class MacBook extends Product {
    static private final String PRODUCT_NAME = "MacBook";
    private String size;
    private int sizePrice;
    private String color;
    private int colorPrice;
    private String memory;
    private int memoryPrice;

    MacBook(Scanner scn) {
        super(1000);
        getUserSelection(scn);
        setTotalCost(calculateCost());
        System.out.println("====== check ======");
        System.out.println("Model (" + getModel() + ") ------ +$" + getModelPrice());
        System.out.println("Size (" + getSize() + ") ------ +$" + getSizePrice());
        System.out.println("Color (" + getColor() + ") ------ +$" + getColorPrice());
        System.out.println("Memory (" + getMemory() + ") ------ +$" + getMemoryPrice());
        System.out.println("Total cost for one " + PRODUCT_NAME + ": $" + getTotalCost());
        System.out.println("Total cost (quantity x " + getQuantity() + "): $" + getTotalCost() * getQuantity());
    }

    public void getUserSelection(Scanner scn) {
        System.out.println("Base cost of the " + PRODUCT_NAME + ": " + getBasePrice());
        System.out.println("Which model do you want (Air or Pro) ");
        while (true) {
            setModel(scn.nextLine());
            if (getModel().equals("Air")) {
                setModelPrice(0);
                break;
            } else if (getModel().equals("Pro")) {
                setModelPrice(200);
                break;
            }
        }
        System.out.println("Which size do you want (13 or 14 or 16) ");
        label1:
        while (true) {
            setSize(scn.nextLine());
            switch (getSize()) {
                case "13":
                    setColorPrice(0);
                    break label1;
                case "14":
                    setColorPrice(20);
                    break label1;
                case "16":
                    setColorPrice(10);
                    break label1;
            }
        }
        System.out.println("Which color do you want (base or Gold or Silver) ");
        label2:
        while (true) {
            setColor(scn.nextLine());
            switch (getColor()) {
                case "base":
                    setColorPrice(0);
                    break label2;
                case "Gold":
                    setColorPrice(20);
                    break label2;
                case "Silver":
                    setColorPrice(10);
                    break label2;
            }
        }
        System.out.println("Which memory do you want (64 or 128 or 256 or 512) ");
        label3:
        while (true) {
            setMemory(scn.nextLine());
            switch (getMemory()) {
                case "64":
                    setMemoryPrice(0);
                    break label3;
                case "128":
                    setMemoryPrice(100);
                    break label3;
                case "256":
                    setMemoryPrice(200);
                    break label3;
                case "512":
                    setMemoryPrice(300);
                    break label3;
            }
        }
        System.out.print("How many do you want buy: ");
        setQuantity(scn.nextInt());
    }

    public int calculateCost() {
        return getBasePrice() + getModelPrice() + getColorPrice() + getMemoryPrice();
    }

    public void setSize(String size) {
        this.size = size;
    }

    public String getSize() {
        return size;
    }

    public void setSizePrice(int sizePrice) {
        this.sizePrice = sizePrice;
    }

    public int getSizePrice() {
        return sizePrice;
    }

    public void setColor(String color) {
        this.color = color;
    }

    public String getColor() {
        return color;
    }

    public void setColorPrice(int colorPrice) {
        this.colorPrice = colorPrice;
    }

    public int getColorPrice() {
        return colorPrice;
    }

    public void setMemory(String memory) {
        this.memory = memory;
    }

    public String getMemory() {
        return memory;
    }

    public void setMemoryPrice(int memoryPrice) {
        this.memoryPrice = memoryPrice;
    }

    public int getMemoryPrice() {
        return memoryPrice;
    }
}
