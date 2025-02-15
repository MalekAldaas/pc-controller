import socket
import sys

def main():
    # Parse command-line arguments for server IP and port
    if len(sys.argv) > 2:
        SERVER_IP = sys.argv[1]
        try:
            SERVER_PORT = int(sys.argv[2])
        except ValueError:
            print("Port must be an integer.")
            sys.exit(1)
    else:
        # Default values if not provided
        SERVER_IP = "192.168.139.130"
        SERVER_PORT = 1234

    # Create and connect the socket
    try:
        print("Creating socket...")
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        print(f"Connecting to {SERVER_IP}:{SERVER_PORT}...")
        client_socket.connect((SERVER_IP, SERVER_PORT))
        print(f"Connected to server {SERVER_IP}:{SERVER_PORT}")
    except Exception as e:
        print("An error occurred:", e)
        sys.exit(1)

    # Define available commands mapped to indices
    commands = {
        "1": "uptime",
        "2": "command2",  # Replace with your actual command
        "3": "command3",  # Replace with your actual command
    }

    while True:
        # Display the command menu
        print("\nAvailable commands:")
        for key, cmd in commands.items():
            print(f"{key}: {cmd}")
        print("0: Exit")

        choice = input("Enter the index of the command: ").strip()

        if choice == "0":
            print("Exiting...")
            break
        elif choice in commands:
            command = commands[choice]
            try:
                print(f"Sending command: {command}")
                client_socket.sendall(command.encode())
                # Wait for and display the server's response
                response = client_socket.recv(1024).decode()
                print("Server response:", response)
            except Exception as e:
                print("Error sending command:", e)
        else:
            print("Invalid choice. Please try again.")

    # Close the connection
    client_socket.close()
    print("Connection closed.")

if __name__ == 'main':
    main()
