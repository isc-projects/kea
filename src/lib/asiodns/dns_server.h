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

#ifndef __ASIOLINK_DNS_SERVER_H
#define __ASIOLINK_DNS_SERVER_H 1

#include <asiolink/io_message.h>

namespace isc {
namespace asiodns {

/// \brief The \c DNSServer class is a wrapper (and base class) for
/// classes which provide DNS server functionality.
///
/// The classes derived from this one, \c TCPServer and \c UDPServer,
/// act as the interface layer between clients sending queries, and
/// functions defined elsewhere that provide answers to those queries.
/// Those functions are described in more detail below under
/// \c SimpleCallback, \c DNSLookup, and \c DNSAnswer.
///
/// Notes to developers:
/// When constructed, this class (and its derived classes) will have its
/// "self_" member set to point to "this".  Objects of this class (as
/// instantiated through a base class) are sometimes passed by
/// reference (as this superclass); calls to methods in the base
/// class are then rerouted via this pointer to methods in the derived
/// class.  This allows code from outside asiodns, with no specific
/// knowledge of \c TCPServer or \c UDPServer, to access their methods.
///
/// This class is both assignable and copy-constructable.  Its subclasses
/// use the "stackless coroutine" pattern, meaning that it will copy itself
/// when "forking", and that instances will be posted as ASIO handler
/// objects, which are always copied.
///
/// Because these objects are frequently copied, it is recommended
/// that derived classes be kept small to reduce copy overhead.
class DNSServer {
protected:
    ///
    /// \name Constructors and destructors
    ///
    /// This is intentionally defined as \c protected, as this base class
    /// should never be instantiated except as part of a derived class.
    //@{
    DNSServer() {
        self_ = this;
    }
public:
    /// \brief The destructor
    virtual ~DNSServer() {}
    //@}

    ///
    /// \name Class methods
    ///
    /// These methods all make their calls indirectly via the "self_"
    /// pointer, ensuring that the functions ultimately invoked will be
    /// the ones in the derived class.  This makes it possible to pass
    /// instances of derived classes as references to this base class
    /// without losing access to derived class data.
    ///
    //@{
    /// \brief The funtion operator
    virtual void operator()(asio::error_code ec = asio::error_code(),
                            size_t length = 0)
    {
        (*self_)(ec, length);
    }

    /// \brief Stop current running server
    virtual void stop() { self_->stop();}

    /// \brief Resume processing of the server coroutine after an
    /// asynchronous call (e.g., to the DNS Lookup provider) has completed.
    ///
    /// \param done If true, this signals the system there is an answer
    ///             to return.
    virtual void resume(const bool done) { self_->resume(done); }

    /// \brief Returns a pointer to a clone of this DNSServer object.
    ///
    /// When a \c DNSServer object is copied or assigned, the result will
    /// normally be another \c DNSServer object containing a copy
    /// of the original "self_" pointer.  Calling clone() guarantees
    /// that the underlying object is also correctly copied.
    ///
    /// \return A deep copy of this DNSServer object
    virtual DNSServer* clone() { return (self_->clone()); }
    //@}

    /// \brief Set timeout for incoming TCP connections
    ///
    /// Since this value is not relevant for every type of DNSServer
    /// (like UDPServer), it has a no-op default implementation.
    /// It is in the base class because the AuthSrv's DNSService has
    /// no direct access to the derived API's after initialization,
    /// and it does need to update running servers if the timeout
    /// setting is changed.
    ///
    /// \param timeout The timeout in milliseconds
    virtual void setTCPRecvTimeout(size_t) {}

protected:
    /// \brief Lookup handler object.
    ///
    /// This is a protected class; it can only be instantiated
    /// from within a derived class of \c DNSServer.
    ///
    /// A server object that has received a query creates an instance
    /// of this class and scheudles it on the ASIO service queue
    /// using asio::io_service::post().  When the handler executes, it
    /// calls the asyncLookup() method in the server object to start a
    /// DNS lookup.  When the lookup is complete, the server object is
    /// scheduled to resume, again using io_service::post().
    ///
    /// Note that the calling object is copied into the handler object,
    /// not referenced.  This is because, once the calling object yields
    /// control to the handler, it falls out of scope and may disappear
    template <typename T>
    class AsyncLookup {
    public:
        AsyncLookup(T& caller) : caller_(caller) {}
        void operator()() { caller_.asyncLookup(); }
    private:
        T caller_;
    };

    /// \brief Carries out a DNS lookup.
    ///
    /// This function calls the \c DNSLookup object specified by the
    /// DNS server when the \c IOService was created, passing along
    /// the details of the query and a pointer back to the current
    /// server object.  It is called asynchronously via the AsyncLookup
    /// handler class.
    virtual void asyncLookup() { self_->asyncLookup(); }

private:
    DNSServer* self_;
};


} // namespace asiodns
} // namespace isc
#endif // __ASIOLINK_DNS_SERVER_H
