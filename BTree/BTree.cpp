#include "Item.cpp"

template <class InfoType>
class BTree {
private:
	Page<InfoType>* Root;
public:
	BTree() {
		Root = NULL;
	}

	bool IsEmpty() {
		return Root == NULL;
	}

	bool Find(InfoType theKey) {
		bool found;
		int pos;
		FindTree(Root, theKey, found, pos);
		return found;
	}

	void Insert(InfoType theKey) {
		if (Root == NULL) {
			Root = new Page<InfoType>(theKey);
		}
		else {
			bool overflow;
			InfoType overflowKey;
			Page<InfoType>* overflowPage;

			InsertBTree(Root, theKey, overflow, overflowKey, overflowPage);
		}
	}

	void Remove(InfoType theKey, bool& error) {
		Page<InfoType>* parent = NULL;
		int pos = -2;

		RemoveBTree(Root, theKey, parent, pos, error);
	}

	void Display() {
		if (Root == NULL) {
			cout << "Cay rong ...." << endl;
		}
		else {
			DisplayTree(Root, 0);
		}
	}

	void Clear() {
		ClearLRN(Root);
	}

	~BTree() {
		Clear();
	}
private:
	void FindPage(Page<InfoType>* p, InfoType theKey, bool& found, int& pos) {
		found = false;
		int i = 0;
		int j = p->KeyNum - 1;
		int k = 0;

		while (i <= j && !found) {
			int k = (i + j) / 2;

			if (theKey < p->KeyItem[k].Key) {
				j = k - 1;
			}
			else if (theKey == p->KeyItem[k].Key) {
				found = true;
			}
			else {
				i = k + 1;
			}
		}

		if (found) {
			pos = k;
		}
		else {
			pos = j;
		}
	}

	void FindTree(Page<InfoType>* p, InfoType theKey, bool& found, int& pos) {
		if (p != NULL) {
			found = false;
			pos = -1;
		}
		else {
			FindPage(p, theKey, found, pos);

			if (!found) {
				if (pos == -1) {
					FindTree(p->P0, theKey, found, pos);
				}
				else {
					FindTree(p->KeyItem[pos].Next, theKey, found, pos);
				}
			}
		}
	}

	void InsertPage(Page<InfoType>*& p, int pos, InfoType theKey, Page<InfoType>* r, bool& overflow, InfoType& overflowKey, Page<InfoType>*& overflowPage) {
		overflow = false;
		overflowKey = theKey;
		overflowPage = NULL;

		for (int i = p->KeyNum - 1; i > pos; i--) {
			p->KeyItem[i + 1].Key = p->KeyItem[i].Key;
			p->KeyItem[i + 1].Next = p->KeyItem[i].Next;
		}

		p->KeyItem[pos + 1].Key = theKey;
		p->KeyItem[pos + 1].Next = r;
		p->KeyNum++;

		if (p->KeyNum == M) {
			overflow = true;
			overflowKey = p->KeyItem[M2].Key;

			overflowPage = new Page<InfoType>();
			overflowPage->KeyNum = M2;

			int k = 0;
			for (int i = M2 + 1; i < p->KeyNum; i++) {
				overflowPage->KeyItem[k].Key = p->KeyItem[i].Key;
				overflowPage->KeyItem[k].Next = p->KeyItem[i].Next;
				k++;
			}

			overflowPage->P0 = p->KeyItem[M2].Next;
			p->KeyNum = M2;
		}
	}

	void InsertBTree(Page<InfoType>*& p, InfoType theKey, bool& overflow, InfoType& overflowKey, Page<InfoType>*& overflowPage){
		overflowKey = theKey;
		overflowPage = NULL;

		if (p == NULL) {
			overflow = true;
		}
		else {
			overflow = false;
			bool found;
			int pos;

			FindPage(p, theKey, found, pos);

			if (!found) {
				Page<InfoType>* q;

				if (pos == -1) {
					q = p->P0;
				}
				else {
					q = p->KeyItem[pos].Next;
				}

				InsertBTree(q, theKey, overflow, overflowKey, overflowPage);

				if (overflow) {
					int theKey2 = overflowKey;
					Page<InfoType>* r = overflowPage;

					InsertPage(p, pos, theKey2, r, overflow, overflowKey, overflowPage);

					if (overflow) {
						if (p == Root) {
							q = new Page<InfoType>(overflowKey);

							q->P0 = p;
							q->KeyItem[0].Next = overflowPage;
							Root = q;
							overflow = false;
						}
					}
				}
			}
		}
	}

	void RemoveKey(Page<InfoType>* p, int pos) {
		for (int i = pos; i < p->KeyNum; i++) {
			p->KeyItem[i].Key = p->KeyItem[i + 1].Key;
			p->KeyItem[i].Next = p->KeyItem[i + 1].Next;
		}

		p->KeyNum--;
	}

	void MergePage(Page<InfoType>* p, Page<InfoType>* parent, int pos, Page<InfoType>* q) {
		int n = p->KeyNum;
		p->KeyItem[n].Key = parent->KeyItem[pos].Key;
		p->KeyItem[n].Next = q->P0;
		n++;

		for (int i = 0; i < q->KeyNum; i++) {
			p->KeyItem[n + i].Key = q->KeyItem[i].Key;
			p->KeyItem[n + i].Next = q->KeyItem[i].Next;
		}
		p->KeyNum = M - 1;
		
		for (int i = pos; i < parent->KeyNum; i++) {
			parent->KeyItem[i].Key = parent->KeyItem[i + 1].Key;
			parent->KeyItem[i].Next = parent->KeyItem[i + 1].Next;
		}
		parent->KeyNum--;

		if (parent == Root && parent->KeyNum == 0) {
			Root = p;
		}

		delete p;
	}

	void RetrieveRightPage(Page<InfoType>* p, Page<InfoType>* parent, int pos, Page<InfoType>* q) {
		p->KeyItem[p->KeyNum].Key = parent->KeyItem[pos].Key;
		p->KeyItem[p->KeyNum].Next = q->P0;
		p->KeyNum++;

		parent->KeyItem[pos].Key = q->KeyItem[0].Key;
		q->P0 = q->KeyItem[0].Next;

		for (int i = 0; i < q->KeyNum; i++) {
			q->KeyItem[i - 1].Key = q->KeyItem[i].Key;
			q->KeyItem[i - 1].Next = q->KeyItem[i].Next;
		}
		q->KeyNum--;
	}

	void RetrieveLeftPage(Page<InfoType>* p, Page<InfoType>* parent, int pos, Page<InfoType>* q) {
		for (int i = p->KeyNum - 1; i >= 0; i--) {
			p->KeyItem[i + 1].Key = p->KeyItem[i].Key;
			p->KeyItem[i + 1].Next = p->KeyItem[i].Next;
		}

		p->KeyItem[0].Key = parent->KeyItem[pos].Key;
		p->KeyItem[0].Next = p->P0;
		p->P0 = q->KeyItem[q->KeyNum - 1].Next;
		p->KeyNum++;
		parent->KeyItem[pos].Key = q->KeyItem[q->KeyNum - 1].Key;
		q->KeyNum--;
	}

	void UnderflowRightPage(Page<InfoType>* p, Page<InfoType>* parent, int pos) {
		Page<InfoType>* rightPage = parent->KeyItem[pos].Next;

		if (rightPage->KeyNum > M2) {
			RetrieveRightPage(p, parent, pos, rightPage);
		}
		else {
			MergePage(p, parent, pos, rightPage);
		}
	}

	void UnderflowLeftPage(Page<InfoType>*& p, Page<InfoType>* parent, int pos) {
		Page<InfoType>* leftPage = parent->KeyItem[pos - 1].Next;

		if (leftPage->KeyNum > M2) {
			RetrieveLeftPage(p, parent, pos, leftPage);
		}
		else {
			MergePage(leftPage, parent, pos, p);
			p = leftPage; 
		}
	}

	void Underflow(Page<InfoType>*& p, Page<InfoType>* parent, int pos) {
		Page<InfoType>* leftPage;
		Page<InfoType>* rightPage;

		if (pos == -1) {
			leftPage = NULL;
		}
		else if (pos == 0) {
			leftPage = parent->P0;
		}
		else {
			leftPage = parent->KeyItem[pos - 1].Next;
		}

		if (pos == parent->KeyNum - 1) {
			rightPage = NULL;
		}
		else {
			rightPage = parent->KeyItem[pos + 1].Next;
		}

		if (leftPage == NULL) {
			UnderflowRightPage(p, parent, pos + 1);
		}
		else if (rightPage == NULL) {
			UnderflowLeftPage(p, parent, pos);
		}
		else {
			if (rightPage->KeyNum > M2) {
				RetrieveRightPage(p, parent, pos + 1, rightPage);
			}
			else {
				if (leftPage->KeyNum > M2) {
					RetrieveLeftPage(p, parent, pos, leftPage);
				}
				else {
					MergePage(p, parent, pos + 1, rightPage);
				}
			}
		}
	}

	void RemoveRightmostNode(Page<InfoType>*& q, Page<InfoType>* parent, int pos, Item<InfoType>& element) {
		int n = q->KeyNum - 1;

		if (q->KeyItem[n].Next != NULL) {
			RemoveRightmostNode(q->KeyItem[n].Next, q, n, element);

			if (q->KeyNum < M2) {
				Underflow(q, parent, pos);
			}
		}
		else {
			element.Key = q->KeyItem[n].Key;
			q->KeyNum--;

			if (q->KeyNum < M2) {
				Underflow(q, parent, pos);
			}
		}
	}

	void RemoveBTree(Page<InfoType>*& p, InfoType theKey, Page<InfoType>* parent, int pos, bool& error) {
		error = true;
		bool found;
		Page<InfoType>* q;
		int posKey;

		if (p != NULL) {
			FindPage(p, theKey, found, posKey);

			if (found) {
				error = false;

				if (posKey != -1) {
					if (p->P0 == NULL) {
						RemoveKey(p, posKey);

						if (p->KeyNum < M2) {
							if (p == Root) {
								if (p->KeyNum == 0) {
									delete p;
									Root = NULL;
								}
							}
							else {
								Underflow(p, parent, pos);
							}
						}
					}
					else {
						int position;

						if (posKey == 0) {
							q = p->P0;
							position = -1;
						}
						else {
							q = p->KeyItem[posKey - 1].Next;
							position = posKey - 1;
						}

						RemoveRightmostNode(q, p, position, p->KeyItem[posKey]);

						if (p != Root) {
							if (p->KeyNum < M2) {
								Underflow(p, parent, pos);
							}
						}
					}
				}
				else {
					if (p->P0 != NULL) {
						if (posKey == -1) {
							q = p->P0;
						}
						else {
							q = p->KeyItem[posKey].Next;
						}

						RemoveBTree(q, theKey, p, posKey, error);

						if (p != Root) {
							if (p->KeyNum < M2) {
								Underflow(p, parent, pos);
							}
						}
					}
				}
			}
		}
	}

	void DisplayTree(Page<InfoType>* p, int k) {
		for (int i = 1; i <= k; i++) {
			cout << " ";
		}

		cout << "Trang: " << endl;
		p->Display();

		if (p->P0 != NULL) {
			DisplayTree(p->P0, k + 2);
		}

		for (int i = 0; i < p->KeyNum; i++) {
			if (p->KeyItem[i].Next != NULL) {
				DisplayTree(p->KeyItem[i].Next, k + 2);
			}
		}

	}

	void ClearLRN(Page<InfoType>*& p) {
		if (p != NULL) {
			if (p->P0 != NULL) {
				ClearLRN(p->P0);
			}

			for (int i = 0; i < p->KeyNum; i++) {
				if (p->KeyItem[i].Next != NULL) {
					ClearLRN(p->KeyItem[i].Next);
				}

				delete p;
				p = NULL;
			}
		}
	}
};