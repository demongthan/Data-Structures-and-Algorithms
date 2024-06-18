#include "Node.cpp"

template <class InfoType>
class AVL {
private:
	Node<InfoType>* Root;
private:
	void NLR(Node<InfoType>* p, int n) {
		for (in ti = 1; i <= n; i++)
			cout << " ";

		if (p != NULL) {
			p->Display();
			NLR(p->Left, n + 3);
			NLR(p->Right, n + 3);
		}
		else {
			cout << "0:0" << endl;
		}
	}

	int GetHeight(Node<InfoType>* p) {
		int height;

		if (p == NULL) {
			height = 0;
		}
		else {
			height = p->Height;
		}

		return height;
	}

	void ComputeHeight(Node<InfoType>* p) {
		int hl = GetHeight(p->Left);
		int hr = GetHeight(p->Right);

		if (hl >= hr) {
			p->Height = hl + 1;
		}
		else {
			p->Height = hr + 1;
		}
	}

	void SingleWithLeftChild(Node<InfoType>*& p) {
		Node<InfoType>* q = p->Left;
		p->Left = q->Right;
		q->Right = p;
		ComputeHeight(p);
		ComputeHeight(q);
		p = q;
	}

	void DoubleWithLeftChild(Node<InfoType>*& p) {
		Node<InfoType>* q = p->Left;
		Node<InfoType>* r = q->Right;

		q->Right = r->Left;
		p->Left = r->Right;
		r->Left = q;
		r->Right = p;
		ComputeHeight(p);
		ComputeHeight(q);
		ComputeHeight(r);
		p = r;
	}

	void RotateWithLeftChild(Node<InfoType>*& p) {
		Node<InfoType>* q = p->Left;

		if (GetHeight(q->Left) >= GetHeight(q->Right)) {
			SingleWithLeftChild(p);
		}
		else {
			DoubleWithLeftChild(p);
		}
	}

	void SingleWithRightChild(Node<InfoType>*& p) {
		Node<InfoType>* q = p->Right;

		p->Right = q->Left;
		q->Left = p;
		ComputeHeight(p);
		ComputeHeight(q);
		p = q;
	}

	void DoubleWithRightChild(Node<InfoType>*& p) {
		Node<InfoType>& q = p->Right;
		Node<InfoType>* r = q->Left;

		q->Left = r->Right;
		p->Right = r->Left;
		r->Left = p;
		r->Right = q;
		ComputeHeight(q);
		ComputeHeight(p);
		ComputeHeight(r);
		p = r;
	}

	void RotateWithRightChild(Node<InfoType>*& p) {
		Node<InfoType>* q = p->Right;

		if (GetHeight(q->Right) >= GetHeight(p->Left)) {
			SingleWithRightChild(p);
		}
		else {
			DoubleWithRightChild(p);
		}
	}

	void InsertAVL(Node<InfoType>*& p, InfoType theKey) {
		if (p == NULL) {
			p = new Node<InfoType>(theKey);
		}
		else if (theKey < p->Key) {
			InsertAVL(p->Left, theKey);

			if (GetHeight(p->Left) - GetHeight(p->Right) == 2) {
				RotateWithLeftChild(p);
			}

			ComputeHeight(p);
		}
		else if (p->Key == theKey) {
			p->Count = p->Count + 1;
		}
		else {
			InsertAVL(p->Right, theKey);

			if (GetHeight(p->Right) - GetHeight(p->Left) == 2) {
				RotateWithRightChild(p);
			}

			ComputeHeight(p);
		}
	}

	void FindBST(Node<InfoType>* p, InfoType theKey){
		bool found = false;

		while (p!=NULL && !found){
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

	void RemoveRightmostNode(Node<InfoType>*& r, Node<InfoType>*& q) {
		if (r->Right != NULL) {
			RemoveRightmostNode(r->Right, q);
			ComputeHeight(r);
		}
		else {
			q->Key = r->Key;
			q->Count = r->Count;
			q = r;
			r = r->Left;
		}
	}

	void RemoveAVL(Node<InfoType>*& p, InfoType theKey, bool& error) {
		error = true;
		
		if (p != NULL) {
			if (theKey < p->Key) {
				RemoveAVL(p->Left, theKey, error);

				if (GetHeight(p->Right) - GetHeight(p->Left) == 2) {
					RotateWithRightChild(p);
				}

				ComputeHeight(p);
			}
			else if (p->Key == theKey) {
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

					if (GetHeight(p->Right) - GetHeight(p->Left) == 2) {
						RotateWithRightChild(p);
					}

					ComputeHeight(p);
				}

				delete(q);
			}
		}
		else {
			RemoveAVL(p->Right, theKey, error);

			if (GetHeight(p->Left) - GetHeight(p->Right) == 2) {
				RotateWithLeftChild(p);
			}

			ComputeHeight(p);
		}
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

	void IsAVL(Node<InfoType>* p, int& height) {
		bool avl;
		height = 0;

		if (p == NULL) {
			avl = true;
		}
		else {
			int leftHeight = 0;
			int rightHeight = 0;
			avl = IsAVL(p->Left, leftHeight);

			if (avl) {
				avl = IsAVL(p->Right, rightHeight);
			}
			
			if (avl) {
				if ((leftHeight == rightHeight + 2) || (rightHeight == leftHeight + 2)) {
					avl = false;
				}
				else {
					if (leftHeight > rightHeight) {
						height = leftHeight + 1;
					}
					else {
						height = rightHeight + 1;
					}
				}
			}
		}

		return avl;
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
	AVL() {
		Root = NULL;
	}

	bool IsEmpty() {
		return Root == NULL;
	}

	void TraverseNLR() {
		if (IsEmpty()) {
			cout << "Cay rong ...." << endl;
		}
		else {
			cout << "AVL: " << endl;
			NLR(Root, 0);
		}
	}

	void Insert(InfoType theKey) {
		InsertAVL(Root, theKey);
	}

	Node<InfoType>* Find(InfoType theKey) {
		Node<InfoType>* result = FindBST(Root, theKey);
		return result;
	}

	void Remove(InfoType theKey, bool& error) {
		RemoveAVL(Root, theKey, error);
	}

	void Create(InfoType a[]) {
		int i = 0;
		CreateTree(Root, a, i);
	}

	bool IsBalanced() {
		int height;
		return IsAVL(Root, height);
	}

	void Clear() {
		ClearLRN(Root);
	}

	~AVL() {
		Clear();
	}
};