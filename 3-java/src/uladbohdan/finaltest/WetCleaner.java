package uladbohdan.finaltest;

public class WetCleaner extends Cleaner {
    public WetCleaner() {
        super();
    }
    public WetCleaner(String brand, String color, int power, String imagePath, int volume) {
        super(brand, color, power, imagePath);
        this.volume = volume;
    }

    @Override
    public String toString() {
        return super.toString()+" "+volume;
    }

    public int getVolume() {
        return volume;
    }

    private int volume;
}
