#include"String.h"

int String::get_size()const
{
	return size;
}
const char* String::get_str()const
{
	return str;
}
char* String::get_str()
{
	return str;
}
String::String(int size) : size(size), str(new char[size] {})
{
	//this->size = size;
	//this->str = new char[size] {}; //��������
	cout << "Constructor:\t" << this << endl;
}
String::String(const char str[]) : String(strlen(str) + 1)
{
	//this->size = strlen(str) + 1;
	//this->str = new char[size] {};
	for (int i{ 0 }; str[i]; ++i)this->str[i] = str[i];
	cout << "SizeConstructor:\t" << this << endl;
}
String::String(const String& other) : String(other.str) //CopyConstructor
{
	//��������� ����������� DeepCopy
	//this->size = other.size; //�������� ������ �� ������� �������
	//this->str = new char[size] {};//�������� ������
	//for (int i{ 0 }; i < size; ++i)this->str[i] = other.str[i];
	cout << "CopyConstructor:\t" << this << endl;
}
String::~String()
{
	delete[]str;
	cout << "Destructor:\t" << this << endl;
}
//OPerators
String& String::operator=(const String& other)
{
	if (this == &other)return *this;
	delete[]this->str;
	this->size = other.size; //�������� ������ �� ������� �������
	this->str = new char[size] {};//�������� ������
	for (int i{ 0 }; i < size; ++i)this->str[i] = other.str[i];
	cout << "CopyAssigment:\t" << this << endl;
	return *this;
}
String& String::operator+=(const String& other)
{
	return *this = *this + other;
}
const char& String::operator[](int i)const
{
	return str[i];
}
char& String::operator[](int i)
{
	return str[i];
}
//Methods
void String::print()const
{
	cout << "Size:\t" << size << endl;
	cout << "Str:\t" << str << endl;
}

String operator+(const String& left, const String& right)
{
	String result(left.get_size() + right.get_size() - 1);// -1 ��� ������� ���� ������������� ����
	for (int i{ 0 }; i < left.get_size(); ++i)
		result[i] = left[i];
	//result.get_str()[i] = left.get_str()[i];
	for (int i{ 0 }; i < right.get_size(); ++i)
		result[i + left.get_size() - 1] = right[i];
	//result.get_str()[i + left.get_size() - 1] = right.get_str()[i];
	return result;
}

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}
std::istream& operator >> (std::istream& is, String& obj)
{
	//return is >> obj.get_str();
	const int SIZE = 10240 * 1000;
	char buffer[SIZE] = {};
	is >> buffer;
	obj = buffer;
	return is;
}

std::istream& getline(std::istream& is, String& obj)
{
	const int SIZE = 1024 * 1000;
	char buffer[SIZE]{};
	is.getline(buffer, SIZE);
	obj = buffer;
	return is;
}
