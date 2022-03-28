#include <stdio.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "mpi.h"

using namespace std;

void read_numbers(vector<int> *numbers) {
    string filename("numbers");

    vector<int> bytes;
    int byte = 0;
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '" << filename << "'" << endl;
        return;
    }

    while (input_file.good()) {
        byte = input_file.get();
        if (!input_file.good()) break;

        numbers->push_back(byte);
    }

    input_file.close();
}

int main(int argc, char *argv[]) {
    int rank, size, num;
    int tag, a, b;
    char version[MPI_MAX_LIBRARY_VERSION_STRING];
    bool swap = true;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;
    MPI_Request request;

    if (rank == 0) {
        vector<int> numbers;
        read_numbers(&numbers);
        for (const int i : numbers) {
            cout << i << " ";
        }
        cout << endl;

        MPI_Send(&numbers[0], 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(&numbers[1], 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
        MPI_Send(&numbers[2], 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
        MPI_Send(&numbers[3], 1, MPI_INT, 2, 1, MPI_COMM_WORLD);
        MPI_Send(&numbers[4], 1, MPI_INT, 3, 0, MPI_COMM_WORLD);
        MPI_Send(&numbers[5], 1, MPI_INT, 3, 1, MPI_COMM_WORLD);
        MPI_Send(&numbers[6], 1, MPI_INT, 4, 0, MPI_COMM_WORLD);
        MPI_Send(&numbers[7], 1, MPI_INT, 4, 1, MPI_COMM_WORLD);

        // cout << "Waiting for response from processor 11 tag 0" << endl;
        MPI_Recv(&num, 1, MPI_INT, 11, 0, MPI_COMM_WORLD, &status);
        cout << num << endl;

        // cout << "Waiting for response from 17 tag 0 processor" << endl;
        MPI_Recv(&num, 1, MPI_INT, 17, 0, MPI_COMM_WORLD, &status);
        cout << num << endl;

        // cout << "Waiting for response from processor 17 tag 1 " << endl;
        MPI_Recv(&num, 1, MPI_INT, 17, 1, MPI_COMM_WORLD, &status);
        cout << num << endl;

        // cout << "Waiting for response from processor 18 tag 0 " << endl;
        MPI_Recv(&num, 1, MPI_INT, 18, 0, MPI_COMM_WORLD, &status);
        cout << num << endl;

        // cout << "Waiting for response from processor 18 tag 1" << endl;
        MPI_Recv(&num, 1, MPI_INT, 18, 1, MPI_COMM_WORLD, &status);
        cout << num << endl;

        // cout << "Waiting for response from processor 19 tag 0" << endl;
        MPI_Recv(&num, 1, MPI_INT, 19, 0, MPI_COMM_WORLD, &status);
        cout << num << endl;

        // cout << "Waiting for response from processor 19 tag 1" << endl;
        MPI_Recv(&num, 1, MPI_INT, 19, 1, MPI_COMM_WORLD, &status);
        cout << num << endl;

        // cout << "Waiting for response from processor 14 tag 1" << endl;
        MPI_Recv(&num, 1, MPI_INT, 14, 1, MPI_COMM_WORLD, &status);
        cout << num << endl;

    } else if (rank == 1) {
        // cout << "processor " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b) {
            MPI_Isend(&a, 1, MPI_INT, 6, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 5, 0, MPI_COMM_WORLD, &request);
        } else {
            MPI_Isend(&a, 1, MPI_INT, 5, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 6, 0, MPI_COMM_WORLD, &request);
        }

    } else if (rank == 2) {  // even process
        // cout << "processor " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b) {
            MPI_Isend(&a, 1, MPI_INT, 6, 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 5, 1, MPI_COMM_WORLD, &request);
        } else {
            MPI_Isend(&a, 1, MPI_INT, 5, 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 6, 1, MPI_COMM_WORLD, &request);
        }

    } else if (rank == 3) {  // even process
        // cout << "processor " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b) {
            MPI_Isend(&a, 1, MPI_INT, 8, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 7, 0, MPI_COMM_WORLD, &request);
        } else {
            MPI_Isend(&a, 1, MPI_INT, 7, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 8, 0, MPI_COMM_WORLD, &request);
        }

    } else if (rank == 4) {  // even process
        // cout << "processor " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b) {
            MPI_Isend(&a, 1, MPI_INT, 8, 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 7, 1, MPI_COMM_WORLD, &request);
        } else {
            MPI_Isend(&a, 1, MPI_INT, 7, 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 8, 1, MPI_COMM_WORLD, &request);
        }

    } else if (rank == 5) {
        // cout << "processor " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 2, 1, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b) {
            MPI_Isend(&a, 1, MPI_INT, 9, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 11, 0, MPI_COMM_WORLD, &request);
        } else {
            MPI_Isend(&a, 1, MPI_INT, 11, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 9, 0, MPI_COMM_WORLD, &request);
        }

    } else if (rank == 6) {  // even process
        // cout << "processor " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 2, 1, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b) {
            MPI_Isend(&a, 1, MPI_INT, 14, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 9, 1, MPI_COMM_WORLD, &request);
        } else {
            MPI_Isend(&a, 1, MPI_INT, 9, 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 14, 0, MPI_COMM_WORLD, &request);
        }

    } else if (rank == 7) {
        // cout << "processor " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 3, 0, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 4, 1, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b) {
            MPI_Isend(&a, 1, MPI_INT, 10, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 11, 1, MPI_COMM_WORLD, &request);
        } else {
            MPI_Isend(&a, 1, MPI_INT, 11, 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 10, 0, MPI_COMM_WORLD, &request);
        }
    } else if (rank == 8) {
        // cout << "processor " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 3, 0, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 4, 1, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b) {
            MPI_Isend(&a, 1, MPI_INT, 14, 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 10, 1, MPI_COMM_WORLD, &request);
        } else {
            MPI_Isend(&a, 1, MPI_INT, 10, 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 14, 1, MPI_COMM_WORLD, &request);
        }
    } else if (rank == 9) {
        // cout << "processor " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 5, 0, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 6, 1, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b) {
            MPI_Isend(&a, 1, MPI_INT, 12, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 13, 0, MPI_COMM_WORLD, &request);
        } else {
            MPI_Isend(&a, 1, MPI_INT, 13, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 12, 0, MPI_COMM_WORLD, &request);
        }
    } else if (rank == 10) {
        // cout << "processor " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 7, 0, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 8, 1, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b) {
            MPI_Isend(&a, 1, MPI_INT, 12, 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 13, 1, MPI_COMM_WORLD, &request);
        } else {
            MPI_Isend(&a, 1, MPI_INT, 13, 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 12, 1, MPI_COMM_WORLD, &request);
        }
    } else if (rank == 11) {
        // cout << "processor " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 5, 0, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 7, 1, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b) {
            MPI_Isend(&a, 1, MPI_INT, 15, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        } else {
            MPI_Isend(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 15, 0, MPI_COMM_WORLD, &request);
        }
    } else if (rank == 12) {
        // cout << "processor " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 9, 0, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 10, 1, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b) {
            MPI_Isend(&a, 1, MPI_INT, 19, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 15, 1, MPI_COMM_WORLD, &request);
        } else {
            MPI_Isend(&a, 1, MPI_INT, 15, 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 19, 0, MPI_COMM_WORLD, &request);
        }
    } else if (rank == 13) {
        // cout << "processor " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 9, 0, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 10, 1, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b) {
            MPI_Isend(&a, 1, MPI_INT, 16, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 17, 1, MPI_COMM_WORLD, &request);
        } else {
            MPI_Isend(&a, 1, MPI_INT, 17, 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 16, 0, MPI_COMM_WORLD, &request);
        }
    } else if (rank == 14) {
        // cout << "processor " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 6, 0, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 8, 1, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b) {
            MPI_Isend(&a, 1, MPI_INT, 10, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 11, 1, MPI_COMM_WORLD, &request);
        } else {
            MPI_Isend(&a, 1, MPI_INT, 16, 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
        }
    } else if (rank == 15) {
        // cout << "processor " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 11, 0, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 12, 1, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b) {
            MPI_Isend(&a, 1, MPI_INT, 18, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 17, 0, MPI_COMM_WORLD, &request);
        } else {
            MPI_Isend(&a, 1, MPI_INT, 17, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 18, 0, MPI_COMM_WORLD, &request);
        }
    } else if (rank == 16) {
        // cout << "processor " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 13, 0, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 14, 1, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b) {
            MPI_Isend(&a, 1, MPI_INT, 19, 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 18, 1, MPI_COMM_WORLD, &request);
        } else {
            MPI_Isend(&a, 1, MPI_INT, 18, 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 19, 1, MPI_COMM_WORLD, &request);
        }
    } else if (rank == 17) {
        // cout << "processor " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 15, 0, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 13, 1, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b) {
            MPI_Isend(&a, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        } else {
            MPI_Isend(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
        }
    } else if (rank == 18) {
        // cout << "processor " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 15, 0, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 16, 1, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b) {
            MPI_Isend(&a, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        } else {
            MPI_Isend(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
        }
    } else if (rank == 19) {
        // cout << "processor " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 12, 0, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 16, 1, MPI_COMM_WORLD, &status);
        // cout << "processor " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b) {
            MPI_Isend(&a, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
        } else {
            MPI_Isend(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);
            MPI_Isend(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
        }
    }
    MPI_Finalize();
    return 0;
}
