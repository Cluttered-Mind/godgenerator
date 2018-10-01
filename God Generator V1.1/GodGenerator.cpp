#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <fstream>
#include <vector>
using namespace std;

//-----------------------------------------------------------------\\

string randomGod(string & role) {
	ifstream godFile;
	string godName;
	int listLength = 0;
	// Pick the random file and open it
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
	// Check if the file opened correctly
	if (!godFile) {
		cerr << "Couldn't open file!" << endl;
	}
	// Choose a random god from the file
	else {
        // Determine how long the list is
		while (getline(godFile, godName)) {
			if (godName != "") {
				listLength++;
			}
		}
		// Set getline back to the beginning
		godFile.clear();
		godFile.seekg(0, ios::beg);
		// Set godName to the random god
		int rGod = rand() % listLength;
		for (int x = 0; x <= rGod; x++) {
			getline(godFile, godName);
		}
	}
	// Close the file and exit the function
	godFile.close();
	return godName;
}

//-----------------------------------------------------------------\\

void randomRelics(string relics[]) {
	string relicName;
	int listLength = 0;
	// Open the relics file
	ifstream relicFile("data/relics/relics.txt");
	// Make sure the file opened correctly
    if (!relicFile) {
		cerr << "Couldn't open file!" << endl;
	}
	// Find the random relics
	else {
        // Determine how long the list is
		while (getline(relicFile, relicName)) {
			if (relicName != "") {
				listLength++;
			}
		}
		// Get a random relic twice and put it in the relics array
		for (int x = 0; x < 2; x++) {
            // Set getline back to the beginning
			relicFile.clear();
			relicFile.seekg(0, ios::beg);
			// Choose the random relic
			int rRelic = rand() % listLength;
			for (int x = 0; x <= rRelic; x++) {
				getline(relicFile, relicName);
			}
			// Put the relic into the relics array
			relics[x] = relicName;
		}
		// Loop until both relics are different
		bool sameRelics = true;
		while (sameRelics) {
            // If the relics are the same get a new random relic
			if (relics[0] == relics[1]) {
				relicFile.clear();
				relicFile.seekg(0, ios::beg);
				int rRelic = rand() % listLength;
				for (int x = 0; x <= rRelic; x++) {
					getline(relicFile, relicName);
				}
				relics[1] = relicName;
			}
			// If the relics are different continue
			else {
				sameRelics = false;
			}
		}
	}
	// Close the relics file
	relicFile.close();
}

//-----------------------------------------------------------------\\

string randomStarter() {
	string starterName;
	int listLength = 0;
	// Open the starter items folder
	ifstream starterFile("data/items/starter.txt");
	// Make sure the file opened correctly
	if (!starterFile) {
		cerr << "Couldn't open file!" << endl;
	}
	// Find the random starter item
	else {
        // Determine how long the list is
		while (getline(starterFile, starterName)) {
			if (starterName != "") {
				listLength++;
			}
		}
		// Set getline back to the beginning
		starterFile.clear();
		starterFile.seekg(0, ios::beg);
		// Set starterName to the name of the random relic
		int rStarter = rand() % listLength;
		for (int x = 0; x <= rStarter; x++) {
			getline(starterFile, starterName);
		}
	}
	// Close the starter items file and exit the function
	starterFile.close();
	return starterName;
}

//-----------------------------------------------------------------\\

void randomItems(string items[], string role) {
	string itemName;
	int listLength = 0;
	ifstream itemFile;
	// Determine the role of the chosen god and open an item list based on the result
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
	// Make sure the list opened correctly
	if (!itemFile) {
		cerr << "Couldn't open file!" << endl;
	}
	// Determine the 6 items of the build
	else {
        // See how long the list it
		while (getline(itemFile, itemName)) {
			if (itemName != "") {
				listLength++;
			}
		}
		// Choose a random item 6 times
		for (int x = 0; x < 6; x++) {
			itemFile.clear();
			itemFile.seekg(0, ios::beg);
			int rItem = rand() % listLength;
			for (int x = 0; x <= rItem; x++) {
				getline(itemFile, itemName);
			}
			items[x] = itemName;
		}
		// Use a nested for loop to check for duplicate items
		for (int j = 0; j < 6; j++) {
			for (int k = j + 1; k < 6; k++) {
                // If the items are the same choose a new item
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
	// Close the items file
	itemFile.close();
}

//-----------------------------------------------------------------\\

int main() {
	// Start the loop
	char choice = 'y';
	while (choice == 'y' || choice == 'Y') {
		// Seed the random number generator
		srand((unsigned)time(0));
		// Generate god and items
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
		
		cout << '\n';
	}
	system("PAUSE");
	return 0;
}
