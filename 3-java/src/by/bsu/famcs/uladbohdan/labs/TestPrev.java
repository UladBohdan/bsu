package by.bsu.famcs.uladbohdan.labs;

import java.util.*;
import java.io.*;

public class TestPrev<T extends Comparable<T>> extends ArrayList<T> {

    TestPrev() {

    }

    public T getMin() throws EmptyCollectionException {
        if (isEmpty())
            throw new EmptyCollectionException();
        return Collections.min(this);
    }
    public T getMax() throws EmptyCollectionException {
        if (isEmpty())
            throw new EmptyCollectionException();
        return Collections.max(this);
    }
        
    public static void main(String[] args) {
        try {
            TestPrev<Double> doubles = new TestPrev<>();
            Scanner in = new Scanner(new File("in1.txt"));
            int n = in.nextInt();
            for (int i=0; i<n; i++)
                doubles.add(in.nextDouble());
            in.close();
            System.out.println("Min double: "+doubles.getMin());
            System.out.println("Max double: "+doubles.getMax());
        }
        catch (FileNotFoundException e) {
            System.out.println("File not found.");
        }
        catch (InputMismatchException e) {
            System.out.println("Invalid symbols in a file. Reading failed.");
        }
        catch (NoSuchElementException e) {
            System.out.println("Not enough data in a file. Reading failed.");
        }
        catch (EmptyCollectionException e) {
            System.out.println("Failed to retrieve data from empty collection.");
        }
        System.out.println();
        try {
            TestPrev<Student> studs = new TestPrev<>();
            Scanner in = new Scanner(new File("in2.txt"));
            int n = in.nextInt();
            for (int i=0; i<n; i++)
                studs.add(new Student(in.next(), in.nextInt(), in.nextDouble()));
            in.close();
            System.out.println("Min student (by GPA): "+studs.getMin());
            System.out.println("Max student (by GPA): "+studs.getMax());
        }
        catch (FileNotFoundException e) {
            System.out.println("File not found.");
        }
        catch (InputMismatchException e) {
            System.out.println("Invalid symbols in a file. Reading failed.");
        }
        catch (NoSuchElementException e) {
            System.out.println("Not enough data in a file. Reading failed.");
        }
        catch (EmptyCollectionException e) {
            System.out.println("Failed to retrieve data from empty collection.");
        }
    }

}

class Student implements Comparable<Student> {
    Student() {

    }
    Student(String name, int course, double gpa) {
        this.name = name;
        this.course = course;
        this.gpa = gpa;
    }

    @Override
    public int compareTo(Student stud) {
        if (Math.abs(this.gpa-stud.gpa)<eps)
            return 0;
        else if (this.gpa-stud.gpa>0)
            return 1;
        else
            return -1;
    }
    @Override
    public String toString() {
        return "Name: "+name+", course: "+course+", GPA: "+gpa;
    }

    private String name;
    private int course;
    private double gpa;
    private static final double eps = 1e-6;
}

class EmptyCollectionException extends Exception {
    EmptyCollectionException() {
        super();
    }
    EmptyCollectionException(String str) {
        super(str);
    }
}