#include <iostream>
#include <cstdlib>  
#include "server.h"
#include "server_config.h"
#include "command.h"
#include "command_status.h"
#include "uptime_command.h" 

int main(int argc, char* argv[]) {
    // default port
    int port = 1234; 
    
    if (argc > 1) {
        try {
            port = std::stoi(argv[1]) ;
            if (port < 0 || port > 65535) {
                throw std::out_of_range("please provide a valid port number between 0 and 65535.") ;
                return 1;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Invalid port number" << e.what() << std::endl ;
        }
    }
    
    if(argc > 2) {
        std::cout << "You have provided many arguments, only the first argument is considered:"
                      << port << "\n";
    } 
    // ServerConfig is a single tone class

    ServerConfig& serverConfig = ServerConfig::getInstance(); 
    serverConfig.initilizeCommands(); 

    Server server(port);
    if (!server.start()) {
        return 1;
    }

    while (true) {
        int clientSocket = server.acceptClient(); 
        if (clientSocket < 0) {
            std::cerr << "Error accepting client" << std::endl ;
            continue ;
        }
        std::string commandName; 

        if (!server.receiveCommand(clientSocket, commandName)) {
            continue; 
        }
        
        std::shared_ptr<Command> command = serverConfig.getCommand(commandName); 
        if (command == nullptr) {
            server.sendResponse(clientSocket, "Unknown Command: " + commandName); 
        }
        else {
            CommandStatus status = command->execute(); 
            server.sendResponse(clientSocket, status.getStatus()) ;
        }
    }
    return 0;
}

