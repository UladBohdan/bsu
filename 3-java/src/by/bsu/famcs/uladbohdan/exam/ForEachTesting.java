package by.bsu.famcs.uladbohdan.exam;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.Iterator;

class MyCollection<T> implements Iterable<T> {
    MyCollection(T[] arr) {
        data = arr;
    }

    @Override
    public Iterator<T> iterator() {
        return new Iterator<T>() {
            private int curPos = 0;

            @Override
            public boolean hasNext() {
                return curPos < data.length;
            }

            @Override
            public T next() {
                return data[curPos++];
            }
        };
    }

    private T[] data;
}

class A {
    static String ID = "LOL";
}

class B extends A {
    static {
        System.out.println("Im in B");
    }
}

public class ForEachTesting {
    <T extends Comparable>T genericMethod(T y) {
        return y;
    }

    public static void main(String[] args) {
        Integer[] a = new Integer[] {4,6,5,2,1};
        Arrays.sort(a);
        MyCollection<Integer> b = new MyCollection<>(a);
        for(int i: b) {
            System.out.print(i+" ");
        }

        System.out.println(B.ID);

        try {
            try {
                throw null;
            }
            finally {
                System.out.println("we are inside");
            }
        }
        catch (NullPointerException e) {
            System.out.println("lol");
        }
        finally {
            System.out.println("we are outside");
        }

        MyEnum x = MyEnum.GREEN;
        System.out.println();
    }

    static class ClassName2 {
        int x;

    }

}

class TestExtend extends ArrayList<String> {

}
