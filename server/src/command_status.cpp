#include <iostream>
#include "command_status.h"

CommandStatus::CommandStatus(const bool& success, const std::string& status) :
     success(success), status(status){}


 std::string CommandStatus::getStatus() const {
     return status; 
 }

bool CommandStatus::isSuccess() const {
    return success;
}

