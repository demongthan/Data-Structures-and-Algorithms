#include <iostream>
using namespace std;

template <class InfoType>
class Item {
public:
	InfoType Info;
	Item<InfoType>* Next;
	Item<InfoType>* Previous;
public:
	Item<InfoType>(){}

	Item<InfoType>(InfoType theInfo) {
		Info = theInfo;
	}

	void Display() {
		cout << Info << endl;
	}
};