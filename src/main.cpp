#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream> // For cout
#include <unistd.h> // For read

#define DEBUG

// include libft and take this function from there
bool is_int(const char* s) {
    for (int i = 0; s[i]; i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

int createServerSocket() {
    // Create a socket (IPv4, TCP)
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cout << "Failed to create socket. errno: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }

    #ifdef DEBUG
    std::cout << "[INFO] Socket has been created.\n";
    #endif

    return sockfd;
}

int main(int argc, char **argv) {
    if (argc != 2 || !is_int(argv[1])) {
        std::cerr << "[ERROR] Port is not provided via command line parameters!\n";
        return -1;
    }
    try {
        int server_socket_fd = createServerSocket();
        #ifdef DEBUG
        std::cout << "Socket FD = " << server_socket_fd << std::endl;
        #endif
        close(server_socket_fd);
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    }
}