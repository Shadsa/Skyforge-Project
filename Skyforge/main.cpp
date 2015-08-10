#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> 
#include "Instance.h"
using namespace std;



int main()
{

	// INITIALIZATION

	cout << "Initialisation phase, please wait..." << endl;
	int prestige = 0;
	int technique = 0;
	vector<Instance> instances;
	map<string, int> resultat;
	bool optimization = true;


	ifstream fichier("Instances.txt", ios::in);
	string line;
	if (fichier){
		while (getline(fichier, line)){
			Instance instance = Instance(line);
			instances.push_back(instance);
		}
		fichier.close();

	}
	else
		cerr << "Impossible d'ouvrir le fichier primaire !" << endl;



	string answer;

	cout << "Enter your prestige :";
	cin >> prestige;
	cout << endl;
	cout << "Enter your technique :";
	cin >> technique;
	cout << endl;
	cout << "Computing entries...";
	cout << endl;



	// COMPUTING TIERS SYNCRONIZATION BEETWEEN PRESTIGE AND TECHNIC









	
	// IN AN OPTIMIZED CASE (computing with technic and scaling with prestige)


	map<string,int> matchingProfInst;
	for (int i = 0; i < instances.size(); i++){		
		map<int, vector<int>> lootMap = instances[i].getLootMap();
		for (int j = 1; j <= instances[i].getLootMap().size(); j++){			
			vector<int> lootBracket = lootMap[j];
			if (lootBracket[0] <= technique && lootBracket[1] >= technique){
				matchingProfInst[instances[i].getName()] = j;
			}
		}
	}

	

	for (std::map<string, int>::iterator it = matchingProfInst.begin(); it != matchingProfInst.end(); ++it){
		for (int i = 0; i < instances.size(); i++){
			if (it->first == instances[i].getName()){
				map<int, int> prestMap = instances[i].getPrestMap();
				if (prestMap[it->second] <= prestige){
					resultat[it->first] = it->second;
				}
			}
		}
	}


	// IN A NOT OPTIMIZED CASED (computing with the highest prestige and the highest technic with such prestige) --> happened when people have too much technic for they prestige.

	if (resultat.size() == 0){
		optimization = false;
		map<string, int> matchingBetterDifficulty;
		map<string, int> matchingBetterLoot;
		for (int i = 0; i < instances.size(); i++){
			map<int, int> prestMap = instances[i].getPrestMap();
			map<int, vector<int>> lootMap = instances[i].getLootMap();
			for (int j = 1; j < prestMap.size(); j++){
				if (prestMap[j] <= prestige && prestMap[j + 1] > prestige){
					matchingBetterDifficulty[instances[i].getName()] = j;
					vector<int> loot = lootMap[j];
					matchingBetterLoot[instances[i].getName()] = loot[1];
				}
			}
		}
		int maxLoot = 0;
		for (std::map<string, int>::iterator it = matchingBetterLoot.begin(); it != matchingBetterLoot.end(); ++it){
			if (it->second > maxLoot)
				maxLoot = it->second;
		}
		for (std::map<string, int>::iterator it = matchingBetterLoot.begin(); it != matchingBetterLoot.end(); ++it){
			if (it->second == maxLoot)
				resultat[it->first] = matchingBetterDifficulty[it->first];
		}
		

		
	}

	//DISPLAY

	if (!optimization){
		cout << "WARNING ! You'r in a not optimize case. It means that you have a too higher technic compare too your prestige. In consequence, the computer selected the highest instances, but you will not be able too loot the highest technic that you should have" <<endl;
		cout << endl;
	}

	cout << "The needed instances are : " << endl;

	for (std::map<string, int>::iterator it = resultat.begin(); it != resultat.end(); ++it){
		string instname = it->first;
		int difficulty;
		if (it->second <= 5){
			difficulty = it->second;
			string pluriel;
			if (difficulty > 1)
				pluriel = " stars";
			else
				pluriel = " star";
			cout << instname << " : " << difficulty << pluriel << endl;
		}
			
		else{
			difficulty = it->second - 5;
			string pluriel;
			if (difficulty > 1)
				pluriel = " skulls";
			else
				pluriel = " skull";
			cout << instname << " : " << difficulty << pluriel << endl;
		}		
	}

	cout << endl;
	cout << "It's OK ? (type y or n)";
	cin >> answer;

}