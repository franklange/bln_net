#pragma once

#include <bln_net/udp_socket.hpp>
#include <bln_net/udp_socket_asio.hpp>

#include <cstdint>
#include <thread>

namespace bln_net::udp {

class socket_hb_cli : public socket
{
    using u16 = std::uint16_t;

public:
    socket_hb_cli(u16 rx, timeout t = 1s, u16 bufSize = 1024, u16 queueSize = 32);

    auto put(packet) -> u16 override;
    auto get() -> std::optional<packet> override;

    auto wait() -> packet override;
    auto wait(const timeout&) -> std::optional<packet> override;

    auto port() const -> u16 override;

private:
    void txthread(endpoint);

    socket_asio m_socket;
    std::thread m_txthread;

    const timeout m_timeout;
};

} // namespace bln_net::udp
