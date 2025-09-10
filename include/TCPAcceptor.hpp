#pragma once

#include <string>
#include <netinet/in.h>
#include "TCPStream.hpp"

//TCPAcceptor manages the server listening socket: set up (socket, bind, listen),
// accepts new connections (accept), produces a TCPStream

class TCPAcceptor
{
    int         m_lsd;
    std::string m_address;
    int         m_port;
    bool        m_listening;

  public:
    TCPAcceptor(int port, const char* address="");
    ~TCPAcceptor();

    int        start();
    TCPStream* accept();

  private:
    TCPAcceptor() {}
};