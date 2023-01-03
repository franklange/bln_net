#pragma once

#include <bln_net/udp_socket.hpp>

struct client
{
    client(bln_net::udp::socket& s);

    void echo(std::string s);

    bln_net::udp::socket& m_socket;
    bln_net::udp::endpoint m_server{"127.0.0.1", 8000};
};
