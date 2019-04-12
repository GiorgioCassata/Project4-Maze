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

class City {
    private:
        Company _parentCompany;
        LineType _parentLineType;
    public:
        City* parent;
        City* one;
        City* two;
        City* three;
        City* four;
        City* five;
        City* six;
        City* seven;

        City() {
            this->parent = NULL;
            this->one = NULL;
            this->two = NULL;
            this->three = NULL;
            this->four = NULL;
            this->five = NULL;
            this->six = NULL;
            this->seven = NULL;
            this->_parentCompany = NOCOMPANY;
            this->_parentLineType = NOLINETYPE;
        }

        City(City *parent, Company company, LineType line) {
            this->parent = parent;
            this->one = NULL;
            this->two = NULL;
            this->three = NULL;
            this->four = NULL;
            this->five = NULL;
            this->six = NULL;
            this->seven = NULL;
            this->_parentCompany = company;
            this->_parentLineType = line;
        }

        /*
        ~City() {
            if (this->one != NULL) delete one;
            if (this->two != NULL) delete two;
            if (this->three != NULL) delete three;
            if (this->four != NULL) delete four;
            if (this->five != NULL) delete five;
            if (this->six != NULL) delete six;
            if (this->seven != NULL) delete seven;
        }
        */
        ~City() {
            delete one;
            delete two;
            delete three;
            delete four;
            delete five;
            delete six;
            delete seven;
        }

        void insert(City *x) {
            if (this->one == NULL) this->one = x;
            if (this->two == NULL) this->two = x;
            if (this->three == NULL) this->three = x;
            if (this->four == NULL) this->four = x;
            if (this->five == NULL) this->five = x;
            if (this->six == NULL) this->six = x;
            if (this->seven == NULL) this->seven = x;
        }

        Company getC() {
            return this->_parentCompany;
        }

        LineType getL() {
            return this->_parentLineType;
        }
};


int main() {
    int numTowns, numTransitLines;
    char parent, child, comp, trans;
    Company company;
    LineType transit;

    map<char, City*> cities;
    map<char, City*>::iterator it;

    ifstream fin;
    ofstream fout;

    // open input file in which the first line has num of towns and num of transit lines
    fin.open("input.txt");
    fin >> numTowns;
    fin >> numTransitLines;

    // initiate root (aka startsville)
    City *startsville = new City();
    cities.emplace('A', startsville);
    // read input and create graph
    while (!fin.eof()) {
        fin >> parent;
        fin >> child;
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

        // parent should already exist
        it = cities.find(parent);
        if (it == cities.end()) {
            cout << "ERROR: Discontinuity in input file" << endl;
            return -1;
        }

        // if parent exists check if child node exists
        // if edge already exists continue
        it = cities.find(child);
        if (it == cities.end()) {
            // create new node at the first null child
            City *cityNode = new City(cities.at(parent), company, transit);
            cities.emplace(child, cityNode);
            cities.at(parent)->insert(cityNode);
        } else {
            //City *cityNode = cities.at(child);
            //cities.at(parent)->insert(cityNode);
            continue;
        }

    }

    fin.close();

    cout << cities.size() << endl;
    for (int i = 0; i < cities.size()+5; ++i) {
        if (cities[i] != 0x0) {
            cout << comp_to_string(cities[i]->getC()) << endl;
        }
    }



    // generate and save output to external file & print to console
    fout.open("output.txt");

    fout.close();

    delete startsville; // deleting root should cause deconstructors for each node to be deleted
    return 0;
}
