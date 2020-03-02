//
//  main.cpp
//  CS32 Project 3
//
//  Created by Emily Wang on 2019/5/16.
//  Copyright © 2019 Emily Wang. All rights reserved.
//

#include <iostream>
#include "Board.h"
#include "Game.h"
#include "Player.h"
#include "Side.h"
#include <cassert>
using namespace std;

void doBoardTests()
{
    // TEST CODE FOR BOARD CONSTRUCTION
    Board b ( 6, 5 );
    assert( b.holes() == 6 );
    cout << "Passed board construction test" << endl;
    assert( b.beans(SOUTH, 0) == 0 );
    assert( b.beans(SOUTH, 4) == 5 );
    assert( b.beans(NORTH, 8) == -1);
    cout << "Passed beans test" << endl;
    assert( b.beansInPlay(NORTH) == 30);
    cout << "Passed beansInPlay test" << endl;
    assert( b.totalBeans() == 60 );
    cout << "Passed totalBeans test" << endl;
    assert( b.setBeans(SOUTH, 3, 7 ) == true);
    assert( b.beans(SOUTH, 3) == 7 );
    cout << "Passed setBeans test" << endl;
    assert( b.moveToPot(SOUTH, 3, NORTH) == true);
    assert( b.beans(NORTH, 0) == 7);
    assert( b.beans(SOUTH, 3) == 0);
    cout << "Passed moveToPot test" << endl;
    b.setBeans(NORTH, 0, 0);
    b.setBeans(SOUTH, 3, 5);
    Side endSide = SOUTH;
    int endHole = -1;
    assert(b.sow(NORTH, 6, endSide, endHole));
    assert( b.beans(NORTH, 1) == 6 );
    assert( b.beans(NORTH, 6) == 0);
    assert(endSide == NORTH);
    Board b2 ( 6, 5 );
    assert( b2. sow(NORTH, 1, endSide, endHole));
    assert( b2.beans(NORTH, 0) == 1);
    assert( b2.beans(SOUTH, 4) == 6);
    assert( endSide == SOUTH && endHole == 4);
    cout << "Passed sow test" << endl;

}

void doPlayerTests()
{
    // TEST CODE FOR GAME & PLAYER
    
    BadPlayer p("Noah");
    BadPlayer p2 ("LJ");
    assert( p.name() == "Noah" && !p.isInteractive() );
    Board b3 ( 3, 0 );
    b3.setBeans(NORTH, 3, 2);
    b3.setBeans(NORTH, 2, 1);
    b3.setBeans(SOUTH, 1, 2);
    
    Game g ( b3, &p, &p2);
    g.display();
    //       0  1  2
    //    0           0
    //       2  0  0
    
    bool over , hasWinner;
    Side winner;
    g.status(over, hasWinner, winner);
    assert( !over && g.beans(NORTH, 0) == 0 && g.beans(SOUTH, 0) == 0 && g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1);
    // assert( g.beans(NORTH, 3) == 2 );
    assert(g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0);
    
    g.move();
    g.display();
    //  Noah chose hole 1
    //        0  1  0
    //    0            3
    //        0  1  0
    g.status(over, hasWinner, winner);
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, 0) == 0 && g.beans(SOUTH, 0) == 3 &&
           g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 &&
           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1);
    
    g.move();
    g.display();
    //  LJ chose hole 2
    //       1  0  0
    //    0           3
    //       0  1  0
    g.status(over, hasWinner, winner);
    assert(!over && g.beans(NORTH, 0) == 0 && g.beans(SOUTH, 0) == 3 &&
           g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 &&
           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 );
    
    g.move();
    g.display();
    //    Noah chose hole 2
    //      1  0  0
    //    0           3
    //      0  0  1
    g.move();
    g.display();
    //    LJ chose hole 1
    //        0  0  0
    //    1           3
    //        0  0  1
    //    LJ gets another turn.
    //        0  0  0
    //    1           3
    //        0  0  1
    //    Sweeping all beans on Noah's side to pot.
    //        0  0  0
    //    1           4
    //        0  0  0
    g.status(over, hasWinner, winner);
    assert(hasWinner && winner == SOUTH);
    assert(over && g.beans(NORTH, 0) == 1 && g.beans(SOUTH, 0) == 4 &&
           g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 &&
           g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 );
    
}

int main ()
{
}
