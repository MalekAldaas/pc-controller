#ifndef UPTIME_COMMAND_H
#define UPTIME_COMMAND_H

#include "command.h"
#include "command_status.h"
#include <iostream>
#include <cstdlib>


class UptimeCommand : public Command{
public:
    UptimeCommand() = default;
    virtual ~UptimeCommand() = default;

    CommandStatus execute(const std::string& args) override ;

};
#endif 
