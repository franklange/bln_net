#pragma once

#include <bln_net/types.hpp>
#include <bln_net/udp_socket.hpp>
#include <bln_queue/msg_queue.hpp>

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/udp.hpp>

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <thread>

namespace bln_net::udp {

using namespace boost::asio;

class socket_asio : public socket
{
    using u16 = std::uint16_t;
    using u32 = std::uint32_t;

    using queue = bln_queue::msg_queue<packet>;
    using guard = executor_work_guard<io_context::executor_type>;

public:
    socket_asio(u16 rx, u16 bufSize = 1024, u16 queueSize = 32);
    ~socket_asio();

    auto put(packet&&) -> u32 override;
    auto put(const packet&) -> u32 override;

    auto get() -> std::optional<packet> override;

    auto wait() -> packet override;
    auto wait(const timeout&) -> std::optional<packet> override;

    auto port() const -> u16 override;

private:
    void read();
    void listen();
    void handle_read(error, u32);

    queue m_queue;
    bytes m_buffer;

    io_context m_io;
    ip::udp::socket m_socket{m_io, ip::udp::v4()};
    ip::udp::endpoint m_sender;

    mutex m_txlock;
    std::thread m_reader;
};

} // namespace bln_net::udp
