// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#include <string>

#include <boost/lexical_cast.hpp>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

using namespace std;
using boost::lexical_cast;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

SOA::SOA(InputBuffer& buffer, size_t) :
    mname_(buffer), rname_(buffer)
{
    // we don't need rdata_len for parsing.  if necessary, the caller will
    // check consistency.
    buffer.readData(numdata_, sizeof(numdata_));
}

SOA::SOA(const std::string& soastr) :
    mname_("."), rname_(".")    // quick hack workaround
{
    istringstream iss(soastr);
    string token;

    iss >> token;
    if (iss.bad() || iss.fail()) {
        isc_throw(InvalidRdataText, "Invalid SOA MNAME");
    }
    mname_ = Name(token);
    iss >> token;
    if (iss.bad() || iss.fail()) {
        isc_throw(InvalidRdataText, "Invalid SOA RNAME");
    }
    rname_ = Name(token);

    uint32_t serial, refresh, retry, expire, minimum;
    iss >> serial >> refresh >> retry >> expire >> minimum;
    if (iss.rdstate() != ios::eofbit) {
        isc_throw(InvalidRdataText, "Invalid SOA format");
    }
    OutputBuffer buffer(20);
    buffer.writeUint32(serial);
    buffer.writeUint32(refresh);
    buffer.writeUint32(retry);
    buffer.writeUint32(expire);
    buffer.writeUint32(minimum);
    memcpy(numdata_,  buffer.getData(), buffer.getLength());
}

SOA::SOA(const Name& mname, const Name& rname, uint32_t serial,
         uint32_t refresh, uint32_t retry, uint32_t expire, uint32_t minimum) :
    mname_(mname), rname_(rname)
{
    OutputBuffer b(20);
    b.writeUint32(serial);
    b.writeUint32(refresh);
    b.writeUint32(retry);
    b.writeUint32(expire);
    b.writeUint32(minimum);
    assert(b.getLength() == sizeof(numdata_));
    memcpy(numdata_, b.getData(), sizeof(numdata_));
}

SOA::SOA(const SOA& other) :
    Rdata(), mname_(other.mname_), rname_(other.rname_)
{
    memcpy(numdata_, other.numdata_, sizeof(numdata_));
}

void
SOA::toWire(OutputBuffer& buffer) const {
    mname_.toWire(buffer);
    rname_.toWire(buffer);
    buffer.writeData(numdata_, sizeof(numdata_));
}

void
SOA::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeName(mname_);
    renderer.writeName(rname_);
    renderer.writeData(numdata_, sizeof(numdata_));
}

Serial
SOA::getSerial() const {
    InputBuffer b(numdata_, sizeof(numdata_));
    return (Serial(b.readUint32()));
}

string
SOA::toText() const {
    InputBuffer b(numdata_, sizeof(numdata_));
    uint32_t serial = b.readUint32();
    uint32_t refresh = b.readUint32();
    uint32_t retry = b.readUint32();
    uint32_t expire = b.readUint32();
    uint32_t minimum = b.readUint32();

    return (mname_.toText() + " " + rname_.toText() + " " +
            lexical_cast<string>(serial) + " " +
            lexical_cast<string>(refresh) + " " +
            lexical_cast<string>(retry) + " " +
            lexical_cast<string>(expire) + " " +
            lexical_cast<string>(minimum));
}

int
SOA::compare(const Rdata& other) const {
    const SOA& other_soa = dynamic_cast<const SOA&>(other);

    int order = compareNames(mname_, other_soa.mname_);
    if (order != 0) {
        return (order);
    }

    order = compareNames(rname_, other_soa.rname_);
    if (order != 0) {
        return (order);
    }

    return (memcmp(numdata_, other_soa.numdata_, sizeof(numdata_)));
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
