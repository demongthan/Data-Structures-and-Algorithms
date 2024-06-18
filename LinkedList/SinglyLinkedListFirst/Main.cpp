#include "LinkedList.h"

int main()
{
	LinkedList<int> lkList;

	int option = 0;

	do
	{
		system("cls");

		cout << "Cac thao tac cua danh sach: " << endl;
		cout << "1. Kiem tra danh sach rong." << endl;
		cout << "2.Them khoa vao danh sach." << endl;
		cout << "3.Tim khoa trong danh sach." << endl;
		cout << "4.Loai bo khoa trong danh sach." << endl;
		cout << "5.Sap thu tu danh sach." << endl;
		cout << "6.Hien thi danh sach." << endl;
		cout << "7.Huy bo danh sach" << endl;
		cout << "0.Ket thuc" << endl;
		cout << "Chon tac vu: ";
		cin >> option;

		switch (option)
		{
			case 1:
			{
				if (lkList.IsEmpty())
					cout << "Danh sach rong ..." << endl;
				else
					cout << "Danh sach khac rong ..." << endl;

				system("pause");
				break;
			}
			case 2:
			{
				int theInfo;

				cout << "Nhap khoa them vao: ";
				cin >> theInfo;

				lkList.InsertOrder(theInfo);

				break;
			}
			case 3:
			{
				int theInfo;

				cout << "Nhap khoa tim kiem: ";
				cin >> theInfo;

				Item<int>* p = lkList.FindOrder(theInfo);

				if (p != NULL)
					cout << "Tim thay " << p->Info << endl;
				else
					cout << "Khong tim thay " << theInfo << endl;

				system("pause");
				break;
			}
			case 4:
			{
				int theInfo;
				bool error;

				cout << "Nhap khoa can loai bo: ";
				cin >> theInfo;

				lkList.RemoveOrder(theInfo, error);

				if (error)
				{
					cout << "Khong co " << theInfo << endl;
					system("pause");
				}
			}
			case 5:
			{
				lkList.BubbleSort();
				break;
			}
			case 6:
			{
				lkList.Display();
				system("pause");
			}
			case 7:
			{
				lkList.Clear();
				break;
			}
			default:
				break;
		}


	} while (option != 0);

	return 0;
}