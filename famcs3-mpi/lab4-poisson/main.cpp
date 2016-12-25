#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <mpi.h>

#include <iostream>

#define ROOT 0

using namespace std;

const double EPS = 1E-6;
const double MPI_MAGIC_TAG = 999991;

// Defining my problem:
double a = 1;
double b = 1;

double f1(double y) { return y*y;       }
double f2(double y) { return y;         }
double f3(double x) { return sin(x);    }
double f4(double x) { return x;         }

double f(double x, double y) { return x * y; }

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("wrong number of arguments: please, provide number of rows and number of columns of the grid.\n");
        return 0;
    }

    int rows;
    sscanf(argv[1], "%d", &rows);
    int cols;
    sscanf(argv[1], "%d", &cols);

    double hx = a / cols;
    double hy = b / rows;

    double startTime;

    int rank, procCount;

    cout << "using 1d topology..." << endl;

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &procCount);

    double** a = new double*[rows];
    for (int i = 0; i < rows; i++) {
        a[i] = new double[cols];
    }

    if (rank == ROOT) {
        // First matrix approximation.
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                a[i][j] = f(hx * i, hy * j);
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        MPI_Bcast(a[i], cols, MPI_DOUBLE, ROOT, MPI_COMM_WORLD);
    }

    if (rank == ROOT) {
        for (int row = 0; row < rows; row++) {
            if (row % procCount != rank) {
                MPI_Send(a[row], cols, MPI_DOUBLE, row % procCount, MPI_MAGIC_TAG, MPI_COMM_WORLD);
            }
        }
    } else {

    }

    MPI_Finalize();
    return 0;
}

double realtime() {
    return double(clock()) / CLOCKS_PER_SEC;
}
