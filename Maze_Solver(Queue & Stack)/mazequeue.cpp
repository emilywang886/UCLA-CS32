//
//  main.cpp
//  CS32-HW2-pt2
//
//  Created by Emily Wang on 2019/5/1.
//  Copyright © 2019 Emily Wang. All rights reserved.
//

#include <iostream>
#include <queue>
using namespace std;



class Coord
{
public:
    Coord(int rr, int cc)
    : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec){
    
    queue <Coord> coordQueue;
    Coord startPoint(sr, sc);
    coordQueue.push(startPoint); //Push the starting coordinate (sr,sc) onto the coordinate queue
    maze[sr][sc] = '#'; // update maze[sr][sc] to indicate that the algorithm has encountered it
    // (i.e., set maze[sr][sc] to have a value other than '.')
    
    int row = sr;
    int col = sc;
    
    while ( !coordQueue.empty() )      //While the queue is not empty
    {
        startPoint = coordQueue.front();
        row = startPoint.r();
        col = startPoint.c();
        coordQueue.pop();               //    Pop the top coordinate off the queue. This gives you the current
        //    (r,c) location that your algorithm is exploring.
        
        
        if( row == er && col == ec ) {  //    If the current (r,c) coordinate is equal to the ending coordinate,
            return true;                //    then we've solved the maze so return true!
        }
        
        
        //   Check each place you can move from the current cell as follows:
        
        if (row < 9 && maze[row+1][col] == '.'){
            //    If you can move SOUTH and haven't encountered that cell yet
            Coord moveSouth ( row + 1, col );
            maze[row+1][col] = '#';
            // then push the coordinate (r+1,c) onto the stack and update
            // maze[r+1][c] to indicate the algorithm has encountered it.
            coordQueue.push(moveSouth);
        }
        if ( col > 0 && maze[row][col-1] == '.'){
            //    If you can move WEST and haven't encountered that cell yet
            Coord moveWest ( row , col - 1 );
            maze[row][col-1] = '#';
            //  then push the coordinate (r,c-1) onto the stack and update
            //  maze[r][c-1] to indicate the algorithm has encountered it.
            coordQueue.push(moveWest);
        }
        if (row > 0  && maze[row-1][col] == '.'){
            //    If you can move NORTH and haven't encountered that cell yet
            Coord moveNorth ( row - 1 , col );
            maze[row-1][col] = '#';
            //  then push the coordinate (r-1,c) onto the stack and update
            //  maze[r-1][c] to indicate the algorithm has encountered it.
            coordQueue.push(moveNorth);
        }
        if ( col < 9 && maze[row][col+1] == '.'){
            //    If you can move EAST and haven't encountered that cell yet
            Coord moveEast ( row , col + 1 );
            maze[row][col+1] = '#';
            // then push the coordinate (r,c+1) onto the stack and update
            // maze[r][c+1] to indicate the algorithm has encountered it.
            coordQueue.push(moveEast);
        }
        
    }
    return false;  //There was no solution, so return false
}



