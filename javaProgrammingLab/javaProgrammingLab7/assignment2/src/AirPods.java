import java.util.Scanner;

public class AirPods extends Product {
    static private final String PRODUCT_NAME = "AirPods";

    AirPods(Scanner scn) {
        super(120);
        getUserSelection(scn);
        setTotalCost(calculateCost());
        System.out.println("====== check ======");
        System.out.println("Model (" + getModel() + ") ------ +$" + getModelPrice());
        System.out.println("Total cost for one " + PRODUCT_NAME + ": $" + getTotalCost());
        System.out.println("Total cost (quantity x " + getQuantity() + "): $" + getTotalCost() * getQuantity());
    }

    public void getUserSelection(Scanner scn) {
        System.out.println("Base cost of the " + PRODUCT_NAME + ": " + getBasePrice());
        System.out.println("Which model do you want (AirPods3 or AirPodsPro or AirPodsMax) ");
        label:
        while(true){
            setModel(scn.nextLine());
            switch (getModel()) {
                case "AirPods3":
                    setModelPrice(0);
                    break label;
                case "AirPodsPro":
                    setModelPrice(100);
                    break label;
                case "AirPodsMax":
                    setModelPrice(200);
                    break label;
            }
        }
        System.out.print("How many do you want buy: ");
        setQuantity(scn.nextInt());
    }

    public int calculateCost() {
        return getBasePrice() + getModelPrice();
    }


}
