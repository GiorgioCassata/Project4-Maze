/*  @Author: Giorgio Cassata
 *  Title: Project 4 - Maze
 *  Description: Takes an input from file and creates a graph
 *
 *
 */
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <set>
#include <sstream>

#include "TypeEnums.h"
#include "functions.h"
#include "City.h"

using namespace std;

int main() {
    int numTowns, numTransitLines;
    char currentCity, targetCity, comp, trans;
    Company company;
    LineType transit;

    map<char, set<City>> cities;
    map<char, set<City>>::iterator it;

    ifstream fin;

    // open input file in which the first line has num of towns and num of transit lines
    fin.open("input.txt");
    fin >> numTowns;
    fin >> numTransitLines;

    // read input and fill map with data
    while (!fin.eof()) {
        fin >> currentCity;
        fin >> targetCity;
        fin >> comp;
        fin >> trans;

        company = char_to_comp(comp);
        transit = char_to_line(trans);

        // Add current city if it doesnt exist
        it = cities.find(currentCity);
        if (it == cities.end()) {
            set<City> newTargets;
            cities.emplace(currentCity, newTargets);
        }
        // add target city to list of currentCity's targets
        City target = City(targetCity, company, transit);
        cities.at(currentCity).emplace(target);

        // add target city if it doesnt exist
        it = cities.find(targetCity);
        if (it == cities.end()) {
            set<City> newTargets;
            cities.emplace(targetCity, newTargets);
        }
        // add current city to list of targetCity's targets
        target = City(currentCity, company, transit);
        cities.at(targetCity).emplace(target);
    }

    fin.close();

    // prints out each city along with each of their connections
    int lineCounter = 0; // counts each transit line (should count each one twice)
    for (map<char, set<City>>::iterator i = cities.begin(); i != cities.end(); ++i) {
        cout << i->first << ": ";
        for (auto j:i->second) {
            cout << "\t";
            printCity(j);
            lineCounter++;
        }
        cout << endl;
    }


    // print statement to verify that the number of nodes and edges found matches
    // the number specified in the input file
    cout << "There are " << cities.size() << "/" << numTowns << " cities with " << lineCounter/2 << "/" << numTransitLines << " transit lines." << endl;

    // abstraction of function that runs a DFS on
    solvePaths(cities);

    choosePath(cities);

    return 0;
}
