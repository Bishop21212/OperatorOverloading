#include<iostream>
#include"String.h"
using namespace std;
#define delimeter "\n------------------------------------------------\n"




//#define CONSTRUCTORS_CHECK
#define OPERATORS_CHECK
//#define INPUT_CHECK

int main()
{
	//char test[1024 * 1024]{};
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	String str1;
	str1.print();
	cout << str1 << endl;

	String str2(25);
	str2.print();

	String str3 = "Hello";
	str3 = str3;
	cout << str3 << endl;

	String str4 = str3;//copy Constructror
	cout << str4 << endl;

	String str5;
	str5 = str3; //CopyAssigment(operator=)
	cout << str5 << endl;
#endif // CONSTRUCTORS_CHECK

#ifdef OPERATORS_CHECK
	String str1 = "Hello";
	String str2 = "World";
	cout << delimeter << endl;
	String str3 = str1 + str2;
	cout << delimeter << endl;
	cout << str3 << endl;
	cout << delimeter << endl;
	str1 += str2;
	cout << str1 << endl;
	cout << delimeter << endl;
#endif // OPERATORS_CHECK

#ifdef INPUT_CHECK
	String str;
	cout << "Введдите строку: ";
	//cin >> str;
	getline(cin, str);
	cout << str << endl;
	str.print();
#endif // INPUT_CHECK

	/*String str1;//Default Constructor
	str1.print();
	String str2 = "Hello";//Single-argument constructor
	str2.print();
	String str3 = str2;//Copy Constructor
	str3.print();
	String str4();//
	//str4.print();//str4 - это функция , а не объект
	String str5{}; //Default Constructor
	str5.print();

	String str6("World");//signle argument constructor
	String str7("Planet");//signle argument constructor*/
}