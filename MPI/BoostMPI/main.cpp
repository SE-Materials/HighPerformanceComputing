//
//  main.cpp
//  BoostMPI
//
//  Created by Aniket Bhushan on 01/03/20.
//  Copyright © 2020 Aniket Bhushan. All rights reserved.
//

#include <iostream>
#include <boost/mpi.hpp>
#include <string>
#include <boost/serialization/serialization.hpp>


struct Person {
    int age;
    std::string name;
    
    friend boost::serialization::access;
    
    template <typename Ar>
    void serialize(Ar& ar, const unsigned int version)
    {
        ar& age;
        ar& name;
    }
};

int main(int argc, const char * argv[]) {
    namespace mpi = boost::mpi;
    
    mpi::environment env;
    mpi::communicator world;
    
    if (world.rank() == 0)
    {
        Person p{89, "Aniket"};
        for (int i=1; i<world.size(); ++i) {
            world.send(i, 0, p);
        }
    }
    else
    {
        Person p;
        world.recv(0, 0, p);
        std::cout << "Hello : " << p.name << std::endl;
    }
    return 0;
}
