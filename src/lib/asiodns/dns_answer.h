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

#ifndef ASIOLINK_DNS_ANSWER_H
#define ASIOLINK_DNS_ANSWER_H 1

#include <asiolink/io_message.h>
#include <util/buffer.h>
#include <dns/message.h>

namespace isc {
namespace asiodns {

/// \brief The \c DNSAnswer class is an abstract base class for a DNS
/// Answer provider function.
///
/// Specific derived class implementations are hidden within the
/// implementation.  Instances of the derived classes can be called
/// as functions via the operator() interface.  Pointers to these
/// instances can then be provided to the \c IOService class
/// via its constructor.
///
/// A DNS Answer provider function takes answer data that has been obtained
/// from a DNS Lookup provider functon and readies it to be sent to the
/// client.  After it has run, the OutputBuffer object passed to it should
/// contain the answer to the query rendered into wire format.
class DNSAnswer {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non-copyable.
    //@{
private:
    DNSAnswer(const DNSAnswer& source);
    DNSAnswer& operator=(const DNSAnswer& source);
protected:
    /// \brief The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class
    /// should never be instantiated (except as part of a derived class).
    DNSAnswer() {}
public:
    /// \brief The destructor
    virtual ~DNSAnswer() {}
    //@}
    /// \brief The function operator
    ///
    /// This makes its call indirectly via the "self" pointer, ensuring
    /// that the function ultimately invoked will be the one in the derived
    /// class.
    ///
    /// \param io_message The event message to handle
    /// \param query_message The DNS MessagePtr of the original query
    /// \param answer_message The DNS MessagePtr of the answer we are
    /// building
    /// \param buffer Intermediate data results are put here
    virtual void operator()(const asiolink::IOMessage& io_message,
                            isc::dns::MessagePtr query_message,
                            isc::dns::MessagePtr answer_message,
                            isc::util::OutputBufferPtr buffer) const = 0;
};

}      // namespace asiodns
}      // namespace isc
#endif // ASIOLINK_DNS_ANSWER_H
