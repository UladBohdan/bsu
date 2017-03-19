package by.bsu.famcs.uladbohdan.labs;

public class ExampleComparable implements Comparable<ExampleComparable> {

    public ExampleComparable() {

    }
    public ExampleComparable (String value) {
        this.value = value;
    }
    @Override
    public int compareTo(ExampleComparable a) {
        int len1 = value.length();
        int len2 = a.getValue().length();
        return new Integer(len1).compareTo(len2);
    }
    @Override
    public String toString() {
        return value;
    }
    public String getValue() {
        return value;
    }
    private String value;
}
