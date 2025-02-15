#include <iostream>
#include <cstdlib>
#include "battery_percentage_command.h"
#include <array>

CommandStatus BatteryCommand::execute(const std::string& args) {
    FILE* pipe = popen("upower --dump | grep percentage | head -n 1 | awk '{print $2}'", "r"); 

    if (!pipe) {
        return CommandStatus(false, "Couldn't retrive battery percentage information"); 
    }

    std::array<char, 128> buffer; 
    std::string result; 

    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result  +=  buffer.data(); 
    }

    pclose(pipe);

    if (!result.empty() && result.back() == '\n') {
        result.pop_back();
    }

    return CommandStatus(true, "Battery Percentage is: " + result);
}
