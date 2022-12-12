# bln_net
A small socket library.

### Dependencies
* bln_queue
* Boost::asio

### Server
```c++
#include <bln_net/udp_socket_asio.hpp>
#include <iostream>

auto main() -> int
{
    bln_net::udp::socket_asio socket{8000};

    while (true)
    {
        auto packet = socket.wait();
        std::cout << "[rx] " << packet.to_string() << std::endl;
        // [rx] [127.0.0.1:9000|b'2]

        socket.put(std::move(packet));
    }

    return 0;
}
```

### Client
```c++
#include <bln_net/udp_socket_asio.hpp>
#include <bln_net/utils.hpp>

auto main() -> int
{
    bln_net::udp::socket_asio socket{9000};

    socket.put({{"127.0.0.1", 8000}, bln_net::to_bytes("hi")});

    const auto packet = socket.wait();
    std::cout << "[rx] " << packet.to_string() << std::endl;
    // [rx] [127.0.0.1:8000|b'2]

    return 0;
}
```