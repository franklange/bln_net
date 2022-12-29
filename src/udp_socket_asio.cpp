#include <bln_net/udp_socket_asio.hpp>
#include <bln_net/utils.hpp>

namespace bln_net::udp {

namespace {

template <typename E>
auto to_boost(E&& e) -> ip::udp::endpoint
{
    return {ip::address::from_string(std::forward<E>(e).addr), e.port};
}

auto from_boost(const ip::udp::endpoint& e) -> endpoint
{
    return {e.address().to_string(), e.port()};
}

} // namespace anonym

socket_asio::socket_asio(const u16 rx, const u16 bufSize, const u16 queueSize)
    : m_queue{queueSize}
    , m_reader{&socket_asio::read, this}
{
    m_buffer.resize(bufSize);

    m_socket.set_option(ip::udp::socket::reuse_address(true));
    m_socket.bind({ip::udp::v4(), rx});
}

socket_asio::~socket_asio()
{
    m_io.stop();

    if (m_reader.joinable())
        m_reader.join();
}

auto socket_asio::put(packet p) -> u16
{
    const spinlock l{m_txlock};
    return m_socket.send_to(buffer(std::move(p.data)), to_boost(std::move(p.remote)));
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

auto socket_asio::port() const -> u16
{
    return m_socket.local_endpoint().port();
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

    m_queue.put({from_boost(m_sender), bytes{m_buffer.begin(), m_buffer.begin() + n}});
    listen();
}

} // namespace bln_net::udp
