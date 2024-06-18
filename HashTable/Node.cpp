#include <iostream>
using namespace std;

template <class InfoType>
class Node {
public:
	InfoType Key;
	int Count;
	Node<InfoType>* Left;
	Node<InfoType>* Right;
public:
	Node(InfoType theInfo) {
		Key = theInfo;
		Count = 1;
		Left = NULL;
		Right = NULL;
	}

	void Display() {
		cout << "(" << Key << "," << Count << ")";
	}
};