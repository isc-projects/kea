// Copyright (C) 2012-2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <d2/d2_update_message.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rrttl.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::d2;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::util;

namespace {

class D2UpdateMessageTest : public ::testing::Test {
public:
    D2UpdateMessageTest() {
    }

    ~D2UpdateMessageTest() {
    };

    // @brief Return string representation of the name encoded in wire format.
    //
    // This function reads the number of bytes specified in the second
    // argument from the buffer. It doesn't check if buffer has sufficient
    // length for reading given number of bytes. Caller should verify it
    // prior to calling this function.
    //
    // @param buf input buffer, its internal pointer will be moved to
    //        the position after a name being read from it.
    // @param name_length length of the name stored in the buffer
    //
    // @return string representation of the name.
    std::string readNameFromWire(InputBuffer& buf, const size_t name_length) {
        // 64 characters bytes should be sufficent for current tests.
        // It may be extended if required.
        char name_data[64];
        // Create another InputBuffer which holds only the name in the wire
        // format.
        buf.readData(name_data, name_length);
        InputBuffer name_buf(name_data, name_length);
        // Parse the name and returns its textual representation.
        Name name(name_buf);
        return (name.toText());
    }
};

// This test verifies that the wire format of the message is produced
// in the render mode.
TEST_F(D2UpdateMessageTest, toWire) {
    D2UpdateMessage msg;
    // Set message ID.
    msg.setQid(0x1234);
    // Make it a Request message by setting the QR flag to 0.
    msg.setQRFlag(D2UpdateMessage::REQUEST);
    // Rcode to NOERROR.
    msg.setRcode(Rcode(Rcode::NOERROR_CODE));

    // Set Zone section. This section must comprise exactly
    // one Zone. toWire function would fail if Zone is not set.
    msg.setZone(Name("example.com"), RRClass::IN());

    // Set prerequisities.

    // 'Name Is Not In Use' prerequisite (RFC 2136, section 2.4.5)
    RRsetPtr prereq1(new RRset(Name("foo.example.com"), RRClass::NONE(),
                               RRType::ANY(), RRTTL(0)));
    msg.addRRset(D2UpdateMessage::SECTION_PREREQUISITE, prereq1);

    // 'Name is In Use' prerequisite (RFC 2136, section 2.4.4)
    RRsetPtr prereq2(new RRset(Name("bar.example.com"), RRClass::ANY(),
                               RRType::ANY(), RRTTL(0)));
    msg.addRRset(D2UpdateMessage::SECTION_PREREQUISITE, prereq2);

    // Set Update Section.

    // Create RR holding a name being added. This RR is constructed
    // in conformance to RFC 2136, section 2.5.1.
    RRsetPtr updaterr1(new RRset(Name("foo.example.com"), RRClass::IN(),
                                 RRType::A(), RRTTL(10)));
    // RR record is of the type A, thus RDATA holds 4 octet Internet
    // address. This address is 10.10.1.1.
    char rdata1[] = {
        0xA, 0xA , 0x1, 0x1
    };
    InputBuffer buf_rdata1(rdata1, 4);
    updaterr1->addRdata(createRdata(RRType::A(), RRClass::IN(), buf_rdata1,
                                    buf_rdata1.getLength()));
    // Add the RR to the message.
    msg.addRRset(D2UpdateMessage::SECTION_UPDATE, updaterr1);

    // Render message into the wire format.
    MessageRenderer renderer;
    ASSERT_NO_THROW(msg.toWire(renderer));

    // Make sure that created packet is not truncated.
    ASSERT_EQ(77, renderer.getLength());

    // Create input buffer from the rendered data. InputBuffer
    // is handy to validate the byte contents of the rendered
    // message.
    InputBuffer buf(renderer.getData(), renderer.getLength());

    // Start validating the message header.

    // Verify message ID.
    EXPECT_EQ(0x1234, buf.readUint16());
    // The 2-bytes following message ID comprise the following fields:
    // - QR - 1 bit indicating that it is REQUEST. Should be 0.
    // - Opcode - 4 bits which should hold value of 5 indicating this is
    //            an Update message. Binary form is "0101".
    // - Z - These bits are unused for Update Message and should be 0.
    // - RCODE - Response code, set to NOERROR for REQUEST. It is 0.
    //8706391835
    // The binary value is:
    //   0   1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // | QR|     Opcode    |           Z               |     RCODE     |
    // +---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
    // | 0 | 0   1   0   1 | 0   0   0   0   0   0   0 | 0   0   0   0 |
    // +---+---+---+-------+---+---+---+---+---+---+---+---+---+---+---+
    // and the hexadecimal representation is 0x2800.
    EXPECT_EQ(0x2800, buf.readUint16());

    // ZOCOUNT - holds the number of zones for the update. For Request
    // message it must be exactly one record (RFC2136, section 2.3).
    EXPECT_EQ(1, buf.readUint16());

    // PRCOUNT - holds the number of prerequisites. Earlier we have added
    // two prerequisites. Thus, expect that this conter is 2.
    EXPECT_EQ(2, buf.readUint16());

    // UPCOUNT - holds the number of RRs in the Update Section. We have
    // added 1 RR, which adds the name foo.example.com to the Zone.
    EXPECT_EQ(1, buf.readUint16());

    // ADCOUNT - holds the number of RRs in the Additional Data Section.
    EXPECT_EQ(0, buf.readUint16());

    // Start validating the Zone section. This section comprises the
    // following data:
    // - ZNAME
    // - ZTYPE
    // - ZCLASS

    // ZNAME holds 'example.com.' encoded as set of labels. Each label
    // is preceded by its length. The name is ended with the byte holding
    // zero value. This yields the total size of the name in wire format
    // of 13 bytes.

    // The simplest way to convert the name from wire format to a string
    // is to use dns::Name class. It should be ok to rely on the Name class
    // to decode the name, because it is unit tested elswhere.
    std::string zone_name = readNameFromWire(buf, 13);
    EXPECT_EQ("example.com.", zone_name);

    // ZTYPE of the Zone section must be SOA according to RFC 2136,
    // section 2.3.
    EXPECT_EQ(RRType::SOA().getCode(), buf.readUint16());

    // ZCLASS of the Zone section is IN.
    EXPECT_EQ(RRClass::IN().getCode(), buf.readUint16());

    // Start checks on Prerequisite section. Each prerequisite comprises
    // the following fields:
    // - NAME - name of the RR in wire format
    // - TYPE - two octets with one of the RR TYPE codes
    // - CLASS - two octets with one of the RR CLASS codes
    // - TTL - a 32-bit signed integer specifying Time-To-Live
    // - RDLENGTH - length of the RDATA field
    // - RDATA - a variable length string of octets containing
    //           resource data.
    // In case of this message, we expect to have two prerequisite RRs.
    // Their structure is checked below.

}

} // End of anonymous namespace
