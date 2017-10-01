//
//  MutationLab.hpp
//  tspGeneticAlgorithmCMD
//
//  Created by Matthew Mccrackin on 9/29/17.
//  Copyright © 2017 Matthew Mccrackin. All rights reserved.
//

#ifndef MutationLab_hpp
#define MutationLab_hpp

#include <stdio.h>
#include <iostream>
#include "Path.hpp"
#include "Coord.h"
#include <string>
#include <vector>

class MutationLab{
public:
    MutationLab();                                      // initialize the simulation
    void runTest();                                     // run the simulation
    ~MutationLab();                                     // destroy the simulation
private:
    Coord startingLocation;                             // location to start
    Coord * locationArr;                                // array of locations to visit
    int numLocations;                                   // the number of locations to visit
    std::vector<Path> myPaths;                          // our population vector
    void swapV(int a, int b, std::vector<Path>& myVec); // shift values in the population vector
    void permuteV(std::vector<Path>& myVec);            // permute values in the population vector
};



#endif /* MutationLab_hpp */
