#include "client.hpp"

#include <bln_net/utils.hpp>

client::client(bln_net::udp::socket &s)
    : m_socket{s}
{}

void client::echo(std::string s)
{
    const auto n = m_socket.put({m_server, bln_net::to_bytes(std::move(s))});
    std::cout << "[tx] " << n << std::endl;

    const auto p = m_socket.wait();
    std::cout << "[rx] " << p.to_string() << std::endl;
}
