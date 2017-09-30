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
    MutationLab();
    void runTest();
    ~MutationLab();
private:
    Coord startingLocation;
    Coord * locationArr;
    int numLocations;
    std::vector<Path> myPaths;
    void swapV(int a, int b, std::vector<Path>& myVec);
    void permuteV(std::vector<Path>& myVec);
};



#endif /* MutationLab_hpp */
