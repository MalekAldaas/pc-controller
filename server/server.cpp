#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

constexpr int PORT = 1234;
constexpr int BUFFER_SIZE = 1024; 
constexpr int BACKLOG = 5;
char buffer[BUFFER_SIZE]; 


int main(){
    int server_fd, client_fd; 
    sockaddr_in server_addr, client_addr; 
    socklen_t client_len = sizeof(client_addr) ; 

    // 1- Create Socket.
    server_fd = socket(AF_INET, SOCK_STREAM, 0); 
    if(server_fd < 0){
        std::cout << "Error creating socket!" << std::endl;
        return 1;
    }

    std::cout << "Socket created successfully" << std::endl ;

    // 2- Bind the socket for a specific ip and port using bind().

    server_addr.sin_family = AF_INET; 
    server_addr.sin_addr.s_addr = INADDR_ANY; 
    server_addr.sin_port = htons(PORT);

    if(bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        std::cout << "Error while creating"; 
        return 1;
    }

    std::cout << "Bind successfully" << std::endl;


    // 3- Listen for coneections 
    
    if (listen(server_fd, BACKLOG) < 0){
        std::cout << "error while listening" << std::endl ;
        return 1;
    }

    std::cout << "Server listen on port " << PORT << std::endl ;

    // 4- Accept a client connection

    client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_len);
    if (client_fd < 0){
        std::cout << "error while accepting" << std::endl;
        return 1;
    }

    std::cout << "Client Connected" << std::endl; 

    // 5- communicat with the client

    while (true) {
    memset(buffer, 0, BUFFER_SIZE); // Clear the buffer before receiving data

    // Wait to receive data from the client
    std::cout << "Waiting to receive data..." << std::endl;
    int bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);

    if (bytes_received < 0) {
        std::cout << "Error receiving data from client" << std::endl;
        break;
    } else if (bytes_received == 0) {
        std::cout << "Client disconnected" << std::endl;
        break;
    } else {
        // Print the received message
        std::cout << "Bytes received: " << bytes_received << std::endl;
        std::cout << "Client: " << buffer << std::endl;

        // Optional: Send acknowledgment back to the client
        std::string response = "Server received: ";
        response += buffer;
        send(client_fd, response.c_str(), response.size(), 0);
       }
    }
    close(client_fd);
    close(server_fd);

    return 0;
}
