#define _USE_MATH_DEFINES
#pragma warning(disable:4326)
#include<iostream>
#include<Windows.h>
//#include<cmath>
/*
------------------------------------------
enum(������������) - ����� ����������� �������� ���� int
��������� ���������� ����� ��������� ��������
� ������ ��������� ����������� ���� ��������,
���� �������� ��������� �� ������� ,�� ��� ������ �������� �� 
������� ������ ����������
������������ ������ ���������� � ����,
����������� ��������� � ����� �++,
������������ ����� �������� ����� ������
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
			std::cout << "�������:\t" << get_area() << std::endl;
			std::cout << "��������:\t" << get_perimeter() << std::endl;
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
			HWND hConsole = GetConsoleWindow();//�������� ���� �������,����� � ���� ����� ���� ����������
			HDC hdc = GetDC(hConsole);//������� �������� ���������� ����������� ����
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);//������� ��������,������� ����� �������� ������
			//PS_SOLID - ��������� �����, 5 - ������� ����� 5 ��������
			SelectObject(hdc, hPen);//�������� �������� ��������
			HBRUSH hBrush = CreateSolidBrush(color);//������� �����.����� ����������� ��������� ������
			SelectObject(hdc, hBrush);//�������� ��������� �����
			//����� � �������� ���������� ��� ����, ����� ������� Rectangle ��������,��� ��������

			::Rectangle(hdc, start_x, start_y, start_x + side, start_y + side);//������ �������

			DeleteObject(hBrush);//������� �����
			DeleteObject(hPen);//������� ��������
			ReleaseDC(hConsole, hdc);//����������� �������� ����������
		}

		void info()const
		{
			std::cout << typeid(*this).name() << std::endl;
			std::cout << "����� �������: " << side << std::endl;
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
			HWND hConsole = GetConsoleWindow();//�������� ���� �������,����� � ���� ����� ���� ����������
			HDC hdc = GetDC(hConsole);//������� �������� ���������� ����������� ����
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);//������� ��������,������� ����� �������� ������
			//PS_SOLID - ��������� �����, 5 - ������� ����� 5 ��������
			SelectObject(hdc, hPen);//�������� �������� ��������
			HBRUSH hBrush = CreateSolidBrush(color);//������� �����.����� ����������� ��������� ������
			SelectObject(hdc, hBrush);//�������� ��������� �����
			//����� � �������� ���������� ��� ����, ����� ������� Rectangle ��������,��� ��������

			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + length);//������ �������

			DeleteObject(hBrush);//������� �����
			DeleteObject(hPen);//������� ��������
			ReleaseDC(hConsole, hdc);//����������� �������� ����������
		}
		void info()const
		{
			std::cout << typeid(*this).name() << std::endl;
			std::cout << "������:\t" << width << std::endl;
			std::cout << "�����:\t" << length << std::endl;
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
			HWND hConsole = GetConsoleWindow();//�������� ���� �������,����� � ���� ����� ���� ����������
			HDC hdc = GetDC(hConsole);//������� �������� ���������� ����������� ����
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);//������� ��������,������� ����� �������� ������
			//PS_SOLID - ��������� �����, 5 - ������� ����� 5 ��������
			SelectObject(hdc, hPen);//�������� �������� ��������
			HBRUSH hBrush = CreateSolidBrush(color);//������� �����.����� ����������� ��������� ������
			SelectObject(hdc, hBrush);//�������� ��������� �����
			//����� � �������� ���������� ��� ����, ����� ������� Rectangle ��������,��� ��������

			::Ellipse (hdc, start_x, start_y, start_x + get_diameter(), start_y + get_diameter());//������ �������

			DeleteObject(hBrush);//������� �����
			DeleteObject(hPen);//������� ��������
			ReleaseDC(hConsole, hdc);//����������� �������� ����������
		}
		void info()const
		{
			std::cout << typeid(*this).name() << std::endl;
			std::cout << "������:\t" << radius << std::endl;
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
	/*cout << "������� ��������:\t" << square.get_side() << endl;
	cout << "������� ��������:\t" << square.get_area() << endl;
	cout << "�������� ��������:\t" << square.get_perimeter() << endl;
	square.draw();*/
	square.info();

	Geometry::Rectangle rect(200, 100, Geometry::Color::red, 300, 400, 5);
	rect.info();

	Geometry::Circle circle(100, Geometry::Color::blue, 300, 400, 5);
	circle.info();
}

