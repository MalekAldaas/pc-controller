#include "launch_application_command.h"
#include <cstdlib>

LaunchApplicationCommand::LaunchApplicationCommand(const std::string& appName)
    : appName(appName) {}

CommandStatus LaunchApplicationCommand::execute(const std::string& args) {
    std::string command = appName + " > /dev/null 2>&1 &";  // Run in background & suppress output
    int result = system(command.c_str());

    if (result != 0) {
        return CommandStatus(false, "Failed to launch " + appName);
    }

    return CommandStatus(true, appName + " launched successfully.");
}

