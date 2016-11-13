#include <mpi.h>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define ROOT 0

using namespace std;

const int MAX_ABS_VALUE = 1e7;
const int ARRAY_MAX_SIZE_TO_SHOW = 200;

int* generateRandomArray(int);
void printArray(int, int*, char*);
double realtime();

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("wrong number of arguments: please, provide the size of an array\n");
        return 0;
    }
    int sz = 0;
    sscanf(argv[1], "%d", &sz);

    int* a;

    srand(time(NULL));

    double startTime = realtime();

    int rank, procCount;

    MPI_Init(NULL, NULL);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &procCount);

    int childSize, rootSize;
    if (rank == ROOT) {
        a = generateRandomArray(sz);
        printArray(sz, a, (char*)"Generated array:\n");
    }

    childSize = sz / procCount;
    rootSize = sz / procCount + sz % procCount;

    MPI_Barrier(MPI_COMM_WORLD);

    int** part = new int*[procCount];
    part[0] = new int[rootSize];
    for (int p = 1; p < procCount; p++) {
        part[p] = new int[childSize];
    }

    if (rank == ROOT) {
        for (int i = 0; i < rootSize; i++) {
            part[0][i] = a[i];
        }
        for (int p = 1; p < procCount; p++) {
            MPI_Send(a + rootSize + childSize*(p-1), childSize, MPI_INT, p, 1, MPI_COMM_WORLD);
        }
    } else {
        for (int p = 1; p < procCount; p++) {
            MPI_Recv(part[p], childSize, MPI_INT, ROOT, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);

    if (rank == ROOT) {
        sort(part[0], part[0] + rootSize);

        for (int p = 1; p < procCount; p++) {
            MPI_Recv(part[p], childSize, MPI_INT, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        }

        int aPos = 0;
        int* pos = new int[procCount];
        int* size = new int[procCount];
        for (int p = 0; p < procCount; p++) {
            pos[p] = 0;
            size[p] = (p == 0 ? rootSize : childSize);
        }
        while (aPos != sz) {
            int mnPos = 0;
            for (int p = 1; p < procCount; p++) {
                if (pos[p] < size[p] && part[p][pos[p]] < part[mnPos][pos[mnPos]]) {
                    mnPos = p;
                }
            }
            a[aPos] = part[mnPos][pos[mnPos]];
            pos[mnPos]++;
            aPos++;
        }

        delete[] pos;
        delete[] size;

        double timeDiff = realtime() - startTime;

        printf("\n\e[1mCalculations finished successfully!\nNumber of processors: %d\nArray size: %d\nTime: %f\e[0m\n", procCount, sz, timeDiff);
        printArray(sz, a, (char*)"Sorted:\n");

    } else {
        sort(part[rank], part[rank] + childSize);
        MPI_Send(part[rank], childSize, MPI_INT, ROOT, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}

int* generateRandomArray(int n) {
    int* a = new int[n];
    for (int i=0; i<n; i++) {
        a[i] = rand()%MAX_ABS_VALUE - MAX_ABS_VALUE/2;
    }
    return a;
}

void printArray(int n, int* a, char* text = (char*)"") {
    if (n > ARRAY_MAX_SIZE_TO_SHOW) {
        return;
    }
    printf("%s", text);
    for (int i=0; i<n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

double realtime() {
    return double(clock()) / CLOCKS_PER_SEC;
}
