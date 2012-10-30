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

#ifndef DNS_INPUTSOURCE_H
#define DNS_INPUTSOURCE_H 1

#include <exceptions/exceptions.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace isc {
namespace dns {
namespace master_lexer_internal {

class InputSource {
public:
    InputSource(std::istream& input_stream);
    InputSource(const char* filename);

    ~InputSource();

    const std::string& getName() const {
        return (name_);
    }

    bool atEOF() const {
        return (at_eof_);
    }

    size_t getCurrentLine() const {
        return (line_);
    }

    void saveLine() {
        saved_line_ = line_;
    }

    /// \brief Exception thrown when ungetChar() is made to go before
    /// the start of buffer.
    struct UngetError : public OutOfRange {
        UngetError(const char* file, size_t line, const char* what) :
            OutOfRange(file, line, what)
        {}
    };

    int getChar();
    void ungetChar();
    void ungetAll();

private:
    bool at_eof_;
    size_t line_;
    size_t saved_line_;

    std::vector<char> buffer_;
    size_t buffer_pos_;

    std::string name_;
    std::fstream file_stream_;
    std::istream& input_;
};

} // namespace master_lexer_internal
} // namespace dns
} // namespace isc

#endif  // DNS_INPUTSOURCE_H

// Local Variables:
// mode: c++
// End:
