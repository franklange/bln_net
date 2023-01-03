#pragma once

#include <bln_net/types.hpp>
#include <bln_net/local_socket.hpp>
#include <bln_queue/msg_queue.hpp>

#include <boost/asio/io_context.hpp>
#include <boost/asio/local/datagram_protocol.hpp>

#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <thread>

namespace bln_net::local {

using namespace boost::asio;

class socket_asio : public socket
{
    using u16 = std::uint16_t;

    using dgram = boost::asio::local::datagram_protocol;
    using queue = bln_queue::msg_queue<packet>;
    using guard = executor_work_guard<io_context::executor_type>;

public:
    socket_asio(std::string, u16 bufSize = 1024, u16 queueSize = 32);
    ~socket_asio();

    auto put(packet) -> u16 override;
    auto get() -> std::optional<packet> override;

    auto wait() -> packet override;
    auto wait(const timeout&) -> std::optional<packet> override;

    auto measured_wait() -> packet;
    auto measured_wait(const timeout&) -> std::optional<packet>;

    auto last_wait() const -> duration;

private:
    void read();
    void listen();
    void handle_read(error, u16);

    queue m_queue;
    bytes m_buffer;

    io_context m_io;

    dgram::endpoint m_path;
    dgram::endpoint m_sender;
    dgram::socket m_socket;

    duration m_lastwait{0};

    mutex m_txlock;
    std::thread m_reader;
};

} // namespace bln_net::local
