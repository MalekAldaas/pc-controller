#include <iostream>
#include "volume_control_command.h"
#include <cstdlib>

VolumeControlCommand::VolumeControlCommand(Action action, const int& change) : action(action), change(change) {}

CommandStatus VolumeControlCommand::execute(const std::string& args) {
    int result;
    bool isGet = false;

    switch (action) {
        case Action::INCREASE:
            result = system(("amixer set Master " + std::to_string(change) + "%+").c_str());
            break;
        case Action::DECREASE:
            result = system(("amixer set Master " + std::to_string(change) + "%-").c_str());
            break;
        case Action::MUTE:
            result = system("amixer set Master mute");  
            break;
        case Action::UNMUTE:
            result = system("amixer set Master unmute");  
            break;
        case Action::GET:
            isGet = true;
            break;
    }
   
      if (result != 0 && isGet == false) {
          return CommandStatus(false, "failed to adjust volume control command");
      }

      std::string message; 
      std::string volume = getCurrentVolume(); 

      if (isGet == false) {
            message = "Volume Adjusted Successfully " + volume;
      }
      else {
          message = volume;
      }

      return CommandStatus(true, message); 
}


std::string VolumeControlCommand::getCurrentVolume() const {
    FILE* pipe = popen("amixer get Master | grep -Po [0-9]+%", "r"); 
    if (pipe == nullptr) {
        std::cerr << "Failed to retrive the current volume." << std::endl;
        return std::string("ERROR"); 
    }

    char buffer[128];
    std::string result; 

    while( fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result  +=  buffer;
    }

    pclose(pipe);

    if (isMute() == true) {
        result  +=  " (Muted)"; 
    }

    return result;
}
    

bool VolumeControlCommand::isMute() const {
    FILE* pipe = popen("amixer get Master | grep -oP off | wc -c", "r"); 
    if (pipe == nullptr) {
        return false ;
    }

    char buffer[20];
    fgets(buffer, sizeof(buffer), pipe); 
    pclose(pipe); 



    if (std::stoi(buffer) == 0) {
        return false ;
    }
    else {
        return true; 
    }
}


