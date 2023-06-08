#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
    int rank;
    int sendarray[8][6];
    int recvarray[8][6];
    MPI_Datatype vector, vector2;


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Initialize arrays
    if (rank == 0) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 6; j++) {
                sendarray[i][j] = (i + 1) * 10 + j + 1;
            }
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 6; j++) {
            recvarray[i][j] = 0;
        }
    }

    if (rank == 0) {
        printf("Data in rank 0\n");
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 6; j++) {
                printf("%3d", sendarray[i][j]);
            }
            printf("\n");
        }
    }

    // Create datatype
    MPI_Type_vector(8, 1, 6, MPI_INT, &vector);
    MPI_Type_create_resized(vector, 0, sizeof(int), &vector2);
    MPI_Type_commit(&vector2);

    // Send two columns of matrix
    if (rank == 0)
        MPI_Send(&sendarray[0][0], 2, vector2, 1, 0, MPI_COMM_WORLD);
    else if (rank == 1)
        MPI_Recv(&recvarray[0][0], 2, vector2, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MPI_Type_free(&vector2);

    if (rank == 1) {
        printf("Received data\n");
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 6; j++) {
                printf("%3d", recvarray[i][j]);
            }
            printf("\n");
        }
    }

    MPI_Finalize();

    return 0;
}
