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


#include <gtest/gtest.h>
#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>

using namespace isc::dns;

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
    void
    callback(bool error, const std::string& file, size_t line,
             const std::string reason)
    {
        std::stringstream ss;
        ss << file << line << reason;
        if (error) {
            errors.push_back(ss.str());
        } else {
            warnings.push_back(ss.str());
        }
    }

    void
    setLoader(const char* file, const Name& origin, const RRClass rrclass,
              const MasterLoader::Options options)
    {
        loader.reset(new MasterLoader(file, origin, rrclass, callbacks_, options));
    }

    MasterLoaderCallbacks callbacks_;
    boost::scoped_ptr<MasterLoader> loader;
    std::vector<std::string> errors;
    std::vector<std::string> warnings;
};

TEST_F(MasterLoaderTest, basicLoad) {
    setLoader("testdata/loader_test.txt",
              Name("example.com."),
              RRClass::IN(),
              MasterLoader::MANY_ERRORS);
    ASSERT_FALSE(loader->loadIncremental(1));
}
