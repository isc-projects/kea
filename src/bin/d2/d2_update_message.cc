// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/opcode.h>
#include <dns/question.h>

#include <d2/d2_update_message.h>

namespace isc {
namespace d2 {

using namespace isc::dns;

D2UpdateMessage::D2UpdateMessage(const bool parse)
    : message_(parse ? dns::Message::PARSE : dns::Message::RENDER) {
    message_.setOpcode(Opcode(Opcode::UPDATE_CODE));
}

D2UpdateMessage::QRFlag
D2UpdateMessage::getQRFlag() const {
    return (message_.getHeaderFlag(dns::Message::HEADERFLAG_QR) ?
            RESPONSE : REQUEST);
}

void
D2UpdateMessage::setQRFlag(const QRFlag flag) {
    bool on = (flag == RESPONSE ? true : false);
    message_.setHeaderFlag(dns::Message::HEADERFLAG_QR, on);
}

uint16_t
D2UpdateMessage::getQid() const {
    return (message_.getQid());
}

void
D2UpdateMessage::setQid(const uint16_t qid) {
    message_.setQid(qid);
}


const dns::Rcode&
D2UpdateMessage::getRcode() const {
    return (message_.getRcode());
}

void
D2UpdateMessage::setRcode(const dns::Rcode& rcode) {
    message_.setRcode(rcode);
}

unsigned int
D2UpdateMessage::getRRCount(const UpdateMsgSection section) const {
    return (message_.getRRCount(ddnsToDnsSection(section)));
}

void
D2UpdateMessage::setZone(const Name& zone, const RRClass& rrclass) {
    if (message_.getRRCount(dns::Message::SECTION_QUESTION) > 0) {
        message_.clearSection(dns::Message::SECTION_QUESTION);
    }

    message_.addQuestion(Question(zone, rrclass, RRType::SOA()));
}

void
D2UpdateMessage::addRRset(const UpdateMsgSection section,
                          const dns::RRsetPtr& rrset) {
    message_.addRRset(ddnsToDnsSection(section), rrset);

}

bool
D2UpdateMessage::hasRRset(const UpdateMsgSection section, const dns::Name& name,
                          const dns::RRClass& rrclass, const dns::RRType& rrtype) {
    return (message_.hasRRset(ddnsToDnsSection(section), name, rrclass, rrtype));
}

bool
D2UpdateMessage::hasRRset(const UpdateMsgSection section, const dns::RRsetPtr &rrset) {
    return (message_.hasRRset(ddnsToDnsSection(section), rrset));
}

void
D2UpdateMessage::toWire(AbstractMessageRenderer& renderer) {
    if (getRRCount(SECTION_ZONE) != 1) {
        isc_throw(InvalidZoneSection, "Zone section of the DNS Update message"
                  " must comprise exactly one record (RFC2136, section 2.3)");
    }
    message_.toWire(renderer);
}

void
D2UpdateMessage::fromWire(isc::util::InputBuffer& buffer) {
    message_.fromWire(buffer);
}

dns::Message::Section
D2UpdateMessage::ddnsToDnsSection(const UpdateMsgSection section) {
    switch(section) {
    case SECTION_ZONE :
        return (dns::Message::SECTION_QUESTION);
    case SECTION_PREREQUISITE:
        return (dns::Message::SECTION_ANSWER);
    case SECTION_UPDATE:
        return (dns::Message::SECTION_AUTHORITY);
    case SECTION_ADDITIONAL:
        return (dns::Message::SECTION_ADDITIONAL);
    default:
        ;
    }
    isc_throw(dns::InvalidMessageSection,
              "unknown message section " << section);
}

} // namespace d2
} // namespace isc

