#include <iostream>
#include <cstdlib>  
#include "server.h"
#include "server_config.h"

int main(int argc, char* argv[]) {
    int port = 1234; 
    
    if (argc > 1) {
        try {
            port = std::stoi(argv[1]);
            if (port < 0 || port > 65535) {
                throw std::out_of_range("Invalid port number");
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Invalid port number: " << e.what() << std::endl;
            return 1;
        }
    }
    
    ServerConfig &serverConfig = ServerConfig::getInstance(); 
    serverConfig.initilizeCommands();
    Server server(port);
    if (!server.start()) {
        return 1;
    }
    return 0;
}
