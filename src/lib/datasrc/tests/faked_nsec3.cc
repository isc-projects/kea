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

#include "faked_nsec3.h"

#include <dns/name.h>

#include <map>

using namespace std;
using namespace isc::dns;

namespace isc {
namespace datasrc {
namespace test {

class TestNSEC3HashCreator::TestNSEC3Hash : public NSEC3Hash {
private:
    typedef map<Name, string> NSEC3HashMap;
    typedef NSEC3HashMap::value_type NSEC3HashPair;
    NSEC3HashMap map_;
public:
    TestNSEC3Hash() {
        // Build pre-defined hash
        map_[Name("example.org")] = apex_hash;
        map_[Name("www.example.org")] = "2S9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM";
        map_[Name("xxx.example.org")] = "Q09MHAVEQVM6T7VBL5LOP2U3T2RP3TOM";
        map_[Name("yyy.example.org")] = "0A9MHAVEQVM6T7VBL5LOP2U3T2RP3TOM";
        map_[Name("x.y.w.example.org")] =
            "2VPTU5TIMAMQTTGL4LUU9KG21E0AOR3S";
        map_[Name("y.w.example.org")] = "K8UDEMVP1J2F7EG6JEBPS17VP3N8I58H";
        map_[Name("w.example.org")] = w_hash;
        map_[Name("zzz.example.org")] = zzz_hash;
        map_[Name("smallest.example.org")] =
            "00000000000000000000000000000000";
        map_[Name("largest.example.org")] =
            "UUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUU";
    }
    virtual string calculate(const Name& name) const {
        const NSEC3HashMap::const_iterator found = map_.find(name);
        if (found != map_.end()) {
            return (found->second);
        }
        isc_throw(isc::Unexpected, "unexpected name for NSEC3 test: "
                  << name);
    }
    virtual bool match(const rdata::generic::NSEC3PARAM&) const {
        return (true);
    }
    virtual bool match(const rdata::generic::NSEC3&) const {
        return (true);
    }
};

NSEC3Hash* TestNSEC3HashCreator::create(const rdata::generic::NSEC3PARAM&)
    const
{
    return (new TestNSEC3Hash);
}

NSEC3Hash* TestNSEC3HashCreator::create(const rdata::generic::NSEC3&) const {
    return (new TestNSEC3Hash);
}

}
}
}
