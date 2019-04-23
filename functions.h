/*  @Author: Giorgio Cassata
 *  Title: Project 4 - Maze
 */
 
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

// Recursive DFS algorithm for generating all paths to 'paths.txt'
// Is helped and called by solvePaths
void recursiveDFS(map<char, set<City>> &cities, vector<City> pathsTaken, char previousCity, City lastPath);

// Clear paths.txt and prep for 'recursiveDFS' (recursive DFS) function
void solvePaths(map<char, set<City>> &cities);

//void solvePaths_BFS(map<char, set<City>> &cities);

// Read paths file to find paths with target as the endpoint
// Identifying the shortest one and printing to output file
void choosePath(map<char, set<City>> &cities, char target);

#endif
