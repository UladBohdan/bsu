package by.bsu.famcs.uladbohdan.vma;

import java.io.*;

//	n - number of rows
//	m - number of columns

public class Matrix {

    protected double a[][];
    protected int n, m;

    public Matrix() {
        this.n = 3;
        this.m = 3;
        this.a = new double[3][3];
        makeZero();
    }
    public Matrix(int n) {		// creates a vector
        this.n = n;
        this.m = 1;
        this.a = new double[n][1];
        makeZero();
    }
    public Matrix(int n, int m) {
        this.n = n;
        this.m = m;
        this.a = new double[n][m];
        makeZero();
    }
    public Matrix(int n, int m, double[] val) throws ArrayInitException {
        if (val.length<n*m)
            throw new ArrayInitException("Array has too few elemets.");
        this.n = n;
        this.m = m;
        this.a = new double[n][m];
        int pos=0;
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++) {
                a[i][j]=val[pos];
                pos++;
            }
    }
    public Matrix(Matrix x) {
        this.n = x.n;
        this.m = x.m;
        this.a = new double[n][m];
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                a[i][j]=x.a[i][j];
    }

    public void setSize(int n, int m){
        this.n=n;
        this.m=m;
    }
    public void makeZero() {
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                a[i][j]=0;
    }
    public boolean isSquare() {
        return (n==m);
    }
    public int getN() {
        return n;
    }
    public int getM() {
        return m;
    }
    public static Matrix getIMatrix(int n) {
        Matrix temp = new Matrix(n,n);
        for (int i=0; i<n; i++)
            temp.a[i][i]=1;
        return temp;
    }

    public Matrix getDiagonal() {
        Matrix temp = new Matrix(n,m);
        for (int i=0; i<n; i++)
            temp.a[i][i]=a[i][i];
        return temp;
    }
    public Matrix getLow() {
        Matrix temp = new Matrix(n,m);
        for (int i=0; i<n; i++)
            for (int j=0; j<i; j++)
                temp.a[i][j]=a[i][j];
        return temp;
    }
    public Matrix getUp() {
        Matrix temp = new Matrix(n,m);
        for (int i=0; i<n; i++)
            for (int j=i+1; j<n; j++)
                temp.a[i][j]=a[i][j];
        return temp;
    }
    public double det() throws MatrixSizeException, IOException {
        if (!isSquare())
            throw new MatrixSizeException("Failed to count determinant for non-square matrix.");
        double x=0;
        if (n==2)
            x = a[0][0]*a[1][1]-a[0][1]*a[1][0];
        else if (n==1)
            x = a[0][0];
        else {
            for (int i=0; i<n; i++)
                x+=a[0][i]*this.algAdd(0, i);
        }
        return x;
    }
    public Matrix transp() {
        Matrix temp = new Matrix(m,n);
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                temp.a[j][i]=a[i][j];
        return temp;
    }
    public double norm() {
        double mx=0;
        for (int i=0; i<n; i++) {
            double temp=0;
            for (int j=0; j<m; j++) {
                temp+=Math.abs(a[i][j]);
            }
            if (temp>mx)
                mx=temp;
        }
        return mx;
    }
    public Matrix getInversed() throws MatrixSizeException, IOException {
        if (!isSquare())
            throw new MatrixSizeException("Not square. Inversion failed.");
        Matrix temp = new Matrix(n,n);
        for (int i=0; i<n; i++)
            for (int j=0; j<n; j++)
                temp.a[i][j]=algAdd(i,j);
        double dett = 1./det();
        temp = temp.mult(dett);
        return temp.transp();
    }
    public double algAdd(int x, int y) throws MatrixSizeException, IOException {
        if (x<0 || x>=n || y<0 || y>=m)
            throw new IOException("Failed to build algAdd.");
        double sign;
        if ((x+y)%2==0)
            sign=1;
        else
            sign=-1;
        Matrix temp = new Matrix(n-1, m-1);
        int posI=0, posJ=0;
        for (int i=0; i<n; i++, posI++) {
            if (i==x) {
                posI--;
                continue;
            }
            posJ=0;
            for (int j=0; j<m; j++, posJ++) {
                if (j==y) {
                    posJ--;
                    continue;
                }
                temp.a[posI][posJ]=a[i][j];
            }
        }
        return sign*temp.det();
    }

    public Matrix add(Matrix b) throws MatrixSizeException {
        if (b.getM()!=m || b.getN()!=n)
            throw new MatrixSizeException("Adding failed. Wrong matrix sizes.");
        Matrix temp = new Matrix(n,m);
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                temp.a[i][j]=a[i][j]+b.a[i][j];
        return temp;
    }
    public Matrix sub(Matrix b) throws MatrixSizeException {
        if (b.getM()!=m || b.getN()!=n)
            throw new MatrixSizeException("Subtracting failed. Wrong matrix sizes.");
        Matrix temp = new Matrix(n,m);
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                temp.a[i][j]=a[i][j]-b.a[i][j];
        return temp;
    }
    public Matrix mult(double x) {
        Matrix temp = new Matrix(n,m);
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                temp.a[i][j]=a[i][j]*x;
        return temp;
    }
    public Matrix mult(Matrix b) throws MatrixSizeException {
        if (b.getN()!=m)
            throw new MatrixSizeException("Multiplying failed. Wrong matrix sizes.");
        Matrix temp = new Matrix(n,b.getM());
        for (int i=0; i<n; i++)
            for (int j=0; j<b.getM(); j++)
                for (int t=0; t<m; t++)
                    temp.a[i][j]+=(a[i][t]*b.a[t][j]);
        return temp;
    }
    public double getScalarProduct(Matrix b) throws MatrixSizeException {
        if (m!=1 || b.getM()!=1 || n!=b.getN())
            throw new MatrixSizeException("Scalar product failed.");
        double temp=0;
        for (int i=0; i<n; i++)
            temp+=(a[i][0]*b.a[i][0]);
        return temp;
    }

    public void outToConsole() {
        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++)
                System.out.print(a[i][j]+" ");
            System.out.println();
        }
        System.out.println();
    }
}