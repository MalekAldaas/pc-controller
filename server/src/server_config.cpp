#include <iostream>
#include "server_config.h"
#include "uptime_command.h"
#include "battery_percentage_command.h"
#include "launch_application_command.h"


ServerConfig& ServerConfig::getInstance() {
    static ServerConfig instance;
    return instance;
}
void ServerConfig::registerCommand(const std::string& commandName, std::shared_ptr<Command> command) {
    commands[commandName] = std::move(command);
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
    registerCommand("battery_percentage", std::make_shared<BatteryCommand>()); 
    registerCommand("launch_telegram", std::make_shared<LaunchApplicationCommand>("telegram-desktop"));
    registerCommand("launch_firefox", std::make_shared<LaunchApplicationCommand>("firefox"));
    registerCommand("launch_thunderbird", std::make_shared<LaunchApplicationCommand>("thunderbird"));
}
