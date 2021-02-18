#include "Sequence.h"
#include "Class.h"
#include <iostream>
using namespace std;


Sequence::Sequence(const int & K, const int & numberOfStudentsForOneClass, Student ** student, const int & Tquiet, const int & Tmessy) : K(K)// constructor
{
    cout << "Creating a sequence" << endl;
    classes = new Class*[K];
    for(int i = 0 ; i < K ; i++) // creating the sequence of the classes by creating the classes and the sequences for every class
    {
		int classNumber = i + 1; // it is i + 1 because  the class numbers starts from 1
		int firstIndex = (classNumber * numberOfStudentsForOneClass) - numberOfStudentsForOneClass;
		int lastIndex = (classNumber * numberOfStudentsForOneClass) - 1; // it is - 1 because we use it for the array
        classes[i] = new Class(classNumber, student, firstIndex, lastIndex, Tquiet, Tmessy); // creating a class and the sequence for the this class

		if((numberOfStudentsForOneClass % 2 == 1) && (classNumber % 2 == 0)) // the number of students for one class is odd so the last student will not
		{																	 // have a pair and the class number is even so the previous class has also the 
			classes[i]->makePairFromAloneStudents(classes[i - 1]);			 // last student without a pair and these two students have oposite genders 
		}																	 // so we will make them pair and put them in the first class of these two
    }
}


Sequence::~Sequence() // destructor
{
    cout << "Deleting a sequence" << endl;
    for(int i = 0 ; i < K ; i++)
        delete classes[i];
    delete[] classes;
}

void Sequence::print() // prints the sequence of the classes by printing the classes
{
    cout << "Printing the sequence of the classes :" << endl;
	for(int i = 0 ; i < K ; i++) // printing the sequence of the classes by printing the classes and the sequences for every class
    {
		cout << endl << '\t';
		cout << "Printing the sequence for the " << classes[i]->getClassNumber() << " class :" << endl;
		cout << endl;
		classes[i]->print(); // printing the class
    }
}


void Sequence::actions(Student * student) // necessary actions for unruly student
{
    if(student->getUnruly() == true) // because if a previous student had on his pair this student then the actions for both students have already been made
    {
        if((classes[student->getClassNumberThatIsNow() - 1 ]->getStudentsPair(student)->hasLeftStudent() == false ) || ((classes[student->getClassNumberThatIsNow() - 1 ]->getStudentsPair(student)->hasRightStudent()) == false)) // the student does not have a pair
        {
            // the student is alone 
            exchangeStudentWithStudentFromTheClass(student); //exchanging with random student of the same gender from the students class
        }
        else // the student have a pair
        {
            if(classes[student->getClassNumberThatIsNow() - 1 ]->getStudentsPair(student)->isUnrulyPair())// if true the students pair is also unruly
            {
                int numberOfUnrulyPairs = classes[student->getClassNumberThatIsNow() - 1]->numberOfUnrulyPairs(); // geting the number of unruling pairs of the class that the student is now
                int numberOfConsecutiveUnrulyPairs = classes[student->getClassNumberThatIsNow() -  1]->numberOfConsecutiveUnrulyPairs(student); // geting the number of consecutive unruling pairs of the class that the student is now (if the student is part of one of these pairs it schould be >=2)

                if(numberOfUnrulyPairs <= 2) // the unruly pairs are 1 or 2 
                {
                    // taking actions only for the pair of the student
                    exchangePairWithStudentsFromTheClass(student); // exchanging both students of the students pair with random students of the same gender from the students class
                }
                else // the number of unruly pairs is more than 2 
                {
                    if(numberOfConsecutiveUnrulyPairs >= 2) // the class that the student is inside now has consecutive unruly pairs and the student is part of one of these pairs
                    {
                        // taking actions only for the pair of the student
                        exchangePairWithStudentsFromRandomClass(student); // exchanging both students of the the students pair with random students of the same gender from a random class
                    }
                    else // the class that the student is inside now has unruly pairs but the pair of the student is not part of consecutive unruly pairs
                    {
                        // taking actions only for the pair of the student
                        exchangePairWithStudentsFromTheNextClass(student); // exchanging both students of the students pair with random students of the same gender from the next class
                    }
                }
            }
            else // this students pair is not unruly
            {
                exchangeStudentWithStudentFromTheClass(student); //exchanging with random student of the same gender from the students class
            }
        }
    }   
}


void Sequence::exchangeStudentWithStudentFromTheClass(Student * student) //exchanging with random student of the same gender from the students class
{
    Class * studentsClass = classes[student->getClassNumberThatIsNow() - 1]; // will point to the students class

    Student * randomStudent = studentsClass->findRandomStudent(student); // finds a random student from the students class and returns him

    Class * randomStudentsClass = classes[randomStudent->getClassNumberThatIsNow() - 1]; // will point to the randomStudents class
    exchangetwostudents(student, studentsClass, randomStudent, randomStudentsClass); // exchanging the two students
    classes[student->getClassNUmber() - 1]->disorderDegreePlus1();

    student->becameRuly();

    if(randomStudent->getUnruly() == true)
    {
        randomStudent->becameRuly();
        classes[randomStudent->getClassNUmber() - 1]->disorderDegreePlus1();
    }

    cout << "The sequences affected by the actions : " << endl;
    classes[student->getClassNumberThatIsNow() - 1]->print();
}



void Sequence::exchangePairWithStudentsFromTheClass(Student * student) // exchanging both students of the students pair with random students of the same gender from the students class
{
    Class * studentsClass = classes[student->getClassNumberThatIsNow() - 1]; // will point to the students class

    PairNode * studentsPair = studentsClass->getStudentsPair(student); // will point to the students pair

    Student * leftStudent =  studentsPair->getLeftStudent();
    Student * rightStudent = studentsPair->getRightStudent();

    Student * StudentForLeft = studentsClass->findRandomStudent(leftStudent); // finds a random student from the class and returns him
    Student * StudentForRight = studentsClass->findRandomStudent(rightStudent); // finds a random student from the class and returns him

    exchangetwostudents(leftStudent, studentsClass, StudentForLeft, studentsClass); // exchanging the two students
    classes[leftStudent->getClassNUmber() - 1]->disorderDegreePlus1();

    exchangetwostudents(rightStudent, studentsClass, StudentForRight, studentsClass); // exchanging the two students
    classes[rightStudent->getClassNUmber() - 1]->disorderDegreePlus1();

    leftStudent->becameRuly();
    rightStudent->becameRuly();
    
    if(StudentForLeft->getUnruly() == true)
    {
        StudentForLeft->becameRuly();
        classes[StudentForLeft->getClassNUmber() - 1]->disorderDegreePlus1();
    }
    if(StudentForRight->getUnruly() == true)
    {
        StudentForRight->becameRuly();
        classes[StudentForRight->getClassNUmber() - 1]->disorderDegreePlus1();
    }

    cout << "The sequences affected by the actions : " << endl;
    classes[leftStudent->getClassNumberThatIsNow() - 1]->print();
}


void Sequence::exchangePairWithStudentsFromRandomClass(Student * student) // exchanging both students of the students pair with random students of the same gender from a random class
{
    Class * studentsClass = classes[student->getClassNumberThatIsNow() - 1]; // will point to the students class

    PairNode * studentsPair = studentsClass->getStudentsPair(student); // will point to the students pair

    Student * leftStudent =  studentsPair->getLeftStudent();
    Student * rightStudent = studentsPair->getRightStudent();

    Student * randomStudentForLeft = findRandomStudentFromRandomClass(leftStudent); // finds a random student from a random class and returns him
    Student * randomStudentForRight = findRandomStudentFromRandomClass(rightStudent); // finds a random student from a random class and returns him

    Class * randomStudentForLeftClass = classes[randomStudentForLeft->getClassNumberThatIsNow() - 1]; // will point to the randomStudentForLeft class
    exchangetwostudents(leftStudent, studentsClass, randomStudentForLeft, randomStudentForLeftClass); // exchanging the two students
    classes[leftStudent->getClassNUmber() - 1]->disorderDegreePlus2();

    Class * randomStudentForRightClass = classes[randomStudentForRight->getClassNumberThatIsNow() - 1]; // will point to the randomStudentForRight class
    exchangetwostudents(rightStudent, studentsClass, randomStudentForRight, randomStudentForRightClass); // exchanging the two students
    classes[rightStudent->getClassNUmber() - 1]->disorderDegreePlus2();

    leftStudent->becameRuly();
    rightStudent->becameRuly();

    if(randomStudentForLeft->getUnruly() == true)
    {
        randomStudentForLeft->becameRuly();
        classes[randomStudentForLeft->getClassNUmber() - 1]->disorderDegreePlus2();
    }
    if(randomStudentForRight->getUnruly() == true)
    {
        randomStudentForRight->becameRuly();
        classes[randomStudentForRight->getClassNUmber() - 1]->disorderDegreePlus2();
    }

    cout << "The sequences affected by the actions : " << endl;
    classes[leftStudent->getClassNumberThatIsNow() - 1]->print();
    if((leftStudent->getClassNumberThatIsNow() - 1) != (rightStudent->getClassNumberThatIsNow() - 1))
        classes[rightStudent->getClassNumberThatIsNow() - 1]->print();
    classes[randomStudentForLeft->getClassNumberThatIsNow() - 1]->print();
}


void Sequence::exchangePairWithStudentsFromTheNextClass( Student * student) // exchanging both students of the students pair with random students of the same gender from the next class
{
    Class * studentsClass = classes[student->getClassNumberThatIsNow() - 1]; // will point to the students class
    Class * nextClass = NULL; // will point to the class that the studnet will go which is the the next class or if there is no next class the first class of the sequence
    if(student->getClassNumberThatIsNow() < K) // there is a next class
        nextClass = classes[student->getClassNumberThatIsNow()];
    else // there is not next class
        nextClass = classes[0]; // put him in the first class of the sequence

    PairNode * studentsPair = studentsClass->getStudentsPair(student); // will point to the students pair

    Student * leftStudent =  studentsPair->getLeftStudent();
    Student * rightStudent = studentsPair->getRightStudent();

    Student * StudentForLeft = nextClass->findRandomStudent(leftStudent); // finds a random student from the nextClass class and returns him
    Student * StudentForRight = nextClass->findRandomStudent(rightStudent); // finds a random student from the nextClass class and returns him

    exchangetwostudents(leftStudent, studentsClass, StudentForLeft, nextClass); // exchanging the two students
    classes[leftStudent->getClassNUmber() - 1]->disorderDegreePlus2();

    exchangetwostudents(rightStudent, studentsClass, StudentForRight, nextClass); // exchanging the two students
    classes[rightStudent->getClassNUmber() - 1]->disorderDegreePlus2();

    leftStudent->becameRuly();
    rightStudent->becameRuly();

    if(StudentForLeft->getUnruly() == true)
    {
        StudentForLeft->becameRuly();
        classes[StudentForLeft->getClassNUmber() - 1]->disorderDegreePlus2();
    }
    if(StudentForRight->getUnruly() == true)
    {
        StudentForRight->becameRuly();
        classes[StudentForRight->getClassNUmber() - 1]->disorderDegreePlus2();
    }

    cout << "The sequences affected by the actions : " << endl;
    classes[leftStudent->getClassNumberThatIsNow() - 1]->print();
    classes[StudentForLeft->getClassNumberThatIsNow() - 1]->print();
}


void Sequence::exchangetwostudents(Student* student, Class* studentsClass, Student* randomStudent, Class* randomStudentsClass) // exchange the two students
{
    PairNode * studentsPair = classes[student->getClassNumberThatIsNow() - 1]->getStudentsPair(student); // wil point to the students pair
    PairNode * randomStudentsPair = classes[randomStudent->getClassNumberThatIsNow() - 1]->getStudentsPair(randomStudent); // will point to the randomsStudents Pair
    int newClassNumberOfStudent = randomStudent->getClassNumberThatIsNow();
    int newClassNumberOfRamdomStudent = student->getClassNumberThatIsNow();


    if(studentsPair->isTheLeftStudent(student) == true)
    {
        if(randomStudentsPair->isTheLeftStudent(randomStudent) == true)
        {
            randomStudentsPair->setLeftStudent(student);
            student->setClassNumberThatIsNow(newClassNumberOfStudent);
            studentsPair->setLeftStudent(randomStudent);
            randomStudent->setClassNumberThatIsNow(newClassNumberOfRamdomStudent);
        }
        else if(randomStudentsPair->isTheRightStudent(randomStudent) == true)
        {
            randomStudentsPair->setRightStudent(student);
            student->setClassNumberThatIsNow(newClassNumberOfStudent);
            studentsPair->setLeftStudent(randomStudent);
            randomStudent->setClassNumberThatIsNow(newClassNumberOfRamdomStudent);
        }
    }
    else if(studentsPair->isTheRightStudent(student) == true)
    {
        if(randomStudentsPair->isTheLeftStudent(randomStudent) == true)
        {
            randomStudentsPair->setLeftStudent(student);
            student->setClassNumberThatIsNow(newClassNumberOfStudent);
            studentsPair->setRightStudent(randomStudent);
            randomStudent->setClassNumberThatIsNow(newClassNumberOfRamdomStudent);
        }
        else if(randomStudentsPair->isTheRightStudent(randomStudent) == true)
        {
            randomStudentsPair->setRightStudent(student);
            student->setClassNumberThatIsNow(newClassNumberOfStudent);
            studentsPair->setRightStudent(randomStudent);
            randomStudent->setClassNumberThatIsNow(newClassNumberOfRamdomStudent);
        }
    }
}


Student * Sequence::findRandomStudentFromRandomClass(Student * student) // finds a random student from a random class and returns him
{
    int randomClassNumber = rand() % K; // random class Number [0, K)

    return classes[randomClassNumber]->findRandomStudent(student); // finds a random student from the class and returns him
}