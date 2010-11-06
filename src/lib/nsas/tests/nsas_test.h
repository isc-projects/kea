// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __NSAS_TEST_H
#define __NSAS_TEST_H

/// \file test_utilities.h
///
/// Contains miscellaneous classes and other stuff to help with the nameserver
/// address store tests.

#include <string>

#include <config.h>

#include <dns/buffer.h>
#include <dns/rdata.h>
#include <dns/rrtype.h>
#include <dns/messagerenderer.h>
#include "../nsas_entry.h"

using namespace isc::dns::rdata;
using namespace isc::dns;

namespace isc {
namespace dns {

/// \brief Class Types
///
/// Very simple classes to provide a type for the RdataTest class below.
/// All they do is return the type code associated with the record type.

class A {
public:
    uint16_t getType() const
    {return RRType::A().getCode();}
};

class AAAA {
public:
    uint16_t getType() const
    {return RRType::AAAA().getCode();}
};

class NS {
public:
    uint16_t getType() const
    {return RRType::NS().getCode();}
};

class MX {
public:
    uint16_t getType() const
    {return RRType::MX().getCode();}
};

/// \brief Hold Rdata
///
/// A concrete implementation of the Rdata class, this holds data for the
/// tests.  All RRs in the tests are either A, AAAA, NS or MX records, and
/// as a result the text form of the Rdata is a single uninterpreted string.
/// For this reason, a single class definition

template <typename T>
class RdataTest: public Rdata {
public:

    /// \brief Constructor
    ///
    /// Set the data in the object.
    ///
    /// \param v4address IPV4 address to store.  (The format of this address is
    /// not checked.)
    RdataTest(const std::string& data) : data_(data)
    {}

    /// \brief Convert Rdata to string
    ///
    /// This is the convenient interface to extract the information stored
    /// in this object into a form that can be used by the tests.
    virtual std::string toText() const {
        return (data_);
    }

    /// \brief Return type of Rdata
    ///
    /// Returns the type of the data.  May be useful in the tests, although this
    /// will not appear in the main code as this interface is not defined.
    virtual uint16_t getType() const {
        return (type_.getType());
    }

    /// \name Unused Methods
    ///
    /// These methods are not used in the tests.
    ///
    //@{
    /// \brief Render the \c Rdata in the wire format to a buffer
    virtual void toWire(OutputBuffer& buffer) const;

    /// \brief render the \Rdata in the wire format to a \c MessageRenderer
    virtual void toWire(MessageRenderer& renderer) const;
    
    /// \brief Comparison Method
    virtual int compare(const Rdata& other) const;
    //@}

private:
    std::string data_;          ///< Rdata itself
    T           type_;          ///< Identifies type of the Rdata
};

template <typename T>
void RdataTest<T>::toWire(OutputBuffer& buffer UNUSED_PARAM) const {
}

template <typename T>
void RdataTest<T>::toWire(MessageRenderer& buffer UNUSED_PARAM) const {
}

template <typename T>
int RdataTest<T>::compare(const Rdata& other UNUSED_PARAM) const {
    return 0;
}

} // namespace dns
} // namespace isc

namespace isc {
namespace nsas {

/// \brief Test Entry Class
///
/// This is an element that can be stored in both the hash table and the
/// LRU list.

class TestEntry : public NsasEntry<TestEntry> {
public:

    /// \brief Constructor
    ///
    /// \param name Name that will be used for the object.  This will form
    /// part of the key.
    /// \param class_code Class associated with the object.
    TestEntry(std::string name, uint16_t class_code) :
        name_(name), class_code_(class_code)
    {}

    /// \brief Virtual Destructor
    virtual ~TestEntry()
        {}

    /// \brief Return Hash Key
    ///
    /// This must be overridden in all classes derived from NsasEntry, and
    /// returns the hash key corresponding to the name and class.
    virtual HashKey hashKey() const {
        return HashKey(name_, class_code_);
    }

    /// \brief Get the Name
    ///
    /// \return Name given to this object
    virtual std::string getName() const {
        return name_;
    }

    /// \brief Set the Name
    ///
    /// \param name New name of the object
    virtual void setName(const std::string& name) {
        name_ = name;
    }

    /// \brief Get the Class
    ///
    /// \return Class code assigned to this object
    virtual uint16_t getClass() const {
        return class_code_;
    }

    /// \brief Set the Class
    ///
    /// \param class_code New class code of the object
    virtual void setClass(uint16_t class_code) {
        class_code_ = class_code;
    }

private:
    std::string name_;          ///< Name of the object
    uint16_t    class_code_;    ///< Class of the object
};

/// \brief isc::nsas Constants
///
/// Some constants used in the various tests.

static const uint32_t HASHTABLE_DEFAULT_SIZE = 1009; ///< First prime above 1000

} // namespace nsas
} // namespace isc

#endif // __NSAS_TEST_H
