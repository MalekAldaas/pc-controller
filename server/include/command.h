#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include "command_status.h"


class Command {
public:
    virtual CommandStatus execute(const std::string& args = "") = 0; 
    virtual ~Command() {}
};


#endif
