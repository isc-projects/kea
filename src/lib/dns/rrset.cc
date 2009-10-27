// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdexcept>
#include <cstring>

#include <dns/buffer.h>
#include <dns/rrset.h>

using ISC::DNS::RRClass;
using ISC::DNS::RRType;
using ISC::DNS::TTL;
using ISC::DNS::Rdata::IN::A;
using ISC::DNS::Rdata::IN::AAAA;
using ISC::DNS::Rdata::Generic::NS;

RRClass::RRClass(const std::string& classstr)
{
    // XXX: this is a quick hack implementation to see feasibility.
    // should be rewritten in a cleaner way.
    if (classstr == "IN")
        classval_ = 1;
    else if (classstr == "CHAOS" || classstr == "CH")
        classval_ = 3;
    else
        throw DNSInvalidRRClass();
}

const std::string
RRClass::to_text() const
{
    // XXX: quick hack
    if (classval_ == 1)
        return ("IN");
    else if (classval_ == 3)
        return ("CH");
    throw std::runtime_error("unexpected class");
}

void
RRClass::to_wire(ISC::Buffer& b) const
{
    b.write_uint16(classval_);
}

const RRClass RRClass::IN("IN");
const RRClass RRClass::CH("CH");

RRType::RRType(const std::string& typestr)
{
    // XXX: this is a quick hack implementation to see feasibility.
    // should be rewritten in a cleaner way.
    if (typestr == "A")
        typeval_ = 1;
    else if (typestr == "NS")
        typeval_ = 2;
    else if (typestr == "AAAA")
        typeval_ = 28;
    else
        throw DNSInvalidRRType();
}

const std::string
RRType::to_text() const
{
    if (typeval_ == 1)
        return ("A");
    else if (typeval_ == 2)
        return ("NS");
    else if (typeval_ == 28)
        return ("AAAA");
    throw std::runtime_error("unexpected type");
}

void
RRType::to_wire(Buffer& buffer) const
{
    buffer.write_uint16(typeval_);
}

const RRType RRType::A("A");
const RRType RRType::NS("NS");
const RRType RRType::AAAA("AAAA");
// ...more to follow

void
TTL::to_wire(Buffer& buffer) const
{
    buffer.write_uint32(ttlval_);
}

A::A(const std::string& addrstr)
{
    if (inet_pton(AF_INET, addrstr.c_str(), &addr_) != 1)
        throw ISCInvalidAddressString();
}

void
A::from_wire(Buffer& buffer, NameDecompressor& decompressor)
{
    //TBD
}

void
A::to_wire(Buffer& buffer, NameCompressor& compressor) const
{
    buffer.write_uint16(sizeof(addr_));
    buffer.write_data(&addr_, sizeof(addr_));
}

std::string
A::to_text() const
{
    char addrbuf[sizeof("255.255.255.255")];

    if (inet_ntop(AF_INET, &addr_, addrbuf, sizeof(addrbuf)) == NULL)
        throw std::runtime_error("unexpected inet_ntop() failure");

    return (std::string(addrbuf));
}

AAAA::AAAA(const std::string& addrstr)
{
    if (inet_pton(AF_INET6, addrstr.c_str(), &addr_) != 1)
        throw ISCInvalidAddressString();
}

void
AAAA::from_wire(Buffer& buffer, NameDecompressor& decompressor)
{
    //TBD
}

void
AAAA::to_wire(Buffer& buffer, NameCompressor& compressor) const
{
    buffer.write_uint16(sizeof(addr_));
    buffer.write_data(&addr_, sizeof(addr_));
}

std::string
AAAA::to_text() const
{
    char addrbuf[sizeof("ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255")];

    if (inet_ntop(AF_INET6, &addr_, addrbuf, sizeof(addrbuf)) == NULL)
        throw std::runtime_error("unexpected inet_ntop() failure");

    return (std::string(addrbuf));
}

void
NS::from_wire(Buffer& buffer, NameDecompressor& decompressor)
{
    //TBD
}

void
NS::to_wire(Buffer& buffer, NameCompressor& compressor) const
{
    // XXX: note that a complete implementation cannot be this simple
    // because we need to disable compression for the NS name.
    buffer.write_uint16(nsname_.get_length());
    nsname_.to_wire(buffer, compressor);
}

std::string
NS::to_text() const
{
    return (nsname_.to_text());
}

#ifdef notyet
void
RdataSet::add_rdata(rdataptr_t rdata)
{
    if (rdata->get_type() != _rdtype)
        throw DNSRdtypeMismatch();
    _rdatalist.push_back(rdata);
}

std::string
RdataSet::to_text() const
{
    std::string s;

    for (vector<rdataptr_t>::const_iterator it = _rdatalist.begin();
         it != _rdatalist.end();
         ++it)
    {
        if (!s.empty())
            s.push_back('\n');
        s += _ttl.to_text() + " " + _rdclass.to_text() + " " +
            _rdtype.to_text() + " " + (**it).to_text();
    }

    return (s);
}

std::string
RRSet::to_text() const
{
    std::string s;

    for (vector<rdataptr_t>::const_iterator it = _rdatalist.begin();
         it != _rdatalist.end();
         ++it)
    {
        if (!s.empty())
            s.push_back('\n');
        s += _name.to_text() + " ";
        s += _ttl.to_text() + " " + _rdclass.to_text() + " " +
            _rdtype.to_text() + " " + (**it).to_text();
    }

    return (s);
}

void
RRSet::add_rdata(rdataptr_t rdata)
{
    if (rdata->get_type() != _rdtype)
        throw DNSRdtypeMismatch();
    _rdatalist.push_back(rdata);
}

int
RRSet::to_wire(Message& message, section_t section)
{
    int num_rrs = 0;

    // sort Rdata list based on rrset-order and sortlist, and possible
    // other options.  Details to be considered.

    Buffer& b = message.get_iobuffer();
    NameCompressor& c = message.get_compressor();
    for (vector<rdataptr_t>::iterator it = _rdatalist.begin();
         it != _rdatalist.end();
         ++it, ++num_rrs)
    {
        _name.to_wire(b, c);
        _rdtype.to_wire(b);
        _rdclass.to_wire(b);
        _ttl.to_wire(b);
        (**it).to_wire(b, c);

        // TBD: handle truncation case
    }

    return (num_rrs);
}

std::string
Question::to_text() const
{
    // return in dig-style format.  note that in the wire format class follows
    // type.
    return (_name.to_text() + " " + _rdclass.to_text() + " " +
            _rdtype.to_text());
}

int
Question::to_wire(Message& message, section_t section)
{
    Buffer& b = message.get_iobuffer();
    NameCompressor& c = message.get_compressor();

    _name.to_wire(b, c);
    _rdtype.to_wire(b);
    _rdclass.to_wire(b);

    return (1);
}

#endif  // notyet
