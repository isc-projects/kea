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
#include <dns/master_lexer_inputsource.h>
#include <dns/master_lexer_state.h>

#include <boost/shared_ptr.hpp>

#include <cassert>
#include <string>
#include <sstream>
#include <vector>

namespace isc {
namespace dns {

namespace {
typedef boost::shared_ptr<master_lexer_internal::InputSource> InputSourcePtr;
}
using namespace master_lexer_internal;

struct MasterLexer::MasterLexerImpl {
    MasterLexerImpl() : source_(NULL), last_was_eol_(false),
                        token_(Token::NOT_STARTED)
    {}

    std::vector<InputSourcePtr> sources_;
    InputSource* source_;       // current source
    bool last_was_eol_;
    Token token_;
};

MasterLexer::MasterLexer() : impl_(new MasterLexerImpl) {
}

MasterLexer::~MasterLexer() {
    delete impl_;
}

bool
MasterLexer::pushSource(const char* filename, std::string* error) {
    if (filename == NULL) {
        isc_throw(InvalidParameter,
                  "NULL filename for MasterLexer::pushSource");
    }
    try {
        impl_->sources_.push_back(InputSourcePtr(new InputSource(filename)));
    } catch (const InputSource::OpenError& ex) {
        if (error != NULL) {
            *error = ex.what();
        }
        return (false);
    }

    impl_->sources_.push_back(InputSourcePtr(new InputSource(filename)));
    impl_->source_ = impl_->sources_.back().get();
    return (true);
}

void
MasterLexer::pushSource(std::istream& input) {
    impl_->sources_.push_back(InputSourcePtr(new InputSource(input)));
    impl_->source_ = impl_->sources_.back().get();
}

void
MasterLexer::popSource() {
    if (impl_->sources_.empty()) {
        isc_throw(InvalidOperation,
                  "MasterLexer::popSource on an empty source");
    }
    impl_->sources_.pop_back();
    impl_->source_ = impl_->sources_.empty() ? NULL :
        impl_->sources_.back().get();
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

namespace master_lexer_internal {
typedef MasterLexer::Token Token; // convenience shortcut

bool
State::wasLastEOL(MasterLexer& lexer) const {
    return (lexer.impl_->last_was_eol_);
}

const MasterLexer::Token
State::getToken(MasterLexer& lexer) const {
    return (lexer.impl_->token_);
}

class Start : public State {
public:
    Start() {}
    virtual const State* handle(MasterLexer& lexer) const {
        const int c = getLexerImpl(lexer)->source_->getChar();
        if (c < 0) {
            // TODO: handle unbalance cases
            getLexerImpl(lexer)->last_was_eol_ = false;
            getLexerImpl(lexer)->token_ = Token(Token::END_OF_FILE);
            return (NULL);
        } else if (c == '\n') {
            getLexerImpl(lexer)->last_was_eol_ = true;
            getLexerImpl(lexer)->token_ = Token(Token::END_OF_LINE);
            return (NULL);
        }
        return (&State::getInstance(State::CRLF)); // placeholder
    }
};

class CRLF : public State {
public:
    CRLF() {}
    virtual const State* handle(MasterLexer& /*lexer*/) const {
        return (NULL);
    }
};

namespace {
const Start START_STATE;
const CRLF CRLF_STARTE;
}

const State&
State::getInstance(ID /*state_id*/) {
    return (START_STATE);
}


} // namespace master_lexer_internal

} // end of namespace dns
} // end of namespace isc
