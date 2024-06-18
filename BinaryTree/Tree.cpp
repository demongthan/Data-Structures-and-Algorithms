#include "Node.cpp"

template <class InfoType>
class Tree {
private:
	Node<InfoType>* Root;
public:
	Tree() {
		Root = NULL;
	}

	bool IsEmpty() {
		Root == NULL;
	}

	void NLR(Node<InfoType>* p, int n) {
		for (int i = 1; i <= n; i++)
			cout << "";

		if (p != NULL) {
			p->Display();
			NLR(p->Left, n + 3);
			NLR(p->Right, n + 3);
		}
		else
			cout << "0" << endl;
	}

	void TraverseNLR() {
		NLR(Root, 0);
	}

	void LNR(Node<InfoType>* p) {
		if (p != NULL) {
			LNR(p->Left);
			p->Display();
			LNR(p->Right);
		}
	}

	void TraverseLNR() {
		LNR(Root);
	}

	void LRN(Node<InfoType>* p) {
		if (p != NULL) {
			LRN(p->Left);
			LRN(p->Right);
			p->Display();
		}
	}

	void TraverseLRN() {
		LRN(Root);
	}

	void CreateTreeNLR(InfoType a[], int& i) {
		Node<InfoType>* p;
		if (a[i] == 0) {
			p = NULL;
		}
		else {
			p = new Node<InfoType>(a[i]);
			i++;
			p->Left = CreateTreeNLR(a[i], i);
			i++;
			p->Right = CreateTreeNLR(a[i], i);
		}

		return p;
	}

	void CreateTree(InfoType a[]) {
		int i = 0;
		CreateTreeNLR(a[], i);
	}

	int ComputeHeightOfTree(Node<InfoType>* p) {
		int height;

		if (p == NULL) {
			height = 0;
		}
		else {
			int leftHeight = ComputeHeightOfTree(p->Left);
			int rightHeight = ComputeHeightOfTree(p->Right);

			if (leftHeight > rightHeight) {
				height = leftHeight + 1;
			}
			else {
				height = rightHeight + 1;
			}
		}

		return height;
	}

	int ComputeHeight() {
		return ComputeHeightOfTree(Root);
	}

	int ComputeNumberOfNodes(Node<InfoType>* p) {
		int n;

		if (p == NULL) {
			n = 0;
		}
		else {
			n = ComputeNumberOfNodes(p->Left) + ComputeNumberOfNodes(p->Right) + 1;
		}

		return n;
	}

	int ComputeNodes() {
		return ComputeNumberOfNodes(Root);
	}

	int ComputeNumberOfLeaves(Node<InfoType>* p){
		int n;

		if (p == NULL) {
			n = 0;
		}
		else if (p->Left == NULL && p->Right == NULL) {
			n = 1;
		}
		else {
			n = ComputeNumberOfLeaves(p->Left) + ComputeNumberOfLeaves(p->Right);
		}

		return n;
	}

	int ComputeLeaves() {
		int n = 0;

		if (Root != NULL) {
			if (Root->Left != NULL || Root->Right != NULL)
				n = ComputeNumberOfLeaves(Root);
		}

		return n;
	}

	int ComputeNUmberOfInteriors(Node<InfoType>* p) {
		int n;

		if (p == NULL) {
			n = 0;
		}
		else if (p->Left == NULL && p->Right == NULL) {
			n = 0;
		}
		else {
			n = ComputeNUmberOfInteriors(p->Left) + ComputeNUmberOfInteriors(p->Right);
		}
	}

	int ComputeInteriors() {
		int n = ComputeNUmberOfInteriors(n);
		return n > 0 ? n-- : n;
	}

	void TraverseLevels() {
		if (IsEmpty()) {

		}
	}
};