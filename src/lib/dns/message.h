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

#include <iterator>
#include <string>

#include <exceptions/exceptions.h>
#include "question.h"
#include "rrset.h"

namespace isc {
namespace dns {

///
/// \brief A standard DNS module exception ...[TBD]
///
class MessageTooShort : public Exception {
public:
    MessageTooShort(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

class InvalidMessageSection : public Exception {
public:
    InvalidMessageSection(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

class InvalidMessageOperation : public Exception {
public:
    InvalidMessageOperation(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

class InvalidMessageUDPSize : public Exception {
public:
    InvalidMessageUDPSize(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

typedef uint8_t rcode_t; // we actually only need 4 bits of it
typedef uint8_t opcode_t; // we actually only need 4 bits of it
typedef uint16_t qid_t;

class InputBuffer;
class MessageRenderer;
class Message;
struct MessageImpl;

template <typename T>
struct SectionIteratorImpl;

class MessageFlag {
public:
    uint16_t getBit() const { return (flagbit_); }
    static const MessageFlag& QR();
    static const MessageFlag& AA();
    static const MessageFlag& TC();
    static const MessageFlag& RD();
    static const MessageFlag& RA();
    static const MessageFlag& AD();
    static const MessageFlag& CD();
private:
    MessageFlag(uint16_t flagbit) : flagbit_(flagbit) {}
    uint16_t flagbit_;
};

inline const MessageFlag&
MessageFlag::QR()
{
    static MessageFlag f(0x8000);
    return (f);
}

inline const MessageFlag&
MessageFlag::AA()
{
    static MessageFlag f(0x0400);
    return (f);
}

inline const MessageFlag&
MessageFlag::TC()
{
    static MessageFlag f(0x0200);
    return (f);
}

inline const MessageFlag&
MessageFlag::RD()
{
    static MessageFlag f(0x0100);
    return (f);
}

inline const MessageFlag&
MessageFlag::RA()
{
    static MessageFlag f(0x0080);
    return (f);
}

inline const MessageFlag&
MessageFlag::AD()
{
    static MessageFlag f(0x0020);
    return (f);
}

inline const MessageFlag&
MessageFlag::CD()
{
    static MessageFlag f(0x0010);
    return (f);
}

class Opcode {
public:
    uint16_t getCode() const { return (code_); }
    bool operator==(const Opcode& other) const
    { return (code_ == other.code_); }
    bool operator!=(const Opcode& other) const
    { return (code_ != other.code_); }
    std::string toText() const;
    static const Opcode& QUERY();
    static const Opcode& IQUERY();
    static const Opcode& STATUS();
    static const Opcode& RESERVED3();
    static const Opcode& NOTIFY();
    static const Opcode& UPDATE();
    static const Opcode& RESERVED6();
    static const Opcode& RESERVED7();
    static const Opcode& RESERVED8();
    static const Opcode& RESERVED9();
    static const Opcode& RESERVED10();
    static const Opcode& RESERVED11();
    static const Opcode& RESERVED12();
    static const Opcode& RESERVED13();
    static const Opcode& RESERVED14();
    static const Opcode& RESERVED15();
private:
    Opcode(uint16_t code) : code_(code) {}
    uint16_t code_;
};

inline const Opcode&
Opcode::QUERY()
{
    static Opcode c(0);
    return (c);
}

inline const Opcode&
Opcode::IQUERY()
{
    static Opcode c(1);
    return (c);
}

inline const Opcode&
Opcode::STATUS()
{
    static Opcode c(2);
    return (c);
}

inline const Opcode&
Opcode::RESERVED3()
{
    static Opcode c(3);
    return (c);
}

inline const Opcode&
Opcode::NOTIFY()
{
    static Opcode c(4);
    return (c);
}

inline const Opcode&
Opcode::UPDATE()
{
    static Opcode c(5);
    return (c);
}

inline const Opcode&
Opcode::RESERVED6()
{
    static Opcode c(6);
    return (c);
}

inline const Opcode&
Opcode::RESERVED7()
{
    static Opcode c(7);
    return (c);
}

inline const Opcode&
Opcode::RESERVED8()
{
    static Opcode c(8);
    return (c);
}

inline const Opcode&
Opcode::RESERVED9()
{
    static Opcode c(9);
    return (c);
}

inline const Opcode&
Opcode::RESERVED10()
{
    static Opcode c(10);
    return (c);
}

inline const Opcode&
Opcode::RESERVED11()
{
    static Opcode c(11);
    return (c);
}

inline const Opcode&
Opcode::RESERVED12()
{
    static Opcode c(12);
    return (c);
}

inline const Opcode&
Opcode::RESERVED13()
{
    static Opcode c(13);
    return (c);
}

inline const Opcode&
Opcode::RESERVED14()
{
    static Opcode c(14);
    return (c);
}

inline const Opcode&
Opcode::RESERVED15()
{
    static Opcode c(15);
    return (c);
}

class Rcode {
public:
    Rcode(uint16_t code);
    uint16_t getCode() const { return (code_); }
    bool operator==(const Rcode& other) const { return (code_ == other.code_); }
    std::string toText() const;
    static const Rcode& NOERROR();
    static const Rcode& FORMERR();
    static const Rcode& SERVFAIL();
    static const Rcode& NXDOMAIN();
    static const Rcode& NOTIMP();
    static const Rcode& REFUSED();
    static const Rcode& YXDOMAIN();
    static const Rcode& YXRRSET();
    static const Rcode& NXRRSET();
    static const Rcode& NOTAUTH();
    static const Rcode& NOTZONE();
    static const Rcode& RESERVED11();
    static const Rcode& RESERVED12();
    static const Rcode& RESERVED13();
    static const Rcode& RESERVED14();
    static const Rcode& RESERVED15();
    // Extended Rcodes follow (EDNS required)
    static const Rcode& BADVERS();
private:
    uint16_t code_;

    // EDNS-extended RCODEs are 12-bit unsigned integers.
    static const uint16_t MAX_RCODE = 0xfff;
};

inline const Rcode&
Rcode::NOERROR()
{
    static Rcode c(0);
    return (c);
}

inline const Rcode&
Rcode::FORMERR()
{
    static Rcode c(1);
    return (c);
}

inline const Rcode&
Rcode::SERVFAIL()
{
    static Rcode c(2);
    return (c);
}

inline const Rcode&
Rcode::NXDOMAIN()
{
    static Rcode c(3);
    return (c);
}

inline const Rcode&
Rcode::NOTIMP()
{
    static Rcode c(4);
    return (c);
}

inline const Rcode&
Rcode::REFUSED()
{
    static Rcode c(5);
    return (c);
}

inline const Rcode&
Rcode::YXDOMAIN()
{
    static Rcode c(6);
    return (c);
}

inline const Rcode&
Rcode::YXRRSET()
{
    static Rcode c(7);
    return (c);
}

inline const Rcode&
Rcode::NXRRSET()
{
    static Rcode c(8);
    return (c);
}

inline const Rcode&
Rcode::NOTAUTH()
{
    static Rcode c(9);
    return (c);
}

inline const Rcode&
Rcode::NOTZONE()
{
    static Rcode c(10);
    return (c);
}

inline const Rcode&
Rcode::RESERVED11()
{
    static Rcode c(11);
    return (c);
}

inline const Rcode&
Rcode::RESERVED12()
{
    static Rcode c(12);
    return (c);
}

inline const Rcode&
Rcode::RESERVED13()
{
    static Rcode c(13);
    return (c);
}

inline const Rcode&
Rcode::RESERVED14()
{
    static Rcode c(14);
    return (c);
}

inline const Rcode&
Rcode::RESERVED15()
{
    static Rcode c(15);
    return (c);
}

inline const Rcode&
Rcode::BADVERS()
{
    static Rcode c(16);
    return (c);
}

class Section {
public:
    /// \brief Returns the relative position of the \c Section in DNS messages.
    unsigned int getCode() const { return (code_); }
    bool operator==(const Section& other) const
        { return (code_ == other.code_); }
    bool operator!=(const Section& other) const
        { return (code_ != other.code_); }

    static const Section& QUESTION();
    static const Section& ANSWER();
    static const Section& AUTHORITY();
    static const Section& ADDITIONAL();
private:
    enum {
        SECTION_QUESTION = 0,
        SECTION_ANSWER = 1,
        SECTION_AUTHORITY = 2,
        SECTION_ADDITIONAL = 3
    };

    Section(int code) : code_(code) {}
    unsigned int code_;
};

inline const Section&
Section::QUESTION()
{
    static Section s(SECTION_QUESTION);
    return (s);
}

inline const Section&
Section::ANSWER()
{
    static Section s(SECTION_ANSWER);
    return (s);
}

inline const Section&
Section::AUTHORITY()
{
    static Section s(SECTION_AUTHORITY);
    return (s);
}

inline const Section&
Section::ADDITIONAL()
{
    static Section s(SECTION_ADDITIONAL);
    return (s);
}

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

class Message {
public:
    enum Mode {
        PARSE = 0,
        RENDER = 1
    };
public:
    Message(Mode mode);
    ~Message();
private:
    Message(const Message& source);
    Message& operator=(const Message& source);
public:
    bool getHeaderFlag(const MessageFlag& flag) const;
    void setHeaderFlag(const MessageFlag& flag);
    void clearHeaderFlag(const MessageFlag& flag);
    bool isDNSSECSupported() const;
    void setDNSSECSupported(bool on);
    uint16_t getUDPSize() const;
    void setUDPSize(uint16_t size);
    qid_t getQid() const;
    void setQid(qid_t qid);
    const Rcode& getRcode() const;
    void setRcode(const Rcode& rcode);
    const Opcode& getOpcode() const;
    void setOpcode(const Opcode& opcode);
    std::string toText() const;
    /// \brief Returns the number of RRs contained in the given section.
    unsigned int getRRCount(const Section& section) const;

    // we don't provide accessors to QD/AN/NS/AR counters as this information
    // is included in the corresponding RRsets.
    // Open issues:
    //   - may want to provide an "iterator" for all RRsets/RRs
    //   - may want to provide a "find" method for a specified type
    //     of RR in the message
    const QuestionIterator beginQuestion() const;
    const QuestionIterator endQuestion() const;
    const RRsetIterator beginSection(const Section& section) const;
    const RRsetIterator endSection(const Section& section) const;

    void addQuestion(QuestionPtr question);
    void addQuestion(const Question& question);
    void removeQuestion(QuestionPtr question);
    void addRRset(const Section& section, RRsetPtr rrset, bool sign = false);
    void removeRRset(const Section& section, RRsetPtr rrset);
    // notyet:
    //void addRR(const Section& section, const RR& rr);
    //void removeRR(const Section& section, const RR& rr);

    void clear(Mode mode);

    // prepare for making a response from a request.  This will clear the
    // DNS header except those fields that should be kept for the response,
    // and clear answer and the following sections.
    // see also dns_message_reply() of BIND9.
    void makeResponse();

    /// \brief Render message.
    void toWire(MessageRenderer& renderer);

    /// \brief Parse a DNS message.
    void fromWire(InputBuffer& buffer);

    ///
    /// \name Protocol constants
    ///
    //@{
    /// \brief The default maximum size of UDP DNS messages that don't cause
    /// truncation.
    ///
    /// With EDNS the maximum size can be increases per message.
    static const uint16_t DEFAULT_MAX_UDPSIZE = 512;

    /// \brief The highest EDNS version this implementation supports.
    static const uint8_t EDNS_SUPPORTED_VERSION = 0;
    //@}

private:
    MessageImpl* impl_;
};

std::ostream& operator<<(std::ostream& os, const Opcode& opcode);
std::ostream& operator<<(std::ostream& os, const Rcode& rcode);
std::ostream& operator<<(std::ostream& os, const Message& message);
}
}
#endif  // __MESSAGE_H

// Local Variables: 
// mode: c++
// End: 
