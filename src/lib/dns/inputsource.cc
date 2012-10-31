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

#include <dns/inputsource.h>

namespace isc {
namespace dns {
namespace master_lexer_internal {

namespace { // unnamed namespace

std::string
createStreamName(std::istream& input_stream) {
     std::stringstream ss;
     ss << "stream-" << &input_stream;
     return (ss.str());
}

} // end of unnamed namespace

InputSource::InputSource(std::istream& input_stream) :
    at_eof_(false),
    line_(1),
    saved_line_(line_),
    buffer_pos_(buffer_.size()),
    name_(createStreamName(input_stream)),
    input_(input_stream)
{}

InputSource::InputSource(const char* filename) :
    at_eof_(false),
    line_(1),
    saved_line_(line_),
    buffer_pos_(buffer_.size()),
    name_(filename),
    input_(file_stream_)
{
    file_stream_.open(filename, std::fstream::in);
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
            return -1;
        }
        // We are not yet at EOF. Read from the stream.
        int c = input_.get();
        // Have we reached EOF now? If so, set at_eof_ and return early,
        // but don't modify buffer_pos_ (which should still be equal to
        // the size of buffer_).
        if (!input_.good()) {
            at_eof_ = true;
            return -1;
        }
        buffer_.push_back(c);
    }

    int c = buffer_[buffer_pos_++];
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
        isc_throw(UngetError, "Cannot skip before the start of buffer");
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
InputSource::compact() {
    if (buffer_pos_ == buffer_.size()) {
        buffer_.clear();
    } else {
        buffer_.erase(buffer_.begin(), buffer_.begin() + buffer_pos_);
    }

    buffer_pos_ = 0;
}

} // namespace master_lexer_internal
} // namespace dns
} // namespace isc
