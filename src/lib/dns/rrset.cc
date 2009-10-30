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

#include <iostream>
#include <stdexcept>
#include <utility>
#include <map>

#include <boost/shared_ptr.hpp>

#include <dns/buffer.h>
#include <dns/rrset.h>

using std::pair;
using std::map;

using isc::Buffer;
using isc::dns::NameDecompressor;
using isc::dns::RRClass;
using isc::dns::RRType;
using isc::dns::TTL;
using isc::dns::Rdata::IN::A;
using isc::dns::Rdata::IN::AAAA;
using isc::dns::Rdata::Generic::NS;
using isc::dns::Rdata::Generic::SOA;
using isc::dns::Rdata::Generic::TXT;
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
    else if (typestr == "SOA")
        typeval_ = 6;
    else if (typestr == "TXT")
        typeval_ = 16;
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
    else if (typeval_ == 6)
        return ("SOA");
    else if (typeval_ == 16)
        return ("TXT");
    else if (typeval_ == 28)
        return ("AAAA");
    else {
        std::stringstream ss;
        ss << "TYPE" << typeval_;
        return (ss.str());
    }
}

void
RRType::toWire(Buffer& buffer) const
{
    buffer.writeUint16(typeval_);
}

const RRType RRType::A("A");
const RRType RRType::NS("NS");
const RRType RRType::SOA("SOA");
const RRType RRType::TXT("TXT");
const RRType RRType::AAAA("AAAA");
// ...more to follow

void
TTL::toWire(Buffer& buffer) const
{
    buffer.writeUint32(ttlval_);
}

typedef Rdata* (*TextRdataFactory)(const std::string& text_rdata);
typedef Rdata* (*WireRdataFactory)(Buffer& buffer,
                                   NameDecompressor& decompressor);
typedef pair<RRClass, RRType> RRClassTypePair;
static map<RRClassTypePair, TextRdataFactory> text_rdata_factory_repository;
static map<RRClassTypePair, WireRdataFactory> wire_rdata_factory_repository;

struct RdataFactoryRegister {
public:
    RdataFactoryRegister();
    ~RdataFactoryRegister() {}
private:
};

static RdataFactoryRegister rdata_factory;

template <typename T>
Rdata*
createDataFromText(const std::string& text_rdata)
{
    return (new T(text_rdata));
}

template <typename T>
Rdata*
createDataFromWire(Buffer& buffer, NameDecompressor& decompressor)
{
    return (new T(buffer, decompressor));
}

RdataFactoryRegister::RdataFactoryRegister()
{
    text_rdata_factory_repository.insert(pair<RRClassTypePair, TextRdataFactory>
                             (RRClassTypePair(RRClass::IN, RRType::A),
                              createDataFromText<isc::dns::Rdata::IN::A>));
    text_rdata_factory_repository.insert(pair<RRClassTypePair, TextRdataFactory>
                             (RRClassTypePair(RRClass::IN, RRType::AAAA),
                              createDataFromText<isc::dns::Rdata::IN::AAAA>));
    //XXX: NS/TXT/SOA belongs to the 'generic' class.  should revisit it.
    text_rdata_factory_repository.insert(pair<RRClassTypePair, TextRdataFactory>
                             (RRClassTypePair(RRClass::IN, RRType::NS),
                              createDataFromText<isc::dns::Rdata::Generic::NS>));
    text_rdata_factory_repository.insert(pair<RRClassTypePair, TextRdataFactory>
                             (RRClassTypePair(RRClass::IN, RRType::TXT),
                              createDataFromText<isc::dns::Rdata::Generic::TXT>));

    // "fromText" for SOA is not yet implemented: parsing multi-field RDATA
    // is not trivial.

    // XXX: we should treat class-agnostic type accordingly.
    text_rdata_factory_repository.insert(pair<RRClassTypePair, TextRdataFactory>
                             (RRClassTypePair(RRClass::CH, RRType::TXT),
                              createDataFromText<isc::dns::Rdata::Generic::TXT>));

    wire_rdata_factory_repository.insert(pair<RRClassTypePair, WireRdataFactory>
                             (RRClassTypePair(RRClass::IN, RRType::A),
                              createDataFromWire<isc::dns::Rdata::IN::A>));
    wire_rdata_factory_repository.insert(pair<RRClassTypePair, WireRdataFactory>
                             (RRClassTypePair(RRClass::IN, RRType::AAAA),
                              createDataFromWire<isc::dns::Rdata::IN::AAAA>));
    wire_rdata_factory_repository.insert(pair<RRClassTypePair, WireRdataFactory>
                             (RRClassTypePair(RRClass::IN, RRType::NS),
                              createDataFromWire<isc::dns::Rdata::Generic::NS>));
    wire_rdata_factory_repository.insert(pair<RRClassTypePair, WireRdataFactory>
                             (RRClassTypePair(RRClass::IN, RRType::SOA),
                              createDataFromWire<isc::dns::Rdata::Generic::SOA>));
}

Rdata *
Rdata::fromText(const RRClass& rrclass, const RRType& rrtype,
                const std::string& text_rdata)
{
    map<RRClassTypePair, TextRdataFactory>::const_iterator entry;
    entry = text_rdata_factory_repository.find(RRClassTypePair(rrclass,
                                                               rrtype));
    if (entry != text_rdata_factory_repository.end()) {
        return (entry->second(text_rdata));
    }

    throw DNSInvalidRRType();
}

Rdata *
Rdata::fromWire(const RRClass& rrclass, const RRType& rrtype,
                Buffer& buffer, NameDecompressor& decompressor)
{
    map<RRClassTypePair, WireRdataFactory>::const_iterator entry;
    entry = wire_rdata_factory_repository.find(RRClassTypePair(rrclass,
                                                               rrtype));
    if (entry != wire_rdata_factory_repository.end()) {
        return (entry->second(buffer, decompressor));
    }

    throw DNSInvalidRRType();
}

A::A(const std::string& addrstr)
{
    if (inet_pton(AF_INET, addrstr.c_str(), &addr_) != 1)
        throw ISCInvalidAddressString();
}

A::A(Buffer& buffer, NameDecompressor& decompressor)
{
    size_t len = buffer.readUint16();
    if (len != sizeof(addr_))
        throw DNSInvalidRdata();
    buffer.readData(&addr_, sizeof(addr_));
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

AAAA::AAAA(Buffer& buffer, NameDecompressor& decompressor)
{
    if (buffer.readUint16() != sizeof(addr_))
        throw DNSInvalidRdata();
    buffer.readData(&addr_, sizeof(addr_));
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

NS::NS(Buffer& buffer, NameDecompressor& decompressor)
{
    size_t len = buffer.readUint16();
    nsname_ = Name(buffer, decompressor);
    if (nsname_.getLength() < len)
        throw DNSInvalidRdata();
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

SOA::SOA(Buffer& buffer, NameDecompressor& decompressor)
{
    size_t len = buffer.readUint16();
    mname_ = Name(buffer, decompressor);
    rname_ = Name(buffer, decompressor);
    serial_ = buffer.readUint32();
    refresh_ = buffer.readUint32();
    retry_ = buffer.readUint32();
    expire_ = buffer.readUint32();
    ttl_ = TTL(buffer.readUint32());
}

void
SOA::toWire(Buffer& buffer, NameCompressor& compressor) const
{
    // XXX: note that a complete implementation cannot be this simple
    // because we need to disable compression for the NS name.
    buffer.writeUint16(mname_.getLength() + rname_.getLength() +
                       5 * sizeof(uint32_t));
    mname_.toWire(buffer, compressor);
    rname_.toWire(buffer, compressor);
    buffer.writeUint32(serial_);
    buffer.writeUint32(refresh_);
    buffer.writeUint32(retry_);
    buffer.writeUint32(expire_);
    ttl_.toWire(buffer);
}

std::string
SOA::toText() const
{
    return (mname_.toText() + " " + rname_.toText() + " " +
            boost::lexical_cast<std::string>(serial_) + " " +
            boost::lexical_cast<std::string>(refresh_) + " " +
            boost::lexical_cast<std::string>(retry_) + " " +
            boost::lexical_cast<std::string>(expire_) + " " +
            ttl_.toText());
}

Rdata*
SOA::copy() const
{
    return (new SOA(mname_.toText(), rname_.toText(), serial_, refresh_, retry_,
                    expire_, ttl_));
}

TXT::TXT(const std::string& text_data)
{
    size_t length = text_data.size();
    size_t pos_begin = 0;

    if (length > 1 && text_data[0] == '"' && text_data[length - 1] == '"') {
        pos_begin = 1;
        length -= 2;
    }
    if (text_data.size() > MAX_CHARACTER_STRING)
        throw DNSCharStringTooLong();
    string_list.push_back(text_data.substr(pos_begin, length));
}

bool
TXT::operator==(const TXT& other) const
{
    std::vector<std::string>::const_iterator lit, rit;

    if (count() != other.count())
        return (false);

    lit = string_list.begin();
    rit = other.string_list.begin();
    while (lit != string_list.end()) {
        if (*lit != *rit)
            return (false);
        ++lit;
        ++rit;
    }

    return (true);
}

void
TXT::fromWire(Buffer& buffer, NameDecompressor& decompressor)
{
    //TBD
}

void
TXT::toWire(Buffer& buffer, NameCompressor& compressor) const
{
    std::vector<std::string>::const_iterator it;
    size_t total_length = 0;
    size_t length_pos;

    length_pos = buffer.getSize();
    buffer.writeUint16(0);      // dummy data.  filled in later

    for (it = string_list.begin(); it != string_list.end(); ++it) {
        buffer.writeUint8((*it).size());
        buffer.writeData((*it).c_str(), (*it).size());
        total_length += (*it).size() + 1;
    }

    buffer.writeUint16At(total_length, length_pos);
}

std::string
TXT::toText() const
{
    std::vector<std::string>::const_iterator it;
    std::string s;

    // XXX: this implementation is not entirely correct.  for example, it
    // should escape double-quotes if they appear in the character string.
    for (it = string_list.begin(); it != string_list.end(); ++it) {
        if (!s.empty())
            s.push_back(' ');
        s.push_back('"');
        s += *it;
        s.push_back('"');
    }

    return (s);
}

Rdata*
TXT::copy() const
{
    return (new TXT(toText()));
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
