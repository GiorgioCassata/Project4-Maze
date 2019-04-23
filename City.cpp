/*  @Author: Giorgio Cassata
 *  Title: Project 4 - Maze
 */
 
#include "TypeEnums.h"
#include "City.h"

City::City(char targetName, Company company, LineType transit) {
    this->targetName = targetName;
    this->company = company;
    this->transit = transit;
}

// necessary for comparisons
bool City::operator<(const City& a) const{
    return (this->targetName < a.targetName);
}

bool City::operator==(const City& a) const{
    if (this->targetName == a.targetName && this->company == a.company && this->transit == a.transit) return true;
    return false;
}
