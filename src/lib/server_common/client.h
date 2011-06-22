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

#ifndef __CLIENT_H
#define __CLIENT_H 1

#include <string>
#include <ostream>

#include <boost/noncopyable.hpp>

#include <acl/ip_check.h>

#include <asiolink/io_message.h>

namespace isc {
namespace acl {
struct IPAddress;
}

namespace server_common {

/// May have to be named something like "DNSClient"
/// should be reusable
/// may want to use different subclasses for auth clients and resolver clients
class Client : boost::noncopyable {
public:
    explicit Client(const isc::asiolink::IOMessage& request_message);
    ~Client();
    const isc::asiolink::IOEndpoint& getRequestSourceEndpoint() const;

    // convenience shortcut
    const isc::acl::IPAddress& getRequestSourceIPAddress() const;

    std::string toText() const;

private:
    struct ClientImpl;
    ClientImpl* impl_;
};

/// \brief Insert the \c Client as a string into stream.
///
/// This method convert \c client into a string and inserts it into the
/// output stream \c os.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param edns A reference to an \c Client object output by the operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream& operator<<(std::ostream& os, const Client& client);
}

namespace acl {
template <>
bool IPCheck<server_common::Client>::matches(
    const server_common::Client& client) const;
}
}

#endif  // __CLIENT_H

// Local Variables:
// mode: c++
// End:
