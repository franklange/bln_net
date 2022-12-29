#include <bln_net/udp_socket_hb_cli.hpp>

namespace bln_net::udp {

socket_hb_cli::socket_hb_cli(u16 rx, timeout t, u16 bs, u16 qs)
    : m_socket{rx, bs, qs}
    , m_timeout{std::move(t)}
{}

auto socket_hb_cli::put(packet p) -> u16
{
    if (!m_txthread.joinable())
        m_txthread = std::thread{&socket_hb_cli::txthread, this, p.remote};

    return m_socket.put(std::move(p));
}

auto socket_hb_cli::get() -> std::optional<packet>
{
    return m_socket.get();
}

auto socket_hb_cli::wait() -> packet
{
    return m_socket.wait();
}

auto socket_hb_cli::wait(const timeout& t) -> std::optional<packet>
{
    return m_socket.wait(t);
}

auto socket_hb_cli::port() const -> u16
{
    return m_socket.port();
}

void socket_hb_cli::txthread(const endpoint srv)
{
    while (true)
    {
        std::this_thread::sleep_for(m_timeout);
        m_socket.put({srv, {}});
    }
}

} // namespace bln_net::udp
