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

#ifndef __ASIOLINK_DNS_SERVICE_H
#define __ASIOLINK_DNS_SERVICE_H 1

#include <resolve/resolver_interface.h>

#include <asiolink/io_service.h>

namespace asiolink {

class SimpleCallback;
class DNSLookup;
class DNSAnswer;
class DNSServiceImpl;

///
/// DNSService is the service that handles DNS queries and answers with
/// a given IOService. This class is mainly intended to hold all the
/// logic that is shared between the authoritative and the recursive
/// server implementations. As such, it handles asio, including config
/// updates (through the 'Checkinprovider'), and listening sockets.
/// 
class DNSService {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    DNSService(const DNSService& source);
    DNSService& operator=(const DNSService& source);

public:
    /// \brief The constructor with a specific IP address and port on which
    /// the services listen on.
    ///
    /// \param io_service The IOService to work with
    /// \param port the port to listen on
    /// \param address the IP address to listen on
    /// \param checkin Provider for cc-channel events (see \c SimpleCallback)
    /// \param lookup The lookup provider (see \c DNSLookup)
    /// \param answer The answer provider (see \c DNSAnswer)
    DNSService(IOService& io_service, const char& port,
               const char& address, SimpleCallback* checkin,
               DNSLookup* lookup, DNSAnswer* answer);
    /// \brief The constructor with a specific port on which the services
    /// listen on.
    ///
    /// It effectively listens on "any" IPv4 and/or IPv6 addresses.
    /// IPv4/IPv6 services will be available if and only if \c use_ipv4
    /// or \c use_ipv6 is \c true, respectively.
    ///
    /// \param io_service The IOService to work with
    /// \param port the port to listen on
    /// \param ipv4 If true, listen on ipv4 'any'
    /// \param ipv6 If true, listen on ipv6 'any'
    /// \param checkin Provider for cc-channel events (see \c SimpleCallback)
    /// \param lookup The lookup provider (see \c DNSLookup)
    /// \param answer The answer provider (see \c DNSAnswer)
    DNSService(IOService& io_service, const char& port,
               const bool use_ipv4, const bool use_ipv6,
               SimpleCallback* checkin, DNSLookup* lookup,
               DNSAnswer* answer);
    /// \brief The constructor without any servers.
    ///
    /// Use addServer() to add some servers.
    DNSService(IOService& io_service, SimpleCallback* checkin,
               DNSLookup* lookup, DNSAnswer* answer);
    /// \brief The destructor.
    ~DNSService();
    //@}

    /// \brief Add another server to the service
    void addServer(uint16_t port, const std::string &address);
    void addServer(const char &port, const std::string &address);
    /// \brief Remove all servers from the service
    void clearServers();

    /// \brief Return the native \c io_service object used in this wrapper.
    ///
    /// This is a short term work around to support other BIND 10 modules
    /// that share the same \c io_service with the authoritative server.
    /// It will eventually be removed once the wrapper interface is
    /// generalized.
    asio::io_service& get_io_service() { return io_service_.get_io_service(); }

    /// \brief Return the IO Service Object
    ///
    /// \return IOService object for this DNS service.
    asiolink::IOService& getIOService() { return (io_service_);}

private:
    DNSServiceImpl* impl_;
    IOService& io_service_;
};

}      // namespace asiolink
#endif // __ASIOLINK_DNS_SERVICE_H
