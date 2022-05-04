#pragma once
//List2Separation
#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
/////////////////////////////////////////////////////////////////
///////// ќбъ€вление класса - class declaration//////////////////
/////////////////////////////////////////////////////////////////

template<typename T>
class List
{
	class Element
	{
		T Data;//значение элемента
		Element* pNext;//адрес следующего элемента
		Element* pPrev;//адрес предыдущего элемента
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List<T>;
	}*Head, * Tail;
	size_t size;//unsigned int 

	class BaseIterator
	{
	protected://ќткрываем пр€мой доступ к перменной Temp из дочерних классов
		Element* Temp;
	public:
		BaseIterator(Element* Temp = nullptr);
		~BaseIterator();

		virtual BaseIterator& operator++() = 0;
		//virtual BaseIterator operator++(int) = 0;
		virtual BaseIterator& operator--() = 0;
		//virtual BaseIterator operator--(int) = 0;

		bool operator==(const BaseIterator& other)const;
		bool operator!=(const BaseIterator& other)const;
		const T& operator*()const;
		operator bool()const;
	};
	/*Element* Head;
	Element* Tail;
	uint32_t size;*/
public:
	class ConstIterator : public BaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class ConstReverseIterator :public BaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr);
		~ConstReverseIterator();

		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};

	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr);
		~Iterator();
		T& operator*();
	};
	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr);
		~ReverseIterator();
		T& operator*();
	};

	ConstIterator cbegin()const;
	ConstIterator cend()const;
	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;

	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();

	List();
	List(const std::initializer_list<T>& il);
	~List();

	//Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(int index, T Data);
	//Removign elements
	void pop_front();
	void pop_back();
	//Methods
	void print()const;
	void reverse_print()const;
};