package by.bsu.famcs.uladbohdan.labs.test;

import java.util.*;

public class VehicleCollection<T extends Vehicle> extends ArrayList<T> {

    public void outToConsole() {
        System.out.println(super.toString());
    }
    public int count(T obj) {
        int n=0;
        for (T local:this)
            if (obj.compareTo(local)==0)
                n++;
        return n;
    }
    public T getMin() {
        return Collections.min(this);
    }
}