#include <bln_net/local_socket_hb.hpp>

#include <algorithm>

namespace bln_net::local {

namespace {

auto is_heartbeat(const packet& p) -> bool
{
    return p.data.empty();
}

} // namespace anonym

socket_hb::socket_hb(std::string p, timeout t, const u16 bufSize, const u16 queueSize)
    : m_socket{std::move(p), bufSize, queueSize}
    , m_rxthread{&socket_hb::rxthread, this}
    , m_txthread{&socket_hb::txthread, this, std::move(t)}
{}

socket_hb::~socket_hb()
{
//    if (m_rxthread.joinable())
//        m_rxthread.join();

//    if (m_txthread.joinable())
//        m_txthread.join();
}

auto socket_hb::put(packet p) -> u16
{
    return m_socket.put(std::move(p));
}

auto socket_hb::get() -> std::optional<packet>
{
    return m_socket.get();
}

auto socket_hb::wait() -> packet
{
    return m_packets.wait();
}

auto socket_hb::wait(const timeout& t) -> std::optional<packet>
{
    return m_packets.wait(t);
}

void socket_hb::recv()
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

void socket_hb::pulsecheck()
{
    auto deads = m_heartbeats.check();

    m_heartbeats.trim(deads);

    for (auto& ep : deads)
        m_packets.put({std::move(ep), {}});
}

void socket_hb::beat()
{
    const auto remotes = m_heartbeats.alive();
    for (const auto& r : remotes)
        m_socket.put({r, {}});
}

void socket_hb::rxthread()
{
    while (true)
        recv();
}

void socket_hb::txthread(const timeout t)
{
    while (true)
    {
        std::this_thread::sleep_for(t);
        pulsecheck();
        beat();
    }
}

} // namespace bln_net::local