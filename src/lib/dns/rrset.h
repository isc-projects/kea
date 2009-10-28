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
    const std::string to_text() const;
    void to_wire(Buffer& b) const;
    uint16_t get_value() const { return (classval_); }
    bool operator==(const RRClass& other) const
    { return (classval_ == other.classval_); }
    bool operator!=(const RRClass& other) const
    { return (classval_ != other.classval_); }

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
    const std::string to_text() const;
    void to_wire(Buffer& b) const;
    uint16_t get_value() const { return (typeval_); }
    bool operator==(const RRType& other) const
    { return (typeval_ == other.typeval_); }
    bool operator!=(const RRType& other) const
    { return (typeval_ != other.typeval_); }

    // (Some) Well-known RRtype constants
    static const RRType A;
    static const RRType NS;
    static const RRType AAAA;
    // more to follow...

private:
    uint16_t typeval_;
};

class TTL {
public:
    TTL() {}
    explicit TTL(uint32_t ttlval) : ttlval_(ttlval) {}
    std::string to_text() const
    { return (boost::lexical_cast<std::string>(ttlval_)); }
    void to_wire(Buffer& b) const;
    uint32_t get_value() { return (ttlval_); }
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
typedef boost::shared_ptr<Rdata> RDATAPTR;
// if we want to avoid the dependency, use this; but we'll have
// to care much more about resource leak.
//typedef Rdata * RDATAPTR;

// Abstract RDATA class
class Rdata {
public:
    virtual ~Rdata() {};
    virtual unsigned int count() const = 0;
    virtual const RRType& get_type() const = 0;
    virtual std::string to_text() const = 0;
    virtual void from_wire(Buffer& b, NameDecompressor& c) = 0;
    virtual void to_wire(Buffer& b, NameCompressor& c) const = 0;
    // need generic method for getting n-th field? c.f. ldns
    // e.g. string getField(int n);

    // polymorphic copy constructor (XXX should revisit it)
    virtual Rdata* copy() const = 0;
};

namespace Generic {
class NS : public Rdata::Rdata {
public:
    NS() {}
    explicit NS(const std::string& namestr) : nsname_(namestr) {}
    explicit NS(const Name& nsname) : nsname_(nsname) {}
    unsigned int count() const { return (1); }
    const RRType& get_type() const { return (RRType::NS); }
    static const RRType& get_type_static() { return (RRType::NS); }
    std::string to_text() const;
    void from_wire(Buffer& b, NameDecompressor& c);
    void to_wire(Buffer& b, NameCompressor& c) const;
    const std::string get_nsname() const { return (nsname_.to_text(false)); }
    bool operator==(const NS &other) const
    { return (nsname_ == other.nsname_); }
    virtual bool operator!=(const NS &other) const { return !(*this == other); }
    virtual Rdata* copy() const;
private:
    Name nsname_;
};
// add MXRdata, etc...
}

namespace IN {
class A : public Rdata::Rdata {
public:
    A() {}
    // constructor from a textual IPv4 address
    explicit A(const std::string& addrstr);
    unsigned int count() const { return (1); }
    const RRType& get_type() const { return (RRType::A); }
    static const RRType& get_type_static() { return (RRType::A); }
    std::string to_text() const;
    void from_wire(Buffer& b, NameDecompressor& c);
    void to_wire(Buffer& b, NameCompressor& c) const;
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
    unsigned int count() const { return (1); }
    std::string to_text() const;
    const RRType& get_type() const { return (RRType::AAAA); }
    static const RRType& get_type_static() { return (RRType::AAAA); }
    void from_wire(Buffer& b, NameDecompressor& c);
    void to_wire(Buffer& b, NameCompressor& c) const;
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
    virtual std::string to_text() const = 0;
    virtual int to_wire(Buffer& buffer, NameCompressor& compressor,
                        section_t section) = 0;
    virtual void add_rdata(Rdata::RDATAPTR rdata) = 0;
    virtual unsigned int count_rdata() const = 0;
    virtual const Name& get_name() const = 0;
    virtual const RRClass& get_class() const = 0;
    virtual const RRType& get_type() const = 0;
    virtual const TTL& get_ttl() const = 0;
    virtual void set_ttl(const TTL& ttl) = 0;
};

class RRset : public AbstractRRset {
public:
    RRset() {}
    explicit RRset(const Name &name, const RRClass &rrclass,
                   const RRType &rrtype, const TTL &ttl) :
        name_(name), rrclass_(rrclass), rrtype_(rrtype), ttl_(ttl) {}
    unsigned int count_rdata() const { return (rdatalist_.size()); }
    void add_rdata(Rdata::RDATAPTR rdata);
    void remove_rdata(const Rdata::Rdata& rdata);
    std::string to_text() const;
    int to_wire(Buffer& buffer, NameCompressor& compressor, section_t section);
    const Name& get_name() const { return (name_); } 
    const RRClass& get_class() const { return (rrclass_); }
    const RRType& get_type() const { return (rrtype_); }
    const TTL& get_ttl() const { return (ttl_); }
    // once constructed, only TTL and rdatalist can be modified.
    void set_ttl(const TTL& ttl) { ttl_ = ttl; }
    const std::vector<Rdata::RDATAPTR>& get_rdatalist() const
    { return (rdatalist_); }
    template <typename T> void get_rdatalist(std::vector<T>&) const;
private:
    Name name_;
    RRClass rrclass_;
    RRType rrtype_;
    TTL ttl_;
    std::vector<Rdata::RDATAPTR> rdatalist_;
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
    std::string to_text() const;
    int to_wire(Buffer& buffer, NameCompressor& compressor, section_t section);
    unsigned int count_rdata() const { return (0); }
    const Name& get_name() const { return (name_); }
    const RRClass& get_class() const { return (rrclass_); }
    const RRType& get_type() const { return (rrtype_); }
    const TTL& get_ttl() const { return (ttl_); } // XXX
    void set_ttl(const TTL& ttl) {}              // XXX
    void add_rdata(Rdata::RDATAPTR rdata) {}     // XXX
private:
    Name name_;
    RRClass rrclass_;
    RRType rrtype_;
    TTL ttl_;
};

// TBD: this interface should be revisited.
template <typename T>
void
RRset::get_rdatalist(std::vector<T>& v) const
{
    std::vector<Rdata::RDATAPTR>::const_iterator it;
    for (it = rdatalist_.begin(); it != rdatalist_.end(); ++it) {
        const T& concreteRdata = static_cast<const T&>(**it); // XXX
        if (T::get_type_static() != (**it).get_type()) {
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
    std::string to_text() const { return (rrset_.to_text()); }
    const Name& get_name() const { return (rrset_.get_name()); }
    const RRClass& get_class() const { return (rrset_.get_class()); }
    const RRType& get_type() const { return (rrset_.get_type()); }
    const TTL& get_ttl() const { return (rrset_.get_ttl()); }
    const Rdata::RDATAPTR get_rdata() const
    { return (*rrset_.get_rdatalist().begin()); }
    void set_ttl(const TTL& ttl) { rrset_.set_ttl(ttl); }
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
