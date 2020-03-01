//
//  main.cpp
//  MPI
//
//  Created by Aniket Bhushan on 01/03/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <mpi.h>
#include <cmath>

int main(int argc, char * argv[]) {

    MPI_Init(&argc, &argv);
    
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if (rank == 0)
    {
        int n;
        std::cout << "Enter a number : ";
        std::cin >> n;
        
        for (int i=1; i<size; ++i) {
            MPI_Send(&n, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        int n;
        MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << n << "^" << rank << " : " << std::pow(n, rank) << std::endl;
    }
    
    MPI_Finalize();
}
