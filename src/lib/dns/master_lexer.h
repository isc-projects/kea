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

#ifndef MASTER_LEXER_H
#define MASTER_LEXER_H 1

#include <exceptions/exceptions.h>

#include <string>

#include <stdint.h>

namespace isc {
namespace dns {

class MasterLexer {
public:
    class Token;       // we define it separate for better readability
};

class MasterLexer::Token {
public:
    enum Type {
        ERROR,
        END_OF_LINE,
        END_OF_FILE,
        INITIAL_WS,
        STRING,
        QSTRING,
        NUMBER
    };

    struct StringRegion {
        const char* beg;
        size_t len;
    };

    explicit Token(Type type) : type_(type) {
        if (type >= STRING) {
            isc_throw(InvalidParameter, "Token per-type constructor "
                      "called with invalid type: " << type);
        }
    }
    Token(const char* str_beg, size_t str_len, bool quoted = false) :
        type_(quoted ? QSTRING : STRING)
    {
        val_.str_region_.beg = str_beg;
        val_.str_region_.len = str_len;
    }
    explicit Token(uint32_t number) : type_(NUMBER) {
        val_.number_ = number;
    }

    Type getType() const { return (type_); }
    std::string getString() const {
        if (type_ != STRING && type_ != QSTRING) {
            isc_throw(InvalidOperation,
                      "Token::getString() for non string-variant type");
        }
        return (std::string(val_.str_region_.beg,
                            val_.str_region_.beg + val_.str_region_.len));
    }
    const StringRegion& getStringRegion() const {
        if (type_ != STRING && type_ != QSTRING) {
            isc_throw(InvalidOperation,
                      "Token::getString() for non string-variant type");
        }
        return (val_.str_region_);
    }
    uint32_t getNumber() const {
        if (type_ != NUMBER) {
            isc_throw(InvalidOperation,
                      "Token::getNumber() for non number type");
        }
        return (val_.number_);
    }

private:
    Type type_;
    union {
        StringRegion str_region_;
        uint32_t number_;
    } val_;
};

} // namespace dns
} // namespace isc
#endif  // MASTER_LEXER_H

// Local Variables:
// mode: c++
// End:
