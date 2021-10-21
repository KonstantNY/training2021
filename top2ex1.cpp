// Тема: виртуальные функции, абстрактные классы. 
// Цель работы: изучить принципы использования виртуальных функций и абстрактных классов.
// Задание: Базовый класс 1 уровня – абстрактный, содержащий чисто виртуальные функции. 
// Классы 2 уровня – абстрактные, содержащие поля, конструкторы, методы и чисто 
// виртуальные функции. Производные классы 3 уровня – конкретные классы, содержащие 
// реализацию виртуальных методов. 
//  
// Перевозчик 
//     Пассажирский: среднее число пассажиров 
//         Автобус 
//         Самолет
//     Грузовой: общая стоимость грузоперевозки 
//         Поезд 
//         Автомобиль

#include <iostream>
#include <cstring> // for 'strlen()'

using std::cout;
using std::endl;


class Carrier
{
public:
    virtual void Print() const = 0;
};


class Passenger: public Carrier
{
private:
    int numberOfPassengers_;
public:
    //virtual void Print() const = 0;
    Passenger(int numberOfPassengers);
    int Get() const;
    static int Average(Passenger* pasArray[], int size); //average number of passengers
};
    Passenger::Passenger(int numberOfPassengers = 0):
        numberOfPassengers_(numberOfPassengers)
    {}

    int Passenger::Get() const
    {
        return numberOfPassengers_;
    }

    int Passenger::Average(Passenger* pasArray[], int size)
    {
        int average = 0;

        for (int i = 0; i < size; i++)
            average += pasArray[i]->Get(); // because numberOfPassengers_ is left private intentionally (just wander) regarding Bus and Plane

        return average / size;
    }


class Bus: public Passenger
{
private:
    //int Passenger::numberOfPassengers_;
    int numberOfStops_; // number of stops on the route
public:
    // //virtual void Carrier::Print() const = 0;
    // Passenger(int numberOfPassengers);
    // int Passenger::Get();
    // int Passenger::Average() const;
    Bus(int numberOfPassengers, int numberOfStops);
    void Print() const; //cant use 'const' specifier because of non-constant method 'Access()' calling
};
    Bus::Bus(int numberOfPassengers = 0, int numberOfStops = 0):
        Passenger(numberOfPassengers),
        numberOfStops_(numberOfStops)
    {}

    void Bus::Print() const
    {
        cout << "Bus: numberOfPassengers = " << Get() <<
                ", numberOfStops = " << numberOfStops_ << endl;
    }


class Plane: public Passenger
{
private:
    //int Passenger::numberOfPassengers_;
    float maxRange_; // maximum flight range without refueling, miles
public:
    // //virtual void Carrier::Print() const = 0;
    // Passenger(int numberOfPassengers);
    // int Passenger::Get();
    // int Passenger::Average() const;
    Plane(int numberOfPassengers, float maxRange);
    void Print() const; //cant use 'const' specifier because of non-constant method 'Access()' calling
};
    Plane::Plane(int numberOfPassengers = 0, float maxRange = 0):
        Passenger(numberOfPassengers),
        maxRange_(maxRange)
    {}

    void Plane::Print() const
    {
        cout << "Plane: numberOfPassengers = " << Get() <<
                ", maxRange = " << maxRange_ << endl;
    }


class Cargo: public Carrier
{
private:
    float freightCost_;
public:
    Cargo(float freightCost);
    float Get() const;
    static float Average(Cargo* cargoArray[], int size); //average number of passengers
};
    Cargo::Cargo(float freightCost = 0):
        freightCost_(freightCost)
    {}

    float Cargo::Get() const
    {
        return freightCost_;
    }

    float Cargo::Average(Cargo* cargoArray[], int size)
    {
        float average = 0;

        for (int i = 0; i < size; i++)
            average += cargoArray[i]->Get(); // because numberOfPassengers_ is left private intentionally (just wander) regarding Bus and Plane

        return average / size;
    }


class Train: public Cargo
{
    private:
    int numberOfStops_; // number of stops on the route
public:
    Train(float freightCost, int numberOfStops);
    void Print() const; //cant use 'const' specifier because of non-constant method 'Access()' calling
};
    Train::Train(float freightCost = 0, int numberOfStops = 0):
        Cargo(freightCost),
        numberOfStops_(numberOfStops)
    {}

    void Train::Print() const
    {
        cout << "Train: freightCost = " << Get() <<
                ", numberOfStops = " << numberOfStops_ << endl;
    }


class Car: public Cargo
{
    private:
    float maxRange_; // maximum move range without refueling, miles
public:
    Car(float freightCost, float maxRange);
    void Print() const; //cant use 'const' specifier because of non-constant method 'Access()' calling
};
    Car::Car(float freightCost = 0, float maxRange = 0):
        Cargo(freightCost),
        maxRange_(maxRange)
    {}

    void Car::Print() const
    {
        cout << "Car: freightCost = " << Get() <<
                ", maxRange = " << maxRange_ << endl;
    }


int main()
{
    system("CLS");

    cout << endl;
    cout << "TEST_1. 2nd generation: 'Print()' by Bus, Plane, Train, Car\n";
    Bus bus0;
    Bus bus1(1, 2);
    bus0.Print();
    bus1.Print();

    cout << endl;
    Plane plane0;
    Plane plane1(3, 4);
    plane0.Print();
    plane1.Print();

    cout << endl;
    Train train0;
    Train train1(5.1, 6);
    train0.Print();
    train1.Print();

    cout << endl;
    Car car0;
    Car car1(7.2, 8);
    car0.Print();
    car1.Print();


    cout << endl << endl;
    cout << "TEST_2. 1st generation: 'Print()' by Passenger, Cargo\n";
    cout << "Passenger::Print()\n";
    Passenger* passenger0;
    passenger0 = &bus1;
    passenger0 ->Print();
    passenger0 = &plane1;
    passenger0 -> Print();
    cout << endl;

    cout << "Cargo::Print()\n";
    Cargo* cargo0;
    cargo0 = &train1;
    cargo0 ->Print();
    cargo0 = &car1;
    cargo0 -> Print();


    cout << endl << endl;
    cout << "TEST_3. 0 generation: 'Print()' by Carrier\n";
    Carrier* carrier0;
    carrier0 = &bus1;
    carrier0 ->Print();
    carrier0 = &plane1;
    carrier0 -> Print();
    carrier0 = &train1;
    carrier0 ->Print();
    carrier0 = &car1;
    carrier0 -> Print();


    cout << endl << endl;
    constexpr int size = 10;
    cout << "TEST_4.1 Passenger::Average()\n";

    Passenger* pasArray[size];
    int i = 0;
    int j = size / 2;

    for (; i < j; i++)
    {
        pasArray[i] = new Bus(rand() % 100, i + j);
    }
    for (; j < size; j++)
        pasArray[j] = new Plane(rand() % 100, j + j);

    cout << "(dbg) pasArray:\n";
    for (i = 0; i < size; i++)
    {
        cout << "(dbg) " << pasArray[i] << " ";
        pasArray[i]->Print();
    }

    cout << endl;
    cout << "the average of passengers of all buses and planes: " << 
            Passenger::Average(pasArray, size);
    cout << endl;

    cout << "\nTEST_4.2 Cargo::Average()\n";

    Cargo* cargoArray[size];
    i = 0;
    j = size / 2;

    for (; i < j; i++)
    {
        cargoArray[i] = new Train((rand() % 10000) * 0.01, i + j);
    }
    for (; j < size; j++)
        cargoArray[j] = new Car((rand() % 10000) * 0.01, j + j);

    cout << "(dbg) cargoArray:\n";
    for (i = 0; i < size; i++)
    {
        cout << "(dbg) " << cargoArray[i] << " ";
        cargoArray[i]->Print();
    }

    cout << endl;
    cout << "the average of freight costs of all trains and cars: " << 
            Cargo::Average(cargoArray, size);


    cout << endl;
    return 0;
}
