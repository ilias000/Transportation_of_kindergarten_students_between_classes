#include "Student.h"
#include <iostream>
using namespace std;

Student::Student(const string name , const int classNumber, const string gender) :  name(name), classNumber(classNumber), gender(gender), unruly(false), classNumberThatIsNow(classNumber)// constructor
{
    cout << endl << "A New Student has been created!" << endl;
    cout << "Name = " << this->name << endl;
    cout << "Class number = " << this->classNumber << endl;
    cout << "Gender = " << this->gender << endl;
}


Student::~Student() // destructor
{
    cout << '\t' << '\t' << '\t' << "A Student to be destroyed!" << endl;
    cout << '\t' << '\t' << '\t' << "Name = " << this->name << endl;
    cout << '\t' << '\t' << '\t' << "Class number = " << this->classNumber << endl;
    cout << '\t' << '\t' << '\t' << "Gender = " << this->gender << endl;
}

void Student::printStudent() // prints the student
{
    cout << '\t' << '\t' << '\t' << '\t' << "Name = " << this->name << endl;
    cout << '\t' << '\t' << '\t' << '\t' << "Class number = " << this->classNumber << endl;
    cout << '\t' << '\t' << '\t' << '\t' << "Gender = " << this->gender << endl;
    cout << '\t' << '\t' << '\t' << '\t' << "Class number that he is now = " << this->classNumberThatIsNow << endl;
}