//
//  Player.cpp
//  CS32 Project 3
//
//  Created by Emily Wang on 2019/5/16.
//  Copyright © 2019 Emily Wang. All rights reserved.
//


#include "Player.h"
#include "Board.h"
#include "Side.h"

//==========================================================================
// AlarmClock ac(numMilliseconds);  // Set an alarm clock that will time out
//                                  // after the indicated number of ms
// if (ac.timedOut())  // Will be false until the alarm clock times out; after
//                     // that, always returns true.
//==========================================================================

#include <chrono>
#include <future>
#include <atomic>

class AlarmClock
{
public:
    AlarmClock(int ms)
    {
        m_timedOut = false;
        m_isRunning = true;
        m_alarmClockFuture = std::async([=]() {
            for (int k = 0; k < ms  &&  m_isRunning; k++)
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            if (m_isRunning)
                m_timedOut = true;
        });
    }
    
    ~AlarmClock()
    {
        m_isRunning = false;
        m_alarmClockFuture.get();
    }
    
    bool timedOut() const
    {
        return m_timedOut;
    }
    
    AlarmClock(const AlarmClock&) = delete;
    AlarmClock& operator=(const AlarmClock&) = delete;
private:
    std::atomic<bool> m_isRunning;
    std::atomic<bool> m_timedOut;
    std::future<void> m_alarmClockFuture;
};


int SmartPlayer:: chooseMove ( const Board& b,  Side s ) const
{
    return 0;
}



// ========================================================================================

int HumanPlayer:: chooseMove ( const Board& b, Side s ) const
{
    
    if ( b.beansInPlay(SOUTH) == 0 || b.beansInPlay(NORTH) == 0 )
    {
        return -1;
    }
    int n;
    do
    {
        cout << "Choose a hole from 1 to" << b.holes() << ":";
        cin >> n;
    } while ( n > b.holes() || n <= 0 || b.beans(s, n) == 0 );
    // keep prompting until a valid hole number is entered
    return n;
}

int BadPlayer:: chooseMove( const Board& b, Side s ) const
{
    if ( b.beansInPlay(SOUTH) == 0 || b.beansInPlay(NORTH) == 0 )
    {
        return -1;
    }
    int n;
    do
    {
        n = (rand() % b.holes()) + 1;
    } while ( b.beans ( s, n ) == 0 );
    // generate a random hole number. regenerate when theres no beans in the hole.
    return n;
}

