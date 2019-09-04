#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

//#define BASE_CHECK
//#define INDEX_OPERATOR_CHECK
//#define CONSTRUCTORS_CHECK

class Element
{
	int Data;		//Значение элемента
	Element* pNext;	//Адрес следующего элемента
	static int count;
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

int Element::count = 0;

class ForwardList
{
	Element* Head;	//Указатель на начало списка
	unsigned int size;
public:
	const int get_size()const
	{
		return this->size;
	}

	Element* begin()
	{
		return Head;
	}

	Element* end()
	{
		return nullptr;
	}

	ForwardList()
	{
		this->Head = nullptr;
		this->size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(int size):ForwardList()
	{
		/*this->Head = nullptr;
		this->size = 0;*/
		while (size--)push_front(0);
	}
	ForwardList(initializer_list<int> il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
			push_back(*it);
	}
	ForwardList(const ForwardList& other):ForwardList()
	{
		for (Element* Temp = other.Head; Temp != nullptr; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LCopyConstruct:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}

	//			Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp != nullptr; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LCopyAssignment:\t" << this << endl;
		return *this;
	}
	int& operator[](int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}

	//			Добавление элементов в список:
	void push_front(int Data)
	{
		//Data - добавляемое значение.
		//1) Создаем элемент, в который можно положить добавляемое значение:
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;*/
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		Element* Temp = Head;
		while (Temp->pNext != nullptr)Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}

	void insert(int index, int data)
	{
		if (index == 0)
		{
			push_front(data);
			return;
		}
		if (index > size)
		{
			cout << "Error: Out of range." << endl;
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		{
			Temp = Temp->pNext;
		}
		/*Element* New = new Element(data);
		New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element(data, Temp->pNext);
		size++;
	}

	//Удаление элементов:
	void pop_front()
	{
		Element* buffer = Head;
		Head = Head->pNext;
		delete buffer;
		size--;
	}

	void pop_back()
	{
		Element* Temp = Head;
		while (Temp->pNext->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
		size--;
	}

	void erase(int index)
	{
		if (index == 0)
		{
			pop_front();
			return;
		}
		if (index >= size)
		{
			cout << "Error: out of range" << endl;
			return;
		}
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)Temp = Temp->pNext;
		Element* buffer = Temp->pNext;

		Temp->pNext = Temp->pNext->pNext;
		delete buffer;
		size--;
	}

	void print()
	{
		//Element* Temp = Head;//Temp - Итератор.
		////Итератор - это указатель, при помощи которого можно получить доступ
		////к элементам структуры данных.
		//while (Temp != nullptr)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;	//Переход на следующий элемент.
		//}

		for(Element* Temp = Head; Temp!= nullptr; Temp = Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементво списка: " << size << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;		//Количество элементов
	//cout << "Введите количество элементов: ";	cin >> n;
#ifdef BASE_CHECK
	ForwardList fl;
	for (int i = 0; i < n; i++)
	{
		fl.push_front(rand() % 100);
	}
	fl.print();
	fl.push_back(123);	fl.print();
	fl.pop_back();	fl.print();

	int index;
	int data;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> data;
	fl.insert(index, data);
	fl.print();

	cout << "Введите индекс удавляемого элемента: "; cin >> index;
	fl.erase(index);
	fl.print();

	/*ForwardList fl2;
	fl2.push_back(3);
	fl2.push_back(5);
	fl2.push_back(8);
	fl2.print();*/
#endif // BASE_CHECK

#ifdef INDEX_OPERATOR_CHECK
	//TODO: exception handling in []
	ForwardList fl(n);
	fl.print();

	cout << int() << endl;
	for (int i = 0; i < fl.get_size(); i++)
	{
		fl[i] = rand() % 100;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << fl[i] << tab;
	}
	cout << endl;
#endif // INDEX_OPERATOR_CHECK

#ifdef CONSTRUCTORS_CHECK
	ForwardList fl = { 3, 5, 8, 13, 21 };
	fl.print();
	fl = fl;
	fl.print();
#endif

	int Arr[] = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < sizeof(Arr) / sizeof(int); i++)
	{
		cout << Arr[i] << tab;
	}
	cout << endl;

	for (int i : Arr)
	{
		cout << i << tab;
	}
	cout << endl;

	char str[] = "Hello";
	for (char i : str)
		cout << i << tab;
	cout << endl;
	ForwardList fl = { 3, 5, 8, 13, 21 };
	for (int i : fl)
	{
		cout << i << tab;
	}
	cout << endl;
}