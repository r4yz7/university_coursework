
#include <iostream>
#include "CompanyShop.h"
using namespace std;
int main()
{
	CompanyShop shop;
	bool menu = false;
	do
	{
		system("cls");
		int choice;
		cout << "1 - Create account\n2 - Sign in\n3 - Exit\nChoice: ";
		cin >> choice;
		switch (choice)
		{
		case 1: {
			shop.createAccount();
		}
		case 2: {
			shop.login();
		}break;
		case 3: {
			exit(0);
		}break;
		default:
			break;
		}
	} while (menu!=true);
}

