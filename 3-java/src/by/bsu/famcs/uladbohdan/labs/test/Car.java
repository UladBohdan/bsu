package by.bsu.famcs.uladbohdan.labs.test;

public class Car extends Vehicle {
    public Car() {
        super();
        material = "";
    }
    public Car(String name, String color, String fuel, String material) throws FuelException {
        super(name,color,fuel);
        this.material = material;
    }

    @Override
    public String toString() {
        return "Car: "+super.toString()+" "+material;
    }

    public String getMaterial() {
        return material;
    }

    private String material;
}
