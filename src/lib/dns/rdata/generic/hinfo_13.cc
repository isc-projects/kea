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
#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rdata/generic/detail/char_string.h>
#include <util/strutil.h>

#include <string>

#include <boost/lexical_cast.hpp>

using namespace std;
using boost::lexical_cast;
using namespace isc::util;
using namespace isc::dns;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

// helper(s)
namespace {

/// \brief Reads one text field from the given buffer into the given CharString
///
/// \return The number of bytes read
size_t
readTextField(detail::CharString& target, InputBuffer& buffer,
              size_t rdata_len) {
    if (rdata_len < 1 || buffer.getLength() < 1) {
        isc_throw(isc::dns::DNSMessageFORMERR, "Error in parsing "
                  "HINFO RDATA: insufficient data");
    }
    const uint8_t len = buffer.readUint8();
    if (rdata_len < len + 1) {
        isc_throw(isc::dns::DNSMessageFORMERR, "Error in parsing "
                  "HINFO RDATA: character string length is too large: " <<
                  static_cast<int>(len));
    }
    if (buffer.getLength() < len) {
        isc_throw(isc::dns::DNSMessageFORMERR, "Error in parsing "
                  "HINFO RDATA: not enough data in buffer to read: " <<
                  static_cast<int>(len) << " bytes");
    }

    target.resize(len + 1);
    target[0] = len;
    buffer.readData(&target[0] + 1, len);

    return (len + 1);
}

/// \brief Compare one CharString field to another
///
/// \param self The CharString field to compare
/// \param other The CharString field to compare to
///
/// \return -1 if \c self would be sorted before \c other
///          1 if \c self would be sorted after \c other
///          0 if \c self and \c other are equal
int compareField(const detail::CharString& self,
                 const detail::CharString& other) {
    const size_t self_len = self[0];
    const size_t other_len = other[0];
    const size_t cmp_len = min(self_len, other_len);
    const int cmp = memcmp(&self[1], &other[1], cmp_len);
    if (cmp < 0) {
        return (-1);
    } else if (cmp > 0) {
        return (1);
    } else if (self_len < other_len) {
        return (-1);
    } else if (self_len > other_len) {
        return (1);
    } else {
        return (0);
    }
}

} // end unnamed namespace

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
        rdata_len -= readTextField(cpu, buffer, rdata_len);
        rdata_len -= readTextField(os, buffer, rdata_len);
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

HINFO::~HINFO() {
    delete impl_;
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

    const int cmp = compareField(impl_->cpu, other_hinfo.impl_->cpu);
    if (cmp != 0) {
        return (cmp);
    }
    return (compareField(impl_->os, other_hinfo.impl_->os));
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

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
