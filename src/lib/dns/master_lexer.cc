// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <exceptions/exceptions.h>

#include <dns/master_lexer.h>
#include <dns/master_lexer_inputsource.h>
#include <dns/master_lexer_state.h>

#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

#include <bitset>
#include <cassert>
#include <limits>
#include <string>
#include <vector>

namespace isc {
namespace dns {

// The definition of SOURCE_SIZE_UNKNOWN.  Note that we initialize it using
// a method of another library.  Technically, this could trigger a static
// initialization fiasco.  But in this particular usage it's very unlikely
// to happen because this value is expected to be used only as a return
// value of a MasterLexer's method, and its constructor needs definitions
// here.
const size_t MasterLexer::SOURCE_SIZE_UNKNOWN =
    std::numeric_limits<size_t>::max();

namespace {
typedef boost::shared_ptr<master_lexer_internal::InputSource> InputSourcePtr;
} // end unnamed namespace
using namespace master_lexer_internal;


struct MasterLexer::MasterLexerImpl {
    MasterLexerImpl() : source_(NULL), token_(MasterToken::NOT_STARTED),
                        total_size_(0), popped_size_(0),
                        paren_count_(0), last_was_eol_(true),
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
        separators_.set('"');
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

    void setTotalSize() {
        assert(source_ != NULL);
        if (total_size_ != SOURCE_SIZE_UNKNOWN) {
            const size_t current_size = source_->getSize();
            if (current_size != SOURCE_SIZE_UNKNOWN) {
                total_size_ += current_size;
            } else {
                total_size_ = SOURCE_SIZE_UNKNOWN;
            }
        }
    }

    std::vector<InputSourcePtr> sources_;
    InputSource* source_;       // current source (NULL if sources_ is empty)
    MasterToken token_;         // currently recognized token (set by a state)
    std::vector<char> data_;    // placeholder for string data

    // Keep track of the total size of all sources and characters that have
    // been read from sources already popped.
    size_t total_size_;         // accumulated size (# of chars) of sources
    size_t popped_size_;        // total size of sources that have been popped

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
    impl_->last_was_eol_ = true;
    impl_->setTotalSize();
    return (true);
}

void
MasterLexer::pushSource(std::istream& input) {
    try {
        impl_->sources_.push_back(InputSourcePtr(new InputSource(input)));
    } catch (const InputSource::OpenError& ex) {
        // Convert the "internal" exception to public one.
        isc_throw(Unexpected, "Failed to push a stream to lexer: " <<
                  ex.what());
    }
    impl_->source_ = impl_->sources_.back().get();
    impl_->has_previous_ = false;
    impl_->last_was_eol_ = true;
    impl_->setTotalSize();
}

void
MasterLexer::popSource() {
    if (impl_->sources_.empty()) {
        isc_throw(InvalidOperation,
                  "MasterLexer::popSource on an empty source");
    }
    impl_->popped_size_ += impl_->source_->getPosition();
    impl_->sources_.pop_back();
    impl_->source_ = impl_->sources_.empty() ? NULL :
        impl_->sources_.back().get();
    impl_->has_previous_ = false;
}

size_t
MasterLexer::getSourceCount() const {
    return (impl_->sources_.size());
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

size_t
MasterLexer::getTotalSourceSize() const {
    return (impl_->total_size_);
}

size_t
MasterLexer::getPosition() const {
    size_t position = impl_->popped_size_;
    BOOST_FOREACH(InputSourcePtr& src, impl_->sources_) {
        position += src->getPosition();
    }
    return (position);
}

const MasterToken&
MasterLexer::getNextToken(Options options) {
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
    impl_->token_ = MasterToken(MasterToken::NO_TOKEN_PRODUCED);
    // And get the token

    // This actually handles EOF internally too.
    const State* state = State::start(*this, options);
    if (state != NULL) {
        state->handle(*this);
    }
    // Make sure a token was produced. Since this Can Not Happen, we assert
    // here instead of throwing.
    assert(impl_->token_.getType() != MasterToken::ERROR ||
           impl_->token_.getErrorCode() != MasterToken::NO_TOKEN_PRODUCED);
    return (impl_->token_);
}

namespace {
inline MasterLexer::Options
optionsForTokenType(MasterToken::Type expect) {
    switch (expect) {
    case MasterToken::STRING:
        return (MasterLexer::NONE);
    case MasterToken::QSTRING:
        return (MasterLexer::QSTRING);
    case MasterToken::NUMBER:
        return (MasterLexer::NUMBER);
    default:
        isc_throw(InvalidParameter,
                  "expected type for getNextToken not supported: " << expect);
    }
}
}

const MasterToken&
MasterLexer::getNextToken(MasterToken::Type expect, bool eol_ok) {
    // Get the next token, specifying an appropriate option corresponding to
    // the expected type.  The result should be set in impl_->token_.
    getNextToken(optionsForTokenType(expect));

    if (impl_->token_.getType() == MasterToken::ERROR) {
        if (impl_->token_.getErrorCode() == MasterToken::NUMBER_OUT_OF_RANGE) {
            ungetToken();
        }
        throw LexerError(__FILE__, __LINE__, impl_->token_);
    }

    const bool is_eol_like =
        (impl_->token_.getType() == MasterToken::END_OF_LINE ||
         impl_->token_.getType() == MasterToken::END_OF_FILE);
    if (eol_ok && is_eol_like) {
        return (impl_->token_);
    }
    if (impl_->token_.getType() == MasterToken::STRING &&
        expect == MasterToken::QSTRING) {
        return (impl_->token_);
    }
    if (impl_->token_.getType() != expect) {
        ungetToken();
        if (is_eol_like) {
            throw LexerError(__FILE__, __LINE__,
                             MasterToken(MasterToken::UNEXPECTED_END));
        }
        assert(expect == MasterToken::NUMBER);
        throw LexerError(__FILE__, __LINE__,
                         MasterToken(MasterToken::BAD_NUMBER));
    }

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

namespace {
const char* const error_text[] = {
    "lexer not started",        // NOT_STARTED
    "unbalanced parentheses",   // UNBALANCED_PAREN
    "unexpected end of input",  // UNEXPECTED_END
    "unbalanced quotes",        // UNBALANCED_QUOTES
    "no token produced",        // NO_TOKEN_PRODUCED
    "number out of range",      // NUMBER_OUT_OF_RANGE
    "not a valid number",       // BAD_NUMBER
    "unexpected quotes"         // UNEXPECTED_QUOTES
};
const size_t error_text_max_count = sizeof(error_text) / sizeof(error_text[0]);
} // end unnamed namespace

std::string
MasterToken::getErrorText() const {
    if (type_ != ERROR) {
        isc_throw(InvalidOperation,
                  "MasterToken::getErrorText() for non error type");
    }

    // The class integrity ensures the following:
    assert(val_.error_code_ < error_text_max_count);
    return (error_text[val_.error_code_]);
}

namespace master_lexer_internal {
// Below we implement state classes for state transitions of MasterLexer.
// Note that these need to be defined here so that they can refer to
// the details of MasterLexerImpl.

bool
State::wasLastEOL(const MasterLexer& lexer) const {
    return (lexer.impl_->last_was_eol_);
}

const MasterToken&
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
    virtual void handle(MasterLexer& lexer) const {
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
        getLexerImpl(lexer)->token_ = MasterToken(MasterToken::END_OF_LINE);
        getLexerImpl(lexer)->last_was_eol_ = true;
    }
};

class String : public State {
public:
    String() {}
    virtual ~String() {}      // see the base class for the destructor
    virtual void handle(MasterLexer& lexer) const;
};

class QString : public State {
public:
    QString() {}
    virtual ~QString() {}      // see the base class for the destructor
    virtual void handle(MasterLexer& lexer) const;
};

class Number : public State {
public:
    Number() {}
    virtual ~Number() {}
    virtual void handle(MasterLexer& lexer) const;
};

// We use a common instance of a each state in a singleton-like way to save
// construction overhead.  They are not singletons in its strict sense as
// we don't prohibit direct construction of these objects.  But that doesn't
// matter much anyway, because the definitions are completely hidden within
// this file.
const CRLF CRLF_STATE;
const String STRING_STATE;
const QString QSTRING_STATE;
const Number NUMBER_STATE;
} // end unnamed namespace

const State&
State::getInstance(ID state_id) {
    switch (state_id) {
    case CRLF:
        return (CRLF_STATE);
    case String:
        return (STRING_STATE);
    case QString:
        return (QSTRING_STATE);
    case Number:
        return (NUMBER_STATE);
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
                lexerimpl.token_ = MasterToken(MasterToken::UNBALANCED_PAREN);
                paren_count = 0; // reset to 0; this helps in lenient mode.
                return (NULL);
            }
            lexerimpl.token_ = MasterToken(MasterToken::END_OF_FILE);
            return (NULL);
        } else if (c == ' ' || c == '\t') {
            // If requested and we are not in (), recognize the initial space.
            if (lexerimpl.last_was_eol_ && paren_count == 0 &&
                (options & MasterLexer::INITIAL_WS) != 0) {
                lexerimpl.last_was_eol_ = false;
                lexerimpl.token_ = MasterToken(MasterToken::INITIAL_WS);
                return (NULL);
            }
        } else if (c == '\n') {
            lexerimpl.last_was_eol_ = true;
            if (paren_count == 0) { // we don't recognize EOL if we are in ()
                lexerimpl.token_ = MasterToken(MasterToken::END_OF_LINE);
                return (NULL);
            }
        } else if (c == '\r') {
            if (paren_count == 0) { // check if we are in () (see above)
                return (&CRLF_STATE);
            }
        } else if (c == '"') {
            if ((options & MasterLexer::QSTRING) != 0) {
                lexerimpl.last_was_eol_ = false;
                return (&QSTRING_STATE);
            } else {
                lexerimpl.token_ = MasterToken(MasterToken::UNEXPECTED_QUOTES);
                return (NULL);
            }
        } else if (c == '(') {
            lexerimpl.last_was_eol_ = false;
            ++paren_count;
        } else if (c == ')') {
            lexerimpl.last_was_eol_ = false;
            if (paren_count == 0) {
                lexerimpl.token_ = MasterToken(MasterToken::UNBALANCED_PAREN);
                return (NULL);
            }
            --paren_count;
        } else if ((options & MasterLexer::NUMBER) != 0 &&isdigit(c)) {
            lexerimpl.last_was_eol_ = false;
            // this character will be handled in the number state
            lexerimpl.source_->ungetChar();
            return (&NUMBER_STATE);
        } else {
            // this character will be handled in the string state
            lexerimpl.source_->ungetChar();
            lexerimpl.last_was_eol_ = false;
            return (&STRING_STATE);
        }
        // no code should be here; we just continue the loop.
    }
}

void
String::handle(MasterLexer& lexer) const {
    std::vector<char>& data = getLexerImpl(lexer)->data_;
    data.clear();

    bool escaped = false;
    while (true) {
        const int c = getLexerImpl(lexer)->skipComment(
            getLexerImpl(lexer)->source_->getChar(), escaped);

        if (getLexerImpl(lexer)->isTokenEnd(c, escaped)) {
            getLexerImpl(lexer)->source_->ungetChar();
            // make sure it nul-terminated as a c-str (excluded from token
            // data).
            data.push_back('\0');
            getLexerImpl(lexer)->token_ =
                MasterToken(&data.at(0), data.size() - 1);
            return;
        }
        escaped = (c == '\\' && !escaped);
        data.push_back(c);
    }
}

void
QString::handle(MasterLexer& lexer) const {
    MasterToken& token = getLexerImpl(lexer)->token_;
    std::vector<char>& data = getLexerImpl(lexer)->data_;
    data.clear();

    bool escaped = false;
    while (true) {
        const int c = getLexerImpl(lexer)->source_->getChar();
        if (c == InputSource::END_OF_STREAM) {
            token = MasterToken(MasterToken::UNEXPECTED_END);
            return;
        } else if (c == '"') {
            if (escaped) {
                // found escaped '"'. overwrite the preceding backslash.
                assert(!data.empty());
                escaped = false;
                data.back() = '"';
            } else {
                // make sure it nul-terminated as a c-str (excluded from token
                // data).  This also simplifies the case of an empty string.
                data.push_back('\0');
                token = MasterToken(&data.at(0), data.size() - 1, true);
                return;
            }
        } else if (c == '\n' && !escaped) {
            getLexerImpl(lexer)->source_->ungetChar();
            token = MasterToken(MasterToken::UNBALANCED_QUOTES);
            return;
        } else {
            escaped = (c == '\\' && !escaped);
            data.push_back(c);
        }
    }
}

void
Number::handle(MasterLexer& lexer) const {
    MasterToken& token = getLexerImpl(lexer)->token_;

    // It may yet turn out to be a string, so we first
    // collect all the data
    bool digits_only = true;
    std::vector<char>& data = getLexerImpl(lexer)->data_;
    data.clear();
    bool escaped = false;

    while (true) {
        const int c = getLexerImpl(lexer)->skipComment(
            getLexerImpl(lexer)->source_->getChar(), escaped);
        if (getLexerImpl(lexer)->isTokenEnd(c, escaped)) {
            getLexerImpl(lexer)->source_->ungetChar();
            // We need to close the string whether it's digits-only (for
            // lexical_cast) or not (see String::handle()).
            data.push_back('\0');
            if (digits_only) {
                try {
                    const uint32_t number32 =
                        boost::lexical_cast<uint32_t, const char*>(&data[0]);
                    token = MasterToken(number32);
                } catch (const boost::bad_lexical_cast&) {
                    // Since we already know we have only digits,
                    // range should be the only possible problem.
                    token = MasterToken(MasterToken::NUMBER_OUT_OF_RANGE);
                }
            } else {
                token = MasterToken(&data.at(0), data.size() - 1);
            }
            return;
        }
        if (!isdigit(c)) {
            digits_only = false;
        }
        escaped = (c == '\\' && !escaped);
        data.push_back(c);
    }
}

} // namespace master_lexer_internal

} // end of namespace dns
} // end of namespace isc
