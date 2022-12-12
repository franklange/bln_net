#include "server.hpp"

#include <iostream>

server::server(bln_net::udp::socket& s)
    : m_socket{s}
{}

void server::process_request()
{
    auto p = m_socket.wait();
    std::cout << "[rx] " << p.to_string() << std::endl;
    m_socket.put(std::move(p));
}
