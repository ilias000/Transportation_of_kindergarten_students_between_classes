#ifndef PAIRNODE_H
#define PAIRNODE_H
#include "Student.h"
#include <iostream>
using namespace std;

class PairNode
{
    Student * leftStudent;
    Student * rightStudent;
    PairNode * nextPairNode;
    int location; 
public:
    PairNode(Student*, Student*, const int); // constructor
    ~PairNode(); // destructor

    bool isTheLastPairNode(); // if the node is the last one it returns true
    PairNode** getNextPairNodePointer(); // returns the adrress of the pointer nextPairNode
    void setNextPairNode(PairNode* nextPairNode); // make the nextPairNode pointer point to the pairNode that the function called with
    string getLeftStudentsGender(); // returns the gender of the left student
    string getRightStudentsGender(); // returns the gender of the right student
    bool hasLeftStudent(); // returns true if it has left student
    bool hasRightStudent(); // returns true if it has right student
    Student * moveAloneStudent(); // returns the student of a pair with one student and removes this student from the pair
    Student * getAloneStudent(); // returns the student of a pair with one student
    void print(); // prints a pair
    bool isTheStudentInThisPair(Student *); // if the student is in this pair returns true
    bool isUnrulyPair(); // if both students are unruly returns true
    bool isTheRightStudent(Student*); // returns true if the student is the right one 
    bool isTheLeftStudent(Student*); // returns true if the student is the left one 

    void setRightStudent(Student * student) // inserts the student as the right student of the pair
    {this->rightStudent = student;}
    void setLeftStudent(Student * student) // inserts the student as the left student of the pair
    {this->leftStudent = student;}
    int getLocation() // returns the location of the pair
    {return location;}
    Student* getLeftStudent() // returns the left student of the pair
    {return leftStudent;}
    Student* getRightStudent() // returns the right student of the pair
    {return rightStudent;}
};
#endif