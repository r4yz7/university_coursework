#pragma once
#include <string>
#include <iostream>
using namespace std;
class Product
{
private:
	string name;
	double purchasePrice;
	double salePrice;
	int quantity;
public:
	Product(string name, double purchasePrice,double salePrice, int quantity) : name(name), purchasePrice(purchasePrice), salePrice(salePrice), quantity(quantity) {}
	Product() {}
	string& getName() {
		return name;
	}

	double getPurchasePrice() {
		return purchasePrice;
	}

	double getSalePrice() {
		return salePrice;
	}
	int getQuantity() {
		return quantity;
	}

	void printInfo() {
		cout << name << ", " << salePrice << " UAH, count: " << quantity << endl;
	}

	void restock(int amount, double price) {
		quantity += amount;
		purchasePrice = price;
	}


};

