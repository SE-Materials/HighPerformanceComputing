//
//  main.cpp
//  WorkSharing
//
//  Created by Aniket Bhushan on 29/02/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <omp.h>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>

int GetRandomValue()
{
    static int i = 0;
    return i++;
}

void parallelizeFor()
{
    long long size = 1000000000;
    std::vector<int> a, b, result;
    a.reserve(size);
    b.reserve(size);
    result.reserve(size);
    
    std::generate(a.begin(), a.end(), GetRandomValue);
    std::generate(b.begin(), b.end(), GetRandomValue);
    std::generate(result.begin(), result.end(), GetRandomValue);
    
    const auto start = std::chrono::steady_clock::now();
    
    omp_set_num_threads(10);
#pragma omp parallel for
    for (int i=0; i<size; ++i) {
        result[i] = a[i] + b[i];
    }
    
    const std::chrono::duration<double> dur = std::chrono::steady_clock::now() - start;
    std::cout << "Time for summation : " << dur.count() << " seconds." << std::endl;
}

// Assign different code blocks to different threads
void Sections()
{
    long long size = 1000000000;
    std::vector<int> a, b, result;
    a.reserve(size);
    b.reserve(size);
    result.reserve(size);
    
#pragma omp parallel sections
    {
#pragma omp section
        {
            for (int i=0; i<size; ++i) {
                a[i] = GetRandomValue();
            }
        }
        
#pragma omp section
        {
            for (int i=0; i<size; ++i) {
                b[i] = GetRandomValue();
            }
        }
    }
    
}

void SingleMaster()
{
#pragma omp parallel
    {
#pragma omp single
        printf("Gathering input : %d\n", omp_get_num_threads());
        
        printf("In parallel : %d\n", omp_get_thread_num());
        
#pragma omp master
        printf("Output on : %d", omp_get_thread_num());
    }
}

void Barrier()
{
#pragma omp parallel
    {
#pragma omp single
        printf("Gathering input on %d: %d\n", omp_get_thread_num(), omp_get_num_threads());
        
        printf("In parallel : %d\n", omp_get_thread_num());
#pragma omp barrier
        
#pragma omp master
        printf("Output on : %d\n", omp_get_thread_num());
    }
}

int main(int argc, const char * argv[]) {
    // parallelizeFor();
    // Sections();
    // SingleMaster();
    Barrier();
    return 0;
}
