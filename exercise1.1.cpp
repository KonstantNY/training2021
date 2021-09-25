//exercise1.1
#include <iostream>
#include <string.h>
#include <iomanip> // setw()
#include <stdlib.h> //rand()

//#define manualInit

using std::cout;
using std::setfill;
using std::setw;
using std::setiosflags;
using std::ios;
using std::resetiosflags;
using std::endl;
using std::string;


constexpr int SIZE = 3;

struct Student
{
	string firstName;
	string lastName;
	int grades[SIZE];
};

int min(int* arr, int n)
{
	int minElement = arr[0];

	for(int i = 1; i < n; i++)
 		if (minElement > arr[i])
 			minElement = arr[i];
	return minElement;
}

void sort_1_Student(Student* stud, int n)
// sort by increasing of minimum grade
{
	Student tmp;

	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if(min(stud[i].grades, SIZE) > min(stud[j].grades, SIZE))
			{
				tmp = stud[i];
				stud[i] = stud[j];
				stud[j] = tmp;
			}
}

void printStudent(Student* stud, int n)
{
	// defining 'setw()' argument:
	int maxFirstName = stud[0].firstName.length();
	int maxLastName = stud[0].lastName.length();
	for(int k = 1; k < n; k++)
	{
		if(maxFirstName > stud[k].firstName.length())
			maxFirstName = stud[k].firstName.length();
		if(maxLastName > stud[k].lastName.length())
			maxLastName = stud[k].lastName.length();
	}
	//output itself
	cout << setiosflags(ios::left) <<
	        setw(maxFirstName + 1 + maxLastName) << 
	        "Student's name" << " |    Grades    |" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << setw(maxFirstName) << stud[i].firstName << " " <<
			    setw(maxLastName) << stud[i].lastName << " | ";
		for (int j = 0; j < 3; j++)
			cout << setiosflags(ios::right) << setw(2) << 
		            stud[i].grades[j] << " | " <<
		            resetiosflags(ios::right);
		cout << endl;
	}
}


int main()
{
	system("CLS");

    // // test of 'min(...)'
    // int arr[]{2, 4, 6, 2, 7, 1, 3};
    // cout << "min{2, 4, 6, 2, 7, 1, 3}: " << min(arr, 7);

#ifdef manualInit
	cout << "1. Enter a number of students: ";
	int n;
	cin >> n;

	cout << "2. Enter the first and last name, " << SIZE << 
	        " grades\n   (use [SPACE] as delimiter):" << endl;
	Student* stud = new Student[n];

	for (int i = 0; i < n; i++)
	{
		cout << setw(4) << i + 1 << ": ";
		cin >> stud[i].firstName >>
			   stud[i].lastName;
		for (int j = 0; j < SIZE; j++)
			cin >> stud[i].grades[j];
	}
#else
	int n = 5;
	Student* stud = new Student[n];
	for (int i = 0; i < n; i++)
	{
		stud[i].firstName = "FirstName";
		stud[i].lastName = "LastName";
		for (int j = 0; j < 3; j++)
			stud[i].grades[j] = rand() % 10 + 1;
	}
#endif

	cout << "1. Initial data:\n\n";
	printStudent(stud, n);

	sort_1_Student(stud, n);
	cout << "\n\n2. Sorted by increasing of minimum grade:\n" << endl;
	printStudent(stud, n);

	delete[] stud;

	return 0;
}
