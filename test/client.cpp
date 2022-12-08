#include "client.hpp"

#include <bln_net/utils.hpp>

client::client(bln_net::udp::socket &s)
    : m_socket{s}
{}

void client::echo(const std::string& s)
{
    m_socket.put({m_server, bln_net::to_bytes(s)});
    std::cout << "[tx] " << s << std::endl;

    const auto [_, reply] = m_socket.wait();
    std::cout << "[rx] " << bln_net::to_string(reply) << std::endl;
}
