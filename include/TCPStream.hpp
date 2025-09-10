#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

// TCPStream class manages a connected socket (read/write (recv, send)), 
// provides peer info (IP, port), closes automatically in destructor

class TCPStream
{
    int             m_sd;
    std::string     m_peerIP;
    int             m_peerPort;

  public:
    friend class TCPConnector;

    ~TCPStream();

    ssize_t send(char* buffer, size_t len);
    ssize_t receive(char* buffer, size_t len);

    std::string getPeerIP();
    int getPeerPort();

  private:
    TCPStream(int sd, struct sockaddr_in* address);
    TCPStream();
    TCPStream(const TCPStream& stream);
};