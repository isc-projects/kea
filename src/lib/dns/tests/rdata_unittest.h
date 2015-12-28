// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RDATA_UNITTEST_H
#define RDATA_UNITTEST_H 1

#include <util/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rdata.h>
#include <dns/master_lexer.h>

#include <gtest/gtest.h>

#include <string>
#include <sstream>

namespace isc {
namespace dns {
namespace rdata {
class RdataTest : public ::testing::Test {
protected:
    RdataTest();
    static RdataPtr rdataFactoryFromFile(const RRType& rrtype,
                                         const RRClass& rrclass,
                                         const char* datafile,
                                         size_t position = 0);

    // Common check to see the result of Rdata construction of given type
    // (template parameter RdataType) either from std::string or with
    // MasterLexer object.  If it's expected to succeed the result should be
    // identical to the commonly used test data (rdata_expected); otherwise it
    // should result in the exception specified as the template parameter:
    // ExForString for the string version, and ExForLexer for the lexer
    // version.  throw_str_version and throw_lexer_version are set to true
    // iff the string/lexer version is expected to throw, respectively.
    // Parameter origin can be set to non NULL for the origin parameter of
    // the lexer version of Rdata constructor.
    template <typename RdataType, typename ExForString, typename ExForLexer>
    void checkFromText(const std::string& rdata_txt,
                       const RdataType& rdata_expected,
                       bool throw_str_version = true,
                       bool throw_lexer_version = true,
                       const Name* origin = NULL)
    {
        SCOPED_TRACE(rdata_txt);

        if (throw_str_version) {
            EXPECT_THROW(RdataType rdata(rdata_txt), ExForString);
        } else {
            EXPECT_EQ(0, RdataType(rdata_txt).compare(rdata_expected));
        }

        std::stringstream ss(rdata_txt);
        MasterLexer lexer;
        lexer.pushSource(ss);
        if (throw_lexer_version) {
            EXPECT_THROW(RdataType rdata(lexer, origin, MasterLoader::DEFAULT,
                                         loader_cb), ExForLexer);
        } else {
            EXPECT_EQ(0, RdataType(lexer, origin, MasterLoader::DEFAULT,
                                   loader_cb).compare(rdata_expected));
        }
    }

    isc::util::OutputBuffer obuffer;
    MessageRenderer renderer;
    /// This is an RDATA object of some "unknown" RR type so that it can be
    /// used to test the compare() method against a well-known RR type.
    RdataPtr rdata_nomatch;
    MasterLexer lexer;
    MasterLoaderCallbacks loader_cb;
};

namespace test {
RdataPtr
createRdataUsingLexer(const RRType& rrtype, const RRClass& rrclass,
                      const std::string& str);
}

}
}
}
#endif // RDATA_UNITTEST_H

// Local Variables:
// mode: c++
// End:
