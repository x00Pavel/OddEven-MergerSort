#include <stdio.h>
#include "mpi/mpi.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void read_numbers(vector<int> *numbers){
    string filename("numbers");

    vector<int> bytes;
    int byte = 0;
    ifstream input_file(filename);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << filename << "'" << endl;
        return;
    }

    while (input_file.good()) {
        byte = input_file.get();
        if (!input_file.good()) break;

        numbers->push_back(byte);
    }

    input_file.close();
}

int main(int argc, char *argv[])
{
    int rank, size, num;
    int tag, a, b;
    char version[MPI_MAX_LIBRARY_VERSION_STRING];
    bool swap = true;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status status;

    if (rank == 0){
        vector<int> numbers;
        read_numbers(&numbers);
        for (const int i: numbers){
            cout << i << " ";
        }
        cout << endl;
        int dst;
        for (int i = 0; i < 8; i++){
            tag = i % 2; // if tag == 0 -> input a, tag == 1 -> input b
            dst = tag == 0 ? i + 1 : i; // if tag == 0 -> then processor is same as the next index, otherwise curent index 
            MPI_Send(&numbers[i], 1, MPI_INT, dst, tag, MPI_COMM_WORLD);
        }
        
        
        // for (int i = 0; i < 8; i++){
        //     tag = i % 2; // if tag == 0 -> input a, tag == 1 -> input b
        //     dst = tag == 0 ? i + 1 : i; // if tag == 0 -> then processor is same as the next index, otherwise curent index 
        //     MPI_Recv(&num, 1, MPI_INT, i );
        //     cout << num << endl;
        //     // MPI_Send(&numbers[i], 1, MPI_INT, dst, tag, MPI_COMM_WORLD);
        // }
        
        cout << "Waiting for response from 1 tag 0 processor" << endl;
        MPI_Recv(&num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &status);
        cout << num << endl;
        
        cout << "Waiting for response from 2 tag 0 processor" << endl;
        MPI_Recv(&num, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &status);
        cout << num << endl;
        
        cout << "Waiting for response from 2 tag 1 processor" << endl;
        MPI_Recv(&num, 1, MPI_INT, 2, 1, MPI_COMM_WORLD, &status);
        cout << num << endl;
        
        cout << "Waiting for response from 4 tag 0 processor" << endl;
        MPI_Recv(&num, 1, MPI_INT, 4, 0, MPI_COMM_WORLD, &status);
        cout << num << endl;
        
        cout << "Waiting for response from 4 tag 1 processor" << endl;
        MPI_Recv(&num, 1, MPI_INT, 4, 1, MPI_COMM_WORLD, &status);
        cout << num << endl;

        cout << "Waiting for response from 6 tag 0 processor" << endl;
        MPI_Recv(&num, 1, MPI_INT, 6, 0, MPI_COMM_WORLD, &status);
        cout << num << endl;
        
        cout << "Waiting for response from 6 tag 1 processor" << endl;
        MPI_Recv(&num, 1, MPI_INT, 6, 1, MPI_COMM_WORLD, &status);
        cout << num << endl;

        cout << "Waiting for response from 7 tag 1 processor" << endl;
        MPI_Recv(&num, 1, MPI_INT, 7, 1, MPI_COMM_WORLD, &status);
        cout << num << endl;
        

    } else if (rank == 7) {
        cout << "proc " << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        cout << "proc " << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        cout << "proc " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b){
            MPI_Send(&a, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
            MPI_Send(&b, 1, MPI_INT, 6, 1, MPI_COMM_WORLD);
        } else {
            MPI_Send(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
            MPI_Send(&a, 1, MPI_INT, 6, 1, MPI_COMM_WORLD);
        }


    } else if (rank == 1) {
        cout << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        cout << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        cout << "proc " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b){
            MPI_Send(&a, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
            MPI_Send(&b, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        } else {
            MPI_Send(&b, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
            MPI_Send(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    } else if (rank == 5) { // this is ods process -> send to even. If 1 or 7 -> loop back to itself 
        // receive from controll process 0
        cout << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        cout << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        cout << "proc " << rank << ": a = " << a << "; b = " << b << endl;

        if (a > b){
            MPI_Send(&a, 1, MPI_INT, 6, 0, MPI_COMM_WORLD);
            MPI_Send(&b, 1, MPI_INT, 4, 1, MPI_COMM_WORLD);
        } else {
            MPI_Send(&b, 1, MPI_INT, 6, 0, MPI_COMM_WORLD);
            MPI_Send(&a, 1, MPI_INT, 4, 1, MPI_COMM_WORLD);
        }

    } else if (rank == 3) { // even process
        cout << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        cout << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        cout << "proc " << rank << ": a = " << a << "; b = " << b << endl;
        
        if (a > b){
            MPI_Send(&a, 1, MPI_INT, 4, 0, MPI_COMM_WORLD);
            MPI_Send(&b, 1, MPI_INT, 2, 1, MPI_COMM_WORLD);
        } else {
            MPI_Send(&b, 1, MPI_INT, 4, 0, MPI_COMM_WORLD);
            MPI_Send(&a, 1, MPI_INT, 2, 1, MPI_COMM_WORLD);
        }
    
    } else if (rank == 2) { // even process
        cout << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        cout << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        cout << "proc " << rank << ": a = " << a << "; b = " << b << endl;
        
        if (a > b){
            MPI_Send(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Send(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        } else {
            MPI_Send(&a, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
            MPI_Send(&b, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }
    
    } else if (rank == 4) { // even process
        cout << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        cout << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        cout << "proc " << rank << ": a = " << a << "; b = " << b << endl;
        
        if (a > b){
            MPI_Send(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Send(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        } else {
            MPI_Send(&b, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Send(&a, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        }
    
    } else if (rank == 6) { // even process
        cout << rank << ": waiting on input a" << endl;
        MPI_Recv(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        cout << rank << ": waiting on input b" << endl;
        MPI_Recv(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
        cout << "proc " << rank << ": a = " << a << "; b = " << b << endl;
        
        if (a > b){
            MPI_Send(&a, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Send(&b, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        } else {
            MPI_Send(&b, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
            MPI_Send(&a, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
        }
    
    }

    MPI_Finalize();
    return 0;
}
