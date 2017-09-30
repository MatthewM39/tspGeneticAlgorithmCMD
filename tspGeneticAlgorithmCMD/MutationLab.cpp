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
    srand(time(NULL)); // seed the rand for a path
    std::cout << "Enter starting coord Name, X value, and Y value separated by spaces: ";
    std::cin >> startingLocation.name >> startingLocation.x >> startingLocation.y;
    std:: cout << "Enter number of locations to visit: ";
    std::cin >> numLocations;
    locationArr = new Coord[numLocations];
    std:: cout << "For each location, enter the Name, X value, and Y value separated by spaces!\n";
    for(int i = 0; i < numLocations; i++){
        std::cout << i + 1 << ": ";
        std::cin >> locationArr[i].name >> locationArr[i].x >> locationArr[i].y;
    }
}

void MutationLab::runTest(){
    int conditions[8];
    int population;
    int fitnessRate;
    int unfitRate;
    int crossVals[2];
    std::cout << "Enter number of cross chains: ";
    std::cin >> crossVals[0];
    std::cout << "Enter length of cross chains: ";
    std::cin >> crossVals[1];
    std::cout << "Enter population number: ";
    std::cin >> population;
    std::cout << "Enter fitness rate: ";
    std::cin >> fitnessRate;
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
        myPaths.emplace_back(Path(numLocations, locationArr, startingLocation, conditions, crossVals));
    }
    int rate = fitnessRate;
    std::cout << "\n";
    for(int i = 0; i < myPaths.size(); i++){
        std::cout << "Completed generation " << i << "\n";
        fitnessRate = rate * myPaths.size() / 100;
        std::sort(myPaths.begin(), myPaths.end());
        std::vector<Path>::iterator myIt = myPaths.begin();
        std::vector<Path> newGeneration;
        if(myIt->distance > max->distance){         // we found a new max path
            max->distance = myIt->distance;
            for(int j = 0; j < numLocations; j++){
                max->myPath[j].x = myIt->myPath[j].x;
                max->myPath[j].y = myIt->myPath[j].y;
                max->myPath[j].name = myIt->myPath[j].name;
            }
        }
        else{
            myPaths.emplace_back(*max);
        }
        std::vector<Path>::iterator mateIt = myPaths.begin();
        std::vector<Path> mates;
        mateIt++;
        for(int j = 0; j < fitnessRate; j++){
            //std::cout << j << " adding to vector from fit\n";
            newGeneration.emplace_back(*myIt);
            mates.emplace_back(*mateIt);
            mateIt++;
            myIt++;
            j++;
        }
        for(int j = fitnessRate; j < myPaths.size(); j++){
            int random = rand() % (unfitRate +  myPaths.size() / unfitRate);
            if(random == 1){
                newGeneration.emplace_back(*myIt);
                mates.emplace_back(*mateIt);
            }
           // std::cout << j << " looping unfit\n";
            mateIt++;
            myIt++;
            j++;
        }
        myPaths.clear();
        permuteV(newGeneration);
        permuteV(mates);
        myIt = newGeneration.begin();
        mateIt = mates.begin();
        for(int j = 0; j < newGeneration.size() && j < mates.size(); j++){
          //  std::cout << j << " looping newGen\n";
            myIt->crossOver(*mateIt);
            Path temp = *myIt;
            myPaths.emplace_back(temp);
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
    Path temp = myVec[a];
    myVec[a] = myVec[b];
    myVec[b] = temp;
}

void MutationLab::permuteV(std::vector<Path>& myVec){
    for(int i = 0; i < myVec.size(); i++){
        int random = rand() % myVec.size();
        swapV(i, random, myVec);
    }
}
