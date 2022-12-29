#include <bln_net/udp_socket_hb_srv.hpp>

#include <algorithm>

namespace bln_net::udp {

namespace {

auto is_heartbeat(const packet& p) -> bool
{
    return p.data.empty();
}

} // namespace anonym

socket_hb_srv::socket_hb_srv(const u16 rx, timeout t, const u16 bufSize, const u16 queueSize)
    : m_socket{rx, bufSize, queueSize}
    , m_rxthread{&socket_hb_srv::rxthread, this}
    , m_gcthread{&socket_hb_srv::gcthread, this, std::move(t)}
{}

auto socket_hb_srv::put(packet p) -> u16
{
    return m_socket.put(std::move(p));
}

auto socket_hb_srv::get() -> std::optional<packet>
{
    return m_socket.get();
}

auto socket_hb_srv::wait() -> packet
{
    return m_packets.wait();
}

auto socket_hb_srv::wait(const timeout& t) -> std::optional<packet>
{
    return m_packets.wait(t);
}

auto socket_hb_srv::port() const -> u16
{
    return m_socket.port();
}

void socket_hb_srv::recv()
{
    auto p = m_socket.wait();

    if (is_heartbeat(p))
    {
        m_heartbeats.beat(p.remote);
        return;
    }

    m_heartbeats.add(p.remote);
    m_packets.put(std::move(p));
}

void socket_hb_srv::pulsecheck()
{
    auto deads = m_heartbeats.check();

    m_heartbeats.trim(deads);

    for (auto& ep : deads)
        m_packets.put({std::move(ep), {}});
}

void socket_hb_srv::rxthread()
{
    while (true)
        recv();
}

void socket_hb_srv::gcthread(const timeout t)
{
    while (true)
    {
        std::this_thread::sleep_for(t);
        pulsecheck();
    }
}

} // namespace bln_net::udp
