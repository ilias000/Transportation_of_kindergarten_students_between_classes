#ifndef PAIRLIST_H
#define PAIRLIST_H
#include "PairNode.h"
#include <iostream>
using namespace std;

class PairList
{
    int numberOfPairs = 0;
    PairNode* firstPairNode;

    PairNode** getLastPairsPointer(); // returns the nextPairNode pointer of the last pair of the list (it is private because we dont want the user to call this)
    void deletePairNodes(); // deletes every pairNode we created (it is private because we dont want the user to call this)
    string getLastPairsStructure(); // it returns FM if the the left student of the last pair is female and the right male else it returns MF (it is private because we dont want the user to call this)
public:
    PairList(); // constructor
    ~PairList(); // destructor

    void insertPair(Student*, Student*); // inserting a pair to the list
    PairNode* getLastPair(); // returns the last pair of the list 
    void deleteLastPair(); // deletes the last pair  
    void print(); // prints all the pairs
    PairNode* getStudentsPair(Student *); // returns a pointer to the pair of the student
    int numberOfUnrulyPairs(); // returns the number of unruling pairs
    int numberOfConsecutiveUnrulyPairs(Student*); // returns the number of consecutive unruling pairs if the student is part of one of these pairs
    PairNode* getNthPair(int); // returns the Nth pair
};
#endif