#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define ROOT 0

int N, R2, Q2;

double** A;
double** submatrix;
double* underA;
double* underSubmatrix;

// Initialized.
//int R1 = 5, Q2, R3 = 5;
// Calculated.
//int Q1, R2, Q3;

void generateMatrix() {
  // Allocating contiguous memory.
  underA = (double*) malloc(N * (N+1) * sizeof(double));
  A = (double**) malloc((N) * sizeof(double*));
  for (int i = 0; i < N; i++) {
    A[i] = underA + i * (N+1);
  }

  for (int i = 0; i < N; i++) {
    double sum = 0;
    for (int j = 0; j < N; j++) {
      A[i][j] = (i == j ? 100. : (2. * i + j) / 100000.);
      sum += A[i][j];
      //A[i][j] = (i == j ? 10. : (2. * i + j));
      //sum += A[i][j] * (j+1) * (j+1);
    }
    A[i][N] = sum;
  }
}

void printMatrix(double** A, int N) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%f ", A[i][j]);
    }
    printf(" | %f\n", A[i][N]);
  }
}

void runGauss(int proc_rank) {
  for (int k = 0; k < N; k++) {

    if (proc_rank == k / R2) {

      double* u = (double*) malloc((N+1) * sizeof(double));
      for (int i = 0; i < N+1; i++) {
        u[i] = 0.;
      }

      int row = k % R2;

      for (int j = k + 1; j < N+1; j++) {
        u[j] = submatrix[row][j] / submatrix[row][k];
        submatrix[row][j] /= submatrix[row][k];
      }
      u[k] = 1.;
      submatrix[row][k] = 1.;

      if (proc_rank != Q2-1) {
        MPI_Send(u, N+1, MPI_DOUBLE, 1, 123, MPI_COMM_WORLD);
      }

      // Applying u row for submatrix.
      for (int i = row+1; i < R2; i++) {
        for (int j = k + 1; j < N+1; j++) {
          submatrix[i][j] -= submatrix[i][k] * u[j];
        }
        submatrix[i][k] = 0.;
      }

      free(u);
    } else if (proc_rank > k / R2) {
      double* u = (double*) malloc((N+1) * sizeof(double));
      MPI_Recv(u, N+1, MPI_DOUBLE, proc_rank-1, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      // Sending to the next process first. TODO>
      if (proc_rank < Q2-1) {
        // Translating the row further.
        MPI_Send(u, N+1, MPI_DOUBLE, proc_rank + 1, 123, MPI_COMM_WORLD);
      }

      // Applying u row for submatrix.
      for (int i = 0; i < R2; i++) {
        for (int j = k + 1; j < N + 1; j++) {
          submatrix[i][j] -= submatrix[i][k] * u[j];
        }
        submatrix[i][k] = 0.;
      }
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }
}

void runIndirectGauss() {
  for (int k = N-1; k>=1; k--) {
    for (int j = k-1; j>=0; j--) {
      A[j][N] -= A[j][k] * A[k][N];
      A[j][k] = 0;
    }
  }
}

int main(int argc, char** argv) {
  MPI_Init(NULL, NULL);
  MPI_Comm_size(MPI_COMM_WORLD, &Q2);

  int proc_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);

  if (proc_rank == ROOT) {
    if (argc != 2) {
      printf("Required number of arguments: 1\n");
      return 0;
    }
  }

  MPI_Barrier(MPI_COMM_WORLD);

  sscanf(argv[1], "%d", &N);

  //  Q1 = (N - 1) / R1 + ((N-1)%R1 == 0 ? 0 : 1);
  R2 = (N - 1) / Q2 + ((N-1)%Q2 == 0 ? 0 : 1);
  //  Q3 = N / R3 + (N%R3 == 0 ? 0 : 1);

  underSubmatrix = malloc(R2 * (N+1) * sizeof(double));
  submatrix = malloc(R2 * sizeof(double*));
  for (int i = 0; i < R2; i++) {
    submatrix[i] = underSubmatrix + i * (N+1);
  }

  if (proc_rank == ROOT) {
    generateMatrix();
    printMatrix(A, N);
    printf("Matrix is generated.\n");

    for (int proc = 1; proc < Q2; proc++) {
      MPI_Send(A[R2*proc], R2 * (N+1), MPI_DOUBLE, proc, 345, MPI_COMM_WORLD);
    }
    for (int i = 0; i < R2; i++) {
      for (int j = 0; j < N+1; j++) {
        submatrix[i][j] = A[i][j];
      }
    }
  } else {
    MPI_Recv(underSubmatrix, R2 * (N+1), MPI_DOUBLE, ROOT, 345, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  MPI_Barrier(MPI_COMM_WORLD);

  runGauss(proc_rank);

  MPI_Barrier(MPI_COMM_WORLD);

  if (proc_rank == ROOT) {
    for (int proc = 1; proc < Q2; proc++) {
      MPI_Recv(A[R2*proc], R2 * (N+1), MPI_DOUBLE, proc, 109, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    for (int i = 0; i < R2; i++) {
      for (int j = 0; j < N+1; j++) {
        A[i][j] = submatrix[i][j];
      }
    }
  } else {
    MPI_Send(underSubmatrix, R2 * (N+1), MPI_DOUBLE, ROOT, 109, MPI_COMM_WORLD);
  }

  MPI_Barrier(MPI_COMM_WORLD);

  if (proc_rank == ROOT) {
    runIndirectGauss();

    printf("======\nTHE SOLUTION\n=======\n");
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        printf("%f ", A[i][j]);
      }
      printf("| %f\n", A[i][N]);
    }
  }

  if (proc_rank) {
    free(underA);
    free(A);
  } else {
    free(underSubmatrix);
    free(submatrix);
  }

  MPI_Finalize();

  return 0;
}
