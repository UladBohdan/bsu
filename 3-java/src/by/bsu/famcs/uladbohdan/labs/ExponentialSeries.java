package by.bsu.famcs.uladbohdan.labs;

public class ExponentialSeries extends Series {
    public ExponentialSeries() {
        super();
    }
    public ExponentialSeries(double begin, double step) {
        super(begin, step);
    }

    @Override
    public double getElement(int k) {
        return begin*Math.pow(step,k-1);
    }
}
