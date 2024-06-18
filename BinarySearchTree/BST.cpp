#include "Node.cpp"

template <class InfoType>
class BST {
private:
	Node<InfoType>* Root;
public:
	BST() {
		Root = NULL;
	}

	bool IsEmpty() {
		return Root == NULL;
	}

	void TraverseNLR(Node<InfoType>* p, int n) {
		for (int i = 1; i < n; i++) {
			cout << " ";
		}

		if (p != NULL) {
			p->Display();
			TraverseNLR(p->Left);
			TraverseNLR(p->Right);
		}
		else
			cout << "0" << endl;
	}

	void Traverse() {
		if (IsEmpty()) {
			cout << "Cay rong ...." << endl;
		}
		else {
			cout << "Cay nhi phan tim kiem: " << endl;
			TraverseNLR(Root, 0);
		}
	}

	void InsertBST(Node<InfoType>*& p, InfoType theKey) {
		if (p == NULL) {
			p = new Node<InfoType>(theKey);
		}
		else if (theKey < p->Key) {
			InsertBST(p->Left, theKey);
		}
		else if (theKey == p->Key) {
			p->Count = p->Count = 1;
		}
		else {
			InsertBST(p->Right, theKey);
		}
	}

	Node<InfoType>* FindBST(Node<InfoType>* p, InfoType theKey) {
		Node<InfoType>* result;

		if (p == NULL) {
			result = NULL;
		}
		else {
			if (theKey < p->Key) {
				result = FindBST(p->Left, theKey);
			}
			else if (p->Key == theKey) {
				result = p;
			}
			else {
				result = FindBST(p->Right, theKey);
			}
		}

		return result;
	}

	Node<InfoType>* Find(InfoType theKey) {
		return FindBST(theKey);
	}

	void RemoveRightmostNode(Node<InfoType>*& r, Node<InfoType>*& q) {
		if (r->Right != NULL) {
			RemoveRightmostNode(r->Right, q);
		}
		else {
			q->Key = r->Key;
			q->Count = r->Count;
			q = r;
			r->Left;
		}
	}

	void RemoveBST(Node<InfoType>*& p, InfoType theKey, bool& error) {
		error = true;

		if (p != NULL) {
			if (theKey < p->Key) {
				RemoveBST(p->Left, theKey, error);
			}
			else if (theKey > p->Key) {
				RemoveBST(p->Right, theKey, error);
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

	void Remove(InfoType theKey, bool& error) {
		RemoveBST(Root, theKey, error);
	}

	void CreateTree(Node<InfoType>*& p, InfoType a[], int& i) {
		if (a[i] == 0) {
			p = NULL;
		}
		else {
			p = new Node<InfoType>(a[i]);
			i++;
			CreateTree(p->Left, a, i);
			i++;
			CreateTree(p->Right, a, i);
		}
	}

	void Create(InfoType a[]) {
		int i = 0;
		CreateTree(Root, a, i);
	}

	bool IsBSTTree(Node<InfoType>* p, InfoType& key, bool& firstTime) {
		bool isBST = true;

		if (p != NULL) {
			isBST = IsBSTTree(p->Left, key, firstTime);

			if (isBST) {
				if (firstTime) {
					firstTime = false;
				}
				else if (key >= p->Key) {
					isBST = false;
				}

				key = p->Key;
			}

			if (isBST) {
				isBST = IsBSTTree(p->Right, key, firstTime);
			}
		}

		return isBST;
	}

	bool IsBST() {
		int key = 0;
		bool firstTime = true;
		bool isBST = IsBSTTree(Root, key, firstTime);
		return IsBST;
	}

	void ClearLRN(Node<InfoType>*& p) {
		if (p != NULL) {
			ClearLRN(p->Left);
			ClearLRN(p->Right);
			delete p;
			p = NULL;
		}
	}

	void Clear() {
		ClearLRN(Root);
	}

	~BST() {
		Clear();
	}
};