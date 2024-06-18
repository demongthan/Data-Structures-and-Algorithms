#include <iostream>
using namespace std;

template <class InfoType>
class Stack {
private:
	InfoType* StatckArray;
	int Sp;
	int Size;
	int Count;
public:
	Stack(int theSize) {
		StatckArray = new InfoType(theSize);
		Sp = -1;
		Size = theSize;
		Count = 0;
	}

	bool IsEmpty() {
		return Sp == -1;
	}

	bool IsFull() {
		return Sp == Size;
	}

	void Peek(InfoType theInfo, bool& error) {
		InfoType result;

		if (IsEmpty()) {
			error = true;
			result = 0;
		}
		else {
			error = false;
			result = StatckArray[sp];
		}

		return result;
	}

	InfoType Push(InfoType theInfo,bool& error) {
		if (IsFull())
			error = true;
		else {
			error = false;
			Sp++;
			StatckArray[Sp] = theInfo;
			Count++;
		}
	}

	InfoType Pop(bool& error) {
		InfoType result;

		if (IsEmpty()) {
			error = true;
			result = 0;
		}
		else {
			error = false;
			result = StatckArray[Sp];
			Sp--;
			Count--;
		}
	}

	void Display() {
		if (IsEmpty())
			cout << "Stack rong" << endl;
		else {
			cout << "Noi dung cua Stack:" << endl;

			for (int i = Sp; i >= 0; i--)
				cout << StatckArray[i] << endl;
			
			cout << "So phan tu hien tai: " << Count << endl;
			cout << "So phan tu toi da : " << Size << endl;
		}
	}

	void Clear() {
		Sp = -1;
		Count = 0;
	}

	~Stack() {
		delete[] StatckArray;
		Sp = -1;
		Count = 0;
	}
};