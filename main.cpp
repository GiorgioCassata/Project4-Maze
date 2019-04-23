/*  @Author: Giorgio Cassata
 *  Title: Project 4 - Maze
 *
 *  Description: Takes an input from file of a city transit network with
 *      specific properties and creates a graph of it. Then possible paths for
 *      one fare are generated. The shortest path to a specified target is found
 *      and saved to an external file
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

    // Open input file in which the first line has num of towns and num of transit lines
    fin.open("input.txt");
    fin >> numTowns;
    fin >> numTransitLines;

    // Read input and fill map with data
    while (!fin.eof()) {
        // Four characters per line: source, dest, color, type
        fin >> currentCity;
        fin >> targetCity;
        fin >> comp;
        fin >> trans;

        // Translate characters to enumerated types
        company = char_to_comp(comp);
        transit = char_to_line(trans);

        // Add current city to map if it doesnt already exist as a vertex
        it = cities.find(currentCity);
        if (it == cities.end()) {
            set<City> newTargets;
            cities.emplace(currentCity, newTargets);
        }

        // Add target city and edge to list of currentCity's targets
        City target = City(targetCity, company, transit);
        cities.at(currentCity).emplace(target);

        // Add target city to map if it doesntalready exist as a vertex
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


    // Prints out each city along with each of their connections
    // Also counts edges for verifying number of transit lines (edges are double counted)
    int lineCounter = 0;
    for (map<char, set<City>>::iterator i = cities.begin(); i != cities.end(); ++i) {
        cout << i->first << ": ";
        for (auto j:i->second) {
            cout << "\t";
            printCity(j);
            lineCounter++;
        }
        cout << endl;
    }

    cout << "There are " << cities.size() << "/" << numTowns << " cities with " << lineCounter/2 << "/" << numTransitLines << " transit lines." << endl;
    // If the number of nodes and edges does not match the numbers specifies
    // in the input, will not solve or generate new outputs
    if (cities.size() != numTowns || lineCounter/2 != numTransitLines) {
        return -1;
    }

    // Abstraction of function that runs a DFS on the graph
    // and creates paths.txt which contains all paths
    solvePaths(cities);


    // Chooses shortest path from first city to specified
    // city in paths.txt and saves it to output.txt
    choosePath(cities, 'j');


    return 0;
}
