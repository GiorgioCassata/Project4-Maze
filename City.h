/*  @Author: Giorgio Cassata
 *  Title: Project 4 - Maze
 */
 
#ifndef _CITY_H
#define _CITY_H

#include <iostream>

struct City {
    char targetName;
    Company company;
    LineType transit;

    City(char targetName, Company company, LineType transit);

    // necessary for comparisons
    bool operator<(const City& a) const;
    bool operator==(const City& a) const;
};


#endif
