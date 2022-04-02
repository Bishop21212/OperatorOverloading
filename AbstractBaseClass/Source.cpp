#pragma warning(disable:4326)
#include<iostream>
#include<Windows.h>
/*
------------------------------------------
enum(перечислени€) - набор именованных констант типа int
ѕозвол€ют определить набор возможных значений
у каждой константы пречислений свое значение,
если значение константы не заданно ,то оно примет значение на 
единицу больше предыдущей
перечислени€ всегда начинаютс€ с нул€,
перчислени€ по€вились в €зыке —++,
перечислени€ также €вл€ютс€ типом данных
-------------------------------------------
*/
enum Color
{
	some_colore,
	console_blue = 0x099,
	console_green = 0x0AA, 
	console_red = 0x0CC,
	console_default = 0x07
};

class Shape
{
protected:
	Color color;
public:
	Shape(Color color) : color(color){}
	virtual ~Shape(){}

	virtual double get_area()const = 0;
	virtual double get_perimeter()const = 0;
	virtual void draw()const = 0;
};

class Square : public Shape
{
	double side;
public:
	double get_side()const
	{
		return side;
	}
	void set_side(double side)
	{
		if (side <= 0)side = 10;
		this->side = side;
	}
	Square(double side, Color color = Color::console_default) :Shape(color)
	{
		set_side(side);
	}
	~Square(){}

	double get_area()const
	{
		return side * side;
	}
	double get_perimeter()const
	{
		return side * 4;
	}
	void draw()const
	{
		/*HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole,color);
		for (int i{ 0 }; i < side; ++i)
		{
			for (int i{ 0 }; i < side; ++i)
			{
				std::cout << "* ";
			}
			std::cout << std::endl;
		}
		SetConsoleTextAttribute(hConsole, Color::console_default);
	}*/
		//H - Handle
		HWND hConsole = GetConsoleWindow();
		HDC hdc = GetDC(hConsole);
		HPEN hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
		SelectObject(hdc, hPen);

		Rectangle(hdc, 300, 300, 400, 400);

		DeleteObject(hPen);
		ReleaseDC(hConsole, hdc);
	}
};

int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD buffer = { 16,16 };
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &buffer);
	using namespace std;
	setlocale(LC_ALL, "");
	Square square(5, Color::console_red);
	cout << "—торона квадрата:\t" << square.get_side() << endl;
	cout << "ѕлощадь квадрата:\t" << square.get_area() << endl;
	cout << "ѕериметр квадрата:\t" << square.get_perimeter() << endl;
	square.draw();
}

