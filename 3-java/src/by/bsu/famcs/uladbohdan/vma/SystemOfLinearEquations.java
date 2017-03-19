package by.bsu.famcs.uladbohdan.vma;

import java.io.*;
import java.util.*;

public class SystemOfLinearEquations {

    public Matrix matr;
    public Matrix b;

    public SystemOfLinearEquations() {
        matr = new Matrix(3,3);
        b = new Matrix(3);
    }
    public SystemOfLinearEquations(Matrix matr, Matrix b) throws MatrixSizeException {
        if (b.m!=1 || matr.n!=b.n || !matr.isSquare())
            throw new MatrixSizeException("Failed to create System of Linear Equations. Wrong arguments.");
        this.matr=matr;
        this.b=b;
    }

    public void loadFromFile(String file) {
        try {
            Scanner in = new Scanner(new File(file));
            int n = in.nextInt();
            matr = new Matrix(n, n);
            b = new Matrix(n);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++)
                    matr.a[i][j] = in.nextDouble();
                b.a[i][0] = in.nextDouble();
            }
            in.close();
        } catch (FileNotFoundException e) {
            System.out.println("Loading failed: file not found.");
        }
    }
}