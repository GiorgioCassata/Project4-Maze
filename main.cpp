/*  @Author: Giorgio Cassata
 *  Title: Project 4 - Maze
 *  Description:
 *
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <set>

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


    // necessary for set data structure & comparisons
    bool operator<(const City& a) const{
        return (this->targetName < a.targetName);
    }
    bool operator==(const City& a) const{
        return (this->targetName == a.targetName);
    }
};


void pathfinder(map<char, set<City>> &cities, vector<City> pathsTaken, char previousCity, City lastPath, char &target) {
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
        // if matches line or company take it
        if (lastPath.company == j.company || lastPath.transit == j.transit) {
            pathsTaken.push_back(j);
            pathfinder(cities, pathsTaken, current->first, j, target);\
            cout << "path:" << endl;
            for (auto k:pathsTaken) {
                cout << k.targetName << ' ';
            }
            cout << endl;
            pathsTaken.pop_back();
        }

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
            pathfinder(cities, pathsTaken, current->first, j, target);
            //pathsTaken.pop_back();
            continue;
        }
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
    cout << "There are " << cities.size() << " cities with " << lineCounter/2 << " transit lines." << endl;
    cout << endl;

    char target;
    vector<City> pathsTaken;
    cin >> target;
    pathsTaken.push_back(*cities.begin()->second.begin());
    pathfinder(cities, pathsTaken, cities.begin()->first,  *cities.begin()->second.begin(), target);

    /*
    set<City> pathsTaken;
    City lastPath;
    char previousCity;
    it = cities.begin();
    set<City>::iterator it2;
    for (auto j:it->second) {
        it2 = pathsTaken.find(j);
        // if the path has been taken or leads to previous city, skip it
        if (it2 != pathsTaken.end() || j.targetName == previousCity) {
            continue;
        }
        // else if matches line or comp take it
    }
    */




    return 0;
}
