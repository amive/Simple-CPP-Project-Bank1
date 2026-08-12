#pragma once
#include <iostream>
using namespace std;

namespace myLib {
	int readNum() {
		int num;
		cin >> num;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return num;
	}
	int readNumFloat() {
		float num;
		cin >> num;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return num;
	}
	int randomNumber(int min, int max) {
		return rand() % (max - min + 1) + min;
	}
	bool repeatProgram() {
		int choice = 0;
		cout << "\nExecute again (1/0)? ";
		cin >> choice;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return bool(choice);
	}
	void swap(int& n1, int& n2) {
		int temp;
		temp = n1;
		n1 = n2;
		n2 = temp;
	}
	string readString() {
		string phrase;
		getline(cin >> ws, phrase);
		return phrase;
	}
	char readChar() {
		char c;
		cin >> c;
		return c;
	}
}