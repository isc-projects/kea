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

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

#include <exceptions/exceptions.h>

#include <dns/buffer.h>
#include <dns/edns.h>
#include <dns/exceptions.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/question.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>
#include <dns/rrset.h>

using namespace std;
using namespace boost;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace dns {

namespace {
typedef uint16_t flags_t;

// protocol constants
const size_t HEADERLEN = 12;

const flags_t FLAG_QR = 0x8000;
const flags_t FLAG_AA = 0x0400;
const flags_t FLAG_TC = 0x0200;
const flags_t FLAG_RD = 0x0100;
const flags_t FLAG_RA = 0x0080;
const flags_t FLAG_AD = 0x0020;
const flags_t FLAG_CD = 0x0010;

//
// EDNS related constants
//
const uint32_t EXTRCODE_MASK = 0xff000000; 

const unsigned int OPCODE_MASK = 0x7800;
const unsigned int OPCODE_SHIFT = 11;
const unsigned int RCODE_MASK = 0x000f;
const unsigned int FLAG_MASK = 0x8ff0;

const unsigned int MESSAGE_REPLYPRESERVE = (FLAG_RD | FLAG_CD);

const Rcode rcodes[] = {
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

const char *rcodetext[] = {
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

const Opcode* opcodes[] = {
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

const char *opcodetext[] = {
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

const char *sectiontext[] = {
    "QUESTION",
    "ANSWER",
    "AUTHORITY",
    "ADDITIONAL"
};
}

string
Opcode::toText() const {
    return (opcodetext[code_]);
}

namespace {
//     0     3               11      15
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//    |UNUSED | EXTENDED-RCODE | RCODE |
//    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//                            <= EXTRCODE_SHIFT
const unsigned int EXTRCODE_SHIFT = 4;
}

Rcode::Rcode(const uint16_t code) : code_(code) {
    if (code_ > MAX_RCODE) {
        isc_throw(OutOfRange, "Rcode is too large to construct: " << code_);
    }
}

Rcode::Rcode(const uint8_t code, const uint8_t extended_code) :
    code_((extended_code << EXTRCODE_SHIFT) | (code & RCODE_MASK))
{
    if (code > RCODE_MASK) {
        isc_throw(OutOfRange,
                  "Base Rcode is too large to construct: "
                  << static_cast<unsigned int>(code));
    }
}

uint8_t
Rcode::getExtendedCode() const {
    return (code_ >> EXTRCODE_SHIFT);
}

string
Rcode::toText() const {
    if (code_ < sizeof(rcodetext) / sizeof (const char *)) {
        return (rcodetext[code_]);
    }

    ostringstream oss;
    oss << code_;
    return (oss.str());
}

namespace {
inline unsigned int
sectionCodeToId(const Section& section) {
    unsigned int code = section.getCode();
    assert(code > 0);
    return (section.getCode() - 1);
}
}

class MessageImpl {
public:
    MessageImpl(Message::Mode mode);
    // Open issues: should we rather have a header in wire-format
    // for efficiency?
    Message::Mode mode_;
    qid_t qid_;
    Rcode rcode_;
    const Opcode* opcode_;
    flags_t flags_;

    bool header_parsed_;
    static const unsigned int SECTION_MAX = 4; // TODO: revisit this design
    int counts_[SECTION_MAX];   // TODO: revisit this definition
    vector<QuestionPtr> questions_;
    vector<RRsetPtr> rrsets_[SECTION_MAX];
    ConstEDNSPtr edns_;

#ifdef notyet
    // tsig/sig0: TODO
    RRsetsSorter* sorter_;
#endif

    void init();
    int parseQuestion(InputBuffer& buffer);
    int parseSection(const Section& section, InputBuffer& buffer);
};

MessageImpl::MessageImpl(Message::Mode mode) :
    mode_(mode), rcode_(Rcode::NOERROR())
{
    init();
}

void
MessageImpl::init() {
    flags_ = 0;
    qid_ = 0;
    rcode_ = Rcode::NOERROR();  // XXX
    opcode_ = NULL;
    edns_ = EDNSPtr();

    for (int i = 0; i < SECTION_MAX; ++i) {
        counts_[i] = 0;
    }

    header_parsed_ = false;
    questions_.clear();
    rrsets_[sectionCodeToId(Section::ANSWER())].clear();
    rrsets_[sectionCodeToId(Section::AUTHORITY())].clear();
    rrsets_[sectionCodeToId(Section::ADDITIONAL())].clear();
}

Message::Message(Mode mode) :
    impl_(new MessageImpl(mode))
{}

Message::~Message() {
    delete impl_;
}

bool
Message::getHeaderFlag(const MessageFlag& flag) const {
    return ((impl_->flags_ & flag.getBit()) != 0);
}

void
Message::setHeaderFlag(const MessageFlag& flag) {
    if (impl_->mode_ != Message::RENDER) {
        isc_throw(InvalidMessageOperation,
                  "setHeaderFlag performed in non-render mode");
    }
    impl_->flags_ |= flag.getBit();
}

void
Message::clearHeaderFlag(const MessageFlag& flag) {
    if (impl_->mode_ != Message::RENDER) {
        isc_throw(InvalidMessageOperation,
                  "clearHeaderFlag performed in non-render mode");
    }
    impl_->flags_ &= ~flag.getBit();
}

qid_t
Message::getQid() const {
    return (impl_->qid_);
}

void
Message::setQid(qid_t qid) {
    if (impl_->mode_ != Message::RENDER) {
        isc_throw(InvalidMessageOperation,
                  "setQid performed in non-render mode");
    }
    impl_->qid_ = qid;
}

const Rcode&
Message::getRcode() const {
    return (impl_->rcode_);
}

void
Message::setRcode(const Rcode& rcode) {
    if (impl_->mode_ != Message::RENDER) {
        isc_throw(InvalidMessageOperation,
                  "setRcode performed in non-render mode");
    }
    impl_->rcode_ = rcode;
}

const Opcode&
Message::getOpcode() const {
    return (*impl_->opcode_);
}

void
Message::setOpcode(const Opcode& opcode) {
    if (impl_->mode_ != Message::RENDER) {
        isc_throw(InvalidMessageOperation,
                  "setOpcode performed in non-render mode");
    }
    impl_->opcode_ = &opcode;
}

ConstEDNSPtr
Message::getEDNS() const {
    return (impl_->edns_);
}

void
Message::setEDNS(ConstEDNSPtr edns) {
    if (impl_->mode_ != Message::RENDER) {
        isc_throw(InvalidMessageOperation,
                  "setEDNS performed in non-render mode");
    }
    impl_->edns_ = edns;
}

unsigned int
Message::getRRCount(const Section& section) const {
    return (impl_->counts_[section.getCode()]);
}

void
Message::addRRset(const Section& section, RRsetPtr rrset, const bool sign) {
    if (impl_->mode_ != Message::RENDER) {
        isc_throw(InvalidMessageOperation,
                  "addRRset performed in non-render mode");
    }

    impl_->rrsets_[sectionCodeToId(section)].push_back(rrset);
    impl_->counts_[section.getCode()] += rrset->getRdataCount();

    RRsetPtr sp = rrset->getRRsig();
    if (sign && sp != NULL) {
        impl_->rrsets_[sectionCodeToId(section)].push_back(sp);
        impl_->counts_[section.getCode()] += sp->getRdataCount();
    }
}

bool
Message::hasRRset(const Section& section, RRsetPtr rrset) {
    BOOST_FOREACH(RRsetPtr r, impl_->rrsets_[sectionCodeToId(section)]) {
        if (r->getType() == rrset->getType() &&
            r->getName() == rrset->getName())
        {
            return (true);

        }
    }

    return (false);
}

void
Message::addQuestion(const QuestionPtr question) {
    if (impl_->mode_ != Message::RENDER) {
        isc_throw(InvalidMessageOperation,
                  "addQuestion performed in non-render mode");
    }

    impl_->questions_.push_back(question);
    ++impl_->counts_[Section::QUESTION().getCode()];
}

void
Message::addQuestion(const Question& question) {
    addQuestion(QuestionPtr(new Question(question)));
}

namespace {
template <typename T>
struct RenderSection {
    RenderSection(MessageRenderer& renderer, const bool partial_ok) :
        counter_(0), renderer_(renderer), partial_ok_(partial_ok),
        truncated_(false)
    {}
    void operator()(const T& entry) {
        // If it's already truncated, ignore the rest of the section.
        if (truncated_) {
            return;
        }
        const size_t pos0 = renderer_.getLength();
        counter_ += entry->toWire(renderer_);
        if (renderer_.isTruncated()) {
            truncated_ = true;
            if (!partial_ok_) {
                // roll back to the end of the previous RRset.
                renderer_.trim(renderer_.getLength() - pos0);
            }
        }
    }
    unsigned int getTotalCount() { return (counter_); }
    unsigned int counter_;
    MessageRenderer& renderer_;
    const bool partial_ok_;
    bool truncated_;
};
}

void
Message::toWire(MessageRenderer& renderer) {
    if (impl_->mode_ != Message::RENDER) {
        isc_throw(InvalidMessageOperation,
                  "Message rendering attempted in non render mode");
    }

    // reserve room for the header
    renderer.skip(HEADERLEN);

    uint16_t qdcount =
        for_each(impl_->questions_.begin(), impl_->questions_.end(),
                 RenderSection<QuestionPtr>(renderer, false)).getTotalCount();

    // TBD: sort RRsets in each section based on configuration policy.
    uint16_t ancount = 0;
    if (!renderer.isTruncated()) {
        ancount =
            for_each(impl_->rrsets_[sectionCodeToId(Section::ANSWER())].begin(),
                     impl_->rrsets_[sectionCodeToId(Section::ANSWER())].end(),
                     RenderSection<RRsetPtr>(renderer, true)).getTotalCount();
    }
    uint16_t nscount = 0;
    if (!renderer.isTruncated()) {
        nscount =
            for_each(impl_->rrsets_[sectionCodeToId(Section::AUTHORITY())].begin(),
                     impl_->rrsets_[sectionCodeToId(Section::AUTHORITY())].end(),
                     RenderSection<RRsetPtr>(renderer, true)).getTotalCount();
    }
    uint16_t arcount = 0;
    if (renderer.isTruncated()) {
        setHeaderFlag(MessageFlag::TC());
    } else {
        arcount =
            for_each(impl_->rrsets_[sectionCodeToId(Section::ADDITIONAL())].begin(),
                     impl_->rrsets_[sectionCodeToId(Section::ADDITIONAL())].end(),
                     RenderSection<RRsetPtr>(renderer, false)).getTotalCount();
    }

    // Add EDNS OPT RR if necessary.  Basically, we add it only when EDNS
    // has been explicitly set.  However, if the RCODE would require it and
    // no EDNS has been set we generate a temporary local EDNS and use it.
    if (!renderer.isTruncated()) {
        ConstEDNSPtr local_edns = this->impl_->edns_;
        if (!local_edns && impl_->rcode_.getExtendedCode() != 0) {
            local_edns = ConstEDNSPtr(new EDNS());
        }
        if (local_edns) {
            arcount += local_edns->toWire(renderer,
                                          impl_->rcode_.getExtendedCode());
        }
    }
 
    // Adjust the counter buffer.
    // XXX: these may not be equal to the number of corresponding entries
    // in rrsets_[] or questions_ if truncation occurred or an EDNS OPT RR
    // was inserted.  This is not good, and we should revisit the entire
    // design.
    impl_->counts_[Section::QUESTION().getCode()] = qdcount;
    impl_->counts_[Section::ANSWER().getCode()] = ancount;
    impl_->counts_[Section::AUTHORITY().getCode()] = nscount;
    impl_->counts_[Section::ADDITIONAL().getCode()] = arcount;

    // TBD: TSIG, SIG(0) etc.

    // fill in the header
    size_t header_pos = 0;
    renderer.writeUint16At(impl_->qid_, header_pos);
    header_pos += sizeof(uint16_t);

    uint16_t codes_and_flags =
        (impl_->opcode_->getCode() << OPCODE_SHIFT) & OPCODE_MASK;
    codes_and_flags |= (impl_->rcode_.getCode() & RCODE_MASK);
    codes_and_flags |= (impl_->flags_ & FLAG_MASK);
    renderer.writeUint16At(codes_and_flags, header_pos);
    header_pos += sizeof(uint16_t);
    // XXX: should avoid repeated pattern (TODO)
    renderer.writeUint16At(qdcount, header_pos);
    header_pos += sizeof(uint16_t);
    renderer.writeUint16At(ancount, header_pos);
    header_pos += sizeof(uint16_t);
    renderer.writeUint16At(nscount, header_pos);
    header_pos += sizeof(uint16_t);
    renderer.writeUint16At(arcount, header_pos);
    header_pos += sizeof(uint16_t);
}

void
Message::parseHeader(InputBuffer& buffer) {
    if (impl_->mode_ != Message::PARSE) {
        isc_throw(InvalidMessageOperation,
                  "Message parse attempted in non parse mode");
    }

    if ((buffer.getLength() - buffer.getPosition()) < HEADERLEN) {
        isc_throw(MessageTooShort, "Malformed DNS message (short length): "
                  << buffer.getLength() - buffer.getPosition());
    }

    impl_->qid_ = buffer.readUint16();
    const uint16_t codes_and_flags = buffer.readUint16();
    impl_->opcode_ = opcodes[((codes_and_flags & OPCODE_MASK) >> OPCODE_SHIFT)];
    impl_->rcode_ = rcodes[(codes_and_flags & RCODE_MASK)];
    impl_->flags_ = (codes_and_flags & FLAG_MASK);
    impl_->counts_[Section::QUESTION().getCode()] = buffer.readUint16();
    impl_->counts_[Section::ANSWER().getCode()] = buffer.readUint16();
    impl_->counts_[Section::AUTHORITY().getCode()] = buffer.readUint16();
    impl_->counts_[Section::ADDITIONAL().getCode()] = buffer.readUint16();

    impl_->header_parsed_ = true;
}

void
Message::fromWire(InputBuffer& buffer) {
    if (impl_->mode_ != Message::PARSE) {
        isc_throw(InvalidMessageOperation,
                  "Message parse attempted in non parse mode");
    }

    if (!impl_->header_parsed_) {
        parseHeader(buffer);
    }

    impl_->counts_[Section::QUESTION().getCode()] =
        impl_->parseQuestion(buffer);
    impl_->counts_[Section::ANSWER().getCode()] =
        impl_->parseSection(Section::ANSWER(), buffer);
    impl_->counts_[Section::AUTHORITY().getCode()] =
        impl_->parseSection(Section::AUTHORITY(), buffer);
    impl_->counts_[Section::ADDITIONAL().getCode()] =
        impl_->parseSection(Section::ADDITIONAL(), buffer);
}

int
MessageImpl::parseQuestion(InputBuffer& buffer) {
    unsigned int added = 0;

    for (unsigned int count = 0;
         count < counts_[Section::QUESTION().getCode()];
         ++count) {
        const Name name(buffer);

        if ((buffer.getLength() - buffer.getPosition()) <
            2 * sizeof(uint16_t)) {
            isc_throw(DNSMessageFORMERR, "Question section too short: " <<
                      (buffer.getLength() - buffer.getPosition()) << " bytes");
        }
        const RRType rrtype(buffer.readUint16());
        const RRClass rrclass(buffer.readUint16());

        // XXX: need a duplicate check.  We might also want to have an optimized
        // algorithm that requires the question section contain exactly one
        // RR.

        questions_.push_back(QuestionPtr(new Question(name, rrclass, rrtype)));
        ++added;
    }

    return (added);
}

namespace {
struct MatchRR : public unary_function<RRsetPtr, bool> {
    MatchRR(const Name& name, const RRType& rrtype, const RRClass& rrclass) :
        name_(name), rrtype_(rrtype), rrclass_(rrclass) {}
    bool operator()(const RRsetPtr& rrset) const {
        return (rrset->getType() == rrtype_ &&
                rrset->getClass() == rrclass_ &&
                rrset->getName() == name_);
    }
    const Name& name_;
    const RRType& rrtype_;
    const RRClass& rrclass_;
};
}

// Note about design decision:
// we need some type specific processing here, including EDNS and TSIG.
// how much we should generalize/hardcode the special logic is subject
// to discussion.  In terms of modularity it would be ideal to introduce
// an abstract class (say "MessageAttribute") and let other such
// concrete notions as EDNS or TSIG inherit from it.  Then we would
// just do:
// message->addAttribute(rrtype, rrclass, buffer);
// to create and attach type-specific concrete object to the message.
//
// A major downside of this approach is, as usual, complexity due to
// indirection and performance penalty.  Also, it may not be so easy
// to separate the processing logic because in many cases we'll need
// parse context for which the message class is responsible (e.g.
// to check the EDNS OPT RR only appears in the additional section,
// and appears only once).
//
// Another point to consider is that we may not need so many special
// types other than EDNS and TSIG (and when and if we implement it,
// SIG(0)); newer optional attributes of the message would more likely
// be standardized as new flags or options of EDNS.  If that's the case,
// introducing an abstract class with all the overhead and complexity
// may not make much sense.
//
// Conclusion: don't over-generalize type-specific logic for now.
// introduce separate concrete classes, and move context-independent
// logic to that class; processing logic dependent on parse context
// is hardcoded here.
int
MessageImpl::parseSection(const Section& section, InputBuffer& buffer) {
    unsigned int added = 0;

    for (unsigned int count = 0; count < counts_[section.getCode()]; ++count) {
        const Name name(buffer);

        // buffer must store at least RR TYPE, RR CLASS, TTL, and RDLEN.
        if ((buffer.getLength() - buffer.getPosition()) <
            3 * sizeof(uint16_t) + sizeof(uint32_t)) {
            isc_throw(DNSMessageFORMERR, sectiontext[section.getCode()] <<
                      " section too short: " <<
                      (buffer.getLength() - buffer.getPosition()) << " bytes");
        }

        const RRType rrtype(buffer.readUint16());
        const RRClass rrclass(buffer.readUint16());
        const RRTTL ttl(buffer.readUint32());
        const size_t rdlen = buffer.readUint16();
        ConstRdataPtr rdata = createRdata(rrtype, rrclass, buffer, rdlen);

        if (rrtype == RRType::OPT()) {
            if (section != Section::ADDITIONAL()) {
                isc_throw(DNSMessageFORMERR,
                          "EDNS OPT RR found in an invalid section");
            }
            if (edns_) {
                isc_throw(DNSMessageFORMERR, "multiple EDNS OPT RR found");
            }

            uint8_t extended_rcode;
            edns_ = ConstEDNSPtr(createEDNSFromRR(name, rrclass, rrtype, ttl,
                                                  *rdata, extended_rcode));
            rcode_ = Rcode(rcode_.getCode(), extended_rcode);
            continue;
        } else {
            vector<RRsetPtr>::iterator it =
                find_if(rrsets_[sectionCodeToId(section)].begin(),
                        rrsets_[sectionCodeToId(section)].end(),
                        MatchRR(name, rrtype, rrclass));
            if (it != rrsets_[sectionCodeToId(section)].end()) {
                (*it)->setTTL(min((*it)->getTTL(), ttl));
                (*it)->addRdata(rdata);
            } else {
                RRsetPtr rrset =
                    RRsetPtr(new RRset(name, rrclass, rrtype, ttl)); 
                rrset->addRdata(rdata);
                rrsets_[sectionCodeToId(section)].push_back(rrset);
            }
            ++added;
        }
    }

    return (added);
}

namespace {
template <typename T>
struct SectionFormatter {
    SectionFormatter(const Section& section, string& output) :
        section_(section), output_(output) {}
    void operator()(const T& entry) {
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
Message::toText() const {
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

    unsigned int arcount = impl_->counts_[Section::ADDITIONAL().getCode()];
    if (impl_->edns_ != NULL) {
        ++arcount;
    }
    s += ", ADDITIONAL: " + lexical_cast<string>(arcount) + "\n";

    if (impl_->edns_ != NULL) {
        s += impl_->edns_->toText();
    }

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
Message::clear(Mode mode) {
    impl_->init();
    impl_->mode_ = mode;
}

void
Message::makeResponse()
{
    if (impl_->mode_ != Message::PARSE) {
        isc_throw(InvalidMessageOperation,
                  "makeResponse() is performed in non-parse mode");
    }

    impl_->mode_ = Message::RENDER;

    impl_->edns_ = EDNSPtr();
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
SectionIterator<T>::SectionIterator(const SectionIteratorImpl<T>& impl) {
    impl_ = new SectionIteratorImpl<T>(impl.it_);
}

template <typename T>
SectionIterator<T>::~SectionIterator() {
    delete impl_;
}

template <typename T>
SectionIterator<T>::SectionIterator(const SectionIterator<T>& source) :
    impl_(new SectionIteratorImpl<T>(source.impl_->it_))
{}

template <typename T>
void
SectionIterator<T>::operator=(const SectionIterator<T>& source) {
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
SectionIterator<T>::operator++() {
    ++(impl_->it_);
    return (*this);
}

template <typename T>
SectionIterator<T>
SectionIterator<T>::operator++(int) {
    SectionIterator<T> tmp(*this);
    ++(*this);
    return (tmp);
}

template <typename T>
const T&
SectionIterator<T>::operator*() const {
    return (*(impl_->it_));
}

template <typename T>
const T*
SectionIterator<T>::operator->() const {
    return (&(operator*()));
}

template <typename T>
bool
SectionIterator<T>::operator==(const SectionIterator<T>& other) const {
    return (impl_->it_ == other.impl_->it_);
}

template <typename T>
bool
SectionIterator<T>::operator!=(const SectionIterator<T>& other) const {
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
Message::beginQuestion() const {
    return (QuestionIterator(QuestionIteratorImpl(impl_->questions_.begin())));
}

const QuestionIterator
Message::endQuestion() const {
    return (QuestionIterator(QuestionIteratorImpl(impl_->questions_.end())));
}

///
/// RRsets iterators
///
const SectionIterator<RRsetPtr>
Message::beginSection(const Section& section) const {
    if (section == Section::QUESTION()) {
        isc_throw(InvalidMessageSection,
                  "RRset iterator is requested for question");
    }

    return (RRsetIterator(
                RRsetIteratorImpl(
                    impl_->rrsets_[sectionCodeToId(section)].begin())));
}

const SectionIterator<RRsetPtr>
Message::endSection(const Section& section) const {
    if (section == Section::QUESTION()) {
        isc_throw(InvalidMessageSection,
                  "RRset iterator is requested for question");
    }

    return (RRsetIterator(
                RRsetIteratorImpl(
                    impl_->rrsets_[sectionCodeToId(section)].end())));
}

ostream&
operator<<(ostream& os, const Opcode& opcode) {
    return (os << opcode.toText());
}

ostream&
operator<<(ostream& os, const Rcode& rcode) {
    return (os << rcode.toText());
}

ostream&
operator<<(ostream& os, const Message& message) {
    return (os << message.toText());
}

} // end of namespace dns
} // end of namespace isc
