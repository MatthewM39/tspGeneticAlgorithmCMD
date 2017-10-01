//
//  MutationLab.cpp
//  tspGeneticAlgorithmCMD
//
//  Created by Matthew Mccrackin on 9/29/17.
//  Copyright © 2017 Matthew Mccrackin. All rights reserved.
//

#include "MutationLab.hpp"
#include <time.h>
#include <algorithm>
#include <stdlib.h>

MutationLab::MutationLab(){
    srand(time(NULL));          // seed the rand for a path
    std::cout << "Enter starting coord Name, X value, and Y value separated by spaces: ";
    std::cin >> startingLocation.name >> startingLocation.x >> startingLocation.y;
    std:: cout << "Enter number of locations to visit: ";
    std::cin >> numLocations;
    locationArr = new Coord[numLocations];
    std:: cout << "For each location, enter the Name, X value, and Y value separated by spaces!\n";
    for(int i = 0; i < numLocations; i++){
        std::cout << i + 1 << ": ";
        std::cin >> locationArr[i].name >> locationArr[i].x >> locationArr[i].y;    // get the places to visit
    }
}

void MutationLab::runTest(){
    int conditions[8];  // mutation values to pass to the population
    int population;     // size of the population
    int fitnessRate;    // percentage to pass on to next generation 1-99
    int unfitRate;      // percentage to pass on for the unfit 0-99
    int crossVals[2];   // crossover values to pass
    int rate;           // the rate that are fit
    std::cout << "Enter number of cross chains: ";
    std::cin >> crossVals[0];
    std::cout << "Enter length of cross chains: ";
    std::cin >> crossVals[1];
    std::cout << "Enter population number: ";
    std::cin >> population;
    std::cout << "Enter fitness rate: ";
    std::cin >> rate;
    std::cout << "Enter non-fit generation rate: ";
    std::cin >> unfitRate;
    std::cout << "Enter number of standard mutations, chance of standard mutations: ";
    std::cin >> conditions[0] >> conditions[1];
    std::cout << "Enter number of swap mutations, chance of swap mutations, and chain length: ";
    std::cin >> conditions[2] >> conditions[3] >> conditions[4];
    std::cout << "Enter number of inverse mutations, chance of inverse mutations, and chain length: ";
    std::cin >> conditions[5] >> conditions[6] >> conditions[7];
    Path * max = new Path(numLocations, locationArr, startingLocation, conditions, crossVals);
    for(int i = 0; i < population; i++){
        myPaths.emplace_back(Path(numLocations, locationArr, startingLocation, conditions, crossVals));     // populate
    }
    
    std::cout << "\n";      // now shift to working on generations...
    int i = 0;
    while(myPaths.size() > 2){
        std::cout << "Completed generation " << i << "\n";
        i++;
        fitnessRate = rate * myPaths.size() / 100;          // calculate the number of fit population members
        std::sort(myPaths.begin(), myPaths.end());          // sort the population with higher distances first
        std::vector<Path>::iterator myIt = myPaths.begin(); // get the max
        std::vector<Path> newGeneration;
        if(myIt->distance > max->distance){                 // we found a new max path
            std::cout << max->distance << std::endl;
            newGeneration.emplace_back(*max);
            *max = *myIt;
        }
        else{
            myPaths.emplace_back(*max);                     // no new max path, so just emplace our old in the population
        }
        std::vector<Path>::iterator mateIt = myPaths.begin();
        std::vector<Path> mates;
        mateIt++;
        for(int j = 0; j < fitnessRate; j++){               // pair the generation up
            newGeneration.emplace_back(*myIt);
            mates.emplace_back(*mateIt);
            mateIt++;                                       // even
            myIt++;                                         // odd
            j++;                                            // double increment j
        }
        for(int j = fitnessRate; j < myPaths.size(); j++){
            int random = rand() % (unfitRate +  myPaths.size() / unfitRate);        // loop through rest with a chance to add them...
            if(random == 1){
                newGeneration.emplace_back(*myIt);
                mates.emplace_back(*mateIt);
            }
            mateIt++;
            myIt++;
            j++;
        }
        myPaths.clear();                // purge the population
        permuteV(newGeneration);        // permute the new generation parents
        permuteV(mates);                // and the mates
        myIt = newGeneration.begin();
        mateIt = mates.begin();
        for(int j = 0; j < newGeneration.size() && j < mates.size(); j++){  // pair up the parents
            myIt->crossOver(*mateIt);
            Path temp = *myIt;
            myPaths.emplace_back(temp);         // put the child in the new population
            myIt++;
            mateIt++;
        }
       
    }
    std::cout << "Maximum path length found!\n\n\n";
    max->printPath();
}

MutationLab::~MutationLab(){
    delete [] locationArr;
}

void MutationLab::swapV(int a, int b,std::vector<Path>& myVec){
    Path temp = myVec[a];                                           // swap the vector coords
    myVec[a] = myVec[b];
    myVec[b] = temp;
}

void MutationLab::permuteV(std::vector<Path>& myVec){
    for(int i = 0; i < myVec.size(); i++){          // permute the values in the vector
        int random = rand() % myVec.size();
        swapV(i, random, myVec);
    }
}
