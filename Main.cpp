#include "Student.h"
#include "Sequence.h"
#include <cstdlib>     
#include <ctime>
#include <string>
#include <iostream>
using namespace std;


int main(int argc, char *argv[])
{
	cout << "                             --- THE PROGRAM STARTED ---                                 " << endl ;

	int K = stoi(argv[1]), L = stoi(argv[2]), Tquiet = stoi(argv[3]), Tmessy = stoi(argv[4]); 
	cout << "K = " << K << endl;
	cout << "L = " << L << endl;
	cout << "Tquiet = " << Tquiet << endl;
	cout << "Tmessy = " << Tmessy << endl << endl;

	cout << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl << endl ;
	cout << "                       1. Να δημιουργεί ένα σύνολο μαθητών που ανήκουν σε " << K << " τμήματα." << endl;
	cout << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl << endl ;

	cout << "                                ~ Creating Students ~ " << endl << endl;
															     //          _
	srand((unsigned) time(0));								     //        / /
                                                                 //       / /____________________________________________________________
	int numberOfStudentsForOneClass = 11; // NUMBER OF STUDENTS 	     |   ____________________________________________________________|			
	int totalNumberOfStudents = K * numberOfStudentsForOneClass; //       \ \
																 //        \_\

	Student * student[totalNumberOfStudents]; // creating a array of pointers to Student objects 

	for(int i = 1, classNumber = 1, studentForThisClass = 0 ; i <= totalNumberOfStudents ; i++)
	{
		// random names
		string maleName[] = {"ΓΕΩΡΓΙΟΣ", "ΚΩΝΣΤΑΝΤΙΝΟΣ", "ΙΩΑΝΝΗΣ", "ΝΙΚΟΛΑΟΣ", "ΧΡΗΣΤΟΣ", "ΠΑΝΑΓΙΩΤΗΣ", "ΒΑΣΙΛΕΙΟΣ", "ΑΘΑΝΑΣΙΟΣ", "ΜΙΧΑΗΛ", "ΣΠΥΡΙΔΩΝ"}; // array to choose a random name for males	
		string femaleName[] = {"ΜΑΡΙΑ", "ΕΛΕΝΗ", "ΑΙΚΑΤΕΡΙΝΗ", "ΒΑΣΙΛΙΚΗ", "ΚΛΑΙΡΗ", "ΓΕΩΡΓΙΑ", "ΣΟΦΙΑ", "ΑΝΑΣΤΑΣΙΑ", "ΕΥΑΓΓΕΛΙΑ", "ΙΩΑΝΝΑ"}; // array to choose a random name for females
        string genderArray[] = {"MALE", "FEMALE"};
        string gender;
        string name;
        if(i % 2 == 0)  // creating one male - one female alternately so we can create the pairs after
        {
            name = maleName[rand() % 10]; // random number [0,9] (because its index for the array) to choose a male name
            gender = "MALE";
        }
        else
        {
            name = femaleName[rand() % 10]; // random number [0,9] (because its index for the array) to choose a female name
            gender = "FEMALE";
        }
        student[i-1] = new Student(name, classNumber, gender); // creating students with random names and inserting them to the array
		studentForThisClass++;
		if(studentForThisClass == numberOfStudentsForOneClass) // this class is full so go to the next one
		{
			classNumber++;
			studentForThisClass = 0;
		}
	}

	cout << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl << endl;
	cout << "                       2. Να δημιουργεί ακολουθίες για τα τμήματα στα οποία ανήκουν." << endl; 
	cout << "                                                     ΚΑΙ                            " << endl;
	cout << "                       3. Να δημιουργεί την ακολουθία των τμημάτων.                 " << endl;
	cout << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    
	Sequence sequence(K, numberOfStudentsForOneClass, student, Tquiet, Tmessy);
    

	cout << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl << endl ;
	cout << "                       4. Να εκτυπώνει την ακολουθία αυτή." << endl;
	cout << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl << endl ;

	sequence.print();



	cout << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl << endl ;
	cout << "                       5. Για " << L <<" ϕορές, να επιλέγονται τυχαίου πλήθους τυχαία παιδιά να κάνουν αταξίες." << endl;
	cout << "                          Για κάθε παιδί, να εκτυπώνονται τα στοιχεία του, να γίνονται οι απαραίτητες ενέργειες" << endl;
 	cout << "                          και να εκτυπώνονται οι ακολουθίες που επηρεάστηκαν από τις ενέργειες αυτές." << endl;
	cout << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl << endl ;

	for(int i = 0 ; i < L ; i++) // L times
	{
		int randomNumberOfStudents = rand() % (totalNumberOfStudents + 1); // random number of students that will be unruly [0, totalNumberOfStudents]

		Student * unrulyStudents[randomNumberOfStudents]; // creating a array of pointers to Student objects 
		int unrulyIndex = 0 ; // index for the unrulyStudents array
		
		cout << "For L = " << i << " the number of students that will be unruly is " << randomNumberOfStudents << " from " << totalNumberOfStudents << endl;

		for(int j = 0 ; j < randomNumberOfStudents ; j++) // making a random student unrly for randomNumberOfStudents students
		{
			int randomIndex = 0;
			do // find a student that is ruly and make him unruly
			{
				randomIndex = rand() % totalNumberOfStudents; // [0, totalNumberOfStudents) because its index for the array of students
			} while (student[randomIndex]->getUnruly() == true);
			student[randomIndex]->becameUnruly(); // make the student unruly
			unrulyStudents[unrulyIndex] = student[randomIndex]; // inserting the student to the array with the unruly students
			unrulyIndex++;
		}

		for(int k = 0; k < randomNumberOfStudents ; k++)
		{
			unrulyStudents[k]->printStudent(); // printing the unruly student
			cout << endl;
			sequence.actions(unrulyStudents[k]); // necessary actions
		}
	}


	cout << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl << endl ;
	cout << "                       6. Τέλος, να εκτυπώνεται η ακολουθία των τμημάτων, όπως αυτή θα έχει διαμορϕωθεί." << endl;
	cout << endl << "-----------------------------------------------------------------------------------------------------------------------------" << endl << endl ;

	sequence.print();

	cout << "                             --- THE PROGRAM ENDED ---                                 " << endl << endl ;
	return 0;
}