#include <mpi.h>

#include <iostream>
#include <fstream>
#include <iomanip>

#include <ctime>
#include <cassert>
#include <vector>
#include <cmath>

#define ROOT 0

using namespace std;

void printGrid(vector<vector<double> >&, char*);
double current_time();

// Defining the problem.
double a = 1;   // width, by x.
double b = 1;   // height, by y.

double f1(double y) { return y*y;       }   // left
double f2(double y) { return y;         }   // right
double f3(double x) { return sin(x);    }   // bottom
double f4(double x) { return x;         }   // top

double f(double x, double y) { return x * y; }
// End of definition.

const double EPS = 1E-6;

struct Point {
    double x, y;

    Point(double _x, double _y) : x(_x), y(_y) {
    }
};

struct Area {
    long top, right, bottom, left;

    Area() {}

    Area(long _top, long _right, long _bottom, long _left)
            : top(_top), right(_right), bottom(_bottom), left(_left) {
    }
};

struct GridArea{
    long rows, rows_offset, columns, columns_offset;
};

class Grid {
 private:
    double step_x, step_y, sqr_step_x, sqr_step_y, weight, residual;
    long rows, columns;
    vector <vector<double> > inner_lines;
    unique_ptr<double[]>
            top_border, adj_top_border,
            right_border, adj_right_border,
            bottom_border, adj_bottom_border,
            left_border, adj_left_border;

    Area area, calc_area, world_area;
    Point left_top;

 public:
    Grid(Area _world_area, Area _area, Point _left_top, double _step_x, double _step_y)
            : world_area(_world_area), area(_area), left_top(_left_top),
              step_x(_step_x), step_y(_step_y) {
        rows = area.bottom - area.top;
        columns = area.right - area.left;

        auto to_number = [](bool a) { return static_cast<long>(a); };

        calc_area.top = to_number(area.top == world_area.top);
        calc_area.left = to_number(area.left == world_area.left);
        calc_area.right = columns - to_number(area.right == world_area.right);
        calc_area.bottom = rows - to_number(area.bottom == world_area.bottom);

        auto allocate_zeros = [](long n) {
            auto ptr = new double[n];
            std::fill_n(ptr, n, 0);
            return ptr;
        };

        if (rows > 0 && columns > 0) {
            sqr_step_x = step_x * step_x;
            sqr_step_y = step_y * step_y;
            // weight = 1 / ( 2 * (1/hx^2 + 1/hy^2) )
            weight = 1. / (2 * (1. / sqr_step_x + 1. / sqr_step_y));

            top_border.reset(allocate_zeros(columns));
            left_border.reset(allocate_zeros(rows));
            bottom_border.reset(allocate_zeros(columns));
            right_border.reset(allocate_zeros(rows));

            if (area.top != world_area.top) {
                adj_top_border.reset(allocate_zeros(columns));
            } else {
                for (long j = 0; j < columns; ++j) {
                    set(0, j, f4(left_top.x + step_x * j));
                }
            }

            if (area.bottom != world_area.bottom) {
                adj_bottom_border.reset(allocate_zeros(columns));
            } else {
                for (long j = 0; j < columns; ++j) {
                    set(rows - 1, j, f3(left_top.x + step_x * j));
                }
            }

            if (area.left != world_area.left) {
                adj_left_border.reset(allocate_zeros(rows));
            } else {
                for (long i = 0; i < rows; ++i) {
                    set(i, 0, f1(left_top.y + step_y * i));
                }
            }

            if (area.right != world_area.right) {
                adj_right_border.reset(allocate_zeros(rows));
            } else {
                for (long i = 0; i < rows; ++i) {
                    set(i, columns - 1, f2(left_top.y + step_y * i));
                }
            }
        }

        if (rows > 2 && columns > 2) {
            inner_lines.resize(rows - 2);
            for (auto &it : inner_lines) {
                it.resize(columns - 2, 0);
            }
        }
    }

    double get(long i, long j) {
        if (j == -1) {
            return adj_left_border[i];
        } else if (j == columns) {
            return adj_right_border[i];
        } else if (i == -1) {
            return adj_top_border[j];
        } else if (i == rows) {
            return adj_bottom_border[j];
        } else if (j == 0) {
            return left_border[i];
        } else if (j == columns - 1) {
            return right_border[i];
        } else if (i == 0) {
            return top_border[j];
        } else if (i == rows - 1) {
            return bottom_border[j];
        } else {
            return inner_lines[i - 1][j - 1];
        }
    }

    void set(long i, long j, double value) {
        if (j == -1) {
            adj_left_border[i] = value;
        } else if (j == columns) {
            adj_right_border[i] = value;
        } else if (i == -1) {
            adj_top_border[j] = value;
        } else if (i == rows) {
            adj_bottom_border[j] = value;
        } else {
            if (j == 0) {
                left_border[i] = value;
            }
            if (j == columns - 1) {
                right_border[i] = value;
            }
            if (i == 0) {
                top_border[j] = value;
            }
            if (i == rows - 1) {
                bottom_border[j] = value;
            }
            if (i > 0 && i < rows - 1 && j > 0 && j < columns - 1) {
                inner_lines[i - 1][j - 1] = value;
            }
        }
    }

    void calculate() {
        /*if (DEBUG) {
            printf("Calculating: top: %ld, left: %ld,"
                " bottom: %ld, right: %ld\n",
                calc_area.top, calc_area.left,
                calc_area.bottom, calc_area.right);
        }*/

        residual = 0;
        for (long i = calc_area.top; i < calc_area.bottom; ++i) {
            for (long j = calc_area.left; j < calc_area.right; ++j) {
                double x = left_top.x + j * step_x;
                double y = left_top.y + i * step_y;
                double value = weight * (
                    (get(i + 1, j) + get(i - 1, j)) / sqr_step_x +
                    (get(i, j + 1) + get(i, j - 1)) / sqr_step_y - f(x, y));
                residual = max(residual, std::abs(value - get(i, j)));
                set(i, j, value);
            }
        }
    }

    double get_residual() {
        return residual;
    }

    double* get_value() {
        auto ptr = new double[rows * columns];
        for (long i = 0; i < rows; ++i) {
            for (long j = 0; j < columns; ++j) {
                ptr[i * columns + j] = get(i, j);
            }
        }
        return std::move(unique_ptr < double[]> (ptr)).get();
    }

    void communicate(MPI_Comm const &communicator) {
        MPI_Status status;
        int top, right, bottom, left;
        MPI_Cart_shift(communicator, 1, 1, &left, &right);
        MPI_Cart_shift(communicator, 0, 1, &top, &bottom);

        /*if (DEBUG) {
            printf("Exchanging data with top: %d, right: %d,"
                " bottom: %d, left: %d\n", top, right, bottom, left);
        }*/

        if (top != MPI_PROC_NULL) {
            MPI_Send(top_border.get(), columns, MPI_DOUBLE, top, 0, communicator);
        }
        if (bottom != MPI_PROC_NULL) {
            MPI_Recv(adj_bottom_border.get(), columns, MPI_DOUBLE, bottom,
                MPI_ANY_TAG, communicator, &status);
        }

        if (bottom != MPI_PROC_NULL) {
            MPI_Send(bottom_border.get(), columns, MPI_DOUBLE, bottom, 0, communicator);
        }
        if (top != MPI_PROC_NULL) {
            MPI_Recv(adj_top_border.get(), columns, MPI_DOUBLE, top,
                MPI_ANY_TAG, communicator, &status);
        }

        if (right != MPI_PROC_NULL) {
            MPI_Send(right_border.get(), rows, MPI_DOUBLE, right, 0, communicator);
        }
        if (left != MPI_PROC_NULL) {
            MPI_Recv(adj_left_border.get(), rows, MPI_DOUBLE, left,
                MPI_ANY_TAG, communicator, &status);
        }

        if (left != MPI_PROC_NULL) {
            MPI_Send(left_border.get(), rows, MPI_DOUBLE, left, 0, communicator);
        }
        if (right != MPI_PROC_NULL) {
            MPI_Recv(adj_right_border.get(), rows, MPI_DOUBLE, right,
                MPI_ANY_TAG, communicator, &status);
        }

        MPI_Barrier(communicator);
    }
};

int main(int argc, char **argv) {
    if (argc != 4) {
        printf("Wrong number of arguments: please, provide number of rows and number of columns of the grid and name of the file for output.\n");
        return 0;
    }

    int rank, procCount;
    int procRows, procColumns;
    long rows, columns;
    char filename[100];

    sscanf(argv[1], "%ld", &rows);
    sscanf(argv[2], "%ld", &columns);
    strcpy(filename, argv[3]);

    MPI_Status status;

    double start_time;

    cout.precision(5);
    cout << fixed;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &procCount);

    procColumns = static_cast<int>(sqrt(procCount));
    while (procColumns > 1 && procCount % procColumns != 0) {
        procColumns--;
    }

    assert(procCount % procColumns == 0);
    procRows = procCount / procColumns;

    if (rank == ROOT) {
        std::cout << "using 1D topology" << std::endl;
    }

    start_time = current_time();
    int dimensions[2] = {procRows, procColumns};
    int periods[2] = {0, 0};
    int coordinates[2];
    MPI_Comm communicator;

    MPI_Cart_create(MPI_COMM_WORLD, 2, dimensions, periods, 1, &communicator);
    MPI_Cart_coords(communicator, rank, 2, coordinates);

    double step_x = a / (columns - 1);
    double step_y = -b / (rows - 1);

    long first_columns = columns / procColumns + columns % procColumns;
    long other_columns = columns / procColumns;
    long first_rows = rows / procRows + rows % procRows;
    long other_rows = rows / procRows;

    int process_i = coordinates[0];
    int process_j = coordinates[1];

    auto calculate_area = [&](int i, int j) {
        long columns_offset = process_j == 0 ? 0 : first_columns +
            (process_j - 1) * other_columns;
        long rows_offset = process_i == 0 ? 0 : first_rows +
            (process_i - 1) * other_rows;
        long columns = process_j == 0 ? first_columns : other_columns;
        long rows = process_i == 0 ? first_rows : other_rows;
        return GridArea{rows, rows_offset, columns, columns_offset};
    };

    auto ca = calculate_area(process_i, process_j);
    double left_top_x = ca.columns_offset == 0 ?
        0 : step_x * ca.columns_offset;
    double left_top_y = ca.rows_offset == 0 ?
        b : b + step_y * ca.rows_offset;

    Point point(left_top_x, left_top_y);
    Area world_area(0, columns, rows, 0);
    Area area(ca.rows_offset, ca.columns_offset + ca.columns,
              ca.rows_offset + ca.rows, ca.columns_offset);
    Grid grid(world_area, area, point, step_x, step_y);

    /*if (DEBUG) {
        printf("\nParameters for process #%d\n", rank);
        printf("\tprocess_i: %d\n\tprocess_j: %d\n", process_i, process_j);
        printf("\tarea.top: %ld\n\tarea.left: %ld\n\t"
            "area.right: %ld\n\tarea.bottom: %ld\n",
            area.top, area.left, area.right, area.bottom);
        printf("\tleft_top.x: %f\n\tleft_top.y: %f\n\n", point.x, point.y);
    }*/

    MPI_Barrier(communicator);

    double max_residual = numeric_limits<double>::infinity();
    long num_iterations = 0;

    while (max_residual > EPS) {
        grid.communicate(communicator);
        grid.calculate();
        num_iterations += 1;
        double residual = grid.get_residual();
        MPI_Allreduce(&residual, &max_residual, 1, MPI_DOUBLE, MPI_MAX, communicator);
    }

    if (rank == ROOT) {
        vector <vector<double> > answer(rows, vector<double>(columns, 0));

        for (long i = 0; i < ca.rows; ++i) {
            for (long j = 0; j < ca.columns; ++j) {
                answer[i][j] = grid.get(i, j);
            }
        }

        for (long i = 1; i < procCount; ++i) {
            MPI_Cart_coords(communicator, i, 2, coordinates);
            process_i = coordinates[0];
            process_j = coordinates[1];

            ca = calculate_area(process_i, process_j);

            unique_ptr<double[]> ptr(new double[ca.rows * ca.columns]);
            MPI_Recv(ptr.get(), ca.rows * ca.columns, MPI_DOUBLE, i,
                MPI_ANY_TAG, communicator, &status);

            for (long i = 0; i < ca.rows; ++i) {
                for (long j = 0; j < ca.columns; ++j) {
                    long a_i = ca.rows_offset + i;
                    long a_j = ca.columns_offset + j;
                    answer[a_i][a_j] = ptr[i * ca.columns + j];
                }
            }
        }

        double end_time = current_time();

        printGrid(answer, filename);

        printf("\nDone!\n");
        printf("Number of iterations: %.ld\n", num_iterations);
        printf("Time: %.3lfs\n", end_time - start_time);

    } else {
        MPI_Send(grid.get_value(), ca.columns * ca.rows,
            MPI_DOUBLE, ROOT, 0, communicator);
    }

    MPI_Finalize();
}

void printGrid(vector<vector<double> >& grid, char* filename) {
    // to file.
    ofstream fout(filename);
    for (auto &row : grid) {
        for (auto &el : row) {
            fout << el << ' ';
        }
        fout << endl;
    }
    fout << endl;
    fout.close();
    // to console.
    if (grid.size() < 20 && grid[0].size() < 20) {
        cout << endl;
        for (auto &row : grid) {
            for (auto &el : row) {
                cout << std::setw(8) << std::setfill(' ') << el;
            }
            cout << endl;
        }
        cout << endl;
    } else {
        cout << "Answer is too large to be printed." << endl;
    }
}

double current_time() {
    return clock() * 1. / CLOCKS_PER_SEC;
}
