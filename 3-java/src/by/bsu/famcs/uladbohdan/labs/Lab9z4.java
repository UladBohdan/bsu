package by.bsu.famcs.uladbohdan.labs;

import java.io.*;

import by.bsu.famcs.uladbohdan.vma.MatrixSizeException;
import by.bsu.famcs.uladbohdan.vma.SolutionSOLE;

public class Lab9z4 {

    public static void main(String[] args) {
        try {
            SolutionSOLE solve = new SolutionSOLE();
            solve.loadFromFile("matrixLab9.txt");
            solve.byGaussianElimination();
            solve.outAnswer();
            System.out.println("Residual:");
            solve.countResidual().outToConsole();
        }
        catch (MatrixSizeException | IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
