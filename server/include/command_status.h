#ifndef COMMAND_STATUS_H
#define COMMAND_STATUS_H

#include <iostream>


class CommandStatus {
public:
    CommandStatus(const bool& success, const std::string& status); 
    std::string getStatus() const;
    bool isSuccess() const;

private:
    std::string status;
    bool success; 
};

#endif 
