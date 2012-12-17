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
#include <dns/rdata.h>

#include <gtest/gtest.h>
#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>

#include <string>
#include <vector>
#include <list>
#include <sstream>

using namespace isc::dns;
using std::vector;
using std::string;
using std::list;
using std::stringstream;
using std::endl;

namespace {
class MasterLoaderTest : public ::testing::Test {
public:
    MasterLoaderTest() :
        callbacks_(boost::bind(&MasterLoaderTest::callback, this,
                               &errors_, _1, _2, _3),
                   boost::bind(&MasterLoaderTest::callback, this,
                               &warnings_, _1, _2, _3))
    {}

    /// Concatenate file, line, and reason, and add it to either errors
    /// or warnings
    void callback(vector<string>* target, const std::string& file, size_t line,
                  const std::string& reason)
    {
        std::stringstream ss;
        ss << reason << " [" << file << ":" << line << "]";
        target->push_back(ss.str());
    }

    void addRRset(const Name& name, const RRClass& rrclass,
                  const RRType& rrtype, const RRTTL& rrttl,
                  const rdata::RdataPtr& data) {
        const RRsetPtr rrset(new BasicRRset(name, rrclass, rrtype, rrttl));
        rrset->addRdata(data);
        rrsets_.push_back(rrset);
    }

    void setLoader(const char* file, const Name& origin,
                   const RRClass& rrclass, const MasterLoader::Options options)
    {
        loader_.reset(new MasterLoader(file, origin, rrclass, callbacks_,
                                       boost::bind(&MasterLoaderTest::addRRset,
                                                   this, _1, _2, _3, _4, _5),
                                       options));
    }

    void setLoader(std::istream& stream, const Name& origin,
                   const RRClass& rrclass, const MasterLoader::Options options)
    {
        loader_.reset(new MasterLoader(stream, origin, rrclass, callbacks_,
                                       boost::bind(&MasterLoaderTest::addRRset,
                                                   this, _1, _2, _3, _4, _5),
                                       options));
    }

    static string prepareZone(const string& line, bool include_last) {
        string result;
        result += "example.org. 3600 IN SOA ns1.example.org. "
            "admin.example.org. 1234 3600 1800 2419200 7200\n";
        result += line;
        if (include_last) {
            result += "\n";
            result += "correct 3600    IN  A 192.0.2.2\n";
        }
        return (result);
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
        EXPECT_EQ(type, current->getType());
        EXPECT_EQ(RRClass::IN(), current->getClass());
        ASSERT_EQ(1, current->getRdataCount());
        EXPECT_EQ(0, isc::dns::rdata::createRdata(type, RRClass::IN(), data)->
                  compare(current->getRdataIterator()->getCurrent()));
    }

    void checkBasicRRs() {
        checkRR("example.org", RRType::SOA(),
                "ns1.example.org. admin.example.org. "
                "1234 3600 1800 2419200 7200");
        checkRR("example.org", RRType::NS(), "ns1.example.org.");
        checkRR("www.example.org", RRType::A(), "192.0.2.1");
        checkRR("www.example.org", RRType::AAAA(), "2001:db8::1");
    }

    void checkARR(const string& name) {
        checkRR(name, RRType::A(), "192.0.2.1");
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

    EXPECT_FALSE(loader_->loadedSucessfully());
    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());

    EXPECT_TRUE(errors_.empty());
    EXPECT_TRUE(warnings_.empty());

    checkBasicRRs();
}

// Test the $INCLUDE directive
TEST_F(MasterLoaderTest, include) {
    // Test various cases of include
    const char* includes[] = {
        "$include",
        "$INCLUDE",
        "$Include",
        "$InCluDe",
        "\"$INCLUDE\"",
        NULL
    };
    for (const char** include = includes; *include != NULL; ++include) {
        SCOPED_TRACE(*include);

        clear();
        // Prepare input source that has the include and some more data
        // below (to see it returns back to the original source).
        const string include_str = string(*include) + " " +
            TEST_DATA_SRCDIR + "/example.org\nwww 3600 IN AAAA 2001:db8::1\n";
        stringstream ss(include_str);
        setLoader(ss, Name("example.org."), RRClass::IN(),
                  MasterLoader::MANY_ERRORS);

        loader_->load();
        EXPECT_TRUE(loader_->loadedSucessfully());
        EXPECT_TRUE(errors_.empty());
        EXPECT_TRUE(warnings_.empty());

        checkBasicRRs();
        checkRR("www.example.org", RRType::AAAA(), "2001:db8::1");
    }
}

TEST_F(MasterLoaderTest, origin) {
    // Various forms of the directive
    const char* origins[] = {
        "$origin",
        "$ORIGIN",
        "$Origin",
        "$OrigiN",
        "\"$ORIGIN\"",
        NULL
    };
    for (const char** origin = origins; *origin != NULL; ++origin) {
        SCOPED_TRACE(*origin);

        clear();
        const string directive = *origin;
        const string input =
            "@  1H  IN  A   192.0.2.1\n" +
            directive + " sub.example.org.\n"
            "\"www\"    1H  IN  A   192.0.2.1\n" +
            // Relative name in the origin
            directive + " relative\n"
            "@  1H  IN  A   192.0.2.1\n"
            // Origin is _not_ used here (absolute name)
            "noorigin.example.org.  60M IN  A   192.0.2.1\n";
        stringstream ss(input);
        setLoader(ss, Name("example.org."), RRClass::IN(),
                  MasterLoader::MANY_ERRORS);

        loader_->load();
        EXPECT_TRUE(loader_->loadedSucessfully());
        EXPECT_TRUE(errors_.empty());
        EXPECT_TRUE(warnings_.empty());

        checkARR("example.org");
        checkARR("www.sub.example.org");
        checkARR("relative.sub.example.org");
        checkARR("noorigin.example.org");
    }
}

// Test the source is correctly popped even after error
TEST_F(MasterLoaderTest, popAfterError) {
    const string include_str = "$include " TEST_DATA_SRCDIR
        "/broken.zone\nwww 3600 IN AAAA 2001:db8::1\n";
    stringstream ss(include_str);
    // We don't test without MANY_ERRORS, we want to see what happens
    // after the error.
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_FALSE(loader_->loadedSucessfully());
    EXPECT_EQ(1, errors_.size()); // For the broken RR
    EXPECT_EQ(1, warnings_.size()); // For missing EOLN

    // The included file doesn't contain anything usable, but the
    // line after the include should be there.
    checkRR("www.example.org", RRType::AAAA(), "2001:db8::1");
}

// Check it works the same when created based on a stream, not filename
TEST_F(MasterLoaderTest, streamConstructor) {
    stringstream zone_stream(prepareZone("", true));
    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    EXPECT_FALSE(loader_->loadedSucessfully());
    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());

    EXPECT_TRUE(errors_.empty());
    EXPECT_TRUE(warnings_.empty());
    checkRR("example.org", RRType::SOA(), "ns1.example.org. "
            "admin.example.org. 1234 3600 1800 2419200 7200");
    checkRR("correct.example.org", RRType::A(), "192.0.2.2");
}

// Try loading data incrementally.
TEST_F(MasterLoaderTest, incrementalLoad) {
    setLoader(TEST_DATA_SRCDIR "/example.org", Name("example.org."),
              RRClass::IN(), MasterLoader::MANY_ERRORS);

    EXPECT_FALSE(loader_->loadedSucessfully());
    EXPECT_FALSE(loader_->loadIncremental(2));
    EXPECT_FALSE(loader_->loadedSucessfully());

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
    EXPECT_TRUE(loader_->loadedSucessfully());

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
    const char* const line;    // The broken line in master file
    const char* const problem; // Description of the problem for SCOPED_TRACE
} const error_cases[] = {
    { "www...   3600    IN  A   192.0.2.1", "Invalid name" },
    { "www      FORTNIGHT   IN  A   192.0.2.1", "Invalid TTL" },
    { "www      3600    XX  A   192.0.2.1", "Invalid class" },
    { "www      3600    IN  A   bad_ip", "Invalid Rdata" },
    { "www      3600    IN", "Unexpected EOLN" },
    { "www      3600    CH  TXT nothing", "Class mismatch" },
    { "www      \"3600\"  IN  A   192.0.2.1", "Quoted TTL" },
    { "www      3600    \"IN\"  A   192.0.2.1", "Quoted class" },
    { "www      3600    IN  \"A\"   192.0.2.1", "Quoted type" },
    { "unbalanced)paren 3600    IN  A   192.0.2.1", "Token error 1" },
    { "www  3600    unbalanced)paren    A   192.0.2.1", "Token error 2" },
    // Check the unknown directive. The rest looks like ordinary RR,
    // so we see the $ is actually special.
    { "$UNKNOWN 3600    IN  A   192.0.2.1", "Unknown $ directive" },
    { "$INCLUD " TEST_DATA_SRCDIR "/example.org", "Include too short" },
    { "$INCLUDES " TEST_DATA_SRCDIR "/example.org", "Include too long" },
    { "$INCLUDE", "Missing include path" },
    { "$INCLUDE /file/not/found", "Include file not found" },
    { "$INCLUDE /file/not/found example.org. and here goes bunch of garbage",
        "Include file not found and garbage at the end of line" },
    { "$ORIGIN", "Missing origin name" },
    { "$ORIGIN invalid...name", "Invalid name for origin" },
    { "$ORIGI name.", "$ORIGIN too short" },
    { "$ORIGINAL name.", "$ORIGIN too long" },
    { NULL, NULL }
};

// Test a broken zone is handled properly. We test several problems,
// both in strict and lenient mode.
TEST_F(MasterLoaderTest, brokenZone) {
    for (const ErrorCase* ec = error_cases; ec->line != NULL; ++ec) {
        SCOPED_TRACE(ec->problem);
        const string zone(prepareZone(ec->line, true));

        {
            SCOPED_TRACE("Strict mode");
            clear();
            stringstream zone_stream(zone);
            setLoader(zone_stream, Name("example.org."), RRClass::IN(),
                      MasterLoader::DEFAULT);
            EXPECT_FALSE(loader_->loadedSucessfully());
            EXPECT_THROW(loader_->load(), MasterLoaderError);
            EXPECT_FALSE(loader_->loadedSucessfully());
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
            stringstream zone_stream(zone);
            setLoader(zone_stream, Name("example.org."), RRClass::IN(),
                      MasterLoader::MANY_ERRORS);
            EXPECT_FALSE(loader_->loadedSucessfully());
            EXPECT_NO_THROW(loader_->load());
            EXPECT_FALSE(loader_->loadedSucessfully());
            EXPECT_EQ(1, errors_.size());
            EXPECT_TRUE(warnings_.empty());
            checkRR("example.org", RRType::SOA(), "ns1.example.org. "
                    "admin.example.org. 1234 3600 1800 2419200 7200");
            // This one is below the error one.
            checkRR("correct.example.org", RRType::A(), "192.0.2.2");
            EXPECT_TRUE(rrsets_.empty());
        }

        {
            SCOPED_TRACE("Error at EOF");
            // This case is interesting only in the lenient mode.
            clear();
            const string zoneEOF(prepareZone(ec->line, false));
            stringstream zone_stream(zoneEOF);
            setLoader(zone_stream, Name("example.org."), RRClass::IN(),
                      MasterLoader::MANY_ERRORS);
            EXPECT_FALSE(loader_->loadedSucessfully());
            EXPECT_NO_THROW(loader_->load());
            EXPECT_FALSE(loader_->loadedSucessfully());
            EXPECT_EQ(1, errors_.size()) << errors_[0] << "\n" << errors_[1];
            // The unexpected EOF warning
            EXPECT_EQ(1, warnings_.size());
            checkRR("example.org", RRType::SOA(), "ns1.example.org. "
                    "admin.example.org. 1234 3600 1800 2419200 7200");
            EXPECT_TRUE(rrsets_.empty());
        }
    }
}

// Check that a garbage after the include generates an error, but not fatal
// one (in lenient mode) and we can recover.
TEST_F(MasterLoaderTest, includeWithGarbage) {
    // Include an origin (example.org) because we expect it to be handled
    // soon and we don't want it to break here.
    const string include_str("$INCLUDE " TEST_DATA_SRCDIR
                             "/example.org example.org. bunch of other stuff\n"
                             "www 3600 IN AAAA 2001:db8::1\n");
    stringstream zone_stream(include_str);
    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    EXPECT_NO_THROW(loader_->load());
    EXPECT_FALSE(loader_->loadedSucessfully());
    ASSERT_EQ(1, errors_.size());
    // It says something about extra tokens at the end
    EXPECT_NE(string::npos, errors_[0].find("Extra"));
    EXPECT_TRUE(warnings_.empty());
    checkBasicRRs();
    checkRR("www.example.org", RRType::AAAA(), "2001:db8::1");
}

// Check we error about garbage at the end of $ORIGIN line (but the line works).
TEST_F(MasterLoaderTest, originWithGarbage) {
    const string origin_str = "$ORIGIN www More garbage here\n"
        "@  1H  IN  A   192.0.2.1\n";
    stringstream ss(origin_str);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);
    EXPECT_NO_THROW(loader_->load());
    EXPECT_FALSE(loader_->loadedSucessfully());
    ASSERT_EQ(1, errors_.size());
    // It says something about extra tokens at the end
    EXPECT_NE(string::npos, errors_[0].find("Extra"));
    EXPECT_TRUE(warnings_.empty());
    checkARR("www.example.org");
}

// Test we can pass both file to include and the origin to switch
TEST_F(MasterLoaderTest, includeAndOrigin) {
    // First, switch origin to something else, so we can check it is
    // switched back.
    const string include_string = "$ORIGIN www\n"
        "@  1H  IN  A   192.0.2.1\n"
        // Then include the file with data and switch origin back
        "$INCLUDE " TEST_DATA_SRCDIR "/example.org example.org.\n"
        // Another RR to see the switch survives after we exit include
        "www    1H  IN  A   192.0.2.1\n";
    stringstream ss(include_string);
    setLoader(ss, Name("example.org"), RRClass::IN(),
              MasterLoader::MANY_ERRORS);
    // Successfully load the data
    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty());
    EXPECT_TRUE(warnings_.empty());
    // And check it's the correct data
    checkARR("www.example.org");
    checkBasicRRs();
    checkARR("www.example.org");
}

// Check the origin doesn't get outside of the included file.
TEST_F(MasterLoaderTest, includeOriginRestore) {
    const string include_string = "$INCLUDE " TEST_DATA_SRCDIR "/origincheck.txt\n"
        "@  1H  IN  A   192.0.2.1\n";
    stringstream ss(include_string);
    setLoader(ss, Name("example.org"), RRClass::IN(),
              MasterLoader::MANY_ERRORS);
    // Successfully load the data
    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty());
    EXPECT_TRUE(warnings_.empty());
    // And check it's the correct data
    checkARR("www.example.org");
    checkARR("example.org");
}

// Check we restore the last name for initial whitespace when returning from
// include. But we do produce a warning if there's one just ofter the include.
TEST_F(MasterLoaderTest, includeAndInitialWS) {
    const string include_string = "xyz  1H  IN  A   192.0.2.1\n"
        "$INCLUDE " TEST_DATA_SRCDIR "/example.org\n"
        "   1H  IN  A   192.0.2.1\n";
    stringstream ss(include_string);
    setLoader(ss, Name("example.org"), RRClass::IN(),
              MasterLoader::MANY_ERRORS);
    // Successfully load the data
    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty());
    EXPECT_EQ(1, warnings_.size());
    checkARR("xyz.example.org");
    checkBasicRRs();
    checkARR("xyz.example.org");
}

// Test the constructor rejects empty add callback.
TEST_F(MasterLoaderTest, emptyCallback) {
    EXPECT_THROW(MasterLoader(TEST_DATA_SRCDIR "/example.org",
                              Name("example.org"), RRClass::IN(), callbacks_,
                              AddRRCallback()), isc::InvalidParameter);
    // And the same with the second constructor
    stringstream ss("");
    EXPECT_THROW(MasterLoader(ss, Name("example.org"), RRClass::IN(),
                              callbacks_, AddRRCallback()),
                 isc::InvalidParameter);
}

// Check it throws when we try to load after loading was complete.
TEST_F(MasterLoaderTest, loadTwice) {
    setLoader(TEST_DATA_SRCDIR "/example.org", Name("example.org."),
              RRClass::IN(), MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_THROW(loader_->load(), isc::InvalidOperation);
}

// Load 0 items should be rejected
TEST_F(MasterLoaderTest, loadZero) {
    setLoader(TEST_DATA_SRCDIR "/example.org", Name("example.org."),
              RRClass::IN(), MasterLoader::MANY_ERRORS);
    EXPECT_THROW(loader_->loadIncremental(0), isc::InvalidParameter);
}

// Test there's a warning when the file terminates without end of
// line.
TEST_F(MasterLoaderTest, noEOLN) {
    // No \n at the end
    const string input("example.org. 3600 IN SOA ns1.example.org. "
                       "admin.example.org. 1234 3600 1800 2419200 7200");
    stringstream ss(input);
    setLoader(ss, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);

    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    EXPECT_TRUE(errors_.empty()) << errors_[0];
    // There should be one warning about the EOLN
    EXPECT_EQ(1, warnings_.size());
    checkRR("example.org", RRType::SOA(), "ns1.example.org. "
            "admin.example.org. 1234 3600 1800 2419200 7200");
}

}
