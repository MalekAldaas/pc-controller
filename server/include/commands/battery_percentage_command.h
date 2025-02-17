#ifndef BATTERY_PERCENTAGE_COMMAND_H
#define BATTERY_PERCENTAGE_COMMAND_H

#include "command.h"
#include "command_status.h"
#include <string>

class BatteryCommand : public Command {
public:
    BatteryCommand() = default; 
    virtual ~BatteryCommand() = default;
    CommandStatus execute(const std::string& args = "") override; 
};

#endif
