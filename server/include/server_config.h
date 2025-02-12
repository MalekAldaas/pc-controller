#ifndef SERVER_CONFIG_H
#define SERVER_CONFIG_H

#include "command.h"
#include <string>
#include <memory>
#include <unordered_map>

class ServerConfig {
    public:
        static ServerConfig& getInstance(); 
        void registerCommand(const std::string& commandName, std::shared_ptr<Command> command); 
        std::shared_ptr<Command> getCommand(const std::string& commandName) const;
        void setPort(const int& port);
        int getPort() const; 

    private:
        ServerConfig() = default; 
        ~ServerConfig() = default;
        ServerConfig(const ServerConfig&) = delete;
        ServerConfig& operator=(const ServerConfig&) = delete;

        int port = 1234; 
        std::unordered_map<std::string, std::shared_ptr<Command>> commands; 
};


#endif
