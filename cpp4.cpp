//exercise4.0
// Тема: наследование. 
//  Цель работы: изучить принципы наследования. 
// Задание:
// 1. Создать базовый класс по варианту, содержащий 2 или более полей, 
//    и определить в нем конструктор, деструктор и метод вывода на экран 
//    значений полей класса. 
// 2. Разработать производные классы, в которые добавить минимум 1 поле 
//    и собственные методы (конструктор, деструктор, метод вывода на экран 
//    значений полей класса и метод, реализующий задание по варианту). 
// 3. Создать объекты разработанных классов и проверить работу реализованных 
//    в них методов.  
//
// Вариант 1:
// транспортное средство | автомобиль, мотоцикл, велосипед | Общая стоимость перевозки
//
//future development 
//1. Add 'FPrint()' method with templates, which using 'static int modelFormat_'; 
//   and 'static int serialFormat_' for alignment;
//2. Ad an 'char* id_' field composing all the 'count_' fields of all included casses
//   like, for example, for 'Car': id_ = V2.E2.M1.C1;
//3. Add correct printing of bool: 'true'/'false' instead '1'/'0' (thernary op, indeed)

#include <iostream>
#include <cstring> // for 'strlen()'
#include <string> // for 'to_string'

using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::to_string;

class Vehicle;


struct Link                           
{
    Vehicle* data_; // !! '-1' reserved by 'Pop()' for '~LinkedList()' correct work                         
    Link* next_;                        
};


class LinkedList                        
{
private:
    Link* first_;                    
public:
    LinkedList();                     
    void Put(Vehicle* data);  
    void PutToEnd(Vehicle* data); //added by me in Lafore10.8
    void Display() const;
    int Length() const;
    Vehicle* Pop(); // added by me in Lafore10.4 
    Vehicle* Read();
    ~LinkedList(); // added by me in Lafore10.4       
};


class Vehicle
{
protected:
    char* model_; // 'Peugeot 406, Honda CBR 650, Giant Talon'
    char* serialNumber_;
    float costPerKm_; 
    float kmPassed_;
    LinkedList* linkedList_;
    //auxiliary fields:
    static int counter_;
    // for right alignment while formated output - for future functional
    // like advanced aligned printing with templates, maybe
    static int modelFormat_; 
    static int serialFormat_; 
public:
    Vehicle(const char* model, const char* serialNumber, float costPerKm, float kmPassed);
    ~Vehicle();
    void Print() const;
    static float Sum(LinkedList* vehicles);
};
    int Vehicle::counter_ = 0;

    int Vehicle::modelFormat_ = 0; 

    int Vehicle::serialFormat_ = 0;

    Vehicle::Vehicle(const char* model = "[vehicle model]", 
                     const char* serialNumber = "[vehicle serial number]", 
                     float costPerKm = 0.0, 
                     float kmPassed = 0.0):
        costPerKm_(costPerKm),
        kmPassed_(kmPassed)
    {
        //here 'serialNumber' should be compoused of 'counters_' of all basic classes and current class itself

        // 'modelFormat_' and 'serialFormat_' are 
        // for right alignment while formated output - for future functional
        // like advanced aligned printing with templates, maybe

        int modelLen = strlen(model);
        model_ = new char[modelLen + 1];
        strcpy(model_, model);
        model_[modelLen] = '\0';
        if (modelFormat_ < modelLen)
            modelFormat_ = modelLen;

        int serialNumberLen = strlen(serialNumber);
        serialNumber_ = new char[serialNumberLen + 1];
        strcpy(serialNumber_, serialNumber);
        serialNumber_[serialNumberLen] = '\0';  
        if (serialFormat_ < serialNumberLen)
            serialFormat_ = serialNumberLen;

        counter_++;

        cout << "(dbg) Vehicle::Vehicle(...) has finished" << endl;
    }

    Vehicle::~Vehicle()                   
    {
        delete[] model_;   
        delete[] serialNumber_; 
        cout << "(dbg) Vehicle::~Vehicle() has finished" << endl;  
    }

    void Vehicle::Print() const
    {
        cout << "(dbg) Vehicle::model_ = " << model_ <<
                "\n(dbg) Vehicle::serialNumber_ = " << serialNumber_ <<
                "\n(dbg) Vehicle::costPerKm_ = " << costPerKm_ <<
                "\n(dbg) Vehicle::kmPassed_ = " << kmPassed_ <<
                "\n(dbg)     Vehicle::counter_ = " << counter_ <<
                "\n(dbg)     Vehicle::modelFormat_ = " << modelFormat_ <<
                "\n(dbg)     Vehicle::serialFormat_ = " << serialFormat_ << endl;
    }

    float Vehicle::Sum(LinkedList* vehicles)
    {
        cout << "(dbg) Vehicle::Sum:" << endl;
        float sum = 0;
        int length = vehicles->Length();
        Vehicle* tmp;
        for (int i = 0; i < length; i++)
        {
            tmp = vehicles->Read();
            sum += tmp->costPerKm_ * tmp->kmPassed_;
            cout << "(dbg) costPerKm_: " << tmp->costPerKm_ <<
                    ", tmp->kmPassed_: " << tmp->kmPassed_ << endl;
        }

        cout << "(dbg) sum = " << sum << endl;
        return sum;
    }


class Engine
{
protected:
    const int horsePower_;
    const bool isElectric_;
    //auxiliary fields:
    static int counter_;
public:
    Engine(int horsePower, bool isElectric);
    ~Engine();
    void Print() const;
};
    int Engine::counter_ = 0;

    Engine::Engine(int horsePower = 0, bool isElectric = false):
        isElectric_(isElectric),
        horsePower_(horsePower)
    {
        counter_++;
        cout << "(dbg) Engine::Engine(...) has finished" << endl;
    }

    Engine::~Engine()
    {
        cout << "(dbg) Engine::~Engine(...) has finished" << endl;      
    }

    void Engine::Print() const
    {
        cout << "(dbg) Engine::horsePower_ = " << horsePower_ <<
                "\n(dbg) Engine::isElectric_ = " << isElectric_ <<
                "\n(dbg)     Engine::counter_ = " << counter_ << endl;
    }


class Bicycle: public Vehicle
{
protected:
// to track inheritance
    // char* Vehicle::model_;
    // char* Vehicle::serialNumber_;
    // float Vehicle::costPerKm_; 
    // float Vehicle::kmPassed_;
    // LinkedList* linkedList_;
    // static int Vehicle::counter_;
    // static int Vehicle::modelFormat_;
    // static int Vehicle::serialFormat_;

    const bool hasSuspension_;
    const bool hasFixedGear_;
    //auxiliary fields:
    static int counter_;
public:
// to track inheritance
    // Vehicle(const char* model, const char* serialNumber, float costPerKm, float kmPassed);
    // ~Vehicle();
    // void Vehicle::Print() const;

    Bicycle(const char* model, const char* serialNumber, float costPerKm, float kmPassed,
            bool hasSuspension, bool hasFixedGear);
    ~Bicycle();
    void Print() const;
};
    int Bicycle::counter_ = 0;

    Bicycle::Bicycle(const char* model = "[bicycle model]", 
                     const char* serialNumber = "[bicycle serial number]", 
                     float costPerKm = 0.0, 
                     float kmPassed = 0.0,
                     bool hasSuspension = false, 
                     bool hasFixedGear = true)
    // here the default 'Vehicle::Vehicle()' will be called if nowhere later
    :
        Vehicle(model, serialNumber, costPerKm, kmPassed), 
        hasSuspension_(hasSuspension),
        hasFixedGear_(hasFixedGear)
    {
        counter_++;
        cout << "(dbg) Bicycle::Bicycle(...) has finished" << endl;
    }

    Bicycle::~Bicycle()
    {
        cout << "(dbg) Bicycle::~Bicycle() has finished" << endl;  
    }

    void Bicycle::Print() const
    {
        Vehicle::Print();
        cout << "(dbg) Bicycle::hasSuspension_ = " << hasSuspension_ <<
                "\n(dbg) Bicycle::hasFixedGear_ = " << hasFixedGear_ <<
                "\n(dbg)     Bicycle::counter_ = " << counter_ << endl;
    }


class Motorcycle: public Vehicle, public Engine
{
protected:
// to track inheritance
    // char* Vehicle::model_;
    // char* Vehicle::serialNumber_;
    // float Vehicle::costPerKm_; 
    // float Vehicle::kmPassed_;
    // LinkedList* linkedList_;
    // static int Vehicle::counter_;
    // static int Vehicle::modelFormat_;
    // static int Vehicle::serialFormat_;

    // const int Engine::horsePower_;
    // const bool Engine::isElectric_;
    // static int Engine::counter_;

    const int maxSpeed_;
    const bool hasSeatHeated_;
    //auxiliary fields:
    static int counter_;
public:
// to track inheritance
    // Vehicle(const char* model, const char* serialNumber, float costPerKm, float kmPassed);
    // ~Vehicle();
    // void Vehicle::Print() const;

    // Engine(int horsePower, bool isElectric);
    // ~Engine();
    // void Engine::Print() const;

    Motorcycle(const char* model, const char* serialNumber, float costPerKm, float kmPassed,
               int horsePower, bool isElectric,
               int maxSpeed, bool hasSeatHeated);
    ~Motorcycle();
    void Print() const;
};
    int Motorcycle::counter_ = 0;

    Motorcycle::Motorcycle(const char* model = "[motorcycle model]", 
                           const char* serialNumber = "[motorcycle serial number]", 
                           float costPerKm = 0.0, 
                           float kmPassed = 0.0,
                           int horsePower = 0, 
                           bool isElectric = false,
                           int maxSpeed = 0, 
                           bool hasSeatHeated = false)
    // here the default 'Vehicle::Vehicle()' will be called if nowhere later
    // here the default 'Engine::Engine()' will be called if nowhere later
    :
        Vehicle(model, serialNumber, costPerKm, kmPassed), 
        Engine(horsePower, isElectric),
        maxSpeed_(maxSpeed),
        hasSeatHeated_(hasSeatHeated)
    {
        counter_++;
        cout << "(dbg) Motorcycle::Motorcycle has finished" << endl;
    }

    Motorcycle::~Motorcycle()
    {
        cout << "(dbg) Motorcycle::~Motorcycle has finished" << endl;   
    }

    void Motorcycle::Print() const
    {
        Vehicle::Print();
        Engine::Print();
        cout << "(dbg) Motorcycle::maxSpeed_ = " << maxSpeed_ <<
                "\n(dbg) Motorcycle::hasSeatHeated_ = " << hasSeatHeated_ <<
                "\n(dbg)     Motorcycle::counter_ = " << counter_ << endl;
    }

enum class BodyType {COUPE = 0, HATCHBACK, SEDAN, WAGON, MINIVAN};

// '<<' operator overloading for 'enum class BodyType':
ostream& operator<< (ostream& stream, BodyType bodyType)
{
    switch(bodyType)
    {
        case BodyType::COUPE:
            return stream << "COUPE";
        case BodyType::HATCHBACK:
            return stream << "HATCHBACK";
        case BodyType::SEDAN:
            return stream << "SEDAN";
        case BodyType::WAGON:
            return stream << "WAGON";
        case BodyType::MINIVAN:
            return stream << "MINIVAN";
        default:
            return stream << "'BodyType' value is undefined";
    }
}

class Car: public Motorcycle
{
protected:
// to track inheritance
    // char* Vehicle::model_;
    // char* Vehicle::serialNumber_;
    // float Vehicle::costPerKm_; 
    // float Vehicle::kmPassed_;
    // LinkedList* linkedList_;
    // static int Vehicle::counter_;
    // static int Vehicle::modelFormat_;
    // static int Vehicle::serialFormat_;

    // const int Engine::horsePower_;
    // const bool Engine::isElectric_;
    // static int Engine::counter_;

    // const int Motorcycle::maxSpeed_;
    // const bool Motorcycle::hasSeatHeated_;
    // static int Motorcycle::counter_;

    BodyType bodyType_;
    //auxiliary fields:
    static int counter_;
public:
// to track inheritance
    // Vehicle(const char* model, const char* serialNumber, float costPerKm, float kmPassed);
    // ~Vehicle();
    // void Vehicle::Print() const;

    // Engine(int horsePower, bool isElectric);
    // ~Engine();
    // void Engine::Print() const;

    // Motorcycle(const char* model, const char* serialNumber, float costPerKm, float kmPassed,
    //            int horsePower, bool isElectric,
    //            int maxSpeed, bool hasSeatHeated);
    // ~Motorcycle();
    // void Motorcycle::Print() const;

    Car(const char* model, const char* serialNumber, float costPerKm, float kmPassed,
        int horsePower, bool isElectric,
        int maxSpeed, bool hasSeatHeated,
        BodyType bodyType);
    ~Car();
    void Print() const;
};
    int Car::counter_ = 0;

    Car::Car(const char* model = "[car model]", 
             const char* serialNumber = "[car serial number]", 
             float costPerKm = 0.0, 
             float kmPassed = 0.0,
             int horsePower = 0, 
             bool isElectric = false,
             int maxSpeed = 0, 
             bool hasSeatHeated = false,
             BodyType bodyType = BodyType::SEDAN)
    // here the default 'Vehicle::Vehicle()' will be called if nowhere later
    // here the default 'Engine::Engine()' will be called if nowhere later
    // here the default 'Motorcycle::Motorcycle()' will be called if nowhere later
    :
        Motorcycle::Motorcycle(model, serialNumber, costPerKm, kmPassed,
                               horsePower, isElectric,
                               maxSpeed, hasSeatHeated),
        bodyType_(bodyType)
    {
        counter_++;
        cout << "(dbg) Car::Car has finished" << endl;
    }

    Car::~Car()
    {
        cout << "(dbg) Car::~Car has finished" << endl;
    }

    void Car::Print() const
    {
        Motorcycle::Print();
        cout << "(dbg) Car::bodyType_ = " << bodyType_ <<
                "\n(dbg)     Car::counter_ = " << counter_ << endl;
    }

// LinkdList definition:
    LinkedList::LinkedList():
        first_(NULL)
    {}  

    void LinkedList::Put(Vehicle* data)         
    {
        Link* newLink = new Link;          
        newLink->data_ = data;                
        newLink->next_ = first_;             
        first_ = newLink;                  
    }

    void LinkedList::PutToEnd(Vehicle* data)         
    {
        Link* newLink = new Link;          
        newLink->data_ = data;                
        newLink->next_ = NULL; 

        if (first_ == NULL)
            first_ = newLink;
        else
        {
            Link* current = first_;             
            while(true)           
            { 
                if (current->next_ == NULL)
                    break;
                current = current->next_;  
            } 
            current->next_ = newLink;
        }     
    }

    void LinkedList::Display() const
    {
        Link* current = first_;             
        while( current != NULL )           
        {
            cout << " " << current->data_;  
            current = current->next_;        
        }
        cout << endl;
    }

    int LinkedList::Length() const
    {
        Link* current = first_; 
        int length = 0;            
        while( current != NULL )
        {          
            length++;
            current = current->next_; 
        }

        return length;
    }

    Vehicle* LinkedList::Pop()
    {
        Vehicle* tmp;
        Link* linkTmp;

        if (first_ != NULL)         
        {
            tmp = first_->data_;  
            linkTmp = first_;
            first_ = first_->next_; 
            delete linkTmp; 
            return tmp;      
        }
        else
        {
            cout << "(dbg) LinkedList::Pop(): the LinkedList is finished" << endl;
            //exit(1); 
            return NULL; // to give an opportunity to the program call all 
                         //destructors - not only for 'LinkedList';
                         // it's ok if suppose that 'data_' is never < 0
        }    
    }

    Vehicle* LinkedList::Read()
    // before read: 1 2 3 4
    // after read: 2 3 4 1
    {
        Vehicle* tmp;
        tmp = this->Pop();
        this->PutToEnd(tmp);

        return tmp;
    }

    LinkedList::~LinkedList()
    {
        int i = 0;
        while (this->Pop() != NULL)
        {
            //this->Pop();
            cout << "(dbg)     link #" << ++i << " has been deleted" << endl; 
        }
        cout << "(dbg) LinkedList::~LinkedList() has finished" << endl;
    }


int main()
{
    system("CLS");


    cout << "\n***TEST_1 Common definitions***" << endl;
    cout << "\n***TEST_1.1 Vehicle's definition***\n" << endl;
    cout << "Vehicles:" << endl;

    Vehicle vehicle0;
    vehicle0.Print();
    cout << endl;

    Vehicle vehicle1("vehicle1", "ABCD5678", 1.1, 200);
    vehicle1.Print();
    cout << endl;

    Vehicle vehicle2("vehicle2", "ABCD5679", 1.2, 300);
    vehicle2.Print();

    cout << endl;


    cout << "Engines:" << endl;
    Engine engine0;
    engine0.Print();
    cout << endl;

    Engine engine1(123, true);
    engine1.Print();
    cout << endl;

    Engine engine2(234, false);
    engine2.Print();

    cout << endl;


    cout << "Bicycles:" << endl;

    Bicycle bicycle0;
    bicycle0.Print();
    cout << endl;

    Bicycle bicycle1("Giant Talon", "Tln/13102001-135", 0.2, 50, 
                     true, false);
    bicycle1.Print();
    cout << endl;

    Bicycle bicycle2("Author Horizont", "Atr/13102001-189", 0.3, 70, 
                     true, false);
    bicycle2.Print();

    cout << endl;


    cout << "Motorcycles:" << endl;

    Motorcycle motorcycle0;
    motorcycle0.Print();
    cout << endl;
    Motorcycle motorcycle1("Honda CBR 650", "[HND650-14102021-0000/98]", 0.5, 1100,
                           140, true,
                           175, true);
    motorcycle1.Print();
    cout << endl;
    Motorcycle motorcycle2("Ducati Devil", "[D650-14102021-0000/99]", 0.6, 1300,
                           120, true,
                           165, true);
    motorcycle2.Print();

    cout << endl;


    cout << "Cars:" << endl;

    Car car0;
    car0.Print();
    cout << endl;

    Car car1("Peugeot 406", "123ABC456.78/2001", 0.8, 2200,
             250, true,
             320, true,
             BodyType::SEDAN);
    car1.Print();
    cout << endl << endl;

    Car car2("Ferrari FF", "FFABC456.78/2001", 2.0, 3400,
             350, true,
             400, true,
             BodyType::COUPE);
    car2.Print();

    cout << endl << endl;


    cout << "***TEST_1.2 LinkedList***\n" << endl;
    LinkedList linkedList0;  

    cout << "LinkedList.Put(), LinkedList.Read() and LinkedList.Pop()" << endl; 
    cout << endl;
    linkedList0.Put( static_cast<Vehicle*>(&bicycle1) );
    linkedList0.Put( static_cast<Vehicle*>(&bicycle2) );
    linkedList0.Put( static_cast<Vehicle*>(&motorcycle1) );
    linkedList0.Put( static_cast<Vehicle*>(&motorcycle2) );
    linkedList0.Put( static_cast<Vehicle*>(&car1) );
    linkedList0.Put( static_cast<Vehicle*>(&car2) );
    cout << "linkedList0: ";
    linkedList0.Display(); 

    int length = linkedList0.Length();
    for (int i = 0; i < length; i++)
    {
        cout << "(dbg) read: " << linkedList0.Read() << "; list: ";
        linkedList0.Display();
        cout << "(dbg) 'linkedList0.Length()': " << linkedList0.Length() << endl;
    }
    cout << endl;

    for (int i = 0; i < length; i++)
    {
        cout << "(dbg) put: " << linkedList0.Pop() << "; left: ";
        linkedList0.Display();
        cout << "(dbg) 'linkedList0.Length()': " << linkedList0.Length() << endl;
    }
    cout << endl << endl;


    cout << "***TEST_2 Sum for all vehicles***\n" << endl;

    linkedList0.Put( static_cast<Vehicle*>(&bicycle1) );
    linkedList0.Put( static_cast<Vehicle*>(&bicycle2) );
    linkedList0.Put( static_cast<Vehicle*>(&motorcycle1) );
    linkedList0.Put( static_cast<Vehicle*>(&motorcycle2) );
    linkedList0.Put( static_cast<Vehicle*>(&car1) );
    linkedList0.Put( static_cast<Vehicle*>(&car2) );

    cout << "(dbg) linkedList0: ";
    linkedList0.Display(); 
    cout << endl;

    float vTranspCost = Vehicle::Sum(&linkedList0);
    cout << "\n***************************************************************";
    cout << "\nTotal cost of all " << linkedList0.Length() << 
            " transportations: " << vTranspCost << endl;
    cout << "***************************************************************";

    cout << "\n\nBefore exit the 'main()':\n";
    return 0;
}

