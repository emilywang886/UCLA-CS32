//
//  Player.hpp
//  CS32 Project 3
//
//  Created by Emily Wang on 2019/5/16.
//  Copyright © 2019 Emily Wang. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <string>
#include "Side.h"
#include "Board.h"
#include <iostream>

using namespace std;
class Player{
public:
    Player(std::string name) { m_name = name; }
    // Create a Player with the indicated name.
    std::string name() const { return  m_name; }
     // Return the name of the player.
    virtual bool isInteractive() const { return false; }
     // Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
    virtual int chooseMove(const Board& b, Side s) const = 0;
     // Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
    virtual ~Player() {};
     // Since this class is designed as a base class, it should have a virtual destructor.
private:
    string m_name;
};


//chooses its move by prompting a person running the program for a move (reprompting if necessary until the person enters a valid hole number),
// and returning that choice

class HumanPlayer : public Player
{
public:
    HumanPlayer ( string name ) : Player ( name ){}
    bool isInteractive() const { return true; }
    int chooseMove ( const Board& b, Side s ) const;
    
    ~HumanPlayer() {}
};

// A BadPlayer is a computer player that chooses an arbitrary valid move and returns that choice. "Arbitrary" can be what you like: leftmost, nearest to pot, fewest beans, random, etc.. The point of this class is to have an easy-to-implement class that at least plays legally.
class BadPlayer : public Player
{
public:
    BadPlayer ( string name ) : Player ( name ) {}
    int chooseMove ( const Board& b, Side s ) const;
    
    ~BadPlayer() {}
};


class SmartPlayer : public Player
{
public:
    SmartPlayer ( string name ) : Player ( name ) {}
    int chooseMove ( const Board& b,  Side s ) const;
    ~SmartPlayer(){}
private:
    
};

#endif /* Player_h */
