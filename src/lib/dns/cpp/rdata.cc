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

// $Id$

#include <cctype>
#include <string>

#include <stdint.h>
#include <string.h>

#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

#include <arpa/inet.h> // XXX: for inet_pton/ntop(), not exist in C++ standards

#include "buffer.h"
#include "name.h"
#include "messagerenderer.h"
#include "rdata.h"
#include "rrparamregistry.h"
#include "rrtype.h"

using namespace std;
using namespace boost;

namespace isc {
namespace dns {
namespace rdata {

// XXX: we need to specify std:: for string to help doxygen match the
// function signature with that given in the header file.
RdataPtr
createRdata(const RRType& rrtype, const RRClass& rrclass,
            const std::string& rdata_string)
{
    return (RRParamRegistry::getRegistry().createRdata(rrtype, rrclass,
                                                       rdata_string));
}

RdataPtr
createRdata(const RRType& rrtype, const RRClass& rrclass,
            InputBuffer& buffer, size_t len)
{
    size_t old_pos = buffer.getPosition();

    RdataPtr rdata =
        RRParamRegistry::getRegistry().createRdata(rrtype, rrclass, buffer,
                                                   len);
                                                   
    if (buffer.getPosition() - old_pos != len) {
        dns_throw(InvalidRdataLength, "RDLENGTH mismatch");
    }

    return (rdata);
}

RdataPtr
createRdata(const RRType& rrtype, const RRClass& rrclass, const Rdata& source)
{
    return (RRParamRegistry::getRegistry().createRdata(rrtype, rrclass,
                                                       source));
}

int
compareNames(const Name& n1, const Name& n2)
{
    size_t len1 = n1.getLength();
    size_t len2 = n2.getLength();
    size_t cmplen = (len1 < len2) ? len1 : len2;

    for (size_t i = 0; i < cmplen; ++i) {
        uint8_t c1 = tolower(n1.at(i));
        uint8_t c2 = tolower(n2.at(i));
        if (c1 < c2) {
            return (-1);
        } else if (c2 > c1) {
            return (1);
        }
    }

    return ((len1 == len2) ? 0 : (len1 < len2) ? -1 : 1);
}

namespace generic {
Generic::Generic(InputBuffer& buffer, size_t rdata_len) :
    data_(rdata_len)
{
    buffer.readData(&data_[0], rdata_len);
    data_.resize(rdata_len);
}

Generic::Generic(const string& rdata_string)
{
    // parse the \# n xx xx... format (TBD)
}

string
Generic::toText() const
{
    // return rdata in the \# n xx xx format (TBD)
    dns_throw(InvalidRdataText, "Not implemented yet");
}

void
Generic::toWire(OutputBuffer& buffer) const
{
    buffer.writeData(&data_[0], data_.size());
}

void
Generic::toWire(MessageRenderer& renderer) const
{
    renderer.writeData(&data_[0], data_.size());
}

int
Generic::compare(const Rdata& other) const
{
    const Generic& other_rdata = dynamic_cast<const Generic&>(other);

    size_t this_len = data_.size();
    size_t other_len = other_rdata.data_.size();
    size_t len = (this_len < other_len) ? this_len : other_len;
    int cmp;

    if ((cmp = memcmp(&data_[0], &other_rdata.data_[0], len)) != 0) {
        return (cmp);
    } else {
        return ((this_len == other_len) ? 0 :
                (this_len < other_len) ? -1 : 1);
    }
}

NS::NS(InputBuffer& buffer, size_t rdata_len) :
    nsname_(buffer)
{
    // we don't need rdata_len for parsing.  if necessary, the caller will
    // check consistency.
}

NS::NS(const NS& other) :
    nsname_(other.nsname_)
{}

void
NS::toWire(OutputBuffer& buffer) const
{
    nsname_.toWire(buffer);
}

void
NS::toWire(MessageRenderer& renderer) const
{
    renderer.writeName(nsname_);
}

string
NS::toText() const
{
    return (nsname_.toText());
}

int
NS::compare(const Rdata& other) const
{
    const NS& other_ns = dynamic_cast<const NS&>(other);

    return (compareNames(nsname_, other_ns.nsname_));
}

const Name&
NS::getNSName() const
{
    return (nsname_);
}

SOA::SOA(InputBuffer& buffer, size_t rdata_len) :
    mname_(buffer), rname_(buffer)
{
    // we don't need rdata_len for parsing.  if necessary, the caller will
    // check consistency.
    buffer.readData(numdata_, sizeof(numdata_));
}

SOA::SOA(const std::string& soastr) :
    mname_("."), rname_(".")
{
    dns_throw(InvalidRdataText, "Not implemented yet");
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
    mname_(other.mname_), rname_(other.rname_)
{
    memcpy(numdata_, other.numdata_, sizeof(numdata_));
}

void
SOA::toWire(OutputBuffer& buffer) const
{
    mname_.toWire(buffer);
    rname_.toWire(buffer);
    buffer.writeData(numdata_, sizeof(numdata_));
}

void
SOA::toWire(MessageRenderer& renderer) const
{
    renderer.writeName(mname_);
    renderer.writeName(rname_);
    renderer.writeData(numdata_, sizeof(numdata_));
}

string
SOA::toText() const
{
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
SOA::compare(const Rdata& other) const
{
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

MX::MX(InputBuffer& buffer, size_t rdata_len) :
    preference_(buffer.readUint16()), mxname_(buffer)
{
    // we don't need rdata_len for parsing.  if necessary, the caller will
    // check consistency.
}

MX::MX(const std::string& mxstr) :
    preference_(0), mxname_(".")
{
    dns_throw(InvalidRdataText, "Not implemented yet");
}

MX::MX(uint16_t preference, const Name& mxname) :
    preference_(preference), mxname_(mxname)
{}

MX::MX(const MX& other) :
    preference_(other.preference_), mxname_(other.mxname_)
{}

void
MX::toWire(OutputBuffer& buffer) const
{
    buffer.writeUint16(preference_);
    mxname_.toWire(buffer);
}

void
MX::toWire(MessageRenderer& renderer) const
{
    renderer.writeUint16(preference_);
    renderer.writeName(mxname_);
}

string
MX::toText() const
{
    return (lexical_cast<string>(preference_) + " " + mxname_.toText());
}

int
MX::compare(const Rdata& other) const
{
    const MX& other_mx = dynamic_cast<const MX&>(other);

    if (preference_ < other_mx.preference_) {
        return (-1);
    } else if (preference_ > other_mx.preference_) {
        return (1);
    }

    return (compareNames(mxname_, other_mx.mxname_));
}

TXT::TXT(InputBuffer& buffer, size_t rdata_len)
{
    uint8_t len;

    // TBD: this is a simple, incomplete implementation that only supports
    // a single character-string.
    len = buffer.readUint8();
    vector<uint8_t> data(len + 1);
    data[0] = len;
    buffer.readData(&data[0] + 1, len);
    string_list_.push_back(data);
}

TXT::TXT(const std::string& txtstr)
{
    size_t length = txtstr.size();
    size_t pos_begin = 0;

    if (length > 1 && txtstr[0] == '"' && txtstr[length - 1] == '"') {
        pos_begin = 1;
        length -= 2;
    }
    if (length > MAX_CHARSTRING_LEN) {
        dns_throw(CharStringTooLong, "");
    }

    vector<uint8_t> data;
    data.reserve(length + 1);
    data.push_back(length);
    data.insert(data.end(), txtstr.begin() + pos_begin,
                txtstr.begin() + pos_begin + length);
    string_list_.push_back(data);
}

TXT::TXT(const TXT& other) :
    string_list_(other.string_list_)
{}

void
TXT::toWire(OutputBuffer& buffer) const
{
    for (vector<vector<uint8_t> >::const_iterator it = string_list_.begin();
         it != string_list_.end();
         ++it)
    {
        buffer.writeData(&(*it)[0], (*it).size());
    }
}

void
TXT::toWire(MessageRenderer& renderer) const
{
    for (vector<vector<uint8_t> >::const_iterator it = string_list_.begin();
         it != string_list_.end();
         ++it)
    {
        renderer.writeData(&(*it)[0], (*it).size());
    }
}

string
TXT::toText() const
{
    string s;

    // XXX: this implementation is not entirely correct.  for example, it
    // should escape double-quotes if they appear in the character string.
    for (vector<vector<uint8_t> >::const_iterator it = string_list_.begin();
         it != string_list_.end();
         ++it)
    {
        if (!s.empty()) {
            s.push_back(' ');
        }
        s.push_back('"');
        s.insert(s.end(), (*it).begin() + 1, (*it).end());
        s.push_back('"');
    }

    return (s);
}

int
TXT::compare(const Rdata& other) const
{
    const TXT& other_txt = dynamic_cast<const TXT&>(other);

    // This implementation is not efficient.  Revisit this (TBD).
    OutputBuffer this_buffer(0);
    toWire(this_buffer);
    size_t this_len = this_buffer.getLength();

    OutputBuffer other_buffer(0);
    other_txt.toWire(other_buffer);
    size_t other_len = other_buffer.getLength();

    size_t cmplen = min(this_len, other_len);
    int cmp = memcmp(this_buffer.getData(), other_buffer.getData(), cmplen);
    if (cmp != 0) {
        return (cmp);
    } else {
        return ((this_len == other_len) ? 0 :
                (this_len < other_len) ? -1 : 1);
    }
}
} // end of namespace generic

namespace in {
A::A(const string& addrstr)
{
    // RFC1035 states textual representation of IN/A RDATA is
    // "four decimal numbers separated by dots without any embedded spaces".
    // This is exactly what inet_pton() accepts for AF_INET.  In particular,
    // it rejects an abbreviated form such as "10.1" meaning "10.0.0.1".
    if (inet_pton(AF_INET, addrstr.c_str(), &addr_) != 1) {
        dns_throw(InvalidRdataText,
                  "failed to parse IPv4 address for IN/A RDATA");
    }
}

A::A(InputBuffer& buffer, size_t rdata_len)
{
    if (rdata_len != sizeof(addr_)) {
        dns_throw(InvalidRdataLength, "Length mismatch for IN/A RDATA");
    }
    buffer.readData(&addr_, sizeof(addr_));
}

A::A(const A& other) :
    addr_(other.addr_)
{}

void
A::toWire(OutputBuffer& buffer) const
{
    buffer.writeData(&addr_, sizeof(addr_));
}

void
A::toWire(MessageRenderer& renderer) const
{
    renderer.writeData(&addr_, sizeof(addr_));
}

string
A::toText() const
{
    char addr_string[sizeof("255.255.255.255")];

    if (inet_ntop(AF_INET, &addr_, addr_string, sizeof(addr_string)) == NULL) {
        dns_throw(Unexpected, "inet_ntop failed for an IPv4 address");
    }

    return (string(addr_string));
}

int
A::compare(const Rdata& other) const
{
    const A& other_a = dynamic_cast<const A&>(other);
    return (memcmp(&addr_, &other_a.addr_, sizeof(addr_)));
}

AAAA::AAAA(const string& addrstr)
{
    if (inet_pton(AF_INET6, addrstr.c_str(), &addr_) != 1) {
        dns_throw(InvalidRdataText,
                  "failed to parse IPv6 address for IN/AAAA RDATA");
    }
}

AAAA::AAAA(InputBuffer& buffer, size_t rdata_len)
{
    if (rdata_len != sizeof(addr_)) {
        dns_throw(InvalidRdataLength, "Length mismatch for IN/AAAA RDATA");
    }
    buffer.readData(&addr_, sizeof(addr_));
}

AAAA::AAAA(const AAAA& other)
{
    memcpy(addr_, other.addr_, sizeof(addr_));
}

void
AAAA::toWire(OutputBuffer& buffer) const
{
    buffer.writeData(&addr_, sizeof(addr_));
}

void
AAAA::toWire(MessageRenderer& renderer) const
{
    renderer.writeData(&addr_, sizeof(addr_));
}

string
AAAA::toText() const
{
    char addr_string[sizeof("ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255")];

    if (inet_ntop(AF_INET6, &addr_, addr_string, sizeof(addr_string)) == NULL) {
        dns_throw(Unexpected, "inet_ntop failed for an IPv6 address");
    }

    return (string(addr_string));
}

int
AAAA::compare(const Rdata& other) const
{
    const AAAA& other_a = dynamic_cast<const AAAA&>(other);
    return (memcmp(&addr_, &other_a.addr_, sizeof(addr_)));
}
} // end of namespace in

namespace ch {
A::A(const string& addrstr)
{
    // TBD
}

A::A(InputBuffer& buffer, size_t rdata_len)
{
    // TBD
}

A::A(const A& source)
{
    // TBD
}

void
A::toWire(OutputBuffer& buffer) const
{
    // TBD
}

void
A::toWire(MessageRenderer& renderer) const
{
    // TBD
}

string
A::toText() const
{
    // TBD
    dns_throw(InvalidRdataText, "Not implemented yet");
}

int
A::compare(const Rdata& other) const
{
    return (0);                 // dummy.  TBD
}
} // end of namespace ch
} // end of namespace rdata
}
}
