// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <gtest/gtest.h>

#include <dns/name.h>
#include <dns/rrttl.h>
#include <exceptions/exceptions.h>

#include <datasrc/database.h>
#include <datasrc/data_source.h>
#include <datasrc/iterator.h>

using namespace isc::datasrc;
using namespace std;
using namespace boost;
using namespace isc::dns;

namespace {

/*
 * A connection with minimum implementation, keeping the original
 * "NotImplemented" methods.
 */
class NopAbstraction : public DatabaseAbstraction {
public:
    virtual std::pair<bool, int> getZone(const Name& name) const {
        if (name == Name("example.org")) {
            return (std::pair<bool, int>(true, 42));
        } else if (name == Name("null.example.org")) {
            return (std::pair<bool, int>(true, 13));
        } else if (name == Name("empty.example.org")) {
            return (std::pair<bool, int>(true, 0));
        } else if (name == Name("bad.example.org")) {
            return (std::pair<bool, int>(true, -1));
        } else {
            return (std::pair<bool, int>(false, 0));
        }
    }
};

/*
 * A virtual database connection that pretends it contains single zone --
 * example.org.
 *
 * It has the same getZone method as NopConnection, but it provides
 * implementation of the optional functionality.
 */
class MockAbstraction : public NopAbstraction {
private:
    class MockIteratorContext : public IteratorContext {
    private:
        int step;
    public:
        MockIteratorContext() :
            step(0)
        { }
        virtual bool getNext(string data[4]) {
            switch (step ++) {
                case 0:
                    data[0] = "example.org";
                    data[1] = "SOA";
                    data[2] = "300";
                    data[3] = "ns1.example.org. admin.example.org. "
                        "1234 3600 1800 2419200 7200";
                    return (true);
                case 1:
                    data[0] = "x.example.org";
                    data[1] = "A";
                    data[2] = "300";
                    data[3] = "192.0.2.1";
                    return (true);
                case 2:
                    data[0] = "x.example.org";
                    data[1] = "A";
                    data[2] = "300";
                    data[3] = "192.0.2.2";
                    return (true);
                case 3:
                    data[0] = "x.example.org";
                    data[1] = "AAAA";
                    data[2] = "300";
                    data[3] = "2001:db8::1";
                    return (true);
                case 4:
                    data[0] = "x.example.org";
                    data[1] = "AAAA";
                    data[2] = "300";
                    data[3] = "2001:db8::2";
                    return (true);
                default:
                    ADD_FAILURE() <<
                        "Request past the end of iterator context";
                case 5:
                    return (false);
            }
        }
    };
    class EmptyIteratorContext : public IteratorContext {
    public:
        virtual bool getNext(string[4]) {
            return (false);
        }
    };
    class BadIteratorContext : public IteratorContext {
    private:
        int step;
    public:
        BadIteratorContext() :
            step(0)
        { }
        virtual bool getNext(string data[4]) {
            switch (step ++) {
                case 0:
                    data[0] = "x.example.org";
                    data[1] = "A";
                    data[2] = "300";
                    data[3] = "192.0.2.1";
                    return (true);
                case 1:
                    data[0] = "x.example.org";
                    data[1] = "A";
                    data[2] = "301";
                    data[3] = "192.0.2.2";
                    return (true);
                default:
                    ADD_FAILURE() <<
                        "Request past the end of iterator context";
                case 2:
                    return (false);
            }
        }
    };
public:
    virtual IteratorContextPtr getIteratorContext(const Name&, int id) const {
        if (id == 42) {
            return (IteratorContextPtr(new MockIteratorContext()));
        } else if (id == 13) {
            return (IteratorContextPtr());
        } else if (id == 0) {
            return (IteratorContextPtr(new EmptyIteratorContext()));
        } else if (id == -1) {
            return (IteratorContextPtr(new BadIteratorContext()));
        } else {
            isc_throw(isc::Unexpected, "Unknown zone ID");
        }
    }
};

// This tests the default getIteratorContext behaviour, throwing NotImplemented
TEST(DatabaseConnectionTest, getIteratorContext) {
    // The parameters don't matter
    EXPECT_THROW(NopAbstraction().getIteratorContext(Name("."), 1),
                 isc::NotImplemented);
}

class DatabaseClientTest : public ::testing::Test {
public:
    DatabaseClientTest() {
        createClient();
    }
    /*
     * We initialize the client from a function, so we can call it multiple
     * times per test.
     */
    void createClient() {
        current_database_ = new MockAbstraction();
        client_.reset(new DatabaseClient(shared_ptr<DatabaseAbstraction>(
             current_database_)));
    }
    // Will be deleted by client_, just keep the current value for comparison.
    MockAbstraction* current_database_;
    shared_ptr<DatabaseClient> client_;
    /**
     * Check the zone finder is a valid one and references the zone ID and
     * database available here.
     */
    void checkZoneFinder(const DataSourceClient::FindResult& zone) {
        ASSERT_NE(ZoneFinderPtr(), zone.zone_finder) << "No zone finder";
        shared_ptr<DatabaseClient::Finder> finder(
            dynamic_pointer_cast<DatabaseClient::Finder>(zone.zone_finder));
        ASSERT_NE(shared_ptr<DatabaseClient::Finder>(), finder) <<
            "Wrong type of finder";
        EXPECT_EQ(42, finder->zone_id());
        EXPECT_EQ(current_database_, &finder->database());
    }
};

TEST_F(DatabaseClientTest, zoneNotFound) {
    DataSourceClient::FindResult zone(client_->findZone(Name("example.com")));
    EXPECT_EQ(result::NOTFOUND, zone.code);
}

TEST_F(DatabaseClientTest, exactZone) {
    DataSourceClient::FindResult zone(client_->findZone(Name("example.org")));
    EXPECT_EQ(result::SUCCESS, zone.code);
    checkZoneFinder(zone);
}

TEST_F(DatabaseClientTest, superZone) {
    DataSourceClient::FindResult zone(client_->findZone(Name(
        "sub.example.org")));
    EXPECT_EQ(result::PARTIALMATCH, zone.code);
    checkZoneFinder(zone);
}

TEST_F(DatabaseClientTest, noConnException) {
    EXPECT_THROW(DatabaseClient(shared_ptr<DatabaseAbstraction>()),
                 isc::InvalidParameter);
}

// If the zone doesn't exist, exception is thrown
TEST_F(DatabaseClientTest, noZoneIterator) {
    EXPECT_THROW(client_->getIterator(Name("example.com")), DataSourceError);
}

// If the zone doesn't exist and iteration is not implemented, it still throws
// the exception it doesn't exist
TEST_F(DatabaseClientTest, noZoneNotImplementedIterator) {
    EXPECT_THROW(DatabaseClient(boost::shared_ptr<DatabaseAbstraction>(
        new NopAbstraction())).getIterator(Name("example.com")),
                 DataSourceError);
}

TEST_F(DatabaseClientTest, notImplementedIterator) {
    EXPECT_THROW(DatabaseClient(shared_ptr<DatabaseAbstraction>(
        new NopAbstraction())).getIterator(Name("example.org")),
                 isc::NotImplemented);
}

// Pretend a bug in the connection and pass NULL as the context
// Should not crash, but gracefully throw
TEST_F(DatabaseClientTest, nullIteratorContext) {
    EXPECT_THROW(client_->getIterator(Name("null.example.org")),
                 isc::Unexpected);
}

// It doesn't crash or anything if the zone is completely empty
TEST_F(DatabaseClientTest, emptyIterator) {
    ZoneIteratorPtr it(client_->getIterator(Name("empty.example.org")));
    EXPECT_EQ(ConstRRsetPtr(), it->getNextRRset());
    // This is past the end, it should throw
    EXPECT_THROW(it->getNextRRset(), isc::Unexpected);
}

// Iterate trough a zone
TEST_F(DatabaseClientTest, iterator) {
    ZoneIteratorPtr it(client_->getIterator(Name("example.org")));
    ConstRRsetPtr rrset(it->getNextRRset());
    ASSERT_NE(ConstRRsetPtr(), rrset);
    EXPECT_EQ(Name("example.org"), rrset->getName());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
    EXPECT_EQ(RRType::SOA(), rrset->getType());
    EXPECT_EQ(RRTTL(300), rrset->getTTL());
    RdataIteratorPtr rit(rrset->getRdataIterator());
    ASSERT_FALSE(rit->isLast());
    rit->next();
    EXPECT_TRUE(rit->isLast());

    rrset = it->getNextRRset();
    ASSERT_NE(ConstRRsetPtr(), rrset);
    EXPECT_EQ(Name("x.example.org"), rrset->getName());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRTTL(300), rrset->getTTL());
    rit = rrset->getRdataIterator();
    ASSERT_FALSE(rit->isLast());
    EXPECT_EQ("192.0.2.1", rit->getCurrent().toText());
    rit->next();
    ASSERT_FALSE(rit->isLast());
    EXPECT_EQ("192.0.2.2", rit->getCurrent().toText());
    rit->next();
    EXPECT_TRUE(rit->isLast());

    rrset = it->getNextRRset();
    ASSERT_NE(ConstRRsetPtr(), rrset);
    EXPECT_EQ(Name("x.example.org"), rrset->getName());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
    EXPECT_EQ(RRType::AAAA(), rrset->getType());
    EXPECT_EQ(RRTTL(300), rrset->getTTL());
    EXPECT_EQ(ConstRRsetPtr(), it->getNextRRset());
    rit = rrset->getRdataIterator();
    ASSERT_FALSE(rit->isLast());
    EXPECT_EQ("2001:db8::1", rit->getCurrent().toText());
    rit->next();
    ASSERT_FALSE(rit->isLast());
    EXPECT_EQ("2001:db8::2", rit->getCurrent().toText());
    rit->next();
    EXPECT_TRUE(rit->isLast());
}

// This has inconsistent TTL in the set (the rest, like nonsense in
// the data is handled in rdata itself).
TEST_F(DatabaseClientTest, badIterator) {
    ZoneIteratorPtr it(client_->getIterator(Name("bad.example.org")));
    EXPECT_THROW(it->getNextRRset(), DataSourceError);
}

}
