//
//  Sequence.hpp
//  CS32-Project 2
//
//  Created by Emily Wang on 2019/4/23.
//  Copyright © 2019 Emily Wang. All rights reserved.
//

#ifndef Sequence_h
#define Sequence_h

#include <stdio.h>
#include <iostream>
#include <string>

typedef std::string ItemType;

class Sequence
{
public:

    Sequence(); // constructor
    Sequence(const Sequence& other); // Copy Constructor
    Sequence& operator=(const Sequence& rhs); // Asignment Operator
    ~Sequence(); // destructor
    
    bool empty() const;
    int size() const;
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);  // done
    bool get(int pos, ItemType& value) const; //done
    bool set(int pos, const ItemType& value); //done
    int find(const ItemType& value) const;  //done
    void swap(Sequence& other);
    
    void dump() const; // helper function
    
private:
    struct node{
        ItemType m_data;
        node* m_prev;
        node* m_next;
    };
    int m_size;
    node* head;
};

int subsequence(const Sequence& seq1, const Sequence& seq2);

void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);


#endif /* Sequence_hpp */
