//CMDLine
#include<iostream>

int main(int argc,char* argv[])// св€зываес с командной строкой
{
	//int argc -(arguments count) - количество прин€тых аргументов командной строки 
	//char* argv - (argument values) - массив строк , который содержит значени€ аргументов
	//нулевой элемет массива argv[] это полное им€ исполн€емого файла программы(включа€ путь к исполн€емому файлу)
	using namespace std;
	setlocale(LC_ALL, "");
	for (int i{ 0 }; i < argc; ++i)
	{
		cout << "argv[" << i << "]\t" << argv[i] << endl;
	}
	/*if (argc > 5)
	{
		cerr << "Ќеправильный синтаксис команды" << endl;
		return 1;
	}*/
}