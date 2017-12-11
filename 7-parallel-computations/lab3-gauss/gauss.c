#include <math.h>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROOT 0

const char* COLOUR_GREEN = "\033[1;32m";
const char* COLOUR_RED = "\033[1;31m";
const char* COLOUR_DEFAULT = "\033[0m";
const double EPS = 0.01;

int N, R2, Q2;

double** A;
double** submatrix;
double** B; // to collect data back.
double* underA;
double* underB;
double* underSubmatrix;

// Metrics.
clock_t time_start;
double time_communications = 0;
void updateTimeComm() { time_communications += (double)(clock() - time_start); }
double time_calculations = 0;
void updateTimeCalc() { time_calculations += (double)(clock() - time_start); }
double time_indirect_gauss = 0;

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
      // A[i][j] = (i == j ? 10. : (2. * i + j));
      // sum += A[i][j] * (j+1) * (j+1); // Answers are number squares then.
    }
    A[i][N] = sum;
  }
}

void alloc_B() {
  underB = (double*) malloc(N * (N+1) * sizeof(double));
  B = (double**) malloc((N) * sizeof(double*));
  for (int i = 0; i < N; i++) {
    B[i] = underB + i * (N+1);
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

void checkCorrectness() {
  // A is a generated matrix.
  // B contains the answer.
  for (int i = 0; i < N; i++) {
    long double val = 0;
    for (int j = 0; j < N; j++) {
      val += A[i][j] * B[j][N];
    }
    if (fabsl(val - A[i][N]) > EPS) {
      printf("%sCHECK FAILED with value %Lf%s\n", COLOUR_RED, fabsl(val - A[i][N]), COLOUR_DEFAULT);
      return;
    }
  }
  printf("%sCHECK PASSED.%s\n", COLOUR_GREEN, COLOUR_DEFAULT);
}

void runGauss(int proc_rank) {

  for (int k = 0; k < N; k++) {

    if (proc_rank == k / R2) {

      time_start = clock();
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
      updateTimeCalc();

      time_start = clock();
      if (proc_rank != Q2-1) {
        MPI_Send(u, N+1, MPI_DOUBLE, 1, 123, MPI_COMM_WORLD);
      }
      updateTimeComm();

      // Applying u row for submatrix.
      time_start = clock();
      for (int i = row+1; i < R2; i++) {
        for (int j = k + 1; j < N+1; j++) {
          submatrix[i][j] -= submatrix[i][k] * u[j];
        }
        submatrix[i][k] = 0.;
      }
      updateTimeCalc();

      free(u);
    } else if (proc_rank > k / R2) {
      double* u = (double*) malloc((N+1) * sizeof(double));
      time_start = clock();
      MPI_Recv(u, N+1, MPI_DOUBLE, proc_rank-1, 123, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

      // Sending to the next process first.
      if (proc_rank < Q2-1) {
        // Translating the row further.
        MPI_Send(u, N+1, MPI_DOUBLE, proc_rank + 1, 123, MPI_COMM_WORLD);
      }
      updateTimeComm();

      // Applying u row for submatrix.
      time_start = clock();
      for (int i = 0; i < R2; i++) {
        for (int j = k + 1; j < N + 1; j++) {
          submatrix[i][j] -= submatrix[i][k] * u[j];
        }
        submatrix[i][k] = 0.;
      }
      updateTimeCalc();
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }
}

void runIndirectGauss() {
  for (int k = N-1; k>=1; k--) {
    for (int j = k-1; j>=0; j--) {
      B[j][N] -= B[j][k] * B[k][N];
      B[j][k] = 0;
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

  clock_t begin_time_total;
  if (proc_rank == ROOT) {
    begin_time_total = clock();
  }

  MPI_Barrier(MPI_COMM_WORLD);

  sscanf(argv[1], "%d", &N);

  if (N % Q2 != 0) {
    if (proc_rank == ROOT) {
      printf("Sorry, not supported. Consider changing matrix size / number of processes.\n");
    }
    return 0;
  }

  //  Q1 = (N - 1) / R1 + ((N-1)%R1 == 0 ? 0 : 1);
  // ?
  R2 = (N - 1) / Q2 + ((N-1)%Q2 == 0 ? 0 : 1);
  R2 = N / Q2;
  //  Q3 = N / R3 + (N%R3 == 0 ? 0 : 1);

  // printf("R2 %d  Q2  %d\n", R2, Q2);

  underSubmatrix = malloc(R2 * (N+1) * sizeof(double));
  submatrix = malloc(R2 * sizeof(double*));
  for (int i = 0; i < R2; i++) {
    submatrix[i] = underSubmatrix + i * (N+1);
  }

  // printf("[%d] what's wrong?\n", proc_rank);

  if (proc_rank == ROOT) {
    generateMatrix();
    //printMatrix(A, N);
    printf("Matrix is generated.\n");

    time_start = clock();
    for (int proc = 1; proc < Q2; proc++) {
      MPI_Send(A[R2*proc], R2 * (N+1), MPI_DOUBLE, proc, 345, MPI_COMM_WORLD);
    }
    updateTimeComm();
    for (int i = 0; i < R2; i++) {
      for (int j = 0; j < N+1; j++) {
        submatrix[i][j] = A[i][j];
      }
    }
  } else {
    // printf("[%d] receiving submatrix... \n", proc_rank);
    time_start = clock();
    MPI_Recv(underSubmatrix, R2 * (N+1), MPI_DOUBLE, ROOT, 345, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    updateTimeComm();
    // printf("[%d] submatrix received.\n", proc_rank);
  }

  MPI_Barrier(MPI_COMM_WORLD);

  runGauss(proc_rank);

  MPI_Barrier(MPI_COMM_WORLD);

  if (proc_rank == ROOT) {
    alloc_B();
    time_start = clock();
    for (int proc = 1; proc < Q2; proc++) {
      MPI_Recv(B[R2*proc], R2 * (N+1), MPI_DOUBLE, proc, 109, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    updateTimeComm();
    for (int i = 0; i < R2; i++) {
      for (int j = 0; j < N+1; j++) {
        B[i][j] = submatrix[i][j];
      }
    }
  } else {
    time_start = clock();
    MPI_Send(underSubmatrix, R2 * (N+1), MPI_DOUBLE, ROOT, 109, MPI_COMM_WORLD);
    updateTimeComm();
  }

  MPI_Barrier(MPI_COMM_WORLD);

  if (proc_rank == ROOT) {
    time_start = clock();
    runIndirectGauss();
    time_indirect_gauss = (double)(clock() - time_start);

    checkCorrectness();

    if (N <= 15) {
      printf("======\nTHE SOLUTION\n");
      for (int i = 0; i < N; i++) {
        /*for (int j = 0; j < N; j++) {
          printf("%f ", B[i][j]);
        }
        printf("| %f\n", B[i][N]);*/
        printf("%f ", B[i][N]);
      }
      printf("\n=======\n");
    }

    printf("TOTAL TIME: %fs\n", ((float)( clock () - begin_time_total ) /  CLOCKS_PER_SEC));
    printf("Indirect Gauss TIME: %fs\n", time_indirect_gauss /  CLOCKS_PER_SEC);
  }

  MPI_Barrier(MPI_COMM_WORLD);

  printf("[%d] total COMMUNICATION time:  %fs\n", proc_rank, time_communications / CLOCKS_PER_SEC);
  printf("[%d] total CALCULATIONS time:   %fs\n", proc_rank, time_calculations / CLOCKS_PER_SEC);

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
