#include "Item.cpp"

template <class InfoType>
class LinkedList {
private:
	Item<InfoType>* Header;
	int Count;
public:
	LinkedList() {
		Header = new Item<InfoType>();
		Header->Next = Header;
		Header->Previous = Header;
		Count = 0;
	}

	bool IsEmpty() {
		return Header->Next == Header;
	}

	void InsertFirst(InfoType theInfo) {
		Item<InfoType>* q = new Item<InfoType>(theInfo);

		Item<InfoType>* sq = Header->Next;
		Header->Next = q;
		q->Next = sq;

		sq->Previous = q;
		q->Previous = Header;
		Count++;
	}

	void InsertLast(InfoType theInfo) {
		Item<InfoType>* q = new Item<InfoType>(theInfo);

		Item<InfoType>* tp = Header->Previous;
		tp->Next = q;
		q->Next = Header;

		Header->Previous = q;
		q->Previous = tp;
		Count++;
	}

	void InsertOrder(InfoType theInfo) {
		bool cont = true;
		Item<InfoType>* p = Header->Next;

		while (p != NULL && cont)
			if (p->Info < theInfo)
				p = p->Next;
			else
				cont = true;

		Item<InfoType>* q = new Item<InfoType>(theInfo);
		Item<InfoType>* tp = p->Previous;

		tp->Next = q;
		q->Next = p;

		q->Previous = tp;
		p->Previous = q;

		Count++;
	}

	Item<InfoType>* FindOrder(InfoType theInfo) {
		bool found = false;
		Item<InfoType>* p = Header->Next;

		while (p != Header && !found)
			if (p->Info < theInfo)
				p = p->Next;
			else if (p->Info == theInfo)
				found = true;
			else
				p = Header;

		return p;
	}

	Item<InfoType>* RemoveOrder(InfoType theInfo) {
		bool found = false;
		Item<InfoType>* p = Header->Next;

		while (p != Header && !found)
			if (p->Info < theInfo)
				p = p->Next;
			else if (p->Info == theInfo)
				found = true;
			else
				p = Header;

		if (found) {
			Item<InfoType>* tp = p->Previous;
			Item<InfoType>* sp = p->Next;

			tp->Next = sp;
			sp->Previous = tp;
			delete p;
			Count--;
		}

		error = !found;
	}

	void DisplayNext() {
		if(IsEmpty())
			cout<<""
	}
};