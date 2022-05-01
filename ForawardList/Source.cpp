//DataContainers
//TemplatedForwardList
#include<iostream>
#include<string>

using std::cout;
using std::cin;
using std::endl;

#define DEBUG
#define tab "\t"

template<typename T>class ForwardList;
template<typename T>class Iterator;

template<typename T>
class Element
{
	static int count;
	T Data;//�������� ��������
	Element<T>* pNext;//����� ���������� ��������
    //Element* - ��������� �� �������
	//Element*<T> - ��������� �� ������� ���������� ����
public:
	Element(T Data, Element<T>* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		std::cout << "EConstructor:\t" << this << std::endl;
#endif // DEBUG

	}
	~Element()
	{
		count--;
#ifdef DEBUG
		std::cout << "EDestructor:\t" << this << std::endl;
#endif // DEBUG

	}
	friend class ForwardList<T>;
	friend class Iterator<T>;
};

template<typename T>
int Element<T>::count = 0;

template<typename T>
class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr) : Temp(Temp)
	{
		std::cout << "ItConstructor:\t" << this << std::endl;
	}
	~Iterator()
	{
		std::cout << "ItDestructor:\t" << this << std::endl;
	}
	Iterator<T>& operator++()//Prefix increment
	{
		Temp = Temp->pNext;//������� �� ��������� �������
		return *this;
	}
	Iterator<T> operator++(int)//Postfix increment
	{
		Iterator old = *this;//��������� ������ �������� ���������
		Temp = Temp->pNext;//�������� ��������
		return old;//���������� ������ ��������
	}
	bool operator ==(const Iterator<T>& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator !=(const Iterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}

	const T& operator*()const
	{
		return Temp->Data;
	}
	T& operator*()
	{
		return Temp->Data;
	}

	operator bool()const
	{
		return Temp;
	}
};

template<typename T>
class ForwardList//����������� (����������������)������
{
	Element<T>* Head;// ������ ������ - ��������� �� ��������� ������� ������
	uint32_t size;//������ ������
public:
	Element<T>* getHead()const
	{
		return Head;
	}
	uint32_t get_size()const
	{
		return this->size;
	}
	Iterator<T> begin()
	{
		return Head;
	}
	Iterator<T> end()
	{
		return nullptr;
	}
	ForwardList()
	{
		Head = nullptr;//���� ������ ��������� �� 0, �� ������ ������
		size = 0;
		std::cout << "LConstructor:\t" << this << std::endl;
	}

	ForwardList(uint32_t size) : ForwardList()
	{
		//this->Head = nullptr;
		//this->size = 0;
		for (int i = 0; i < size; ++i)
		{
			push_front(T());
			//T() - �������� �� ��������� ��� ���������� ����
		}
	}
	ForwardList(const std::initializer_list<T>& il) : ForwardList()
	{
		//il.begin() - ���������� �������� �� ������ ����������
		//il.end() - ���������� �������� �� ������ ����������
		cout << typeid(il.begin()).name() << endl;
		//const int* - ������������ ���������(�� ���������� �����)
		//int const* - ��������� �� ���������(�� ���������� �������� �� ������)
		/*for (int const* it = il.begin(); it != il.end(); ++it)
		{
			//it - iterator
			push_back(*it);//*it - ���������� �������� �� ������
		}*/
		for (T const* it = il.end() - 1; it != il.begin() - 1; --it)
		{
			push_front(*it);
		}
	}
	ForwardList(const ForwardList<T>& other) : ForwardList()
	{
		//for (Element<T>* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		for (Iterator<T> it = other.Head; it != nullptr; it++)push_back(*it);
		cout << "CopyConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		std::cout << "LDestructor:\t" << this << std::endl;
	}
	//Operators
	ForwardList<T>& operator=(const ForwardList<T>& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();//������� ���� ������
		for (Iterator<T> it = other.Head; it; ++it)push_back(*it);//�������� �� ���� ������, 
		//��������� �������� ��� ��������� � ���� ������
		cout << "CopyAssigment:\t" << this << endl;
	}
	const T& operator[](int index)const
	{
		Element<T>* Temp = Head;
		for (int i = 0; i < index; ++i)Temp = Temp->pNext;
		return Temp->Data;
	}
	T& operator[](int index)
	{
		Element<T>* Temp = Head;
		for (int i = 0; i < index; ++i)Temp = Temp->pNext;
		return Temp->Data;
	}
	//					Adding elements
	void push_front(T Data)
	{
		//Element* New = new Element(Data);//������� ����� ������� � �������� � ���� �������� Data
		//New->pNext = Head;//����������� ����� ������� � ������ ������
		//Head = New;//��������� ������ �� ����� �������
		Head = new Element<T>(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		//��������� �������� �� ������ ������
		if (Head == nullptr)return push_front(Data);
		//������� ����� �������
		//Element* New = new Element(Data);
		//������� �� ����� ������
		Element<T>* Temp = Head;
		while (Temp->pNext)// ���� pNext �������� �������� �� ����
			Temp = Temp->pNext;//��������� �� �������� �������
		//������ �� ��������� � ��������� ��������, �.� Temp->pNext == nulptr
		//������������ ����� ������� � ����������
		//Temp->pNext = New;
		Temp->pNext = new Element<T>(Data);
		size++;
	}
	//Remove elements
	void pop_front()
	{
		if (Head == nullptr)return;
		//���������� ����� ���������� ��������
		Element<T>* Erased = Head;
		//��������� ��������� ������� �� ������
		Head = Erased->pNext;
		//������� ������� �� ������
		delete Erased;

		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		//������� �� �������������� �������a
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//������� ������� �� ������
		delete Temp->pNext;
		//�������� ����� ���������� �������� �����
		Temp->pNext = nullptr;
		size--;
	}

	void erase(int index)
	{
		if (index > size)return;
		//������� �� ������� ��������
		if (index == 0)return pop_front();
		Element<T>* Temp = Head;//������� �������� � ������� � ������ ����� ������
		//������ � ��������� ����� ��������� ��������
		for (int i = 0; i < index - 1; ++i)Temp = Temp->pNext;
		//���������� ����� ���� ���������� ��������
		Element<T>* Erased = Temp->pNext;
		//��������� �� ������
		Temp->pNext = Temp->pNext->pNext;//Erased->pNext
		//������� ������� �� ������
		delete Erased;
		size--;
	}
	void insert(int index, T Data)
	{
		if (index == 0 || Head == nullptr)return push_front(Data);
		if (index > size)return;
		//Element* New = new Element(Data);
		//������� �� ������� ��������
		Element<T>* Temp = Head;
		for (int i{ 0 }; i < index - 1; ++i)Temp = Temp->pNext;
		//�������� ����� ������� � ������:
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;
		Temp->pNext = new Element<T>(Data, Temp->pNext);
		size++;
	}
	//Methods
	void print()const
	{
#if OLD_PRINT
		Element* Temp = Head;//Temp - �������� 
//�������� - ��������� ��� ������ �������� ����� �������� ������ � ��������� ��������� ������
		while (Temp)//���� �������� �������� ���������� �����
		{
			std::cout << Temp << tab << Temp->Data << tab
				<< Temp->pNext << std::endl;
			Temp = Temp->pNext;//������� �� ��������� �������
		}
#endif // OLD_PRINT

		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		//for (Element* Temp = Head; Temp; Temp++)
			std::cout << Temp << tab << Temp->Data << tab << Temp->pNext << std::endl;
		std::cout << "���������� ��������� ������: " << size << std::endl;
		std::cout << "����� ���������� ��������� ������: " << Head->count << std::endl;
	}
};

template<typename T>
void print_list(const ForwardList<T>& list)
{
	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
}

//#define BASE_CHECK
//#define DESTRUCTOR_CHECK
//#define HOME_WORK1
//#define HOME_WORK2
//#define RANGE_BASED_FOR_ARRAY


int main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n; cout << "������� ������ ������: "; cin >> n;
	ForwardList list;
	list.pop_front();
	for (int i{ 0 }; i < n; ++i)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	//list.push_back(123);
	//list.pop_front();
	//list.pop_back();

	int index;
	int value;
	cout << "������� �����c ������������ ��������: "; cin >> index;
	cout << "������� �������� ������������ ��������: "; cin >> value;

	list.insert(index, value);
	list.print();

	cout << "������� ������ ���������� ��������: "; cin >> index;
	list.erase(index);
	list.print();

#endif // BASE_CHECK

	/*ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);
	list2.print();*/

#ifdef DESTRUCTOR_CHECK
	int n;
	std::cout << "������� ������ ������: "; std::cin >> n;
	ForwardList list;
	for (int i = 0; i < n; ++i)
	{
		list.push_front(rand());
	}
	//std::cout << "������ ��������" << std::endl;
	list.print();
#endif // DESTRUCTOR_CHECK

#ifdef HOME_WORK1
	int n;
	cout << "������� ������ ������: "; cin >> n;
	ForwardList list(n);
	for (int i = 0; i < n; ++i)
	{
		list[i] = rand() % 100;
	}

	for (int i = 0; i < n; ++i)
	{
		cout << list[i] << tab;
	}
	cout << endl;
#endif // HOME_WORK1

#ifdef HOME_WORK2
	//l-value = r-value
	ForwardList list = { 3,5,8,13,21 };//������ ������� ������ ������ initializer_list
	//ForwardList = initializer_list
	//list.print();
	for (Iterator it = list.getHead(); it != nullptr; ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	/*Iterator it = list.getHead();
	Iterator it2 = ++it;*/
#endif // HOME_WORK2

#ifdef RANGE_FOR_BASED_ARRAY
	int arr[] = { 3,5,8,13,21 };
	/*for (int i = 0; i < sizeof(arr) / sizeof(int); ++i)
	{
		cout << arr[i] << tab;
	}
	cout << endl;*/

	for (int i : arr)// range - based for(for ��� ���������)
	{
		cout << i << tab;
	}
	cout << endl;
	//��� ������������ ���������� ���������(������,������)
	// � ������ ������ ���������� foreach  
#endif // RANGE_FOR_BASED_ARRAY

	ForwardList<int> list = { 3,5,8,13,21 };
	for (Iterator<int> it = list.begin(); it != list.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
	/*
	for(value : container)
	{
		cout << value;
	}
	value - ��������������� ��������� �������� ���� ��������� ����������

	*/

	/*
	* class object;  �������� �������� ������
	* class<type> object;  �������� ���������� ������
	* template<typename T>
	*/
	ForwardList<double> d_list = { 2.5, 3.14, 5.2, 8.3 };
	for (double i : d_list)
	{
		cout << i << tab;
	}
	cout << endl;

	ForwardList<std::string> s_list = { "Have","a","nice","day" };
	for (std::string i : s_list)cout << i << tab; cout << endl;

	//ForwardList<std::string> s_list2 = s_list;//CopyConstructor
	ForwardList<std::string> s_list2;
	s_list2 = s_list;
	for (std::string i : s_list2)cout << i << tab; cout << endl;

}