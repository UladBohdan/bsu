package by.bsu.famcs.uladbohdan.labs.test;

public abstract class Vehicle implements Comparable<Vehicle> {
    public Vehicle() {
        name = "N/A";
        color = "N/A";
        fuel = "oil";
    }
    public Vehicle(String name, String color, String fuel) throws FuelException {
        if (fuel.equals("oil")==false && fuel.equals("diesel")==false)
            throw new FuelException("Wrong fuel value");
        this.name = name;
        this.color = color;
        this.fuel = fuel;
    }

    @Override
    public String toString() {
        return name+" "+color+" "+fuel;
    }

    @Override
    public int compareTo(Vehicle obj) {
        if (fuel.compareTo(obj.getFuel())!=0)
            return fuel.compareTo(obj.getFuel());
        else if (name.compareTo(obj.getName())!=0)
            return name.compareTo(obj.getName());
        else if (color.compareTo(obj.getColor())!=0)
            return color.compareTo(obj.getColor());
        else
            return 0;
    }

    public String getName() {
        return name;
    }
    public String getColor() {
        return color;
    }
    public String getFuel() {
        return fuel;
    }

    private String name;
    private String color;
    private String fuel;
}
