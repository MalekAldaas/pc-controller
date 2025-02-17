#ifndef VOLUME_CONTROL_COMMAND_H
#define VOLUME_CONTROL_COMMAND_H

#include <string>
#include "command.h"
#include "command_status.h"

class VolumeControlCommand : public Command {
public:
    enum class Action {
        INCREASE,
        DECREASE,
        MUTE,
        UNMUTE,
        GET
    };

    VolumeControlCommand(Action action, const int& change = 5); 
    CommandStatus execute(const std::string& args) override; 



private:
    int change;
    Action action;
    std::string getCurrentVolume() const; 
    bool isMute() const;
}; 

#endif 
