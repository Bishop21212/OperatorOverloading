//Fraction
#include<iostream>
using namespace std;

class Fraction;
Fraction operator*(Fraction left, Fraction right);

class Fraction
{
	int integer;
	int numerator;
	int denominator;
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)denominator = 1;
		this->denominator = denominator;
	}
	//Constructors
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		cout << "DefaultConstructor:\t" << this << endl;
	}
	explicit Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		cout << "1argConsturctor\t" << this << endl;
	}
	Fraction(double decimal)
	{
		decimal += 1e-11;
		integer = decimal;
		denominator = 1e+9;
		decimal -= integer; //убираем целую часть из десятичной дроби
		numerator = decimal * denominator;
		reduce();
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator); //чтобы не обойти фильтрацию данных
		cout << "Constructor:\t" << this << endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		set_denominator(denominator);
		cout << "Constructor:\t" << this << endl;
	}
	~Fraction()
	{
		cout << "Destructor:\t" << this << endl;
	}
	//Operators
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
		cout << "CopyAssigment:\t" << this << endl;
		return *this;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this * other;
	}
	//Type - cast operators
	explicit operator int()const
	{
		return integer;
	}
	explicit operator double()const
	{
		return integer + (double)numerator / denominator;
	}
	//Methods
	Fraction& to_improper() //в неправильную
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& to_proper() //в правильную
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction& reduce()
	{
		if (numerator == 0)return *this;
		int more, less;
		int rest;
		if (numerator > denominator)
		{
			more = numerator;
			less = denominator;
		}
		else
		{
			less = numerator;
			more = denominator;
		}
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more; //GCD - НОД
		numerator /= GCD;
		denominator /= GCD;
	}
	Fraction inverted()
	{
		to_improper();
		return Fraction(this->denominator, this->numerator);
	}
	ostream& print(ostream& os)const
	{
		if (integer)os << integer;
		if (numerator)
		{
			if (integer)os << "(";
			os << numerator << "/" << denominator;
			if (integer)os << ")";
		}
		else if (integer == 0)os << 0;
		return os;
	}
};

Fraction operator*( Fraction left, Fraction right) // параметры по ссылке
// чтобы не копировались в тело функции объекты,лучше убрать const,и убрать ссылки.
{
	left.to_improper();
	right.to_improper();
	/*Fraction result
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	);*/

	/*result.set_numerator(left.get_numerator() * right.get_numerator());
	result.set_denominator(left.get_denominator() * right.get_denominator());*/
	//result.to_proper();
	//result.to_improper();
	//result.reduce();
	//return result;
	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();
}
Fraction operator/( Fraction left,  Fraction right)
{
	return left * right.inverted();
}

ostream& operator << (ostream& os, const Fraction obj)
{
	/*if (obj.get_integer())os << obj.get_integer();
	if (obj.get_numerator())
	{
		if (obj.get_integer())os << "(";
		os << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())os << ")";
	}
	else if (obj.get_integer() == 0)os << 0;
	return os;*/
	return obj.print(os);
}
std::istream& operator >> (std::istream& is, Fraction& obj)
{
	/*int integer;
	int numerator;
	int denominator;
	is >> integer >> numerator >> denominator;
	obj.set_integer(integer);
	obj.set_numerator(numerator);
	obj.set_denominator(denominator);*/
	obj = Fraction(); //обнуляем объект
	const int SIZE = 256;
	char buffer[SIZE]{};
	char delimeters[] = "() /";
	is.getline(buffer, SIZE);
	char* number[3] = {};
	int n = 0;

	for (char* pch = strtok(buffer, delimeters); pch; pch = strtok(NULL, delimeters))
	{
		number[n++] = pch;
	}

	/*for (int i{0}; i < n; ++i)
	{
		cout << number[i] << "\t";
	}
	cout << endl;*/

	switch (n)
	{
	case 1: obj.set_integer(atoi(number[0])); break;
	case2:
		obj.set_numerator(atoi(number[0]));
		obj.set_denominator(atoi(number[1]));
		break;
	case 3:
		obj.set_integer(atoi(number[0]));
		obj.set_numerator(atoi(number[1]));
		obj.set_denominator(atoi(number[2]));
	}

	return is;
}

//#define CONSTRUCTORS_CHECK
//#define OPERATORS_CHECK
//#define TYPE_CONVERSONS_BASICS
//#define CONVERSION_FROM_OTHER_TO_CLASS
//#define CONVERSION_FROM_CLASS_TO_OTHER
//#define HOME_WORK
int main()
{
	setlocale(LC_ALL, "");
#ifdef  CONSTRUCTORS_CHECK
	Fraction A; //Default constructor
	A.print();
	double b = 5;
	Fraction B = 5;
	B.print();
	Fraction C(3, 4);
	C.print();
	Fraction D(2, 3, 4);
	D.print();
#endif //  CONSTRUCTORS_CHECK

#ifdef OPERATORS_CHECK
	double a = 2.5;
	double b = 3.4;
	double c = a * b;
	cout << c << endl;

	Fraction A(2, 1, 2);
	Fraction B(3, 2, 5);
	/*Fraction C = A * B;
	C.print();*/

	/*Fraction D(840, 3600);
	D.reduce();
	D.print();*/
	/*C = A / B;
	C.print();*/
	A *= B;
	A.print();
	//A = A * B;

#endif // DEBUG1

#ifdef TYPE_CONVERSIONS_BASICS
	int a = 2;
	double b = 3;
	int c = b;
	int d = 4.5;
	cout << d << endl;
#endif // TYPE_CONVERSIONS_BASICS

#ifdef CONVERSION_FROM_OTHER_TO_CLASS
	double a = 2;
	Fraction A = (Fraction)5;
	A.print();

	Fraction B;
	B = Fraction(8);
	B.print();

	Fraction C(12);
#endif // CONVERSION_FROM_OTHER_TO_CLASS


	//Type - cat operators
	/*operator type()
	{

	}*/
#ifdef CONVERSION_FROM_CLASS_TO_OTHER
	double b = 2;
	int c = b;

	Fraction A(2);  //если explicit конструктор, то знак = не ставится, вызовет ошибку
	int a(A);
	cout << a << endl;
	int i = (int)A;
#endif // CONVERSION_FROM_CLASS_TO_OTHER

#ifdef HOME_WORK
	Fraction A(2, 3, 4);
	double a = A;
	cout << a << endl;

	double b = 2.77111222;
	Fraction B = b;
	B.print();
#endif // HOME_WORK

	/*Fraction A(2, 3, 4);
	cout << A << endl;
	A.print();*/

	Fraction A;
	cout << "Введите простую дробь: "; cin >> A;
	cout  << A << endl;
}