package uladbohdan.finaltest;

public abstract class Cleaner implements Comparable<Cleaner> {
    public Cleaner() {
    }
    public Cleaner(String brand, String color, int power, String imagePath) {
        this.brand = brand;
        this.color = color;
        this.power = power;
        this.imagePath = imagePath;
    }

    @Override
    public int compareTo(Cleaner cl) {
        int cmp = brand.compareTo(cl.getBrand());
        if (cmp!=0)
            return cmp;
        cmp = Integer.compare(cl.getPower(), power);
        if (cmp!=0)
            return cmp;
        return color.compareTo(cl.color);
    }

    @Override
    public String toString() {
        return brand+" "+color+" "+power;
    }

    public String getBrand() {
        return brand;
    }

    public String getColor() {
        return color;
    }

    public int getPower() {
        return power;
    }

    public String getImagePath() {
        return imagePath;
    }

    private String brand;
    private String color;
    private int power;
    private String imagePath;
}
