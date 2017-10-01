//
//  main.cpp
//  tspGeneticAlgorithmCMD
//
//  Created by Matthew Mccrackin on 9/29/17.
//  Copyright © 2017 Matthew Mccrackin. All rights reserved.
//

#include <iostream>
#include "MutationLab.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, welcome to the TSP Genetic Solver!\n";
    MutationLab * myLab = new MutationLab;
    myLab->runTest();
    return 0;
}
