// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dns/master_lexer_inputsource.h>
#include <dns/master_lexer.h>

#include <istream>
#include <iostream>
#include <cassert>
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

size_t
getStreamSize(std::istream& is) {
    errno = 0;                  // see below
    is.seekg(0, std::ios_base::end);
    if (is.bad()) {
        // This means the istream has an integrity error.  It doesn't make
        // sense to continue from this point, so we treat it as a fatal error.
        isc_throw(InputSource::OpenError,
                  "failed to seek end of input source");
    } else if (is.fail() || errno != 0) {
        // This is an error specific to seekg().  There can be several
        // reasons, but the most likely cause in this context is that the
        // stream is associated with a special type of file such as a pipe.
        // In this case, it's more likely that other main operations of
        // the input source work fine, so we continue with just setting
        // the stream size to "unknown".
        //
        // (At least some versions of) Solaris + SunStudio shows deviant
        // behavior here: seekg() apparently calls lseek(2) internally, but
        // even if it fails it doesn't set the error bits of istream. That will
        // confuse the rest of this function, so, as a heuristic workaround
        // we check errno and handle any non 0 value as fail().
        is.clear();   // clear this error not to confuse later ops.
        return (MasterLexer::SOURCE_SIZE_UNKNOWN);
    }
    const std::streampos len = is.tellg();
    size_t ret = len;
    if (len == static_cast<std::streampos>(-1)) { // cast for some compilers
        if (!is.fail()) {
            // tellg() returns -1 if istream::fail() would be true, but it's
            // not guaranteed that it shouldn't be returned in other cases.
            // In fact, with the combination of SunStudio and stlport,
            // a stringstream created by the default constructor showed that
            // behavior.  We treat such cases as an unknown size.
            ret = MasterLexer::SOURCE_SIZE_UNKNOWN;
        } else {
            isc_throw(InputSource::OpenError, "failed to get input size");
        }
    }
    is.seekg(0, std::ios::beg);
    if (is.fail()) {
        isc_throw(InputSource::OpenError,
                  "failed to seek beginning of input source");
    }
    assert(len >= 0 || ret == MasterLexer::SOURCE_SIZE_UNKNOWN);
    return (ret);
}

} // end of unnamed namespace

// Explicit definition of class static constant.  The value is given in the
// declaration so it's not needed here.
const int InputSource::END_OF_STREAM;

InputSource::InputSource(std::istream& input_stream) :
    at_eof_(false),
    line_(1),
    saved_line_(line_),
    buffer_pos_(0),
    total_pos_(0),
    name_(createStreamName(input_stream)),
    input_(input_stream),
    input_size_(getStreamSize(input_))
{}

namespace {
// A helper to initialize InputSource::input_ in the member initialization
// list.
std::istream&
openFileStream(std::ifstream& file_stream, const char* filename) {
    errno = 0;
    file_stream.open(filename);
    if (file_stream.fail()) {
        std::string error_txt("Error opening the input source file: ");
        error_txt += filename;
        if (errno != 0) {
            error_txt += "; possible cause: ";
            error_txt += std::strerror(errno);
        }
        isc_throw(InputSource::OpenError, error_txt);
    }

    return (file_stream);
}
}

InputSource::InputSource(const char* filename) :
    at_eof_(false),
    line_(1),
    saved_line_(line_),
    buffer_pos_(0),
    total_pos_(0),
    name_(filename),
    input_(openFileStream(file_stream_, filename)),
    input_size_(getStreamSize(input_))
{}

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
            isc_throw(MasterLexer::ReadError,
                      "Error reading from the input stream: " << getName());
        }
        buffer_.push_back(c);
    }

    const int c = buffer_[buffer_pos_];
    ++buffer_pos_;
    ++total_pos_;
    if (c == '\n') {
        ++line_;
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
        --buffer_pos_;
        --total_pos_;
        if (buffer_[buffer_pos_] == '\n') {
            --line_;
        }
    }
}

void
InputSource::ungetAll() {
    assert(total_pos_ >= buffer_pos_);
    total_pos_ -= buffer_pos_;
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
