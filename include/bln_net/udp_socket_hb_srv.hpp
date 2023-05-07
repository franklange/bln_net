#pragma once

#include <bln_net/heartbeats.hpp>
#include <bln_net/udp_socket.hpp>
#include <bln_net/udp_socket_asio.hpp>

#include <boost/asio/io_context.hpp>
#include <boost/asio/steady_timer.hpp>

#include <cstdint>
#include <thread>

namespace bln_net::udp {

class socket_hb_srv : public socket
{
    using u16 = std::uint16_t;
    using guard = executor_work_guard<io_context::executor_type>;
    using queue = bln_queue::msg_queue<packet>;
    using beats = heartbeats<udp::endpoint>;

public:
    socket_hb_srv(u16 rx, timeout t = 5s, u16 bufSize = 1024, u16 queueSize = 32);

    auto put(packet) -> u16 override;
    auto get() -> std::optional<packet> override;

    auto wait() -> packet override;
    auto wait(const timeout&) -> std::optional<packet> override;

    auto port() const -> u16 override;

private:
    void recv();
    void pulsecheck();

    void rxthread();
    void gcthread(timeout t);

    socket_asio m_socket;

    queue m_packets;
    beats m_heartbeats;

    std::thread m_rxthread;
    std::thread m_gcthread;
};

} // namespace bln_net::udp
