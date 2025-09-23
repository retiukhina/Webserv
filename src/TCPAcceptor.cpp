#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include "../include/TCPAcceptor.hpp"

TCPAcceptor::TCPAcceptor(int port, std::string ip)
    : lsd(0)
    , port(port)
    , ip(ip)
    , listening(false)
{}

TCPAcceptor::~TCPAcceptor() {
    if (lsd > 0) {
        close(lsd);
    }
}

int TCPAcceptor::start()
{
    // checks to see if a listening socket already exists
    if (listening == true) {
        return 0;
    }
    // create a listening socket descriptor for TCP/IP
    lsd = socket(PF_INET, SOCK_STREAM, 0);

    // initialize a socket address structure
    struct sockaddr_in address;
    memset(&address, 0, sizeof(address));
    address.sin_family = PF_INET;
    address.sin_port = htons(port);
    // if the server listening IP address has been set,
    // inet_ntop() is called to convert it to a numerical IP address
    // in network byte order
    if (ip.size() > 0) {
        inet_pton(PF_INET, ip.c_str(), &(address.sin_addr));
    }
    else {
        address.sin_addr.s_addr = INADDR_ANY;
    }

    int optval = 1;
    setsockopt(lsd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

    int result = bind(lsd, (struct sockaddr*)&address, sizeof(address));
    if (result != 0) {
        perror("bind() failed");
        return result;
    }
    result = listen(lsd, 5);
    if (result != 0) {
        perror("listen() failed");
        return result;
    }
    listening = true;
    return result;
}

TCPStream* TCPAcceptor::accept()
{
    if (listening == false) {
        return NULL;
    }

    struct sockaddr_in address;
    socklen_t len = sizeof(address);
    memset(&address, 0, sizeof(address));
    int sd = ::accept(lsd, (struct sockaddr*)&address, &len);
    if (sd < 0) {
        perror("accept() failed");
        return NULL;
    }
    return new TCPStream(sd, &address);
}

