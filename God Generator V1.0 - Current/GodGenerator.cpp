#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <fstream>
#include <vector>

using namespace std;

string randomGod(string & role) {
	ifstream godFile;
	string godName;
	int listLength = 0;
	// Pick the random file
	int rList = (rand() % 5) + 1;
	if (rList == 1) {
		godFile.open("data/gods/assassin.txt");
		role = "Assassin";
	}
	else if (rList == 2) {
		godFile.open("data/gods/guardian.txt");
		role = "Guardian";
	}
	else if (rList == 3) {
		godFile.open("data/gods/hunter.txt");
		role = "Hunter";
	}
	else if (rList == 4) {
		godFile.open("data/gods/mage.txt");
		role = "Mage";
	}
	else if (rList == 5) {
		godFile.open("data/gods/warrior.txt");
		role = "Warrior";
	}
	// Pick the random god from the file
	if (!godFile) {
		cerr << "Couldn't open file!" << endl;
	}
	else {
		while (getline(godFile, godName)) {
			if (godName != "") {
				listLength++;
			}
		}
		godFile.clear();
		godFile.seekg(0, ios::beg);
		int rGod = rand() % listLength;
		for (int x = 0; x <= rGod; x++) {
			getline(godFile, godName);
		}
	}
	godFile.close();
	return godName;
}

void randomRelics(string relics[]) {
	string relicName;
	int listLength = 0;
	ifstream relicFile("data/relics/relics.txt");
	if (!relicFile) {
		cerr << "Couldn't open file!" << endl;
	}
	else {
		while (getline(relicFile, relicName)) {
			if (relicName != "") {
				listLength++;
			}
		}
		for (int x = 0; x < 2; x++) {
			relicFile.clear();
			relicFile.seekg(0, ios::beg);
			int rRelic = rand() % listLength;
			for (int x = 0; x <= rRelic; x++) {
				getline(relicFile, relicName);
			}
			relics[x] = relicName;
		}
		bool sameRelics = true;
		while (sameRelics) {
			if (relics[0] == relics[1]) {
				relicFile.clear();
				relicFile.seekg(0, ios::beg);
				int rRelic = rand() % listLength;
				for (int x = 0; x <= rRelic; x++) {
					getline(relicFile, relicName);
				}
				relics[1] = relicName;
			}
			else {
				sameRelics = false;
			}
		}
	}
	relicFile.close();
}

string randomStarter() {
	string starterName;
	int listLength = 0;
	ifstream starterFile("data/items/starter.txt");
	if (!starterFile) {
		cerr << "Couldn't open file!" << endl;
	}
	else {
		while (getline(starterFile, starterName)) {
			if (starterName != "") {
				listLength++;
			}
		}
		starterFile.clear();
		starterFile.seekg(0, ios::beg);
		int rStarter = rand() % listLength;
		for (int x = 0; x <= rStarter; x++) {
			getline(starterFile, starterName);
		}
	}
	starterFile.close();
	return starterName;
}

void randomItems(string items[], string role) {
	string itemName;
	int listLength = 0;
	ifstream itemFile;
	
	if (role == "Assassin") {
		itemFile.open("data/items/assassin.txt");
	}
	else if (role == "Guardian") {
		itemFile.open("data/items/guardian.txt");
	}
	else if (role == "Hunter") {
		itemFile.open("data/items/hunter.txt");
	}
	else if (role == "Mage") {
		itemFile.open("data/items/mage.txt");
	}
	else if (role == "Warrior") {
		itemFile.open("data/items/warrior.txt");
	}
	
	if (!itemFile) {
		cerr << "Couldn't open file!" << endl;
	}
	else {
		while (getline(itemFile, itemName)) {
			if (itemName != "") {
				listLength++;
			}
		}
		for (int x = 0; x < 6; x++) {
			itemFile.clear();
			itemFile.seekg(0, ios::beg);
			int rItem = rand() % listLength;
			for (int x = 0; x <= rItem; x++) {
				getline(itemFile, itemName);
			}
			items[x] = itemName;
		}
		for (int j = 0; j < 6; j++) {
			for (int k = j + 1; k < 6; k++) {
				if (items[j] == items[k]) {
					itemFile.clear();
					itemFile.seekg(0, ios::beg);
					int rItem = rand() % listLength;
					for (int x = 0; x <= rItem; x++) {
						getline(itemFile, itemName);
					}
					items[k] = itemName;
				}
			}
		}
	}
	itemFile.close();
}

int main() {
	// Start the loop
	bool isRunning = true;
	while (isRunning) {
		// Seed the random number generator
		srand((unsigned)time(0));
		// Generate god
		string role;
		string god = randomGod(role);
		cout << "God: " << god << '\n';
		cout << "Role: " << role << '\n';
		string relics[2];
		randomRelics(relics);
		cout << "Relics: " << relics[0] << " and " << relics[1] << '\n';
		string starterItem = randomStarter();
		cout << "Starter Item: " << starterItem << '\n';
		string items[6];
		randomItems(items, role);
		cout << "Items: ";
		for (int x = 0; x < 6; x++) {
			if (x == 5) {
				cout << items[x] << '\n';
			}
			else {
				cout << items[x] << ", ";
			}
		}
		// Choice to continue or quit
		char choice;
		cout << "Spin again? (y or n) ";
		cin >> choice;
		if (choice == 'n' || choice == 'N') {
			isRunning = false;
		}
		cout << '\n';
	}
	system("PAUSE");
	return 0;
}
