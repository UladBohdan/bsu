package by.bsu.famcs.uladbohdan.vma;

import java.io.*;

/**Solves systems of linear equations by:
 * Gauss
 * Simple Iteration
 * Gradient Descent
 * Relaxation
 * Seidel
 * you may get answer using getAnswer() method our redirect an answer to console using outAnswer()
 */
public class SolutionSOLE extends SystemOfLinearEquations {

    private double eps;
    private int numberOfIterations;
    private Matrix ans;
    private Matrix symmMatrix;
    private Matrix bT;

    public SolutionSOLE() {
        super();
    }
    public SolutionSOLE(double eps) {
        super();
        this.eps=eps;
    }

    public void setAccuracy(double eps) {
        this.eps=eps;
    }
    public int getNumberOfIterations() {
        return numberOfIterations;
    }
    public Matrix getAnswer() {
        return ans;
    }

    public void outAnswer() throws IOException {
        if (ans==null)
            throw new IOException("Answer hasn't been counted yet.");
        System.out.println("Solution: ");
        ans.outToConsole();
    }
    public void outNumberOfIterations() {
        System.out.println("Number of iterations: "+numberOfIterations);
    }

    public void byGaussianElimination() throws MatrixSizeException, IOException {
        Matrix temp = new Matrix(matr);
        Matrix bb = new Matrix(b);
        int n = temp.getN();
        if (ans==null)
            ans = new Matrix(n);
        else
            ans.makeZero();
        for (int i=0; i<n; i++) {
            if (temp.a[i][i]!=0) {
                for (int j=i+1; j<n; j++)
                    temp.a[i][j] /= temp.a[i][i];
                bb.a[i][0] /= temp.a[i][i];
                temp.a[i][i]=1;
                for (int j=i+1; j<n; j++) {
                    double koef = temp.a[j][i];
                    for (int k=0; k<n; k++)
                        temp.a[j][k] -= koef*temp.a[i][k];
                    bb.a[j][0] -= koef*bb.a[i][0];
                }
            }
            else {
                for (int j = i + 1; j < n; j++)
                    if (temp.a[j][i] != 0) {
                        double t;
                        for (int k = 0; k < n; k++) {
                            t = temp.a[j][k];
                            temp.a[j][k] = temp.a[i][k];
                            temp.a[i][k] = t;
                        }
                        t = bb.a[j][0];
                        bb.a[j][0] = bb.a[i][0];
                        bb.a[i][0] = t;
                        i--;
                        j = n;
                    }
            }
        }
        for (int i=n-1; i>=0; i--) {
            ans.a[i][0]=bb.a[i][0];
            for (int j=i-1; j>=0; j--) {
                bb.a[j][0] -= temp.a[j][i]*bb.a[i][0];
            }
        }
    }

    public void bySimpleIteration() throws MatrixSizeException, IOException {
        int n=matr.getN();
        Matrix BB = new Matrix(n, n);		// B
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (i==j)
                    BB.a[i][j]=0;
                else
                    BB.a[i][j]=-1*matr.a[i][j]/matr.a[i][i];
            }
        }
        if (BB.norm()>=1)
            throw new IOException("System cannot be solved by Simple Iteration.");
        Matrix gVect = new Matrix(n);
        for (int i=0; i<n; i++)
            gVect.a[i][0]=b.a[i][0]/matr.a[i][i];

        System.out.println("Expected number of iterations: "+(int)(Math.log(1./eps)/Math.log(1./BB.norm())+1));
        System.out.println();

        Matrix x0 = gVect;
        numberOfIterations=0;
        if (ans!=null)
            ans.makeZero();
        boolean cond1=false, cond2=false;
        while(true) {
            ans = BB.mult(x0).add(gVect);
            numberOfIterations++;
            if (cond1==false && ans.sub(x0).norm()<eps)
            {
                System.out.println("Number of iterations stopped by condition |X(k+1)-X(k)|: "+numberOfIterations);
                cond1=true;
            }
            if (cond2==false && countResidual().norm()<eps)
            {
                System.out.println("Number of iterations stopped by condition |R(k+1)-R(k)|: "+numberOfIterations);
                cond2=true;
            }
            if (cond1==true && cond2==true)
                break;
            x0=ans;
        }
    }

    public void byGradientDescent() throws MatrixSizeException, IOException {
        countSymmetricMatrix();
        Matrix x0 = bT;
        numberOfIterations=0;
        if (ans!=null)
            ans.makeZero();
        boolean cond1=false, cond2=false;
        while(true) {
            Matrix r0 = symmMatrix.mult(x0).sub(bT);
            double temp = r0.getScalarProduct(r0);
            temp /= symmMatrix.mult(r0).getScalarProduct(r0);
            ans = x0.sub( r0.mult(temp) );
            numberOfIterations++;
            if (cond1==false && ans.sub(x0).norm()<eps)
            {
                System.out.println("Number of iterations stopped by condition |X(k+1)-X(k)|: "+numberOfIterations);
                cond1=true;
            }
            if (cond2==false && countResidual().norm()<eps)
            {
                System.out.println("Number of iterations stopped by condition |R(k+1)-R(k)|: "+numberOfIterations);
                cond2=true;
            }
            if (cond1==true && cond2==true)
                break;
            x0=ans;
        }
    }

    public void bySuccessiveOverRelaxation (double w) throws MatrixSizeException, IOException {
        if (w<=0 || w>=2)
            throw new IOException("W doesn't belong to (0,2).");
        countSymmetricMatrix();
        numberOfIterations=0;
        if (ans!=null)
            ans.makeZero();

        Matrix D = symmMatrix.getDiagonal();
        Matrix L = symmMatrix.getLow();
        Matrix R = symmMatrix.getUp();
        Matrix dwlInv = L.mult(w).add(D).getInversed();
        Matrix BW = D.mult(1-w).sub(R.mult(w));
        BW = dwlInv.mult(BW);
        Matrix GW = dwlInv.mult(bT);

        Matrix x0 = bT;
        boolean cond1=false, cond2=false;
        while (true) {
            ans = BW.mult(x0).add(GW);
            numberOfIterations++;
            if (cond1==false && ans.sub(x0).norm()<eps)
            {
                System.out.println("Number of iterations stopped by condition |X(k+1)-X(k)|: "+numberOfIterations);
                cond1=true;
            }
            if ((cond2==false && countResidual().norm()<eps) || numberOfIterations>20000)
            {
                System.out.println("Number of iterations stopped by condition |R(k+1)-R(k)|: "+numberOfIterations);
                cond2=true;
            }
            if (cond1==true && cond2==true)
                break;
            x0 = ans;
        }
        ans = ans.mult(w);
    }

    public void byUniversalSeidel() throws MatrixSizeException, IOException {
        bySuccessiveOverRelaxation(1);
    }

    public void byCanonicalSeidel() throws MatrixSizeException, IOException {
        int n = matr.getN();
        Matrix matrB = new Matrix(n, n);
        Matrix matrG = new Matrix(n);
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (i==j)
                    matrB.a[i][j]=0;
                else
                    matrB.a[i][j]=-1*matr.a[i][j]/matr.a[i][i];
            }
        }
        for (int i=0; i<n; i++)
            matrG.a[i][0]=b.a[i][0]/matr.a[i][i];
        if (matrB.norm()>=1)
            throw new IOException("Canonical Seidel may not be used.");

        Matrix H = matrB.getLow();
        Matrix F = matrB.getUp().add(matrB.getDiagonal());

        Matrix BB = Matrix.getIMatrix(n).sub(H).getInversed().mult(F);
        Matrix gVect = Matrix.getIMatrix(n).sub(H).getInversed().mult(matrG);
        if (BB.norm()>=1)
            throw new IOException("Canonical Seidel may not be used.");

        if (ans!=null)
            ans.makeZero();
        numberOfIterations=0;
        Matrix x0 = gVect;
        boolean cond1=false, cond2=false;
        while(true) {
            ans = BB.mult(x0).add(gVect);
            numberOfIterations++;
            if (cond1==false && ans.sub(x0).norm()<eps)
            {
                System.out.println("Number of iterations stopped by condition |X(k+1)-X(k)|: "+numberOfIterations);
                cond1=true;
            }
            if (cond2==false && countResidual().norm()<eps)
            {
                System.out.println("Number of iterations stopped by condition |R(k+1)-R(k)|: "+numberOfIterations);
                cond2=true;
            }
            if (cond1==true && cond2==true)
                break;
            x0=ans;
        }
    }

    public Matrix countResidual() throws MatrixSizeException, IOException {
        Matrix temp;
        temp = matr.mult(ans).sub(b);
        return temp;
    }
    private void countSymmetricMatrix() throws MatrixSizeException {
        symmMatrix = matr.transp().mult(matr);
        bT = matr.transp().mult(b);
    }
}