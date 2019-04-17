#include "TypeEnums.h"
#include "City.h"

City::City(char targetName, Company company, LineType transit) {
    this->targetName = targetName;
    this->company = company;
    this->transit = transit;
}
/*
void City::print() {
    cout << this->targetName << " with " << comp_to_string(this->company) << "'s " << trans_to_string(this->transit) << endl;
}
*/
// necessary for comparisons
bool City::operator<(const City& a) const{
    return (this->targetName < a.targetName);
}

bool City::operator==(const City& a) const{
    if (this->targetName == a.targetName && this->company == a.company && this->transit == a.transit) return true;
    return false;
}