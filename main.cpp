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

using namespace std;

enum Company {RED, BLUE, GREEN, NOCOMPANY};
enum LineType {HORSE, CABLE, TROLLEY, BUS, NOLINETYPE};

struct City {
    char targetName;
    Company company;
    LineType transit;
    City(char targetName, Company company, LineType transit);
    // necessary for comparisons
    bool operator<(const City& a) const;
    bool operator==(const City& a) const;
};

void printCity(City a);
// to_string functions for printing names of enumerated variables
string comp_to_string(Company comp);
string trans_to_string(LineType trans);
// conversion from characters found in input file to the enumerated types
Company char_to_comp(char a);
LineType char_to_line(char a);
// Recursive DFS algorithm for generating all paths to 'paths.txt'
// Is helped and called by solvePaths
void recursiveDFS(map<char, set<City>> &cities, vector<City> pathsTaken, char previousCity, City lastPath);
// Clear paths.txt and prep for 'recursiveDFS' (recursive DFS) function
void solvePaths(map<char, set<City>> &cities);
// Read paths file to find paths with target as the endpoint
// Identifying the shortest one and printing to output file
void choosePath(map<char, set<City>> &cities, char target);

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


City::City(char targetName, Company company, LineType transit) {
    this->targetName = targetName;
    this->company = company;
    this->transit = transit;
}

// necessary for comparisons
bool City::operator<(const City& a) const{
    return (this->targetName < a.targetName);
}

bool City::operator==(const City& a) const{
    if (this->targetName == a.targetName && this->company == a.company && this->transit == a.transit) return true;
    return false;
}


void printCity(City a) {
        cout << a.targetName << " with " << comp_to_string(a.company) << "'s " << trans_to_string(a.transit) << endl;
}

// to_string functions for printing names of enumerated variables
string comp_to_string(Company comp) {
        switch (comp) {
            case RED:
                return "RED";
            case BLUE:
                return "BLUE";
            case GREEN:
                return "GREEN";
            default:
                return "NONE";
        }
}
string trans_to_string(LineType trans) {
        switch (trans) {
            case HORSE:
                return "HORSE";
            case CABLE:
                return "CABLE";
            case TROLLEY:
                return "TROLLEY";
            case BUS:
                return "BUS";
            default:
                return "NONE";
        }
}

// conversion from characters found in input file to the enumerated types
Company char_to_comp(char a) {
    switch (a) {
        case 'R':
            return RED;
            break;
        case 'B':
            return BLUE;
            break;
        case 'G':
            return GREEN;
            break;
        default:
            return NOCOMPANY;
    }
}
LineType char_to_line(char a) {
    switch (a) {
        case 'H':
            return HORSE;
            break;
        case 'C':
            return CABLE;
            break;
        case 'T':
            return TROLLEY;
            break;
        case 'B':
            return BUS;
            break;
        default:
            return NOLINETYPE;
    }
}

// Recursive DFS algorithm for generating all paths to 'paths.txt'
// Is helped and called by solvePaths
void recursiveDFS(map<char, set<City>> &cities, vector<City> pathsTaken, char previousCity, City lastPath) {
    map<char, set<City>>::iterator current = cities.find(lastPath.targetName);
    // For each path off of current city...
    for (auto j:current->second) {
        // If the specific path has been taken or leads to the previous city, skip it
        bool temp = false;
        for (auto k:pathsTaken) {
            if (j == k) {
                temp = true;
                break;
            }
        }
        if (temp) continue;
        if (j.targetName == previousCity) {
            continue;
        }

        // If matches transit line or company, take it
        if (lastPath.company == j.company || lastPath.transit == j.transit) {
            pathsTaken.push_back(j);
            recursiveDFS(cities, pathsTaken, current->first, j);

            // by putting this after the function call the paths are saved from
            // deepest to shallowest for each branch
            ofstream fout;
            fout.open("paths.txt", std::ofstream::app); // must append to file as to not overwrite previous paths

            fout << cities.begin()->first << ' '; // print starting node
            for (auto k:pathsTaken) {
                fout << k.targetName << ' ';
            }
            fout << endl;
            fout.close();

            pathsTaken.pop_back();
        }
    }
    return;
}

// Clear paths.txt and prep for 'recursiveDFS' function
void solvePaths(map<char, set<City>> &cities) {
    ofstream fout;
    fout.open("paths.txt");
    fout.close();
    vector<City> pathsTaken;
    pathsTaken.push_back(*cities.begin()->second.begin());
    recursiveDFS(cities, pathsTaken, cities.begin()->first,  *cities.begin()->second.begin());
}

// Read paths file to find paths with target as the endpoint
// Identifying the shortest one and printing to output file
void choosePath(map<char, set<City>> &cities, char target) {
    ifstream fin;
    ofstream foutput;

    fin.open("paths.txt");
    foutput.open("output.txt");
    string inputLine;
    string shortestPath = "NA";
    while(getline(fin, inputLine)) {
        if (inputLine.at(inputLine.size()-2) == target) {
            if (shortestPath == "NA") {
                shortestPath = inputLine;
            } else if (inputLine.size() < shortestPath.size()) {
                shortestPath = inputLine;
            }
        }
    }
    foutput << shortestPath << endl;
    fin.close();
    foutput.close();
}
