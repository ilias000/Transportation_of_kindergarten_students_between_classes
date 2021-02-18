#ifndef STUDENT_H
#define STUDENT_H
#include <string>
#include <iostream>
using namespace std;

class Student
{
    bool unruly; // is true if a student is unruly
    string name;
    int classNumber;
    string gender;
    int classNumberThatIsNow; // is the number of the class that the student is now
public:
    Student(const string, const int, const string); // constructor
    ~Student(); // destructor

    void printStudent(); // prints the student

    void printName() // prints the students name
    {cout << "Name : " << name << endl;}

    void printClassNumber() // prints the students class number
    {cout << "Class number : " << classNumber << endl;}

    void printGender() // prints the students gender
    {cout << "Gender : " << gender << endl;}

    string getGender() // returns the gender 
    {return gender;}

    string getName() // returns the name 
    {return name;}

    bool getUnruly() // returns True if a student is unruly
    {return unruly;}

    void becameUnruly() // the student became unruly
    {unruly = true;}

    void becameRuly() // the student became ruly
    {unruly = false;}

    int getClassNumberThatIsNow() // returns the number of the class that the student is now
    {return classNumberThatIsNow;}

    int getClassNUmber() // returns the class number
    {return classNumber;}

    void setClassNumberThatIsNow(int classNumberThatIsNow) // change the number of the class that the student is now
    {this->classNumberThatIsNow = classNumberThatIsNow;}
};
#endif