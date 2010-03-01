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

#include <stdint.h>

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

#include <exceptions/exceptions.h>

#include "buffer.h"
#include "message.h"
#include "messagerenderer.h"
#include "name.h"
#include "question.h"
#include "rrclass.h"
#include "rrtype.h"
#include "rrttl.h"
#include "rrset.h"

using namespace std;
using namespace boost;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace dns {

namespace {
typedef uint16_t flags_t;

// protocol constants
static const size_t HEADERLEN = 12;

static const flags_t FLAG_QR = 0x8000;
static const flags_t FLAG_AA = 0x0400;
static const flags_t FLAG_TC = 0x0200;
static const flags_t FLAG_RD = 0x0100;
static const flags_t FLAG_RA = 0x0080;
static const flags_t FLAG_AD = 0x0020;
static const flags_t FLAG_CD = 0x0010;

//
// EDNS0 related constants
//
static const flags_t EXTFLAG_MASK = 0xffff;
static const flags_t EXTFLAG_DO = 0x8000;
static const uint32_t EXTRCODE_MASK = 0xff000000; 
static const uint32_t EDNSVERSION_MASK = 0x00ff0000;

static const unsigned int OPCODE_MASK = 0x7800;
static const unsigned int OPCODE_SHIFT = 11;
static const unsigned int RCODE_MASK = 0x000f;
static const unsigned int FLAG_MASK = 0x8ff0;

static const unsigned int MESSAGE_REPLYPRESERVE = (FLAG_RD | FLAG_CD);

static const Rcode rcodes[] = {
    Rcode::NOERROR(),
    Rcode::FORMERR(),
    Rcode::SERVFAIL(),
    Rcode::NXDOMAIN(),
    Rcode::NOTIMP(),
    Rcode::REFUSED(),
    Rcode::YXDOMAIN(),
    Rcode::YXRRSET(),
    Rcode::NXRRSET(),
    Rcode::NOTAUTH(),
    Rcode::NOTZONE(),
    Rcode::RESERVED11(),
    Rcode::RESERVED12(),
    Rcode::RESERVED13(),
    Rcode::RESERVED14(),
    Rcode::RESERVED15(),
    Rcode::BADVERS()
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
    "RESERVED15",
    "BADVERS"
};

static const Opcode* opcodes[] = {
    &Opcode::QUERY(),
    &Opcode::IQUERY(),
    &Opcode::STATUS(),
    &Opcode::RESERVED3(),
    &Opcode::NOTIFY(),
    &Opcode::UPDATE(),
    &Opcode::RESERVED6(),
    &Opcode::RESERVED7(),
    &Opcode::RESERVED8(),
    &Opcode::RESERVED9(),
    &Opcode::RESERVED10(),
    &Opcode::RESERVED11(),
    &Opcode::RESERVED12(),
    &Opcode::RESERVED13(),
    &Opcode::RESERVED14(),
    &Opcode::RESERVED15()
};

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
}

string
Opcode::toText() const
{
    return (opcodetext[code_]);
}

Rcode::Rcode(uint16_t code) : code_(code)
{
    if (code_ > MAX_RCODE) {
        dns_throw(OutOfRange, "Rcode is too large to construct");
    }
}

string
Rcode::toText() const
{
    if (code_ < sizeof(rcodetext) / sizeof (const char *)) {
        return (rcodetext[code_]);
    }

    ostringstream oss;
    oss << code_;
    return (oss.str());
}

namespace {
inline unsigned int
sectionCodeToId(const Section& section)
{
    unsigned int code = section.getCode();
    assert(code > 0);
    return (section.getCode() - 1);
}
}

class MessageImpl {
public:
    MessageImpl();
    // Open issues: should we rather have a header in wire-format
    // for efficiency?
    qid_t qid_;
    Rcode rcode_;
    const Opcode* opcode_;
    flags_t flags_;
    bool dnssec_ok_;

    static const unsigned int SECTION_MAX = 4; // TODO: revisit this design
    int counts_[SECTION_MAX];   // TODO: revisit this definition
    vector<QuestionPtr> questions_;
    vector<RRsetPtr> rrsets_[SECTION_MAX];
    RRsetPtr edns_;
    uint16_t udpsize_;

#ifdef notyet
    // tsig/sig0: TODO
    RRsetsSorter* sorter_;
#endif

    void init();
    void parseQuestion(Message& message, InputBuffer& buffer);
    void parseSection(Message& messge, const Section& section,
                      InputBuffer& buffer);
};

MessageImpl::MessageImpl() :
    rcode_(Rcode::NOERROR())
{
    init();
}

void
MessageImpl::init()
{
    flags_ = 0;
    qid_ = 0;
    rcode_ = Rcode::NOERROR();  // XXX
    opcode_ = NULL;
    dnssec_ok_ = false;
    edns_ = RRsetPtr();
    udpsize_ = Message::DEFAULT_MAX_UDPSIZE;

    for (int i = 0; i < SECTION_MAX; i++) {
        counts_[i] = 0;
    }

    questions_.clear();
    rrsets_[sectionCodeToId(Section::ANSWER())].clear();
    rrsets_[sectionCodeToId(Section::AUTHORITY())].clear();
    rrsets_[sectionCodeToId(Section::ADDITIONAL())].clear();
}

Message::Message() :
    impl_(new MessageImpl())
{
}

Message::~Message()
{
    delete impl_;
}

bool
Message::getHeaderFlag(const MessageFlag& flag) const
{
    return ((impl_->flags_ & flag.getBit()) != 0);
}

void
Message::setHeaderFlag(const MessageFlag& flag)
{
    impl_->flags_ |= flag.getBit();
}

void
Message::clearHeaderFlag(const MessageFlag& flag)
{
    impl_->flags_ &= ~flag.getBit();
}

bool
Message::isDNSSECSupported() const
{
    return (impl_->dnssec_ok_);
}

uint16_t
Message::getUDPSize() const
{
    return (impl_->udpsize_);
}

qid_t
Message::getQid() const
{
    return (impl_->qid_);
}

void
Message::setQid(qid_t qid)
{
    impl_->qid_ = qid;
}

const Rcode&
Message::getRcode() const
{
    return (impl_->rcode_);
}

void
Message::setRcode(const Rcode& rcode)
{
    impl_->rcode_ = rcode;
}

const Opcode&
Message::getOpcode() const
{
    return (*impl_->opcode_);
}

void
Message::setOpcode(const Opcode& opcode)
{
    impl_->opcode_ = &opcode;
}

unsigned int
Message::getRRCount(const Section& section) const
{
    return (impl_->counts_[section.getCode()]);
}

void
Message::addRRset(const Section& section, RRsetPtr rrset, bool sign)
{
    // Note: should check duplicate (TBD)
    impl_->rrsets_[sectionCodeToId(section)].push_back(rrset);
    impl_->counts_[section.getCode()] += rrset->getRdataCount();

    RRsetPtr sp = rrset->getRRsig();
    if (sign && sp) {
        impl_->rrsets_[sectionCodeToId(section)].push_back(sp);
        impl_->counts_[section.getCode()] += sp->getRdataCount();
    }
}

void
Message::addQuestion(const QuestionPtr question)
{
    impl_->questions_.push_back(question);
    impl_->counts_[Section::QUESTION().getCode()]++;
}

void
Message::addQuestion(const Question& question)
{
    addQuestion(QuestionPtr(new Question(question)));
}

namespace {
template <typename T>
struct RenderSection
{
    RenderSection(MessageRenderer& renderer) :
        counter_(0), renderer_(renderer) {}
    void operator()(const T& entry)
    {
        // TBD: if truncation is necessary, do something special.
        // throw an exception, set an internal flag, etc.
        counter_ += entry->toWire(renderer_);
    }
    unsigned int getTotalCount() { return (counter_); }
    unsigned int counter_;
    MessageRenderer& renderer_;
};
}

void
Message::toWire(MessageRenderer& renderer)
{
    uint16_t codes_and_flags;

    // reserve room for the header
    renderer.skip(HEADERLEN);

    uint16_t qrcount =
        for_each(impl_->questions_.begin(), impl_->questions_.end(),
                 RenderSection<QuestionPtr>(renderer)).getTotalCount();

    // TBD: sort RRsets in each section based on configuration policy.
    uint16_t ancount =
        for_each(impl_->rrsets_[sectionCodeToId(Section::ANSWER())].begin(),
                 impl_->rrsets_[sectionCodeToId(Section::ANSWER())].end(),
                 RenderSection<RRsetPtr>(renderer)).getTotalCount();
    uint16_t nscount =
        for_each(impl_->rrsets_[sectionCodeToId(Section::AUTHORITY())].begin(),
                 impl_->rrsets_[sectionCodeToId(Section::AUTHORITY())].end(),
                 RenderSection<RRsetPtr>(renderer)).getTotalCount();
    uint16_t arcount =
        for_each(impl_->rrsets_[sectionCodeToId(Section::ADDITIONAL())].begin(),
                 impl_->rrsets_[sectionCodeToId(Section::ADDITIONAL())].end(),
                 RenderSection<RRsetPtr>(renderer)).getTotalCount();

    // TBD: EDNS, TSIG, etc.

    // fill in the header
    size_t header_pos = 0;
    renderer.writeUint16At(impl_->qid_, header_pos);
    header_pos += sizeof(uint16_t);
    codes_and_flags = (impl_->opcode_->getCode() << OPCODE_SHIFT) & OPCODE_MASK;
    codes_and_flags |= (impl_->rcode_.getCode() & RCODE_MASK);
    codes_and_flags |= (impl_->flags_ & FLAG_MASK);
    renderer.writeUint16At(codes_and_flags, header_pos);
    header_pos += sizeof(uint16_t);
    // XXX: should avoid repeated pattern (TODO)
    renderer.writeUint16At(qrcount, header_pos);
    header_pos += sizeof(uint16_t);
    renderer.writeUint16At(ancount, header_pos);
    header_pos += sizeof(uint16_t);
    renderer.writeUint16At(nscount, header_pos);
    header_pos += sizeof(uint16_t);
    renderer.writeUint16At(arcount, header_pos);
    header_pos += sizeof(uint16_t);
}

void
Message::fromWire(InputBuffer& buffer)
{
    if ((buffer.getLength() - buffer.getPosition()) < HEADERLEN) {
        dns_throw(MessageTooShort, "");
    }

    impl_->qid_ = buffer.readUint16();
    uint16_t codes_and_flags = buffer.readUint16();
    impl_->opcode_ = opcodes[((codes_and_flags & OPCODE_MASK) >> OPCODE_SHIFT)];
    impl_->rcode_ = rcodes[(codes_and_flags & RCODE_MASK)];
    impl_->flags_ = (codes_and_flags & FLAG_MASK);
    impl_->counts_[Section::QUESTION().getCode()] = buffer.readUint16();
    impl_->counts_[Section::ANSWER().getCode()] = buffer.readUint16();
    impl_->counts_[Section::AUTHORITY().getCode()] = buffer.readUint16();
    impl_->counts_[Section::ADDITIONAL().getCode()] = buffer.readUint16();

    impl_->parseQuestion(*this, buffer);
    impl_->parseSection(*this, Section::ANSWER(), buffer);
    impl_->parseSection(*this, Section::AUTHORITY(), buffer);
    impl_->parseSection(*this, Section::ADDITIONAL(), buffer);
}

void
MessageImpl::parseQuestion(Message& message, InputBuffer& buffer)
{
    for (unsigned int count = 0;
         count < counts_[Section::QUESTION().getCode()];
         count++) {
        Name name(buffer);

        if ((buffer.getLength() - buffer.getPosition()) <
            2 * sizeof(uint16_t)) {
            dns_throw(MessageTooShort, "");
        }
        RRType rrtype(buffer.readUint16());
        RRClass rrclass(buffer.readUint16());

        // XXX: need a duplicate check.  We might also want to have an optimized
        // algorithm that requires the question section contain exactly one
        // RR.

        questions_.push_back(QuestionPtr(new Question(name, rrclass, rrtype))); 
    }
}

namespace {
struct MatchRR : public unary_function<RRsetPtr, bool> {
    MatchRR(const Name& name, const RRType& rrtype, const RRClass& rrclass) :
        name_(name), rrtype_(rrtype), rrclass_(rrclass) {}
    bool operator()(const RRsetPtr& rrset) const
    {
        return (rrset->getType() == rrtype_ &&
                rrset->getClass() == rrclass_ &&
                rrset->getName() == name_);
    }
    const Name& name_;
    const RRType& rrtype_;
    const RRClass& rrclass_;
};
}

void
MessageImpl::parseSection(Message& message, const Section& section,
                          InputBuffer& buffer)
{
    for (unsigned int count = 0; count < counts_[section.getCode()]; count++) {
        Name name(buffer);

        // buffer must store at least RR TYPE, RR CLASS, TTL, and RDLEN.
        if ((buffer.getLength() - buffer.getPosition()) <
            3 * sizeof(uint16_t) + sizeof(uint32_t)) {
            dns_throw(MessageTooShort, "");
        }

        RRType rrtype(buffer.readUint16());
        RRClass rrclass(buffer.readUint16());
        RRTTL ttl(buffer.readUint32());
        size_t rdlen = buffer.readUint16();
        RdataPtr rdata = createRdata(rrtype, rrclass, buffer, rdlen);

        // XXX: we wanted to avoid hardcoding type-specific logic here,
        // but this would be the fastest way for a proof-of-concept
        // implementation.  We'll revisit this part later.
        if (rrtype == RRType::OPT()) {
            if (section != Section::ADDITIONAL()) {
                dns_throw(DNSMessageFORMERR,
                          "EDNS OPT RR found in an invalid section");
            }
            if (edns_ != NULL) {
                dns_throw(DNSMessageFORMERR, "multiple EDNS OPT RR found");
            }
            if (((ttl.getValue() & EDNSVERSION_MASK) >> 16) >
                // XXX: we should probably not reject the message yet, because
                // it's better to let the requestor know the responder-side
                // highest version as indicated in Section 4.6 of RFC2671.
                // This is probably because why BIND 9 does the version check
                // in the client code.
                // This is a TODO item.  Right now we simply reject it.
                Message::EDNS0_SUPPORTED_VERSION) {
                dns_throw(DNSMessageBADVERS, "unsupported EDNS version");
            }
            if (name != Name::ROOT_NAME()) {
                dns_throw(DNSMessageFORMERR,
                          "invalid owner name for EDNS OPT RR");
            }

            edns_ = RRsetPtr(new RRset(name, rrclass, rrtype, ttl));
            edns_->addRdata(rdata);

            dnssec_ok_ = (((ttl.getValue() & EXTFLAG_MASK) & EXTFLAG_DO) != 0);
            if (rrclass.getCode() > Message::DEFAULT_MAX_UDPSIZE) {
                udpsize_ = rrclass.getCode();
            }
            rcode_ = Rcode(((ttl.getValue() & EXTRCODE_MASK) >> 20) |
                           rcode_.getCode());
            continue;
        }

        vector<RRsetPtr>::iterator it =
            find_if(rrsets_[sectionCodeToId(section)].begin(),
                    rrsets_[sectionCodeToId(section)].end(),
                    MatchRR(name, rrtype, rrclass));
        if (it != rrsets_[sectionCodeToId(section)].end()) {
            (*it)->setTTL(min((*it)->getTTL(), ttl));
            (*it)->addRdata(rdata);
        } else {
            RRsetPtr rrset = RRsetPtr(new RRset(name, rrclass, rrtype, ttl)); 
            rrset->addRdata(rdata);
            rrsets_[sectionCodeToId(section)].push_back(rrset);
        }
    }
}

namespace {
static const char *sectiontext[] = {
    "QUESTION",
    "ANSWER",
    "AUTHORITY",
    "ADDITIONAL"
};

template <typename T>
struct SectionFormatter
{
    SectionFormatter(const Section& section, string& output) :
        section_(section), output_(output) {}
    void operator()(const T& entry)
    {
        if (section_ == Section::QUESTION()) {
            output_ += ";";
        }
        output_ += entry->toText();
    }
    const Section& section_;
    string& output_;
};
}

string
Message::toText() const
{
    string s;

    s += ";; ->>HEADER<<- opcode: " + impl_->opcode_->toText();
    // for simplicity we don't consider extended rcode (unlike BIND9)
    s += ", status: " + impl_->rcode_.toText();
    s += ", id: " + boost::lexical_cast<string>(impl_->qid_);
    s += "\n;; flags: ";
    if (getHeaderFlag(MessageFlag::QR()))
        s += "qr ";
    if (getHeaderFlag(MessageFlag::AA()))
        s += "aa ";
    if (getHeaderFlag(MessageFlag::TC()))
        s += "tc ";
    if (getHeaderFlag(MessageFlag::RD()))
        s += "rd ";
    if (getHeaderFlag(MessageFlag::RA()))
        s += "ra ";
    if (getHeaderFlag(MessageFlag::AD()))
        s += "ad ";
    if (getHeaderFlag(MessageFlag::CD()))
        s += "cd ";

    // for simplicity, don't consider the update case for now
    s += "; QUESTION: " +
        lexical_cast<string>(impl_->counts_[Section::QUESTION().getCode()]);
    s += ", ANSWER: " +
        lexical_cast<string>(impl_->counts_[Section::ANSWER().getCode()]);
    s += ", AUTHORITY: " +
        lexical_cast<string>(impl_->counts_[Section::AUTHORITY().getCode()]);
    s += ", ADDITIONAL: " +
        lexical_cast<string>(impl_->counts_[Section::ADDITIONAL().getCode()])
        + "\n";

    if (!impl_->questions_.empty()) {
        s += "\n;; " +
            string(sectiontext[Section::QUESTION().getCode()]) + " SECTION:\n";
        for_each(impl_->questions_.begin(), impl_->questions_.end(),
                 SectionFormatter<QuestionPtr>(Section::QUESTION(), s));
    }
    if (!impl_->rrsets_[sectionCodeToId(Section::ANSWER())].empty()) {
        s += "\n;; " +
            string(sectiontext[Section::ANSWER().getCode()]) + " SECTION:\n";
        for_each(impl_->rrsets_[sectionCodeToId(Section::ANSWER())].begin(),
                 impl_->rrsets_[sectionCodeToId(Section::ANSWER())].end(),
                 SectionFormatter<RRsetPtr>(Section::ANSWER(), s));
    }
    if (!impl_->rrsets_[sectionCodeToId(Section::AUTHORITY())].empty()) {
        s += "\n;; " +
            string(sectiontext[Section::AUTHORITY().getCode()]) + " SECTION:\n";
        for_each(impl_->rrsets_[sectionCodeToId(Section::AUTHORITY())].begin(),
                 impl_->rrsets_[sectionCodeToId(Section::AUTHORITY())].end(),
                 SectionFormatter<RRsetPtr>(Section::AUTHORITY(), s));
    }
    if (!impl_->rrsets_[sectionCodeToId(Section::ADDITIONAL())].empty()) {
        s += "\n;; " +
            string(sectiontext[Section::ADDITIONAL().getCode()]) +
            " SECTION:\n";
        for_each(impl_->rrsets_[sectionCodeToId(Section::ADDITIONAL())].begin(),
                 impl_->rrsets_[sectionCodeToId(Section::ADDITIONAL())].end(),
                 SectionFormatter<RRsetPtr>(Section::ADDITIONAL(), s));
    }

    return (s);
}

void
Message::clear()
{
    impl_->init();
}

void
Message::makeResponse()
{
    impl_->flags_ &= MESSAGE_REPLYPRESERVE;
    setHeaderFlag(MessageFlag::QR());

    impl_->rrsets_[sectionCodeToId(Section::ANSWER())].clear();
    impl_->counts_[Section::ANSWER().getCode()] = 0;
    impl_->rrsets_[sectionCodeToId(Section::AUTHORITY())].clear();
    impl_->counts_[Section::AUTHORITY().getCode()] = 0;
    impl_->rrsets_[sectionCodeToId(Section::ADDITIONAL())].clear();
    impl_->counts_[Section::ADDITIONAL().getCode()] = 0;
}

///
/// Template version of Section Iterator
///
template <typename T>
struct SectionIteratorImpl {
    SectionIteratorImpl(const typename vector<T>::const_iterator& it) :
        it_(it) {}
    typename vector<T>::const_iterator it_;
};

template <typename T>
SectionIterator<T>::SectionIterator(const SectionIteratorImpl<T>& impl)
{
    impl_ = new SectionIteratorImpl<T>(impl.it_);
}

template <typename T>
SectionIterator<T>::~SectionIterator()
{
    delete impl_;
}

template <typename T>
SectionIterator<T>::SectionIterator(const SectionIterator<T>& source) :
    impl_(new SectionIteratorImpl<T>(source.impl_->it_))
{}

template <typename T>
void
SectionIterator<T>::operator=(const SectionIterator<T>& source)
{
    if (impl_ == source.impl_) {
        return;
    }
    SectionIteratorImpl<T>* newimpl =
        new SectionIteratorImpl<T>(source.impl_->it_);
    delete impl_;
    impl_ = newimpl;
}

template <typename T>
SectionIterator<T>&
SectionIterator<T>::operator++()
{
    ++(impl_->it_);
    return (*this);
}

template <typename T>
SectionIterator<T>
SectionIterator<T>::operator++(int)
{
    SectionIterator<T> tmp(*this);
    ++(*this);
    return (tmp);
}

template <typename T>
const T&
SectionIterator<T>::operator*() const
{
    return (*(impl_->it_));
}

template <typename T>
const T*
SectionIterator<T>::operator->() const
{
    return (impl_->it_.operator->());
}

template <typename T>
bool
SectionIterator<T>::operator!=(const SectionIterator<T>& other) const
{
    return (impl_->it_ != other.impl_->it_);
}

///
/// We need to explicitly instantiate these template classes because these
/// are public classes but defined in this implementation file.
///
template class SectionIterator<QuestionPtr>;
template class SectionIterator<RRsetPtr>;

namespace {
typedef SectionIteratorImpl<QuestionPtr> QuestionIteratorImpl;
typedef SectionIteratorImpl<RRsetPtr> RRsetIteratorImpl;
}

///
/// Question iterator
///
const QuestionIterator
Message::beginQuestion() const
{
    return (QuestionIterator(QuestionIteratorImpl(impl_->questions_.begin())));
}

const QuestionIterator
Message::endQuestion() const
{
    return (QuestionIterator(QuestionIteratorImpl(impl_->questions_.end())));
}

///
/// RRsets iterators
///
const SectionIterator<RRsetPtr>
Message::beginSection(const Section& section) const
{
    if (section == Section::QUESTION()) {
        dns_throw(InvalidMessageSection, "");
    }

    return (RRsetIterator(
                RRsetIteratorImpl(
                    impl_->rrsets_[sectionCodeToId(section)].begin())));
}

const SectionIterator<RRsetPtr>
Message::endSection(const Section& section) const
{
    if (section == Section::QUESTION()) {
        dns_throw(InvalidMessageSection, "");
    }

    return (RRsetIterator(
                RRsetIteratorImpl(
                    impl_->rrsets_[sectionCodeToId(section)].end())));
}

ostream&
operator<<(ostream& os, const Opcode& opcode)
{
    return (os << opcode.toText());
}

ostream&
operator<<(ostream& os, const Rcode& rcode)
{
    return (os << rcode.toText());
}

ostream&
operator<<(ostream& os, const Message& message)
{
    return (os << message.toText());
}

} // end of namespace dns
} // end of namespace isc
