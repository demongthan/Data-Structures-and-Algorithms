#include <iostream>
using namespace std;

template <class InfoType>
class Node {
public:
	InfoType Key;
	int Height;
	int Count;
	Node<InfoType>* Left;
	Node<InfoType>* Right;
public:
	Node(InfoType theInfo) {
		Key = theInfo;
		Height = 1;
		Count = 1;
		Left = NULL;
		Right = NULL;
	}

	void Display() {
		cout << Key << ":" << Height << endl;
	}
};