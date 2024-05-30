#include "role.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

User *Role::getUser() { return user; }

const std::string Role::getName() const
{
    return name;
}

void Role::setName(const std::string &new_name)
{
    name = new_name;
}
// TO DO
//  void Role::browse() {

// }
