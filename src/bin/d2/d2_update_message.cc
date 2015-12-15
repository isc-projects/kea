// Copyright (C) 2013-2014 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <d2/d2_update_message.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/opcode.h>
#include <dns/question.h>

namespace isc {
namespace d2 {

using namespace isc::dns;

D2UpdateMessage::D2UpdateMessage(const Direction direction)
    : message_(direction == INBOUND ?
               dns::Message::PARSE : dns::Message::RENDER) {
    // If this object is to create an outgoing message, we have to
    // set the proper Opcode field and QR flag here.
    if (direction == OUTBOUND) {
        message_.setOpcode(Opcode(Opcode::UPDATE_CODE));
        message_.setHeaderFlag(dns::Message::HEADERFLAG_QR, false);
        message_.setRcode(Rcode::NOERROR());
    }
}

D2UpdateMessage::QRFlag
D2UpdateMessage::getQRFlag() const {
    return (message_.getHeaderFlag(dns::Message::HEADERFLAG_QR) ?
            RESPONSE : REQUEST);
}

uint16_t
D2UpdateMessage::getId() const {
    return (message_.getQid());
}

void
D2UpdateMessage::setId(const uint16_t id) {
    message_.setQid(id);
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

const dns::RRsetIterator
D2UpdateMessage::beginSection(const UpdateMsgSection section) const {
    return (message_.beginSection(ddnsToDnsSection(section)));
}

const dns::RRsetIterator
D2UpdateMessage::endSection(const UpdateMsgSection section) const {
    return (message_.endSection(ddnsToDnsSection(section)));
}

void
D2UpdateMessage::setZone(const Name& zone, const RRClass& rrclass) {
    // The Zone data is kept in the underlying Question class. If there
    // is a record stored there already, we need to remove it, because
    // we may have at most one Zone record in the DNS Update message.
    if (message_.getRRCount(dns::Message::SECTION_QUESTION) > 0) {
        message_.clearSection(dns::Message::SECTION_QUESTION);
    }
    // Add the new record...
    Question question(zone, rrclass, RRType::SOA());
    message_.addQuestion(question);
    // ... and update the local class member holding the D2Zone object.
    zone_.reset(new D2Zone(question.getName(), question.getClass()));
}

D2ZonePtr
D2UpdateMessage::getZone() const {
    return (zone_);
}

void
D2UpdateMessage::addRRset(const UpdateMsgSection section,
                          const dns::RRsetPtr& rrset) {
    if (section == SECTION_ZONE) {
        isc_throw(isc::BadValue, "unable to add RRset to the Zone section"
                  " of the DNS Update message, use setZone instead");
    }
    message_.addRRset(ddnsToDnsSection(section), rrset);
}

void
D2UpdateMessage::toWire(AbstractMessageRenderer& renderer,
                        TSIGContext* const tsig_context) {
    // We are preparing the wire format of the message, meaning
    // that this message will be sent as a request to the DNS.
    // Therefore, we expect that this message is a REQUEST.
    if (getQRFlag() != REQUEST) {
        isc_throw(InvalidQRFlag, "QR flag must be cleared for the outgoing"
                  " DNS Update message");
    }
    // According to RFC2136, the ZONE section may contain exactly one
    // record.
    if (getRRCount(SECTION_ZONE) != 1) {
        isc_throw(InvalidZoneSection, "Zone section of the DNS Update message"
                  " must comprise exactly one record (RFC2136, section 2.3)");
    }
    message_.toWire(renderer, tsig_context);
}

void
D2UpdateMessage::fromWire(const void* received_data, size_t bytes_received,
                          dns::TSIGContext* const tsig_context) {
    // First, use the underlying dns::Message implementation to get the
    // contents of the DNS response message. Note that it may or may
    // not be the message that we are interested in, but needs to be
    // parsed so as we can check its ID, Opcode etc.
    isc::util::InputBuffer received_data_buffer(received_data, bytes_received);
    message_.fromWire(received_data_buffer);

    // If tsig_contex is not NULL, then we need to verify the message.
    if (tsig_context) {
        TSIGError error = tsig_context->verify(message_.getTSIGRecord(),
                                               received_data, bytes_received);
        if (error != TSIGError::NOERROR()) {
            isc_throw(TSIGVerifyError, "TSIG verification failed: "
                      << error.toText());
        }
    }

    // This class exposes the getZone() function. This function will return
    // pointer to the D2Zone object if non-empty Zone section exists in the
    // received message. It will return NULL pointer if it doesn't exist.
    // The pointer is held in the D2UpdateMessage class member. We need to
    // update this pointer every time we parse the message.
    if (getRRCount(D2UpdateMessage::SECTION_ZONE) > 0) {
        // There is a Zone section in the received message. Replace
        // Zone pointer with the new value.
        QuestionPtr question = *message_.beginQuestion();
        // If the Zone counter is greater than 0 (which we have checked)
        // there must be a valid Question pointer stored in the message_
        // object. If there isn't, it is a programming error.
        assert(question);
        zone_.reset(new D2Zone(question->getName(), question->getClass()));

    } else {
        // Zone section doesn't hold any pointers, so set the pointer to NULL.
        zone_.reset();

    }
    // Check that the content of the received message is sane.
    // One of the basic checks to do is to verify that we have
    // received the DNS update message. If not, it can be dropped
    // or an error message can be printed. Other than that, we
    // will check that there is at most one Zone record and QR flag
    // is set.
    validateResponse();
}

dns::Message::Section
D2UpdateMessage::ddnsToDnsSection(const UpdateMsgSection section) {
    /// The following switch maps the enumerator values from the
    /// DNS Update message to the corresponding enumerator values
    /// representing fields of the DNS message.
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

void
D2UpdateMessage::validateResponse() const {
    // Verify that we are dealing with the DNS Update message. According to
    // RFC 2136, section 3.8 server will copy the Opcode from the query.
    // If we are dealing with a different type of message, we may simply
    // stop further processing, because it is likely that the message was
    // directed to someone else.
    if (message_.getOpcode() != Opcode::UPDATE()) {
        isc_throw(NotUpdateMessage, "received message is not a DDNS update,"
                  << " received message code is "
                  << message_.getOpcode().getCode());
    }
    // Received message should have QR flag set, which indicates that it is
    // a RESPONSE.
    if (getQRFlag() == REQUEST) {
        isc_throw(InvalidQRFlag, "received message should have QR flag set,"
                  " to indicate that it is a RESPONSE message; the QR"
                  << " flag in received message is unset");
    }
    // DNS server may copy a Zone record from the query message. Since query
    // must comprise exactly one Zone record (RFC 2136, section 2.3), the
    // response message may contain 1 record at most. It may also contain no
    // records if a server chooses not to copy Zone section.
    if (getRRCount(SECTION_ZONE) > 1) {
        isc_throw(InvalidZoneSection, "received message contains "
                  << getRRCount(SECTION_ZONE) << " Zone records,"
                  << " it should contain at most 1 record");
    }
}

} // namespace d2
} // namespace isc

