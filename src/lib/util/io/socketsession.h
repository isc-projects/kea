// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef __SOCKETSESSION_H_
#define __SOCKETSESSION_H_ 1

#include <string>

#include <boost/noncopyable.hpp>

#include <exceptions/exceptions.h>

namespace isc {
namespace util {
namespace io {

class SocketSessionError: public Exception {
public:
    SocketSessionError(const char *file, size_t line, const char *what):
        isc::Exception(file, line, what) {}
};

class SocketSessionForwarder : boost::noncopyable {
public:
    // Note about SIGPIPE.  Assuming this class is not often instantiated
    // (so the overhead of signal setting should be marginal) and could also be
    // instantiated by multiple threads, it always set the filter.
    explicit SocketSessionForwarder(const std::string& unix_file);

    ~SocketSessionForwarder();

    void connectToReceptor();

    void close();

    void push(int sock, int family, int sock_type, int protocol,
              const struct sockaddr& local_end,
              const struct sockaddr& remote_end,
              const void* data, size_t data_len);

private:
    struct ForwarderImpl;
    ForwarderImpl* impl_;
};

class SocketSession {
public:
    SocketSession(int sock, int family, int type, int protocol,
                  const sockaddr* local_end, const sockaddr* remote_end,
                  size_t data_len, const void* data);
    int getSocket() const { return (sock_); }
    int getFamily() const { return (family_); }
    int getType() const { return (type_); }
    int getProtocol() const { return (protocol_); }
    const sockaddr& getLocalEndpoint() const { return (*local_end_); }
    const sockaddr& getRemoteEndpoint() const { return (*remote_end_); }
    const void* getData() const { return (data_); }
    size_t getDataLength() const { return (data_len_); }

private:
    const int sock_;
    const int family_;
    const int type_;
    const int protocol_;
    const sockaddr* local_end_;
    const sockaddr* remote_end_;
    const size_t data_len_;
    const void* const data_;
};

class SocketSessionReceptor : boost::noncopyable {
public:
    explicit SocketSessionReceptor(int fd);
    ~SocketSessionReceptor();
    SocketSession pop();

private:
    struct ReceptorImpl;
    ReceptorImpl* impl_;
};

}
}
}

#endif  // __SOCKETSESSION_H_

// Local Variables:
// mode: c++
// End:
