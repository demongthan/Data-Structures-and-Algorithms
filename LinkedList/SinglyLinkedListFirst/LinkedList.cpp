#include<iostream>
using namespace std;

template <class InfoType>
class Item
{
public:
	InfoType Info;

	Item<InfoType>* Next;

public:
	Item(InfoType theInfo);

	void Display();
};

template<class InfoType>
class LinkedList
{
private:
	Item<InfoType>* First;

	int Count;

public:
	LinkedList();

	bool IsEmpty();

	void InsertFirst(InfoType theInfo);

	void InsertOrder(InfoType theInfo);

	Item<InfoType>* FindOrder(InfoType theInfo);

	void RemoveOrder(InfoType theInfo, bool& error);

	void BubbleSort();

	void Display();

	void Clear();

	~LinkedList();

private:
	void Swap(InfoType& x, InfoType& y);
};

template <class InfoType>
LinkedList<InfoType>::LinkedList()
{
	First = NULL;
	Count = 0;
}

template <class InfoType>
bool LinkedList<InfoType>::IsEmpty()
{
	return First == NULL;
}

template <class InfoType>
void LinkedList<InfoType>::InsertFirst(InfoType theInfo)
{
	Item<InfoType>* q = new Item<InfoType>(theInfo);

	q->Next = First;
	First = q;
	Count++;
}

template <class InfoType>
void LinkedList<InfoType>::InsertOrder(InfoType theInfo)
{
	bool cont = true;
	Item<InfoType>* tp=NULL;
	Item<InfoType>* p = First;

	while ((p != NULL) && cont)
		if (p->Info < theInfo)
		{
			tp = p;
			p = p->Next;
		}
		else 
			cont = false;

	Item<InfoType>* q = new Item<InfoType>(theInfo);

	if (First == NULL)
		First = q;
	else
		tp->Next = q;

	q->Next = p;
	Count++;
}

template <class InfoType>
Item<InfoType>* LinkedList<InfoType>::FindOrder(InfoType theInfo)
{
	bool found = false;
	Item<InfoType>* p = First;

	while (p != NULL && !found)
		if (p->Info < theInfo)
			p = p->Next;
		else if (p->Info == theInfo)
			found = true;
		else
			p = NULL;

	return p;
}

template <class InfoType>
void LinkedList<InfoType>::RemoveOrder(InfoType theInfo, bool &error)
{
	bool found = false;
	Item<InfoType>* tp=NULL;
	Item<InfoType>* p = First;

	while (p != NULL && !found)
		if (p->Info < theInfo)
		{
			tp = p;
			p = p->Next;
		}
		else if (p->Info == theInfo)
			found = true;
		else
			p = NULL;

	if (found)
	{
		if (p == First)
			First = p->Next;
		else
			tp->Next = p->Next;

		delete p;
		Count--;
	}

	error = !found;
}

template <class InfoType>
void LinkedList<InfoType>::Swap(InfoType& x, InfoType& y)
{
	InfoType temp = x;
	x = y;
	y = temp;
}

template <class InfoType>
void LinkedList<InfoType>::BubbleSort()
{
	Item<InfoType>* end = NULL;
	Item<InfoType>* last = NULL;
	bool flag = true;

	while (flag)
	{
		flag = false;
		Item<InfoType>* p = First;

		while (p != end)
		{
			Item<InfoType>* q = p->Next;

			if (q != end)
				if (p->Info > q->Info)
				{
					flag = true;

					Swap(p->Info, q->Info);
					last = q;
				}
			
			p = q;
		}
		end = last;
	}
}

template <class InfoType>
void LinkedList<InfoType>::Display()
{
	if (IsEmpty())
		cout << "Danh sach rong" << endl;
	else
	{
		cout << "Noi dung cua danh sach: " << endl;

		Item<InfoType>* p = First;

		while (p!=NULL)
		{
			p->Display(); 
			p = p->Next;
		}

		cout << "So phan tu: " << Count << endl;
	}
}

template <class InfoType>
void LinkedList<InfoType>::Clear()
{
	Item<InfoType>* p;

	while (First!=NULL)
	{
		p = First;
		First = p->Next;
		delete p;
	}

	Count = 0;
}

template <class InfoType>
LinkedList<InfoType>::~LinkedList()
{
	Clear();
}

int main()
{
	LinkedList<int> lkList;

	int option = 0;

	do
	{
		system("cls");

		cout << "Cac thao tac cua danh sach: " << endl;
		cout << "1. Kiem tra danh sach rong." << endl;
		cout << "2.Them khoa vao danh sach." << endl;
		cout << "3.Tim khoa trong danh sach." << endl;
		cout << "4.Loai bo khoa trong danh sach." << endl;
		cout << "5.Sap thu tu danh sach." << endl;
		cout << "6.Hien thi danh sach." << endl;
		cout << "7.Huy bo danh sach" << endl;
		cout << "0.Ket thuc" << endl;
		cout << "Chon tac vu: ";
		cin >> option;

		switch (option)
		{
		case 1:
		{
			if (lkList.IsEmpty())
				cout << "Danh sach rong ..." << endl;
			else
				cout << "Danh sach khac rong ..." << endl;

			system("pause");
			break;
		}
		case 2:
		{
			int theInfo;

			cout << "Nhap khoa them vao: ";
			cin >> theInfo;

			lkList.InsertOrder(theInfo);

			break;
		}
		case 3:
		{
			int theInfo;

			cout << "Nhap khoa tim kiem: ";
			cin >> theInfo;

			Item<int>* p = lkList.FindOrder(theInfo);

			if (p != NULL)
				cout << "Tim thay " << p->Info << endl;
			else
				cout << "Khong tim thay " << theInfo << endl;

			system("pause");
			break;
		}
		case 4:
		{
			int theInfo;
			bool error;

			cout << "Nhap khoa can loai bo: ";
			cin >> theInfo;

			lkList.RemoveOrder(theInfo, error);

			if (error)
			{
				cout << "Khong co " << theInfo << endl;
				system("pause");
			}
		}
		case 5:
		{
			lkList.BubbleSort();
			break;
		}
		case 6:
		{
			lkList.Display();
			system("pause");
		}
		case 7:
		{
			lkList.Clear();
			break;
		}
		default:
			break;
		}


	} while (option != 0);

	return 0;
}