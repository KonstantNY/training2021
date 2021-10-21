//exercise1.1
#include <iostream>
#include <string.h>
#include <iomanip> // setw()
#include <stdlib.h> //rand()

//#define manualInit // switches off/on manual entering of Struct*

using std::cout;
using std::cin;
using std::setw;
using std::setiosflags;
using std::ios;
using std::resetiosflags;
using std::endl;
using std::string;

constexpr int numberOfGrades = 5; // can be changed seamlessly if program is recompiled

struct Student
{
    // I hope, it's acceptable here to initialize init values in structure 'drawing' (unlike in class)
    string firstName = "[empty first name]";
    string lastName =  "[empty last name]";
    int grades[numberOfGrades]{0};
    // initialized 'indexOfMinGrade' just to prevent marking pseudo min grades before sorting
    // instead of tracing 'sorted' / 'not sorted' state of 'Student*' (i.e. of array)
    int indexOfMinGrade = -1; 
};

int min(Student& stud, int grades)
{
    int minGrade = stud.grades[0];
    stud.indexOfMinGrade = 0;

    for(int i = 1; i < grades; i++)
        if (minGrade > stud.grades[i])
        {
            minGrade = stud.grades[i];
            stud.indexOfMinGrade = i;
        }
    //cout << "(debug) minGrade: " << minGrade << endl; 
    return minGrade;
}

void sort_1_Student(Student* stud, int students)
// sort by increasing of minimum grade
{
    Student tmp;
    for (int i = 0; i < students - 1; i++)
        for (int j = i + 1; j < students; j++)
            if(min(stud[i], numberOfGrades) > min(stud[j], numberOfGrades))
            {
                tmp = stud[i];
                stud[i] = stud[j];
                stud[j] = tmp;
            }
}

void printStudent(Student* stud, int n)
{
    // defining 'setw()' argument:
    // we need the next behavior (alignment) of printed table in names' column
    // case 1:
    // "Student's name | Grades"
    // "Bill Gates^^^^ |       ", where by '^' added space is marked
    // case 2:
    // "^^^Student's name | Grades", where by '^' added space is marked
    // "Richard Hendricks |       "
    // i.e. all for the sake of proper 'setwArgument' calculation
    const string namesHead = "Student's name";
    const string gradesHead = "Grades";
    const string namesDelimiter = " ";
    const string namesFromGradesDelimiter = " | ";
    int maxFirstName = stud[0].firstName.length();
    int maxLastName = stud[0].lastName.length();
    for(int k = 1; k < n; k++)
    {
        if(maxFirstName < stud[k].firstName.length())
            maxFirstName = stud[k].firstName.length();
        if(maxLastName < stud[k].lastName.length())
            maxLastName = stud[k].lastName.length();
    }
    cout << endl;
    int namesHeadLength = namesHead.length();
    int namesLength = maxFirstName +
                      namesDelimiter.length() + 
                      maxLastName;
    int setwArgument = ( (namesHeadLength > namesLength) ? namesHeadLength : namesLength );
    cout << setw(setwArgument) << 
            namesHead <<
            namesFromGradesDelimiter <<
            gradesHead << endl;

    // printing itself finally :)
    for (int i = 0; i < n; i++)
    {
        cout << setiosflags(ios::left) <<
                setw(setwArgument) << 
                stud[i].firstName + 
                namesDelimiter + 
                stud[i].lastName <<
                namesFromGradesDelimiter <<
                resetiosflags(ios::left);
        for (int j = 0; j < numberOfGrades; j++)
            cout << setw(3) << 
                    stud[i].grades[j] <<
                    ( (j == stud[i].indexOfMinGrade) ? " *| " : "  | ");
        cout << "(dbg)* " << stud[i].indexOfMinGrade;
        cout << endl;
    }
}


int main()
{
    system("CLS");

    // // test of 'min(...)'
    // int arr[]{2, 4, 6, 2, 7, 1, 3};
    // cout << "min{2, 4, 6, 2, 7, 1, 3}: " << min(arr, 7);
    int numberOfStudents;

#ifdef manualInit
    cout << "1. Enter a number of students: ";
    cin >> numberOfStudents;
    cout << "2. Enter the first and last name, " << numberOfGrades << 
            " grades (from 1 to 10)\n   (use [SPACE] as delimiter):" << endl;
    Student* stud = new Student[numberOfStudents];
    for (int i = 0; i < numberOfStudents; i++)
    {
        cout << setw(4) << i + 1 << ": ";
        cin >> stud[i].firstName >>
               stud[i].lastName;
        for (int j = 0; j < numberOfGrades; j++)
            cin >> stud[i].grades[j];
    }
#else
    numberOfStudents = 10; // can be changed seamlessly if program is recompiled
    string names[10] = {"Bill", "Sergey", "Steve", "Jeff", "Mark",
                        "Hendricks", "Belson", "Hanneman", "Bachman", "'Big Head'"};
    Student* stud = new Student[numberOfStudents];
    for (int i = 0; i < numberOfStudents; i++)
    {
        stud[i].firstName = names[rand() % 5];
        stud[i].lastName = names[rand() % 5 + 5];
        for (int j = 0; j < numberOfGrades; j++)
            stud[i].grades[j] = rand() % 10 + 1;
    }
#endif
    cout << "(debug) '#define manualInit' is commented, i.e. manual input is turned off\n"; 
    cout << endl;
    cout << "1. Initial data:\n";
    printStudent(stud, numberOfStudents);
    cout << endl;

    sort_1_Student(stud, numberOfStudents);
    cout << "\n2. Sorted by increasing of minimum grade:\n" <<
            "(by '*' symbol student's min grade is marked)\n";
    printStudent(stud, numberOfStudents);
    cout << endl;

    delete[] stud;

    return 0;
}
