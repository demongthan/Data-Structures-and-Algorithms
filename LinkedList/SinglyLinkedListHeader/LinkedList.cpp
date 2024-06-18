#include "Item.cpp"

template <class InfoType>
class LinkedList
{
private:
	Item<InfoType>* Header;
	int Count;

public:
	LinkedList() {
		Header = new Item<InfoType>();
		Header->Next = NULL;
		Count = 0;
	};

	bool IsEmpty() {
		return Header->Next == NULL;
	}

	void InsertFirst(InfoType theInfo) {
		Item<InfoType>* q = new Item<InfoType>(theInfo);

		q->Next = Header->Next;
		Header->Next = q;
		Count++;
	}

	void InsertOrder(InfoType theInfo) {
		bool cont = true;
		Item<InfoType>* tp = Header;
		Item<InfoType>* p = Header->Next;

		while (p != NULL && cont)
			if (p->Info < theInfo) {
				tp = p;
				p = p->Next;
			}
			else
				cont = false;

		Item<InfoType>* q = new Item<InfoType>(theInfo);

		tp->Next = q;
		q->Next = p;
		Count++;
	}

	Item<InfoType>* FindOrder(InfoType theInfo) {
		bool found = false;
		Item<InfoType>* p = Header->Next;

		while (p != NULL && !found)
			if (p->Info < theInfo)
				p = p->Next;
			else if (p->Info == theInfo)
				found = true;
			else
				p = NULL;

		return p;
	}

	void RemoveOrder(InfoType theInfo, bool& error) {
		bool found = false;
		Item<InfoType>* tp = Header;
		Item<InfoType>* p = Header->Next;

		while (p != NULL && !found)
			if (p->Info < theInfo)
			{
				tp = p->Next;
				p = p->Next;
			}
			else
				found = true;

		if (found)
		{
			tp->Next = p->Next;
			delete p;
			Count--;
		}

		error = !found;
	}

	void Display() {
		if (IsEmpty())
			cout << "Danh sach rong" << endl;
		else {
			cout << "Noi dung cua danh sach: " << endl;
			
			Item<InfoType>* p = Header->Next;

			while (p != NULL) {
				p->Display();
				p = p->Next;
			}

			cout << "So phan tu: " << Count << endl;
		}
	}

	void Clear() {
		Item<InfoType>* p;

		while (p != NULL)
		{
			p = Header->Next;
			Header->Next = p->Next;
			delete p;
		}

		Count = 0;
	}

	~LinkedList() {
		Clear();
	}
};