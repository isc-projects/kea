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

#include <stdexcept>
#include <functional>
#include <algorithm>

#include <boost/lexical_cast.hpp>

#include <dns/buffer.h>
#include <dns/rrset.h>
#include <dns/message.h>

using isc::dns::Name;
using isc::dns::Message;
using isc::dns::RRType;
using isc::dns::RRClass;
using isc::dns::RRsetPtr;
using isc::dns::RR;
using isc::dns::TTL;

Message::Message()
{
    initialize();

    default_buffer_ = new isc::SingleBuffer;
    buffer_ = default_buffer_;

    default_compressor_ = new NameCompressor;
    compressor_ = default_compressor_;

    default_decompressor_ = new NameDecompressor;
    decompressor_ = default_decompressor_;
}

Message::~Message()
{
    delete default_buffer_;
    delete default_compressor_;
    delete default_decompressor_;
}

void
Message::initialize()
{
    qid_ = 0;
    rcode_ = RCODE_NOERROR;
    opcode_ = OPCODE_QUERY;     // default
    flags_ = 0;
    for (int section = SECTION_QUESTION; section < SECTION_MAX; ++section) {
        counts_[section] = 0;
    }

    edns_ = NULL;
    buffer_ = NULL;
    compressor_ = NULL;
    decompressor_ = NULL;
    sorter_ = NULL;
    default_compressor_ = NULL;
    default_decompressor_ = NULL;
}

void
Message::addRrset(section_t section, RRsetPtr rrsetp)
{
    if (section >= SECTION_MAX)
        throw DNSInvalidMessageSection();

    // Note: should check duplicate (TBD)
    sections_[section].push_back(rrsetp);
}

void
Message::addQuestion(const Name& qname, const RRClass& qclass,
                      const RRType& qtype)
{
    addRrset(SECTION_QUESTION, RRsetPtr(new Question(qname, qclass, qtype)));
}

void
Message::toWire()
{
    uint16_t codes_and_flags;

    if (buffer_ == NULL)
        throw DNSNoMessageBuffer();

    // reserve room for the header
    buffer_->reserve(HEADERLEN);

    for (int section = SECTION_QUESTION; section < SECTION_MAX; ++section) {
        if (sorter_ != NULL)
            sorter_->sort(*this, (section_t)section); //TBD
        counts_[section] = 0;
        for (std::vector<RRsetPtr>::const_iterator it =
                 getSection((section_t)section).begin();
             it != getSection((section_t)section).end();
             ++it)
        {
            int counter = (*it)->toWire(*buffer_, getCompressor(),
                                        (section_t)section);

            // TBD: if truncation is necessary, do something special.
            // throw an exception, return an error code (in which case the
            // function signature should be changed), etc.

            counts_[section] += counter;
        }
    }

    // EDNS, TSIG, etc.

    // fill in the header
    size_t header_pos = 0;
    buffer_->writeUint16At(qid_, header_pos);
    header_pos += sizeof(uint16_t);
    codes_and_flags = (opcode_ << OPCODE_SHIFT) & OPCODE_MASK;
    codes_and_flags |= (rcode_ & RCODE_MASK);
    codes_and_flags |= (flags_ & FLAG_MASK);
    buffer_->writeUint16At(codes_and_flags, header_pos);
    header_pos += sizeof(uint16_t);
    for (int section = SECTION_QUESTION; section < SECTION_MAX; ++section) {
        buffer_->writeUint16At(counts_[section], header_pos);
        header_pos += sizeof(uint16_t);
    }
}

void
Message::fromWire()
{
    if (buffer_ == NULL)
        throw DNSNoMessageBuffer();

    if (buffer_->getSpace() < HEADERLEN)
        throw DNSMessageTooShort();

    qid_ = buffer_->readUint16();
    uint16_t codes_and_flags = buffer_->readUint16();
    opcode_ = ((codes_and_flags & OPCODE_MASK) >> OPCODE_SHIFT);
    rcode_ = (codes_and_flags & RCODE_MASK);
    flags_ = (codes_and_flags & FLAG_MASK);
    counts_[SECTION_QUESTION] = buffer_->readUint16();
    counts_[SECTION_ANSWER] = buffer_->readUint16();
    counts_[SECTION_AUTHORITY] = buffer_->readUint16();
    counts_[SECTION_ADDITIONAL] = buffer_->readUint16();

    parse_question();
    // parse other sections (TBD)
}

void
Message::parse_question()
{
    Name name;

    if (buffer_ == NULL)
        throw DNSNoMessageBuffer();

    for (int count = 0; count < this->counts_[SECTION_QUESTION]; count++) {
        Name name(*buffer_, getDecompressor());

        // Get type and class
        if (buffer_->getSpace() < 2 * sizeof(uint16_t))
            throw DNSMessageTooShort();

        // XXX: need a duplicate check.  We might also want to have an optimized
        // algorithm that requires the question section contain exactly one
        // RR.

        RRType rrtype(buffer_->readUint16());
        RRClass rrclass(buffer_->readUint16());
        addRrset(SECTION_QUESTION,
                 RRsetPtr(new Question(name, rrclass, rrtype))); 
    }
}

static const char *opcodetext[] = {
    "QUERY",
    "IQUERY",
    "STATUS",
    "RESERVED3",
    "NOTIFY",
    "UPDATE",
    "RESERVED6",
    "RESERVED7",
    "RESERVED8",
    "RESERVED9",
    "RESERVED10",
    "RESERVED11",
    "RESERVED12",
    "RESERVED13",
    "RESERVED14",
    "RESERVED15"
};

static const char *rcodetext[] = {
    "NOERROR",
    "FORMERR",
    "SERVFAIL",
    "NXDOMAIN",
    "NOTIMP",
    "REFUSED",
    "YXDOMAIN",
    "YXRRSET",
    "NXRRSET",
    "NOTAUTH",
    "NOTZONE",
    "RESERVED11",
    "RESERVED12",
    "RESERVED13",
    "RESERVED14",
    "RESERVED15"
};

static const char *sectiontext[] = {
    "QUESTION",
    "ANSWER",
    "AUTHORITY",
    "ADDITIONAL"
};

std::string
Message::toText() const
{
    std::string s;

    s += ";; ->>HEADER<<- opcode: " + std::string(opcodetext[opcode_]);
    // for simplicity we don't consider extended rcode (unlike BIND9)
    s += ", status: " + std::string(rcodetext[rcode_]);
    s += ", id: " + boost::lexical_cast<std::string>(qid_);
    s += "\n;; flags: ";
    if (getQR())
        s += "qr ";
    if (getAA())
        s += "aa ";
    if (getTC())
        s += "tc ";
    if (getRD())
        s += "rd ";
    if (getRA())
        s += "ra ";
    if (getAD())
        s += "ad ";
    if (getCD())
        s += "cd ";

    // for simply, don't consider the update case
    s += "; QUESTION: " +
        boost::lexical_cast<std::string>(counts_[SECTION_QUESTION]);
    s += ", ANSWER: " +
        boost::lexical_cast<std::string>(counts_[SECTION_ANSWER]);
    s += ", AUTHORITY: " +
        boost::lexical_cast<std::string>(counts_[SECTION_AUTHORITY]);
    s += ", ADDITIONAL: " +
        boost::lexical_cast<std::string>(counts_[SECTION_ADDITIONAL]) + "\n";

    for (int section = SECTION_QUESTION; section < SECTION_MAX; ++section) {
        if (sections_[section].empty())
            continue;

        s += "\n;; " + std::string(sectiontext[section]) + " SECTION:\n";

        std::vector<RRsetPtr>::const_iterator it;
        for (it = sections_[section].begin();
             it !=  sections_[section].end();
             ++it)
        {
            if (section == SECTION_QUESTION)
                s += ";";
            s += (**it).toText() + "\n";
        }
    }

    return (s);
}

struct MatchRR : public std::binary_function<RRsetPtr, RR, bool> {
    bool operator()(const RRsetPtr& rrset, const RR& rr) const
    {
        return (rrset->getType() == rr.getType() &&
                rrset->getClass() == rr.getClass() &&
                rrset->getName() == rr.getName());
    }
};

void
Message::addRr(section_t section, const RR& rr)
{
    std::vector<RRsetPtr>::iterator it;
    it = find_if(sections_[section].begin(), sections_[section].end(),
                 std::bind2nd(MatchRR(), rr));
    if (it != sections_[section].end()) {
        (*it)->setTtl(std::min((*it)->getTtl(), rr.getTtl()));
        (*it)->addRdata(Rdata::RDATAPTR(rr.getRdata()->copy()));
    } else {
        RRset *rrset = new RRset(rr.getName(), rr.getClass(), rr.getType(),
                                 rr.getTtl());
        rrset->addRdata(Rdata::RDATAPTR(rr.getRdata()->copy()));
        sections_[section].push_back(RRsetPtr(rrset));
    }
}

void
Message::makeResponse()
{
    flags_ &= MESSAGE_REPLYPRESERVE;
    setQR(true);

    for (int section = SECTION_ANSWER; section < SECTION_MAX; ++section) {
        sections_[section].clear();
    }
}
