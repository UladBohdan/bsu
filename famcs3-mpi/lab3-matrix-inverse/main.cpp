#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <mpi.h>

#include <iostream>

#define ROOT 0

using namespace std;

const int MAX_ABS_VALUE = 10;
const int MAX_MATRIX_SIZE_TO_SHOW = 5;
const int MAGIC_NUMBER = 576;
const double EPS = 1E-3;

void generateRandomMatrix(double**, int);
void readMatrixFromFile(double**, int, const char*);
double realtime();
void printMatrix(double**, int);
bool ensureMatrixIsInverse(double**, double**, int);

int main(int argc, char** argv) {
    if (argc > 3) {
        printf("wrong number of arguments: please, provide the size of a matrix and, optionally, a file with the matrix.\n");
        return 0;
    }
    int n;
    char* matrix_path = new char[0];
    sscanf(argv[1], "%d", &n);
    if (argc == 3) {
        matrix_path = argv[2];
    }

    double** a;
    double** b;
    double** raw;

    srand(time(NULL));

    double startTime;

    int rank, procCount;

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &procCount);

    a = new double*[n];
    for (int i = 0; i < n; i++) {
        a[i] = new double[n];
    }

    b = new double*[n];
    for (int i = 0; i < n; i++) {
        b[i] = new double[n];
        for (int j = 0; j < n; j++) {
            b[i][j] = (i == j ? 1 : 0);
        }
    }

    if (rank == ROOT) {
        if (strlen(matrix_path) == 0) {
            generateRandomMatrix(a, n);
        } else {
            readMatrixFromFile(a, n, matrix_path);
        }

        raw = new double*[n];
        for (int i = 0; i < n; i++) {
            raw[i] = new double[n];
            for (int j = 0; j < n; j++) {
                raw[i][j] = a[i][j];
            }
        }

        printMatrix(a, n);
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == ROOT) {
        startTime = realtime();
    }

    for (int i = 0; i < n; i++) {
        MPI_Bcast(a[i], n, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);
    }

    for (int i = 0; i < n; i++) {
        MPI_Bcast(b[i], n, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);
    }

    double* shared_a = new double[n];
    double* shared_b = new double[n];

    // Starting Gaussian elimination.
    for (int row = rank; row < n; row += procCount) {
        for (int rcv_row = 0; rcv_row < row; rcv_row++) {
            int rcv_from = rcv_row % procCount;

            MPI_Recv(shared_a, n, MPI_DOUBLE, rcv_from, rcv_row * n + row, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(shared_b, n, MPI_DOUBLE, rcv_from, rcv_row * n + row, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // subtracting every received row.
            double mult = a[row][rcv_row];

            for (int i = 0; i < n; i++) {
                shared_a[i] *= mult;
                shared_b[i] *= mult;
                a[row][i] -= shared_a[i];
                b[row][i] -= shared_b[i];
            }
        }

        for (int i = 0; i < n; i++) {
            shared_a[i] = a[row][i];
        }
        double div_on = shared_a[row];
        for (int col = 0; col < n; col++) {
            if (div_on == 0) {
                printf("\x1b[32mPANIC! DIVIDE ON 0!\x1b[0m\n");
                return 0;
            }
            shared_a[col] /= div_on;
            a[row][col] /= div_on;
            b[row][col] /= div_on;
            shared_b[col] = b[row][col];
        }

        for (int send_to_row = row + 1; send_to_row < n; send_to_row++) {
            MPI_Send(a[row], n, MPI_DOUBLE, send_to_row % procCount, row * n + send_to_row, MPI_COMM_WORLD);
            MPI_Send(shared_b, n, MPI_DOUBLE, send_to_row % procCount, row * n + send_to_row, MPI_COMM_WORLD);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    int start_from_row = n - 1;
    while (start_from_row % procCount != rank) {
        start_from_row--;
    }

    for (int row = start_from_row; row >= 0; row -= procCount) {
        for (int rcv_row = n - 1; rcv_row > row; rcv_row--) {
            int rcv_from = rcv_row % procCount;

            MPI_Recv(shared_a, n, MPI_DOUBLE, rcv_from, rcv_row * n + row, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(shared_b, n, MPI_DOUBLE, rcv_from, rcv_row * n + row, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // subtracting every received row.
            double mult = a[row][rcv_row];

            for (int i = 0; i < n; i++) {
                shared_a[i] *= mult;
                shared_b[i] *= mult;
                a[row][i] -= shared_a[i];
                b[row][i] -= shared_b[i];
            }
        }

        for (int i = 0; i < n; i++) {
            shared_a[i] = a[row][i];
        }
        double div_on = shared_a[row];
        for (int col = 0; col < n; col++) {
            if (div_on == 0) {
                printf("\x1b[32mPANIC! DIVIDE ON 0!\x1b[0m\n");
                return 0;
            }
            shared_a[col] /= div_on;
            a[row][col] /= div_on;
            b[row][col] /= div_on;
            shared_b[col] = b[row][col];
        }

        for (int send_to_row = row - 1; send_to_row >= 0; send_to_row--) {
            MPI_Send(a[row], n, MPI_DOUBLE, send_to_row % procCount, row * n + send_to_row, MPI_COMM_WORLD);
            MPI_Send(shared_b, n, MPI_DOUBLE, send_to_row % procCount, row * n + send_to_row, MPI_COMM_WORLD);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == ROOT) {
        for (int row = 0; row < n; row++) {
            if (row % procCount != ROOT) {
                MPI_Recv(b[row], n, MPI_DOUBLE, row % procCount, MAGIC_NUMBER, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            }
        }
        double duration = realtime() - startTime;
        printMatrix(b, n);
        printf("Ensuring if matrix is inverse...");
        bool succeed = ensureMatrixIsInverse(raw, b, n);
        printf("%s\n", (succeed ? "OK." : "FAILED."));
        printf("Time for elimination: \x1b[33m%lf sec.\x1b[0m\n", duration);
    } else {
        for (int row = 0; row < n; row++) {
            if (row % procCount != ROOT) {
                MPI_Send(b[row], n, MPI_DOUBLE, ROOT, MAGIC_NUMBER, MPI_COMM_WORLD);
            }
        }
    }

    MPI_Finalize();
    return 0;
}

bool ensureMatrixIsInverse(double** a, double** b, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j ++) {
            double sum = 0;
            for (int k = 0; k < n; k++) {
                sum += a[i][k] * b[k][j];
            }
            if ( (i == j && (fabs(sum - 1.) > EPS)) ||
                 (i != j && (fabs(sum - 0.) > EPS)) ) {
                     return false;
                 }
        }
    }
    return true;
}

void generateRandomMatrix(double** a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = rand() % MAX_ABS_VALUE - MAX_ABS_VALUE / 2;
        }
    }
}

void readMatrixFromFile(double** a, int n, const char* path) {
    FILE* file = fopen(path, "r");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%lf ", &a[i][j]);
        }
        fscanf(file, "\n");
    }
    fclose(file);
}

void printMatrix(double** a, int n) {
    if (n > MAX_MATRIX_SIZE_TO_SHOW) {
        printf("Matrix is too large to be printed\n");
    } else {
        printf("Matrix (size=%d):\n", n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                printf("%.3f ", a[i][j]);
            }
            printf("\n");
        }
    }
}

double realtime() {
    return double(clock()) / CLOCKS_PER_SEC;
}
