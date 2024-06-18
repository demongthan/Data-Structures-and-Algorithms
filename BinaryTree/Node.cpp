#include <iostream>
using namespace std;

template <class InfoType>
class Node {
public:
	InfoType Info;
	Node<InfoType>* Left;
	Node<InfoType>* Right;
public:
	Node(InfoType theInfo) {
		Info = theInfo;
		Left=NULL:
		Right = NULL;
	}

	void Display() {
		cout << Info << endl;
	}
};