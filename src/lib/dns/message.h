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

#include <stdint.h>

#include <iterator>
#include <string>
#include <ostream>

#include <exceptions/exceptions.h>

#include <dns/edns.h>
#include <dns/question.h>
#include <dns/rrset.h>

namespace isc {
namespace dns {

///
/// \brief A standard DNS module exception that is thrown if a wire format
/// message parser encounters a short length of data that don't even contain
/// the full header section.
///
class MessageTooShort : public Exception {
public:
    MessageTooShort(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if a section iterator
/// is being constructed for an incompatible section.  Specifically, this
/// happens RRset iterator is being constructed for a Question section.
///
class InvalidMessageSection : public Exception {
public:
    InvalidMessageSection(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if a \c Message
/// class method is called that is prohibited for the current mode of
/// the message.
///
class InvalidMessageOperation : public Exception {
public:
    InvalidMessageOperation(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if a UDP buffer size
/// smaller than the standard default maximum (DEFAULT_MAX_UDPSIZE) is
/// being specified for the message.
///
class InvalidMessageUDPSize : public Exception {
public:
    InvalidMessageUDPSize(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

typedef uint16_t qid_t;

class InputBuffer;
class MessageRenderer;
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
class SectionIterator : public std::iterator<std::input_iterator_tag, T> {
public:
    SectionIterator<T>() : impl_(NULL) {}
    SectionIterator<T>(const SectionIteratorImpl<T>& impl);
    ~SectionIterator<T>();
    SectionIterator<T>(const SectionIterator<T>& source);
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
/// - may want to provide a "find" method for a specified type
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
    /// Since these are enum constants, however, invalid value could be passed
    /// via casting without an error at compilation time.
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
    /// bit is the most significant bit of the 2nd 16 bits of the header.
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
        HEADERFLAG_AD = 0x0020, ///< DNSSEC checking disabled (RFC4035)
        HEADERFLAG_CD = 0x0010  ///< Authentic %data (RFC4035)
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
    ~Message();
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
    /// This interface takes into account the RRSIG possibly attached to
    /// \c rrset.  This interface design needs to be revisited later.
    ///
    /// This method is only allowed in the \c RENDER mode;
    /// if the \c Message is in other mode, an exception of class
    /// InvalidMessageOperation will be thrown.
    /// \c section must be a valid constant of the \c Section type;
    /// otherwise, an exception of class \c OutOfRange will be thrown.
    ///
    /// Note that \c addRRset() does not currently check for duplicate
    /// data before inserting RRsets.  The caller is responsible for
    /// checking for these (see \c hasRRset() below).
    void addRRset(const Section section, RRsetPtr rrset, bool sign = false);

    /// \brief Determine whether the given section already has an RRset
    /// matching the given name, RR class and RR type.
    ///
    /// \c section must be a valid constant of the \c Section type;
    /// otherwise, an exception of class \c OutOfRange will be thrown.
    ///
    /// This should probably be extended to be a "find" method that returns
    /// a matching RRset if found.
    bool hasRRset(const Section section, const Name& name,
                  const RRClass& rrclass, const RRType& rrtype);

    // The following methods are not currently implemented.
    //void removeQuestion(QuestionPtr question);
    //void removeRRset(const Section section, RRsetPtr rrset);
    // notyet:
    //void addRR(const Section section, const RR& rr);
    //void removeRR(const Section section, const RR& rr);

    /// \brief Clear the message content (if any) and reinitialize it in the
    /// specified mode.
    void clear(Mode mode);

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

    /// \brief Render the message in wire formant into a \c MessageRenderer
    /// object.
    ///
    /// This \c Message must be in the \c RENDER mode and both \c Opcode and
    /// \c Rcode must have been set beforehand; otherwise, an exception of
    /// class \c InvalidMessageOperation will be thrown.
    void toWire(MessageRenderer& renderer);

    /// \brief Parse the header section of the \c Message.
    void parseHeader(InputBuffer& buffer);

    /// \brief Parse the \c Message.
    void fromWire(InputBuffer& buffer);

    ///
    /// \name Protocol constants
    ///
    //@{
    /// \brief The default maximum size of UDP DNS messages that don't cause
    /// truncation.
    ///
    /// With EDNS the maximum size can be increased per message.
    static const uint16_t DEFAULT_MAX_UDPSIZE = 512;
    //@}

private:
    MessageImpl* impl_;
};

/// \brief Pointer-like type pointing to a \c Message
///
/// This type is expected to be used as an argument in asynchronous
/// callback functions.  The internal reference-counting will ensure that
/// that ongoing state information will not be lost if the object
/// that originated the asynchronous call falls out of scope.
typedef boost::shared_ptr<Message> MessagePtr;

std::ostream& operator<<(std::ostream& os, const Opcode& opcode);
std::ostream& operator<<(std::ostream& os, const Rcode& rcode);
std::ostream& operator<<(std::ostream& os, const Message& message);
}
}
#endif  // __MESSAGE_H

// Local Variables: 
// mode: c++
// End: 
