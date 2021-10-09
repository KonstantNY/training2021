//exercise2.0
// Тема: классы и объекты.
// Цель работы: изучить структуру класса, атрибуты доступа к компонентам 
//              класса, принципы работы с объектами.
// Задание:
//     1. Разработать класс «строка». Методы класса: конструктор, 
//        деструктор и метод, выполняющий задание в соответствии с вариантом.
// 2.1
// Дана строка символов. Заменить в ней каждую букву "a" на последнюю букву 
// последовательности, подсчитать количество таких замен.
// 2.2
// Дана строка символов, среди которых есть хотя бы один пробел. 
// Заменить в ней знаком "!" все запятые после первого пробела, подсчитать 
// количество таких замен.

#include <iostream>
#include <cstring>

 using std::cout;
 using std::endl;

 class String
 {
 private:     
     static int counter_;
     const int numberOfEntity_;
     constexpr static short SIZE_ = 51; //50 meaningfull symbols + '\0'
     char string_[SIZE_];
     bool isMatching_[SIZE_ - 1];  
     void InitIsMatching(); // initialize 'isMatching_' array
     void PrintIsMatching() const; // represents 'bool isMatching_' as combination of '_' and '|' symbols
 public:
     String();
     String(const char string[]);
     ~String();
     void Print() const;     
     char& operator[] (int i); // "bilateral" call: we can read and write thanks to '&''
     int Length() const;
     const bool* Find(const char toFind); // my clumsy 'hack' :( - would be better to create by 'new' an array with 'true' positions
     const bool* Replace(const char has, const char should, int start);
     const bool* Insert(const char toInsert, int position); // for fun - it's not in spec
     const bool* Delete(int position); // for fun - it's not in spec
     const bool* Reverse(); // for fun - it's not in spec
 };

 int String::counter_ = 0;

 void String::InitIsMatching()
 {
 	for (int i = 0; i < SIZE_; i++)
     	isMatching_[i] = false;
 }

 void String::PrintIsMatching() const
 {
 	int size = Length();
 	for (int i = 0; i < size; i++)
     	cout << (isMatching_[i] ? '|' : '_');
    cout << endl;
 }

 String::String():
 	numberOfEntity_(++counter_)
 {
    strcpy(string_, "");
    InitIsMatching();
 }

 String::String(const char string[]):
 	numberOfEntity_(++counter_)
 {
    strcpy(string_, string);
	InitIsMatching();
 }

 String::~String()
 {
 	cout << "~String() done: entity " << numberOfEntity_ << " has been deleted" << endl;
 }

 void String::Print() const
 {
     //cout << "string of size " << Length() << " (max " << SIZE_ - 1 << "):\n";
     cout << string_ << endl; 
     PrintIsMatching();
     cout << endl;
 }

 char& String::operator[] (int i)
 {
 	if (i < 0 || i >= Length())
 	{
 		cout << "! error: the index is out of bounds" << endl;
 		exit(1);
 	}
 	InitIsMatching();
 	isMatching_[i] = true;

 	return string_[i];
 }

 int String::Length() const
 {
 	int i = 0;
 	while (string_[i] != '\0')
		i++;
	return i;
 }

 const bool* String::Find(const char toFind)
 {
 	InitIsMatching();
 	int size = Length();
 	for (int i = 0; i < size; i++)
 		if (string_[i] == toFind)
 			isMatching_[i] = true;
 	const bool* pbool = isMatching_;

 	return pbool;
 }
// !! to fix in the next iteration: refresh 'isMatching_'
 const bool* String::Replace(const char has, const char should, int start = 0)
 {
 	Find(has);
 	int size = Length();
 	for (int i = start; i < size; i++)
 		if (isMatching_[i])
 			string_[i] = should;
 	for (int i = 0; i < start; i++)
 		isMatching_[i] = false; // refreshing the obsolete part of 'isMatching_'
 	const bool* pbool = isMatching_;

 	return pbool;
 }

 const bool* String::Insert(const char toInsert, int position)
 {
 	int size = Length();
 	InitIsMatching();
 	if (size >= SIZE_)
 	{
 		cout << "error ! : there is no space to add the element" << endl;
 		exit(2);
 	}
 	for (int i = size; i >= position; i--)
 		string_[i + 1] = string_[i];
 	string_[position] = toInsert;
 	isMatching_[position] = true;
 	const bool* pbool = isMatching_;

 	return pbool;
 }

 const bool* String::Delete(int position)
 {
 	int size = Length();
 	InitIsMatching();
 	if (size <= 0)
 	{
 		cout << "error ! : the string is empty" << endl;
 		exit(3);
 	}
 	else if (size < position)
 	{
 		cout << "error ! : the requested position is too high" << endl;
 		exit(4);
 	} 
 	for (int i = position; i < size; i++)
 		string_[i] = string_[i + 1];
 	isMatching_[position] = true;
 	const bool* pbool = isMatching_;

 	return pbool;
 }

 const bool* String::Reverse()
 {
 	int size = Length();
 	int halfSize = size / 2;
 	InitIsMatching();

 	char tmp;
 	for (int i = 0; i < halfSize; i++)
 	{
 		tmp = string_[i];
 		string_[i] = string_[size - i - 1];
 		string_[size - i - 1] = tmp;
 	}

 	isMatching_[halfSize] = true; // one ore two '|' depending n parity
 	if (! (size % 2))
        isMatching_[halfSize - 1] = true;
    const bool* pbool = isMatching_;

    return pbool;
 }


 int main()
 {
	system("CLS");

	cout << "*** Test 1: methods of class ***\n" <<
	        "(the '|' symbol points to a place in the string where the\n" << 
	        "operation has just took place)\n";
	cout << endl;


	String str("123456789-qwertyuio-987654321-oiuytrewq");
	//String str("1234");

	cout << "Initial 'str':" << endl;
	str.Print();

	cout << "Overloaded 'access' operator '[]' as an r-value\n" <<
	        "cout << str[3]: " << str[3] << endl;
	str.Print();

	cout << "Overloaded 'access' operator '[]' as an l-value\n" <<
	        "str[6] = ?: " << endl;
	str[6] = '?';
	str.Print();

	cout << "Searching for all entrances of a symbol to the string\n" <<
	        "str.Find('q'):";
	const bool* pbool = str.Find('q');
	for (int i = 0; i < str.Length(); i++)
		if(*pbool++)
			cout << " " << i;
	cout << " - indexes of found entrances";
	cout << endl;
	str.Print();

	cout << "Replacing all the entrances of one symbol to some another\n" <<
	        "str.Replace('q', 'Q'):" << endl;
	str.Replace('q', 'Q');
	str.Print();

	cout << "Inserting some symbol to some position of the string\n" <<
	        "str.Insert('^', 5):" << endl;
	str.Insert('^', 5);
	str.Print();

	cout << "Deleting symbol by its index\n" <<
	        "str.Delete(6):" << endl;
	str.Delete(6);
	str.Print();

	cout << "Reversing the string the way depending on number\n" <<
	        "of elements that may be odd or even\n" <<
	        "('|' points here to unmoved, i.e. 'central' symbols)" << 
	        "str.Reverse():" << endl;
	str.Reverse();
	str.Print();
	cout << "str.Delete(1) (to switch from 'odd' to 'even' way of reversing):" << endl;
	str.Delete(6);
	str.Reverse();
	str.Print();
	cout << endl;
	// //wonder, does it work or not like that:
	//str.~String();
	// //no: destructior has been called again in the end of the program


	cout << "*** Test 2: specific tasks ***\n";
    int i;


	cout << "2.1 Replace all the 'a' symbols by the last symbol of the string.\n" <<
	        "    Calculate the number of such replacements made.\n" << endl;

	cout << "(0) initial string:\n";
	String str1 = "a--aa--^";
	str1.Print();

	cout << "(1) initial string with found symbols:\n";
	pbool = str1.Find('a');
	i = 0; 
	for (int j = 0; j < str1.Length(); j++)
		if (*(pbool + j))
			i++;
	// replacement itself
	str1.Print();

	cout << "(2) string after replacements:\n";
	str1.Replace('a', str1[str1.Length() - 1]);
	str1.Print();

	cout << "(3) replacements' number: " << i << endl << endl;
	cout << endl;


	cout << "2.2 A string with at least one ' ' (space) symbol is given.\n" << 
	        "    Replace all the ',' (commas) after the first entrance of space\n" <<
	        "    symbol. Calculate the number of such replacements made.\n"<< endl;

	cout << "(0) initial string:\n";
	String str2 = "-,, -  -,, ,-";	
	str2.Print();	

	cout << "(1) initial string with found symbols:\n";
	pbool = str2.Find(' ');
	// finding the first occurrence of ' ' (space):
	i = 0; 
	while (! *(pbool + i))
		i++;
	str2.Print();

	cout << "(2) string after replacements:\n";
	str2.Replace(',', '!', i);
	str2.Print();

	// finding the number of replacements - a little bit clumsy ((
	i = 0;	
	for (int j = 0; j < str2.Length(); j++)
		if (*(pbool + j))
			i++;
	cout << "(3) replacements' number: " << i << endl << endl;

	return 0;
}