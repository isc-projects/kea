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
#include <vector>

namespace isc {
namespace dns {

namespace {
typedef boost::shared_ptr<master_lexer_internal::InputSource> InputSourcePtr;
}
using namespace master_lexer_internal;

struct MasterLexer::MasterLexerImpl {
    MasterLexerImpl() : source_(NULL), token_(Token::NOT_STARTED),
                        paren_count_(0), last_was_eol_(false)
    {}

    // A helper method to skip possible comments toward the end of EOL or EOF.
    // commonly used by state classes.  It returns the corresponding "end-of"
    // character in case it's a comment; otherwise it simply returns the
    // current character.
    int skipComment(int c) {
        if (c == ';') {
            while (true) {
                c = source_->getChar();
                if (c == '\n' || c == InputSource::END_OF_STREAM) {
                    return (c);
                }
            }
        }
        return (c);
    }

    std::vector<InputSourcePtr> sources_;
    InputSource* source_;       // current source (NULL if sources_ is empty)
    Token token_;               // currently recognized token (set by a state)

    // These are used in states, and defined here only as a placeholder.
    // The main lexer class does not need these members.
    size_t paren_count_;        // nest count of the parentheses
    bool last_was_eol_; // whether the lexer just passed an end-of-line
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
// Below we implement state classes for state transitions of MasterLexer.
// Note that these need to be defined here so that they can refer to
// the details of MasterLexerImpl.

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

namespace {
class CRLF : public State {
public:
    CRLF() {}
    virtual const State* handle(MasterLexer& lexer) const {
        // We've just seen '\r'.  If this is part of a sequence of '\r\n',
        // we combine them as a single END-OF-LINE.  Otherwise we treat the
        // single '\r' as an EOL and continue tokeniziation from the character
        // immediately after '\r'.  One tricky case is that there's a comment
        // between '\r' and '\n'.  This implementation combines these
        // characters and treats them as a single EOL (the behavior derived
        // from BIND 9).  Technically this may not be correct, but in practice
        // the caller wouldn't distinguish this case from the case it has
        // two EOLs, so we simplify the process.
        const int c = getLexerImpl(lexer)->skipComment(
            getLexerImpl(lexer)->source_->getChar());
        if (c != '\n') {
            getLexerImpl(lexer)->source_->ungetChar();
        }
        getLexerImpl(lexer)->token_ = Token(Token::END_OF_LINE);
        getLexerImpl(lexer)->last_was_eol_ = true;
        return (NULL);
    }
};

// Currently this is provided mostly as a place holder
class String : public State {
public:
    String() {}
    virtual const State* handle(MasterLexer& /*lexer*/) const {
        return (NULL);
    }
};

// We use a common instance of a each state in a singleton-like way to save
// construction overhead.  They are not singletons in its strict sense as
// we don't prohibit direct construction of these objects.  But that doesn't
// matter much anyway, because the definitions are completely hidden within
// this file.
const CRLF CRLF_STATE;
const String STRING_STATE;
}

const State&
State::getInstance(ID state_id) {
    switch (state_id) {
    case CRLF:
        return (CRLF_STATE);
    case String:
        return (STRING_STATE);
    }

    // This is a bug of the caller, and this method is only expected to be
    // used by tests, so we just forcefully make it fail by asserting the
    // condition.
    assert(false);
    return (STRING_STATE); // a dummy return, to silence some compilers.
}

const State*
State::start(MasterLexer& lexer, MasterLexer::Options options) {
    // define some shortcuts
    MasterLexer::MasterLexerImpl& lexerimpl = *lexer.impl_;
    size_t& paren_count = lexerimpl.paren_count_;

    while (true) {
        const int c = lexerimpl.skipComment(lexerimpl.source_->getChar());
        if (c == InputSource::END_OF_STREAM) {
            lexerimpl.last_was_eol_ = false;
            if (paren_count != 0) {
                lexerimpl.token_ = Token(Token::UNBALANCED_PAREN);
                paren_count = 0; // reset to 0; this helps in lenient mode.
                return (NULL);
            }
            lexerimpl.token_ = Token(Token::END_OF_FILE);
            return (NULL);
        } else if (c == ' ' || c == '\t') {
            // If requested and we are not in (), recognize the initial space.
            if (lexerimpl.last_was_eol_ && paren_count == 0 &&
                (options & MasterLexer::INITIAL_WS) != 0) {
                lexerimpl.last_was_eol_ = false;
                lexerimpl.token_ = Token(Token::INITIAL_WS);
                return (NULL);
            }
        } else if (c == '\n') {
            lexerimpl.last_was_eol_ = true;
            if (paren_count == 0) { // we don't recognize EOL if we are in ()
                lexerimpl.token_ = Token(Token::END_OF_LINE);
                return (NULL);
            }
        } else if (c == '\r') {
            if (paren_count == 0) { // check if we are in () (see above)
                return (&CRLF_STATE);
            }
        } else if (c == '(') {
            lexerimpl.last_was_eol_ = false;
            ++paren_count;
        } else if (c == ')') {
            lexerimpl.last_was_eol_ = false;
            if (paren_count == 0) {
                lexerimpl.token_ = Token(Token::UNBALANCED_PAREN);
                return (NULL);
            }
            --paren_count;
        } else {
            // Note: in #2373 we should probably ungetChar().
            lexerimpl.last_was_eol_ = false;
            return (&STRING_STATE);
        }
        // no code should be here; we just continue the loop.
    }
}

} // namespace master_lexer_internal

} // end of namespace dns
} // end of namespace isc
