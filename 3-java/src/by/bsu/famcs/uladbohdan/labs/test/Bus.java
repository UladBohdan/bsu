package by.bsu.famcs.uladbohdan.labs.test;

public class Bus extends Vehicle {
    public Bus() {
        super();
    }
    public Bus(String name, String color, String fuel, int places, int doors) throws FuelException {
        super(name,color,fuel);
        this.places = places;
        this.doors = doors;
    }

    @Override
    public String toString() {
        return "Car: "+super.toString()+" "+places+" "+doors;
    }

    public int getPlaces() {
        return places;
    }
    public int getDoors() {
        return doors;
    }

    private int places;
    private int doors;
}
