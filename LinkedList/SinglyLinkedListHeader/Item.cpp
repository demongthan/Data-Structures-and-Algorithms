#include <iostream>
using namespace std;

template <class InfoType>
class Item 
{
public:
	InfoType theInfo;
	Item<InfoType>* Next;

public:
	Item(InfoType theInfo)
	{
		Info = theInfo;
		Next = NULL;
	}

	Item();

	void Display()
	{
		cout << Info << endl;
	}
};