#include "PairNode.h"
#include "Student.h"
#include <iostream>
using namespace std;

PairNode::PairNode(Student * leftStudent, Student * rightStudent, const int location) : leftStudent(leftStudent), rightStudent(rightStudent), location(location), nextPairNode(NULL) // constructor
{
    if(this->leftStudent == NULL)
        cout << '\t' << '\t' << "Creating a Pair with ΝΟ left student and right student " << this->rightStudent->getName() << endl << endl;
    else if(this->rightStudent == NULL)
        cout << '\t' << '\t' << "Creating a Pair with left student " << this->leftStudent->getName() << " and NO right student " << endl << endl;
    else
        cout << '\t' << '\t' << "Creating a Pair with left student " << this->leftStudent->getName() << " and right student " << this->rightStudent->getName() << endl << endl;
}


PairNode::~PairNode() // destructor
{
    if((this->rightStudent == NULL) && (this->leftStudent == NULL))
        cout << endl << '\t' << '\t' << "Deleting the last Pair from this class (because the student from this pair became pair with another student from the previous class)" << endl; // when we make a pair from two alone students from two classes the pairNode of the second one will be deleted
    else if(this->leftStudent == NULL) // the pair has only right student
        cout << endl << '\t' << '\t' << "Deleting a Pair with NO left student and right student " << this->rightStudent->getName() << endl;
    else if(this->rightStudent == NULL) // the pair has only left student
        cout << endl << '\t' << '\t' << "Deleting a Pair with left student " << this->leftStudent->getName() << " and NO right student " << endl;
    else
        cout << endl << '\t' << '\t' << "Deleting a Pair with left student " << this->leftStudent->getName() << " and right student " << this->rightStudent->getName() << endl;

    // deleting the students of the pair
    if(leftStudent != NULL) // if the pair has a left student 
        delete leftStudent; 
    if(rightStudent != NULL) // if a pair has a right student
        delete rightStudent;
}


bool PairNode::isTheLastPairNode()  // if the node is the last one it returns true
{
    if(nextPairNode == NULL)
        return true;
    else
        return false;
}


PairNode** PairNode::getNextPairNodePointer() // returns the adrress of the pointer nextPairNode
{
    return &nextPairNode;
}


void PairNode::setNextPairNode(PairNode* nextPairNode) // make the nextPairNode pointer point to the pairNode that the function called with
{
    this->nextPairNode = nextPairNode;
}


string PairNode::getLeftStudentsGender() // returns the gender of the left student
{
    return leftStudent->getGender();
}


string PairNode::getRightStudentsGender() // returns the gender of the right student
{
    return rightStudent->getGender();
}


bool PairNode::hasLeftStudent() // returns true if it has left student
{
    if(leftStudent != NULL)
        return true;
    else 
        return false;
}


bool PairNode::hasRightStudent() // returns true if it has right student
{
    if(rightStudent != NULL)
        return true;
    else 
        return false;
}


Student * PairNode::moveAloneStudent() // returns the student of a pair with one student and removes this student from the pair
{
    Student * student = NULL;

    if((rightStudent == NULL) && (leftStudent != NULL))
    {
        student = leftStudent;
        leftStudent = NULL;
    }
    else if((rightStudent != NULL) && (leftStudent == NULL))
    {
        student = rightStudent;
        rightStudent = NULL;
    }
    return student;
}


Student * PairNode::getAloneStudent() // returns the student of a pair with one student
{
    Student * student = NULL;

    if((rightStudent == NULL) && (leftStudent != NULL))
    {
        student = leftStudent;
    }
    else if((rightStudent != NULL) && (leftStudent == NULL))
    {
        student = rightStudent;
    }
    return student;
}


void PairNode::print() // prints a pair
{
    cout << '\t' << '\t' << "Location of pair in the sequence is " << location << endl;
    if(leftStudent != NULL)
    {
        cout << '\t' << '\t' << "Left student of the pair is :" << endl;
        leftStudent->printStudent();
    }
    else 
        cout << '\t' << '\t' << "The pair has NO left student" << endl;

    if(rightStudent != NULL)
    {
        cout << '\t' << '\t' << "Right student of the pair is :" << endl; 
        rightStudent->printStudent();
    }
    else
        cout << '\t' << '\t' << "The pair has NO right student" << endl;
}


bool PairNode::isTheStudentInThisPair(Student * student) // if the student is in this pair returns true
{
    // the pointer that points to the left student of the pair or the pointer that points to the right student of the pair 
    // are pointing to the same memory address that the pointer that points to the student are pointing then its the same 
    // student so the student is inside this pair
    if((leftStudent == student) || (rightStudent == student)) 
        return true;
    else 
        return false;
}

bool PairNode::isUnrulyPair() // if both students are unruly returns true
{
    if((leftStudent != NULL) && (rightStudent != NULL))
    {
        if((leftStudent->getUnruly()) && (rightStudent->getUnruly()))
            return true;
        else 
            return false;
    }
}


    bool PairNode::isTheRightStudent(Student* student) // returns true if the student is the right one 
    {
        if(rightStudent == student)
            return true;
        else 
            return false;
    }


    bool PairNode::isTheLeftStudent(Student* student) // returns true if the student is the left one 
    {
        if(leftStudent == student)
            return true;
        else 
            return false;
    }