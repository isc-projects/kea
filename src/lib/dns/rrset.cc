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
using ISC::DNS::RRset;
using ISC::DNS::Question;
using ISC::DNS::RR;

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

std::string
RRset::to_text() const
{
    std::string s;

    for (std::vector<Rdata::RDATAPTR>::const_iterator it = rdatalist_.begin();
         it != rdatalist_.end();
         ++it)
    {
        if (!s.empty())
            s.push_back('\n');
        s += name_.to_text() + " ";
        s += ttl_.to_text() + " " + rdclass_.to_text() + " " +
            rdtype_.to_text() + " " + (**it).to_text();
    }

    return (s);
}

void
RRset::add_rdata(Rdata::RDATAPTR rdata)
{
    if (rdata->get_type() != rdtype_)
        throw DNSRdtypeMismatch();
    rdatalist_.push_back(rdata);
}

int
RRset::to_wire(Buffer& buffer, NameCompressor& compressor, section_t section)
{
    int num_rrs = 0;

    // sort Rdata list based on rrset-order and sortlist, and possible
    // other options.  Details to be considered.
    // section is not currently used.  will be, when we implement rrset-order
    // etc.

    for (std::vector<Rdata::RDATAPTR>::iterator it = rdatalist_.begin();
         it != rdatalist_.end();
         ++it, ++num_rrs)
    {
        name_.to_wire(buffer, compressor);
        rdtype_.to_wire(buffer);
        rdclass_.to_wire(buffer);
        ttl_.to_wire(buffer);
        (**it).to_wire(buffer, compressor);

        // TBD: handle truncation case
    }

    return (num_rrs);
}

std::string
Question::to_text() const
{
    // return in dig-style format.  note that in the wire format class follows
    // type.
    return (name_.to_text() + " " + rdclass_.to_text() + " " +
            rdtype_.to_text());
}

int
Question::to_wire(Buffer& buffer, NameCompressor& compressor, section_t section)
{
    name_.to_wire(buffer, compressor);
    rdtype_.to_wire(buffer);
    rdclass_.to_wire(buffer);

    return (1);
}

RR::RR(const Name& name, const RRClass& rrclass, const RRType& rrtype,
       const TTL& ttl, const Rdata::Rdata& rdata) :
    rrset_(name, rrclass, rrtype, ttl)
{
    // XXX: this implementation is BAD.  we took the ugly bad fastest approach
    // for rapid experiment.  should rewrite it.
    if (rrtype == RRType::A) {
        rrset_.add_rdata(Rdata::RDATAPTR(new A(rdata.to_text())));
    } else if (rrtype == RRType::AAAA) {
        rrset_.add_rdata(Rdata::RDATAPTR(new AAAA(rdata.to_text())));
    } else if (rrtype == RRType::NS) {
        rrset_.add_rdata(Rdata::RDATAPTR(new NS(rdata.to_text())));
    } else {
        // XXX
        throw std::runtime_error("RR constructor encountered "
                                 "an unsupported type");
    }
}
