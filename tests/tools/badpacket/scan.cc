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

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include <stdlib.h>

#include <config.h>

#include <asio.hpp>

#include <asiolink/io_address.h>
#include <asiodns/io_fetch.h>
#include <util/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/opcode.h>
#include <dns/question.h>
#include <dns/rcode.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <util/strutil.h>

#include "command_options.h"
#include "header_flags.h"
#include "scan.h"

using namespace std;
using namespace isc::asiolink;
using namespace isc::asiodns;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::util::str;

namespace isc {
namespace badpacket {

// Perform the scan from start to end on a single question.
void
Scan::scan(const CommandOptions& options) {

    // Create the message buffer to use
    Message message(Message::RENDER);
    message.setOpcode(Opcode::QUERY());
    message.setRcode(Rcode::NOERROR());
    message.addQuestion(Question(Name(options.getQname()), RRClass::IN(),
                        RRType::A()));

    OutputBufferPtr msgbuf(new OutputBuffer(512));
    MessageRenderer renderer;
    renderer.setBuffer(msgbuf.get());
    message.toWire(renderer);

    iterateFlagsStart(msgbuf, options);
}

// Iterate through the various settings in the flags fields.
void
Scan::iterateFlagsStart(OutputBufferPtr& msgbuf, const CommandOptions& options) {
    HeaderFlags flags;
    iterateFlags(msgbuf, options, flags, OptionInfo::FLAGS_START,
                 OptionInfo::FLAGS_END);
}
void
Scan::iterateFlags(OutputBufferPtr& msgbuf, const CommandOptions& options,
                   HeaderFlags& flags, int index, int maxindex)
{
    // Is the index valid?
    if (index <= maxindex) {

        // Index is valid, did the command line specify a range of values for
        // this field?
        if (options.present(index)) {

            // It did, so loop between minimum and maximum values given.
            for (uint32_t i = options.minimum(index);
                          i <= options.maximum(index); ++i) {
                flags.set(index, i);

                // Recurse to set the next option.
                iterateFlags(msgbuf, options, flags, (index + 1), maxindex);
            }
        } else {

            // Not specified on command line, so set the default value in the
            // flags and process the next index.
            flags.set(index, OptionInfo::defval(index));
            iterateFlags(msgbuf, options, flags, (index + 1), maxindex);
        }
    } else {

        // Index is not valid, so we have recursed enough to process all the
        // flags fields.  Set the value in the message header and call the next
        // stage in the processing.
        //
        // (In the next statement, the "word" offset of in the header is the
        // same for all flags options, so the value for an arbitrary field
        // (QR) has been used.)
        msgbuf->writeUint16At(flags.getValue(),
                              OptionInfo::word(OptionInfo::QR));
        iterateCountStart(msgbuf, options);
    }
}

// Iterate through the various count fields
void
Scan::iterateCountStart(OutputBufferPtr& msgbuf, const CommandOptions& options)
{
    iterateCount(msgbuf, options, OptionInfo::COUNT_START,
                 OptionInfo::COUNT_END);
}

void
Scan::iterateCount(OutputBufferPtr& msgbuf, const CommandOptions& options,
                   int index, int maxindex)
{
    // If the index is valid, process the iteration over the range for this
    // flags field.
    if (index <= maxindex) {

        // Index is valid, did the command line specify a range of values for
        // this field?
        if (options.present(index)) {

            // It did, so loop between minimum and maximum values given.
            for (uint32_t i = options.minimum(index);
                          i <= options.maximum(index); ++i) {

                // Set the value in the message buffer header and recurse to
                // the next option.
                msgbuf->writeUint16At(i, OptionInfo::word(index));
                iterateCount(msgbuf, options, (index + 1), maxindex);
            }
        } else {

            // Not specified on command line, so do change anything and process
            // the next index.
            iterateCount(msgbuf, options, (index + 1), maxindex);
        }
    } else {

        // Index is not valid, so we have recursed enough to process all the
        // flags fields.  Do the next stage of the processing.
        sizeMessage(msgbuf, options);
    }
}

// Alter the message size.
void
Scan::sizeMessage(OutputBufferPtr& msgbuf, const CommandOptions& options) {

    if (options.present(OptionInfo::MS)) {

        // Iterate over the range of message sizes
        for (size_t i = options.minimum(OptionInfo::MS);
                    i <= options.maximum(OptionInfo::MS); ++i) {

            // Copy the data into a new buffer.
            OutputBufferPtr newbuf(new OutputBuffer(i));
            newbuf->writeData(msgbuf->getData(), min(msgbuf->getLength(), i));

            // Pad with junk (actually pseudo-random data) if the new buffer is
            // longer than the old.
            for (size_t j = newbuf->getLength(); j < i; ++j) {
                newbuf->writeUint8(static_cast<uint8_t>(rand() & 0xFFU));
            }

            // ... and process.
            scanOne(newbuf, options);
        }
    } else {

        // No packet size given, just process the message as it.
        scanOne(msgbuf, options);
    }
}

// Perform the message exchange for a single combination command options.
void
Scan::scanOne(isc::util::OutputBufferPtr& msgbuf, const CommandOptions& options) {
    // Store the interpretation of outgoing message.
    string fields = string("(") + getFields(msgbuf) + string(")");

    // Do the I/O, waiting for a reply
    OutputBufferPtr replybuf(new OutputBuffer(512));
    performIO(msgbuf, replybuf, options);

    string status = "";
    string returned = "";
    switch (result_) {
    case IOFetch::SUCCESS:
        {
            status = "SUCCESS";

            // Parse the reply and get the fields
            returned = string("(") + getFields(replybuf) + string(")");
            lowercase(returned);
        }
        break;

    case IOFetch::TIME_OUT:
        status = "TIMEOUT";
        break;

    case IOFetch::STOPPED:
        status = "STOPPED";
        break;

    default:
        status = "UNKNOWN";
    }

    // ... and output the result
    cout << status << ": " << fields << " " << returned << "\n";
}

// Get interpretation of the message fields.
std::string
Scan::getFields(isc::util::OutputBufferPtr& msgbuf) {

    // Header flags. (Note that all come from the same word in the message, so
    // using the word offset for the QR flag as the position in the buffer from
    // which to extract the values is valid.)
    HeaderFlags flags;
    InputBuffer inbuf(msgbuf->getData(), msgbuf->getLength());
    inbuf.setPosition(OptionInfo::word(OptionInfo::QR));
    flags.setValue(inbuf.readUint16());

    std::ostringstream os;
    os << std::hex << std::uppercase <<
         "QR:" << flags.get(OptionInfo::QR) <<
        " OP:" << flags.get(OptionInfo::OP) <<
        " AA:" << flags.get(OptionInfo::AA) <<
        " TC:" << flags.get(OptionInfo::TC) <<
        " RD:" << flags.get(OptionInfo::RD) <<
        " RA:" << flags.get(OptionInfo::RA) <<
        " Z:"  << flags.get(OptionInfo::Z)  <<
        " AD:" << flags.get(OptionInfo::AD) <<
        " CD:" << flags.get(OptionInfo::CD) <<
        " RC:" << flags.get(OptionInfo::RC);

    // Section count fields.
    inbuf.setPosition(OptionInfo::word(OptionInfo::QC));
    os << std::dec << std::uppercase <<
        " QC:" << inbuf.readUint16();

    inbuf.setPosition(OptionInfo::word(OptionInfo::AC));
    os << std::dec << std::uppercase <<
        " AC:" << inbuf.readUint16();

    inbuf.setPosition(OptionInfo::word(OptionInfo::UC));
    os << std::dec << std::uppercase <<
        " UC:" << inbuf.readUint16();

    inbuf.setPosition(OptionInfo::word(OptionInfo::DC));
    os << std::dec << std::uppercase <<
        " DC:" << inbuf.readUint16();

    // ... and message size.
    os << std::dec << std::uppercase <<
        " MS:" << msgbuf->getLength();

    return (os.str());
}

// Perform the I/O to the nameserver.
void
Scan::performIO(OutputBufferPtr& sendbuf, OutputBufferPtr& recvbuf,
                const CommandOptions& options)
{
    // Set up an I/O service for the I/O.  This needs to be initialized before
    // every call as the callback called when the I/O completes stops it.
    service_.reset(new IOService());

    // The object that will do the I/O
    IOFetch fetch(IOFetch::UDP, *service_, sendbuf,
                  IOAddress(options.getAddress()), options.getPort(), recvbuf,
                  this, options.getTimeout());

    // Execute the message exchange.  The call to run() will return when a
    // response is received or when the I/O times out.
    (service_->get_io_service()).post(fetch); 
    service_->run();
}

// I/O Callback.  Called when the message exchange completes or times out.
void
Scan::operator()(IOFetch::Result result) {

    // Record the result.  This is accessed when deciding what was returned
    // (if a timeout, nothing was returned).
    result_ = result;

    // Stop the I/O service.  This will cause the call to run() to return.
    service_->stop();
}

} // namespace test
} // namespace isc
