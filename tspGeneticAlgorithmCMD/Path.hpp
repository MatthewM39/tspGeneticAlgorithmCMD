//
//  Path.hpp
//  tspGeneticAlgorithmCMD
//
//  Created by Matthew Mccrackin on 9/29/17.
//  Copyright © 2017 Matthew Mccrackin. All rights reserved.
//

#ifndef Path_hpp
#define Path_hpp

#include <stdio.h>
#include <string>
#include "Coord.h"


/* A Path represents a possible route that may be taken from  a starting location.
 A path is randomly generated when it is initialized from the vector of locations.
 During crossover, a new child path is created combining traits from its parents. */

class Path{
public:
    
    /* The length of the path is how many locations there are to visit.
    locations is the array of all locations that must be visited.
    When a path is initialized, its values are permuted from locations. */
    Path(int len, Coord * locations, Coord start, int mutations[8], int crosses[2]);
    
    /* This function is used to cross two paths with each other.
     The Path that calls this function is transformed into the Offspring
     and the mate passed as a parameter is deleted. */
    void crossOver(Path mate);
    void printPath();
    // destructor for a path
   // ~Path();
    
    Coord * myPath;
    double distance;
    friend bool operator<(const Path& l, const Path& r)
    {
        return l.distance > r.distance;
    }
    double pointDist(Coord a, Coord b);
    Path(const Path &obj);
private:
    

    int length;
    int crossVals[2];
    int mutationVals[8];
    Coord startingLocation;
    
    /* This function is used to swap two values in the Path's array of locations */
    void swap(int a, int b);
    
    /* This function is used to randomly permute a path when it is initialized */
    void permutePath();
    
    /* Utilized during crossover. When a gene is taken from the mate and written to
     a slot, we need to find where that gene is already in the array and swap it with
     what the mate gene is going to overwrite */
    void swapGenes(Coord a, int ind);
    
    /* A mutation has some fixed chance of occuring. If a mutation occurs, two random adjacent
     genes will be swapped. The number of mutations determines the number of times to
     generate a chance of mutation. */
    void mutate();
    
    /* A swapping mutation has some fixed chance of occuring. The number of swap mutations
     determines how many number of times to generate a chance of swap mutation. The chainlength
     tells how long the nonoverlapping chains that are swapped should be. */
    void swapMutate();
    
    /* An inversion mutation has some fixed chance of occuring and the number of times one may occur
     during crossover is determined by the number of inverse mutations. The invert length
     tells how long the chain that is inverted should be */
    void invertMutate();
    
    void calcDistance();
    
};




#endif /* Path_hpp */
