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

/// \file nsas_test.h
///
/// Contains miscellaneous classes and other stuff to help with the nameserver
/// address store tests.

#include <string>
#include <vector>

#include <config.h>

#include <dns/buffer.h>
#include <dns/rdata.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>
#include <dns/messagerenderer.h>
#include <dns/rdataclass.h>
#include "../nsas_entry.h"
#include "../resolver_interface.h"

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
    TestEntry(std::string name, const isc::dns::RRClass& class_code) :
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
    virtual const isc::dns::RRClass& getClass() const {
        return class_code_;
    }

    /// \brief Set the Class
    ///
    /// \param class_code New class code of the object
    virtual void setClass(const isc::dns::RRClass& class_code) {
        class_code_ = class_code;
    }

private:
    std::string name_;          ///< Name of the object
    isc::dns::RRClass    class_code_;    ///< Class of the object
};

/// \brief isc::nsas Constants
///
/// Some constants used in the various tests.

static const uint32_t HASHTABLE_DEFAULT_SIZE = 1009; ///< First prime above 1000

} // namespace nsas
} // namespace isc

namespace {

using namespace std;

/*
 * This pretends to be a resolver. It stores the queries and
 * they can be answered.
 */
class TestResolver : public isc::nsas::ResolverInterface {
    private:
        bool checkIndex(size_t index) {
            return (requests.size() > index);
        }

        typedef std::map<isc::dns::Question, boost::shared_ptr<AbstractRRset> >
            PresetAnswers;
        PresetAnswers answers_;
    public:
        typedef pair<QuestionPtr, CallbackPtr> Request;
        vector<Request> requests;
        virtual void resolve(QuestionPtr q, CallbackPtr c) {
            PresetAnswers::iterator it(answers_.find(*q));
            if (it == answers_.end()) {
                requests.push_back(Request(q, c));
            } else {
                if (it->second) {
                    c->success(it->second);
                } else {
                    c->failure();
                }
            }
        }

        /*
         * Add a preset answer. If shared_ptr() is passed (eg. NULL),
         * it will generate failure. If the question is not preset,
         * it goes to requests and you can answer later.
         */
        void addPresetAnswer(const isc::dns::Question& question,
            boost::shared_ptr<AbstractRRset> answer)
        {
            answers_[question] = answer;
        }

        // Thrown if the query at the given index does not exist.
        class NoSuchRequest : public std::exception { };

        // Thrown if the answer does not match the query
        class DifferentRequest : public std::exception { };

        QuestionPtr operator[](size_t index) {
            if (index >= requests.size()) {
                throw NoSuchRequest();
            }
            return (requests[index].first);
        }
        /*
         * Looks if the two provided requests in resolver are A and AAAA.
         * Sorts them so index1 is A.
         *
         * Returns false if there aren't enough elements
         */
        bool asksIPs(const Name& name, size_t index1, size_t index2) {
            size_t max = (index1 < index2) ? index2 : index1;
            if (!checkIndex(max)) {
                return false;
            }
            EXPECT_EQ(name, (*this)[index1]->getName());
            EXPECT_EQ(name, (*this)[index2]->getName());
            EXPECT_EQ(RRClass::IN(), (*this)[index1]->getClass());
            EXPECT_EQ(RRClass::IN(), (*this)[index2]->getClass());
            // If they are the other way around, swap
            if ((*this)[index1]->getType() == RRType::AAAA() &&
                (*this)[index2]->getType() == RRType::A())
            {
                TestResolver::Request tmp((*this).requests[index1]);
                (*this).requests[index1] =
                    (*this).requests[index2];
                (*this).requests[index2] = tmp;
            }
            // Check the correct addresses
            EXPECT_EQ(RRType::A(), (*this)[index1]->getType());
            EXPECT_EQ(RRType::AAAA(), (*this)[index2]->getType());
            return (true);
        }

        /*
         * Sends a simple answer to a query.
         * Provide index of a query and the address to pass.
         */
        void answer(size_t index, const Name& name, const RRType& type,
            const rdata::Rdata& rdata, size_t TTL = 100)
        {
            if (index >= requests.size()) {
                throw NoSuchRequest();
            }
            RRsetPtr set(new RRset(name, RRClass::IN(),
                type, RRTTL(TTL)));
            set->addRdata(rdata);
            requests[index].second->success(set);
        }

        void provideNS(size_t index,
            boost::shared_ptr<AbstractRRset> nameservers)
        {
            if (index >= requests.size()) {
                throw NoSuchRequest();
            }
            if (requests[index].first->getName() != nameservers->getName() ||
                requests[index].first->getType() != RRType::NS())
            {
                throw DifferentRequest();
            }
            requests[index].second->success(nameservers);
        }
};

// String constants.  These should end in a dot.
static const std::string EXAMPLE_CO_UK("example.co.uk.");
static const std::string EXAMPLE_NET("example.net.");
static const std::string MIXED_EXAMPLE_CO_UK("EXAmple.co.uk.");

class TestWithRdata : public ::testing::Test {
protected:
    typedef boost::shared_ptr<RRset> RRsetPtr;
    /// \brief Constructor
    ///
    /// Initializes the RRsets used in the tests.  The RRsets themselves have to
    /// be initialized with the basic data on their construction. The Rdata for
    /// them is added in SetUp().
    TestWithRdata() :
        rrv4_(new RRset(Name(EXAMPLE_CO_UK), RRClass::IN(), RRType::A(),
            RRTTL(1200))),
        rrcase_(new RRset(Name(MIXED_EXAMPLE_CO_UK), RRClass::IN(),
            RRType::A(), RRTTL(1200))),
        rrch_(new RRset(Name(EXAMPLE_CO_UK), RRClass::CH(), RRType::A(),
            RRTTL(1200))),
        rrns_(new RRset(Name(EXAMPLE_CO_UK), RRClass::IN(), RRType::NS(),
            RRTTL(1200))),
        rr_single_(new RRset(Name(EXAMPLE_CO_UK), RRClass::IN(),
            RRType::NS(), RRTTL(600))),
        rr_empty_(new RRset(Name(EXAMPLE_CO_UK), RRClass::IN(),
            RRType::NS(), RRTTL(600))),
        rrv6_(new RRset(Name(EXAMPLE_CO_UK), RRClass::IN(),
            RRType::AAAA(), RRTTL(900))),
        rrnet_(new RRset(Name(EXAMPLE_NET), RRClass::IN(), RRType::A(),
            RRTTL(600))),
        ns_name_("ns.example.net.")
    {}

    /// \brief Add Rdata to RRsets
    ///
    /// The data are added as const pointers to avoid the stricter type checking
    /// applied by the Rdata code.  There is no need for it in these tests.
    virtual void SetUp() {

        // A records
        rrv4_->addRdata(ConstRdataPtr(new RdataTest<A>("1.2.3.4")));
        rrv4_->addRdata(ConstRdataPtr(new RdataTest<A>("5.6.7.8")));
        rrv4_->addRdata(ConstRdataPtr(new RdataTest<A>("9.10.11.12")));

        // A records
        rrcase_->addRdata(ConstRdataPtr(new RdataTest<A>("13.14.15.16")));

        // No idea what Chaosnet address look like other than they are 16 bits
        // The fact that they are type A is probably also incorrect.
        rrch_->addRdata(ConstRdataPtr(new RdataTest<A>("1324")));

        // NS records take a single name
        rrns_->addRdata(rdata::generic::NS("example.fr"));
        rrns_->addRdata(rdata::generic::NS("example.de"));

        // Single NS record with 0 TTL
        rr_single_->addRdata(rdata::generic::NS( "ns.example.net."));

        // AAAA records
        rrv6_->addRdata(ConstRdataPtr(new RdataTest<AAAA>("2001::1002")));
        rrv6_->addRdata(ConstRdataPtr(new RdataTest<AAAA>("dead:beef:feed::")));

        // A record for example.net
        rrnet_->addRdata(ConstRdataPtr(new RdataTest<A>("17.18.18.20")));
    }

    /// \brief Data for the tests
    RRsetPtr rrv4_;           ///< Standard RRSet - IN, A, lowercase name
    RRsetPtr rrcase_;         ///< Mixed-case name
    RRsetPtr rrch_;           ///< Non-IN RRset (Chaos in this case)
    RRsetPtr rrns_;           ///< NS RRset
    RRsetPtr rr_single_;      ///< NS RRset with single NS
    RRsetPtr rr_empty_;       ///< NS RRset without any nameservers
    RRsetPtr rrv6_;           ///< Standard RRset, IN, AAAA, lowercase name
    RRsetPtr rrnet_;          ///< example.net A RRset
    Name ns_name_;  ///< Nameserver name of ns.example.net
};

} // Empty namespace

#endif // __NSAS_TEST_H
