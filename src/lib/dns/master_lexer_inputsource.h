// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DNS_INPUTSOURCE_H
#define DNS_INPUTSOURCE_H 1

#include <exceptions/exceptions.h>

#include <boost/noncopyable.hpp>

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
/// This class is not meant for public use. We also enforce that
/// instances are non-copyable.
class InputSource : boost::noncopyable {
public:
    /// \brief Returned by getChar() when end of stream is reached.
    ///
    /// \note C++ allows a static const class member of an integral type to
    /// be used without explicit definition as long as its address isn't
    /// required.  But, since this is a public member variable and we cannot
    /// assume how it's used, we give a definition in the implementation.
    static const int END_OF_STREAM = -1;

    /// \brief Exception thrown when ungetChar() is made to go before
    /// the start of buffer.
    struct UngetBeforeBeginning : public OutOfRange {
        UngetBeforeBeginning(const char* file, size_t line, const char* what) :
            OutOfRange(file, line, what)
        {}
    };

    /// \brief Exception thrown when we fail to open the input file.
    struct OpenError : public Unexpected {
        OpenError(const char* file, size_t line, const char* what) :
            Unexpected(file, line, what)
        {}
    };

    /// \brief Constructor which takes an input stream. The stream is
    /// read-from, but it is not closed.
    ///
    /// \throws OpenError If the data size of the input stream cannot be
    /// detected.
    explicit InputSource(std::istream& input_stream);

    /// \brief Constructor which takes a filename to read from. The
    /// associated file stream is managed internally.
    ///
    /// \throws OpenError when opening the input file fails or the size of
    /// the file cannot be detected.
    explicit InputSource(const char* filename);

    /// \brief Destructor
    ~InputSource();

    /// \brief Returns a name for the InputSource. Typically this is the
    /// filename, but if the InputSource was constructed for an
    /// \c std::istream, it returns a name in the format "stream-%p".
    const std::string& getName() const {
        return (name_);
    }

    /// \brief Returns the size of the input source in bytes.
    ///
    /// If the size is unknown, it returns \c MasterLexer::SOURCE_SIZE_UNKNOWN.
    ///
    /// See \c MasterLexer::getTotalSourceSize() for the definition of
    /// the size of sources and for when the size can be unknown.
    ///
    /// \throw None
    size_t getSize() const { return (input_size_); }

    /// \brief Returns the current read position in the input source.
    ///
    /// This method returns the position of the character that was last
    /// retrieved from the source.  Unless some characters have been
    /// "ungotten" by \c ungetChar() or \c ungetAll(), this value is equal
    /// to the number of calls to \c getChar() until it reaches the
    /// END_OF_STREAM.  Note that the position of the first character in
    /// the source is 1.  At the point of the last character, the return value
    /// of this method should be equal to that of \c getSize(), and
    /// recognizing END_OF_STREAM doesn't increase the position.
    ///
    /// If \c ungetChar() or \c ungetAll() is called, the position is
    /// decreased by the number of "ungotten" characters.  So the return
    /// values may not always monotonically increase.
    ///
    /// \throw None
    size_t getPosition() const { return (total_pos_); }

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
    ///
    /// TODO: Please make this method private if it is unused after the
    /// MasterLexer implementation is complete (and only \c mark() is
    /// used instead).
    void saveLine();

    /// Removes buffered content before the current location in the
    /// \c InputSource. It's not possible to \c ungetChar() after this,
    /// unless we read more data using \c getChar().
    ///
    /// TODO: Please make this method private if it is unused after the
    /// MasterLexer implementation is complete (and only \c mark() is
    /// used instead).
    void compact();

    /// Calls \c saveLine() and \c compact() in sequence.
    void mark();

    /// \brief Returns a single character from the input source. If end
    /// of file is reached, \c END_OF_STREAM is returned.
    ///
    /// \throws MasterLexer::ReadError when reading from the input stream or
    /// file fails.
    int getChar();

    /// \brief Skips backward a single character in the input
    /// source. The last-read character is unget.
    ///
    /// \throws UngetBeforeBeginning if we go backwards past the start
    /// of reading, or backwards past the last time compact() was
    /// called.
    void ungetChar();

    /// Forgets what was read, and skips back to the position where
    /// \c compact() was last called. If \c compact() was not called, it
    /// skips back to where reading started. If \c saveLine() was called
    /// previously, it sets the current line number to the line number
    /// saved.
    void ungetAll();

private:
    bool at_eof_;
    size_t line_;
    size_t saved_line_;

    std::vector<char> buffer_;
    size_t buffer_pos_;
    size_t total_pos_;

    const std::string name_;
    std::ifstream file_stream_;
    std::istream& input_;
    const size_t input_size_;
};

} // namespace master_lexer_internal
} // namespace dns
} // namespace isc

#endif  // DNS_INPUTSOURCE_H

// Local Variables:
// mode: c++
// End:
