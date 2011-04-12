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

#ifndef __SCAN_H
#define __SCAN_H

#include <stdint.h>

#include <boost/scoped_ptr.hpp>

#include <config.h>

#include <asiolink/io_fetch.h>
#include <asiolink/io_service.h>
#include <dns/buffer.h>

#include "command_options.h"

namespace isc {
namespace badpacket {

/// \brief Field Scan
///
/// This class implements a field scan.  Given a CommandOptions object, it
/// will cycle through combinations of the given options, sending and
/// receiving packets.  For each packet exchange, a summary is written to
/// stdout.

class Scan : public asiolink::IOFetch::Callback {
public:

    /// \brief Constructor
    Scan() : service_(), result_()
    {}

    /// \brief Run Scan
    ///
    /// \param options Command-line options
    void scan(const CommandOptions& options);

    /// \brief Callback
    ///
    /// This class is derived from the IOFetch::Callback class as it acts as the
    /// callback object. When an asynchronous I/I has completed, this method
    /// will be called.
    ///
    /// \param result Result of the asynchronous I/O.  Zero implies success.
    virtual void operator()(asiolink::IOFetch::Result result);

private:
    /// \brief Set Flags Fields Options
    ///
    /// Iterates through all combinations of the DNS message flags fields specified
    /// on the command line and calls scanOne for each combination.
    ///
    /// \param msgbuf Message that will be sent to the remote nameserver.  The
    ///        QID given will be ignored - the value used will be determined by
    ///        the sending code
    /// \param options Command-line options (the important ones being address,
    ///        port and timeout).
    void iterateFlagsFields(isc::dns::OutputBufferPtr& msgbuf,
                 const CommandOptions& options);

    /// \brief Set Count Fields Options
    ///
    /// Iterates through all combinations of the count fields specified on the
    /// command line.
    ///
    /// The count fields are set by default to question count = 1, all the rest
    /// zero.  Command-line options allow these values to be altered, although
    /// the actual contents of the sections are not changed.
    ///
    /// \param msgbuf Message that will be sent to the remote nameserver.  The
    ///        QID given will be ignored - the value used will be determined by
    ///        the sending code
    /// \param options Command-line options (the important ones being address,
    ///        port and timeout).
    void iterateCountFields(isc::dns::OutputBufferPtr& msgbuf,
                 const CommandOptions& options);

    /// \brief Scan One Value
    ///
    /// Performs one exchange of packets with the remote nameserver, sending
    /// the specified message.
    ///
    /// \param msgbuf Message that will be sent to the remote nameserver.  The
    ///        QID given will be ignored - the value used will be determined by
    ///        the sending code
    /// \param options Command-line options (the important ones being address,
    ///        port and timeout).
    void scanOne(isc::dns::OutputBufferPtr& msgbuf,
                 const CommandOptions& options);

    /// \brief Perform I/O
    ///
    /// Performs a single query to the nameserver and reads the response.  It
    /// outputs a summary of the result.
    ///
    /// \param sendbuf Buffer sent to the nameserver
    /// \param recvbuf Buffer to hold reply from the nameserver
    /// \param options Command-line options
    void performIO(isc::dns::OutputBufferPtr& sendbuf,
                   isc::dns::OutputBufferPtr& recvbuf,
                   const CommandOptions& options);

    /// \brief Get Fields
    ///
    /// Interprets the flags fields in a DNS message and converts them to a
    /// terxtual format.
    ///
    /// \param msg Message for which the header is value
    ///
    /// \return A string that holds a textual interpretation of all the fields
    ///         in the header.
    std::string getFields(isc::dns::OutputBufferPtr& msgbuf);

    // Member variables

    boost::scoped_ptr<asiolink::IOService> service_;///< Service to run the scan
    asiolink::IOFetch::Result   result_;            ///< Result of the I/O
};

} // namespace test
} // namespace isc

#endif // __SCAN_H
