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

#ifndef SCAN_H
#define SCAN_H

#include <stdint.h>

#include <boost/scoped_ptr.hpp>

#include <config.h>

#include <asiolink/io_service.h>
#include <asiodns/io_fetch.h>
#include <util/buffer.h>

#include "command_options.h"
#include "header_flags.h"

namespace isc {
namespace badpacket {

/// \brief Field Scan
///
/// This class implements a field scan.  Given a CommandOptions object, it will
/// cycle through combinations of the given options, sending and receiving
/// messages. For each packet exchange, a summary is written to stdout.

class Scan : public isc::asiodns::IOFetch::Callback {
public:

    /// \brief Constructor
    Scan() : service_(), result_()
    {}

    /// \brief Run Scan
    ///
    /// Actually performs the scan for the combination of options.
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
    virtual void operator()(isc::asiodns::IOFetch::Result result);

private:
    /// \brief Iterate over flags fields options
    ///
    /// This method relies on the fact that data concerning the settings for
    /// the fields in the flags word of the DNS message are held at adjacent
    /// elements in the various data arrays and so can be accessed by a set
    /// of contiguous index values.
    ///
    /// The method is passed an index value and the maximum valid index value.
    /// If a set of values for the field at the given index was specified on
    /// the command line, it loops through those values and sets the appropriate
    /// value in the a copy of the DNS message header flags.  It then calls
    /// itself with an incremented index.  If the value was not given, it just
    /// sets a default value calls itself (with the incremented index).  When
    /// called with an index above the maximum valid index, the header flags
    /// in the message buffer are set and the next stage of processing called.
    ///
    /// In this way, all fields can be cycled through without the need for a
    /// single function to nest loops very deeply.
    ///
    /// \param msgbuf Message that will be sent to the remote nameserver.  The
    ///        QID given will be ignored - the value used will be determined by
    ///        the sending code
    /// \param options Command-line options (the important ones being address,
    ///        port and timeout).
    /// \param flags Header flags
    /// \param index Index of the current field to be processed.
    /// \param maxindex Maximum valid index value
    void iterateFlags(isc::util::OutputBufferPtr& msgbuf,
                 const CommandOptions& options, HeaderFlags& flags,
                 int index, int maxindex);

    /// \brief Start iterating over flags field options
    ///
    /// Kicks off the call to \c iterateFlags by calling it with the initial
    /// index value.
    ///
    /// \param msgbuf Message that will be sent to the remote nameserver.  The
    ///        QID given will be ignored - the value used will be determined by
    ///        the sending code
    /// \param options Command-line options (the important ones being address,
    ///        port and timeout).
    void iterateFlagsStart(isc::util::OutputBufferPtr& msgbuf,
                           const CommandOptions& options);

    /// \brief Iterate over count fields
    ///
    /// In a manner similar to iterateFlags, this iterates over all specified
    /// values for each count field, recursively calling itself to process the
    /// next field.  When all fields have been processed, it chains to the
    /// next stage of packet processing.
    ///
    /// \param msgbuf Message that will be sent to the remote nameserver.  The
    ///        QID given will be ignored - the value used will be determined by
    ///        the sending code
    /// \param options Command-line options (the important ones being address,
    ///        port and timeout).
    /// \param index Index of the current field to be processed.
    /// \param maxindex Maximum valid index value
    void iterateCount(isc::util::OutputBufferPtr& msgbuf,
                      const CommandOptions& options, int index, int maxindex);

    /// \brief Start iterating over count fields
    ///
    /// Kicks off the call to \c iterateCount by calling it with the initial
    /// index value.
    ///
    /// \param msgbuf Message that will be sent to the remote nameserver.  The
    ///        QID given will be ignored - the value used will be determined by
    ///        the sending code
    /// \param options Command-line options (the important ones being address,
    ///        port and timeout).
    void iterateCountStart(isc::util::OutputBufferPtr& msgbuf,
                           const CommandOptions& options);

    /// \brief Iterate over message sizes
    ///
    /// If the message size option is given on the command line, the message
    /// sent to the remote system is either truncated or extended (with zeroes)
    /// before being set.
    ///
    /// \param msgbuf Message that will be sent to the remote nameserver.  The
    ///        QID given will be ignored - the value used will be determined by
    ///        the sending code
    /// \param options Command-line options (the important ones being address,
    ///        port and timeout).
    void sizeMessage(isc::util::OutputBufferPtr& msgbuf,
                     const CommandOptions& options);

    /// \brief Scan One Value
    ///
    /// Performs one exchange of messages with the remote nameserver, sending
    /// the specified message.
    ///
    /// \param msgbuf Message that will be sent to the remote nameserver.  The
    ///        QID given will be ignored - the value used will be determined by
    ///        the sending code
    /// \param options Command-line options (the important ones being address,
    ///        port and timeout).
    void scanOne(isc::util::OutputBufferPtr& msgbuf,
                 const CommandOptions& options);

    /// \brief Perform I/O
    ///
    /// Performs a single query to the nameserver and reads the response.  It
    /// outputs a summary of the result.
    ///
    /// \param sendbuf Buffer sent to the nameserver
    /// \param recvbuf Buffer to hold reply from the nameserver
    /// \param options Command-line options
    void performIO(isc::util::OutputBufferPtr& sendbuf,
                   isc::util::OutputBufferPtr& recvbuf,
                   const CommandOptions& options);

    /// \brief Get Fields
    ///
    /// Interprets the fields in a DNS message and converts them to a brief
    /// textual format.
    ///
    /// \param msg Message for which the header is value
    ///
    /// \return A string that holds a textual interpretation of all the fields
    ///         in the header.
    std::string getFields(isc::util::OutputBufferPtr& msgbuf);

    // Member variables

    boost::scoped_ptr<isc::asiolink::IOService> service_;
                                                    ///< Service to run the scan
    isc::asiodns::IOFetch::Result   result_;        ///< Result of the I/O
};

} // namespace test
} // namespace isc

#endif // SCAN_H
