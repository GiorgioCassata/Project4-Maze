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

using namespace std;

enum Company {RED, BLUE, GREEN, NOCOMPANY};
enum LineType {HORSE, CABLE, TROLLEY, BUS, NOLINETYPE};

string comp_to_string(Company comp){
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
        return "ERROR";
}
string trans_to_string(LineType trans){
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
        return "ERROR";
}

struct City {
    char targetName;
    Company company;
    LineType transit;

    City(char targetName, Company company, LineType transit) {
        this->targetName = targetName;
        this->company = company;
        this->transit = transit;
    }

    void print() {
        cout << this->targetName << " with " << comp_to_string(this->company) << "'s " << trans_to_string(this->transit) << endl;
    }

    // necessary for comparisons
    bool operator<(const City& a) const{
        return (this->targetName < a.targetName);
    }
    bool operator==(const City& a) const{
        if (this->targetName == a.targetName && this->company == a.company && this->transit == a.transit) return true;
        return false;
    }
};

// recursive DFS algorithm for generating all paths to 'paths.txt'
void pathfinder(map<char, set<City>> &cities, vector<City> pathsTaken, char previousCity, City lastPath) {
    map<char, set<City>>::iterator current = cities.find(lastPath.targetName);
    // for each path off of previous city...
    for (auto j:current->second) {
        // if the path has been taken or leads to the previous city, skip it
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
        // if matches transit line or company, take it
        if (lastPath.company == j.company || lastPath.transit == j.transit) {
            pathsTaken.push_back(j);

            pathfinder(cities, pathsTaken, current->first, j);

            // by putting this after the function call the paths are saved from
            // deepest to shallowest for each branch (This benefits finding path speed)
            ofstream fout;
            fout.open("paths.txt", std::ofstream::app);

            // print all paths possible, one on each line
            fout << cities.begin()->first << ' '; // startsville
            for (auto k:pathsTaken) {
                fout << k.targetName << ' ';
            }
            fout << endl;
            fout.close();

            pathsTaken.pop_back();
        }
        /*
        //cities.rbegin()->first
        if (j.targetName == target && (j.transit == lastPath.transit || lastPath.company == j.company)) {
            pathsTaken.push_back(j);
            // generate and save output to external file & print to console
            ofstream fout;
            string fileName = "output";
            fileName +=  "_";
            fileName += to_string(pathsTaken.size());
            fileName += ".txt";

            fout.open(fileName);

            cout << "PATH:" << endl;
            // print paths taken this will be answer
            fout << cities.begin()->first << ' '; // startsville
            for (auto k:pathsTaken) {
                k.print();
                fout << k.targetName << ' ';
            }
            fout.close();

            //these dont seem to change outcome
            //pathfinder(cities, pathsTaken, current->first, j, target);
            //pathsTaken.pop_back();
            continue;
        }
        */
    }
    return;
}


int main() {
    int numTowns, numTransitLines;
    char currentCity, targetCity, comp, trans;
    Company company;
    LineType transit;

    map<char, set<City>> cities;
    map<char, set<City>>::iterator it;

    ifstream fin;
    ofstream foutput;


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

        switch (comp) {
            case 'R':
                company = RED;
                break;
            case 'B':
                company = BLUE;
                break;
            case 'G':
                company = GREEN;
                break;
            default:
                company = NOCOMPANY;
        }
        switch (trans) {
            case 'H':
                transit = HORSE;
                break;
            case 'C':
                transit = CABLE;
                break;
            case 'T':
                transit = TROLLEY;
                break;
            case 'B':
                transit = BUS;
                break;
            default:
                transit = NOLINETYPE;
        }

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
            j.print();
            lineCounter++;
        }
        cout << endl;
    }
    // print statement to verify that the number of nodes and edges found matches
    // the number specified in the input file
    cout << "There are " << cities.size() << "/" << numTowns << " cities with " << lineCounter/2 << "/" << numTransitLines << " transit lines." << endl;


    // clear paths.txt and prep for 'pathfinder' function
    ofstream fout;
    fout.open("paths.txt");
    fout.close();
    vector<City> pathsTaken;
    pathsTaken.push_back(*cities.begin()->second.begin());
    pathfinder(cities, pathsTaken, cities.begin()->first,  *cities.begin()->second.begin());


    // Read paths file to find specified target and print them to an output file
    char target = cities.rbegin()->first;
    //cin >> target;
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

    return 0;
}
