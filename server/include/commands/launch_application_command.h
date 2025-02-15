#ifndef LAUNCH_APPLICATION_COMMAND_H
#define LAUNCH_APPLICATION_COMMAND_H

#include "command.h"
#include "command_status.h"
#include <string>

class LaunchApplicationCommand : public Command {
public:
    explicit LaunchApplicationCommand(const std::string& appName);
    CommandStatus execute(const std::string& args = "") override;

private:
    std::string appName;
};

#endif

