#include <arpa/inet.h>
#include "../include/TCPStream.hpp"

// The constructor stores the connected socket descriptor then converts
// the socket information structure fields to a peer IP address string and peer TCP port.
TCPStream::TCPStream(int sd, struct sockaddr_in* address) : sd(sd) {
    char ip[50];
    inet_ntop(PF_INET, (struct in_addr*)&(address->sin_addr.s_addr),
              ip, sizeof(ip)-1);
    peerIP = ip;
    peerPort = ntohs(address->sin_port);
}

// The destructor closes the connection.
TCPStream::~TCPStream()
{
    close(sd);
}

ssize_t TCPStream::send(char* buffer, size_t len) {
    return ::send(sd, buffer, len, 0);
}

ssize_t TCPStream::receive(char* buffer, size_t len) {
    return ::recv(sd, buffer, len, 0);
}