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
//#include <cstring>
#include <utility>
#include <map>

#include <dns/buffer.h>
#include <dns/rrset.h>

using std::pair;
using std::map;

using isc::dns::RRClass;
using isc::dns::RRType;
using isc::dns::TTL;
using isc::dns::Rdata::IN::A;
using isc::dns::Rdata::IN::AAAA;
using isc::dns::Rdata::Generic::NS;
using isc::dns::RRset;
using isc::dns::Rdata::Rdata;
using isc::dns::Question;
using isc::dns::RR;

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
RRClass::toText() const
{
    // XXX: quick hack
    if (classval_ == 1)
        return ("IN");
    else if (classval_ == 3)
        return ("CH");
    throw std::runtime_error("unexpected class");
}

void
RRClass::toWire(isc::Buffer& b) const
{
    b.writeUint16(classval_);
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
RRType::toText() const
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
RRType::toWire(Buffer& buffer) const
{
    buffer.writeUint16(typeval_);
}

const RRType RRType::A("A");
const RRType RRType::NS("NS");
const RRType RRType::AAAA("AAAA");
// ...more to follow

void
TTL::toWire(Buffer& buffer) const
{
    buffer.writeUint32(ttlval_);
}

typedef Rdata* (*RdataFactory)(const std::string& text_rdata);
typedef pair<RRClass, RRType> RRClassTypePair;
static map<RRClassTypePair, RdataFactory> rdata_factory_repository;

struct RdataFactoryRegister {
public:
    RdataFactoryRegister();
    ~RdataFactoryRegister() {}
private:
};

static RdataFactoryRegister rdata_factory;

Rdata *
createADataFromText(const std::string& text_rdata)
{
    return (new A(text_rdata));
}

Rdata *
createAAAADataFromText(const std::string& text_rdata)
{
    return (new AAAA(text_rdata));
}

Rdata *
createNSDataFromText(const std::string& text_rdata)
{
    return (new NS(text_rdata));
}

RdataFactoryRegister::RdataFactoryRegister()
{
    rdata_factory_repository.insert(pair<RRClassTypePair, RdataFactory>
                                    (RRClassTypePair(RRClass::IN, RRType::A),
                                     createADataFromText));
    rdata_factory_repository.insert(pair<RRClassTypePair, RdataFactory>
                                    (RRClassTypePair(RRClass::IN, RRType::AAAA),
                                     createAAAADataFromText));
    //XXX: NS belongs to the 'generic' class.  should revisit it.
    rdata_factory_repository.insert(pair<RRClassTypePair, RdataFactory>
                                    (RRClassTypePair(RRClass::IN, RRType::NS),
                                     createNSDataFromText));
}

Rdata *
Rdata::fromText(const RRClass& rrclass, const RRType& rrtype,
                const std::string& text_rdata)
{
    map<RRClassTypePair, RdataFactory>::const_iterator entry;
    entry = rdata_factory_repository.find(RRClassTypePair(rrclass, rrtype));
    if (entry != rdata_factory_repository.end()) {
        return (entry->second(text_rdata));
    }

    throw DNSInvalidRRType();
}

A::A(const std::string& addrstr)
{
    if (inet_pton(AF_INET, addrstr.c_str(), &addr_) != 1)
        throw ISCInvalidAddressString();
}

void
A::fromWire(Buffer& buffer, NameDecompressor& decompressor)
{
    //TBD
}

void
A::toWire(Buffer& buffer, NameCompressor& compressor) const
{
    buffer.writeUint16(sizeof(addr_));
    buffer.writeData(&addr_, sizeof(addr_));
}

std::string
A::toText() const
{
    char addrbuf[sizeof("255.255.255.255")];

    if (inet_ntop(AF_INET, &addr_, addrbuf, sizeof(addrbuf)) == NULL)
        throw std::runtime_error("unexpected inet_ntop() failure");

    return (std::string(addrbuf));
}

Rdata*
A::copy() const
{
    return (new A(toText()));
}

AAAA::AAAA(const std::string& addrstr)
{
    if (inet_pton(AF_INET6, addrstr.c_str(), &addr_) != 1)
        throw ISCInvalidAddressString();
}

void
AAAA::fromWire(Buffer& buffer, NameDecompressor& decompressor)
{
    //TBD
}

void
AAAA::toWire(Buffer& buffer, NameCompressor& compressor) const
{
    buffer.writeUint16(sizeof(addr_));
    buffer.writeData(&addr_, sizeof(addr_));
}

std::string
AAAA::toText() const
{
    char addrbuf[sizeof("ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255")];

    if (inet_ntop(AF_INET6, &addr_, addrbuf, sizeof(addrbuf)) == NULL)
        throw std::runtime_error("unexpected inet_ntop() failure");

    return (std::string(addrbuf));
}

Rdata*
AAAA::copy() const
{
    return (new AAAA(toText()));
}

void
NS::fromWire(Buffer& buffer, NameDecompressor& decompressor)
{
    //TBD
}

void
NS::toWire(Buffer& buffer, NameCompressor& compressor) const
{
    // XXX: note that a complete implementation cannot be this simple
    // because we need to disable compression for the NS name.
    buffer.writeUint16(nsname_.getLength());
    nsname_.toWire(buffer, compressor);
}

std::string
NS::toText() const
{
    return (nsname_.toText());
}

Rdata*
NS::copy() const
{
    return (new NS(toText()));
}

std::string
RRset::toText() const
{
    std::string s;

    for (std::vector<Rdata::RdataPtr>::const_iterator it = rdatalist_.begin();
         it != rdatalist_.end();
         ++it)
    {
        if (!s.empty())
            s.push_back('\n');
        s += name_.toText() + " ";
        s += ttl_.toText() + " " + rrclass_.toText() + " " +
            rrtype_.toText() + " " + (**it).toText();
    }

    return (s);
}

void
RRset::addRdata(Rdata::RdataPtr rdata)
{
    if (rdata->getType() != rrtype_)
        throw DNSRRtypeMismatch();
    rdatalist_.push_back(rdata);
}

int
RRset::toWire(Buffer& buffer, NameCompressor& compressor, section_t section)
{
    int num_rrs = 0;

    // sort Rdata list based on rrset-order and sortlist, and possible
    // other options.  Details to be considered.
    // section is not currently used.  will be, when we implement rrset-order
    // etc.

    for (std::vector<Rdata::RdataPtr>::iterator it = rdatalist_.begin();
         it != rdatalist_.end();
         ++it, ++num_rrs)
    {
        name_.toWire(buffer, compressor);
        rrtype_.toWire(buffer);
        rrclass_.toWire(buffer);
        ttl_.toWire(buffer);
        (**it).toWire(buffer, compressor);

        // TBD: handle truncation case
    }

    return (num_rrs);
}

std::string
Question::toText() const
{
    // return in dig-style format.  note that in the wire format class follows
    // type.
    return (name_.toText() + " " + rrclass_.toText() + " " +
            rrtype_.toText());
}

int
Question::toWire(Buffer& buffer, NameCompressor& compressor, section_t section)
{
    name_.toWire(buffer, compressor);
    rrtype_.toWire(buffer);
    rrclass_.toWire(buffer);

    return (1);
}

RR::RR(const Name& name, const RRClass& rrclass, const RRType& rrtype,
       const TTL& ttl, const Rdata::Rdata& rdata) :
    rrset_(name, rrclass, rrtype, ttl)
{
    rrset_.addRdata(Rdata::RdataPtr(rdata.copy()));
}

RR::RR(const Name& name, const RRClass& rrclass, const RRType& rrtype,
       const TTL& ttl, Rdata::RdataPtr rdata) :
    rrset_(name, rrclass, rrtype, ttl)
{
    rrset_.addRdata(rdata);
}
