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

#ifndef __MESSAGE_H
#define __MESSAGE_H 1

#include <sys/socket.h>

#include <vector>
#include <string>

#include <boost/shared_ptr.hpp>

#include <dns/exceptions.h>
#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/rrset.h>

namespace isc {
namespace dns {
typedef uint8_t rcode_t; // we actually only need 4 bits of it
typedef uint8_t opcode_t; // we actually only need 4 bits of it
typedef uint16_t flags_t;
typedef uint16_t qid_t;

class Message;
class EDNS;             // see below

typedef boost::shared_ptr<AbstractRRset> RRsetPtr;

class RRsetsSorter {
public:
    void sort(Message& message, section_t section) {} // dummy for now.
};

#define get_msgflg(flg, capflg) \
bool get_ ## flg() const { return ((flags_ & FLAG_ ## capflg) != 0); }
#define set_msgflg(flg, capflg) \
bool set_ ## flg(bool on) { \
        if (on) \
            flags_ |= FLAG_ ## capflg; \
        else \
            flags_ &= ~FLAG_ ## capflg; \
    }

class Message {
public:
    Message();
    ~Message();
    qid_t get_qid() const { return (qid_); }
    void set_qid(qid_t qid) { qid_ = qid; }
    get_msgflg(rd, RD)
    set_msgflg(rd, RD)
    get_msgflg(aa, AA)
    set_msgflg(aa, AA)
    get_msgflg(qr, QR)
    set_msgflg(qr, QR)
    get_msgflg(tc, TC)
    set_msgflg(tc, TC)
    get_msgflg(ra, RA)
    set_msgflg(ra, RA)
    get_msgflg(ad, AD)
    set_msgflg(ad, AD)
    get_msgflg(cd, CD)
    set_msgflg(cd, CD)
    rcode_t get_rcode() const { return (rcode_); }
    void set_rcode(rcode_t rcode) { rcode_ = rcode; }
    opcode_t get_opcode() const { return (opcode_); }
    void set_opcode(opcode_t opcode) { opcode_ = opcode; }
    std::string to_text() const;

    // we don't provide accessors to QD/AN/NS/AR counters as this information
    // is included in the corresponding RRsets.
    // Open issues:
    //   - should we handle the question section separately?
    //   - may want to provide an "iterator" for all RRsets/RRs
    //   - may want to provide a "find" method for a specified type
    //     of RR in the message
    const std::vector<RRsetPtr>& get_section(section_t section) const
    { return (sections_[section]); }
    void add_rrset(section_t section, RRsetPtr rrset);
    // add_question() is redundant in that it's a special case of add_rrset,
    // but it'd be convenient for general purpose applications.
    void add_question(const Name& qname, const RRClass& qclass,
                      const RRType& qtype);
    void remove_rrset(section_t section, RRsetPtr rrset);
    void add_rr(section_t section, const RR& rr);
    void remove_rr(section_t section, const RR& rr);

    // should we separate methods for different EDNS0-related
    // parameters/options?  it would probably be better to have a
    // separate class for future extensibility.
    // on the other hand, considering we're going to use EDNS0 pretty
    // ubiquitously, perhaps we should include currently-defined EDNS0
    // parameters and options by default.
    void set_edns(EDNS* edns);    // TBD
    const EDNS* get_edns() const; // TBD

    // prepare for making a response from a request.  This will clear the
    // DNS header except those fields that should be kept for the response,
    // and clear answer and the following sections.
    // see also dns_message_reply() of BIND9.
    void make_response();

    // Render message
    void to_wire();      // should probably return some result code?

    Buffer& get_buffer()
    {
        if (buffer_ == NULL)
            throw DNSNoMessageBuffer();
        return (*buffer_);
    }

    NameCompressor& get_compressor()
    {
        if (compressor_ == NULL)
            throw DNSNoNameCompressor();
        return (*compressor_);
    }

    NameDecompressor& get_decompressor()
    {
        if (decompressor_ == NULL)
            throw DNSNoNameDecompressor();
        return (*decompressor_);
    }

    // Parse message:
    // This function may throw exceptions.  We may revisit this design.
    void from_wire();

public:
    // public protocol constants
    static const rcode_t RCODE_NOERROR = 0;
    static const rcode_t RCODE_FORMERR = 1;
    static const rcode_t RCODE_SERVFAIL = 2;
    static const rcode_t RCODE_NXDOMAIN = 3;
    static const rcode_t RCODE_NOTIMP = 4;
    static const rcode_t RCODE_REFUSED = 5;
    // ...more to follow

    static const opcode_t OPCODE_QUERY = 0;
    static const opcode_t OPCODE_IQUERY = 1;
    static const opcode_t OPCODE_STATUS = 2;
    static const opcode_t OPCODE_NOTIFY = 4;
    static const opcode_t OPCODE_UPDATE = 5;

private:
    void initialize();
    void parse_question();

private:
    // Open issues: should we rather have a header in wire-format
    // for efficiency?
    qid_t qid_;
    rcode_t rcode_;
    opcode_t opcode_;
    flags_t flags_;

    int counts_[SECTION_MAX];   // TODO: revisit this definition

    // TODO: revisit the type of vector items
    std::vector<RRsetPtr> sections_[SECTION_MAX]; 

    // tsig/sig0: TODO
    EDNS* edns_;
    Buffer* buffer_;
    NameCompressor* compressor_;
    NameDecompressor* decompressor_;
    RRsetsSorter* sorter_;

    // created internally with the default constructor.  TBD: revisit this idea.
    Buffer* default_buffer_;
    NameCompressor* default_compressor_;
    NameDecompressor* default_decompressor_;

    // protocol constants
    static const size_t HEADERLEN = 12;

    static const flags_t FLAG_QR = 0x8000;
    static const flags_t FLAG_AA = 0x0400;
    static const flags_t FLAG_TC = 0x0200;
    static const flags_t FLAG_RD = 0x0100;
    static const flags_t FLAG_RA = 0x0080;
    static const flags_t FLAG_AD = 0x0020;
    static const flags_t FLAG_CD = 0x0010;

    static const unsigned int OPCODE_MASK = 0x7800;
    static const unsigned int OPCODE_SHIFT = 11;
    static const unsigned int RCODE_MASK = 0x000f;
    static const unsigned int FLAG_MASK = 0x8ff0;

    static const unsigned int MESSAGE_REPLYPRESERVE = (FLAG_RD | FLAG_CD);
};
}
}
#endif  // __MESSAGE_H

// Local Variables: 
// mode: c++
// End: 
