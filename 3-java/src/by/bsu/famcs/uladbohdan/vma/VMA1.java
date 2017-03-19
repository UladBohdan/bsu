package by.bsu.famcs.uladbohdan.vma;

import java.io.*;

public class VMA1 {

    public static void main(String[] args) {
        SolutionSOLE solve = new SolutionSOLE(1e-4);
        solve.loadFromFile("matrixVMA1.txt");
        try {
            System.out.println();
            System.out.println("GAUSS----------------------------------------------------");
            solve.byGaussianElimination();
            solve.outAnswer();
        }
        catch (MatrixSizeException | IOException e) {
              System.out.println(e.getMessage());
        }
        try {
            System.out.println();
            System.out.println("SIMPLE ITERATION-----------------------------------------");
            solve.loadFromFile("matrixVMA1_diag.txt");
            solve.bySimpleIteration();
            solve.outAnswer();
        }
        catch (MatrixSizeException | IOException e) {
            System.out.println(e.getMessage());
        }
        try {
            System.out.println();
            System.out.println("GRADIENT DESCENT-----------------------------------------");
            solve.loadFromFile("matrixVMA1.txt");
            solve.byGradientDescent();
            solve.outAnswer();
        }
        catch (MatrixSizeException | IOException e) {
            System.out.println(e.getMessage());
        }
        try {
            System.out.println();
            System.out.println("RELAXATION-----------------------------------------------");
            solve.bySuccessiveOverRelaxation(1.5);
            solve.outAnswer();
        }
        catch (MatrixSizeException | IOException e) {
            System.out.println(e.getMessage());
        }
        solve.loadFromFile("matrixVMA1_diag.txt");
        try {
            System.out.println();
            System.out.println("CANONICAL SEIDEL-----------------------------------------");
            solve.byCanonicalSeidel();
            solve.outAnswer();
        }
        catch (MatrixSizeException | IOException e) {
            System.out.println(e.getMessage());
        }
        try {
            System.out.println();
            System.out.println("UNIVERSAL SEIDEL-----------------------------------------");
            solve.byUniversalSeidel();
            solve.outAnswer();
        }
        catch (MatrixSizeException | IOException e) {
            System.out.println(e.getMessage());
        }
    }

}