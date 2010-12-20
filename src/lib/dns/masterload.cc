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

#include <istream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>

#include <boost/scoped_ptr.hpp>

#include <exceptions/exceptions.h>

#include <dns/masterload.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>
#include <dns/rrtype.h>

using namespace std;
using namespace boost;
using namespace isc::dns::rdata;

namespace isc {
namespace dns {
void
masterLoad(const char* const filename, const Name& origin,
           const RRClass& zone_class, MasterLoadCallback callback)
{
    ifstream ifs;

    ifs.open(filename, ios_base::in);
    if (ifs.fail()) {
        isc_throw(MasterLoadError, "Failed to open master file: " << filename);
    }
    masterLoad(ifs, origin, zone_class, callback);
    ifs.close();
}

void
masterLoad(istream& input, const Name& origin, const RRClass& zone_class,
           MasterLoadCallback callback)
{
    RRsetPtr rrset;
    string line;
    unsigned int line_count = 1;

    do {
        getline(input, line);
        if (input.bad() || (input.fail() && !input.eof())) {
            isc_throw(MasterLoadError, "Unexpectedly failed to read a line");
        }

        // blank/comment lines should be simply skipped.
        if (line.empty() || line[0] == ';') {
            continue;
        }

        // The line shouldn't have leading space (which means omitting the
        // owner name).
        if (isspace(line[0])) {
            isc_throw(MasterLoadError, "Leading space at line " << line_count);
        }

        // Parse a single RR
        istringstream iss(line);
        string owner_txt, ttl_txt, rrclass_txt, rrtype_txt;
        stringbuf rdatabuf;
        iss >> owner_txt >> ttl_txt >> rrclass_txt >> rrtype_txt >> &rdatabuf;
        if (iss.bad() || iss.fail()) {
            isc_throw(MasterLoadError, "Parse failure for a valid RR at line "
                      << line_count);
        }

        // This simple version doesn't support relative owner names with a
        // separate origin.
        if (owner_txt.empty() || *(owner_txt.end() - 1) != '.') {
            isc_throw(MasterLoadError, "Owner name is not absolute at line "
                      << line_count);
        }

        // XXX: this part is a bit tricky (and less efficient).  We are going
        // to validate the text for the RR parameters, and throw an exception
        // if any of them is invalid by converting an underlying exception
        // to MasterLoadError.  To do that, we need to define the corresponding
        // variables used for RRset construction outside the try-catch block,
        // but we don't like to use a temporary variable with a meaningless
        // initial value.  So we define pointers outside the try block
        // and allocate/initialize the actual objects within the block.
        // To make it exception safe we use Boost.scoped_ptr.
        scoped_ptr<const Name> owner;
        scoped_ptr<const RRTTL> ttl;
        scoped_ptr<const RRClass> rrclass;
        scoped_ptr<const RRType> rrtype;
        ConstRdataPtr rdata;
        try {
            owner.reset(new Name(owner_txt));
            ttl.reset(new RRTTL(ttl_txt));
            rrclass.reset(new RRClass(rrclass_txt));
            rrtype.reset(new RRType(rrtype_txt));
            rdata = createRdata(*rrtype, *rrclass, rdatabuf.str());
        } catch (const Exception& ex) {
            isc_throw(MasterLoadError, "Invalid RR text at line " << line_count
                      << ": " << ex.what());
        }

        // Origin related validation:
        //  - reject out-of-zone data
        //  - reject SOA whose owner is not at the top of zone
        const NameComparisonResult cmp_result = owner->compare(origin);
        if (cmp_result.getRelation() != NameComparisonResult::EQUAL &&
            cmp_result.getRelation() != NameComparisonResult::SUBDOMAIN) {
            isc_throw(MasterLoadError, "Out-of-zone data at line "
                      << line_count);
        }
        if (*rrtype == RRType::SOA() &&
            cmp_result.getRelation() != NameComparisonResult::EQUAL) {
            isc_throw(MasterLoadError, "SOA not at top of zone at line "
                      << line_count);
        }

        // Reject RR class mismatching
        if (*rrclass != zone_class) {
            isc_throw(MasterLoadError, "RR class (" << rrclass_txt
                      << ") does not match the zone class (" << zone_class
                      << ") at line " << line_count);
        }

        // Everything is okay.  Now create/update RRset with the new RR.
        // If this is the first RR or the RR type/name is new, we are seeing
        // a new RRset.
        if (!rrset || rrset->getType() != *rrtype ||
            rrset->getName() != *owner) {
            // Commit the previous RRset, if any.
            if (rrset) {
                callback(rrset);
            }
            rrset = RRsetPtr(new RRset(*owner, *rrclass, *rrtype, *ttl));
        }
        rrset->addRdata(rdata);
    } while (++line_count, !input.eof());

    // Commit the last RRset, if any.
    if (rrset) {
        callback(rrset);
    }
}
} // namespace dns
} // namespace isc
