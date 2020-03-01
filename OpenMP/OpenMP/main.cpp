//
//  main.cpp
//  OpenMP
//
//  Created by Aniket Bhushan on 29/02/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <omp.h>


void hello_openmp()
{
    omp_set_num_threads(8);
#pragma omp parallel
    {
#pragma omp critical
        std::cout << omp_get_thread_num() << "/" << omp_get_num_threads() <<  " : Hello world" << std::endl;
    }
}

int main(int argc, const char * argv[]) {
    hello_openmp();
    return 0;
}
