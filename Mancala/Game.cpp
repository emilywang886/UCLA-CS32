//
//  Game.cpp
//  CS32 Project 3
//
//  Created by Emily Wang on 2019/5/16.
//  Copyright © 2019 Emily Wang. All rights reserved.
//

#include "Game.h"
#include <iostream>
using namespace std;

Game:: Game(const Board& b, Player* south, Player* north)
: m_board(b)
{
    m_sPlayer = south;
    m_nPlayer = north;
    m_turn = SOUTH;
}

void Game:: display() const
// Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of the state of the board.
{
    // north's name
    for ( int i = 0 ; i <= m_board.holes()*2 - 2 ; i++ ){
        cout << " " ;
    }
    cout << m_nPlayer->name()<< endl;
    
    // north holes
    cout << " ";
    for ( int i = 1 ; i <= m_board.holes() ; i++ )
    {
        cout << "  " << m_board.beans(NORTH, i);
    }
    cout << endl;
    
    // north pot + south pot
    cout << m_board.beans(NORTH, 0 );
    for ( int i = 0 ; i < m_board.holes() ; i++ )
    {
        cout << "   " ;
    }
    cout << "  " << m_board.beans(SOUTH, 0 ) << endl;
    
    // south holes
    cout << " ";
    for ( int i = 1 ; i <= m_board.holes() ; i++ )
    {
        cout << "  " << m_board.beans(SOUTH, i);
    }
    cout << endl;
    
    // south's name
    for ( int i = 0 ; i <= m_board.holes()*2 - 2 ; i++ ){
        cout << " " ;
    }
    cout << m_sPlayer->name() << endl;
}


void Game:: status(bool& over, bool& hasWinner, Side& winner) const
// If the game isn't over (i.e., more moves are possible), set over to false and do not change anything else. Otherwise, set over to true and hasWinner to true if the game has a winner, or false if it resulted in a tie. If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.
{
    if ( m_board.beansInPlay(SOUTH) != 0 && m_board.beansInPlay(NORTH) != 0)
    {
        over = false;
        return;
    }
    else
        over = true;
    if ( m_board.beans(NORTH, 0) == m_board.beans(SOUTH, 0))
    {
        hasWinner = false;
    }
    else
        hasWinner = true;
    winner = ( m_board.beans(NORTH, 0) < m_board.beans(SOUTH, 0)) ? SOUTH : NORTH;
}

bool Game:: move()
// If the game is over, return false. Otherwise, make a complete move for the player whose turn it is (so that it becomes the other player's turn) and return true. "Complete" means that the player sows the seeds from a hole and takes any additional turns required or completes a capture. If the player gets an additional turn, you should display the board so someone looking at the screen can follow what's happening.
{
    bool over, hasWinner;
    Side winner;
    status(over , hasWinner, winner);
    
    if (over)
    {
        return false;
    }
    
    Side endSide;
    int endHole;
    Player* currentPlayer;
    int hole;
    
    currentPlayer = ( m_turn == NORTH ) ? m_nPlayer : m_sPlayer;
    hole = currentPlayer->chooseMove(m_board, m_turn);
    cout << currentPlayer->name() << " chose hole " << hole << endl;
    
    m_board.sow(m_turn, hole, endSide, endHole);
    
    if ( endHole != 0 && endSide == m_turn && m_board.beans(m_turn, endHole) - 1 == 0 && m_board.beans(opponent(m_turn), endHole) != 0 )
        // if player can perform a capture
    {
        m_board.moveToPot(m_turn, endHole, m_turn);
        m_board.moveToPot(opponent(m_turn), endHole, m_turn);
    }
    
    while ( endHole == 0 && endSide == m_turn )
        // if player ends in own pot
    {
        display();
        cout << currentPlayer->name() << " gets another turn." << endl;
        hole = currentPlayer->chooseMove(m_board, m_turn);
        if ( hole == -1 )
            break;
        if ( ! m_board.sow(m_turn, hole, endSide, endHole))
            break;
        cout << currentPlayer->name() << " chose hole " << hole << endl;
    }
    
    // if either side clears out first
    if ( m_board.beansInPlay(NORTH) == 0 )
    {
        display();
        cout << " Sweeping all beans on " << m_sPlayer->name() << "'s side to pot." << endl;
        for ( int i = 0 ; i <= m_board.holes() ; i++ )
        {
            m_board.moveToPot(m_turn, i, m_turn);
            m_board.moveToPot(opponent(m_turn), i, opponent(m_turn));
        }
        display();
    }
    else if ( m_board.beansInPlay(SOUTH) == 0 )
    {
        display();
        cout << " Sweeping all beans on " << m_nPlayer->name() << "'s side to pot." << endl;
        for ( int i = 0 ; i <= m_board.holes() ; i++ )
        {
            m_board.moveToPot(m_turn, i, m_turn);
            m_board.moveToPot(opponent(m_turn), i, opponent(m_turn));
        }
        display();
    }
    
    m_turn = opponent(m_turn);
    return true;
}


void Game:: play()
// Play the game. Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed. (The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your liking the responsibility for displaying the board between this function and the move function. (Note: If when this function is called, South has no beans in play, so can't make the first move, sweep any beans on the North side into North's pot and act as if the game is thus over.)
{
    bool over, hasWinner;
    Side winner;
    Player* currentPlayer;
    
    while (!over)
    {
        display();
        
        if ( !m_nPlayer->isInteractive() && !m_sPlayer->isInteractive())
        {
            cout << " Press ENTER to continue. ";
            cin.ignore();
        }
        
        move();
        status(over, hasWinner, winner);
    }
    
    cout << "The game is over." << endl;
    
    if ( hasWinner )
    {
        currentPlayer = ( winner == NORTH) ? m_nPlayer : m_sPlayer;
        cout << "The winner is: " << currentPlayer->name() << endl;
    }
    else
    {
        cout << "The game resulted in a tie. " << endl;
    }
}

int Game:: beans(Side s, int hole) const
{
   if ( hole < 0 || hole >= m_board.holes())
   {
       return -1;
   }

    return m_board.beans( s, hole );
}



