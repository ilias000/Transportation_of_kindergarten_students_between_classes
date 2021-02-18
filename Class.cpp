#include "Class.h"
#include "Student.h"
#include <iostream>
using namespace std;

Class::Class(const int classNumber, Student** student, const int firstIndex, const int lastIndex, const int Tquiet, const int Tmessy) : classNumber(classNumber), disorderDegree(0), numberOfStudents((lastIndex + 1) - firstIndex), Tquiet(Tquiet), Tmessy(Tmessy) // constructor
{
    cout << "A new Class has been created with class number : " << classNumber << endl << endl;
    
    int last = lastIndex; // because if the last one does not have a pair we dont want the for to use him
    if( numberOfStudents % 2 == 1) // a student does not have a pair
    {
        last = lastIndex - 1; // because we want the for loop to run only for the pairs of students
    }
    
    for(int i = firstIndex ; i <= last ; i += 2) // it will run for all the pairs 
    {
        Student *male = NULL;
        Student *female = NULL;

        if(student[i]->getGender() == "MALE") // it is AKAKAKAKAK
        {
            male = student[i];
            female = student[i + 1];
        }
        else // it is KAKAKAKAKA
        {
            female = student[i];
            male = student[i + 1];
        }

        // creating the pair
        pairList.insertPair(male, female);
    }

    if( numberOfStudents % 2 == 1) // a student does not have a pair
    {
            Student *male = NULL;
            Student *female = NULL;
            // the alone student will be last so
            if(student[lastIndex]->getGender() == "MALE") // the student with no pair is a male 
                male = student[lastIndex]; // the male points to the student and the female to null
            else // the student with no pair is a female 
                female = student[lastIndex]; // the female points to the student and male to null

            pairList.insertPair(male, female); // one points to the student and the other to null
    }
}


Class::~Class() // destructor
{
    cout << endl << endl << "Deleting Class with class number : " << classNumber << endl;
}



void Class::makePairFromAloneStudents(Class * previousClass) // finds the alone student of the class it has been called with and the alone student of the class that called it and makes a pair
{
    PairNode * previousClassLastPair = previousClass->pairList.getLastPair(); // will point to the last pair of the previous class
    PairNode * thisClassLastPair = this->pairList.getLastPair(); // will point to the last pair of this class
    Student * studentToBeMoved = thisClassLastPair->moveAloneStudent();
    Student * studentOfPreviousClass = previousClassLastPair->getAloneStudent();

    if(previousClassLastPair->hasLeftStudent()) // if true the last pair of the previous class has left student and no right student
    {
        previousClassLastPair->setRightStudent(studentToBeMoved); // inserting the alone studnet of this class as the right student of the last pair of the previous class
    }
    else // the last pair of the previous class has right student and no left student
    {
        previousClassLastPair->setLeftStudent(studentToBeMoved); // inserting the alone student of this class as the left student of the last pair of the previous class
    }
    studentToBeMoved->setClassNumberThatIsNow(studentOfPreviousClass->getClassNumberThatIsNow());
    this->pairList.deleteLastPair(); // deleting the last pair of this class because it has no students
    numberOfStudents--; // one student left
    previousClass->numberOfStudents++; // one student came
}


void Class::print() // prints the class by printing the sequence of the class
{
    if(disorderDegree < (Tquiet * numberOfStudents))
        cout << "What a quiet class!" << endl;
    else if(disorderDegree > (Tmessy * numberOfStudents))
        cout << "What a mess!" << endl;
    else 
        cout << "Please, be quiet!" << endl;
    pairList.print(); // printing the list of pairs
    
}


PairNode* Class::getStudentsPair(Student* student) // returns a pointer to the pair of the student
{
    return pairList.getStudentsPair(student);
}


int Class::numberOfUnrulyPairs() // returns the number of unruling pairs of the class
{
    return pairList.numberOfUnrulyPairs();
}

int Class::numberOfConsecutiveUnrulyPairs(Student * student) // returns the number of consecutive unruling pairs of the class that the student is now if the student is part of one of these pairs
{
    return pairList.numberOfConsecutiveUnrulyPairs(student);
}


Student* Class::findRandomStudent(Student * student) // finds a random student from the students class and returns him
{
    Student * randomStudent; // will point to the random student
    do
    {
        int randomStudentsIndex = rand() % numberOfStudents; // [0, numberOfStudents)
        randomStudent = getNthStudent(randomStudentsIndex); // random student points to the randomStudentIndexth student of the class
    } while ((randomStudent == NULL) || (randomStudent == student) || (randomStudent->getGender() != student->getGender())); // if the random student is the same student as the student or he has deferend gender find another one

    return randomStudent;
}


Student * Class::getNthStudent(int index) // returns the Nth student of the class
{
    PairNode * NthPair = NULL;
    Student * NthStudent = NULL;
    int indexOfPair;

    if(index % 2 == 0) // index of pair in even 
        indexOfPair = index / 2;
    else // index of pair is odd
        indexOfPair = (index / 2 ) + 1;

    NthPair = pairList.getNthPair(indexOfPair); // we have the pair that the indexth student is inside

    if(index % 2 == 0) // index of pair is even so the student is at the left position of the pair
        NthStudent = NthPair->getLeftStudent();
    else // index of pair is odd so the student is at the left position of the pair
        NthStudent = NthPair-> getRightStudent();

    return NthStudent;
    
}