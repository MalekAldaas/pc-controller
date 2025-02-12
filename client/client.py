import socket

SERVER_IP = "192.168.139.130"
SERVER_PORT = 1234

def main():
    try:
        print("Creating socket...")
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        
        print(f"Connecting to {SERVER_IP}:{SERVER_PORT}...")
        client_socket.connect((SERVER_IP, SERVER_PORT))
        print(f"Connected to server {SERVER_IP}:{SERVER_PORT}")

        while True:
            message = input("Enter message to send (or 'exit' to quit): ")
            if message.lower() == "exit":
                print("Exiting...")
                break

            # Send message to server
            print(f"Sending message: {message}")
            client_socket.sendall(message.encode())  # Send the message
            print("Message sent!")  # Debug confirmation
            
            # Optional: Receive server's response
            try:
                response = client_socket.recv(1024).decode()
                print(f"Server response: {response}")
            except Exception as e:
                print(f"No response received from server: {e}")

        client_socket.close()
        print("Connection closed.")

    except Exception as e:
        print(f"An error occurred: {e}")

main()
