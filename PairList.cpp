#include "PairList.h"
#include "Student.h"
#include <iostream>
using namespace std;

PairList::PairList() : firstPairNode(NULL)// constructor
{
    cout << endl << "Creating a PairList " << endl;
}


PairList::~PairList() // destructor
{
    cout << "Deleting a PairList " << endl;
    deletePairNodes(); // delete all the pairNodes
}


 void PairList::insertPair(Student*  male , Student* female) // inserting a pair to the list
 {
    PairNode** lastPairNodePointer = NULL; // will point to the nextPairNode pointer of the last pair in the list
    lastPairNodePointer = getLastPairsPointer();
    int location = numberOfPairs;


    Student* leftStudent = male;
    Student* rightStudent = female;

    string lastPairsStructure = getLastPairsStructure();
    if(lastPairsStructure == "FM") // in the last pair the left student is female and the right student is male
    {
        leftStudent = male;
        rightStudent = female;
    }
    else if(lastPairsStructure == "MF") // in the last pair the left student is male and the right student is female
    {
        leftStudent = female;
        rightStudent = male;
    }
    // because if a student does not have a pair he will be entered last the pair before him will be FM or MF so we dont have to check if the pair is -F or -M 0r F- or M-

    *lastPairNodePointer = new PairNode(leftStudent, rightStudent, location); // making the nextPairNode pointer of the last pair in the list point to the next pair we creating
    numberOfPairs++;
 }


 PairNode** PairList::getLastPairsPointer() // returns the nextPairNode pointer of the last pair of the list
 {
    PairNode** nextPairNodePointer = NULL; // wil point to the nextPairNode pointer of the last pairNode
    PairNode** nextPairNode = NULL; // will point to a pairNode and every time if this node is not the last one it will point to the next one 
    if(firstPairNode == NULL) // the list is empty
    {
        nextPairNodePointer = &firstPairNode;
    }
    else // the list is not empty
    {
        nextPairNode = &firstPairNode;
        while((*nextPairNode)->isTheLastPairNode() == false) // while this is not the last node
        {
            nextPairNode = (*nextPairNode)->getNextPairNodePointer(); // go to the next node
        }
        nextPairNodePointer = (*nextPairNode)->getNextPairNodePointer(); // points to the nextPairNode pointer of the last pairNode
    }
    return nextPairNodePointer;
 }


 void PairList::deletePairNodes() // deletes every pairNode we created 
 {
    PairNode** lastPairNode = NULL; // will point to the nextPairNode pointer that points to the last pairNode

    while(firstPairNode != NULL) // if the firstPairNode is not NULL then the list is not empty yet 
    {
        lastPairNode = &firstPairNode; // starting fromm the start of the list 
        while((*lastPairNode)->isTheLastPairNode() == false) // while this is not the last node
        {
            lastPairNode = (*lastPairNode)->getNextPairNodePointer(); // go to the next node
        }
        delete *lastPairNode; // deleting the last pairNode
        *lastPairNode = NULL; // making the pointer that pointed to the last pairNode NULL
    }
 }


 string PairList::getLastPairsStructure() // it returns FM if the the left student of the last pair is female and the right male else it returns MF
 {  
     PairNode** lastPairNode = NULL; // will point to the nextPairNode pointer that points to the last pairNode
     string lastPairsStructure;
     if(firstPairNode == NULL) // the list is empty
    {
        lastPairsStructure = "MF"; // we will return MF so the first pair will be FM 
    }
    else // the list is not empty
    {
        lastPairNode = &firstPairNode; // starting form the start of the list 
        while((*lastPairNode)->isTheLastPairNode() == false) // while this is not the last node
        {
            lastPairNode = (*lastPairNode)->getNextPairNodePointer(); // go to the next node
        }

        if(((*lastPairNode)->getLeftStudentsGender() == "FEMALE") && ((*lastPairNode)->getRightStudentsGender() == "MALE"))
        {
            lastPairsStructure = "FM";
        }
        else if(((*lastPairNode)->getLeftStudentsGender() == "MALE") && ((*lastPairNode)->getRightStudentsGender() == "FEMALE"))
        {
            lastPairsStructure = "MF";
        }
    }
    return lastPairsStructure;
 }


 PairNode* PairList::getLastPair() // returns the last pair of the list 
 {
    PairNode** lastPairNode = NULL; // will point to the nextPairNode pointer that points to the last pairNode
    lastPairNode = &firstPairNode; // starting fromm the start of the list 
    while((*lastPairNode)->isTheLastPairNode() == false) // while this is not the last node
    {
        lastPairNode = (*lastPairNode)->getNextPairNodePointer(); // go to the next node
    }
    return *lastPairNode;
 }


 void PairList::deleteLastPair() // deletes the last pair 
 {
    PairNode** lastPairNode = NULL; // will point to the nextPairNode pointer that points to the last pairNode

    lastPairNode = &firstPairNode; // starting from the start of the list 
    while((*lastPairNode)->isTheLastPairNode() == false) // while this is not the last node
    {
        lastPairNode = (*lastPairNode)->getNextPairNodePointer(); // go to the next node
    }
    delete *lastPairNode; // deleting the last pairNode
    *lastPairNode = NULL; // making the pointer that pointed to the last pairNode NULL
 }


 void PairList::print() // prints all the pairs
 {
    PairNode** nextPairNode = NULL; // will point to the nextPairNode pointer

    nextPairNode = &firstPairNode; // starting from the start of the list 
    while((*nextPairNode)->isTheLastPairNode() == false) // while this is not the last node 
    {
        (*nextPairNode)->print(); // prints the pair
        cout << endl;
        nextPairNode = (*nextPairNode)->getNextPairNodePointer(); // go to the next node
    }
    (*nextPairNode)->print(); // prints the last pair
 }


 PairNode* PairList::getStudentsPair(Student * student) // returns a pointer to the pair of the student
 {
    PairNode** studentsPair = NULL; // will point to the nextPairNode pointer that points to the students pairNode

    studentsPair = &firstPairNode; // starting from the start of the list 
    while((*studentsPair)->isTheStudentInThisPair(student) == false) // while the student is not inside this pair
    {
        studentsPair = (*studentsPair)->getNextPairNodePointer(); // go to the next node
    }
    return *studentsPair;
}


int PairList::numberOfUnrulyPairs() // returns the number of unruling pairs
{
    int numberOfUnrulyPairs = 0;
    PairNode** lastPairNode = NULL; // will point to the nextPairNode pointer that points to the last pairNode

    lastPairNode = &firstPairNode; // starting from the start of the list 
    while((*lastPairNode)->isTheLastPairNode() == false) // while this is not the last node
    {
        if((*lastPairNode)->isUnrulyPair() == true)
            numberOfUnrulyPairs++;
        lastPairNode = (*lastPairNode)->getNextPairNodePointer(); // go to the next node
    }
    if((*lastPairNode)->isUnrulyPair() == true)
            numberOfUnrulyPairs++;
    return numberOfUnrulyPairs;
}


int PairList::numberOfConsecutiveUnrulyPairs(Student * student) // returns the number of consecutive unruling pairs if the student is part of one of these pairs
{
    int numberOfConsecutiveUnrulyPairs = 0; // if the student is not part of one of these pairs it will return 0
    PairNode** nextPairNode = NULL; // will point to the nextPairNode pointer that points to a pairNode
    bool previousWas = false;
    bool StudentIsPart = false;

    nextPairNode = &firstPairNode; // starting from the start of the list 

    while((*nextPairNode)->isTheLastPairNode() == false) // while this is not the last node
    {
        if((*nextPairNode)->isUnrulyPair() == true)
        {
            if(previousWas == true)
                numberOfConsecutiveUnrulyPairs++;
            else
            {
                numberOfConsecutiveUnrulyPairs++;
                previousWas = true;
            }
            
            if((*nextPairNode)->isTheStudentInThisPair(student) == true)
                StudentIsPart = true;
        }
        else 
        {
            if(StudentIsPart == true)
                return numberOfConsecutiveUnrulyPairs;

            numberOfConsecutiveUnrulyPairs = 0;
            previousWas = false;
        }
        nextPairNode = (*nextPairNode)->getNextPairNodePointer(); // go to the next node
    }
    if((*nextPairNode)->isUnrulyPair() == true) // for the last one
    {
        if(previousWas == true)
        {
            numberOfConsecutiveUnrulyPairs++;
        }
        else
        {
            numberOfConsecutiveUnrulyPairs++;
            previousWas = true;
        }
        
        if((*nextPairNode)->isTheStudentInThisPair(student) == true)
            StudentIsPart = true;
    }
    else 
    {
        if(StudentIsPart == true)
            return numberOfConsecutiveUnrulyPairs;

        numberOfConsecutiveUnrulyPairs = 0;
        previousWas = false;
    }
    return numberOfConsecutiveUnrulyPairs;
}


PairNode* PairList::getNthPair(int indexOfPair) // returns the Nth pair
{
    PairNode** NthPairNode = NULL; // will point to the nextPairNode pointer that points to the Nth pairNode

    NthPairNode = &firstPairNode; // starting from the start of the list 
    while((*NthPairNode)->isTheLastPairNode() == false) // while the pair is not the last pair
    {
        if((*NthPairNode)->getLocation() == indexOfPair)
            break;
        NthPairNode = (*NthPairNode)->getNextPairNodePointer(); // go to the next node
    }
    return *NthPairNode;
}