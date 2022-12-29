#include <bln_net/local_socket_asio.hpp>
#include <bln_net/utils.hpp>

#include <unistd.h>

namespace bln_net::local {

using dgram = boost::asio::local::datagram_protocol;

namespace {

auto make_socket(io_context& c, dgram::endpoint& p) -> dgram::socket
{
    ::unlink(p.path().c_str());
    return {c, p};
}

} // namespace anonym

socket_asio::socket_asio(const std::string& p, const u16 bufSize, const u16 queueSize)
    : m_queue{queueSize}
    , m_buffer(bufSize)
    , m_path{p}
    , m_socket{make_socket(m_io, m_path)}
    , m_reader{&socket_asio::read, this}
{}

socket_asio::~socket_asio()
{
    m_io.stop();

    if (m_reader.joinable())
        m_reader.join();

    ::unlink(m_path.path().c_str());
}

auto socket_asio::put(packet p) -> u16
{
    const spinlock l{m_txlock};
    return m_socket.send_to(buffer(std::move(p.data)), {std::move(p.remote)});
}

auto socket_asio::get() -> std::optional<packet>
{
    return m_queue.get();
}

auto socket_asio::wait() -> packet
{
    return m_queue.wait();
}

auto socket_asio::wait(const timeout& t) -> std::optional<packet>
{
    return m_queue.wait(t);
}

auto socket_asio::measured_wait() -> packet
{
    const auto s = clock::now();
    const auto p = m_queue.wait();

    m_lastwait = to_duration(clock::now() - s);

    return p;
}

auto socket_asio::measured_wait(const timeout& t) -> std::optional<packet>
{
    const auto s = clock::now();
    const auto p = m_queue.wait(t);

    m_lastwait = p ? to_duration(clock::now() - s) : t;

    return p;
}

auto socket_asio::last_wait() const -> duration
{
    return m_lastwait;
}

void socket_asio::read()
{
    guard w{m_io.get_executor()};
    listen();
    m_io.run();
}

void socket_asio::listen()
{
    m_socket.async_receive_from(buffer(m_buffer), m_sender, [&](const auto e, const auto n) {
        handle_read(e, n); }
    );
}

void socket_asio::handle_read(const error e, const u16 n)
{
    if (e)
        return;

    m_queue.put({m_sender.path(), bytes{m_buffer.begin(), m_buffer.begin() + n}});
    listen();
}

} // namespace bln_net::local
