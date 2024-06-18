#include <iostream>
using namespace std;

template <class InfoType>
class Heap {
private:
	InfoType* Arr;
	int Size;
	int Count;

private:
	void Swap(InfoType& x, InfoType& y) {
		InfoType temp = x;
		x = y;
		y = temp;
	}

	void ShiftUp(int i) {
		if (i > 0) {
			int parent = (i - 1) / 2;

			if (Arr[parent] < Arr[i]) {
				Swap(Arr[i], Arr[parent]);
				ShiftUp(parent);
			}
		}
	}

	void ShiftDown(int p, int q) {
		int i = p;
		int theKey = Arr[i];
		int j = 2 * i + 1;
		bool cont = true;

		while (j <= q && cont) {
			if (j < q)
				if (Arr[j] < Arr[j + 1])
					j = j + 1;

			if (theKey < Arr[j]) {
				Arr[i] = Arr[j];
				i = j;
				j = j * 2 + 1;
			}
			else
				cont = false;
		}

		Arr[i] = theKey;
	}

public:
	Heap(int theSize) {
		Arr = new InfoType[theSize];
		Size = theSize;
		Count = 0;
	}

	bool IsEmpty() {
		return Count == 0;
	}

	bool IsFull() {
		return Count == Size;
	}

	void CreateHeapShiftUp() {
		for (int i = 0; i < Count; i++)
			ShiftUp(i);
	}

	void CreateHeapShiftDown() {
		for (int i = 0; i < Count; i++)
			ShiftDown(i);
	}

	void Display() {
		if (IsEmpty())
			cout << "Heap rong." << endl;
		else {
			cout << "Heap: " << endl;

			for (int i = 0; i < Count; i++)
				cout << Arr[i] << "  ";

			cout << endl;
			cout << "So phan tu cua Heap: " << Count << endl;
		}
	}

	void Insert(InfoType theKey, bool& error) {
		if (IsFull())
			error = true;
		else {
			error = false;
			Arr[Count] = theKey;
			ShiftUp(Count);
			Count++;
		}
	}

	InfoType Remove(bool& error) {
		InfoType theKey;

		if (IsEmpty()) {
			error = true;
			theKey = NULL;
		}
		else {
			error = false;
			theKey = Arr[0];
			Arr[0] = Arr[Count - 1];
			Count--;
			CreateHeapShiftUp();
		}

		return theKey;
	}

	void Copy(InfoType a[], int n) {
		delete[] Arr;
		Arr = new InfoType[n];

		for (int i = 0; i < n; i++) {
			Arr[i] = a[i];
		}

		Count = n;
		Size = n;
	}

	InfoType Peek(int k, bool& error) {
		int theKey;

		if (IsEmpty() || k<0 || k>Count) {
			error = true;
			theKey = 0;
		}
		else {
			error = false;
			InfoType* a = new InfoType[Count];
			int n = 0;

			for (int i = 1; i <= k; i++) {
				a[n] = Remove(error);
				n++;
			}

			for (int i = 0; i < n; i++)
				Insert(a[i], error);

			theKey = a[n - 1];
		}

		return theKey;
	}

	void Clear() {
		Size = 0;
		Count = 0;
	}

	~Heap() {
		Clear();
	}
};