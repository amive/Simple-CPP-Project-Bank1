#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cctype>
#include <fstream>
#include <iomanip>
#include "myLib.h"
using namespace std;

const string fileName = "Clients.txt";

string tabs(int amount) {
	string t = "";
	for (int i = 0; i < amount; i++) {
		t+= "\t";
	}
	return t;
}

vector <string> strSplit(string str, string delimeter) {
	int pos = 0;
	string token = "";
	vector <string> vTokens;
	while ((pos = str.find(delimeter)) != string::npos) {
		token = str.substr(0, pos);
		if (token != "") {
			vTokens.push_back(token);
		}
		str.erase(0, pos + delimeter.length());
	}
	if (str != "") {
		vTokens.push_back(str);
	}
	return vTokens;
}

struct stClients {
	bool markClientForDelete = false;
	string accNum;
	string pin;
	string name;
	string phoneNum;
	float balance;
};

bool findClientByAccNum(string accNum, stClients& client);

string convertRecordToLine(stClients client, string delimeter = "|") {
	string dataLine = "";

	dataLine += client.accNum + delimeter;
	dataLine += client.pin + delimeter;
	dataLine += client.name + delimeter;
	dataLine += client.phoneNum + delimeter;
	dataLine += to_string(client.balance);

	return dataLine;
}

stClients convertLineToRecord(string dataLine, string delimeter = "|") {
	vector <string> vData = strSplit(dataLine, delimeter);
	stClients client;
	client.accNum = vData[0];
	client.pin= vData[1];
	client.name = vData[2];
	client.phoneNum = vData[3];
	client.balance = stof(vData[4]);
	return client;
}

vector <stClients> loadFileData(string fileName, stClients client) {
	fstream clientsData;
	vector <stClients> vClients;
	clientsData.open(fileName, ios::in);
	string dataLine = "";
	if (clientsData.is_open()) {
		while (getline(clientsData, dataLine)) {
			vClients.push_back(convertLineToRecord(dataLine));
		}
		clientsData.close();
	}
	return vClients;
}

stClients readClient() {
	stClients client;

	cout << "Enter account number: ";
	getline(cin >> ws, client.accNum);
	while (findClientByAccNum(client.accNum, client)) {
		cout << "\n Client \"" << client.accNum << "\" Already exists, Enter a different account number: ";
		getline(cin >> ws, client.accNum);
	}
	cout << "Enter pin code: ";
	getline(cin, client.pin);
	cout << "Enter client's name: ";
	getline(cin, client.name);
	cout << "Enter phone number: ";
	getline(cin, client.phoneNum);
	cout << "Enter balance: ";
	cin >> client.balance;

	return client;
}

stClients readNewClientInfo(stClients client) {
	stClients newClientInfo;

	cout << "\n\nEnter new client's info:" << endl;
	newClientInfo.accNum = client.accNum;
	cout << "Enter new pin code: ";
	getline(cin >> ws, newClientInfo.pin);
	cout << "Enter new client's name: ";
	getline(cin, newClientInfo.name);
	cout << "Enter new phone number: ";
	getline(cin, newClientInfo.phoneNum);
	cout << "Enter new balance: ";
	cin >> newClientInfo.balance;

	return newClientInfo;
}

void printClientDetails(stClients client) {
	cout << "\nClient's details:" << endl;
	cout << "-------------------------------------" << endl;
	cout << "Account Number: " << client.accNum << endl;
	cout << "Pin Code: " << client.pin << endl;
	cout << "Name: " << client.name << endl;
	cout << "Phone Number: " << client.phoneNum << endl;
	cout << "Account Balance: " << to_string(client.balance) << endl;
	cout << "-------------------------------------" << endl;
}

void printClient(stClients client) {
	cout << "| " << left << setw(21) << client.accNum << "| " << left << setw(15) <<
		client.pin << "| " << left << setw(32) << client.name << "| " << left << setw(20) <<
		client.phoneNum << "| " << left << setw(15) << to_string(client.balance) << left << endl;
}

void printAllClients(vector <stClients> vClients) {
	for (stClients c : vClients) {
		printClient(c);
	}
	cout << "______________________________________________________________________________________________________________________";

}

void displayMainMenuScreen() {
	cout << "\n=================================" << endl;
	cout << setw(21) << "Main Menu" << endl;
	cout << "=================================" << endl;
	cout << "   [1] Show Client List" << endl;
	cout << "   [2] Add New Client" << endl;
	cout << "   [3] Delete Client" << endl;
	cout << "   [4] Update Client Info" << endl;
	cout << "   [5] Find Client" << endl;
	cout << "   [6] Exit" << endl;
	cout << "=================================" << endl;
}

int readMenuChoice() {
	int choice;
	cout << "\nChoose an option [1-6]: ";
	choice = myLib::readNum();
	return choice;
}

void printTableHeader() {
	cout << "\n______________________________________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(21) << "Account Number" << "| " << left << setw(15) <<
		"Pin Code" << "| " << left << setw(32) << "Client Name" << "| " << left << setw(20) <<
		"Phone Number" << "| " << left << setw(15) << "Balance" << left << endl;
	cout << "______________________________________________________________________________________________________________________\n\n";
}

void addDataToFile(string fileName, string data) {
	fstream file;
	file.open(fileName, ios::out | ios::app);

	if (file.is_open()) {
		file << data << endl;
	}
	file.close();
}

void overwriteFileData(string fileName, vector <stClients> vClients) {
	fstream file;
	string data = "";

	file.open(fileName, ios::out);
	for (stClients& c : vClients) {
		if (file.is_open()) {
			if (!c.markClientForDelete) {
				data = convertRecordToLine(c);
				file << data << endl;
			}
		}
	}
	file.close();
}

bool findClientByAccNum(string accNum, stClients& client) {
	vector <stClients> vClients = loadFileData(fileName, client);

	for (stClients& c : vClients) {
		if (c.accNum == accNum) {
			client = c;
			return true;
		}
	}
	return false;
}

bool markClientForDelete(string accNum, vector <stClients>& vClients) {
	for (stClients& c : vClients) {
		if (c.accNum == accNum) {
			c.markClientForDelete = true;
			return true;
		}
	}
	return false;
}

//Options

void showClientList(vector <stClients> vClients) {
	cout << "\n" << tabs(6) << "Client List (" << vClients.size() << ") Client(s).";
	printTableHeader();
	printAllClients(vClients);
}

void AddNewClient(vector <stClients>& vClients) {

	cout << "\n--------------------------------------" << endl;
	cout << tabs(1) << "Add New Clients Screen" << endl;
	cout << "--------------------------------------" << endl;
	cout << "Adding New Client:\n" << endl;

	stClients client;
	char choice = 'Y';
	do {
		client = readClient();

		string dataLine = convertRecordToLine(client);

		addDataToFile(fileName, dataLine);
		vClients = loadFileData(fileName, client);

		cout << "\n\tClient Added Successfully, Add more clients (Y/N)? ";
		cin >> choice;
	} while (choice == 'Y' || choice == 'y');
}

void deleteClient(vector <stClients>& vClients) {
	cout << "\n--------------------------------------" << endl;
	cout << tabs(1) << "Delete Clients Screen" << endl;
	cout << "--------------------------------------" << endl;

	stClients client;
	string accNum = "";

	char choice = 'Y';

	do {

		cout << "Enter account number: ";
		accNum = myLib::readString();

		while (!findClientByAccNum(accNum, client)) {
			cout << "\nClient Not Found, Enter a different account number: ";
			accNum = myLib::readString();
		}

		printClientDetails(client);

		char choice2 = 'Y';
		cout << "Are you sure you want to delete this client (Y/N)? ";
		cin >> choice2;
		if (choice2 == 'Y' || choice2 == 'y') {
			markClientForDelete(accNum, vClients);
			overwriteFileData(fileName, vClients);
			vClients = loadFileData(fileName, client);
			cout << "\tClient Deleted Successfully, Delete More Clients (Y/N)? ";
			cin >> choice;
		}
		else return;
	} while (choice == 'Y' || choice == 'y');
}

void updateClientInfo(vector <stClients>& vClients) {
	cout << "\n--------------------------------------" << endl;
	cout << tabs(1) << "Update Clients Screen" << endl;
	cout << "--------------------------------------" << endl;

	string accNum = "";

	stClients client;

	char choice = 'Y';

	do {
		cout << "Enter account number: ";
		accNum = myLib::readString();

		while (!findClientByAccNum(accNum, client)) {
			cout << "\nClient Not Found, Enter a different account number: ";
			accNum = myLib::readString();
		}

		printClientDetails(client);

		char choice2 = 'Y';

		cout << "Are you sure you want to update this client (Y/N)? ";
		cin >> choice2;

		if (choice2 == 'Y' || choice2 == 'y') {

			for (stClients& c : vClients) {
				if (c.accNum == accNum) {
					c = readNewClientInfo(client);
					break;
				}
			}
			overwriteFileData(fileName, vClients);
			cout << "\tClient Updated Successfully, Update More Clients (Y/N)? ";
			cin >> choice;
		}
		else return;
	} while (choice == 'Y' || choice == 'y');
}

void findClient() {
	cout << "\n-------------------------------------" << endl;
	cout << tabs(1) << "Find Client Screen" << endl;
	cout << "-------------------------------------" << endl;

	stClients client;

	string accNum = "";
	cout << "Enter account number: ";
	accNum = myLib::readString();
	
	while (!findClientByAccNum(accNum, client)) {
		cout << "\nClient Not Found, Enter a different account number: ";
		accNum = myLib::readString();
	}
	
	printClientDetails(client);
}

//Menu Navigation System
void menuNavigation(vector <stClients>& vClients);
void showMainMenu(vector <stClients>& vClients) {
	cout << "\nPress any key to go back to the main menu...";
	system("pause > 0");
	menuNavigation(vClients);
}
void menuNavigation(vector <stClients>& vClients) {
	system("cls");
	int choice = 0;
	displayMainMenuScreen();
	choice = readMenuChoice();
	stClients client;

	switch (choice) {
	case 1: 
		system("cls");
		showClientList(vClients);
		showMainMenu(vClients);
		break;
	case 2:
		system("cls");
		AddNewClient(vClients);
		showMainMenu(vClients);
		break;
	case 3:
		system("cls");
		deleteClient(vClients);
		showMainMenu(vClients);
		break;
	case 4:
		system("cls");
		updateClientInfo(vClients);
		showMainMenu(vClients);
		break;
	case 5:
		system("cls");
		findClient();
		showMainMenu(vClients);
		break;
	case 6:
		return;
	}
}

int main() {
		system("cls");
		stClients client;
		vector <stClients> vClients = loadFileData(fileName, client);
		menuNavigation(vClients);
}