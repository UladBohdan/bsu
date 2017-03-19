package uladbohdan.finaltest;

public class RobotCleaner extends Cleaner {
    public RobotCleaner() {
        super();
    }
    public RobotCleaner(String brand, String color, int power, String imagePath, boolean screen) {
        super(brand, color, power, imagePath);
        this.screen = screen;
    }

    @Override
    public String toString() {
        return super.toString()+" "+screen;
    }

    public boolean isScreen() {
        return screen;
    }

    boolean screen;
}
