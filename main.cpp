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

    // necessary for set data structure
    bool operator<(const City& a) const{
        return (this->targetName < a.targetName);
    }
};

int main() {
    int numTowns, numTransitLines;
    char currentCity, targetCity, comp, trans;
    Company company;
    LineType transit;

    map<char, set<City>> cities;
    map<char, set<City>>::iterator it;

    ifstream fin;
    ofstream fout;

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
    map<char, set<City>> temp;
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

    // BFS for pretty display
    vector<city>



    // generate and save output to external file & print to console
    fout.open("output.txt");

    fout.close();

    return 0;
}
