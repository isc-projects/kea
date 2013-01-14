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

#include <config.h>

#include <exceptions/exceptions.h>
#include <dns/exceptions.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rdata/generic/detail/char_string.h>
#include <util/buffer.h>

using namespace std;
using namespace isc::util;
using namespace isc::dns;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

class HINFOImpl {
public:
    HINFOImpl(const std::string& hinfo_str) {
        std::istringstream ss(hinfo_str);
        MasterLexer lexer;
        lexer.pushSource(ss);

        try {
            parseHINFOData(lexer);
            // Should be at end of data now
            if (lexer.getNextToken(MasterToken::QSTRING, true).getType() !=
                MasterToken::END_OF_FILE) {
                isc_throw(InvalidRdataText,
                          "Invalid HINFO text format: too many fields.");
            }
        } catch (const MasterLexer::LexerError& ex) {
            isc_throw(InvalidRdataText, "Failed to construct HINFO RDATA from "
                                        << hinfo_str << "': " << ex.what());
        }
    }

    HINFOImpl(InputBuffer& buffer, size_t rdata_len) {
        rdata_len -= detail::bufferToCharString(buffer, rdata_len, cpu);
        rdata_len -= detail::bufferToCharString(buffer, rdata_len, os);
        if (rdata_len != 0) {
            isc_throw(isc::dns::DNSMessageFORMERR, "Error in parsing " <<
                      "HINFO RDATA: bytes left at end: " <<
                      static_cast<int>(rdata_len));
        }
    }

    HINFOImpl(MasterLexer& lexer)
    {
        parseHINFOData(lexer);
    }

private:
    void
    parseHINFOData(MasterLexer& lexer) {
        MasterToken token = lexer.getNextToken(MasterToken::QSTRING);
        stringToCharString(token.getStringRegion(), cpu);
        token = lexer.getNextToken(MasterToken::QSTRING);
        stringToCharString(token.getStringRegion(), os);
    }

public:
    detail::CharString cpu;
    detail::CharString os;
};

HINFO::HINFO(const std::string& hinfo_str) : impl_(new HINFOImpl(hinfo_str))
{}


HINFO::HINFO(InputBuffer& buffer, size_t rdata_len) :
    impl_(new HINFOImpl(buffer, rdata_len))
{}

HINFO::HINFO(const HINFO& source):
    Rdata(), impl_(new HINFOImpl(*source.impl_))
{
}

HINFO::HINFO(MasterLexer& lexer, const Name*,
             MasterLoader::Options, MasterLoaderCallbacks&) :
    impl_(new HINFOImpl(lexer))
{}

HINFO&
HINFO::operator=(const HINFO& source)
{
    impl_.reset(new HINFOImpl(*source.impl_));
    return (*this);
}

HINFO::~HINFO() {
}

std::string
HINFO::toText() const {
    string result;
    result += "\"";
    result += detail::charStringToString(impl_->cpu);
    result += "\" \"";
    result += detail::charStringToString(impl_->os);
    result += "\"";
    return (result);
}

void
HINFO::toWire(OutputBuffer& buffer) const {
    toWireHelper(buffer);
}

void
HINFO::toWire(AbstractMessageRenderer& renderer) const {
    toWireHelper(renderer);
}

int
HINFO::compare(const Rdata& other) const {
    const HINFO& other_hinfo = dynamic_cast<const HINFO&>(other);

    const int cmp = compareCharStrings(impl_->cpu, other_hinfo.impl_->cpu);
    if (cmp != 0) {
        return (cmp);
    }
    return (compareCharStrings(impl_->os, other_hinfo.impl_->os));
}

const std::string
HINFO::getCPU() const {
    return (detail::charStringToString(impl_->cpu));
}

const std::string
HINFO::getOS() const {
    return (detail::charStringToString(impl_->os));
}

template <typename T>
void
HINFO::toWireHelper(T& outputer) const {
    outputer.writeData(&impl_->cpu[0], impl_->cpu.size());
    outputer.writeData(&impl_->os[0], impl_->os.size());
}

void HINFO::ptr() const {
    std::cout << "[XX] PTR: " << impl_.get() << std::endl;
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
