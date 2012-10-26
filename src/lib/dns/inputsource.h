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

#include <iostream>
#include <string>
#include <vector>

namespace isc {
namespace dns {
namespace master_lexer_internal {

class InputSource {
public:
    InputSource(std::istream& input, const std::string& name) :
        input_(input),
        name_(name),
        at_eof_(false),
        line_(1),
        saved_line_(line_),
        buffer_pos_(buffer_.size())
    {}

    const std::string& getName() {
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

    int getChar();
    void ungetChar();
    void ungetAll();

private:
    std::istream& input_;
    const std::string name_;
    bool at_eof_;
    size_t line_;
    size_t saved_line_;

    std::vector<char> buffer_;
    size_t buffer_pos_;
};

} // namespace master_lexer_internal
} // namespace dns
} // namespace isc

#endif  // DNS_INPUTSOURCE_H

// Local Variables:
// mode: c++
// End:
