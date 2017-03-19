package by.bsu.famcs.uladbohdan.labs;

import java.io.*;

public abstract class Series {
    public Series() {
        this.begin = 0;
        this.step = 0;
        this.count = 0;
    }
    public Series(double begin, double step) {
        this.begin = begin;
        this.step = step;
        this.count = 0;
    }

    public abstract double getElement(int k);
    public double getSum() {
        double sum=0;
        for (int i=1; i<=count; i++)
            sum+=getElement(i);
        return sum;
    }
    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        for (int i=1; i<=count; i++)
            str.append(getElement(i)+" ");
        str.deleteCharAt(str.length()-1);
        return str.toString();
    }
    public void saveToFile(String fileName) throws IOException {
        FileWriter out = new FileWriter(fileName);
        out.write(toString());
        out.close();
    }
    public void setNumber(int count) {
        this.count = count;
    }
    protected double begin;
    protected double step;
    protected double count;
}
