#ifndef SEQUENCE_H
#define SEQUENCE_H
#include "Class.h"
#include <iostream>
using namespace std;

class Sequence
{
    Class ** classes;
    int K;
public:
    Sequence(const int &, const int &, Student **, const int &, const int &); // constructor
    ~Sequence(); // destructor

    void print(); // prints the sequence of the classes by printing the classes
    void actions(Student * student); // necessary actions for unruly student
    void exchangeStudentWithStudentFromTheClass(Student *); //exchanging with random student of the same gender from the students class
    void exchangePairWithStudentsFromTheClass(Student *); // exchanging both students of the students pair with random students of the same gender from the students class
    void exchangePairWithStudentsFromRandomClass(Student *); // exchanging both students of the students pair with random students of the same gender from a random class
    void exchangePairWithStudentsFromTheNextClass( Student *); // exchanging both students of the students pair with random students of the same gender from the next class
    void exchangetwostudents(Student*, Class*, Student*, Class*); // exchang the two students
    Student * findRandomStudentFromRandomClass(Student *); // finds a random student from a random class and returns him

};
#endif