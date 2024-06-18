#include "BTree.cpp"

int main() {
	BTree<int> tree;
	int option = 0;

	do {
		system("cls");

		cout << "Cac tac vu cua cay: " << endl;
		cout << "1.Kiem tra cay rong." << endl;
		cout << "2.Them khoa vao cay." << endl;
		cout << "3.Tim khoa trong cay." << endl;
		cout << "4.Loai bo khoa trong cay" << endl;
		cout << "5.Duyet cay theo thu tu NLR." << endl;
		cout << "6.Huy bo cay." << endl;
		cout << "0.Ket thuc." << endl;
		cout << "Chon tac vu:";
		cin >> option;

		switch (option)
		{
			case 1:
			{
				if (tree.IsEmpty()) {
					cout << "Cay rong ...." << endl;
				}
				else {
					cout << "Cay khac rong" << endl;
				}

				system("pause");
				break;
			}
			case 2:
			{
				int theKey;

				cout << "Nhap khoa them vao: ";
				cin >> theKey;

				tree.Insert(theKey);

				break;
			}
			case 3:
			{
				int theKey;

				cout << "Nhap khoa tim kiem" << endl;
				cin >> theKey;

				bool found = tree.Find(theKey);

				if (found) {
					cout << "Tim thay khoa" << endl;
				}
				else {
					cout << "Khong tim thay khoa" << endl;
				}

				system("pause");
				break;
			}
			case 4:
			{
				int theKey;
				bool error;

				cout << "Nhap khoa loai bo: " << endl;
				cin >> theKey;

				tree.Remove(theKey, error);

				if (error) {
					cout << "Khong co khoa" << endl;
					system("pause");
				}
			}
			case 5:
			{
				if (tree.IsEmpty()) {
					cout << "Cay rong ...." << endl;
				}
				else {
					tree.Display();
				}

				system("pause");
				break;
			}
			case 6:
			{
				tree.Clear();
				break;
			}
		}

	} while (option != 0);

	return 0;
}