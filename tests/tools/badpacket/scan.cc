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

    // Now loop through the flags setting data.  This is quite deep nesting,
    // but we will continue to indent so as to make things clear (for those
    // readers lucky enough to have a wide screen).
    CommandOptions::FlagValues values = options.getFlagValues();
    HeaderFlags flags;
    for (uint16_t qr = values.qr[0]; qr <= values.qr[1]; ++qr) {
        flags.setQR(qr);
        for (uint16_t op = values.op[0]; op <= values.op[1]; ++op) {
            flags.setOP(op);
            for (uint16_t aa = values.aa[0]; aa <= values.aa[1]; ++aa) {
                flags.setAA(aa);
                for (uint16_t tc = values.tc[0]; tc <= values.tc[1]; ++tc) {
                    flags.setTC(tc);
                    for (uint16_t rd = values.rd[0]; rd <= values.rd[1]; ++rd) {
                        flags.setRD(rd);
                        for (uint16_t ra = values.ra[0]; ra <= values.ra[1]; ++ra) {
                            flags.setRA(ra);
                            for (uint16_t z = values.z[0]; z <= values.z[1]; ++z) {
                                flags.setZ(z);
                                for (uint16_t ad = values.ad[0]; ad <= values.ad[1]; ++ad) {
                                    flags.setAD(ad);
                                    for (uint16_t cd = values.cd[0]; cd <= values.cd[1]; ++cd) {
                                        flags.setCD(cd);
                                        for (uint16_t rc = values.rc[0]; rc <= values.rc[1]; ++rc) {
                                            flags.setRC(rc);

                                            // Set the flags in the message and do the I/O.
                                            msgbuf->writeUint16At(flags.getValue(), 2);
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
        "QR:" << flags.getQR() << " " <<
        "OP:" << flags.getOP() << " " <<
        "AA:" << flags.getAA() << " " <<
        "TC:" << flags.getTC() << " " <<
        "RD:" << flags.getRD() << " " <<
        "RA:" << flags.getRA() << " " <<
         "Z:" << flags.getZ()  << " " <<
        "AD:" << flags.getAD() << " " <<
        "CD:" << flags.getCD() << " " <<
        "RC:" << flags.getRC();
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
