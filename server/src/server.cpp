#include "server.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <memory>
#include "server_config.h"

constexpr int BUFFER_SIZE = 1024; 
constexpr int BACKLOG = 5;

Server::Server(int port) : port(port), serverSocket(-1) {}

Server::~Server() {
    if (serverSocket != -1) {
        close(serverSocket);
    }
    for (auto& t : clientThreads) {
        if (t.joinable()) {
            t.join();
        }
    }
}

bool Server::start() {
    if (!setupSocket()) return false;
    
    while (true) {
        std::cout << "Waiting for a client...\n";
        sockaddr_in clientAddr;
        socklen_t clientLen = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientLen);

        if (clientSocket < 0) {
            std::cerr << "Error accepting client connection.\n";
            continue;
        }
        
        std::cout << "Client connected.\n";
        clientThreads.emplace_back(&Server::handleClient, this, clientSocket);
    }
}

bool Server::setupSocket() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Error creating socket!\n";
        return false;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Error binding socket!\n";
        return false;
    }

    if (listen(serverSocket, BACKLOG) < 0) {
        std::cerr << "Error listening on socket!\n";
        return false;
    }

    std::cout << "Server listening on port " << port << std::endl;
    return true;
}

void Server::handleClient(int clientSocket) {
    char buffer[BUFFER_SIZE];
    ServerConfig& serverConfig = ServerConfig::getInstance();

    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);

        if (bytesReceived <= 0) {
            std::cerr << "Client disconnected or error receiving data.\n";
            break;
        }

        std::string commandName(buffer);
        std::cout << "Command received: " << commandName << "\n";

        std::shared_ptr<Command> command = serverConfig.getCommand(commandName);
        std::string response = command ? command->execute().getStatus() : "Unknown Command: " + commandName;
        send(clientSocket, response.c_str(), response.size(), 0);
    }

    close(clientSocket);
    std::cout << "Client connection closed.\n";
}
