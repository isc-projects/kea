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

#ifndef __RRSET_H
#define __RRSET_H 1

#include <netinet/in.h>

#include <vector>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <dns/exceptions.h>
#include <dns/buffer.h>
#include <dns/name.h>

namespace isc {
namespace dns {
class Message;
class NameCompressor;

// XXX: this should be defined somewhere else.
typedef enum { SECTION_QUESTION = 0,
               SECTION_ANSWER = 1,
               SECTION_AUTHORITY = 2,
               SECTION_ADDITIONAL = 3,
               SECTION_MAX = 4 } section_t;

class RRClass {
public:
    RRClass() {}
    explicit RRClass(uint16_t classval) : classval_(classval) {}
    explicit RRClass(const std::string& classstr);
    const std::string toText() const;
    void toWire(Buffer& b) const;
    uint16_t getValue() const { return (classval_); }
    bool operator==(const RRClass& other) const
    { return (classval_ == other.classval_); }
    bool operator!=(const RRClass& other) const
    { return (classval_ != other.classval_); }
    bool operator<(const RRClass& other) const
    { return (classval_ < other.classval_); }

    // (Some) well-known RRclass constants
    static const RRClass IN;
    static const RRClass CH;
private:
    uint16_t classval_;
};

class RRType {
public:
    RRType() {}
    explicit RRType(uint16_t typeval) : typeval_(typeval) {}
    explicit RRType(const std::string& typestr);
    const std::string toText() const;
    void toWire(Buffer& b) const;
    uint16_t getValue() const { return (typeval_); }
    bool operator==(const RRType& other) const
    { return (typeval_ == other.typeval_); }
    bool operator!=(const RRType& other) const
    { return (typeval_ != other.typeval_); }
    bool operator<(const RRType& other) const
    { return (typeval_ < other.typeval_); }

    // (Some) Well-known RRtype constants
    static const RRType A;
    static const RRType NS;
    static const RRType SOA;
    static const RRType MX;
    static const RRType TXT;
    static const RRType AAAA;
    // more to follow...

private:
    uint16_t typeval_;
};

class TTL {
public:
    TTL() {}
    explicit TTL(uint32_t ttlval) : ttlval_(ttlval) {}
    std::string toText() const
    { return (boost::lexical_cast<std::string>(ttlval_)); }
    void toWire(Buffer& b) const;
    uint32_t getValue() { return (ttlval_); }
    bool operator==(const TTL& other) const
    { return (ttlval_ == other.ttlval_); }
    bool operator!=(const TTL& other) const
    { return (ttlval_ != other.ttlval_); }
    bool operator<=(const TTL &other) const
    { return (ttlval_ <= other.ttlval_); }
    bool operator>=(const TTL &other) const
    { return (ttlval_ >= other.ttlval_); }
    bool operator<(const TTL &other) const
    { return (ttlval_ < other.ttlval_); }
    bool operator>(const TTL &other) const
    { return (ttlval_ > other.ttlval_); }
private:
    uint32_t ttlval_;
};

namespace Rdata {
// Standard DNS Rdata Subclasses
// if we worry about data copy, we may have to use
// shared pointers at the cost of depending on boost.
class Rdata;
typedef boost::shared_ptr<Rdata> RDATAPTR; // for compatibility
typedef boost::shared_ptr<Rdata> RdataPtr;
// if we want to avoid the dependency, use this; but we'll have
// to care much more about resource leak.
//typedef Rdata * RdataPtr;

// Abstract RDATA class
class Rdata {
public:
    virtual ~Rdata() {};
    virtual unsigned int count() const = 0;
    virtual const RRType& getType() const = 0;
    virtual std::string toText() const = 0;
    virtual void toWire(Buffer& b, NameCompressor& c) const = 0;
    // need generic method for getting n-th field? c.f. ldns
    // e.g. string getField(int n);

    // semi-polymorphic factories.
    static Rdata* fromText(const RRClass& rrclass, const RRType& rrtype,
                           const std::string& text_rdata);
    static Rdata* fromWire(const RRClass& rrclass, const RRType& rrtype,
                           Buffer& b, NameDecompressor& d);

    // polymorphic copy constructor (XXX should revisit it)
    virtual Rdata* copy() const = 0;
};

namespace Generic {
class NS : public Rdata::Rdata {
public:
    NS() {}
    explicit NS(const std::string& namestr) : nsname_(namestr) {}
    explicit NS(const Name& nsname) : nsname_(nsname) {}
    explicit NS(Buffer& buffer, NameDecompressor& decompressor);
    unsigned int count() const { return (1); }
    const RRType& getType() const { return (RRType::NS); }
    static const RRType& getTypeStatic() { return (RRType::NS); }
    std::string toText() const;
    void toWire(Buffer& b, NameCompressor& c) const;
    const std::string getNsname() const { return (nsname_.toText(false)); }
    bool operator==(const NS &other) const
    { return (nsname_ == other.nsname_); }
    virtual bool operator!=(const NS &other) const { return !(*this == other); }
    virtual Rdata* copy() const;
private:
    Name nsname_;
};

class MX : public Rdata::Rdata {
public:
    MX() {}
    explicit MX(uint16_t preference, const std::string& namestr) :
        preference_(preference), mxname_(namestr) {}
    explicit MX(Buffer& buffer, NameDecompressor& decompressor);
    unsigned int count() const { return (1); }
    const RRType& getType() const { return (RRType::MX); }
    static const RRType& getTypeStatic() { return (RRType::MX); }
    std::string toText() const;
    void toWire(Buffer& buffer, NameCompressor& compressor) const;
    bool operator==(const MX& other) const
    { return (preference_ == other.preference_ && mxname_ == other.mxname_); }
    virtual bool operator!=(const MX &other) const { return !(*this == other); }
    virtual Rdata* copy() const;
private:
    uint16_t preference_;
    Name mxname_;
};

class SOA : public Rdata::Rdata {
public:
    SOA() {}
    explicit SOA(const std::string& mname, const std::string& rname,
                 uint32_t serial, uint32_t refresh, uint32_t retry,
                 uint32_t expire, const TTL& ttl) :
        mname_(mname), rname_(rname), serial_(serial), refresh_(refresh),
        retry_(retry), expire_(expire), ttl_(ttl) {}
    explicit SOA(Buffer& buffer, NameDecompressor& decompressor);
    unsigned int count() const { return (1); }
    const RRType& getType() const { return (RRType::SOA); }
    static const RRType& getTypeStatic() { return (RRType::SOA); }
    std::string toText() const;
    void toWire(Buffer& buffer, NameCompressor& compressor) const;
    bool operator==(const SOA &other) const;
    virtual bool operator!=(const SOA &other) const
    { return !(*this == other); }
    virtual Rdata* copy() const;
private:
    Name mname_;
    Name rname_;
    uint32_t serial_;
    uint32_t refresh_;
    uint32_t retry_;
    uint32_t expire_;
    TTL ttl_;
};

inline bool
SOA::operator==(const SOA& other) const
{
    return (mname_ == other.mname_ && rname_ == other.rname_ &&
            serial_ == other.serial_ && refresh_ == other.refresh_ &&
            retry_ == other.retry_ && expire_ == other.expire_ &&
            ttl_ == other.ttl_);
}

// A quick hack implementation of TXT RR.  It currently supports only one
// "character-string".
class TXT : public Rdata::Rdata {
public:
    TXT() {}
    explicit TXT(const std::string& text_data);
    unsigned int count() const { return (string_list.size()); }
    const RRType& getType() const { return (RRType::TXT); }
    static const RRType& getTypeStatic() { return (RRType::TXT); }
    std::string toText() const;
    void fromWire(Buffer& b, NameDecompressor& c);
    void toWire(Buffer& b, NameCompressor& c) const;
    bool operator==(const TXT &other) const;
    virtual bool operator!=(const TXT &other) const
    { return !(*this == other); }
    virtual Rdata* copy() const;
private:
    static const unsigned int MAX_CHARACTER_STRING = 255;
    std::vector<std::string> string_list;
};
// add MXRdata, etc...
}

namespace IN {
class A : public Rdata::Rdata {
public:
    A() {}
    // constructor from a textual IPv4 address
    explicit A(const std::string& addrstr);
    explicit A(Buffer& buffer, NameDecompressor& decompressor);
    unsigned int count() const { return (1); }
    const RRType& getType() const { return (RRType::A); }
    static const RRType& getTypeStatic() { return (RRType::A); }
    std::string toText() const;
    void toWire(Buffer& b, NameCompressor& c) const;
    const struct in_addr& getAddress() const { return (addr_); }
    bool operator==(const A &other) const
    { return (addr_.s_addr == other.addr_.s_addr); }
    virtual bool operator!=(const A &other) const
    { return !(*this == other); }
    virtual Rdata* copy() const;
private:
    // XXX: should probably define an "address class" and use it.
    struct in_addr addr_;
};

class AAAA : public Rdata::Rdata {
public:
    AAAA() {}
    // constructor from a textual IPv6 address
    explicit AAAA(const std::string& addrstr);
    explicit AAAA(Buffer& buffer, NameDecompressor& decompressor);
    unsigned int count() const { return (1); }
    std::string toText() const;
    const RRType& getType() const { return (RRType::AAAA); }
    static const RRType& getTypeStatic() { return (RRType::AAAA); }
    void toWire(Buffer& b, NameCompressor& c) const;
    const struct in6_addr& getAddress() const { return (addr_); }
    bool operator==(const AAAA &other) const
    { return (IN6_ARE_ADDR_EQUAL(&addr_, &other.addr_)); }
    virtual bool operator!=(const AAAA &other) const
    { return !(*this == other); }
    virtual Rdata* copy() const;
private:
    // XXX: should probably define an "address class" and use it.
    struct in6_addr addr_;
};
}
}

// An RRset.  Conceptually it's a named RdataSet.  A (section
// of) DNS message would consist of a list of RRsets.
// This is a primary class internally used in our major software such as name
// servers.
//
// Note about terminology: there has been a discussion at the IETF namedroppers
// ML about RRset vs RRSet (case of "s").  While RFC2181 uses the latter,
// many other RFCs use the former, and most of the list members who showed
// their opinion seem to prefer RRset.  We follow that preference in this
// implementation.
//
// Open Issues:
//   - add more set-like operations, e.g, merge?
//   - add a "sort" method?  "search(find)" method?
//   - BIND9 libdns has some special DNSSEC-related methods
//     such as addnoqname(), addclosest().  do we need these?
//   - need to check duplicate rdata in addrdata()?
//   - need a comparison method?  if so, should it compare
//     rdata's as a set or as a list (compare each rdata one
//     by one)?  ldns has ldns_rr_list_compare(), which takes
//     the latter approach (assuming the caller sorts the lists
//     beforehand?).
class AbstractRRset {
public:
    virtual ~AbstractRRset() {}
    virtual std::string toText() const = 0;
    virtual int toWire(Buffer& buffer, NameCompressor& compressor,
                        section_t section) = 0;
    virtual void addRdata(Rdata::RdataPtr rdata) = 0;
    virtual unsigned int countRdata() const = 0;
    virtual const Name& getName() const = 0;
    virtual const RRClass& getClass() const = 0;
    virtual const RRType& getType() const = 0;
    virtual const TTL& getTtl() const = 0;
    virtual void setTtl(const TTL& ttl) = 0;
};

class RRset : public AbstractRRset {
public:
    RRset() {}
    explicit RRset(const Name &name, const RRClass &rrclass,
                   const RRType &rrtype, const TTL &ttl) :
        name_(name), rrclass_(rrclass), rrtype_(rrtype), ttl_(ttl) {}
    unsigned int countRdata() const { return (rdatalist_.size()); }
    void addRdata(Rdata::RdataPtr rdata);
    void removeRdata(const Rdata::Rdata& rdata);
    std::string toText() const;
    int toWire(Buffer& buffer, NameCompressor& compressor, section_t section);
    const Name& getName() const { return (name_); } 
    const RRClass& getClass() const { return (rrclass_); }
    const RRType& getType() const { return (rrtype_); }
    const TTL& getTtl() const { return (ttl_); }
    // once constructed, only TTL and rdatalist can be modified.
    void setTtl(const TTL& ttl) { ttl_ = ttl; }
    const std::vector<Rdata::RdataPtr>& getRdatalist() const
    { return (rdatalist_); }
    template <typename T> void getRdatalist(std::vector<T>&) const;
private:
    Name name_;
    RRClass rrclass_;
    RRType rrtype_;
    TTL ttl_;
    std::vector<Rdata::RdataPtr> rdatalist_;
};

//
// Generic Question section entry
// XXX: it seems to be not a good idea to inherit from RRset.  We should
// probably re-define it as a separate class.
//
class Question : public AbstractRRset {
public:
    explicit Question(const Name& name, const RRClass& rrclass,
             const RRType& rrtype) :
        name_(name), rrclass_(rrclass), rrtype_(rrtype), ttl_(0) {}
    std::string toText() const;
    int toWire(Buffer& buffer, NameCompressor& compressor, section_t section);
    unsigned int countRdata() const { return (0); }
    const Name& getName() const { return (name_); }
    const RRClass& getClass() const { return (rrclass_); }
    const RRType& getType() const { return (rrtype_); }
    const TTL& getTtl() const { return (ttl_); } // XXX
    void setTtl(const TTL& ttl) {}              // XXX
    void addRdata(Rdata::RdataPtr rdata) {}     // XXX
private:
    Name name_;
    RRClass rrclass_;
    RRType rrtype_;
    TTL ttl_;
};

// TBD: this interface should be revisited.
template <typename T>
void
RRset::getRdatalist(std::vector<T>& v) const
{
    std::vector<Rdata::RdataPtr>::const_iterator it;
    for (it = rdatalist_.begin(); it != rdatalist_.end(); ++it) {
        const T& concreteRdata = static_cast<const T&>(**it); // XXX
        if (T::getTypeStatic() != (**it).getType()) {
            throw DNSRRtypeMismatch();
        }
        v.push_back(concreteRdata);
    }
}

// A single RR.  Architecturally this is redundant, but it
// would often be convenient if we can handle each RR
// separately.
// Note: an RR *is-not-a* set, so conceptually it cannot be a
// derived class of RdataSet.
class RR {
public:
    RR() {}
    explicit RR(const std::string& rrstr);
    explicit RR(const Name& name, const RRClass& rrclass,
                const RRType& rrtype, const TTL& ttl,
                const Rdata::Rdata& rdata);
    explicit RR(const Name& name, const RRClass& rrclass,
                const RRType& rrtype, const TTL& ttl,
                Rdata::RdataPtr rdata);
    std::string toText() const { return (rrset_.toText()); }
    const Name& getName() const { return (rrset_.getName()); }
    const RRClass& getClass() const { return (rrset_.getClass()); }
    const RRType& getType() const { return (rrset_.getType()); }
    const TTL& getTtl() const { return (rrset_.getTtl()); }
    const Rdata::RdataPtr getRdata() const
    { return (*rrset_.getRdatalist().begin()); }
    void setTtl(const TTL& ttl) { rrset_.setTtl(ttl); }
private:
    // An RR is (could be) actually implemented as an RRset containing at most
    // one RR.
    RRset rrset_;
};
}
}
#endif  // __RRSET_H

// Local Variables: 
// mode: c++
// End: 
