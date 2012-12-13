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
#include <dns/rrttl.h>
#include <dns/name.h>
#include <dns/rdata.h>

#include <gtest/gtest.h>

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
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
using boost::lexical_cast;

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
    void checkRR(const string& name, const RRType& type, const string& data,
                 const RRTTL& rrttl = RRTTL(3600)) {
        ASSERT_FALSE(rrsets_.empty());
        RRsetPtr current = rrsets_.front();
        rrsets_.pop_front();

        EXPECT_EQ(Name(name), current->getName());
        EXPECT_EQ(type, current->getType());
        EXPECT_EQ(RRClass::IN(), current->getClass());
        EXPECT_EQ(rrttl, current->getTTL());
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
    const char* const reason;  // If non NULL, the reason string
    const char* const problem; // Description of the problem for SCOPED_TRACE
} const error_cases[] = {
    { "www...   3600    IN  A   192.0.2.1", NULL, "Invalid name" },
    { "www      FORTNIGHT   IN  A   192.0.2.1", NULL, "Invalid TTL" },
    { "www      3600    XX  A   192.0.2.1", NULL, "Invalid class" },
    { "www      3600    IN  A   bad_ip", NULL, "Invalid Rdata" },
    { "www      3600    IN", NULL, "Unexpected EOLN" },
    { "www      3600    CH  TXT nothing", NULL, "Class mismatch" },
    { "www      \"3600\"  IN  A   192.0.2.1", NULL, "Quoted TTL" },
    { "www      3600    \"IN\"  A   192.0.2.1", NULL, "Quoted class" },
    { "www      3600    IN  \"A\"   192.0.2.1", NULL, "Quoted type" },
    { "unbalanced)paren 3600    IN  A   192.0.2.1", NULL, "Token error 1" },
    { "www  3600    unbalanced)paren    A   192.0.2.1", NULL,
      "Token error 2" },
    // Check the unknown directive. The rest looks like ordinary RR,
    // so we see the $ is actually special.
    { "$UNKNOWN 3600    IN  A   192.0.2.1", NULL, "Unknown $ directive" },
    { "$INCLUDE", NULL, "Missing include path" },
    { "$INCLUDE /file/not/found", NULL, "Include file not found" },
    { "$INCLUDE /file/not/found and here goes bunch of garbage", NULL,
        "Include file not found and garbage at the end of line" },
    { "$TTL 100 extra-garbage", "Extra tokens at the end of line",
      "$TTL with extra token" },
    { "$TTL", "unexpected end of input", "missing TTL" },
    { "$TTL No-ttl", "Unknown unit used: N in: No-ttl", "bad TTL" },
    { "$TTL \"100\"", "invalid TTL: \"100\"", "bad TTL, quoted" },
    { "$TT 100", "Unknown directive 'TT'", "bad directive, too short" },
    { "$TTLLIKE 100", "Unknown directive 'TTLLIKE'", "bad directive, extra" },
    { NULL, NULL, NULL }
};

// A commonly used helper to check callback message.
void
checkCallbackMessage(const string& actual_msg, const string& expected_msg,
                     size_t expected_line) {
    // The actual message should begin with the expected message.
    EXPECT_EQ(0, actual_msg.find(expected_msg)) << "actual message: "
                                                << actual_msg;

    // and it should end with "...:<line_num>]"
    const string line_desc = ":" + lexical_cast<string>(expected_line) + "]";
    EXPECT_EQ(actual_msg.size() - line_desc.size(), actual_msg.find(line_desc));
}

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
            if (ec->reason != NULL) {
                checkCallbackMessage(errors_.at(0), ec->reason, 2);
            }
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
                             "/example.org example.org bunch of other stuff\n"
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

// Test for "$TTL"
TEST_F(MasterLoaderTest, ttlDirective) {
    stringstream zone_stream;

    // Set the default TTL with $TTL followed by an RR omitting the TTL
    zone_stream << "$TTL 1800\nexample.org. IN A 192.0.2.1\n";
    // $TTL can be quoted.  Also testing the case of $TTL being changed.
    zone_stream << "\"$TTL\" 100\na.example.org. IN A 192.0.2.2\n";
    // Extended TTL form is accepted.
    zone_stream << "$TTL 1H\nb.example.org. IN A 192.0.2.3\n";
    // Matching is case insensitive.
    zone_stream << "$tTl 360\nc.example.org. IN A 192.0.2.3\n";

    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::DEFAULT);
    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    checkRR("example.org", RRType::A(), "192.0.2.1", RRTTL(1800));
    checkRR("a.example.org", RRType::A(), "192.0.2.2", RRTTL(100));
    checkRR("b.example.org", RRType::A(), "192.0.2.3", RRTTL(3600));
    checkRR("c.example.org", RRType::A(), "192.0.2.3", RRTTL(360));
}

TEST_F(MasterLoaderTest, ttlFromSOA) {
    // No $TTL, and the SOA doesn't have an explicit TTL field.  Its minimum
    // TTL field will be used as the RR's TTL, and it'll be used as the
    // default TTL for others.
    stringstream zone_stream("example.org. IN SOA . . 0 0 0 0 1800\n"
                             "a.example.org. IN A 192.0.2.1\n");
    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::DEFAULT);
    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    checkRR("example.org", RRType::SOA(), ". . 0 0 0 0 1800", RRTTL(1800));
    checkRR("a.example.org", RRType::A(), "192.0.2.1", RRTTL(1800));

    // The use of SOA minimum TTL should have caused a warning.
    EXPECT_EQ(1, warnings_.size());
    checkCallbackMessage(warnings_.at(0),
                         "no TTL specified; using SOA MINTTL instead", 1);
}

TEST_F(MasterLoaderTest, ttlFromPrevious) {
    // No available default TTL.  2nd and 3rd RR will use the TTL of the
    // 1st RR.  This will result in a warning, but only for the first time.
    stringstream zone_stream("a.example.org. 1800 IN A 192.0.2.1\n"
                             "b.example.org. IN A 192.0.2.2\n"
                             "c.example.org. IN A 192.0.2.3\n");
    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::DEFAULT);
    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());
    checkRR("a.example.org", RRType::A(), "192.0.2.1", RRTTL(1800));
    checkRR("b.example.org", RRType::A(), "192.0.2.2", RRTTL(1800));
    checkRR("c.example.org", RRType::A(), "192.0.2.3", RRTTL(1800));

    EXPECT_EQ(1, warnings_.size());
    checkCallbackMessage(warnings_.at(0), "using RFC1035 TTL semantics", 2);
}

TEST_F(MasterLoaderTest, ttlFromPreviousSOA) {
    // Mixture of the previous two cases: SOA has explicit TTL, followed by
    // an RR without an explicit TTL.  In this case the minimum TTL won't be
    // recognized as the "default TTL".
    stringstream zone_stream("example.org. 100 IN SOA . . 0 0 0 0 1800\n"
                             "a.example.org. IN A 192.0.2.1\n");
    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::DEFAULT);
    loader_->load();
    EXPECT_TRUE(loader_->loadedSucessfully());

    checkRR("example.org", RRType::SOA(), ". . 0 0 0 0 1800", RRTTL(100));
    checkRR("a.example.org", RRType::A(), "192.0.2.1", RRTTL(100));

    EXPECT_EQ(1, warnings_.size());
    checkCallbackMessage(warnings_.at(0), "using RFC1035 TTL semantics", 2);
}

TEST_F(MasterLoaderTest, ttlUnknown) {
    // No available TTL is known for the first RR.
    stringstream zone_stream("a.example.org. IN A 192.0.2.1\n");
    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::DEFAULT);
    EXPECT_THROW(loader_->load(), MasterLoaderError);
}

TEST_F(MasterLoaderTest, ttlUnknownAndContinue) {
    stringstream zone_stream("a.example.org. IN A 192.0.2.1\n"
                             "b.example.org. 1800 IN A 192.0.2.2\n");
    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);
    loader_->load();
    EXPECT_FALSE(loader_->loadedSucessfully());
    checkRR("b.example.org", RRType::A(), "192.0.2.2", RRTTL(1800));

    EXPECT_TRUE(warnings_.empty());
    EXPECT_EQ(1, errors_.size());
    checkCallbackMessage(errors_.at(0), "no TTL specified; load rejected", 1);
}

TEST_F(MasterLoaderTest, ttlUnknownAndEOF) {
    // Similar to the previous case, but the input will be abruptly terminated
    // after the offending RR.  This will cause an additional warning.
    stringstream zone_stream("a.example.org. IN A 192.0.2.1");
    setLoader(zone_stream, Name("example.org."), RRClass::IN(),
              MasterLoader::MANY_ERRORS);
    loader_->load();
    EXPECT_FALSE(loader_->loadedSucessfully());
    EXPECT_TRUE(rrsets_.empty());

    EXPECT_EQ(1, errors_.size());
    checkCallbackMessage(errors_.at(0), "no TTL specified; load rejected", 1);

    // RDATA implementation can complain about it, too.  To be independent of
    // its details, we focus on the very last warning.
    EXPECT_FALSE(warnings_.empty());
    checkCallbackMessage(*warnings_.rbegin(), "Unexpected end end of file", 1);
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
