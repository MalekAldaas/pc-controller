#include "server.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

constexpr int BUFFER_SIZE = 1024; 
constexpr int BACKLOG = 5;

Server::Server(int port) : port(port), serverSocket(-1) {}

Server::~Server() {
    if (serverSocket != -1) {
        close(serverSocket);
    }
}

bool Server::start() {
    return setupSocket();
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

int Server::acceptClient() {
    sockaddr_in clientAddr;
    socklen_t clientLen = sizeof(clientAddr);
    int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientLen);

    if (clientSocket < 0) {
        std::cerr << "Error accepting client connection.\n";
        return -1;
    } else {
        std::cout << "Client connected.\n";
    }

    return clientSocket;
}

bool Server::receiveCommand(int clientSocket, std::string& command) {
    char buffer[BUFFER_SIZE]{};
    int bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE - 1, 0);

    if (bytesReceived <= 0) {
        std::cerr << "Error receiving data or client disconnected.\n";
        return false;
    }

    buffer[bytesReceived] = '\0';
    command = buffer;
    return true;
}

bool Server::sendResponse(int clientSocket, const std::string& message) {
    int bytesSent = send(clientSocket, message.c_str(), message.size(), 0);
    return bytesSent >= 0;
}

void Server::closeClient(int clientSocket) {
    if (clientSocket >= 0) {
        close(clientSocket);
        std::cout << "Client connection closed." << std::endl;
    }
}

