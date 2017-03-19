package by.bsu.famcs.uladbohdan.labs;

import java.util.*;
import java.io.*;

public class Lab10tree {

    public static void main(String[] args) {
        BinaryTree<Integer> tree = new BinaryTree<>();
        try {
            Scanner in = new Scanner(new File("tree0.txt"));
            Integer[] arr = new Integer[in.nextInt()];
            for (int i = 0; i < arr.length; i++)
                arr[i] = in.nextInt();
            tree.add(arr);

            tree.show();

            System.out.print("Pre-order tree traversal: ");
            tree.preOrderTraversal();
            System.out.print("In-order tree traversal: ");
            tree.inOrderTraversal();
            System.out.print("Post-order tree traversal: ");
            tree.postOrderTraversal();

            tree.showOnTree(11);
            tree.showOnTree(5);

            if (tree.remove(new Integer[] {11,20,2,4,5}))
                System.out.println("All elements from array has been removed successfully");
            else
                System.out.println("Something hasn't been removed");

            tree.show();

            if(tree.remove(new Integer[] {1,3}))
                System.out.println("All elements from array has been removed successfully");
            else
                System.out.println("Something hasn't been removed");

            tree.show();

            if (tree.search(19))
                System.out.println("19 exists");
            else
                System.out.println("19 is not in a tree");

            if (tree.remove(8))
                System.out.println("Successfully removed 8");
            else
                System.out.println("8 has not been found");
            if (tree.remove(19))
                System.out.println("Successfully removed 19");
            else
                System.out.println("19 has not been found");

            tree.show();

            if (tree.remove(7))
                System.out.println("Successfully removed 7");
            else
                System.out.println("7 has not been found");
            if (tree.remove(6))
                System.out.println("Successfully removed 6");
            else
                System.out.println("6 has not been found");

            tree.show();
        }
        catch (FileNotFoundException e) {
            System.out.println("Failed loading from file.");
        }
        System.out.println("---------------------TREE 2---------------------------");

        BinaryTree<ExampleComparable> tree2 = new BinaryTree<>();
        ExampleComparable x = new ExampleComparable("aaa");
        ExampleComparable y = new ExampleComparable("bb");
        ExampleComparable z = new ExampleComparable("xxxx");
        tree2.add(x);
        tree2.add(y);
        tree2.add(z);
        tree2.show();
    }
}