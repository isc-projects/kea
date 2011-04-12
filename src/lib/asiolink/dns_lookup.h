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

#ifndef __ASIOLINK_DNS_LOOKUP_H
#define __ASIOLINK_DNS_LOOKUP_H 1

#include <asiolink/io_message.h>
#include <asiolink/dns_server.h>
#include <util/io/buffer.h>
#include <dns/message.h>

namespace asiolink {

/// \brief The \c DNSLookup class is an abstract base class for a DNS
/// Lookup provider function.
///
/// Specific derived class implementations are hidden within the
/// implementation.  Instances of the derived classes can be called
/// as functions via the operator() interface.  Pointers to these
/// instances can then be provided to the \c IOService class
/// via its constructor.
///
/// A DNS Lookup provider function obtains the data needed to answer
/// a DNS query (e.g., from authoritative data source, cache, or upstream
/// query).  After it has run, the OutputBuffer object passed to it
/// should contain the answer to the query, in an internal representation.
class DNSLookup {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    DNSLookup(const DNSLookup& source);
    DNSLookup& operator=(const DNSLookup& source);
protected:
    /// \brief The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class
    /// should never be instantiated (except as part of a derived class).
    DNSLookup() : self_(this) {}
public:
    /// \brief The destructor
    virtual ~DNSLookup() {}
    //@}
    /// \brief The function operator
    ///
    /// This makes its call indirectly via the "self" pointer, ensuring
    /// that the function ultimately invoked will be the one in the derived
    /// class.
    ///
    /// \param io_message The event message to handle
    /// \param message The DNS MessagePtr that needs handling
    /// \param answer_message The final answer will be constructed in
    ///                       this MessagePtr
    /// \param buffer The final answer is put here
    /// \param server DNSServer object to use
    virtual void operator()(const IOMessage& io_message,
                            isc::dns::MessagePtr message,
                            isc::dns::MessagePtr answer_message,
                            isc::util::io::OutputBufferPtr buffer,
                            DNSServer* server) const
    {
        (*self_)(io_message, message, answer_message, buffer, server);
    }
private:
    DNSLookup* self_;
};

}      // namespace asiolink
#endif // __ASIOLINK_DNS_LOOKUP_H
