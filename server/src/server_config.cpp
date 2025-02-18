#include <iostream>
#include "server_config.h"
#include "uptime_command.h"
#include "battery_percentage_command.h"
#include "launch_application_command.h"
#include "volume_control_command.h"


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
    registerCommand("launch_protonvpn", std::make_shared<LaunchApplicationCommand>("protonvpn-app")); 
    registerCommand("launch_calculator", std::make_shared<LaunchApplicationCommand>("gnome-calculator")); 
    registerCommand("increase_volume", std::make_shared<VolumeControlCommand>(VolumeControlCommand::Action::INCREASE)); 
    registerCommand("decrease_volume", std::make_shared<VolumeControlCommand>(VolumeControlCommand::Action::DECREASE)); 
    registerCommand("mute_volume", std::make_shared<VolumeControlCommand>(VolumeControlCommand::Action::MUTE)); 
    registerCommand("unmute_volume", std::make_shared<VolumeControlCommand>(VolumeControlCommand::Action::UNMUTE)); 
    registerCommand("get_volume", std::make_shared<VolumeControlCommand>(VolumeControlCommand::Action::GET)); 
}
