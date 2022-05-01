#define _USE_MATH_DEFINES
#pragma warning(disable:4326)
#include<iostream>
#include<Windows.h>
//#include<cmath>
/*
------------------------------------------
enum(перечисления) - набор именованных констант типа int
Позволяют определить набор возможных значений
у каждой константы пречислений свое значение,
если значение константы не заданно ,то оно примет значение на 
единицу больше предыдущей
перечисления всегда начинаются с нуля,
перчисления появились в языке С++,
перечисления также являются типом данных
-------------------------------------------
*/
namespace Geometry
{
	enum Color
	{
		red = 0x000000F,
		green = 0x0000FF00,
		blue = 0x00FF0000,

		some_colore,
		console_blue = 0x099,
		console_green = 0x0AA,
		console_red = 0x0CC,
		console_default = 0x07
	};

	class Shape
	{
	protected:
		uint32_t start_x;
		uint32_t start_y;
		uint32_t line_width;
		Color color;
	public:
		void set_start_x(uint32_t start_x)
		{
			if (start_x > 300)start_x = 300;
			this->start_x = start_x;
		}
		void set_start_y(uint32_t start_y)
		{
			if (start_y > 300)start_y = 300;
			this->start_y = start_y;
		}
		void set_line_width(uint32_t)
		{
			if (line_width > 20)line_width = 20;
			this->line_width = line_width;
		}
		Shape(Color color, uint32_t start_x, uint32_t start_y, uint32_t line_width) : color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}

		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;

		virtual void info()const
		{
			std::cout << "Площадь:\t" << get_area() << std::endl;
			std::cout << "Периметр:\t" << get_perimeter() << std::endl;
			draw();
		}
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
		Square(double side, Color color,
			uint32_t start_x, uint32_t start_y, uint32_t line_width)
			:Shape(color, start_x, start_y, line_width)
		{
			set_side(side);
		}
		~Square() {}

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
			HWND hConsole = GetConsoleWindow();//получаем окно консоли,чтобы к нему можно было обратиться
			HDC hdc = GetDC(hConsole);//Создаем контекст устройства ролученного окна
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);//Создаем карандаш,который будет рисовать контур
			//PS_SOLID - срплошная линия, 5 - толщина линии 5 пикселов
			SelectObject(hdc, hPen);//выбираес созданый карандаш
			HBRUSH hBrush = CreateSolidBrush(color);//Создаем кисть.Кисть закрашивает замкнутые фигуры
			SelectObject(hdc, hBrush);//Выбираем созданную кисть
			//Кисть и карандаш выбираются для того, чтобы функция Rectangle понимала,чем рисовать

			::Rectangle(hdc, start_x, start_y, start_x + side, start_y + side);//Рисует квадрат

			DeleteObject(hBrush);//удаляем кисть
			DeleteObject(hPen);//удаляем карандаш
			ReleaseDC(hConsole, hdc);//освобождаем контекст устройства
		}

		void info()const
		{
			std::cout << typeid(*this).name() << std::endl;
			std::cout << "Длина стороны: " << side << std::endl;
			Shape::info();
		}
	};

	class Rectangle : public Shape
	{
		double width;
		double length;
	public:
		double get_width()const
		{
			return width;
		}
		double get_length()const
		{
			return length;
		}
		void set_width(double width)
		{
			if (width <= 0)width = 20;
			this->width = width;
		}
		void set_length(double length)
		{
			if (length <= 0)length = 10;
			this->length = length;
		}
		Rectangle(double width, double length,
			Color color, uint32_t start_x, uint32_t start_y, uint32_t line_width)
			:Shape(color, start_x, start_y, line_width)
		{
			set_width(width);
			set_length(length);
		}
		~Rectangle() {}

		double get_area()const
		{
			return width * length;
		}
		double get_perimeter()const
		{
			return(width + length) * 2;
		}
		void draw()const
		{
			HWND hConsole = GetConsoleWindow();//получаем окно консоли,чтобы к нему можно было обратиться
			HDC hdc = GetDC(hConsole);//Создаем контекст устройства ролученного окна
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);//Создаем карандаш,который будет рисовать контур
			//PS_SOLID - срплошная линия, 5 - толщина линии 5 пикселов
			SelectObject(hdc, hPen);//выбираес созданый карандаш
			HBRUSH hBrush = CreateSolidBrush(color);//Создаем кисть.Кисть закрашивает замкнутые фигуры
			SelectObject(hdc, hBrush);//Выбираем созданную кисть
			//Кисть и карандаш выбираются для того, чтобы функция Rectangle понимала,чем рисовать

			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + length);//Рисует квадрат

			DeleteObject(hBrush);//удаляем кисть
			DeleteObject(hPen);//удаляем карандаш
			ReleaseDC(hConsole, hdc);//освобождаем контекст устройства
		}
		void info()const
		{
			std::cout << typeid(*this).name() << std::endl;
			std::cout << "Ширина:\t" << width << std::endl;
			std::cout << "Длина:\t" << length << std::endl;
			Shape::info();
		}
	};

	class Circle : public Shape
	{
		double radius;
	public:
		double get_radius()const
		{
			return radius;
		}
		double get_diameter()const
		{
			return radius * 2;
		}
		void set_radius(double radius)
		{
			if (radius <= 0)radius = 10;
			this->radius = radius;
		}
		Circle(double radius,Color color, uint32_t start_x, uint32_t start_y, uint32_t line_width)
			:Shape(color, start_x, start_y,line_width)
		{
			set_radius(radius);
		}
		~Circle(){}

		double get_area()const
		{
			return M_PI * radius * radius;
		}
		double get_perimeter()const
		{
			return 2 * M_PI * radius;
		}
		void draw()const
		{
			HWND hConsole = GetConsoleWindow();//получаем окно консоли,чтобы к нему можно было обратиться
			HDC hdc = GetDC(hConsole);//Создаем контекст устройства ролученного окна
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);//Создаем карандаш,который будет рисовать контур
			//PS_SOLID - срплошная линия, 5 - толщина линии 5 пикселов
			SelectObject(hdc, hPen);//выбираес созданый карандаш
			HBRUSH hBrush = CreateSolidBrush(color);//Создаем кисть.Кисть закрашивает замкнутые фигуры
			SelectObject(hdc, hBrush);//Выбираем созданную кисть
			//Кисть и карандаш выбираются для того, чтобы функция Rectangle понимала,чем рисовать

			::Ellipse (hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());//Рисует квадрат

			DeleteObject(hBrush);//удаляем кисть
			DeleteObject(hPen);//удаляем карандаш
			ReleaseDC(hConsole, hdc);//освобождаем контекст устройства
		}
		void info()const
		{
			std::cout << typeid(*this).name() << std::endl;
			std::cout << "Радиус:\t" << radius << std::endl;
			Shape::info();
		}
	};

}
int main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD buffer = { 16,16 };
	//SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &buffer);
	using namespace std;
	setlocale(LC_ALL, "");
	Geometry::Square square(250, Geometry::Color::green,100,300,5);
	/*cout << "Сторона квадрата:\t" << square.get_side() << endl;
	cout << "Площадь квадрата:\t" << square.get_area() << endl;
	cout << "Периметр квадрата:\t" << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect(200, 100, Geometry::Color::red, 300, 400, 5);
	rect.info();

	Geometry::Circle circle(100, Geometry::Color::blue, 300, 400, 5);
	circle.info();
}

