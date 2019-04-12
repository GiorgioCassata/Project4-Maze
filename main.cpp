/*  @Author: Giorgio Cassata, Dominick Dunn, Sushmita Patil
 *
 *  Description: Dynamic solution with O(2^n) complexity
 *
*/
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// A recursive function that builds all combinations of
// days with no repeats and without considering order (Not Including 0)
vector<vector<int>> Combinations(int n, vector<vector<int>> list) {
    vector<vector<int>> list2;
    // stop condition for recursion
    if (n == 0) {
      return list;
    }
    // add combination of just current day
    list2.push_back({n});

    // add all previous combinations
    list2.insert(list2.end(), list.begin(), list.end());
    // add current day to all previous combinations
    for (int i = 1; i < list2.size(); ++i) {
        list2.at(i).push_back(n);
    }

    // combine current day combinations to previous combinations
    list.insert(list.end(), list2.begin(), list2.end());
    // recursive call to calculate combinations for next smaller size
    return Combinations(n-1, list);
}


int main() {
    vector<vector<int>> list;
    vector<int> x, s;

    int numDays;
    int greatestIndex;
    int temp;

    bool trigger;
    ifstream file;
    ofstream fout;

    // open input file in which the first entry is n = number of days
    file.open("input.txt");
    file >> numDays;

    // read in and store into vectors, the x and s series  of numbers
    for (int i = 0; i < numDays; ++i) {
        file >> temp;
        x.push_back(temp);
    }
    for (int i = 0; i < numDays; ++i) {
        file >> temp;
        s.push_back(temp);
    }
    file.close();

    vector<vector<int>> processes (numDays);
    // calculate all possible processes possible just one time and store into matrix
    for (int i = 0; i < numDays; ++i) {
        for (int j = 0; j < numDays; ++j) {
            if (s.at(j) > x.at(i)) {
                processes.at(i).push_back(x.at(i));
            } else {
                processes.at(i).push_back(s.at(j));
            }
            if (j >= i) {
                break;
            }
        }
    }

    // call recursive function to create combinations list
    list = Combinations(numDays-1, list);
    list.insert(list.begin(), {0});


    int *sums = new int[list.size()];
    int *tempPrint = new int[numDays];
    int *toPrint = new int[numDays];
    // calculate possible sums using each combination
    for (int k = 0; k < list.size(); ++k) {
        temp = 0;
        sums[k] = 0;
        for (int i = 0; i < numDays; ++i) {
            trigger = false;
            for (int a = 0; a < list.at(k).size(); ++a) {
                if (list.at(k).at(a)-1 == i) {
                    temp = 0;
                    trigger = true;
                    break;
                }
            }
            if (trigger) {
                tempPrint[i] = 0;
                continue;
            }
            sums[k] += processes.at(i).at(temp);
            tempPrint[i] = processes.at(i).at(temp);
            temp++;
        }
        if (k > 1) {
            if (sums[k] > sums[greatestIndex]) {
                greatestIndex = k;
                for (int b = 0; b < numDays; ++b) {
                    toPrint[b] = tempPrint[b];
                }
            }
        } else {
            greatestIndex = k;
            for (int b = 0; b < numDays; ++b) {
                toPrint[b] = tempPrint[b];
            }
        }
    }
    delete[] tempPrint;

    // generate and save output to external file & print to console
    fout.open("output.txt");
    fout << sums[greatestIndex] << endl;
    cout << sums[greatestIndex] << endl;
    for (int i = 0; i < numDays; ++i) {
        fout << toPrint[i] << " ";
        cout << toPrint[i] << " ";
    }
    fout.close();
    cout << endl;

    delete[] toPrint;
    delete[] sums;

    return 0;
}
