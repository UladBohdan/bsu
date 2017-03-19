package by.bsu.famcs.uladbohdan.labs;

public class LinearSeries extends Series {
    public LinearSeries() {
        super();
    }
    public LinearSeries(double begin, double step) {
        super(begin, step);
    }

    @Override
    public double getElement(int k) {
        return begin+step*(k-1);
    }
}
