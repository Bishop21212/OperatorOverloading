//BinaryTree
#include<iostream>
using std::cout;
using std::endl;
using std::cin;

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pRight;
		Element* pLeft;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) : Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructors:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}

		bool is_Leaf()const
		{
			return pLeft == pRight;
		}

		friend class Tree;
		friend class UniqueTree;
	}*Root;
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		this->Root = nullptr;// ������ ������
		cout << "TConstructor:\t" << this << endl;
	}
	Tree(const std::initializer_list<int>& il) : Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			insert(*it, Root);
		}
	}
	Tree(const Tree& other) : Tree()
	{
		copy(other.Root);
		cout << "CopyConstructor:\t" << this << endl;
	}
	~Tree()
	{
		clear();
		cout << "TDestructor:\t" << this << endl;
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	void clear()
	{
		clear(Root);
		Root = nullptr;
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int size()const
	{
		return size(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	double Avg()const
	{
		return (double)sum(Root) / size(Root);
	}
	void print()const
	{
		 print(Root);
		 cout << endl;
	}
private:
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			return;
		}
		if (Root == nullptr)return;//������� ������ �� ��������
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void erase(int Data, Element*&  Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->is_Leaf())
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (size(Root->pLeft) > size(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}

	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
	void copy(Element* Root)
	{
		if (Root == nullptr)return;
		insert(Root->Data, this->Root);
		copy(Root->pLeft);
		copy(Root->pRight);
	}
	int minValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
		//else if (Root->pLeft == nullptr)return Root->Data;
		//else return minValue(Root->pLeft);
		//return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
		return Root->pLeft ? minValue(Root->pLeft) : Root->Data;
	}
	int maxValue(Element* Root)const
	{
		if (Root == nullptr)return 0;
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;

	}
	int size(Element* Root)const
	{
		return !Root ? 0 : size(Root->pLeft) + size(Root->pRight) + 1;
	}
	int sum(Element* Root)const
	{
		return Root == nullptr ? 0 : sum(Root->pLeft) + sum(Root->pRight) + Root->Data;
	}

	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << "\t";
		print(Root->pRight);
	}
};

class UniqueTree : public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)
		{
			this->Root = new Element(Data);
			return;
		}
		if (Root == nullptr)return;//������� ������ �� ��������
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if(Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, this->Root);
	}
};

//#define BASE_CHECK
int main()
{
	using namespace std;
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	cout << typeid(nullptr).name() << endl;
	int n;
	cout << "������� ������ ������: "; cin >> n;
	UniqueTree tree;
	for (int i = 0; i < n; ++i)
	{
		tree.insert(rand() % 100);
	}
	/*tree.clear();*/
	tree.print();//�������� ������ �� �����������, ��� ���������� ��������������
	cout << endl;
	cout << "MinValue Tree: " << tree.minValue() << endl;
	cout << "MaxValue Tree: " << tree.maxValue() << endl;
	cout << "Value Element Size " << tree.size() << endl;
	cout << "Sum Element Tree : " << tree.sum() << endl;
	cout << "Avg Element Tree: " << tree.Avg() << endl;
#endif // BASE_CHECK

	Tree tree = { 50,25,75,16,32,64,80,27,35};
	tree.print();
	/*Tree tree2 = tree;
	tree2.print();*/
	int value;
	cout << "������� ��������� �������� "; cin >> value;
	tree.erase(value);
	tree.print();
}