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

#include <exceptions/exceptions.h>

#include <dns/master_lexer.h>

#include <boost/shared_ptr.hpp>

#include <cassert>
#include <string>
#include <sstream>
#include <vector>

namespace isc {
namespace dns {

namespace master_lexer_internal {
std::string
createStreamName(std::istream& input_stream) {
    std::stringstream ss;
    ss << "stream-" << &input_stream;
    return (ss.str());
}

// A fake version of InputSource until #2369 is ready.  This class only
// provides some interfaces and doesn't manipulate the input source further.
class InputSource {
public:
    InputSource(std::istream& input_stream) :
        name_(createStreamName(input_stream))
    {}
    InputSource(const char* filename) : name_(filename) {}
    const std::string& getName() const { return (name_); }
    size_t getCurrentLine() const { return (1); }

private:
    const std::string name_;
};

typedef boost::shared_ptr<InputSource> InputSourcePtr;
}
using namespace master_lexer_internal;

struct MasterLexer::MasterLexerImpl {
    std::vector<InputSourcePtr> sources_;
};

MasterLexer::MasterLexer() : impl_(new MasterLexerImpl) {
}

MasterLexer::~MasterLexer() {
    delete impl_;
}

void
MasterLexer::open(const char* filename) {
    impl_->sources_.push_back(InputSourcePtr(new InputSource(filename)));
}

void
MasterLexer::open(std::istream& input) {
    impl_->sources_.push_back(InputSourcePtr(new InputSource(input)));
}

void
MasterLexer::close() {
    if (impl_->sources_.empty()) {
        isc_throw(InvalidOperation, "MasterLexer::close on an empty source");
    }
    impl_->sources_.pop_back();
}

std::string
MasterLexer::getSourceName() const {
    if (impl_->sources_.empty()) {
        return (std::string());
    }
    return (impl_->sources_.back()->getName());
}

size_t
MasterLexer::getSourceLine() const {
    if (impl_->sources_.empty()) {
        return (0);
    }
    return (impl_->sources_.back()->getCurrentLine());
}

namespace {
const char* const error_text[] = {
    "lexer not started",        // NOT_STARTED
    "unbalanced parentheses",   // UNBALANCED_PAREN
    "unexpected end of input",  // UNEXPECTED_END
    "unbalanced quotes"         // UNBALANCED_QUOTES
};
const size_t error_text_max_count = sizeof(error_text) / sizeof(error_text[0]);
}

std::string
MasterLexer::Token::getErrorText() const {
    if (type_ != ERROR) {
        isc_throw(InvalidOperation,
                  "Token::getErrorText() for non error type");
    }

    // The class integrity ensures the following:
    assert(val_.error_code_ < error_text_max_count);
    return (error_text[val_.error_code_]);
}

} // end of namespace dns
} // end of namespace isc
