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

int main() {
    int numDays, numTransitLines;



    ifstream file;
    ofstream fout;

    // open input file in which the first line has num of towns and num of transit lines
    file.open("input.txt");
    file >> numTowns;
    file >> numTransitLines

    // read input and create graph

    file.close();


    // generate and save output to external file & print to console
    fout.open("output.txt");

    fout.close();


    return 0;
}
