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
    MasterLexerImpl() : source_(NULL), paren_count_(0), last_was_eol_(false),
                        token_(Token::NOT_STARTED)
    {}

    std::vector<InputSourcePtr> sources_;
    InputSource* source_;       // current source
    size_t paren_count_;
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
State::wasLastEOL(const MasterLexer& lexer) const {
    return (lexer.impl_->last_was_eol_);
}

const MasterLexer::Token&
State::getToken(const MasterLexer& lexer) const {
    return (lexer.impl_->token_);
}

size_t
State::getParenCount(const MasterLexer& lexer) const {
    return (lexer.impl_->paren_count_);
}

class Start : public State {
public:
    Start() {}
    virtual const State* handle(MasterLexer& lexer,
                                MasterLexer::Options& options,
                                MasterLexer::Options orig_options) const;
};

class CRLF : public State {
public:
    CRLF() {}
    virtual const State* handle(MasterLexer& /*lexer*/,
                                MasterLexer::Options& /*options*/,
                                MasterLexer::Options /*orig_options*/) const
    {
        return (NULL);
    }
};

class String : public State {
public:
    String() {}
    virtual const State* handle(MasterLexer& /*lexer*/,
                                MasterLexer::Options& /*options*/,
                                MasterLexer::Options /*orig_options*/) const
    {
        return (NULL);
    }
};

namespace {
const Start START_STATE;
const CRLF CRLF_STATE;
const String STRING_STATE;
}

const State&
State::getInstance(ID state_id) {
    switch (state_id) {
    case Start:
        return (START_STATE);
    case CRLF:
        return (CRLF_STATE);
    case EatLine:
        return (CRLF_STATE);    // XXX
    case String:
        return (STRING_STATE);    // XXX
    }
}

inline void
cancelOptions(MasterLexer::Options& options,
              MasterLexer::Options canceled_options)
{
    options = static_cast<MasterLexer::Options>(
        options & static_cast<MasterLexer::Options>(~canceled_options));
}

const State*
Start::handle(MasterLexer& lexer, MasterLexer::Options& options,
              MasterLexer::Options orig_options) const
{
    while (true) {
        const int c = getLexerImpl(lexer)->source_->getChar();
        if (c == InputSource::END_OF_STREAM) {
            // TODO: handle unbalance cases
            getLexerImpl(lexer)->last_was_eol_ = false;
            getLexerImpl(lexer)->token_ = Token(Token::END_OF_FILE);
            return (NULL);
        } else if (c == ' ' || c == '\t') {
            if (getLexerImpl(lexer)->last_was_eol_ &&
                (options & MasterLexer::INITIAL_WS) != 0) {
                getLexerImpl(lexer)->last_was_eol_ = false;
                getLexerImpl(lexer)->token_ = Token(Token::INITIAL_WS);
                return (NULL);
            }
            continue;
        } else if (c == '\n') {
            if ((options & MasterLexer::END_OF_LINE) != 0) {
                getLexerImpl(lexer)->last_was_eol_ = true;
                getLexerImpl(lexer)->token_ = Token(Token::END_OF_LINE);
                return (NULL);
            }
        } else if (c == '(') {
            getLexerImpl(lexer)->last_was_eol_ = false;
            cancelOptions(options,
                          MasterLexer::END_OF_LINE | MasterLexer::INITIAL_WS);
            ++getLexerImpl(lexer)->paren_count_;
            continue;
        } else if (c == ')') {
            // TBD: unbalanced case
            --getLexerImpl(lexer)->paren_count_;
            if (getLexerImpl(lexer)->paren_count_ == 0) {
                options = orig_options;
            }
            continue;
        } else {
            getLexerImpl(lexer)->last_was_eol_ = false;
            return (&STRING_STATE);
        }
    }
}

} // namespace master_lexer_internal

} // end of namespace dns
} // end of namespace isc
