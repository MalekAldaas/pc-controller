#include <iostream>
#include "server_config.h"
#include "uptime_command.h"


ServerConfig& ServerConfig::getInstance() {
    static ServerConfig instance;
    return instance;
}
void ServerConfig::registerCommand(const std::string& commandName, std::shared_ptr<Command> command) {
    this->commands[commandName] = std::move(command);
}   

std::shared_ptr<Command> ServerConfig::getCommand(const std::string& commandName) const {
    auto it = this->commands.find(commandName); 
    if (it != this->commands.end()) {
        return it->second; 
    }
    return nullptr; 
}

// ##add new commands here##
void ServerConfig::initilizeCommands() {
    registerCommand("uptime", std::make_shared<UptimeCommand>());
}
