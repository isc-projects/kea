// Copyright (C) 2010, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <util/encode/hex.h>

#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/master_lexer.h>
#include <dns/rdata.h>
#include <dns/rrparamregistry.h>
#include <dns/rrtype.h>

#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

#include <algorithm>
#include <cctype>
#include <string>
#include <sstream>
#include <iomanip>
#include <ios>
#include <ostream>
#include <vector>

#include <stdint.h>
#include <string.h>

using namespace std;
using boost::lexical_cast;
using namespace isc::util;

namespace isc {
namespace dns {
namespace rdata {

uint16_t
Rdata::getLength() const {
    OutputBuffer obuffer(0);

    toWire(obuffer);

    return (obuffer.getLength());
}

// XXX: we need to specify std:: for string to help doxygen match the
// function signature with that given in the header file.
RdataPtr
createRdata(const RRType& rrtype, const RRClass& rrclass,
            const std::string& rdata_string)
{
    return (RRParamRegistry::getRegistry().createRdata(rrtype, rrclass,
                                                       rdata_string));
}

RdataPtr
createRdata(const RRType& rrtype, const RRClass& rrclass,
            isc::util::InputBuffer& buffer, size_t len)
{
    if (len > MAX_RDLENGTH) {
        isc_throw(InvalidRdataLength, "RDLENGTH too large");
    }

    size_t old_pos = buffer.getPosition();

    RdataPtr rdata =
        RRParamRegistry::getRegistry().createRdata(rrtype, rrclass, buffer,
                                                   len);

    if (buffer.getPosition() - old_pos != len) {
        isc_throw(InvalidRdataLength, "RDLENGTH mismatch: " <<
                  buffer.getPosition() - old_pos << " != " << len);
    }

    return (rdata);
}

RdataPtr
createRdata(const RRType& rrtype, const RRClass& rrclass, const Rdata& source)
{
    return (RRParamRegistry::getRegistry().createRdata(rrtype, rrclass,
                                                       source));
}

namespace {
void
fromtextError(bool& error_issued, const MasterLexer& lexer,
              MasterLoaderCallbacks& callbacks,
              const MasterToken* token, const char* reason)
{
    // Don't be too noisy if there are many issues for single RDATA
    if (error_issued) {
        return;
    }
    error_issued = true;

    if (token == NULL) {
        callbacks.error(lexer.getSourceName(), lexer.getSourceLine(),
                        "createRdata from text failed: " + string(reason));
        return;
    }

    switch (token->getType()) {
    case MasterToken::STRING:
    case MasterToken::QSTRING:
        callbacks.error(lexer.getSourceName(), lexer.getSourceLine(),
                        "createRdata from text failed near '" +
                        token->getString() + "': " + string(reason));
        break;
    case MasterToken::ERROR:
        callbacks.error(lexer.getSourceName(), lexer.getSourceLine(),
                        "createRdata from text failed: " +
                        token->getErrorText());
        break;
    default:
        // This case shouldn't happen based on how we use MasterLexer in
        // createRdata(), so we could assert() that here.  But since it
        // depends on detailed behavior of other classes, we treat the case
        // in a bit less harsh way.
        isc_throw(Unexpected, "bug: createRdata() saw unexpected token type");
    }
}
}

RdataPtr
createRdata(const RRType& rrtype, const RRClass& rrclass,
            MasterLexer& lexer, const Name* origin,
            MasterLoader::Options options,
            MasterLoaderCallbacks& callbacks)
{
    RdataPtr rdata;

    bool error_issued = false;
    try {
        rdata = RRParamRegistry::getRegistry().createRdata(
            rrtype, rrclass, lexer, origin, options, callbacks);
    } catch (const MasterLexer::LexerError& error) {
        fromtextError(error_issued, lexer, callbacks, &error.token_, "");
    } catch (const Exception& ex) {
        // Catching all isc::Exception is too broad, but right now we don't
        // have better granularity.  When we complete #2518 we can make this
        // finer.
        fromtextError(error_issued, lexer, callbacks, NULL, ex.what());
    }
    // Other exceptions mean a serious implementation bug or fatal system
    // error; it doesn't make sense to catch and try to recover from them
    // here.  Just propagate.

    // Consume to end of line / file.
    // Call callback via fromtextError once if there was an error.
    do {
        const MasterToken& token = lexer.getNextToken();
        switch (token.getType()) {
        case MasterToken::END_OF_LINE:
            return (rdata);
        case MasterToken::END_OF_FILE:
            callbacks.warning(lexer.getSourceName(), lexer.getSourceLine(),
                              "file does not end with newline");
            return (rdata);
        default:
            rdata.reset();      // we'll return NULL
            fromtextError(error_issued, lexer, callbacks, &token,
                          "extra input text");
            // Continue until we see EOL or EOF
        }
    } while (true);

    // We shouldn't reach here
    assert(false);
    return (RdataPtr()); // add explicit return to silence some compilers
}

int
compareNames(const Name& n1, const Name& n2) {
    size_t len1 = n1.getLength();
    size_t len2 = n2.getLength();
    size_t cmplen = min(len1, len2);

    for (size_t i = 0; i < cmplen; ++i) {
        uint8_t c1 = tolower(n1.at(i));
        uint8_t c2 = tolower(n2.at(i));
        if (c1 < c2) {
            return (-1);
        } else if (c1 > c2) {
            return (1);
        }
    }

    return ((len1 == len2) ? 0 : (len1 < len2) ? -1 : 1);
}

namespace generic {
struct GenericImpl {
    GenericImpl(const vector<uint8_t>& data) : data_(data) {}
    vector<uint8_t> data_;
};

Generic::Generic(isc::util::InputBuffer& buffer, size_t rdata_len) {
    if (rdata_len > MAX_RDLENGTH) {
        isc_throw(InvalidRdataLength, "RDLENGTH too large");
    }

    vector<uint8_t> data(rdata_len);
    if (rdata_len > 0) {
        buffer.readData(&data[0], rdata_len);
    }

    impl_ = new GenericImpl(data);
}

GenericImpl*
Generic::constructFromLexer(MasterLexer& lexer) {
    const MasterToken& token = lexer.getNextToken(MasterToken::STRING);
    if (token.getString() != "\\#") {
        isc_throw(InvalidRdataText,
                  "Missing the special token (\\#) for "
                  "unknown RDATA encoding");
    }

    // Initialize with an absurd value.
    uint32_t rdlen = 65536;

    try {
        rdlen = lexer.getNextToken(MasterToken::NUMBER).getNumber();
    } catch (const MasterLexer::LexerError&) {
        isc_throw(InvalidRdataLength,
                  "Unknown RDATA length is invalid");
    }

    if (rdlen > 65535) {
        isc_throw(InvalidRdataLength,
                  "Unknown RDATA length is out of range: " << rdlen);
    }

    vector<uint8_t> data;

    if (rdlen > 0) {
        string hex_txt;
        string hex_part;
        // Whitespace is allowed within hex data, so read to the end of input.
        while (true) {
            const MasterToken& token =
                lexer.getNextToken(MasterToken::STRING, true);
            if ((token.getType() == MasterToken::END_OF_FILE) ||
                (token.getType() == MasterToken::END_OF_LINE)) {
                // Unget the last read token as createRdata() expects us
                // to leave it at the end-of-line or end-of-file when we
                // return.
                lexer.ungetToken();
                break;
            }
            token.getString(hex_part);
            hex_txt.append(hex_part);
        }

        try {
            isc::util::encode::decodeHex(hex_txt, data);
        } catch (const isc::BadValue& ex) {
            isc_throw(InvalidRdataText,
                      "Invalid hex encoding of generic RDATA: " << ex.what());
        }
    }

    if (data.size() != rdlen) {
        isc_throw(InvalidRdataLength,
                  "Size of unknown RDATA hex data doesn't match RDLENGTH: "
                  << data.size() << " vs. " << rdlen);
    }

    return (new GenericImpl(data));
}

Generic::Generic(const std::string& rdata_string) :
    impl_(NULL)
{
    // We use auto_ptr here because if there is an exception in this
    // constructor, the destructor is not called and there could be a
    // leak of the GenericImpl that constructFromLexer() returns.
    std::auto_ptr<GenericImpl> impl_ptr(NULL);

    try {
        std::istringstream ss(rdata_string);
        MasterLexer lexer;
        lexer.pushSource(ss);

        impl_ptr.reset(constructFromLexer(lexer));

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for unknown RDATA: "
                      << rdata_string);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct unknown RDATA "
                  "from '" << rdata_string << "': " << ex.what());
    }

    impl_ = impl_ptr.release();
}

Generic::Generic(MasterLexer& lexer, const Name*,
                 MasterLoader::Options,
                 MasterLoaderCallbacks&) :
    impl_(constructFromLexer(lexer))
{
}

Generic::~Generic() {
    delete impl_;
}

Generic::Generic(const Generic& source) :
    Rdata(), impl_(new GenericImpl(*source.impl_))
{}

Generic&
// Our check is better than the usual if (this == &source),
// but cppcheck doesn't recognize it.
// cppcheck-suppress operatorEqToSelf
Generic::operator=(const Generic& source) {
    if (impl_ == source.impl_) {
        return (*this);
    }

    GenericImpl* newimpl = new GenericImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

namespace {
class UnknownRdataDumper {
public:
    UnknownRdataDumper(ostringstream& oss) : oss_(&oss) {}
    void operator()(const unsigned char d)
    {
        *oss_ << setw(2) << static_cast<unsigned int>(d);
    }
private:
    ostringstream* oss_;
};
}

string
Generic::toText() const {
    ostringstream oss;

    oss << "\\# " << impl_->data_.size() << " ";
    oss.fill('0');
    oss << right << hex;
    for_each(impl_->data_.begin(), impl_->data_.end(), UnknownRdataDumper(oss));

    return (oss.str());
}

void
Generic::toWire(isc::util::OutputBuffer& buffer) const {
    buffer.writeData(&impl_->data_[0], impl_->data_.size());
}

void
Generic::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeData(&impl_->data_[0], impl_->data_.size());
}

namespace {
inline int
compare_internal(const GenericImpl& lhs, const GenericImpl& rhs) {
    size_t this_len = lhs.data_.size();
    size_t other_len = rhs.data_.size();
    size_t len = (this_len < other_len) ? this_len : other_len;
    int cmp;

    // TODO: is there a need to check len - should we just assert?
    // (Depends if it is possible for rdata to have zero length)
    if ((len != 0) &&
        ((cmp = memcmp(&lhs.data_[0], &rhs.data_[0], len)) != 0)) {
        return (cmp);
    } else {
        return ((this_len == other_len) ? 0 :
                (this_len < other_len) ? -1 : 1);
    }
}
}

int
Generic::compare(const Rdata& other) const {
    const Generic& other_rdata = dynamic_cast<const Generic&>(other);

    return (compare_internal(*impl_, *other_rdata.impl_));
}

std::ostream&
operator<<(std::ostream& os, const Generic& rdata) {
    return (os << rdata.toText());
}
} // end of namespace generic

} // end of namespace rdata
}
}
