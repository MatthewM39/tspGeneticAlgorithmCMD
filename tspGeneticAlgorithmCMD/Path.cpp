//
//  Path.cpp
//  tspGeneticAlgorithmCMD
//
//  Created by Matthew Mccrackin on 9/29/17.
//  Copyright © 2017 Matthew Mccrackin. All rights reserved.
//

#include "Path.hpp"
#include <iostream>
#include <stdlib.h>
#include <math.h>

Path::Path(int len, Coord * locations, Coord start, int mutations[8], int crosses[2]){
    for(int i = 0; i < 8; i++){
        mutationVals[i] = mutations[i];
    }
    startingLocation = start;
    length = len;
    myPath = new Coord [length];
    for(int i = 0; i < length; i++){
        myPath[i] = locations[i];
    }
    crossVals[0] = crosses[0];
    crossVals[1] = crosses[1];
    permutePath();
    calcDistance();
}

void Path::swap(int a, int b){
    Coord temp = myPath[a]; // set temp to be the first
    myPath[a] = myPath[b]; // set the first to be the second
    myPath[b] = temp;     // now set the second to be temp
}

void Path::permutePath(){
    for(int i = 0; i < length; i++){
        int random = rand() % length;
        swap(i, random);
    }
}

void Path::mutate(){
    for(int i = 0; i < mutationVals[0]; i++){
        if(rand() % (10000 / mutationVals[1]) == 1){
            int ind = rand() % length;
            if(ind == length - 1){
                swap(ind - 1, ind);
            }
            else{
                swap(ind, ind + 1);
            }
        }
    }
}

void Path::swapMutate(){
    for(int i = 0; i < mutationVals[2]; i++){
        if(rand() % (10000 / mutationVals[3]) == 1){
            int ind;
            int ind2;
            do {                                                // make sure the chains dont overlap!
                ind = rand() % length;                          // get a random number from 0 to length-1
                if(ind >= length - mutationVals[4]){            // if the index excedes the chain length...
                    ind -= mutationVals[4];                     // then we need to subtract the chain length
                }
                ind2 = rand() % length;                     // generate a new second index until they dont overlap!
                if(ind2 >= length - mutationVals[4]){
                    ind2 -= (mutationVals[4] + 1);            // subtract one just to be safe!
                }
            } while(abs(ind2 - ind) < mutationVals[4]);
            
            for(int j = 0; j < mutationVals[4]; j++){       // now we can swap the two chains!
                swap(ind + j, ind2 + j);                    // swap each, value by value
            }
        }
    }
}

void Path::invertMutate(){
    for(int i = 0; i < mutationVals[5]; i++){
        if(rand() % (10000 / mutationVals[6]) == 1){
            int ind = rand() % length;
            if(ind <= mutationVals[7]){                     // check if our index is less than the length of a chain
                ind = 0;                                    // if so make our starting index 0
            }
            else if(ind >= length - mutationVals[7]){       // check if our index is out of bounds past the length of a chain
                ind -= (mutationVals[7] + 1);               // if so, go back by the length of the chain and 1
            }
            for(int j = 1; j < mutationVals[7]; j++){       // now loop through the length of the chain
                swap(ind + j, ind + mutationVals[7] - j);   // swap the elements in the chain so that they reverse!
            }
        }
    }
}

void Path::swapGenes(Coord a, int ind){
    int swapInd = 0;
    for(int i = 0; i < length; i++){
        if(myPath[i].x == a.x && myPath[i].y == a.y){       // find in the chain where a coord is...
            swapInd = i;                                    // get its index
            break;
        }
    }
    myPath[swapInd] = myPath[ind];                          // set its value to the gene we are replacing...
    myPath[ind] = a;                                        // now replace the gene value...
}

void Path::crossOver(Path mate){
    for(int i = 0; i < crossVals[0]; i ++){                 // do as many crossovers as we are supposed to!
        int random = rand() % length;                       // get a random index to start!
        if(random >= length - crossVals[1]){                // make sure it's not out of bounds!
            random = length - crossVals[1] - 1;             // fix it if it is OOB
        }
        for(int j = 0; j < crossVals[1]; j++){              // now loop the length of a crossover chain...
            swapGenes(mate.myPath[random], j);              // swap the mate's gene in and replace the old!
        }
        mutate();                                           // Crossing over has a chance of causing mutations!
        swapMutate();
        invertMutate();
        calcDistance();
    }
}
void Path::calcDistance(){
    distance = pointDist(myPath[0], startingLocation);
    for(int i = 0; i < length - 1; i++){
        distance += pointDist(myPath[i], myPath[i+1]);
    }
    distance += pointDist(myPath[length - 1], startingLocation);
}

void Path::printPath(){
    std::cout << startingLocation.name << " (" << startingLocation.x << "," << startingLocation.y << ") to ";
    std::cout << myPath[0].name << " (" << myPath[0].x << "," << myPath[0].y << ") : " << pointDist(startingLocation, myPath[0])
    << "\n";
    for(int i = 0; i < length - 1; i++){
        std::cout << myPath[i].name << " (" << myPath[i].x << "," << myPath[i].y << ") to ";
        std::cout << myPath[i+1].name << " (" << myPath[i+1].x << "," << myPath[i+1].y << ") : " << pointDist(myPath[i], myPath[i+1])
        << "\n";
    }
    std::cout << myPath[length - 1].name << " (" << myPath[length - 1].x << "," << myPath[length - 1].y << ") to ";
    std::cout << startingLocation.name << " (" << startingLocation.x << "," << startingLocation.y << "): " <<
    pointDist(startingLocation, myPath[length - 1]) << "\n";
    calcDistance();
    std::cout << "Total distance: " << distance << "\n";
}

double Path::pointDist(Coord a, Coord b){
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}


Path::Path(const Path &obj){
    for(int i = 0; i < 8; i++){
        mutationVals[i] = obj.mutationVals[i];
    }
    startingLocation = obj.startingLocation;
    length = obj.length;
    myPath = new Coord [length];
    for(int i = 0; i < length; i++){
        myPath[i] = obj.myPath[i];
    }
    crossVals[0] = obj.crossVals[0];
    crossVals[1] = obj.crossVals[1];
    distance = obj.distance;
}
