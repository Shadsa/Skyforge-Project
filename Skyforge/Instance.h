#pragma once
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>


using namespace std;


class Instance
{
public:
	/** Default constructor */
	Instance(string name);
	vector<string> cutLine(string line);
	map<int, vector<int>> getLootMap();
	map<int, int> getPrestMap();
	string getName();

protected:
private:
	string name; //!< Member variable "name;"
	map<int, vector<int>> lootByAccess; //!< Member variable "minLootByAccess;"
	map<int, int> prestByAccess; //!< Member variable "minPrestByAccess;"
};

