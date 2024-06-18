#include "Item.cpp"

template <class InfoType>
class Queue {
private:
	Item<InfoType>* Front;
	Item<InfoType>* Rear;
	int Count;
public:
	Queue() {
		Front = NULL;
		Rear = NULL;
		Count = 0;
	}

	bool IsEmpty() {
		return Front == NULL;
	}

	void Enqueue(InfoType theInfo) {
		Item<InfoType>* p = new Item<InfoType>(theInfo);

		if (Front == NULL) {
			Front = p;
		}
		else {
			Rear->Next = p;
		}

		Rear = p;
		Count++;
	}

	void Dequeue(bool& error) {
		InfoType result;

		if (IsEmpty()) {
			error = true;
			result = 0;
		}
		else {
			error = false;

			Item<InfoType>* p = Front;
			result = p->Info;

			if (Front == Rear) {
				Rear == NULL;
			}

			Front = p->Next;
			delete p;
			Count--;
		}
	}

	void Peek(bool& error) {
		InfoType result;

		if (IsEmpty()) {
			error = false;
			result = 0;
		}
		else {
			error = false;
			result = Front->Info;
		}

		return result;
	}

	void Display() {
		if (IsEmpty())
			cout << "Queue rong ...." << endl;
		else {
			cout << "Noi dung cua queue: " << endl;

			Item<InfoType>* p = Front;
			while (p != NULL) {
				p->Display();
				p = p->Next;
			}

			cout << "So luong phan tu: " << Count << endl;
		}
	}

	void Clear() {
		Item<InfoType>* p;

		while (Front != NULL) {
			p = Front;
			Front = p->Next;
			delete p;
		}

		Rear = NULL;
		Count = 0;
	}

	~Queue() {
		Clear();
	}
};