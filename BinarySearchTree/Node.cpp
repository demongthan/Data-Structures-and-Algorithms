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
	Node(InfoType theKey) {
		Key = theKey;
		Count = 1;
		Left = NULL;
		Right = NULL;
	}

	void Display() {
		cout << Key << endl;
	}
};