#include<iostream>
#include<fstream>

//#define WRITE_TO_FILE
#define READ_FROM_FILE

int main()
{
	using namespace std;
	setlocale(LC_ALL, "");
#ifdef WRITE_TO_FILE
	cout << "Hello World" << endl;

	ofstream fout("file.txt", ios::app);//app - добавить, дописать
	fout << "Hello World" << endl;
	fout.close();

	system("notepad file.txt");
#endif // WRITE_TO_FILE

	const int SIZE = 256;
	char buffer[SIZE]{};

	ifstream fin;//создаем поток
	fin.open("file.txt");

	if (fin.is_open())
	{
		//читаем файл
		while (!fin.eof())//пока не конец файла
		{
			//fin >> buffer;
			fin.getline(buffer, SIZE);
			cout << buffer << endl;
		}
	}
	else
	{
		cerr << "Eror: file not found" << endl;
	}

	fin.close();

}