//
//  main.cpp
//  CS32-Project 2
//
//  Created by Emily Wang on 2019/4/23.
//  Copyright © 2019 Emily Wang. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
#include "Sequence.h"
using namespace std;
int main(){
    Sequence s;

    // TEST INSERT(POS , VALUE)
    s.insert(0, "d");
    s.insert(0, "a");
    s.insert(1, "b");
    // a , b , d
    s.dump();

    // TEST INSERT (VALUE)
    s.insert("c");
    s.dump();

    // TEST ERASE(POS)
    s.erase(2);
    s.dump();

    string erased;
    s.get(2, erased);
    cerr << erased << endl ;

    // TEST REMOVE (VALUE)
    s.insert("c");
    s.insert(2, "a");
    s.insert(2, "a");
    s.insert(4, "a");
    s.insert(6, "a"); // a, b, a, a, c, a, d, a
    int a = s.remove("a");
    cerr << a << endl; //5
    s.dump();

    // TEST GET (POS, VALUE)
    string get;
    s.insert(0, "a"); // a, b, c, d
    s.get(0, get);
    cerr << get << endl;
    s.get(3, get);
    cerr << get << endl;

    // TEST SET (POS, VALUE)
    s.set(3, "e"); // a, b, c, e
    s.dump();

    // TEST FIND
    int foundPosition = s.find("b");
    cerr << foundPosition << endl;
    int nonExsistent = s.find("d");
    cerr << nonExsistent << endl;

    // TEST SWAP
    Sequence s1;
    s1.insert(0, "today");
    s1.insert(0, "you");
    s1.insert(0, "are");
    s1.insert(0, "how");
    s1.insert(0, "hello");
    s1.swap(s);
    s.dump();
    s1.dump();
    assert(s.size() == 5);
    assert(s1.size() == 4);
    
    // TEST  subsequence(const Sequence& seq1, const Sequence& seq2)
    Sequence seq1;
    Sequence seq2;
    seq1.insert(0, "4");
    seq1.insert(0, "3");
    seq1.insert(0, "2");
    seq1.insert(0, "1");
    seq1.insert(0, "0");
    // seq1 : 0, 1, 2, 3, 4
    seq2.insert(0, "3");
    seq2.insert(0, "2");
    // seq2 : 2, 3
    
    cerr << subsequence(seq1, seq2) << endl;
    seq1.dump();
    seq2.dump();
    
    //  TEST interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
    Sequence r;
    r.insert(0, "8");
    r.insert(0, "8");
    r.insert(0, "8");
    interleave(seq1, seq2, r);
    r.dump();
}
