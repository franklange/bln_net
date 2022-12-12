#pragma once

#include <bln_net/udp_socket.hpp>

struct server
{
    server(bln_net::udp::socket&);

    void process_request();

    bln_net::udp::socket& m_socket;
};
