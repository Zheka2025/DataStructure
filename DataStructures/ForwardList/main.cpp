#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;		//Значение элемента
	Element* pNext;	//Адрес следующего элемента
public:
	Element(int Data, Element* pNext = nullptr)
	{
		this->Data = Data;
		this->pNext = pNext;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};

class ForwardList
{
	Element* Head;	//Указатель на начало списка
public:
	ForwardList()
	{
		this->Head = nullptr;
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}

	//			Добавление элементов в список:
	void push_front(int Data)
	{
		//Data - добавляемое значение.
		//1) Создаем элемент, в который можно положить добавляемое значение:
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
	}
	void push_back(int Data)
	{
		
	}

	void print()
	{
		Element* Temp = Head;//Temp - Итератор.
		//Итератор - это указатель, при помощи которого можно получить доступ
		//к элементам структуры данных.
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//Переход на следующий элемент.
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;		//Количество элементов
	cout << "Введите количество элементов: ";
	cin >> n;
	ForwardList fl;
	for (int i = 0; i < n; i++)
	{
		fl.push_front(rand() % 100);
	}
	fl.print();
}