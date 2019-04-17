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
