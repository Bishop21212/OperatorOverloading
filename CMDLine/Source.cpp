//CMDLine
#include<iostream>

int main(int argc,char* argv[])// ��������� � ��������� �������
{
	//int argc -(arguments count) - ���������� �������� ���������� ��������� ������ 
	//char* argv - (argument values) - ������ ����� , ������� �������� �������� ����������
	//������� ������ ������� argv[] ��� ������ ��� ������������ ����� ���������(������� ���� � ������������ �����)
	using namespace std;
	setlocale(LC_ALL, "");
	for (int i{ 0 }; i < argc; ++i)
	{
		cout << "argv[" << i << "]\t" << argv[i] << endl;
	}
	/*if (argc > 5)
	{
		cerr << "������������ ��������� �������" << endl;
		return 1;
	}*/
}