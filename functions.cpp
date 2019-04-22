#include "functions.h"


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

void printCity(City a) {
        cout << a.targetName << " with " << comp_to_string(a.company) << "'s " << trans_to_string(a.transit) << endl;
}

// recursive DFS algorithm for generating all paths to 'paths.txt'
// is helped and called by solvePaths
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
    }
    return;
}

// clear paths.txt and prep for 'pathfinder' function
void solvePaths(map<char, set<City>> &cities) {
    ofstream fout;
    fout.open("paths.txt");
    fout.close();
    vector<City> pathsTaken;
    pathsTaken.push_back(*cities.begin()->second.begin());
    pathfinder(cities, pathsTaken, cities.begin()->first,  *cities.begin()->second.begin());
}

/*
void solvePaths_BFS(map<char, set<City>> &cities) {
    ofstream fout;
    fout.open("paths.txt");
    fout.close();
    set<char> greyPaths;
    set<char> blackPaths;
    set<char> whitePaths;
    map<char, set<City>>::iterator it;
    for (it = cities.begin(); it != cities.end(); ++it) {
        whitePaths.emplace(it->first);
    }

    //while(greyPaths.size() != 0) {
    for (int i = 0; i < 10; ++i) {
    map<char, set<City>>::iterator current = cities.find(*whitePaths.begin());
        whitePaths.erase(current->first);
        greyPaths.emplace(current->first);
        // for each path off of previous city...
        for (auto j:current->second) {
            if (lastPath.company == j.company || lastPath.transit == j.transit) {
                if (greyPaths.find(j.targetName) == greyPaths.end() && blackPaths.find(j.targetName) == blackPaths.end()) {
                    whitePaths.erase(j.targetName);
                    greyPaths.emplace(j.targetName);
                }
            }
        }
        greyPaths.erase(current->first);
        blackPaths.emplace(current->first);
    }
    ofstream fout;
    fout.open("paths.txt", std::ofstream::app);

    // print all paths possible, one on each line
    for (auto k:blackPaths) {
        fout << k << ' ';
    }
    fout << endl;
    fout.close();
    return;
}
*/

void choosePath(map<char, set<City>> &cities) {
    ifstream fin;
    ofstream foutput;
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
}
