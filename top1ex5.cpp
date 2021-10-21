//exercise_5.0
// Тема: дружественные функции.
// Цель работы: изучить назначение и принципы работы дружественных функций и классов.

// Задание:
//     1. Разработать класс «массив» (двумерный динамический массив). 
//     Методы класса: конструктор (выполняет ввод размерности массива, 
//     динамическое выделение памяти и ввод элементов массива), 
//     деструктор (освобождает динамически выделенную под массив память), 
//     метод печати (выполняет форматный вывод элементов массива в виде таблицы)
//     и friend-метод, выполняющий решение задачи по варианту 
//     (если задачу решить нельзя, то сообщить об этом).
//
// 8.Найти сумму модулей элементов, расположенных выше главной диагонали
// (добавил для полноты картины и сумму моделей элементов, расположенных ниже)

#include <iostream>
#include <iomanip> // for setw()
#include <cmath> // for abs(), pow()

using std::cout;
using std::endl;
using std::setw;

class Array;

class ArrayFriend
{
public:
    int halfSum(const Array& array, bool isTopRightCorner);
};

class Array
{
private:
    int** array2d_;
    const int rows_;
    const int columns_;
    const int entityCounter_; // just wonder to see destructors' order
    static int destructorsOrder_; // just wonder to see destructors' order
    int minmax(bool isMin) const; //used here just for formated printing
    int minDigits() const; //used for formated printing
    friend int ArrayFriend::halfSum(const Array& array, bool isTopRightCorner);
public:
    Array(int* array, int rows, int columns);
    ~Array();
    void Print() const;
};
    int Array::destructorsOrder_ = 0;

    int Array::minmax(bool isMin = true) const
    // returns min or max element of 'array2d_' depending on 'isMin' value
    {
        int minmaxElement = **array2d_; // [0][0], i.e. first element of 'array2d_'
        if (rows_ * columns_ > 2)
        {
            int someElement;
            for (int i = 0; i < rows_; i++)
                for (int j = 0; j < columns_; j++)
                {
                    someElement = *(*(array2d_ + i) + j);
                    // // var_1: works, but takes enough lines                  
                    // if (isMin) // searching for min element
                    // {
                    //  if (minmaxElement > someElement)
                       //   minmaxElement = someElement;
                    // }
                    // else // searching for max element
                    // {
                       //  if (minmaxElement < someElement)
                       //   minmaxElement = someElement;
                    // }
                    
                    // var_2: came up with shorter, but less readable variant:
                    if (isMin == (minmaxElement > someElement)) // that's the trick
                        minmaxElement = someElement;
                }
        }
        if (isMin)
            cout << "(debug) min: "; 
        else
            cout << "(debug) max: ";
        cout << minmaxElement << endl;

        return minmaxElement;
    }

    int Array::minDigits() const
    // returns min number of digits to allign in readable order elements while 
    // depending on 
    // (1) max number of digits in largest 'array2d_' abs(element) and 
    // (2) sign of elements while printing
    {       
        int i = 1;
        int min = this->minmax();
        if (min) // i.e. if(min != 0)
        {
            i += log10( abs(min) );
            if (min < 0)
                i++;
        }
        //cout << "(debug) digits: " << i << endl;

        int j = 1;
        int max = this->minmax(false);
        if (max)
        {
            j += log10( abs(max) );
            if (max < 0)
                j++;
        }
        //cout << "(debug) digits: " << j << endl;

        return ( (i > j) ? i : j );
    }

    Array::Array(int* array = new int[1]{-1}, int rows = 1, int columns = 1):
        rows_(rows),
        columns_(columns),
        entityCounter_(destructorsOrder_++)
    {
        if (rows < 1 || columns_ < 1)
        {
            constexpr int errorCode = 1;
            cout << "! error_" << errorCode << " : the columns' number or size";
            cout << " is less than 1; \nprogram is closed" << endl;
            exit(errorCode);
        }
        array2d_ = new int*[rows_];
        for (int i = 0; i < rows_; i++)
            *(array2d_ + i) = new int[columns_];
        for (int i = 0; i < rows_; i++)
            for (int j = 0; j < columns_; j++)
                *(*(array2d_ + i) + j) = *(array + j + i * columns_);
    }

    Array::~Array()
    {
        for (int i = 0; i < rows_; i++)
            delete[] *(array2d_ + i);
        delete[] array2d_;
        cout << "destructor of entity "<< entityCounter_ << " done !" << endl;
    }

    void Array::Print() const
    {
        bool isMatrixSquare = ( (rows_ == columns_) ? true : false );
        int digits = minDigits();
        cout << "(debug) min digits: " << digits << endl;
        for (int i = 0; i < rows_; i++)
        {
            for (int j = 0; j < columns_; j++)
                cout << setw(digits) << *(*(array2d_ + i) + j) << 
                        ( (i == j && isMatrixSquare) ? "* " : "  ");
            cout << endl;
        }
    }

    int ArrayFriend::halfSum(const Array& array, bool isTopRightCorner = true)
    //                 |0 1 2|
    // array.array2d_: |3 4 5|
    //                 |6 7 8|
    // if 'isTopRightCorner = true', the sum = 1 + 2 + 5
    // else the sum = 3 + 6 + 7
    {
        int element;
        int sum = 0;
        if (array.rows_ != array.columns_)
        {
            sum = -1;
            cout << "! error: the array isn't square ('sum' is illegal); exiting program..." << endl;
            // // here must be some way to call all the destructors; may be through
            // // exception call instead of just clumsy 'exit()'- haven't knew yet how to
            //exit(1);
        }
        else if (array.rows_ == 1)
        // and, indeed, 'array.columns_ == 1' according to 
        // square, i.e. previous condition
            sum = abs(**array.array2d_);
        else 
        {
            cout << "(debug) elements to be added: " << endl;
            if (isTopRightCorner)           
                for (int i = 0; i < array.rows_ - 1; i++)
                {               
                    cout << "(debug) ";
                    //for (int j = array.columns_ - 1; j > i; j--)
                    for (int j = i + 1; j < array.columns_; j++)
                    {
                        element = *(*(array.array2d_ + i) + j);
                        cout << element << " ";
                        sum += abs(element);
                    }
                    cout << endl;
                }
            else
                for (int i = 1; i < array.rows_; i++)
                {               
                    cout << "(debug) ";
                    //for (int j = array.columns_ - 1; j > i; j--)
                    for (int j = 0; j < i; j++)
                    {
                        element = *(*(array.array2d_ + i) + j);
                        cout << element << " ";
                        sum += abs(element);
                    }
                    cout << endl;
                }
        }

        return sum;
    }


int main()
{
    system("CLS");

    ArrayFriend arrayFriend0;
    int sum;
    cout << "'*' after element means 'a member of main diagonal' if it take place" << endl << endl; 


    cout << "array0 (default values assigned to the constructor's parameters):\n";
    Array array0;
    array0.Print();
    sum = arrayFriend0.halfSum(array0);
    cout << "top sum of absolute values of 'array0':\n" << sum << endl;
    sum = arrayFriend0.halfSum(array0, false);
    cout << "bottom sum of absolute values of 'array0':\n" << sum << endl << endl;

  
    const int size = 40;
    // //initialization var_1:
    //int* explicitArray = new int[size] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    // //or, what's the same
    // //initialization var_2:
    int explicitArray[]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    cout << "array1x1:" << endl;
    Array array1x1(explicitArray, 1, 1);
    array1x1.Print();
    sum = arrayFriend0.halfSum(array1x1);
    cout << "top sum of absolute values of 'array1x1':\n" << sum << endl;
    sum = arrayFriend0.halfSum(array1x1, false);
    cout << "bottom sum of absolute values of 'array1x1':\n" << sum << endl << endl;


    cout << "array4x4:" << endl;
    Array array4x4(explicitArray, 4, 4);
    array4x4.Print();
    sum = arrayFriend0.halfSum(array4x4);
    cout << "top sum of absolute values of 'array4x4':\n" << sum << endl;
    sum = arrayFriend0.halfSum(array4x4, false);
    cout << "bottom sum of absolute values of 'array4x4':\n" << sum << endl << endl;


    cout << "array6x5 \n(some 'arbitrary' values are expected after requesting\n" <<
            "more than " << sizeof(explicitArray)/sizeof(explicitArray[0]) <<
            " element(s) - it's not a 'bug', but predicted behavior):" << endl;
    Array array6x5(explicitArray, 6, 5);
    array6x5.Print();
    sum = arrayFriend0.halfSum(array6x5);
    cout << "top sum of absolute values of 'array6x5':\n" << sum << endl;
    sum = arrayFriend0.halfSum(array6x5, false);
    cout << "bottom sum of absolute values of 'array6x5':\n" << sum << endl << endl;
   
    int* implicitArray = new int[size];
    for (int i = 0; i < size; i++)
        *(implicitArray + i) = rand() % 100 * ( (rand() % 2) ? -1 : 1 );
    cout << "array6x6:" << endl;
    Array array6x6(implicitArray, 6, 6);
    delete[] implicitArray;
    array6x6.Print();
    sum = arrayFriend0.halfSum(array6x6);
    cout << "top sum of absolute values of 'array6x6':\n" << sum << endl;
    sum = arrayFriend0.halfSum(array6x6, false);
    cout << "bottom sum of absolute values of 'array6x6':\n" << sum << endl << endl;


    return 0;
}
