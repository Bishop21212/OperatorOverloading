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
	T Data;//Значение элемента
	Element<T>* pNext;//Адрес следующего элемента
    //Element* - указатель на элемент
	//Element*<T> - указатель на элемент шаблонного типа
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
		Temp = Temp->pNext;//переход на следующий элемент
		return *this;
	}
	Iterator<T> operator++(int)//Postfix increment
	{
		Iterator old = *this;//Сохраняем старое значение итератора
		Temp = Temp->pNext;//Изменяем итератор
		return old;//возвращаем старое значение
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
class ForwardList//односвязный (однонаправленный)список
{
	Element<T>* Head;// Голова списка - указывает на начальный элемент списка
	uint32_t size;//размер списка
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
		Head = nullptr;//если голова указывает на 0, то список пустой
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
			//T() - значение по умолчанию для шаблонного типа
		}
	}
	ForwardList(const std::initializer_list<T>& il) : ForwardList()
	{
		//il.begin() - возвращает итератор на начало контейнера
		//il.end() - возвращает итератор на начало контейнера
		cout << typeid(il.begin()).name() << endl;
		//const int* - контстантный указатель(не изменяется адрес)
		//int const* - указатель на константу(не изменяется значение по адресу)
		/*for (int const* it = il.begin(); it != il.end(); ++it)
		{
			//it - iterator
			push_back(*it);//*it - возвращает значение по адресу
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
		while (Head)pop_front();//Очищаем этот список
		for (Iterator<T> it = other.Head; it; ++it)push_back(*it);//проходим по тому списку, 
		//вставляем значения его элементов в этот список
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
		//Element* New = new Element(Data);//создаем новый элеиент и помещаем в него значение Data
		//New->pNext = Head;//привязываем новый элемент к началу списка
		//Head = New;//переводим Голову на новый элемент
		Head = new Element<T>(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		//проверяем является ли список пустым
		if (Head == nullptr)return push_front(Data);
		//Создаем новый элемент
		//Element* New = new Element(Data);
		//Доходим до конца списка
		Element<T>* Temp = Head;
		while (Temp->pNext)// пока pNext текущего элемента не ноль
			Temp = Temp->pNext;//переходим на следущий элемент
		//теперь мы находимся в последнем элементе, т.е Temp->pNext == nulptr
		//Присоединяем новый элемент к последнему
		//Temp->pNext = New;
		Temp->pNext = new Element<T>(Data);
		size++;
	}
	//Remove elements
	void pop_front()
	{
		if (Head == nullptr)return;
		//запоминаем адрес удаляемого элемента
		Element<T>* Erased = Head;
		//исключаем удаляемый элемент из списка
		Head = Erased->pNext;
		//удаляем элемент из памяти
		delete Erased;

		size--;
	}
	void pop_back()
	{
		if (Head == nullptr)return;
		if (Head->pNext == nullptr)return pop_front();
		//доходим до предпоследнего элементa
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//Удаляем элемент из памяти
		delete Temp->pNext;
		//затираем адрес удаленного элемента нулем
		Temp->pNext = nullptr;
		size--;
	}

	void erase(int index)
	{
		if (index > size)return;
		//доходим до нужного элемента
		if (index == 0)return pop_front();
		Element<T>* Temp = Head;//создаем итератор и заходим в список через голову
		//теперь в итераторе адрес головного элемента
		for (int i = 0; i < index - 1; ++i)Temp = Temp->pNext;
		//запоминаем адрес куда удаляемого элемента
		Element<T>* Erased = Temp->pNext;
		//исключаем из списка
		Temp->pNext = Temp->pNext->pNext;//Erased->pNext
		//удаляем элемент из памяти
		delete Erased;
		size--;
	}
	void insert(int index, T Data)
	{
		if (index == 0 || Head == nullptr)return push_front(Data);
		if (index > size)return;
		//Element* New = new Element(Data);
		//Доходим до нужного элемента
		Element<T>* Temp = Head;
		for (int i{ 0 }; i < index - 1; ++i)Temp = Temp->pNext;
		//Включаем новый элемент в список:
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;
		Temp->pNext = new Element<T>(Data, Temp->pNext);
		size++;
	}
	//Methods
	void print()const
	{
#if OLD_PRINT
		Element* Temp = Head;//Temp - итератор 
//Итератор - указатель при помощи которого можно получить доступ к элементам структуры данных
		while (Temp)//пока итератор содержит ненулеовой адрес
		{
			std::cout << Temp << tab << Temp->Data << tab
				<< Temp->pNext << std::endl;
			Temp = Temp->pNext;//переход на следующий элемент
		}
#endif // OLD_PRINT

		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		//for (Element* Temp = Head; Temp; Temp++)
			std::cout << Temp << tab << Temp->Data << tab << Temp->pNext << std::endl;
		std::cout << "Количество элементов списка: " << size << std::endl;
		std::cout << "Общее количество элементов списка: " << Head->count << std::endl;
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
	int n; cout << "Введите размер списка: "; cin >> n;
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
	cout << "Введите индекc добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;

	list.insert(index, value);
	list.print();

	cout << "Введите индекс удаляемого элемента: "; cin >> index;
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
	std::cout << "Введите размер списка: "; std::cin >> n;
	ForwardList list;
	for (int i = 0; i < n; ++i)
	{
		list.push_front(rand());
	}
	//std::cout << "Список заполнен" << std::endl;
	list.print();
#endif // DESTRUCTOR_CHECK

#ifdef HOME_WORK1
	int n;
	cout << "Введите размер списка: "; cin >> n;
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
	ForwardList list = { 3,5,8,13,21 };//неявно создает объект класса initializer_list
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

	for (int i : arr)// range - based for(for для диапазона)
	{
		cout << i << tab;
	}
	cout << endl;
	//под диапазононом понимается контейнер(массив,список)
	// в других языках называется foreach  
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
	value - последовательно принимает значения всех элементов контейнера

	*/

	/*
	* class object;  создание обычного класса
	* class<type> object;  создание шаблонного класса
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