// Copyright (C) 2009-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MESSAGE_H
#define MESSAGE_H 1

#include <stdint.h>

#include <iterator>
#include <string>
#include <ostream>

#include <dns/exceptions.h>

#include <dns/edns.h>
#include <dns/question.h>
#include <dns/rrset.h>

namespace isc {
namespace util {
class InputBuffer;
}

namespace dns {
class TSIGContext;
class TSIGRecord;

///
/// \brief A standard DNS module exception that is thrown if a wire format
/// message parser encounters a short length of data that don't even contain
/// the full header section.
///
class MessageTooShort : public isc::dns::Exception {
public:
    MessageTooShort(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if a section iterator
/// is being constructed for an incompatible section.  Specifically, this
/// happens RRset iterator is being constructed for a Question section.
///
class InvalidMessageSection : public isc::dns::Exception {
public:
    InvalidMessageSection(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if a \c Message
/// class method is called that is prohibited for the current mode of
/// the message.
///
class InvalidMessageOperation : public isc::dns::Exception {
public:
    InvalidMessageOperation(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if a UDP buffer size
/// smaller than the standard default maximum (DEFAULT_MAX_UDPSIZE) is
/// being specified for the message.
///
class InvalidMessageUDPSize : public isc::dns::Exception {
public:
    InvalidMessageUDPSize(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

typedef uint16_t qid_t;

class AbstractMessageRenderer;
class Message;
class MessageImpl;
class Opcode;
class Rcode;

template <typename T>
struct SectionIteratorImpl;

/// \c SectionIterator is a templated class to provide standard-compatible
/// iterators for Questions and RRsets for a given DNS message section.
/// The template parameter is either \c QuestionPtr (for the question section)
/// or \c RRsetPtr (for the answer, authority, or additional section).
template <typename T>
class SectionIterator {
public:
    // Aliases used to enable iterator behavior on this class
    using iterator_category = std::input_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    SectionIterator() : impl_(NULL) {}
    SectionIterator(const SectionIteratorImpl<T>& impl);
    ~SectionIterator();
    SectionIterator(const SectionIterator<T>& source);
    void operator=(const SectionIterator<T>& source);
    SectionIterator<T>& operator++();
    SectionIterator<T> operator++(int);
    const T& operator*() const;
    const T* operator->() const;
    bool operator==(const SectionIterator<T>& other) const;
    bool operator!=(const SectionIterator<T>& other) const;
private:
    SectionIteratorImpl<T>* impl_;
};

typedef SectionIterator<QuestionPtr> QuestionIterator;
typedef SectionIterator<RRsetPtr> RRsetIterator;

class MessageImpl;
/// @brief Pointer to the @ref MessageImpl object.
typedef boost::shared_ptr<MessageImpl> MessageImplPtr;

/// \brief The \c Message class encapsulates a standard DNS message.
///
/// Details of the design and interfaces of this class are still in flux.
/// Here are some notes about the current design.
///
/// Since many realistic DNS applications deal with messages, message objects
/// will be frequently used, and can be performance sensitive.  To minimize
/// the performance overhead of constructing and destructing the objects,
/// this class is designed to be reusable.  The \c clear() method is provided
/// for this purpose.
///
/// A \c Message class object is in either the \c PARSE or the \c RENDER mode.
/// A \c PARSE mode object is intended to be used to convert wire-format
/// message data into a complete \c Message object.
/// A \c RENDER mode object is intended to be used to convert a \c Message
/// object into wire-format data.
/// Some of the method functions of this class are limited to a specific mode.
/// In general, "set" type operations are only allowed for \c RENDER mode
/// objects.
/// The initial mode must be specified on construction, and can be changed
/// through some method functions.
///
/// This class uses the "pimpl" idiom, and hides detailed implementation
/// through the \c impl_ pointer.  Since a \c Message object is expected to
/// be reused, the construction overhead of this approach should be acceptable.
///
/// Open issues (among other things):
/// - We may want to provide an "iterator" for all RRsets/RRs for convenience.
///   This will be for applications that do not care about performance much,
///   so the implementation can only be moderately efficient.
/// - We may want to provide a "find" method for a specified type
///   of RR in the message.
class Message {
public:
    /// Constants to specify the operation mode of the \c Message.
    enum Mode {
        PARSE = 0,              ///< Parse mode (handling an incoming message)
        RENDER = 1              ///< Render mode (building an outgoing message)
    };

    /// \brief Constants for flag bit fields of a DNS message header.
    ///
    /// Only the defined constants are valid where a header flag is required
    /// in this library (e.g., in \c Message::setHeaderFlag()).
    /// Since these are enum constants, however, an invalid value could be
    /// passed via casting without an error at compilation time.
    /// It is generally the callee's responsibility to check and reject invalid
    /// values.
    /// Of course, applications shouldn't pass invalid values even if the
    /// callee does not perform proper validation; the result in such usage
    /// is undefined.
    ///
    /// In the current implementation, the defined values happen to be
    /// a 16-bit integer with one bit being set corresponding to the
    /// specified flag in the second 16 bits of the DNS Header section
    /// in order to make the internal implementation simpler.
    /// For example, \c HEADERFLAG_QR is defined to be 0x8000 as the QR
    /// bit is the most significant bit of the second 16 bits of the header.
    /// However, applications should not assume this coincidence and
    /// must solely use the enum representations.
    /// Any usage based on the assumption of the underlying values is invalid
    /// and the result is undefined.
    ///
    /// Likewise, bit wise operations such as AND or OR on the flag values
    /// are invalid and are not guaranteed to work, even if it could compile
    /// with casting.
    /// For example, the following code will compile:
    /// \code const uint16_t combined_flags =
    ///           static_cast<uint16_t>(Message::HEADERFLAG_AA) |
    ///           static_cast<uint16_t>(Message::HEADERFLAG_CD);
    /// message->setHeaderFlag(static_cast<Message::HeaderFlag>(combined_flags));
    /// \endcode
    /// and (with the current definition) happens to work as if it were
    /// validly written as follows:
    /// \code message->setHeaderFlag(Message::HEADERFLAG_AA);
    /// message->setHeaderFlag(Message::HEADERFLAG_CD);
    /// \endcode
    /// But the former notation is invalid and may not work in future versions.
    /// We did not try to prohibit such usage at compilation time, e.g., by
    /// introducing a separately defined class considering the balance
    /// between the complexity and advantage, but hopefully the cast notation
    /// is sufficiently ugly to prevent proliferation of the usage.
    enum HeaderFlag {
        HEADERFLAG_QR = 0x8000, ///< Query (if cleared) or response (if set)
        HEADERFLAG_AA = 0x0400, ///< Authoritative answer
        HEADERFLAG_TC = 0x0200, ///< Truncation
        HEADERFLAG_RD = 0x0100, ///< Recursion desired
        HEADERFLAG_RA = 0x0080, ///< Recursion available
        HEADERFLAG_AD = 0x0020, ///< Authentic %data (RFC4035)
        HEADERFLAG_CD = 0x0010  ///< DNSSEC checking disabled (RFC4035)
    };

    /// \brief Constants to specify sections of a DNS message.
    ///
    /// The sections are those defined in RFC 1035 excluding the Header
    /// section; the fields of the Header section are accessed via specific
    /// methods of the \c Message class (e.g., \c getQid()).
    ///
    /// <b>Open Design Issue:</b>
    /// In the current implementation the values for the constants are
    /// sorted in the order of appearance in DNS messages, i.e.,
    /// from %Question to Additional.
    /// So, for example,
    /// code <code>section >= Message::SECTION_AUTHORITY</code> can be
    /// used to do something in or after the Authority section.
    /// This would be convenient, but it is not clear if it's really a good
    /// idea to rely on relationship between the underlying values of enum
    /// constants.  At the moment, applications are discouraged to rely on
    /// this implementation detail.  We will see if such usage is sufficiently
    /// common to officially support it.
    ///
    /// Note also that since we don't define \c operator++ for this enum,
    /// the following code intending to iterate over all sections will
    /// \b not compile:
    /// \code for (Section s; s <= SECTION_ADDITIONAL; ++s) { // ++s undefined
    ///     // do something
    /// } \endcode
    /// This is intentional at this moment, and we'll see if we need to allow
    /// that as we have more experiences with this library.
    ///
    /// <b>Future Extension:</b> We'll probably also define constants for
    /// the section names used in dynamic updates in future versions.
    enum Section {
        SECTION_QUESTION = 0,   ///< %Question section
        SECTION_ANSWER = 1,     ///< Answer section
        SECTION_AUTHORITY = 2,  ///< Authority section
        SECTION_ADDITIONAL = 3  ///< Additional section
    };

    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private.
    /// The intended use case wouldn't require copies of a \c Message object;
    /// once created, it would normally be expected to be reused, changing the
    /// mode from \c PARSE to \c RENDER, and vice versa.
    //@{
public:
    /// \brief The constructor.
    /// The mode of the message is specified by the \c mode parameter.
    Message(Mode mode);
    /// \brief The destructor.
    ~Message() = default;
private:
    Message(const Message& source);
    Message& operator=(const Message& source);
    //@}
public:
    /// \brief Return whether the specified header flag bit is set in the
    /// header section.
    ///
    /// This method is basically exception free, but if
    /// \c flag is not a valid constant of the \c HeaderFlag type,
    /// an exception of class \c InvalidParameter will be thrown.
    ///
    /// \param flag The header flag constant to test.
    /// \return \c true if the specified flag is set; otherwise \c false.
    bool getHeaderFlag(const HeaderFlag flag) const;

    /// \brief Set or clear the specified header flag bit in the header
    /// section.
    ///
    /// The optional parameter \c on indicates the operation mode,
    /// set or clear; if it's \c true the corresponding flag will be set;
    /// otherwise the flag will be cleared.
    /// In either case the original state of the flag does not affect the
    /// operation; for example, if a flag is already set and the "set"
    /// operation is attempted, it effectively results in no operation.
    ///
    /// The parameter \c on can be omitted, in which case a value of \c true
    /// (i.e., set operation) will be assumed.
    /// This is based on the observation that the flag would have to be set
    /// in the vast majority of the cases where an application needs to
    /// use this method.
    ///
    /// This method is only allowed in the \c RENDER mode;
    /// if the \c Message is in other mode, an exception of class
    /// InvalidMessageOperation will be thrown.
    ///
    /// If \c flag is not a valid constant of the \c HeaderFlag type,
    /// an exception of class \c InvalidParameter will be thrown.
    ///
    /// \param flag The header flag constant to set or clear.
    /// \param on If \c true the flag will be set; otherwise the flag will be
    /// cleared.
    void setHeaderFlag(const HeaderFlag flag, const bool on = true);

    /// \brief Return the query ID given in the header section of the message.
    qid_t getQid() const;

    /// \brief Set the query ID of the header section of the message.
    ///
    /// This method is only allowed in the \c RENDER mode;
    /// if the \c Message is in other mode, an exception of class
    /// InvalidMessageOperation will be thrown.
    void setQid(qid_t qid);

    /// \brief Return the Response Code of the message.
    ///
    /// This includes extended codes specified by an EDNS OPT RR (when
    /// included).  In the \c PARSE mode, if the received message contains
    /// an EDNS OPT RR, the corresponding extended code is identified and
    /// returned.
    ///
    /// The message must have been properly parsed (in the case of the
    /// \c PARSE mode) or an \c Rcode has been set (in the case of the
    /// \c RENDER mode) beforehand.  Otherwise, an exception of class
    /// \c InvalidMessageOperation will be thrown.
    const Rcode& getRcode() const;

    /// \brief Set the Response Code of the message.
    ///
    /// This method is only allowed in the \c RENDER mode;
    /// if the \c Message is in other mode, an exception of class
    /// InvalidMessageOperation will be thrown.
    ///
    /// If the specified code is an EDNS extended RCODE, an EDNS OPT RR will be
    /// included in the message.
    void setRcode(const Rcode& rcode);

    /// \brief Return the OPCODE given in the header section of the message.
    ///
    /// The message must have been properly parsed (in the case of the
    /// \c PARSE mode) or an \c Opcode has been set (in the case of the
    /// \c RENDER mode) beforehand.  Otherwise, an exception of class
    /// \c InvalidMessageOperation will be thrown.
    const Opcode& getOpcode() const;

    /// \brief Set the OPCODE of the header section of the message.
    ///
    /// This method is only allowed in the \c RENDER mode;
    /// if the \c Message is in other mode, an exception of class
    /// InvalidMessageOperation will be thrown.
    void setOpcode(const Opcode& opcode);

    /// \brief Return, if any, the EDNS associated with the message.
    ///
    /// This method never throws an exception.
    ///
    /// \return A shared pointer to the EDNS.  This will be a null shared
    /// pointer if the message is not associated with EDNS.
    ConstEDNSPtr getEDNS() const;

    /// \brief Set EDNS for the message.
    ///
    /// This method is only allowed in the \c RENDER mode;
    /// if the \c Message is in other mode, an exception of class
    /// InvalidMessageOperation will be thrown.
    ///
    /// \param edns A shared pointer to an \c EDNS object to be set in
    /// \c Message.
    void setEDNS(ConstEDNSPtr edns);

    /// \brief Return, if any, the TSIG record contained in the received
    /// message.
    ///
    /// Currently, this method is only intended to return a TSIG record
    /// for an incoming message built via the \c fromWire() method in the
    /// PARSE mode.  A call to this method in the RENDER mode is invalid and
    /// result in an exception.  Also, calling this method is meaningless
    /// unless \c fromWire() is performed.
    ///
    /// The returned pointer is valid only during the lifetime of the
    /// \c Message object and until \c clear() is called.  The \c Message
    /// object retains the ownership of \c TSIGRecord; the caller must not
    /// try to delete it.
    ///
    /// \exception InvalidMessageOperation Message is not in the PARSE mode.
    ///
    /// \return A pointer to the stored \c TSIGRecord or \c NULL.
    const TSIGRecord* getTSIGRecord() const;

    /// \brief Returns the number of RRs contained in the given section.
    ///
    /// In the \c PARSE mode, the returned value may not be identical to
    /// the actual number of RRs of the incoming message that is parsed.
    /// The \c Message class handles some "meta" RRs such as EDNS OPT RR
    /// separately.  This method doesn't include such RRs.
    /// Also, a future version of the parser will detect and unify duplicate
    /// RRs (which should be rare in practice though), in which case
    /// the stored RRs in the \c Message object will be fewer than the RRs
    /// originally contained in the incoming message.
    ///
    /// Likewise, in the \c RENDER mode, even if \c EDNS is set in the
    /// \c Message, this method doesn't count the corresponding OPT RR
    /// in the Additional section.
    ///
    /// This method is basically exception free, but if
    /// \c section is not a valid constant of the \c Section type,
    /// an exception of class \c OutOfRange will be thrown.
    ///
    /// \param section The section in the message where RRs should be
    /// counted.
    /// \return The number of RRs stored in the specified section of the
    /// message.
    unsigned int getRRCount(const Section section) const;

    /// \brief Return an iterator corresponding to the beginning of the
    /// Question section of the message.
    const QuestionIterator beginQuestion() const;

    /// \brief Return an iterator corresponding to the end of the
    /// Question section of the message.
    const QuestionIterator endQuestion() const;

    /// \brief Return an iterator corresponding to the beginning of the
    /// given section (other than Question) of the message.
    ///
    /// \c section must be a valid constant of the \c Section type;
    /// otherwise, an exception of class \c OutOfRange will be thrown.
    const RRsetIterator beginSection(const Section section) const;

    /// \brief Return an iterator corresponding to the end of the
    /// given section (other than Question) of the message.
    ///
    /// \c section must be a valid constant of the \c Section type;
    /// otherwise, an exception of class \c OutOfRange will be thrown.
    const RRsetIterator endSection(const Section section) const;

    /// \brief Add a (pointer like object of) Question to the message.
    ///
    /// This method is only allowed in the \c RENDER mode;
    /// if the \c Message is in other mode, an exception of class
    /// InvalidMessageOperation will be thrown.
    void addQuestion(QuestionPtr question);

    /// \brief Add a (pointer like object of) Question to the message.
    ///
    /// This version internally creates a \c QuestionPtr object from the
    /// given \c question and calls the other version of this method.
    /// So this is inherently less efficient, but is provided because this
    /// form may be more intuitive and may make more sense for performance
    /// insensitive applications.
    ///
    /// This method is only allowed in the \c RENDER mode;
    /// if the \c Message is in other mode, an exception of class
    /// InvalidMessageOperation will be thrown.
    void addQuestion(const Question& question);

    /// \brief Add a (pointer like object of) RRset to the given section
    /// of the message.
    ///
    /// Note that \c addRRset() does not currently check for duplicate
    /// data before inserting RRsets.  The caller is responsible for
    /// checking for these (see \c hasRRset() below).
    ///
    /// \throw InvalidParameter rrset is NULL
    /// \throw InvalidMessageOperation The message is not in the \c RENDER
    /// mode.
    /// \throw OutOfRange \c section doesn't specify a valid \c Section value.
    ///
    /// \param section The message section to which the rrset is to be added
    /// \param rrset The rrset to be added.  Must not be NULL.
    void addRRset(const Section section, RRsetPtr rrset);

    /// \brief Determine whether the given section already has an RRset
    /// matching the given name, RR class and RR type.
    ///
    /// \c section must be a valid constant of the \c Section type;
    /// otherwise, an exception of class \c OutOfRange will be thrown.
    ///
    /// This should probably be extended to be a "find" method that returns
    /// a matching RRset if found.
    bool hasRRset(const Section section, const Name& name,
                  const RRClass& rrclass, const RRType& rrtype) const;

    /// \brief Determine whether the given section already has an RRset
    /// matching the one pointed to by the argument
    ///
    /// \c section must be a valid constant of the \c Section type;
    /// otherwise, an exception of class \c OutOfRange will be thrown.
    bool hasRRset(const Section section, const RRsetPtr& rrset) const;

    /// \brief Remove RRSet from Message
    ///
    /// Removes the RRset identified by the section iterator from the message.
    /// Note: if,.for some reason, the RRset is duplicated in the section, only
    /// one occurrence is removed.
    ///
    /// If the operation is successful, all iterators into the section are
    /// invalidated.
    ///
    /// \param section Section to which the iterator belongs
    /// \param iterator Iterator pointing to the element to be removed
    ///
    /// \return true if the element was removed, false if the iterator was not
    /// found in the specified section.
    bool removeRRset(const Section section, RRsetIterator& iterator);

    /// \brief Remove all RRSets from the given Section
    ///
    /// This method is only allowed in the \c RENDER mode, and the given
    /// section must be valid.
    ///
    /// \throw InvalidMessageOperation Message is not in the \c RENDER mode
    /// \throw OutOfRange The specified section is not valid
    ///
    /// \param section Section to remove all rrsets from
    void clearSection(const Section section);

    // The following methods are not currently implemented.
    //void removeQuestion(QuestionPtr question);
    // notyet:
    //void addRR(const Section section, const RR& rr);
    //void removeRR(const Section section, const RR& rr);

    /// \brief Clear the message content (if any) and reinitialize it in the
    /// specified mode.
    void clear(Mode mode);

    /// \brief Adds all rrsets from the source the given section in the
    /// source message to the same section of this message
    ///
    /// \param section the section to append
    /// \param source The source Message
    void appendSection(const Section section, const Message& source);

    /// \brief Prepare for making a response from a request.
    ///
    /// This will clear the DNS header except those fields that should be kept
    /// for the response, and clear answer and the following sections.
    /// See also dns_message_reply() of BIND9.
    void makeResponse();

    /// \brief Convert the Message to a string.
    ///
    /// At least \c Opcode and \c Rcode must be validly set in the \c Message
    /// (as a result of parse in the \c PARSE mode or by explicitly setting
    /// in the \c RENDER mode);  otherwise, an exception of
    /// class \c InvalidMessageOperation will be thrown.
    std::string toText() const;

    /// \brief Render the message in wire formant into a message renderer
    /// object with (or without) TSIG.
    ///
    /// This \c Message must be in the \c RENDER mode and both \c Opcode and
    /// \c Rcode must have been set beforehand; otherwise, an exception of
    /// class \c InvalidMessageOperation will be thrown.
    ///
    /// If a non-NULL \c tsig_ctx is passed, it will also add a TSIG RR
    /// with (in many cases) the TSIG MAC for the message along with the
    /// given TSIG context (\c tsig_ctx).  The TSIG RR will be placed at
    /// the end of \c renderer. The \c TSIGContext at \c tsig_ctx will
    /// be updated based on the fact it was used for signing and with
    /// the latest MAC.
    ///
    /// \exception InvalidMessageOperation The message is not in the Render
    /// mode, or either Rcode or Opcode is not set.
    /// \exception InvalidParameter The allowable limit of \c renderer is too
    /// small for a TSIG or the Header section.  Note that this shouldn't
    /// happen with parameters as defined in the standard protocols,
    /// so it's more likely a program bug.
    /// \exception Unexpected Rendering the TSIG RR fails.  The implementation
    /// internally makes sure this doesn't happen, so if that ever occurs
    /// it should mean a bug either in the TSIG context or in the renderer
    /// implementation.
    ///
    /// \note The renderer's internal buffers and data are automatically
    /// cleared, keeping the length limit and the compression mode intact.
    /// In case truncation is triggered, the renderer is cleared completely.
    ///
    /// \param renderer DNS message rendering context that encapsulates the
    /// output buffer and name compression information.
    /// \param tsig_ctx A TSIG context that is to be used for signing the
    /// message
    void toWire(AbstractMessageRenderer& renderer,
                TSIGContext* tsig_ctx = NULL);

    /// Parse options.
    ///
    /// describe PRESERVE_ORDER: note doesn't affect EDNS or TSIG.
    ///
    /// The option values are used as a parameter for \c fromWire().
    /// These are values of a bitmask type.  Bitwise operations can be
    /// performed on these values to express compound options.
    enum ParseOptions {
        PARSE_DEFAULT = 0,       ///< The default options
        PRESERVE_ORDER = 1       ///< Preserve RR order and don't combine them
    };

    /// \brief Parse the header section of the \c Message.
    ///
    /// NOTE: If the header has already been parsed by a previous call
    /// to this method, this method simply returns (i.e., it does not
    /// read from the \c buffer).
    void parseHeader(isc::util::InputBuffer& buffer);

    /// \brief (Re)build a \c Message object from wire-format data.
    ///
    /// This method parses the given wire format data to build a
    /// complete Message object.  On success, the values of the header section
    /// fields can be accessible via corresponding get methods, and the
    /// question and following sections can be accessible via the
    /// corresponding iterators.  If the message contains an EDNS or TSIG,
    /// they can be accessible via \c getEDNS() and \c getTSIGRecord(),
    /// respectively.
    ///
    /// This \c Message must be in the \c PARSE mode.
    ///
    /// This method performs strict validation on the given message based
    /// on the DNS protocol specifications.  If the given message data is
    /// invalid, this method throws an exception (see the exception list).
    ///
    /// By default, this method combines RRs of the same name, RR type and
    /// RR class in a section into a single RRset, even if they are interleaved
    /// with a different type of RR (though it would be a rare case in
    /// practice).  If the \c PRESERVE_ORDER option is specified, it handles
    /// each RR separately, in the appearing order, and converts it to a
    /// separate RRset (so this RRset should contain exactly one Rdata).
    /// This mode will be necessary when the higher level protocol is
    /// ordering conscious.  For example, in AXFR and IXFR, the position of
    /// the SOA RRs are crucial.
    ///
    /// \exception InvalidMessageOperation \c Message is in the RENDER mode
    /// \exception DNSMessageFORMERR The given message data is syntactically
    /// \exception MessageTooShort The given data is shorter than a valid
    /// header section
    /// \exception std::bad_alloc Memory allocation failure
    /// \exception Others \c Name, \c Rdata, and \c EDNS classes can also throw
    ///
    /// \param buffer A input buffer object that stores the wire
    /// data. This method reads from position 0 in the passed buffer.
    /// \param options Parse options
    void fromWire(isc::util::InputBuffer& buffer, ParseOptions options
        = PARSE_DEFAULT);

    ///
    /// \name Protocol constants
    ///
    //@{
    /// \brief The default maximum size of UDP DNS messages that don't cause
    /// truncation.
    ///
    /// With EDNS the maximum size can be increased per message.
    static const uint16_t DEFAULT_MAX_UDPSIZE = 512;

    /// \brief The default maximum size of UDP DNS messages we can handle
    static const uint16_t DEFAULT_MAX_EDNS0_UDPSIZE = 4096;
    //@}

private:
    MessageImplPtr impl_;
};

/// \brief Pointer-like type pointing to a \c Message
///
/// This type is expected to be used as an argument in asynchronous
/// callback functions.  The internal reference-counting will ensure that
/// that ongoing state information will not be lost if the object
/// that originated the asynchronous call falls out of scope.
typedef boost::shared_ptr<Message> MessagePtr;
typedef boost::shared_ptr<const Message> ConstMessagePtr;

/// Insert the \c Message as a string into stream.
///
/// This method convert \c message into a string and inserts it into the
/// output stream \c os.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param message A \c Message object output by the operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream& operator<<(std::ostream& os, const Message& message);

}  // namespace dns
}  // namespace isc

#endif  // MESSAGE_H
