#include "Instance.h"
Instance::Instance(string name)
{
	this->name = name;
	string line;

	ifstream fichier("Prestige.txt", ios::in);
	if (fichier)
	{
		bool goodline = false;
		while (!goodline){
			getline(fichier, line);
			istringstream iss(line);
			string mot;
			std::getline(iss, mot, ',');
			if (mot == this->name){
				goodline = true;
			}
		}
		vector<string> prestige = cutLine(line);
		for (int i = 1; i<prestige.size(); i++){
			this->prestByAccess[i] = std::stoi(prestige[i]);
		}
		fichier.close();

	}

	else
		cerr << "Impossible d'ouvrir le fichier 1 !" << endl;


	ifstream fichier2("Proficiency.txt", ios::in);
	if (fichier2)
	{
		bool goodline = false;
		while (!goodline){
			getline(fichier2, line);
			istringstream iss(line);
			string mot;
			std::getline(iss, mot, ',');
			if (mot == this->name){
				goodline = true;
			}
		}

		vector<string> proficiency = cutLine(line);
		for (int i = 1; i<proficiency.size(); i++){
			istringstream iss(proficiency[i]);
			string mot;
			std::getline(iss, mot, '-');
			int lowestProf = std::stoi(mot);
			std::getline(iss, mot, '-');
			int highestProf = std::stoi(mot);
			vector<int> proficiencyBracket;
			proficiencyBracket.push_back(lowestProf);
			proficiencyBracket.push_back(highestProf);

			this->lootByAccess[i] = proficiencyBracket;
		}
		fichier2.close();

	}

	else
		cerr << "Impossible d'ouvrir le fichier 2 !" << endl;




}

vector<string> Instance::cutLine(string line){
	vector <string> result;
	istringstream iss(line);
	string mot;
	while (std::getline(iss, mot, ',')){
		result.push_back(mot);
	}
	return result;
}

map<int, int> Instance::getPrestMap(){
	return prestByAccess;
}

map<int, vector<int>> Instance::getLootMap(){
	return lootByAccess;
}

string Instance::getName(){
	return name;
}
