#include "uptime_command.h"

#include <iostream>
#include <sstream>
#include <array>
#include <memory>
#include <cstdlib>



CommandStatus UptimeCommand::execute(const std::string& args) {
    std::array<char, 128> buffer; 
    std::string uptime_str = ""; 

    FILE* uptime_file = popen("uptime -p", "r");
    if(uptime_file == nullptr){
        return CommandStatus(false, "Failed to run the `uptime -p` command"); 
    }

    while(fgets(buffer.data(), buffer.size(), uptime_file) != nullptr) {
        uptime_str  +=  buffer.data();
    }

    pclose(uptime_file);

    return CommandStatus(true, uptime_str); 
}



