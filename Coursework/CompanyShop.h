#pragma once
#include <iostream>
#include "User.h"
#include <vector>
#include <fstream>
#include "Product.h"

using namespace std;
class CompanyShop
{
private:
	vector<User> users;
	vector<Product> products;
	double balance;
public:

	CompanyShop() {
		readUserFromFile("Users.txt");
		readBalanceFromFile("Balance.txt");
		readProductsFromFile("Products.txt");
	}

	void login() {
		system("cls");
		User currentUser;
		string username, password;
		cout << "Enter username: ";
		cin >> username;
		cout << "Enter password: ";
		cin >> password;
		bool isLogged = false;

		for (size_t i = 0; i < users.size(); i++) {
			if (users[i].getUsername() == username && users[i].getPassword() == password) {
				currentUser = users[i];
				isLogged = true;
				break;
			}
		}
		if (!isLogged) {
			cout << "Invalid username or password.\n";
			system("pause");
		}
		else {
			if (currentUser.getRole()) {
				adminPanel(currentUser);
			}
			else {
				userPanel(currentUser);
			}
		}
	}

	void adminPanel(User currentUser) {
		bool menu=true;
		do
		{
			system("cls");
			cout << currentUser.getUsername() << "(" << (currentUser.getRole() ? "admin" : "user") << ")\n\n\n";
			cout << "0) Exit\n1) Users\n2) Check balance\n3) Products\n";
			cout << "Choice: ";
			int choice;
			cin >> choice;
			switch (choice)
			{
			case 0: {
				menu = false;
			}break;
			case 1: {
				bool userList = true;
				do
				{
					system("cls");
					for (size_t i = 0; i < users.size(); i++)
					{
						cout << i << ") ";
						users[i].printUser();
					}
					cout << endl << "0 - Back\n1 - Change role\nChoice: ";
					int temp;
					cin >> temp;
					switch (temp)
					{
					case 0: {
						userList = false;
					}break;
					case 1: {
						int n;
						cout << "Enter the user number for whom you want to change the role: ";
						cin >> n;
						if (n >= 0 && n < users.size()) {
							User& user = users[n];
							user.toggleRole();
							cout << "Role changed successfully!" << endl;
							writeUsersToFile("Users.txt");
						}
						else {
							cout << "Invalid user number!" << endl;
						}
					}
					default:
						break;
					}
				} while (userList);
			}break;
			case 2: {
				bool bal = true;
				do
				{
					system("cls");
					cout << "Balance: " << balance << " UAH\n";
					cout << endl << "0 - Back\n1 - Top up balance\n2 - Withdraw money from balance\nChoice: ";
					int temp;
					cin >> temp;
					switch (temp)
					{
					case 0: {
						bal = false;
					}break;
					case 1: {
						double t;
						cout << "Enter amount: ";
						cin >> t;
						balance += t;
						writeBalanceToFile("Balance.txt");
					}break;
					case 2: {
						double t;
						cout << "Enter amount: ";
						cin >> t;
						balance -= t;
						writeBalanceToFile("Balance.txt");
					}break;
					default:
						break;
					}
				} while (bal);
			}break;
			case 3: {
				bool prodList = true;
				do
				{
					system("cls");
					for (size_t i = 0; i < products.size(); i++)
					{
						cout << i << ") ";
						products[i].printInfo();
					}
					cout << endl << "0 - Back\n1 - Replenish stock\n2 - Add product\nChoice: ";
					int temp;
					cin >> temp;
					switch (temp)
					{
					case 0: {
						prodList = false;
					}break;
					case 1: {
						int n;
						cout << "Enter the ID of the product you want to purchase: ";
						cin >> n;
						if (n >= 0 && n < products.size()) {
							Product& product = products[n];
							cout << "Enter how many units you want to purchase: ";
							int c;
							cin >> c;
							product.restock(c, product.getPurchasePrice());
							balance = balance - (c * product.getPurchasePrice());
							cout << "Product purchased" << endl;
							writeProductToFile("Products.txt");
							writeBalanceToFile("Balance.txt");
						}
						else {
							cout << "Invalid product number!" << endl;
						}
					}break;
					case 2: {

						string name;
						double purchasePrice;
						double salePrice;
						int quantity = 0;

						do {
							cout << "Enter product name: ";
							cin >> name;
							if (name.empty()) {
								cout << "Product name cannot be empty. Please try again." << endl;
							}
						} while (name.empty());

						while (true) {
							cout << "Enter purchase price: ";
							cin >> purchasePrice;
							if (cin.fail() || purchasePrice <= 0) {
								cout << "Invalid purchase price. Please enter a positive number." << endl;
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
							}
							else {
								break;
							}
						}


						while (true) {
							cout << "Enter sales price: ";
							cin >> salePrice;
							if (cin.fail() || salePrice <= 0) {
								cout << "Invalid sales price. Please enter a positive number." << endl;
								cin.clear();
								cin.ignore(numeric_limits<streamsize>::max(), '\n');
							}
							else {
								break;
							}
						}

						products.push_back(Product(name, purchasePrice, salePrice, quantity));
						writeProductToFile("Products.txt");
						cout << "Product added successfully!" << endl;
					}break;
					default:
						break;
					}
				} while (prodList);
			}
			default:
				break;
			}
		} while (menu);
	}



	void userPanel(User currentUser) {
		bool prodMenu = true;
		do {
			system("cls");
			for (size_t i = 0; i < products.size(); i++) {
				cout << i << ") ";
				products[i].printInfo();
			}
			int ch;
			cout << "0 - Exit\n1 - Buy product\nChoice: ";
			cin >> ch;
			switch (ch) {
			case 0: {
				prodMenu = false;
			} break;
			case 1: {
				cout << "Enter product id: ";
				int prodId;
				cin >> prodId;
				cout << "Enter count: ";
				int count;
				cin >> count;
				if (prodId >= 0 && prodId < products.size()) {
					Product& product = products[prodId];
					if (product.getQuantity() <= 0 || product.getQuantity() - count < 0) {
						cout << "There are not enough goods in stock.\n";
						system("pause");
					}
					else {
						product.restock(-count, product.getPurchasePrice());
						balance += count * product.getSalePrice();
						writeProductToFile("Products.txt");
						writeBalanceToFile("Balance.txt");
						cout << "Purchase completed successfully!\n";
						system("pause");
					}
				}
				else {
					cout << "Invalid product id!\n";
					system("pause");
				}
			} break;
			default:
				break;
			}
		} while (prodMenu);
	}

	void createAccount() {
		string firstname, surname, username, password;
		bool isAdmin = false;
		do {
			system("cls");
			cout << "Enter firstname: ";
			cin >> firstname;
		} while (!correctFirstnameAndSurname(firstname));

		do {
			system("cls");
			cout << "Enter surname: ";
			cin >> surname;
		} while (!correctFirstnameAndSurname(surname));

		do {
			system("cls");
			cout << "Enter username: ";
			cin >> username;
		} while (isUsernameTaken(username));

		do {
			system("cls");
			cout << "Enter password (minimum 6 characters):";
			cin >> password;
		} while (password.length() < 6);


		User user = User(firstname, surname, username, password, isAdmin);
		users.push_back(user);
		ofstream file("Users.txt", ios::app);
		if (!file.is_open()) {
			cout << "Error opening customers file for writing\n";
			return;
		}
		file << firstname << " " << surname << " " << username << " " << password << " " << isAdmin << endl;
		file.close();
	
	}

	bool correctFirstnameAndSurname(const string& name) {
		for (char c : name) {
			if (!isalpha(c))
				return false;
		}
		return true;
	}

	bool isUsernameTaken(const string& username) {
		for (const auto& user : users) {
			if (user.getUsername() == username) {
				return true;
			}
		}
		return false;
	}
	void readUserFromFile(string path) {
		ifstream file(path);
		if (!file.is_open()) {
			cout << "Error opening employees file for reading\n";
			return;
		}
		string firstname, surname, username, password;
		bool isAdmin;
		while (file >> firstname >> surname >> username >> password >> isAdmin) {
			users.emplace_back(firstname, surname, username, password, isAdmin);
		}
		file.close();
	}

	void readBalanceFromFile(string path) {
		ifstream file(path);
		if (!file.is_open()) {
			cout << "error\n";
			return;
		}
		double bal;
		while (file >> bal) {
			balance = bal;
		}
		file.close();
	}


	void readProductsFromFile(string path) {
		ifstream file(path);
		if (!file.is_open()) {
			cout << "error\n";
			return;
		}
		string name;
		double purchasePrice;
		double salePrice;
		int quantity;
		while (file >> name >> purchasePrice >> salePrice >> quantity) {
			products.emplace_back(name,purchasePrice,salePrice,quantity);
		}
		file.close();
	}

	void writeUsersToFile(const string& path) {
		ofstream file(path);
		if (!file.is_open()) {
			cout << "Error opening file for writing\n";
			return;
		}
		for (const auto& user : users) {
			file << user.getFirstname() << " " << user.getSurname() << " " << user.getUsername() << " " << user.getPassword() << " " << user.getRole() << endl;
		}
		file.close();
	}

	void writeBalanceToFile(const string& path) {
		ofstream file(path);
		if (!file.is_open()) {
			cout << "Error opening file for writing\n";
			return;
		}
		file << balance << endl;
		file.close();
	}

	void writeProductToFile(const string& path) {
		ofstream file(path);
		if (!file.is_open()) {
			cout << "Error opening file for writing\n";
			return;
		}
		for (auto& prod : products) {
			file << prod.getName() << " " << prod.getPurchasePrice() << " " << prod.getSalePrice() << " " << prod.getQuantity() << endl;
		}
		file.close();
	}
};

