#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <thread>
#include <vector>
#include <mutex>

class Server {
public:
    Server(int port);
    ~Server();

    bool start();                  
    void handleClient(int clientSocket);

private:
    int port;                      
    int serverSocket;              
    std::vector<std::thread> clientThreads;
    bool setupSocket();            
};

#endif
