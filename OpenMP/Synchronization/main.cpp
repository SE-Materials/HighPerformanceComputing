//
//  main.cpp
//  Synchronization
//
//  Created by Aniket Bhushan on 29/02/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <omp.h>
#include <chrono>
#include <random>
#include <vector>

constexpr long long size = 100000000;

void Atomic()
{
    std::vector<int> randValues;
    unsigned long long sum = 0;
    
    randValues.reserve(size);
    
    // random values
    std::random_device seed;
    std::mt19937 engine(seed());
    std::uniform_int_distribution<> uniformDist(1, 10);
    for (long long i=0; i<size; ++i) {
        randValues.push_back(uniformDist(engine));
    }
    
    const auto start = std::chrono::steady_clock::now();
    
#pragma omp parallel for num_threads(150)
    for (int i=0; i<size; ++i) {
#pragma omp atomic
        sum += randValues[i];
    }
    
    const std::chrono::duration<double> duration = std::chrono::steady_clock::now() - start;
    std::cout << "Took " << duration.count() << " seconds. sum : " << sum << std::endl;
}

void Ordered()
{
    std::vector<int> squares;
    
#pragma omp parallel for ordered
    for (int i=1; i<=20; ++i)
    {
        printf("%d : %d\t", omp_get_thread_num(), i);
        int j = i*i;
        
#pragma omp ordered
            squares.push_back(j);
    }
    
    printf("\n");
    for (auto n : squares)
    {
        printf("%d\t", n);
    }
}

void SingleMaster()
{
#pragma omp parallel
    {
#pragma omp single nowait
        {
            int n;
            std::cin >> n;
            printf("Gathering input on %d\n", omp_get_thread_num());
        }
        
        printf("In parallel on %d\n", omp_get_thread_num());
        
#pragma omp barrier
        
#pragma omp master
        printf("Output on %d\n", omp_get_thread_num());
    }
}

int main(int argc, const char * argv[]) {
    // Atomic();
    // Ordered();
    SingleMaster();
    return 0;
}
