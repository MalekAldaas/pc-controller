#ifndef SERVER_H
#define SERVER_H

#include <string>

class Server {
public:
    Server(int port);
    ~Server();

    bool start();                 
    int acceptClient();           
    bool receiveCommand(int clientSocket, std::string& command);  
    bool sendResponse(int clientSocket, const std::string& message); 
    void closeClient(int clientSocket);  

private:
    int port;                     
    int serverSocket;              
    bool setupSocket();             
};

#endif

