// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <dns/master_loader_callbacks.h>
#include <dns/master_loader.h>
#include <dns/rrtype.h>
#include <dns/rrset.h>
#include <dns/rrclass.h>
#include <dns/name.h>

#include <gtest/gtest.h>
#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>

#include <string>
#include <vector>
#include <list>

using namespace isc::dns;
using std::vector;
using std::string;
using std::list;

class MasterLoaderTest : public ::testing::Test {
public:
    MasterLoaderTest() :
        callbacks_(boost::bind(&MasterLoaderTest::callback, this,
                               true, _1, _2, _3),
                   boost::bind(&MasterLoaderTest::callback, this,
                               false, _1, _2, _3))
    {}

    /// Concatenate file, line, and reason, and add it to either errors
    /// or warnings
    void callback(bool error, const std::string& file, size_t line,
                  const std::string reason)
    {
        std::stringstream ss;
        ss << file << line << reason;
        if (error) {
            errors_.push_back(ss.str());
        } else {
            warnings_.push_back(ss.str());
        }
    }

    void addRRset(const Name& name, const RRClass& rrclass,
                  const RRType& rrtype, const RRTTL& rrttl,
                  const rdata::RdataPtr& data) {
        const RRsetPtr rrset(new BasicRRset(name, rrclass, rrtype, rrttl));
        rrset->addRdata(data);
        rrsets_.push_back(rrset);
    }

    void setLoader(const char* file, const Name& origin, const RRClass rrclass,
                   const MasterLoader::Options options)
    {
        loader_.reset(new MasterLoader((string(TEST_DATA_SRCDIR "/") +
                                        file).c_str(), origin, rrclass,
                                       callbacks_,
                                       boost::bind(&MasterLoaderTest::addRRset,
                                                   this, _1, _2, _3, _4, _5),
                                       options));
    }

    // Check the next RR in the ones produced by the loader
    // Other than passed arguments are checked to be the default for the tests
    void checkRR(const string& name, const RRType& type, const string& data) {
        ASSERT_FALSE(rrsets_.empty());
        RRsetPtr current = rrsets_.front();
        rrsets_.pop_front();

        EXPECT_EQ(Name(name), current->getName());
        ASSERT_EQ(type, current->getType());
        ASSERT_EQ(1, current->getRdataCount());
        EXPECT_EQ(data, current->getRdataIterator()->getCurrent().toText());
    }

    MasterLoaderCallbacks callbacks_;
    boost::scoped_ptr<MasterLoader> loader_;
    vector<string> errors_;
    vector<string> warnings_;
    list<RRsetPtr> rrsets_;
};

// Test simple loading. The zone file contains no tricky things, and nothing is
// omitted. No RRset contains more than one RR Also no errors or warnings.
TEST_F(MasterLoaderTest, basicLoad) {
    setLoader("example.org",
              Name("example.org."),
              RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();

    EXPECT_TRUE(errors_.empty());
    EXPECT_TRUE(warnings_.empty());

    checkRR("example.org", RRType::SOA(), "ns1.example.org. admin.example.org. "
            "1234 3600 1800 2419200 7200");
    checkRR("example.org", RRType::NS(), "ns1.example.org.");
    checkRR("www.example.org", RRType::A(), "192.0.2.1");
}
