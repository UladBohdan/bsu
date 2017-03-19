package by.bsu.famcs.uladbohdan.labs.test;

import java.util.*;
import java.io.*;

public class Demo {

    public static void main(String[] args) {
        try {
            VehicleCollection<Car> cars = new VehicleCollection<>();
            Scanner in = new Scanner(new File("cars.txt"));
            int n = in.nextInt();
            for (int i=0; i<n; i++)
                cars.add(new Car(in.next(), in.next(), in.next(), in.next()));
            in.close();
            cars.outToConsole();
            System.out.println("Number of cars "+cars.get(0)+"  : "+cars.count(cars.get(0)));
            System.out.println("Min car: "+cars.getMin());
        }
        catch (FileNotFoundException e) {
            System.out.println("File not found.");
        }
        catch (FuelException e) {
            System.out.println(e.getMessage());
        }
        catch (InputMismatchException e) {
            System.out.println("Invalid symbols in a file. Reading failed.");
        }
        catch (NoSuchElementException e) {
            System.out.println("Not enough data in a file. Reading failed.");
        }
        System.out.println();
        try {
            VehicleCollection<Bus> buses = new VehicleCollection<>();
            Scanner in = new Scanner(new File("buses.txt"));
            int n = in.nextInt();
            for (int i=0; i<n; i++)
                buses.add(new Bus(in.next(), in.next(), in.next(), in.nextInt(), in.nextInt()));
            in.close();
            buses.outToConsole();
            System.out.println("Number of buses "+buses.get(0)+"  : "+buses.count(buses.get(0)));
            System.out.println("Min bus: "+buses.getMin());
        }
        catch (FileNotFoundException e) {
            System.out.println("File not found.");
        }
        catch (FuelException e) {
            System.out.println(e.getMessage());
        }
        catch (InputMismatchException e) {
            System.out.println("Invalid symbols in a file. Reading failed.");
        }
        catch (NoSuchElementException e) {
            System.out.println("Not enough data in a file. Reading failed.");
        }
    }

}
