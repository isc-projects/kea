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

#include <config.h>

#include <string>

#include <util/buffer.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <dns/rdata/generic/detail/lexer_util.h>

using namespace std;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

NS::NS(const std::string& namestr) :
    // Fill in dummy name and replace them soon below.
    nsname_(Name::ROOT_NAME())
{
    try {
        std::istringstream ss(namestr);
        MasterLexer lexer;
        lexer.pushSource(ss);

        nsname_ = createNameFromLexer(lexer, NULL);

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for NS: "
                      << namestr);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct NS from '" <<
                  namestr << "': " << ex.what());
    }
}

NS::NS(InputBuffer& buffer, size_t) :
    nsname_(buffer)
{
    // we don't need rdata_len for parsing.  if necessary, the caller will
    // check consistency.
}

NS::NS(MasterLexer& lexer, const Name* origin,
       MasterLoader::Options, MasterLoaderCallbacks&) :
    nsname_(createNameFromLexer(lexer, origin))
{}

NS::NS(const NS& other) :
    Rdata(), nsname_(other.nsname_)
{}

void
NS::toWire(OutputBuffer& buffer) const {
    nsname_.toWire(buffer);
}

void
NS::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeName(nsname_);
}

string
NS::toText() const {
    return (nsname_.toText());
}

int
NS::compare(const Rdata& other) const {
    const NS& other_ns = dynamic_cast<const NS&>(other);

    return (compareNames(nsname_, other_ns.nsname_));
}

const Name&
NS::getNSName() const {
    return (nsname_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
