//
//  Coord.h
//  tspGeneticAlgorithmCMD
//
//  Created by Matthew Mccrackin on 9/29/17.
//  Copyright © 2017 Matthew Mccrackin. All rights reserved.
//

#ifndef Coord_h
#define Coord_h
#include <string>

struct Coord{
    double x,y;         // 2D x,y coordinates for a place
    std::string name;  // name of the place
    void operator = (const Coord &C ) {
        x = C.x;
        y = C.y;
        name = C.name;
    }
};

#endif /* Coord_h */
