/*  @Author: Giorgio Cassata
 *  Title: Project 4 - Maze
 *  Description:
 *
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

enum Company {RED, BLUE, GREEN, NOCOMPANY};
enum LineType {HORSE, CABLE, TROLLEY, BUS, NOLINETYPE};

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
            parent = NULL;
            one = NULL;
            two = NULL;
            three = NULL;
            four = NULL;
            five = NULL;
            six = NULL;
            seven = NULL;
            _parentCompany = NOCOMPANY;
            _parentLineType = NOLINETYPE;
        }

        ~City() {
            delete one;
            delete two;
            delete three;
            delete four;
            delete five;
            delete six;
            delete seven;
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



    ifstream fin;
    ofstream fout;

    // open input file in which the first line has num of towns and num of transit lines
    fin.open("input.txt");
    fin >> numTowns;
    fin >> numTransitLines;

    while (!fin.eof()) {
        fin >>
    }
    // read input and create graph

    fin.close();

    City *startsville = new City;
    if (startsville->getC() == NOCOMPANY) {
        cout << "No city lmao" << endl;
    }
    delete startsville;

    // generate and save output to external file & print to console
    fout.open("output.txt");

    fout.close();


    return 0;
}
