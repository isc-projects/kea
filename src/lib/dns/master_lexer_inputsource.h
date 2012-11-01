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

/// \brief An input source that is used internally by MasterLexer.
///
/// This is a helper internal class for MasterLexer, and represents
/// state of a single source of the entire zone data to be
/// parsed. Normally this means the master zone file, but MasterLexer
/// can have multiple InputSources if $INCLUDE is used. The source can
/// also be generic input stream (std::istream).
///
/// This class is not meant for public use.
class InputSource {
public:
    /// \brief Constructor which takes an input stream. The stream is
    /// read-from, but it is not closed.
    InputSource(std::istream& input_stream);

    /// \brief Constructor which takes a filename to read from. The
    /// associated file stream is managed internally.
    InputSource(const char* filename);

    /// \brief Destructor
    ~InputSource();

    /// \brief Returns a name for the InputSource. Typically this is the
    /// filename, but if the InputSource was constructed for an
    /// \c std::istream, it returns a name in the format "stream-%p".
    const std::string& getName() const {
        return (name_);
    }

    /// \brief Returns if the input source is at end of file.
    bool atEOF() const {
        return (at_eof_);
    }

    /// \brief Returns the current line number being read.
    size_t getCurrentLine() const {
        return (line_);
    }

    /// \brief Saves the current line being read. Later, when
    /// \c ungetAll() is called, it skips back to the last-saved line.
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

    /// \brief Returns a single character from the input source. If end
    /// of file is reached, -1 is returned.
    int getChar();

    /// \brief Skips backward a single character in the input
    /// source. The last-read character is unget.
    void ungetChar();

    /// Forgets everything read so far, and skips back to the position
    /// where reading started. If \c saveLine() was called previously,
    /// it sets the current line number to the line number saved then.
    void ungetAll();

    /// Removes buffered content before the current location in the
    /// \c InputSource. It's not possible to \c ungetChar() after this,
    /// unless we read more data using \c getChar().
    void compact();

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
