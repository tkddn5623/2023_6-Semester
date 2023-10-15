import java.util.Scanner;

abstract public class Product {
    private int basePrice;
    private int totalCost;
    private String model;
    private int modelPrice;
    private int quantity;

    Product(int basePrice) {
        setBasePrice(basePrice);
    }

    public void setBasePrice(int basePrice) {
        this.basePrice = basePrice;
    }

    public int getBasePrice() {
        return basePrice;
    }

    public void setTotalCost(int totalCost) {
        this.totalCost = totalCost;
    }

    public int getTotalCost() {
        return totalCost;
    }

    public void setModel(String model) {
        this.model = model;
    }

    public String getModel() {
        return model;
    }

    public void setModelPrice(int modelPrice) {
        this.modelPrice = modelPrice;
    }

    public int getModelPrice() {
        return modelPrice;
    }

    public void setQuantity(int quantity) {
        this.quantity = quantity;
    }

    public int getQuantity() {
        return quantity;
    }

    public void getUserSelection(Scanner scn) {
    } // Abstract function

    public int calculateCost() {
        return 0;
    } // Abstract function
}
