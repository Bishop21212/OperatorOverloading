//Department
#include<iostream>
#include<string>
#include<fstream>
using std::cout; using std::cin;using std::endl;


#define HUMAN_TAKE_PARAMETERS const std::string& last_name,const std::string& first_name,uint32_t age
#define HUMAN_GIVE_PARAMETERS last_name,first_name,age

class Human
{
	std::string last_name;
	std::string first_name;
	uint32_t age;
public:// реализаци€ инкапсул€ции константным методом
	const std::string& get_last_name()const
	{
		return last_name;
		last_name.length();
	}
	const std::string& get_first_name()const
	{
		return first_name;
	}
	uint32_t get_age()const
	{
		return age;
	}
	void set_last_name(const std::string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const std::string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(uint32_t age)
	{
		this->age = age;
	}
	//Constructors
	Human(const std::string& last_name, const std::string& first_name, uint32_t age)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		cout << "HDestructor:\t" << this << endl;
	}
	//Methods
	virtual std::ostream& print(std::ostream& os)const 
	{
		//return os << last_name << " " << first_name << " " << age << " лет" << endl;
		os.width(10);
		os << last_name;
		os.width(10);
		os << first_name;
		os.width(3);
		os << age << " лет";
		return os;
	}
	virtual std::ofstream& print(std::ofstream& os)const
	{
		//return os << last_name << " " << first_name << " " << age << " лет" << endl;
		os.width(10);
		os << last_name;
		os.width(10);
		os << first_name;
		os.width(3);
		os << age;
		return os;
	}
};

std::ostream& operator << (std::ostream& os, const Human& obj)
{
	return obj.print(os);
}

std::ofstream& operator << (std::ofstream& os, const Human& obj)
{
	return obj.print(os);
}

#define EMPLOYEE_TAKE_PARAMETERS	const std::string& position
#define EMPLOYEE_GIVE_PARAMETERS    position

class Employee:public Human
{
	std::string position;
public:
	const std::string& get_position()const
	{
		return position;
	}
	void set_position(const std::string& position)
	{
		this->position = position;
	}
	virtual double get_salary()const = 0;

	Employee(HUMAN_TAKE_PARAMETERS,EMPLOYEE_TAKE_PARAMETERS):Human(HUMAN_GIVE_PARAMETERS)
	{
		set_position(position);
		cout << "EConstructor:\t" << this << endl;
	}
	~Employee()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	std::ostream& print(std::ostream& os)const
	{
		Human::print(os) << " "; //print - вызываем из базового класса
		os.width(10);
		return os << position;
	}
	std::ofstream& print(std::ofstream& os)const
	{
		Human::print(os) << " "; //print - вызываем из базового класса
		os.width(10);
		os << position;
		return os;
	}
};

#define PERMANENT_EMPLOYEE_TAKE_PARAMETERS double salary
#define PERMANENT_EMPLOYEE_GIVE_PARAMETERS  salary

class PermanentEmployee : public Employee
{
	double salary;
public:
	double get_salary()const
	{
		return salary;
	}
	void set_salary(double salary)
	{
		this->salary = salary;
	}
	PermanentEmployee
	(
		HUMAN_TAKE_PARAMETERS,
		EMPLOYEE_TAKE_PARAMETERS,
		PERMANENT_EMPLOYEE_TAKE_PARAMETERS
	) :Employee(HUMAN_GIVE_PARAMETERS, EMPLOYEE_GIVE_PARAMETERS)
	{
		set_salary(salary);
		cout << "PEConstructor:\t" << this << endl;
	}
	~PermanentEmployee()
	{
		cout << "PEDestructor:\t" << this << endl;
	}
    std::ostream& print(std::ostream& os)const
	{
		Employee::print(os) << " ";
		return os << salary;
	}
	std::ofstream& print(std::ofstream& os)const
	{
		Employee::print(os) << " ";
		 os << salary;
		 return os;
	}
};


#define HOURLY_EMPLOYEE_TAKE_PARAMETERS double rate,int hours
#define HOURLY_EMPLOYEE_GIVE_PARAMETERS rate,hours

class HourlyEmployee :public Employee
{
	double rate;//тариф (савка за час) 
	int hours;//количество отработанных часов
public:
	double get_rate()const
	{
		return rate;
	}
	int get_hours()const
	{
		return hours;
	}
	double get_salary()const
	{
		return rate * hours;
	}
	void set_rate(double rate)
	{
		this->rate = rate;
	}
	void set_hours(int hours)
	{
		this->hours = hours;
	}
	HourlyEmployee(HUMAN_TAKE_PARAMETERS, EMPLOYEE_TAKE_PARAMETERS, HOURLY_EMPLOYEE_TAKE_PARAMETERS)
		:Employee(HUMAN_GIVE_PARAMETERS, EMPLOYEE_GIVE_PARAMETERS)
	{
		set_rate(rate);
		set_hours(hours);
		cout << "HEConstructor:\t" << this << endl;
	}
	~HourlyEmployee()
	{
		cout << "HEDestructor:\t" << this << endl;
	}
	std::ostream& print(std::ostream& os)const
	{
	    Employee::print(os) << " ";
		os << "тариф:";
		os.width(5);
		os << rate;
		os << ", отработанно:";
		os.width(3);
		os << hours << ", итого:" << get_salary();
		return os;
	}
	std::ofstream& print(std::ofstream& os)const
	{
		Employee::print(os) << " ";
		os.width(10);
		os << rate;
		os.width(3);
		os << hours;
		return os;
	}
};

int main()
{
	using namespace std;
	std::string str = "Hello";
	cout << str.c_str()[1] << endl;
	cout << typeid(str.c_str()).name() << endl;
	setlocale(LC_ALL, "");
	Employee* department[] =
	{
		new PermanentEmployee("Rosenberg","Ken",30,"Lawyer",2000),
		new PermanentEmployee("Diaz","Ricardo", 50,"Boss",5000),
		new HourlyEmployee("Vercetti","tomas",30,"Securuty",500,8)
	};

	//cout << department[0]->get_first_name().c_str();
	//dinamic_cast<> - преобразует указатель на базовый класс в дочерний 
	double total_salary = 0;
	for (int i{ 0 }; i < sizeof(department) / sizeof(Employee*); ++i)
	{
		//department[i]->print();
		cout << *department[i] << endl;
		total_salary += department[i]->get_salary();
		cout << "\n----------------------------------------\n";
	}
	cout << "ќбща€ зарплата всего отдела`: " << total_salary << endl;
	cout << "\n--------------------------------------------\n";

	ofstream fout("file.txt");
	for (int i{ 0 }; i < sizeof(department) / sizeof(Employee*); ++i)
	{
		fout.width(23);
		fout << left;
		fout << std::string(typeid(*department[i]).name()) << ':';
			fout << * department[i] << endl;
	}
	fout.close();
	system(" start notepad file.txt");

	for (int i{ 0 }; i < sizeof(department) / sizeof(Employee*); ++i)
	{
		delete department[i];
	}
}
