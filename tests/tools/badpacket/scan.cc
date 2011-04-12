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

#include <boost/scoped_ptr.hpp>

#include <asio.hpp>

#include <asiolink/io_address.h>
#include <asiolink/io_fetch.h>
#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/opcode.h>
#include <dns/question.h>
#include <dns/rcode.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <log/strutil.h>

#include "command_options.h"
#include "header_flags.h"
#include "scan.h"

using namespace std;
using namespace asiolink;
using namespace isc::dns;
using namespace isc::strutil;

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
    MessageRenderer renderer(*msgbuf);
    message.toWire(renderer);

    iterateFlagsFields(msgbuf, options);
}

// Iterate through the various settings in the flags fields
void
Scan::iterateFlagsFields(OutputBufferPtr& msgbuf, const CommandOptions& options) {

    // Loop through the flags setting data.  This is quite deep nesting,
    // but we will continue to indent so as to make things clear (for those
    // readers lucky enough to have a wide screen).
    HeaderFlags flags;
    for (uint32_t qr =  options.minimum(OptionInfo::QR);
                  qr <= options.maximum(OptionInfo::QR); ++qr) {
        flags.set(OptionInfo::QR, qr);

        for (uint32_t op =  options.minimum(OptionInfo::OP);
                      op <= options.maximum(OptionInfo::OP); ++op) {
            flags.set(OptionInfo::OP, op);

            for (uint32_t aa =  options.minimum(OptionInfo::AA);
                          aa <= options.maximum(OptionInfo::AA); ++aa) {
                flags.set(OptionInfo::AA, aa);

                for (uint32_t tc =  options.minimum(OptionInfo::TC);
                              tc <= options.maximum(OptionInfo::TC); ++tc) {
                    flags.set(OptionInfo::TC, tc);

                    for (uint32_t rd =  options.minimum(OptionInfo::RD);
                                  rd <= options.maximum(OptionInfo::RD); ++rd) {
                        flags.set(OptionInfo::RD, rd);

                        for (uint32_t ra =  options.minimum(OptionInfo::RA);
                                      ra <= options.maximum(OptionInfo::RA); ++ra) {
                            flags.set(OptionInfo::RA, ra);

                            for (uint32_t z =  options.minimum(OptionInfo::Z);
                                          z <= options.maximum(OptionInfo::Z); ++z) {
                                flags.set(OptionInfo::Z, z);

                                for (uint32_t ad =  options.minimum(OptionInfo::AD);
                                              ad <= options.maximum(OptionInfo::AD); ++ad) {
                                    flags.set(OptionInfo::AD, ad);

                                    for (uint32_t cd =  options.minimum(OptionInfo::CD);
                                                  cd <= options.maximum(OptionInfo::CD); ++cd) {
                                        flags.set(OptionInfo::CD, cd);

                                        for (uint32_t rc =  options.minimum(OptionInfo::RC);
                                                      rc <= options.maximum(OptionInfo::RC); ++rc) {
                                            flags.set(OptionInfo::RC, rc);

                                            // Set the flags in the message.
                                            msgbuf->writeUint16At(flags.getValue(), 2);

                                            // Do the I/O.
                                            scanOne(msgbuf, options);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

// Perform the message exchange for a single combination of flags.
void
Scan::scanOne(isc::dns::OutputBufferPtr& msgbuf, const CommandOptions& options) {

    // Store the interpretation of the flags field.
    string fields = getFields(msgbuf);

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
            returned = getFields(replybuf);
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
    cout << status << ": (" << fields << ") (" << returned << ")\n";
}

// Get interpretation of the message fields.
//
// This takes the second and third bytes of the passed buffer and interprets
// the values.  A summary string listing them is returned.
std::string
Scan::getFields(isc::dns::OutputBufferPtr& msgbuf) {
    HeaderFlags flags;

    // Extract the flags field from the buffer
    InputBuffer inbuf(msgbuf->getData(), msgbuf->getLength());
    inbuf.setPosition(2);
    flags.setValue(inbuf.readUint16());

    std::ostringstream os;
    os << std::hex << std::uppercase <<
        "QR:" << flags.get(OptionInfo::QR) << " " <<
        "OP:" << flags.get(OptionInfo::OP) << " " <<
        "AA:" << flags.get(OptionInfo::AA) << " " <<
        "TC:" << flags.get(OptionInfo::TC) << " " <<
        "RD:" << flags.get(OptionInfo::RD) << " " <<
        "RA:" << flags.get(OptionInfo::RA) << " " <<
         "Z:" << flags.get(OptionInfo::Z)  << " " <<
        "AD:" << flags.get(OptionInfo::AD) << " " <<
        "CD:" << flags.get(OptionInfo::CD) << " " <<
        "RC:" << flags.get(OptionInfo::RC);
    return (os.str());
}

// Perform the I/O.
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

    // Execute the message exhange.  The call to run() will return when a
    // response is received or when the I/O times out.
    (service_->get_io_service()).post(fetch); 
    service_->run();
}

// I/O Callback.  Called when the message exchange compltes or times out.
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
