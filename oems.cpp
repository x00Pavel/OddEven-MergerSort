#include <stdio.h>
#include <mpi.h>



int main(int argc, char *argv[])
{
    int rank, size;
    char version[MPI_MAX_LIBRARY_VERSION_STRING];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    printf("Hello, world, I am %d of %d\n", rank, size);
    
    MPI_Finalize();
    return 0;
}
