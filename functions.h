#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <set>
#include <sstream>

#include "TypeEnums.h"
#include "City.h"

using namespace std;

// to_string functions for printing names of enumerated variables
string comp_to_string(Company comp);
string trans_to_string(LineType trans);

// conversion from characters found in input file to the enumerated types
Company char_to_comp(char a);
LineType char_to_line(char a);

void printCity(City a);

// recursive DFS algorithm for generating all paths to 'paths.txt'
void pathfinder(map<char, set<City>> &cities, vector<City> pathsTaken, char previousCity, City lastPath);

void solvePaths(map<char, set<City>> &cities);

//void solvePaths_BFS(map<char, set<City>> &cities);

void choosePath(map<char, set<City>> &cities);

#endif
