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

#include <bitset>
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
                        paren_count_(0), last_was_eol_(false),
                        has_previous_(false),
                        previous_paren_count_(0),
                        previous_was_eol_(false)
    {
        separators_.set('\r');
        separators_.set('\n');
        separators_.set(' ');
        separators_.set('\t');
        separators_.set('(');
        separators_.set(')');
        esc_separators_.set('\r');
        esc_separators_.set('\n');
    }

    // A helper method to skip possible comments toward the end of EOL or EOF.
    // commonly used by state classes.  It returns the corresponding "end-of"
    // character in case it's a comment; otherwise it simply returns the
    // current character.
    int skipComment(int c, bool escaped = false) {
        if (c == ';' && !escaped) {
            while (true) {
                c = source_->getChar();
                if (c == '\n' || c == InputSource::END_OF_STREAM) {
                    return (c);
                }
            }
        }
        return (c);
    }

    bool isTokenEnd(int c, bool escaped) {
        // Special case of EOF (end of stream); this is not in the bitmaps
        if (c == InputSource::END_OF_STREAM) {
            return (true);
        }
        // In this implementation we only ensure the behavior for unsigned
        // range of characters, so we restrict the range of the values up to
        // 0x7f = 127
        return (escaped ? esc_separators_.test(c & 0x7f) :
                separators_.test(c & 0x7f));
    }

    std::vector<InputSourcePtr> sources_;
    InputSource* source_;       // current source (NULL if sources_ is empty)
    Token token_;               // currently recognized token (set by a state)
    std::vector<char> data_;    // placeholder for string data

    // These are used in states, and defined here only as a placeholder.
    // The main lexer class does not need these members.
    size_t paren_count_;        // nest count of the parentheses
    bool last_was_eol_; // whether the lexer just passed an end-of-line

    // Bitmaps that gives whether a given (positive) character should be
    // considered a separator of a string/number token.  The esc_ version
    // is a subset of the other, excluding characters that can be ignored
    // if escaped by a backslash.  See isTokenEnd() for the bitmap size.
    std::bitset<128> separators_;
    std::bitset<128> esc_separators_;

    // These are to allow restoring state before previous token.
    bool has_previous_;
    size_t previous_paren_count_;
    bool previous_was_eol_;
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
    impl_->has_previous_ = false;
    return (true);
}

void
MasterLexer::pushSource(std::istream& input) {
    impl_->sources_.push_back(InputSourcePtr(new InputSource(input)));
    impl_->source_ = impl_->sources_.back().get();
    impl_->has_previous_ = false;
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
    impl_->has_previous_ = false;
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

MasterLexer::Token
MasterLexer::getNextToken(Options options) {
    // If the source is not available
    if (impl_->source_ == NULL) {
        isc_throw(isc::InvalidOperation, "No source to read tokens from");
    }
    // Store the current state so we can restore it in ungetToken
    impl_->previous_paren_count_ = impl_->paren_count_;
    impl_->previous_was_eol_ = impl_->last_was_eol_;
    impl_->source_->mark();
    impl_->has_previous_ = true;
    // Reset the token now. This is to check a token was actually produced.
    // This is debugging aid.
    impl_->token_ = Token(Token::NO_TOKEN_PRODUCED);
    // And get the token

    // This actually handles EOF internally too.
    for (const State *state = start(options); state != NULL;
         state = state->handle(*this)) {
        // Do nothing here. All is handled in the for cycle header itself.
    }
    // Make sure a token was produced. Since this Can Not Happen, we assert
    // here instead of throwing.
    assert(impl_->token_.getType() != Token::ERROR ||
           impl_->token_.getErrorCode() != Token::NO_TOKEN_PRODUCED);
    return (impl_->token_);
}

void
MasterLexer::ungetToken() {
    if (impl_->has_previous_) {
        impl_->has_previous_ = false;
        impl_->source_->ungetAll();
        impl_->last_was_eol_ = impl_->previous_was_eol_;
        impl_->paren_count_ = impl_->previous_paren_count_;
    } else {
        isc_throw(isc::InvalidOperation, "No token to unget ready");
    }
}

const State*
MasterLexer::start(Options options) {
    return (State::start(*this, options));
}

namespace {
const char* const error_text[] = {
    "lexer not started",        // NOT_STARTED
    "unbalanced parentheses",   // UNBALANCED_PAREN
    "unexpected end of input",  // UNEXPECTED_END
    "unbalanced quotes",        // UNBALANCED_QUOTES
    "no token produced"         // NO_TOKEN_PRODUCED
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
    virtual ~CRLF() {}          // see the base class for the destructor
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

class String : public State {
public:
    String() {}
    virtual ~String() {}      // see the base class for the destructor
    virtual const State* handle(MasterLexer& lexer) const;
};

class QString : public State {
public:
    QString() {}
    virtual ~QString() {}      // see the base class for the destructor
    virtual const State* handle(MasterLexer& lexer) const;
};

// We use a common instance of a each state in a singleton-like way to save
// construction overhead.  They are not singletons in its strict sense as
// we don't prohibit direct construction of these objects.  But that doesn't
// matter much anyway, because the definitions are completely hidden within
// this file.
const CRLF CRLF_STATE;
const String STRING_STATE;
const QString QSTRING_STATE;
}

const State&
State::getInstance(ID state_id) {
    switch (state_id) {
    case CRLF:
        return (CRLF_STATE);
    case String:
        return (STRING_STATE);
    case QString:
        return (QSTRING_STATE);
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

    // Note: the if-else in the loop is getting complicated.  When we complete
    // #2374, revisit the organization to see if we need a fundamental
    // refactoring.
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
        } else if (c == '"' && (options & MasterLexer::QSTRING) != 0) {
            lexerimpl.last_was_eol_ = false;
            return (&QSTRING_STATE);
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
            // this character will be handled in the string state
            lexerimpl.source_->ungetChar();
            lexerimpl.last_was_eol_ = false;
            return (&STRING_STATE);
        }
        // no code should be here; we just continue the loop.
    }
}

const State*
String::handle(MasterLexer& lexer) const {
    std::vector<char>& data = getLexerImpl(lexer)->data_;
    data.clear();

    bool escaped = false;
    while (true) {
        const int c = getLexerImpl(lexer)->skipComment(
            getLexerImpl(lexer)->source_->getChar(), escaped);

        if (getLexerImpl(lexer)->isTokenEnd(c, escaped)) {
            getLexerImpl(lexer)->source_->ungetChar();
            getLexerImpl(lexer)->token_ =
                MasterLexer::Token(&data.at(0), data.size());
            return (NULL);
        }
        escaped = (c == '\\' && !escaped);
        data.push_back(c);
    }
}

const State*
QString::handle(MasterLexer& lexer) const {
    MasterLexer::Token& token = getLexerImpl(lexer)->token_;
    std::vector<char>& data = getLexerImpl(lexer)->data_;
    data.clear();

    bool escaped = false;
    while (true) {
        const int c = getLexerImpl(lexer)->source_->getChar();
        if (c == InputSource::END_OF_STREAM) {
            token = Token(Token::UNEXPECTED_END);
            return (NULL);
        } else if (c == '"') {
            if (escaped) {
                // found escaped '"'. overwrite the preceding backslash.
                assert(!data.empty());
                escaped = false;
                data.back() = '"';
            } else {
                token = MasterLexer::Token(&data.at(0), data.size(), true);
                return (NULL);
            }
        } else if (c == '\n' && !escaped) {
            getLexerImpl(lexer)->source_->ungetChar();
            token = Token(Token::UNBALANCED_QUOTES);
            return (NULL);
        } else {
            escaped = (c == '\\' && !escaped);
            data.push_back(c);
        }
    }
}

namespace {

// A fake state that just eats something from the input, pushes
// a given token and calls a callback if it is set. It refers to
// another state to return.
class FakeState : public State {
public:
    FakeState(const State* next, size_t eat_chars,
              MasterLexer::Token* token,
              int paren_change, const bool* set_eol,
              const boost::function<void (const std::string&)>& callback) :
        next_(next),
        eat_chars_(eat_chars),
        token_(token),
        paren_change_(paren_change),
        set_eol_(set_eol),
        callback_(callback)
    {}
    virtual const State* handle(MasterLexer& lexer) const {
        std::string input;
        for (size_t i = 0; i < eat_chars_; ++i) {
            input += getLexerImpl(lexer)->source_->getChar();
        }
        if (!callback_.empty()) {
            callback_(input);
        }
        if (token_ != NULL) {
            getLexerImpl(lexer)->token_ = *token_;
        }
        getLexerImpl(lexer)->paren_count_ += paren_change_;
        if (set_eol_ != NULL) {
            getLexerImpl(lexer)->last_was_eol_ = *set_eol_;
        }
        return (next_);
    }
private:
    const State* const next_;
    size_t eat_chars_;
    MasterLexer::Token* const token_;
    const int paren_change_;
    const bool* const set_eol_;
    const boost::function<void (const std::string&)> callback_;
};

}

State*
State::getFakeState(const State* next, size_t eat_chars,
                    MasterLexer::Token* token,
                    int paren_change, const bool* set_eol,
                    const boost::function<void (const std::string&)>& callback)
{
    // Just allocate new FakeState with the parameters.
    return (new FakeState(next, eat_chars, token, paren_change, set_eol,
                          callback));
}

} // namespace master_lexer_internal

} // end of namespace dns
} // end of namespace isc
