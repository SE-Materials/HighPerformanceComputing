//
//  main.cpp
//  DataSharing
//
//  Created by Aniket Bhushan on 01/03/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <omp.h>

void DataSharing()
{
    int i = 10;
    
//#pragma omp parallel for ;// this will use global i
//#pragma omp parallel for private(i) // private per thread, initial value of i is random here
//#pragma omp parallel for firstprivate(i) // private per thread and initialize with the above value
#pragma omp parallel for lastprivate(i) // random init value, but store the final value of i to the global
    for (int a=0; a<10; ++a) {
        
#pragma omp critical
        {
            printf("For thread %d, i = %d\n", omp_get_thread_num(), i);
            i = 1000 + omp_get_thread_num();
        }
    }
    
    printf("i : %d", i);
    
}

int main(int argc, const char * argv[]) {
    DataSharing();
    return 0;
}
