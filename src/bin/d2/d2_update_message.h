// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef D2_UPDATE_MESSAGE_H
#define D2_UPDATE_MESSAGE_H

#include <d2/d2_zone.h>
#include <dns/message.h>
#include <dns/name.h>
#include <dns/rcode.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/tsig.h>

#include <map>

namespace isc {
namespace d2 {

/// @brief Exception indicating that Zone section contains invalid content.
///
/// This exception is thrown when ZONE section of the DNS Update message
/// is invalid. According to RFC2136, section 2.3, the zone section is
/// allowed to contain exactly one record. When Request message contains
/// more records or is empty, this exception is thrown.
class InvalidZoneSection : public Exception {
public:
    InvalidZoneSection(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Exception indicating that QR flag has invalid value.
///
/// This exception is thrown when QR flag has invalid value for
/// the operation performed on the particular message. For instance,
/// the QR flag must be set to indicate that the given message is
/// a RESPONSE when @c D2UpdateMessage::fromWire is performed.
/// The QR flag must be cleared when @c D2UpdateMessage::toWire
/// is executed.
class InvalidQRFlag : public Exception {
public:
    InvalidQRFlag(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Exception indicating that the parsed message is not DNS Update.
///
/// This exception is thrown when decoding the DNS message which is not
/// a DNS Update.
class NotUpdateMessage : public Exception {
public:
    NotUpdateMessage(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Exception indicating that a signed, inbound message failed to verfiy
///
/// This exception is thrown when TSIG verification of a DNS server's response
/// fails.
class TSIGVerifyError : public Exception {
public:
    TSIGVerifyError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};


class D2UpdateMessage;

/// @brief Pointer to the DNS Update Message.
typedef boost::shared_ptr<D2UpdateMessage> D2UpdateMessagePtr;

/// @brief The @c D2UpdateMessage encapsulates a DNS Update message.
///
/// This class represents the DNS Update message. Functions exposed by this
/// class allow to specify the data sections carried by the message and create
/// an on-wire format of this message. This class is also used to decode
/// messages received from the DNS server in the on-wire format.
///
/// <b>Design choice:</b> A dedicated class has been created to encapsulate
/// DNS Update message because existing @c isc::dns::Message is designed to
/// support regular DNS messages (described in RFC 1035) only. Although DNS
/// Update has the same format, particular sections serve different purposes.
/// In order to avoid rewrite of significant portions of @c isc::dns::Message
/// class, this class is implemented in-terms-of @c isc::dns::Message class
/// to reuse its functionality where possible.
class D2UpdateMessage {
public:

    /// @brief Indicates if the @c D2UpdateMessage object encapsulates Inbound
    /// or Outbound message.
    enum Direction {
        INBOUND,
        OUTBOUND
    };

    /// @brief Indicates whether DNS Update message is a REQUEST or RESPONSE.
    enum QRFlag {
        REQUEST,
        RESPONSE
    };

    /// @brief Identifies sections in the DNS Update Message.
    ///
    /// Each message comprises message Header and may contain the following
    /// sections:
    /// - ZONE
    /// - PREREQUISITE
    /// - UPDATE
    /// - ADDITIONAL
    ///
    /// The enum elements are used by functions such as @c getRRCount (to get
    /// the number of records in a corresponding section) and @c beginSection
    /// and @c endSection (to access data in the corresponding section).
    enum UpdateMsgSection {
        SECTION_ZONE,
        SECTION_PREREQUISITE,
        SECTION_UPDATE,
        SECTION_ADDITIONAL
    };

public:
    /// @brief Constructor used to create an instance of the DNS Update Message
    /// (either outgoing or incoming).
    ///
    /// This constructor is used to create an instance of either incoming or
    /// outgoing DNS Update message. The boolean argument indicates wheteher it
    /// is incoming (true) or outgoing (false) message. For incoming messages
    /// the @c D2UpdateMessage::fromWire function is used to parse on-wire data.
    /// For outgoing messages, modifier functions should be used to set the
    /// message contents and @c D2UpdateMessage::toWire function to create
    /// on-wire data.
    ///
    /// @param direction indicates if this is an inbound or outbound message.
    D2UpdateMessage(const Direction direction = OUTBOUND);

    ///
    /// @name Copy constructor and assignment operator
    ///
    /// Copy constructor and assignment operator are private because we assume
    /// there will be no need to copy messages on the client side.
    //@{
private:
    D2UpdateMessage(const D2UpdateMessage& source);
    D2UpdateMessage& operator=(const D2UpdateMessage& source);
    //@}

public:

    /// @brief Returns enum value indicating if the message is a
    /// REQUEST or RESPONSE
    ///
    /// The returned value is REQUEST if the message is created as an outgoing
    /// message. In such case the QR flag bit in the message header is cleared.
    /// The returned value is RESPONSE if the message is created as an incoming
    /// message and the QR flag bit was set in the received message header.
    ///
    /// @return An enum value indicating whether the message is a
    /// REQUEST or RESPONSE.
    QRFlag getQRFlag() const;

    /// @brief Returns message ID.
    ///
    /// @return message ID.
    uint16_t getId() const;

    /// @brief Sets message ID.
    ///
    /// @param id 16-bit value of the message id.
    void setId(const uint16_t id);

    /// @brief Returns an object representing message RCode.
    ///
    /// @return An object representing message RCode.
    const dns::Rcode& getRcode() const;

    /// @brief Sets message RCode.
    ///
    /// @param rcode An object representing message RCode.
    void setRcode(const dns::Rcode& rcode);

    /// @brief Returns number of RRsets in the specified message section.
    ///
    /// @param section An @c UpdateMsgSection enum specifying a message section
    /// for which the number of RRsets is to be returned.
    ///
    /// @return A number of RRsets in the specified message section.
    unsigned int getRRCount(const UpdateMsgSection section) const;

    /// @name Functions returning iterators to RRsets in message sections.
    ///
    //@{
    /// @brief Return iterators pointing to the beginning of the list of RRsets,
    /// which belong to the specified section.
    ///
    /// @param section An @c UpdateMsgSection enum specifying a message section
    /// for which the iterator should be returned.
    ///
    /// @return An iterator pointing to the beginning of the list of the
    /// RRsets, which belong to the specified section.
    const dns::RRsetIterator beginSection(const UpdateMsgSection section) const;

    /// @brief Return iterators pointing to the end of the list of RRsets,
    /// which belong to the specified section.
    ///
    /// @param section An @c UpdateMsgSection enum specifying a message section
    /// for which the iterator should be returned.
    ///
    /// @return An iterator pointing to the end of the list of the
    /// RRsets, which belong to the specified section.
    const dns::RRsetIterator endSection(const UpdateMsgSection section) const;
    //@}

    /// @brief Sets the Zone record.
    ///
    /// This function creates the @c D2Zone object, representing a Zone record
    /// for the outgoing message. If the Zone record is already set, it is
    /// replaced by the new record being set by this function. The RRType for
    /// the record is always SOA.
    ///
    /// @param zone A name of the zone being updated.
    /// @param rrclass A class of the zone record.
    void setZone(const dns::Name& zone, const dns::RRClass& rrclass);

    /// @brief Returns a pointer to the object representing Zone record.
    ///
    /// @return A pointer to the object representing Zone record.
    D2ZonePtr getZone() const;

    /// @brief Adds an RRset to the specified section.
    ///
    /// This function may throw exception if the specified section is
    /// out of bounds or Zone section update is attempted. For Zone
    /// section @c D2UpdateMessage::setZone function should be used instead.
    /// Also, this function expects that @c rrset argument is non-NULL.
    ///
    /// @param section A message section where the RRset should be added.
    /// @param rrset A reference to a RRset which should be added.
    void addRRset(const UpdateMsgSection section, const dns::RRsetPtr& rrset);

    /// @name Functions to handle message encoding and decoding.
    ///
    //@{
    /// @brief Encode outgoing message into wire format.
    ///
    /// This function encodes the DNS Update into the wire format. The format of
    /// such a message is described in the RFC2136, section 2. Some of the
    /// sections which belong to encoded message may be empty. If a particular
    /// message section is empty (does not comprise any RRs), the corresponding
    /// counter in the message header is set to 0. These counters are: PRCOUNT,
    /// UPCOUNT, ADCOUNT for the Prerequisites, Update RRs and Additional Data
    /// RRs respectively. The ZOCOUNT must be equal to 1 because RFC2136
    /// requires that the message comprises exactly one Zone record.
    ///
    /// If given a TSIG context, this method will pass the context down into
    /// dns::Message.toWire() method which signs the message using the context.
    ///
    /// This function does not guarantee exception safety. However, exceptions
    /// should be rare because @c D2UpdateMessage class API prevents invalid
    /// use of the class. The typical case, when this function may throw an
    /// exception is when this it is called on the object representing
    /// incoming (instead of outgoing) message. In such case, the QR field
    /// will be set to RESPONSE, which is invalid setting when calling this
    /// function.
    ///
    /// @param renderer A renderer object used to generate the message wire
    /// format.
    /// @param tsig_ctx A TSIG context that is to be used for signing the
    /// message. If NULL the message will not be signed.
    void toWire(dns::AbstractMessageRenderer& renderer,
                dns::TSIGContext* const tsig_ctx = NULL);

    /// @brief Decode incoming message from the wire format.
    ///
    /// This function decodes the DNS Update message stored in the buffer
    /// specified by the function argument.  If given a TSIG context, then
    /// the function will first attempt to use that context to verify the
    /// message signature.  If verification fails a TSIGVefiryError exception
    /// will be thrown. The function then parses message header and extracts
    /// the section counters: ZOCOUNT, PRCOUNT, UPCOUNT and ADCOUNT. Using
    /// these counters, function identifies message sections, which follow
    /// message header. These sections can be later accessed using:
    /// @c D2UpdateMessage::getZone, @c D2UpdateMessage::beginSection and
    /// @c D2UpdateMessage::endSection functions.
    ///
    /// This function is NOT exception safe. It signals message decoding errors
    /// through exceptions. Message decoding error may occur if the received
    /// message does not conform to the general DNS Message format, specified in
    /// RFC 1035. Errors which are specific to DNS Update messages include:
    /// - Invalid Opcode - not an UPDATE.
    /// - Invalid QR flag - the QR bit should be set to indicate that the
    /// message is the server response.
    /// - The number of records in the Zone section is greater than 1.
    ///
    /// @param received_data buffer holding DNS Update message to be parsed.
    /// @param bytes_received the number of bytes in received_data
    /// @param tsig_context A TSIG context that is to be used to verify the
    /// message. If NULL TSIG verification will not be attempted.
    void fromWire(const void* received_data, size_t bytes_received,
                  dns::TSIGContext* const tsig_context = NULL);
    //@}

private:
    /// Maps the values of the @c UpdateMessageSection field to the
    /// corresponding values in the @c isc::dns::Message class. This
    /// mapping is required here because this class uses @c isc::dns::Message
    /// class to do the actual processing of the DNS Update message.
    ///
    /// @param section An enum indicating the section for which the
    /// corresponding  enum value from @c isc::dns::Message will be returned.
    ///
    /// @return The enum value indicating the section in the DNS message
    /// represented by the @c isc::dns::Message class.
    static
    dns::Message::Section ddnsToDnsSection(const UpdateMsgSection section);

    /// @brief Checks received response message for correctness.
    ///
    /// This function verifies that the received response from a server is
    /// correct. Currently this function checks the following:
    /// - Opcode is 'DNS Update',
    /// - QR flag is RESPONSE (flag bit is set),
    /// - Zone section comprises at most one record.
    ///
    /// The function will throw exception if any of the conditions above are
    /// not met.
    ///
    /// @throw isc::d2::NotUpdateMessage if invalid Opcode.
    /// @throw isc::d2::InvalidQRFlag if QR flag is not set to RESPONSE
    /// @throw isc::d2::InvalidZone section, if Zone section comprises more
    /// than one record.
    void validateResponse() const;

    /// @brief An object representing DNS Message which is used by the
    /// implementation of @c D2UpdateMessage to perform low level.
    ///
    /// Declaration of this object pollutes the header with the details
    /// of @c D2UpdateMessage implementation. It might be cleaner to use
    /// Pimpl idiom to hide this object in an D2UpdateMessageImpl. However,
    /// it would bring additional complications to the implementation
    /// while the benefit would low - this header is not a part of any
    /// common library. Therefore, if implementation is changed, modification of
    /// private members of this class in the header has low impact.
    dns::Message message_;

    /// @brief Holds a pointer to the object, representing Zone in the DNS
    /// Update.
    D2ZonePtr zone_;

};

} // namespace d2
} // namespace isc

#endif // D2_UPDATE_MESSAGE_H
