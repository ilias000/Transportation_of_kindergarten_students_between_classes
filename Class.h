#ifndef CLASS_H
#define CLASS_H
#include "PairList.h"
#include <iostream>
using namespace std;

class Class
{
    int Tquiet, Tmessy;
    int classNumber, numberOfStudents, disorderDegree;
    PairList pairList;
public:
    Class(const int, Student**, const int, const int, const int, const int); // constructor
    ~Class(); // destructor
    
    void makePairFromAloneStudents(Class *); // finds the alone student of the class it has been called with and the alone student of the class that called it and makes a pair
    void print(); // prints the class by printing the sequence of the class
    PairNode* getStudentsPair(Student*); // returns a pointer to the pair of the student
    int numberOfUnrulyPairs(); // returns the number of unruling pairs of the class
    int numberOfConsecutiveUnrulyPairs(Student *); // returns the number of consecutive unruling pairs of the class that the student is now if the student is part of one of these pairs
    Student* findRandomStudent(Student *); // finds a random student from the students class and returns him
    Student * getNthStudent(int); // returns the Nth student of the the class
    void disorderDegreePlus2() // +2 on the disorder Degree
    {disorderDegree = disorderDegree + 2;}
    void disorderDegreePlus1() // +1 on the disorder Degree
    {disorderDegree = disorderDegree + 1;}


    int getClassNumber() // returns the class number
    {return classNumber;}
};
#endif