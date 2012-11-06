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

#include <dns/master_lexer_inputsource.h>

#include <cerrno>
#include <cstring>

namespace isc {
namespace dns {
namespace master_lexer_internal {

namespace { // unnamed namespace

std::string
createStreamName(const std::istream& input_stream) {
     std::stringstream ss;
     ss << "stream-" << &input_stream;
     return (ss.str());
}

} // end of unnamed namespace

InputSource::InputSource(std::istream& input_stream) :
    at_eof_(false),
    line_(1),
    saved_line_(line_),
    buffer_pos_(0),
    name_(createStreamName(input_stream)),
    input_(input_stream)
{}

InputSource::InputSource(const char* filename) :
    at_eof_(false),
    line_(1),
    saved_line_(line_),
    buffer_pos_(0),
    name_(filename),
    input_(file_stream_)
{
    errno = 0;
    file_stream_.open(filename);
    if (file_stream_.fail()) {
        std::string error_txt("Error opening the input source file: ");
        error_txt += filename;
        if (errno != 0) {
            error_txt += "; possible cause: ";
            error_txt += std::strerror(errno);
        }
        isc_throw(OpenError, error_txt);
    }
}

InputSource::~InputSource()
{
    if (file_stream_.is_open()) {
        file_stream_.close();
    }
}

int
InputSource::getChar() {
    if (buffer_pos_ == buffer_.size()) {
        // We may have reached EOF at the last call to
        // getChar(). at_eof_ will be set then. We then simply return
        // early.
        if (at_eof_) {
            return (END_OF_STREAM);
        }
        // We are not yet at EOF. Read from the stream.
        const int c = input_.get();
        // Have we reached EOF now? If so, set at_eof_ and return early,
        // but don't modify buffer_pos_ (which should still be equal to
        // the size of buffer_).
        if (input_.eof()) {
            at_eof_ = true;
            return (END_OF_STREAM);
        }
        // This has to come after the .eof() check as some
        // implementations seem to check the eofbit also in .fail().
        if (input_.fail()) {
            isc_throw(ReadError,
                      "Error reading from the input stream: " << getName());
        }
        buffer_.push_back(c);
    }

    const int c = buffer_[buffer_pos_++];
    if (c == '\n') {
        line_++;
    }

    return (c);
}

void
InputSource::ungetChar() {
    if (at_eof_) {
        at_eof_ = false;
    } else if (buffer_pos_ == 0) {
        isc_throw(UngetBeforeBeginning,
                  "Cannot skip before the start of buffer");
    } else {
        buffer_pos_--;
        if (buffer_[buffer_pos_] == '\n') {
            line_--;
        }
    }
}

void
InputSource::ungetAll() {
    buffer_pos_ = 0;
    line_ = saved_line_;
    at_eof_ = false;
}

void
InputSource::saveLine() {
    saved_line_ = line_;
}

void
InputSource::compact() {
    if (buffer_pos_ == buffer_.size()) {
        buffer_.clear();
    } else {
        buffer_.erase(buffer_.begin(), buffer_.begin() + buffer_pos_);
    }

    buffer_pos_ = 0;
}

void
InputSource::mark() {
    saveLine();
    compact();
}

} // namespace master_lexer_internal
} // namespace dns
} // namespace isc
