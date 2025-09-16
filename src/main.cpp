#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream> // For cout
#include <unistd.h> // For read
#include "../include/TCPAcceptor.hpp"
#include "../include/TCPStream.hpp"

#define DEBUG

// include libft and take this function from there
bool is_int(const char* s) {
    for (int i = 0; s[i]; i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

int main(int argc, char **argv) {
    if ((argc < 2 && argc > 3) || !is_int(argv[1])) {
        std::cerr << "[ERROR] Port is not provided via command line parameters!\n";
        return -1;
    }
    try {
        int port = atoi(argv[1]);
        std::string ip = (argc == 3) ? argv[2] : "";

        TCPAcceptor acceptor(port, ip);
        if (acceptor.start() != 0) {
            throw std::runtime_error("Could not start the server");
        }

        while (true) {
            TCPStream* stream = acceptor.accept();
            if (!stream) {
                throw std::runtime_error("accept() failed");
            }

            char line[256];
            ssize_t len;
            while ((len = stream->receive(line, sizeof(line) - 1)) > 0) {
                line[len] = '\0';
                printf("received - %s\n", line);
                stream->send(line, len); // echo back
            }
            delete stream;
        }
    } catch (const std::exception& e) {
        std::cerr << "Server error: " << e.what() << std::endl;
    } catch(...) {
        std::cerr << "Server error: Unknown error occurred\n" << std::endl;
    }
}