#pragma once

#include <bln_net/heartbeats.hpp>
#include <bln_net/local_socket.hpp>
#include <bln_net/local_socket_asio.hpp>

#include <cstdint>
#include <thread>

namespace bln_net::local {

class socket_hb : public socket
{
    using u16 = std::uint16_t;
    using guard = executor_work_guard<io_context::executor_type>;
    using queue = bln_queue::msg_queue<packet>;
    using beats = heartbeats<local::endpoint>;

public:
    socket_hb(std::string, timeout t = 1s, u16 bufSize = 1024, u16 queueSize = 32);
    ~socket_hb();

    auto put(packet) -> u16 override;
    auto get() -> std::optional<packet> override;

    auto wait() -> packet override;
    auto wait(const timeout&) -> std::optional<packet> override;

private:
    void recv();
    void pulsecheck();
    void beat();

    void rxthread();
    void txthread(timeout t);

    socket_asio m_socket;

    queue m_packets;
    beats m_heartbeats;

    std::thread m_rxthread;
    std::thread m_txthread;
};

} // namespace bln_net::udp
