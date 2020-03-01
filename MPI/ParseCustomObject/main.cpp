//
//  main.cpp
//  ParseCustomObject
//
//  Created by Aniket Bhushan on 01/03/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <mpi.h>
#include <string>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <sstream>

struct Person {
    int age;
    std::string name;
    
    friend class boost::serialization::access;
    
    template <typename Ar>
    void serialize(Ar& ar, const unsigned int version)
    {
        ar& name;
        ar& age;
    }
};

int main(int argc, char * argv[]) {
    MPI_Init(&argc, &argv);
    
    int size, rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if (rank == 0)
    {
        Person p{5000, "Aniket"};
        
        std::ostringstream ofs;
        boost::archive::text_oarchive ar(ofs);
        ar << p;
        
        auto str = ofs.str();
        std::cout << str << " from : " << rank << std::endl;
        
        for (int i=1; i<size; ++i) {
            MPI_Send(str.c_str(), (int)str.size()+1, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Status status;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        
        int count;
        MPI_Get_count(&status, MPI_CHAR, &count);
        
        char* buffer = new char[count];
        MPI_Recv(&buffer, count, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        
        std::istringstream iss(buffer);
        boost::archive::text_iarchive ar(iss);
        Person p;
        ar >> p;
        
        delete [] buffer;
    }
    
    MPI_Finalize();
    return 0;
}
