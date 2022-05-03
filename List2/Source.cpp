//TemplatedList2
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

template<typename T>
class List
{
	class Element
	{
		T Data;//�������� ��������
		Element* pNext;//����� ���������� ��������
		Element* pPrev;//����� ����������� ��������
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :
			Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;

#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class List<T>;
	}*Head, * Tail;
	size_t size;//unsigned int 

	class BaseIterator
	{
	protected://��������� ������ ������ � ��������� Temp �� �������� �������
		Element* Temp;
	public:
		BaseIterator(Element* Temp = nullptr) : Temp(Temp)
		{
#ifdef DEBUG
			cout << "BitConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~BaseIterator()
		{
#ifdef DEBUG
			cout << "BitDestructor:\t" << this << endl;
#endif // DEBUG

		}

		virtual BaseIterator& operator++() = 0;
		//virtual BaseIterator operator++(int) = 0;
		virtual BaseIterator& operator--() = 0;
		//virtual BaseIterator operator--(int) = 0;

		bool operator==(const BaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const BaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		const T& operator*()const
		{
			return Temp->Data;
		}
		operator bool()const
		{
			return Temp;
		}
	};
	/*Element* Head;
	Element* Tail;
	uint32_t size;*/
public:
	class ConstIterator : public BaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :BaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "CItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ConstIterator()
		{
#ifdef DEBUG
			cout << "CItDestructor:\t" << this << endl;
#endif // DEBUG

		}
		ConstIterator& operator++()
		{
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return *this;
		}
		ConstIterator operator++(int)
		{
			ConstIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return old;
		}
		ConstIterator& operator--()
		{
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return *this;
		}
		ConstIterator operator--(int)
		{
			ConstIterator old = *this;//��������� ������ ��������
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return old;
		}
	};
	class ConstReverseIterator :public BaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :BaseIterator(Temp)
		{
#ifdef DEBUG
			cout << "CRItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ConstReverseIterator()
		{
#ifdef DEBUG
			cout << "CRItDestructor:\t" << this << endl;
#endif // DEBUG

		}

		ConstReverseIterator& operator++()
		{
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int)
		{
			ConstReverseIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return old;
		}
		ConstReverseIterator& operator--()
		{
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return old;
		}
	};

	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr) : ConstIterator(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Iterator()
		{
#ifdef DEBUG
			cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG

		}
		T& operator*()
		{
			return BaseIterator::Temp->Data;
		}
	};

	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) : ConstReverseIterator(Temp)
		{
#ifdef DEBUG
			cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~ReverseIterator()
		{
#ifdef DEBUG
			cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG

		}
		T& operator*()
		{
			return BaseIterator::Temp->Data;
		}
	};

	ConstIterator cbegin()const//const begin
	{
		return Head;
	}
	ConstIterator cend()const//const end
	{
		return nullptr;
	}
	ConstReverseIterator crbegin()const//const reverse begin
	{
		return Tail;
	}
	ConstReverseIterator crend()const//const reverse end
	{
		return nullptr;
	}

	Iterator begin()//const begin
	{
		return Head;
	}
	Iterator end()//const end
	{
		return nullptr;
	}
	ReverseIterator rbegin()//const reverse begin
	{
		return Tail;
	}
	ReverseIterator rend()//const reverse end
	{
		return nullptr;
	}

	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<T>& il) :List()
	{
		cout << typeid(il.begin()).name() << endl;
		for (T const* it = il.begin(); it != il.end(); ++it)
		{
			//it - iterator
			push_back(*it);
		}
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}

	//Adding elements:
	void push_front(T Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head->pPrev = New;
		Head = New;*/
		Head = Head->pPrev = new Element(Data, Head);
		size++;
		//Head = Head->pPrev = new Element(Data, Head);
	}
	void push_back(T Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
			size++;
			return;
		}
		/*	Element* New = new Element(Data);
			New->pPrev = Tail;
			Tail->pNext = New;
			Tail = New;*/
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		size++;
	}
	void insert(int index, T Data)
	{
		if (index > size)return;
		if (index == 0)return push_front(Data);
		if (index == size)return push_back(Data);
		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; ++i)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - 1 - index; ++i)Temp = Temp->pPrev;
		}
		//������� � ����� ������� ��������� �� ������� ��������
		//��������� ���������� ������ �������� ����� ����������
		/*Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;*/
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		size++;
	}
	//Removign elements
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			size--;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
		size--;
	}
	void pop_back()
	{
		if (Head == Tail)return pop_front();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	//Methods
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data <<
			tab << Temp->pNext << endl;
		cout << "���������� ��������� ������: " << size << endl;
	}
	void reverse_print()const// ������� ������ ����� �� �����
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data <<
			tab << Temp->pNext << endl;
		cout << "���������� �������� ������: " << size << endl;
	}
};

//#define BASE_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST

int main()
{
	using namespace std;
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "������� ������ ������: "; cin >> n;
	List list;
	for (int i = 0; i < n; ++i)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	//list.pop_front();
	//list.print();
	//list.reverse_print();
	int index;
	int value;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� �������� ������������ ��������: "; cin >> value;
	list.insert(index, value);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

	/*int n;
	unsigned long long int f = 1;
	cout << "������� �����: "; cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		cout << i << "! = ";
		f *= i;
		cout << f << endl;
	}*/

#ifdef RANGE_BASED_FOR_ARRAY
	int arr[]{ 3,5,8,13,21 };//range_base_for
	cout << typeid(arr).name() << endl;
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
		cout << arr[i] << tab;
	cout << endl;

	//	print(arr);

#endif // RANGE_BASED_FOR_ARRAY

#ifdef RANGE_BASED_FOR_LIST
	List<int> list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)
		cout << i << tab;
	cout << endl;
	for (List<int>::ConstReverseIterator it = list.crbegin(); it; it++)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // RANGE_BASED_FOR_LIST

	List<double> d_list = { 2.5,3.14,5.2,8.3 };
	for (double i : d_list)cout << i << tab; cout << endl;
	for (List<double>::ReverseIterator it = d_list.rbegin(); it; ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	List<std::string> s_list = { "Have","a","nice","day" };
	for (std::string i : s_list)cout << i << tab; cout << endl;
	for (List<std::string>::ReverseIterator it = s_list.rbegin(); it != s_list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
}
