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
#include <fstream>

using namespace isc::dns;
using std::vector;
using std::string;
using std::list;
using std::ofstream;
using std::endl;

namespace {
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
        ss << reason << " [" << file << ":" << line << "]";
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
        loader_.reset(new MasterLoader(file, origin, rrclass, callbacks_,
                                       boost::bind(&MasterLoaderTest::addRRset,
                                                   this, _1, _2, _3, _4, _5),
                                       options));
    }

    void prepareBrokenZone(const string& filename, const string& line) {
        ofstream out(filename.c_str(),
                     std::ios_base::out | std::ios_base::trunc);
        ASSERT_FALSE(out.fail());
        out << "example.org. 3600 IN SOA ns1.example.org. "
            "admin.example.org. 1234 3600 1800 2419200 7200" << endl;
        out << line << endl;
        out << "correct 3600    IN  A 192.0.2.2" << endl;
        out.close();
    }

    void clear() {
        warnings_.clear();
        errors_.clear();
        rrsets_.clear();
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
    setLoader(TEST_DATA_SRCDIR "/example.org", Name("example.org."),
              RRClass::IN(), MasterLoader::MANY_ERRORS);

    loader_->load();

    EXPECT_TRUE(errors_.empty());
    EXPECT_TRUE(warnings_.empty());

    checkRR("example.org", RRType::SOA(),
            "ns1.example.org. admin.example.org. "
            "1234 3600 1800 2419200 7200");
    checkRR("example.org", RRType::NS(), "ns1.example.org.");
    checkRR("www.example.org", RRType::A(), "192.0.2.1");
}

// Try loading data incrementally.
TEST_F(MasterLoaderTest, incrementalLoad) {
    setLoader(TEST_DATA_SRCDIR "/example.org", Name("example.org."),
              RRClass::IN(), MasterLoader::MANY_ERRORS);

    EXPECT_FALSE(loader_->loadIncremental(2));

    EXPECT_TRUE(errors_.empty());
    EXPECT_TRUE(warnings_.empty());

    checkRR("example.org", RRType::SOA(),
            "ns1.example.org. admin.example.org. "
            "1234 3600 1800 2419200 7200");
    checkRR("example.org", RRType::NS(), "ns1.example.org.");

    // The third one is not loaded yet
    EXPECT_TRUE(rrsets_.empty());

    // Load the rest.
    EXPECT_TRUE(loader_->loadIncremental(20));

    EXPECT_TRUE(errors_.empty());
    EXPECT_TRUE(warnings_.empty());

    checkRR("www.example.org", RRType::A(), "192.0.2.1");
}

// Try loading from file that doesn't exist. There should be single error
// saying so.
TEST_F(MasterLoaderTest, invalidFile) {
    setLoader("This file doesn't exist at all",
              Name("exmaple.org."), RRClass::IN(), MasterLoader::MANY_ERRORS);

    // Nothing yet. The loader is dormant until invoked.
    // Is it really what we want?
    EXPECT_TRUE(errors_.empty());

    loader_->load();

    EXPECT_TRUE(warnings_.empty());
    EXPECT_TRUE(rrsets_.empty());
    ASSERT_EQ(1, errors_.size());
    EXPECT_EQ(0, errors_[0].find("Error opening the input source file: ")) <<
        "Different error: " << errors_[0];
}

struct ErrorCase {
    const char* const line;
    const char* const problem;
} const error_cases[] = {
    { "www...   3600    IN  A   192.0.2.1", "Invalid name" },
    { "www      FORTNIGHT   IN  A   192.0.2.1", "Invalid TTL" },
    { "www      3600    XX  A   192.0.2.1", "Invalid class" },
    { "www      3600    IN  A   bad_ip", "Invalid Rdata" },
    { "www      3600    IN", "Unexpected EOLN" },
    { "www      3600    CH  TXT nothing", "Class mismatch" },
    { NULL, NULL }
};

// Test a broken zone is handled properly. We test several problems,
// both in strict and lenient mode.
TEST_F(MasterLoaderTest, brokenZone) {
    const string filename(TEST_DATA_BUILDDIR "/broken.zone");
    for (const ErrorCase* ec = error_cases; ec->line != NULL; ++ec) {
        SCOPED_TRACE(ec->problem);
        prepareBrokenZone(filename, ec->line);

        {
            SCOPED_TRACE("Strict mode");
            clear();
            setLoader(filename.c_str(), Name("example.org."), RRClass::IN(),
                      MasterLoader::DEFAULT);
            loader_->load();
            EXPECT_EQ(1, errors_.size());
            EXPECT_TRUE(warnings_.empty());

            checkRR("example.org", RRType::SOA(), "ns1.example.org. "
                    "admin.example.org. 1234 3600 1800 2419200 7200");
            // In the strict mode, it is aborted. The last RR is not
            // even attempted.
            EXPECT_TRUE(rrsets_.empty());
        }

        {
            SCOPED_TRACE("Lenient mode");
            clear();
            setLoader(filename.c_str(), Name("example.org."), RRClass::IN(),
                      MasterLoader::MANY_ERRORS);
            loader_->load();
            EXPECT_EQ(1, errors_.size());
            EXPECT_TRUE(warnings_.empty());
            checkRR("example.org", RRType::SOA(), "ns1.example.org. "
                    "admin.example.org. 1234 3600 1800 2419200 7200");
            // This one is below the error one.
            checkRR("correct.example.org", RRType::A(), "192.0.2.2");
            EXPECT_TRUE(rrsets_.empty());
        }
    }
}

// Test the constructor rejects empty add callback.
TEST_F(MasterLoaderTest, emptyCallback) {
    EXPECT_THROW(MasterLoader(TEST_DATA_SRCDIR "/example.org",
                              Name("example.org"), RRClass::IN(), callbacks_,
                              AddRRCallback()), isc::InvalidParameter);
}

// Check it throws when we try to load after loading was complete.
TEST_F(MasterLoaderTest, loadTwice) {
    setLoader(TEST_DATA_SRCDIR "/example.org", Name("example.org."),
              RRClass::IN(), MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_THROW(loader_->load(), isc::InvalidOperation);
}
}
