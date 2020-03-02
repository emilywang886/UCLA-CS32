//
//  Board.cpp
//  CS32 Project 3
//
//  Created by Emily Wang on 2019/5/16.
//  Copyright © 2019 Emily Wang. All rights reserved.
//

#include "Board.h"

Board::Board(int nHoles, int nInitialBeansPerHole)
//Construct a Board with the indicated number of holes per side (not counting the pot) and initial number of beans per hole. If nHoles is not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.
{
    if ( nHoles <= 0 )
    {
        nHoles = 1;
    }
    if ( nInitialBeansPerHole < 0 )
    {
        nInitialBeansPerHole = 0;
    }
    
    m_holes = nHoles;
    
    //push 0s to the pots
    m_sHoleBeans.push_back(0);
    m_nHoleBeans.push_back(0);
    
    for ( int i = 1 ; i <= nHoles ;  i++ )
    {
        m_nHoleBeans.push_back(nInitialBeansPerHole);
    }
    
    for ( int i = 1 ; i <= nHoles ;  i++ )
    {
        m_sHoleBeans.push_back(nInitialBeansPerHole);
    }
}


int Board::holes() const{
    //Return the number of holes on a side (not counting the pot).
    return m_holes;
}

int Board::beans(Side s, int hole) const{
    //Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.
    if ( hole < 0 || hole > m_holes){
        return -1;
    }
    
    if ( s == SOUTH){
        return m_sHoleBeans[hole];
    }
    if ( s == NORTH )
    {
        return m_nHoleBeans[hole];
    }
    return -1;
}

int Board:: beansInPlay(Side s) const{
    //Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
    int tBeans = 0;
    if ( s == SOUTH ){
        for ( int i = 1; i <= m_holes ; i++){
            tBeans = tBeans + m_sHoleBeans[i];
        }
    }
    if ( s == NORTH ){
        for ( int i = 1; i <= m_holes ; i++){
            tBeans = tBeans + m_nHoleBeans[i];
        }
    }
    return tBeans;
}


int Board :: totalBeans() const{
    //Return the total number of beans in the game, including any in the pots.
    int allBeans = 0;
    allBeans = beansInPlay(SOUTH) + beansInPlay(NORTH) + m_sHoleBeans[0] + m_nHoleBeans[0];
    return allBeans;
}

bool Board:: sow(Side s, int hole, Side& endSide, int& endHole){
    //If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything. Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The parameters endSide and endHole are set to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)
    if ( beans(s, hole) == 0 ){
        return false;
    }
    if ( hole <= 0 || hole > m_holes){
        return false;
    }
    
    
    int beansInHand = beans( s, hole);
    endHole = hole;
    endSide = s;
    
    if ( s == NORTH)
        m_nHoleBeans[hole] = 0;
    else
        m_sHoleBeans[hole] = 0;

    // for( ; beansInHand != 0 ; beansInHand--)
    while ( beansInHand != 0 )
    {
        if ( endHole == 0 ) // if we're in a pot, move to opponent's side
        {
            if ( endSide == SOUTH)
                endHole = m_holes;
            else
                endHole = 1;
            endSide = opponent(endSide);
        }
        else if ( endHole == m_holes && endSide == SOUTH ) // if we're at the last south hole, move to south's pot
        {
            if ( s == SOUTH)    // started as south player
                endHole = 0;
            else
                endHole = m_holes;
        }
        else if ( endHole == 1 && endSide == NORTH ) // if we're at the last north hole, move to north's pot
        {
            if ( s == NORTH )   // started as north player
                endHole = 0;
            else
                endHole = 1;
        }
        
        else
        {
            endHole += ( endSide == NORTH ) ? -1 : 1 ;  // in other cases, move left when in north and right when in south
        }
        
        if ( endSide == NORTH )
            m_nHoleBeans[endHole]++;
        else
            m_sHoleBeans[endHole]++;
        beansInHand--;
    }
    return true;
    
//    int beansInHand = beans(s, hole);
//    m_nHoleBeans[hole] = 0;
//    Side currentSide = s;
//
//    while ( beansInHand > 0 ){
//    if ( currentSide == NORTH){
//        for ( int i = hole - 1 ; i >= 0 ; i-- ){
//
//            m_nHoleBeans[i]++;
//            beansInHand--;
//            if ( beansInHand == 0 ){
//                break;
//            }
//
//            if ( i == 1 && s == NORTH ){
//                currentSide = SOUTH;
//                hole = 0 ;
//            }
//            else if ( i == 1 && s == SOUTH ){
//                currentSide = SOUTH;
//                hole = 0 ;
//                break;
//            }
//        }
//    }
//    else if ( currentSide == SOUTH){
//        // needs a special case for starting at the last hole
//        for ( int i = hole + 1 ; i <= m_holes ; i++ ){
//
//            m_sHoleBeans[i]++;
//            beansInHand--;
//
//            if ( beansInHand == 0 ){
//                break;
//            }
//
//            if ( i == m_holes && s == SOUTH){
//                m_sHoleBeans[0]++;
//                beansInHand--;
//                currentSide = NORTH;
//                hole = m_holes + 1;
//            }
//            else if ( i == m_holes && s == NORTH){
//                currentSide = NORTH;
//                hole = m_holes + 1;
//            }
//
//        }
//
//    }
//
//    }
//
//    endSide = s;
//    endHole = hole;

}
bool Board::moveToPot(Side s, int hole, Side potOwner)
    //If the indicated hole is invalid or a pot, return false without changing anything. Otherwise, move all the beans in hole (s,hole) into the pot belonging to potOwner and return true.
{
    if ( hole <= 0 || hole > m_holes){
        return false;
    }
    if ( s != SOUTH && s != NORTH){
        return false;
    }
    
    if ( s == NORTH ){
        if ( potOwner == NORTH)
        {
            m_nHoleBeans[0] = beans( NORTH, 0 ) + beans( NORTH , hole );
        }
        else
        {
            m_sHoleBeans[0] = beans( SOUTH, 0 ) + beans( NORTH , hole );
        }
        m_nHoleBeans[hole] = 0;
    }
    else if ( s == SOUTH ){
        if ( potOwner == NORTH)
        {
            m_nHoleBeans[0] = beans( NORTH, 0 ) + beans( SOUTH , hole );
        }
        else
        {
            m_sHoleBeans[0] = beans( SOUTH, 0 ) + beans( SOUTH , hole );
        }
        m_sHoleBeans[hole] = 0;
    }
    return true;
}
bool Board::setBeans(Side s, int hole, int beans)
    //If the indicated hole is invalid or beans is negative, this function returns false without changing anything. Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of the third parameter. (This may change what beansInPlay and totalBeans return if they are called later.) This function exists solely so that we and you can more easily test your program: None of your code that implements the member functions of any class is allowed to call this function directly or indirectly. (We'll show an example of its use below.)
{
    
    if ( hole < 0 || hole > m_holes){
        return false;
    }
    if ( s != SOUTH && s != NORTH){
        return false;
    }
    
    if ( s == NORTH ){
        m_nHoleBeans[hole] = beans;
    }
    else if ( s == SOUTH ){
        m_sHoleBeans[hole] = beans;
    }
    return true;

    
}
    
    

