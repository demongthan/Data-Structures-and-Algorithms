#include <iostream>
using namespace std;

template <class InfoType>
class Item {
public:
	InfoType Info;
	Item<InfoType>* Next;
	Item<InfoType>* Previous;
public:
	Intem(InfoType theInfo) {
		Info = theInfo;
		Next = NULL;
		Previous = NULL;
	}

	void Display() {
		cout << Info << endl;
	}
};