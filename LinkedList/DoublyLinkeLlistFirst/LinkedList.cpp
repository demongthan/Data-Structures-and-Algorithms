#include "Item.cpp"

template <class InfoType>
class LinkedList {
private:
	Item<InfoType>* First;
	Item<InfoType>* Last;
	int Count;
public:
	LinkedList() {
		First = NULL;
		Last = NULL;
		Count = 0;
	}

	bool IsEmpty() {
		return First == NULL;
	}

	void InsertFirst(InfoType theInfo) {
		Item<InfoType>* q = new Item<InfoType>(theInfo);

		if (First != NULL)
			First->Previous = q;
		else
			Last = q;

		q->Next = First;
		First = q;
		Count++;
	}

	void InsertLast(InfoType theInfo) {
		Item<InfoType> q = new Item<InfoType>(theInfo);

		if (Last != NULL)
			Last->Next = q;
		else
			First = q;

		q->Previous = Last;
		Last = q;
		Count++;
	}

	void InsertOrder(InfoType theInfo) {
		bool cont = true;

		Item<InfoType> *p = First;

		while (p != NULL && cont)
			if (p->Info < theInfo)
				p = p->Next;
			else
				cont = false;

		if (p == First)
			InsertFirst(theInfo);
		else {
			if (p == NULL)
				InsertLast(theInfo);
			else {
				Item<InfoType> q = new Item<InfoType>(theInfo);

				Item<InfoType>* tp = p->Previous;
				tp->Next = q;
				q->Previous = tp;
				q->Next = p;
				Count++;
			}
		}

	}

	Item<InfoType>* FindOrder(InfoType theInfo) {
		bool found = false;

		Item<InfoType>* p = First;

		while (p != NULL && !found)
			if (p->Info < theInfo)
				p = p->Next;
			else if (p->Info = theInfo)
				found = true;
			else
				p = NULL;

		return p;
	}

	void RemoveOrder(InfoType theInfo) {
		bool found = false;

		Item<InfoType>* p = First;

		while (p != NULL && !found)
			if (p->Info < theInfo)
				p = p->Next;
			else if (p->Info == theInfo)
				found = true;
			else
				p = NULL;

		if (found) {
			Item<InfoType>* tp = p->Previous;
			Item<InfoType>* sp = p->Next;

			if (tp != NULL)
				tp->Next = sp;
			else
				First = sp;

			if (sp != NULL)
				sp->Previous = tp;
			else
				Last = tp;

			delete p;
			Count--;
		}
	}

	void DisplayNext() {
		if (IsEmpty())
			cout << "Danh sach rong" << endl;
		else
		{
			cout << "Noi dung cua danh sach: " << endl;

			Item<InfoType>* p = First;

			while (p != NULL) {
				p->Display();
				p = p->Next;
			}

			cout << "So phan tu: " << Cout << endl;
		}
	}

	void DisplayPrevious() {
		if (IsEmpty())
			cout << "Danh sach rong" << endl;
		else {
			cout << "Noi dung cua danh sach:" << endl;

			Item<InfoType>* p = Last;

			while (p!=NULL){
				p->Display();
				p = p->Previous;
			}

			cout << "So luong phan tu: " << Count << endl;
		}
	}

	void Clear() {
		Item<InfoType>* p;

		while (First!=NULL){
			p = First;
			First = p->Next;
			delete p;
		}

		Count = 0;
	}

	~LinkedList() {
		Clear();
	}
};