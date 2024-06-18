#include <iostream>
using namespace std;

template <class InfoType>
class Page;

const int M = 5;
const int M2 = M / 2;

template <class InfoType>
class Item {
public:
	InfoType Key;
	Page<InfoType>* Next;
public:
	Item() {
	}

	Item(InfoType theKey) {
		Key = theKey;
		Next = NULL;
	}
};

template <class InfoType>
class Page {
public:
	Item<InfoType> KeyItem[M];
	Page<InfoType>* P0;
	int KeyNum;
public:
	Page() {
		KeyNum = 0;
		P0 = NULL;

		for (int i = 0; i < M; i++) {
			KeyItem[i].Next = NULL;
		}
	}

	Page(InfoType theKey) {
		KeyItem[0].Key = theKey;
		KeyNum = 1;
		P0 = NULL;

		for (int i = 0; i < M; i++) {
			KeyItem[i].Next = NULL;
		}
	}

	void Display() {
		for (int i = 0; i < KeyNum; i++) {
			cout << KeyItem[i].Key << " ";
		}
		cout << endl;
	}
};