#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <limits>
using namespace std;
//---------------------------------------------------------------------------//
string randomGod(string & role) {
	// Initialize variables
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
	// Make sure the file opened
	if (!godFile) {
		cerr << "Couldn't open file!" << endl;
	}
	// Choose the random god
	else {
		// Find the length of the file
		while (getline(godFile, godName)) {
			if (godName != "") {
				listLength++;
			}
		}
		// Go back to the beginning of the file
		godFile.clear();
		godFile.seekg(0, ios::beg);
		// Set godName to the random god
		int rGod = rand() % listLength;
		for (int x = 0; x <= rGod; x++) {
			getline(godFile, godName);
		}
	}
	// Close the file and return godName
	godFile.close();
	return godName;
}
//---------------------------------------------------------------------------//
void randomRelics(string relics[]) {
	// Initialize variables
	string relicName;
	int listLength = 0;
	// Open file
	ifstream relicFile("data/relics/relics.txt");
	// Make sure the file opened
	if (!relicFile) {
		cerr << "Couldn't open file!" << endl;
	}
	// Choose the random relics
	else {
		// Find the length of the file
		while (getline(relicFile, relicName)) {
			if (relicName != "") {
				listLength++;
			}
		}
		// Choose two random relics
		for (int x = 0; x < 2; x++) {
			relicFile.clear();
			relicFile.seekg(0, ios::beg);
			int rRelic = rand() % listLength;
			for (int x = 0; x <= rRelic; x++) {
				getline(relicFile, relicName);
			}
			relics[x] = relicName;
		}
		// If the two relics are the same, choose a new one
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
	// Close the file and return
	relicFile.close();
	return;
}
//---------------------------------------------------------------------------//
string randomStarter() {
	// Initialize variables
	string starterName;
	int listLength = 0;
	// Open the file
	ifstream starterFile("data/items/starter.txt");
	// Make sure the file opened
	if (!starterFile) {
		cerr << "Couldn't open file!" << endl;
	}
	// Choose a random starter item
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
	// Close the file and return starterName
	starterFile.close();
	return starterName;
}
//---------------------------------------------------------------------------//
void randomItems(string items[], string role) {
	// Initialize variables
	string itemName;
	int listLength = 0;
	ifstream itemFile;
	// Choose the file that matches god role
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
	// Make sure the file opened
	if (!itemFile) {
		cerr << "Couldn't open file!" << endl;
	}
	// Choose the random items
	else {
		// Find the length of the file
		while (getline(itemFile, itemName)) {
			if (itemName != "") {
				listLength++;
			}
		}
		// Choose 6 random items and put them into the array
		for (int x = 0; x < 6; x++) {
			itemFile.clear();
			itemFile.seekg(0, ios::beg);
			int rItem = rand() % listLength;
			for (int x = 0; x <= rItem; x++) {
				getline(itemFile, itemName);
			}
			items[x] = itemName;
		}
		// Make sure none of the items are the same and regenerate if they are
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
	// Close the file and return
	itemFile.close();
	return;
}
//---------------------------------------------------------------------------//
/*int main() {
	// Start the loop
	bool isRunning = true;
	while (isRunning) {
		// Seed the random number generator
		srand((unsigned)time(0));
		// Generate god and output results
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
		// Update first item if god is Ratatoskr
		if (god == "Ratatoskr") {
			items[0] = "Acorn of Yggdrasil";
		}
		// Print items
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
	return 0;
}*/
