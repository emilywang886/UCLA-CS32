//
//  Sequence.cpp
//  CS32-Project 2
//
//  Created by Emily Wang on 2019/4/23.
//  Copyright © 2019 Emily Wang. All rights reserved.
//

#include "Sequence.h"
#include <iostream>
using namespace std;

Sequence::Sequence()
// Default Constructor
:m_size(0)
{
    // Construct an empty Sequence through Circularly Linked Lists with dummy node
    
    head = new node;
    head->m_next = head;
    head->m_prev = head;
}

Sequence::~Sequence()
// Destructor
// When a Sequence is destroyed, the nodes in the linked list must be deallocated.
{
    node* p = head->m_next;
    for (p = head->m_next; p != head; ){
        node* temp = p->m_next;
        delete p;
        p = temp;
    }
}


Sequence:: Sequence(const Sequence& other)
// Copy Constructor
// When a brand new Sequence is created as a copy of an existing Sequence, enough new nodes must be allocated to hold a duplicate of the original list.
:m_size(other.m_size)
{
    // Initialize the dummy node
    head = new node;
    head -> m_next = head;
    head -> m_prev = head;
    
    int i = 0;
    
    for ( node* p = other.head -> m_next ; p != other.head ; p = p -> m_next){
        insert( i , p -> m_data);
        i++;
    }
    
}


Sequence& Sequence:: operator = (const Sequence& rhs)
// Assignment Operator
// When an existing Sequence (the left-hand side) is assigned the value of another Sequence (the right-hand side), the result must be that the left-hand side object is a duplicate of the right-hand side object, with no memory leak of list nodes (i.e. no list node from the old value of the left-hand side should be still allocated yet inaccessible).
{
    if (this != & rhs){
        Sequence t = rhs;
        swap(t);
    }
    return *this;
}

bool Sequence::empty() const  // Return true if the sequence is empty, otherwise false.
{
    if ( m_size > 0){
        return false;
    }
    else
        return true;
}

int Sequence::size() const   // Return the number of items in the sequence.
{
    return m_size;
}

int Sequence::insert(int pos, const ItemType& value)

{
    if ( pos < 0 || pos > size()){
        return -1;
    }
    else{
        node* p = head;
        for ( int i = 0 ; i <= pos ; i++){
            p = p -> m_next;
        }
        
        node* newNode = new node;
        newNode -> m_data = value;
        
        newNode->m_next = p;
        newNode -> m_prev = p -> m_prev;
        p->m_prev->m_next = newNode;
        p -> m_prev = newNode;
        m_size++;
        return pos;
    }
}



int Sequence:: insert(const ItemType& value)
{
    // Let p be the smallest integer such that value <= the item at
    // position p in the sequence;
    node* p = head;
    int i;
    for ( i = 0 ; i < size() ; i++) {
        p = p -> m_next;
        if ( p -> m_data >= value){
            break;
        }
    }
    
    return insert( i, value ); // this will return the pos because of the other insert function
}

bool Sequence:: erase(int pos)
// If 0 <= pos < size(), remove the item at position pos from
// the sequence (so that all items that followed that item end up at
// positions one lower than they were at before), and return true.
// Otherwise, leave the sequence unchanged and return false.
{
    if ( pos < 0 || pos > size()){
        return false;
    }
    else{
        node* p = head;
        for ( int i = 0 ; i <= pos ; i++){
            // i <= pos because we're starting at the dummy node and need to delete the first actual data
            p = p -> m_next;
        }
        
        p -> m_prev -> m_next = p -> m_next;
        p -> m_next -> m_prev = p -> m_prev;
        delete p;
        m_size--;
        return true;
    }
}

int Sequence:: remove(const ItemType& value)
// Erase all items from the sequence that == value.  Return the
// number of items removed (which will be 0 if no item == value).
{
    node* p = head -> m_prev;
    int amount = 0;
    
    while ( p != head){
        if ( p -> m_data == value){
            node* tempNode = p -> m_prev;
            p -> m_prev -> m_next = p -> m_next;
            p -> m_next -> m_prev = p -> m_prev;
            delete p;
            m_size--;
            amount++;
            p = tempNode;
        }
        else{
            p = p -> m_prev;
        }
    }
    return amount;
}


bool Sequence:: get(int pos, ItemType& value) const
// If 0 <= pos < size(), copy into value the item at position pos
// of the sequence and return true.  Otherwise, leave value unchanged
// and return false.
{
    if ( pos < 0 || pos >= size()){
        return false;
    }
    else{
        node* p = head;
        for ( int i = 0 ; i <= pos ; i++){
            p = p -> m_next;
        }
        value = p -> m_data;
    }
    return true;
}

bool Sequence:: set(int pos, const ItemType& value)
// If 0 <= pos < size(), replace the item at position pos in the
// sequence with value and return true.  Otherwise, leave the sequence
// unchanged and return false.
{
    if ( pos < 0 || pos >= size()){
        return false;
    }
    else{
        node* p = head;
        for ( int i = 0 ; i <= pos ; i++){
            p = p -> m_next;
        }
        p -> m_data = value;
    }
    return true;
}

int Sequence:: find(const ItemType& value) const
// if value exist in the sequence, return its position
// if no such item exists, return -1.
{
    node* p = head;
    for ( int i = 0 ; i < size() ; i++ ){
        p = p -> m_next;
        if ( p -> m_data == value){
            return i;
        }
    }
    return -1;
}


void Sequence:: swap(Sequence& other)
// Exchange the contents of this sequence with the other one.
{
    node* temp = head;
    head = other.head;
    other.head = temp;
    
    int temp_size = m_size;
    m_size = other.m_size;
    other.m_size = temp_size;
    
}


void Sequence::dump() const
//prints out the array
{
    node* p = head;
    for (int i = 0 ; i < size(); i++){
        p = p -> m_next;
        cerr << p -> m_data << ",";
        
    }
    cerr << endl;
}

int subsequence(const Sequence& seq1, const Sequence& seq2){
    
    if (seq2.size() > seq1.size()){
        return -1;
    }
    
    for ( int i = 0 ; i <= seq1.size()-seq2.size() ; i++){  //  seq1.size()-seq2.size() because it has to start at a point that its possible for seq2 to exist
        
        bool found = true;
        for ( int k = 0 ; k < seq2.size() ; k ++){
            ItemType temp1;
            ItemType temp2;
            seq2.get(k, temp2);
            seq1.get(i+k, temp1);
            if ( temp1 != temp2){
                found = false;
                break;
            }
        }
        
        if (found){
            return i;
        }
    }
    return -1;
}

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result){
    
    result = Sequence(); // reset  result to an empty sequence
    
    int i = 0;
    for ( ; i < seq1.size() && i < seq2.size() ; i++ ){   // make sure i is looping through common elements
        ItemType temp1;
        ItemType temp2;
        seq1.get( i , temp1);
        seq2.get( i , temp2);
        result.insert(result.size(), temp1);    // insert the stuff at the end
        result.insert(result.size(), temp2);
    }
    
    if ( seq1.size() < seq2.size()){
        for ( ; i < seq2.size() ; i++){
            ItemType temp2;
            seq2.get(i, temp2);
            result.insert( result.size(), temp2);
        }
    }
    
    else if( seq1.size() > seq2.size()){
        for ( ; i < seq1.size() ; i++){
            ItemType temp1;
            seq1.get(i, temp1);
            result.insert( result.size(), temp1);
        }

     }

}
