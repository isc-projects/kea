// Copyright (C) 2012, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <dns/rrset_collection.h>
#include <dns/rrttl.h>
#include <dns/rdataclass.h>

#include <gtest/gtest.h>

#include <list>
#include <fstream>

using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace std;

namespace {

class RRsetCollectionTest : public ::testing::Test {
public:
    RRsetCollectionTest() :
        rrclass("IN"),
        origin("example.org"),
        collection(TEST_DATA_SRCDIR "/example.org", origin, rrclass)
    {}

    const RRClass rrclass;
    const Name origin;
    RRsetCollection collection;
};

TEST_F(RRsetCollectionTest, istreamConstructor) {
    std::ifstream fs(TEST_DATA_SRCDIR "/example.org");
    RRsetCollection collection2(fs, origin, rrclass);

    RRsetCollectionBase::Iterator iter = collection.begin();
    RRsetCollectionBase::Iterator iter2 = collection2.begin();
    while (iter != collection.end()) {
         ASSERT_TRUE(iter2 != collection2.end());
         EXPECT_EQ((*iter).toText(), (*iter2).toText());
         ++iter;
         ++iter2;
    }
    ASSERT_TRUE(iter2 == collection2.end());
}

template <typename T, typename TP>
void doFind(T& collection, const RRClass& rrclass) {
    // Test the find() that returns ConstRRsetPtr
    TP rrset = collection.find(Name("www.example.org"), rrclass, RRType::A());
    EXPECT_TRUE(rrset);
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRTTL(3600), rrset->getTTL());
    EXPECT_EQ(RRClass("IN"), rrset->getClass());
    EXPECT_EQ(Name("www.example.org"), rrset->getName());

    // foo.example.org doesn't exist
    rrset = collection.find(Name("foo.example.org"), rrclass, RRType::A());
    EXPECT_FALSE(rrset);

    // www.example.org exists, but not with MX
    rrset = collection.find(Name("www.example.org"), rrclass, RRType::MX());
    EXPECT_FALSE(rrset);

    // www.example.org exists, with AAAA
    rrset = collection.find(Name("www.example.org"), rrclass, RRType::AAAA());
    EXPECT_TRUE(rrset);

    // www.example.org with AAAA does not exist in RRClass::CH()
    rrset = collection.find(Name("www.example.org"), RRClass::CH(),
                            RRType::AAAA());
    EXPECT_FALSE(rrset);
}

TEST_F(RRsetCollectionTest, findConst) {
    // Test the find() that returns ConstRRsetPtr
    const RRsetCollection& ccln = collection;
    doFind<const RRsetCollection, ConstRRsetPtr>(ccln, rrclass);
}

TEST_F(RRsetCollectionTest, find) {
    // Test the find() that returns RRsetPtr
    doFind<RRsetCollection, RRsetPtr>(collection, rrclass);
}

void
doAddAndRemove(RRsetCollection& collection, const RRClass& rrclass) {
    // foo.example.org/A doesn't exist
    RRsetPtr rrset_found = collection.find(Name("foo.example.org"), rrclass,
                                           RRType::A());
    EXPECT_FALSE(rrset_found);

    // Add foo.example.org/A
    RRsetPtr rrset(new BasicRRset(Name("foo.example.org"), rrclass, RRType::A(),
                                  RRTTL(7200)));
    rrset->addRdata(in::A("192.0.2.1"));
    collection.addRRset(rrset);

    // foo.example.org/A should now exist
    rrset_found = collection.find(Name("foo.example.org"), rrclass,
                                  RRType::A());
    EXPECT_TRUE(rrset_found);
    EXPECT_EQ(RRType::A(), rrset_found->getType());
    EXPECT_EQ(RRTTL(7200), rrset_found->getTTL());
    EXPECT_EQ(RRClass("IN"), rrset_found->getClass());
    EXPECT_EQ(Name("foo.example.org"), rrset_found->getName());

    // The collection must not be empty.
    EXPECT_TRUE(collection.end() != collection.begin());

    // Adding a duplicate RRset must throw.
    EXPECT_THROW({
        collection.addRRset(rrset);
    }, isc::InvalidParameter);

    // Remove foo.example.org/A, which should pass
    EXPECT_TRUE(collection.removeRRset(Name("foo.example.org"),
                                       rrclass, RRType::A()));
    // foo.example.org/A should not exist now
    rrset_found = collection.find(Name("foo.example.org"), rrclass,
                                  RRType::A());
    EXPECT_FALSE(rrset_found);

    // Removing foo.example.org/A should fail now
    EXPECT_FALSE(collection.removeRRset(Name("foo.example.org"),
                                        rrclass, RRType::A()));
}

TEST_F(RRsetCollectionTest, addAndRemove) {
    doAddAndRemove(collection, rrclass);
}

TEST_F(RRsetCollectionTest, empty) {
    RRsetCollection cln;

    // Here, cln is empty.
    EXPECT_TRUE(cln.end() == cln.begin());

    doAddAndRemove(cln, rrclass);

    // cln should be empty again here, after the add and remove
    // operations.
    EXPECT_TRUE(cln.end() == cln.begin());
}

TEST_F(RRsetCollectionTest, iteratorTest) {
    // The collection must not be empty.
    EXPECT_TRUE(collection.end() != collection.begin());

    // Here, we just count the records and do some basic tests on them.
    size_t count = 0;
    for (RRsetCollection::Iterator it = collection.begin();
         it != collection.end(); ++it) {
         ++count;
         const AbstractRRset& rrset = *it;
         EXPECT_EQ(rrclass, rrset.getClass());
         EXPECT_EQ(RRTTL(3600), rrset.getTTL());
    }

    // example.org master file has SOA, NS, A, AAAA
    EXPECT_EQ(4, count);
}

// This is a dummy class which is used in iteratorCompareDifferent test
// to compare iterators from different RRsetCollectionBase
// implementations.
class MyRRsetCollection : public RRsetCollectionBase {
public:
    MyRRsetCollection()
    {}

    virtual isc::dns::ConstRRsetPtr find(const isc::dns::Name&,
                                         const isc::dns::RRClass&,
                                         const isc::dns::RRType&) const {
        return (ConstRRsetPtr());
    }

    typedef std::list<isc::dns::RRset> MyCollection;

protected:
    class MyIter : public RRsetCollectionBase::Iter {
    public:
        explicit MyIter(MyCollection::iterator& iter) :
            iter_(iter)
        {}

        virtual const isc::dns::AbstractRRset& getValue() {
            return (*iter_);
        }

        virtual IterPtr getNext() {
            MyCollection::iterator it = iter_;
            ++it;
            return (RRsetCollectionBase::IterPtr(new MyIter(it)));
        }

        virtual bool equals(Iter& other) {
            const MyIter* other_real = dynamic_cast<MyIter*>(&other);
            if (other_real == NULL) {
                return (false);
            }
            return (iter_ == other_real->iter_);
        }

    private:
        MyCollection::iterator iter_;
    };

    virtual RRsetCollectionBase::IterPtr getBeginning() {
        MyCollection::iterator it = dummy_list_.begin();
        return (RRsetCollectionBase::IterPtr(new MyIter(it)));
    }

    virtual RRsetCollectionBase::IterPtr getEnd() {
        MyCollection::iterator it = dummy_list_.end();
        return (RRsetCollectionBase::IterPtr(new MyIter(it)));
    }

private:
    MyCollection dummy_list_;
};

TEST_F(RRsetCollectionTest, iteratorCompareDifferent) {
    // Create objects of two different RRsetCollectionBase
    // implementations.
    RRsetCollection cln1;
    MyRRsetCollection cln2;

    // Comparing two iterators from different RRsetCollectionBase
    // implementations must not throw.
    EXPECT_TRUE(cln2.begin() != cln1.begin());
    EXPECT_TRUE(cln1.end() != cln2.end());
}

} // namespace
