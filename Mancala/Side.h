
//
//  Header.h
//  CS32 Project 3
//
//  Created by Emily Wang on 2019/5/16.
//  Copyright © 2019 Emily Wang. All rights reserved.
//

#ifndef Side_h
#define Side_h

#include <iostream>
using namespace std;

enum Side { NORTH, SOUTH };

const int NSIDES = 2;
const int POT = 0;

inline
Side opponent(Side s)
{
    return Side(NSIDES - 1 - s);
}


#endif /* Header_h */
