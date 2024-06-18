#include "Node.cpp"

template <class InfoType>
class HashTable {
private:
	Node<InfoType>** Arr;
	int M;
private:
	Node<InfoType> FindBST(Node<InfoType>* p, InfoType theKey) {
		bool found = false;

		while (p != NULL && !found) {
			if (theKey < p->Key) {
				p = p->Left;
			}
			else if (theKey == p->Key) {
				found = true;
			}
			else {
				p = p->Right;
			}
		}

		return p;
	}

	int HashFunc(InfoType theKey) {
		return theKey % M;
	}

	void InsertBST(Node<InfoType>* p, InfoType theKey) {
		if (p == NULL) {
			p = new Node<InfoType>(theKey);
		}
		else {
			if (theKey<p>Key) {
				InsertBST(p->Left, theKey)
			}
			else if (p->Key == theKey) {
				p->Count++;
			}
			else {
				InsertBST(p->Right, theKey);
			}
		}
	}

	void RemoveRightmostNode(Node<InfoType>*& r, Node<InfoType>*& q) {
		if (r->Right != NULL) {
			RemoveRightmostNode(r->Right, q);
		}
		else {
			q->Key = r->Key;
			q->Count = r->Count;
			q = r;
			r = r->Left;
		}
	}

	void RemoveBST(Node<InfoType>*& p, InfoType theKey, bool& error) {
		error = true;

		if (p != NULL) {
			if (theKey < p->Key) {
				RemoveRightmostNode(p->Left, theKey, error);
			}
			else if (theKey > p->Key) {
				RemoveRightmostNode(p->Right, theKey, error);
			}
			else {
				error = false;
				Node<InfoType>* q = p;
				
				if (p->Left == NULL && p->Right == NULL) {
					p = NULL;
				}
				else if (p->Left != NULL && p->Right == NULL) {
					p = p->Left;
				}
				else if (p->Left == NULL && p->Right != NULL) {
					p = p->Right;
				}
				else {
					RemoveRightmostNode(p->Left, q);
				}

				delete q;
			}
		}
	}

	void TraverseLNR(Node<InfoType>* p) {
		if (p != NULL) {
			TraverseLNR(p->Left);
			p->Display();
			TraverseLNR(p->Right);
		}
	}

	void ClearLRN(Node<InfoType>*& p) {
		if (p != NULL) {
			ClearLRN(p->Left);
			ClearLRN(p->Right);
			delete p;
			p = NULL;
		}
	}
public:
	HashTable(int m) {
		M = m;
		Arr = new Node<InfoType>*[M];
		
		for (int i = 0; i < M; i++) {
			Arr[i] = NULL;
		}
	}

	void Display() {
		cout << "Bang bam: " << endl;

		for (int i = 0; i < M; i++) {
			cout << "Phan tu " << i << ":";
			TraverseLNR(Arr[i]);
			cout << endl;
		}
	}

	Node<InfoType>* Find(InfoType theKey) {
		int address = HashFunc(theKey);
		Node<InfoType>* p = FindBST(Arr[address], theKey);

		return p;
	}

	void Insert(InfoType theKey) {
		int address = HashFunc(theKey);
		InsertBST(Arr[address], theKey);
	}

	void Remove(InfoType theKey, bool& error) {
		int address = HashFunc(theKey);
		RemoveBST(Arr[address], theKey, error);
	}

	void Clear() {
		for (int i = 0; i < M; i++) {
			ClearLRN(Arr[i]);
		}
	}

	~HashTable() {
		Clear();
	}
};