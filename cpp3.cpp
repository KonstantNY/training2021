//exercise3.0
// Тема: конструктор и деструктор.
// Цель работы: рассмотреть принцип работы конструкторов (с параметрами, 
//           с параметрами по умолчанию) и деструктора при работе с объектами.
// Задание:
//     1. Разработать класс «вектор» (одномерный динамический массив). 
//        Методы класса: конструкторы, деструктор и методы преобразования массива 
//        в соответствии с вариантом. 
//     2. Ввести 2 массива по 10 элементов, используя различные конструкторы.
//     3. Один из массивов отсортировать (четные варианты – по убыванию, 
//        нечетные – по возрастанию), найти минимальное, среднее и максимальное 
//        значение массива. 
//     4. Для второго массива выполнить задание по варианту
//
// Найти сумму элементов массива, расположенных после максимального элемента

#include <iostream>
using std::cout;
using std::endl;

class Vector
{
private:
    int size_;
    int* array_;
public:
    Vector(int n, int* array);
    ~Vector();
    int& operator[](int i);
    int Size() const;
    void Print() const;
    void Max(int& i, int& element) const;
    int Sum(int start, int end) const;
    void Sort(bool fromMinToMax);
};

Vector::Vector(int n, int* array = NULL)
{
    size_ = n;
    array_ = new int[size_]; // to make destructor alife

    if (array != NULL)
        for (int i = 0; i < size_; i++)
            *(array_ + i) = *(array + i);
    else
        for (int i = 0; i < size_; i++)
            *(array_ + i) = 0;
}

Vector::~Vector()
{
    delete array_;
    cout << "'~Vector()' done" << endl;
}

int& Vector::operator[](int i) // an alternative to "setter" and "getter"
{
    if (i < 0 || i >= size_)
    {
        cout << "! error: the index is out of bounds" << endl;
        this->~Vector(); //// it's not enough - other objects will not be deleted; need exception ?
        exit(1);
    }
    return *(array_ + i);
}

int Vector::Size() const // fo future when make the 'size_' defined inside class (by structure, for example)
{
    return size_;
}

void Vector::Print() const
{
    for (int i = 0; i < size_; i++)
        cout << *(array_ + i) << " ";
    cout << endl;
}

void Vector::Max(int& i, int& element) const
{
    i = 0;
    element = *(array_);
    for (int j = 1; j < size_; j++)
        if (element < *(array_ + j))
        {
            element = *(array_ + j);
            i = j;
        }
}

int Vector::Sum(int start = 0, int end = 1) const // sum of elements [start; end)
{
    int sum = 0;

    for (int i = start; i < end; i++)
        sum += *(array_ + i);

    return sum;
}

void Vector::Sort(bool fromMinToMax = true)
{       
    int tmp;
//var_1: 
//doubles the code, but more readable:
 //    if (fromMinToMax)
 //    {
    //     for (int i = 0; i < size_ - 1; i++)
    //         for (int j = i + 1; j < size_; j++)            
    //             if(*(array_ + i) > *(array_ + j))
    //             {
    //                 tmp = *(array_ + i);
    //                 *(array_ + i) = *(array_+ j);
    //                 *(array_ + j) = tmp;
    //             } 
 //    }
    // else    
    // {
    //  for (int i = 0; i < size_ - 1; i++)
    //         for (int j = i + 1; j < size_; j++)            
    //             if(! (*(array_ + i) > *(array_ + j)) )
    //             {
    //                 tmp = *(array_ + i);
    //                 *(array_ + i) = *(array_+ j);
    //                 *(array_ + j) = tmp;
    //             }        
    // }
//var_2:
//came up with the same functional, but shorter and less readable at the same time
        for (int i = 0; i < size_ - 1; i++)
            for (int j = i + 1; j < size_; j++)            
                if( fromMinToMax == (*(array_ + i) > *(array_ + j)) ) // that's the trick
                {
                    tmp = *(array_ + i);
                    *(array_ + i) = *(array_+ j);
                    *(array_ + j) = tmp;
                } 
}


int main()
{
    system("CLS");

    Vector vc1(10);
    cout << "'Vector vc1(10)' result:\n" <<
            "vc1: "; 
    vc1.Print();

    int array[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    int n = sizeof(array) / sizeof(array[0]);
    Vector vc2(n, array);
    cout << endl;

    cout << "'Vector vc2(n, array)', where\n" << 
            "'array[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10}', result:\n" <<
            "vc2: "; 
    vc2.Print();
    cout << endl;

    cout << "Assignment of random values to vc1:\n";
    int m = vc1.Size();
    for (int i = 0; i < m; i++)
        vc1[i] = rand() % 10;
    cout << "vc1: "; 
    vc1.Print();
    cout << endl;

    int i, element;
    cout << "Index and value of 'vc1' max element:\n";
    vc1.Max(i, element);
    cout << "vc1.Max(i, element): i = " << i 
         << ", element = " << element << endl;
    cout << endl;

    cout << "Default sum of array's elements, i.e. the first element:\n";
    cout << "vc1.Sum(): " << vc1.Sum() << endl;
    cout << endl;

    cout << "Sum of array's elements starting from element with 'i' index:\n";
    cout << "vc1.Sum(" << i << ", vc1.Size()): " << vc1.Sum(i, vc1.Size()) << endl;
    cout << endl;

    cout << "Full sum of array's elements:\n";
    cout << "vc1.Sum(0, vc1.Size()): " << vc1.Sum(0, vc1.Size()) << endl;
    cout << endl;

    cout << "vc1.Sort()\n";
    cout << "ascending sort\n";
    vc1.Sort();
    vc1.Print();
    cout << "descending sort\n";
    vc1.Sort(false);
    vc1.Print();
    cout << endl;

    cout << "vc2.Sort()\n";
    cout << "ascending sort\n";
    vc2.Sort();
    vc2.Print();
    cout << "descending sort\n";
    vc2.Sort(false);
    vc2.Print();
    cout << endl;

    cout << "Destructors' work:" << endl;

    return 0;
}