# UVIRC

A modern, event-driven Internet Relay Chat (IRC) server built with **libuv**.

UVIRC is a lightweight IRC server that combines the simplicity of the IRC protocol with the high-performance asynchronous I/O capabilities of libuv. It is designed as both a production-ready server and a reference implementation for developers interested in networking, event loops, and protocol implementation in C.

---

## Features

* Event-driven architecture powered by libuv
* Non-blocking TCP networking
* Multi-client support
* RFC-inspired IRC command handling
* Channels with user membership management
* Nickname registration
* User registration
* Private messaging
* Channel messaging
* User modes
* Channel modes
* Server notices
* Configurable server settings
* Graceful client disconnect handling
* Cross-platform support

  * Linux
  * macOS
  * Windows
* Minimal external dependencies
* Clean modular architecture
* Easily extensible command system

---

## Why libuv?

libuv provides a high-performance asynchronous programming model used by projects such as Node.js. It offers:

* Cross-platform event loops
* Asynchronous networking
* Timers
* DNS resolution
* File system APIs
* Thread pools
* Signal handling

Using libuv allows UVIRC to scale efficiently while keeping the implementation relatively simple.

---

## Architecture

```
                   +------------------+
                   |   TCP Listener   |
                   +--------+---------+
                            |
                     Accept Connection
                            |
                 +----------v-----------+
                 |    Client Session    |
                 +----------+-----------+
                            |
                  Read IRC Line (async)
                            |
                 +----------v-----------+
                 | IRC Command Parser   |
                 +----------+-----------+
                            |
          +----------------+----------------+
          |                |                |
     Registration      Channel Logic   Messaging
          |                |                |
          +----------------+----------------+
                           |
                    Response Generator
                           |
                     Async TCP Write
```

---

## Project Layout

```
.
├── include/
│   ├── server.h
│   ├── client.h
│   ├── channel.h
│   ├── parser.h
│   ├── commands.h
│   └── config.h
│
├── src/
│   ├── main.c
│   ├── server.c
│   ├── client.c
│   ├── parser.c
│   ├── channel.c
│   ├── command_dispatch.c
│   ├── commands/
│   │   ├── nick.c
│   │   ├── user.c
│   │   ├── join.c
│   │   ├── part.c
│   │   ├── privmsg.c
│   │   ├── ping.c
│   │   └── quit.c
│   └── utils.c
│
├── tests/
├── docs/
├── examples/
├── CMakeLists.txt
└── README.md
```

---

## Building

### Requirements

* C11 compatible compiler
* CMake 3.18+
* libuv

### Linux

```bash
mkdir build
cd build

cmake ..
make
```

### Windows

```bash
mkdir build
cd build

cmake ..
cmake --build . --config Release
```

---

## Running

```bash
./uvirc
```

or

```bash
./uvirc --config server.conf
```

Example output:

```
[INFO] UVIRC Server v1.0
[INFO] Listening on 0.0.0.0:6667
```

---

## Connecting

Using a traditional IRC client:

```
Server: localhost
Port: 6667
SSL: Disabled
```

Or using netcat:

```bash
nc localhost 6667
```

Example session:

```
NICK alice
USER alice 0 * :Alice Example

JOIN #general

PRIVMSG #general :Hello everyone!
```

---

## Supported Commands

| Command | Description                      |
| ------- | -------------------------------- |
| NICK    | Set nickname                     |
| USER    | Register user                    |
| JOIN    | Join a channel                   |
| PART    | Leave a channel                  |
| QUIT    | Disconnect                       |
| PRIVMSG | Send private or channel messages |
| NOTICE  | Send notices                     |
| LIST    | List channels                    |
| WHO     | Query users                      |
| WHOIS   | User information                 |
| MODE    | User/channel modes               |
| PING    | Keepalive                        |
| PONG    | Ping response                    |
| TOPIC   | Set or retrieve channel topic    |
| INVITE  | Invite users                     |
| KICK    | Remove users from a channel      |

---

## Networking Model

Each connected client owns:

* a libuv TCP handle
* a read buffer
* a write queue
* parser state
* registration state
* channel membership list

The server itself owns:

* event loop
* TCP listener
* global client registry
* channel registry
* timers
* configuration

No thread is required for each client. All networking occurs inside the libuv event loop.

---

## Connection Lifecycle

```
Accept

↓

Allocate Client

↓

Begin Async Read

↓

Receive IRC Line

↓

Parse Command

↓

Execute Handler

↓

Generate Replies

↓

Async Write

↓

Repeat

↓

Disconnect

↓

Cleanup Resources
```

---

## Command Processing

Incoming IRC messages are processed in several stages:

1. Receive bytes from the socket.
2. Accumulate data until a complete IRC line is available.
3. Parse the command and parameters.
4. Validate registration and permissions.
5. Dispatch to the appropriate command handler.
6. Generate one or more responses.
7. Queue asynchronous writes back to the client.

This separation keeps parsing, validation, business logic, and networking independent.

---

## Memory Management

The server emphasizes predictable memory usage:

* Explicit ownership of allocated objects
* Reference-safe client and channel relationships
* Cleanup on disconnect
* Reusable read/write buffers where practical
* Minimal heap allocations during normal operation

---

## Error Handling

The server reports:

* Invalid commands
* Unknown commands
* Missing parameters
* Nickname collisions
* Permission errors
* Registration failures
* Channel errors
* Network failures

Whenever possible, numeric IRC replies are returned in accordance with established IRC conventions.

---

## Configuration

Example configuration:

```
listen = 0.0.0.0
port = 6667

server_name = UVIRC

max_clients = 2048

ping_timeout = 120

motd = motd.txt
```

---

## Logging

Example log output:

```
[INFO] Client connected

[INFO] alice registered

[INFO] alice joined #general

[INFO] alice -> #general

[INFO] Client disconnected
```

---

## Testing

Recommended testing methods:

* Manual IRC client testing
* Integration tests
* Command parser unit tests
* Load testing with multiple concurrent clients
* Long-running stability tests
* Memory leak detection with AddressSanitizer or Valgrind

---

## Performance Goals

Designed to support:

* Thousands of simultaneous TCP connections
* Low memory overhead per client
* Efficient asynchronous writes
* Minimal blocking operations
* Fast command dispatch

Actual performance depends on hardware, operating system, compiler optimizations, and configuration.

---

## Roadmap

Future improvements may include:

* TLS support
* SASL authentication
* IRCv3 capability negotiation
* IPv6 enhancements
* WebSocket transport
* Server-to-server federation
* Services integration
* Rate limiting
* Operator commands
* Plugin architecture
* Metrics and observability
* Persistent channel state

---

## Contributing

Contributions are welcome.

Please:

* Keep code modular.
* Follow the project's coding style.
* Write tests for new functionality.
* Document new commands and configuration options.
* Ensure the project builds on all supported platforms.

---

## License

This project is released under the MIT License.

See the `LICENSE` file for details.

---

## Acknowledgements

* The libuv developers for the asynchronous runtime.
* The IRC community for decades of protocol evolution.
* Contributors, testers, and users who help improve the project.

