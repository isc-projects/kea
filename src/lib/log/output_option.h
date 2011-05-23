// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __OUTPUT_OPTION_H
#define __OUTPUT_OPTION_H

#include <cstddef>
#include <cstdint>
#include <string>

/// \brief Logger Output Option
///
/// The logging configuration options are a list of logger specifications, each
/// with one or more output options.  This class represents an output option;
/// one or more of these are attached to a LoggerSpecification object which is
/// then passed to the LoggerManager to configure the logger.
///
/// Although there are three distinct output types (console, file, syslog) and
/// the options for each do not really overlap.  Although it is tempting to
/// define a base OutputOption class and derive a class for each type
/// (ConsoleOutputOptions etc.), it would be messy to use in practice.  At
/// some point the exact class would have to be known to get the class-specific
/// options and the (pointer to) the base class cast to the appropriate type.
/// Instead, this "struct" contains the union of all output options; it is up
/// to the caller to cherry-pick the members it needs.
///
/// One final note: this object holds data and does no computation.  For this
/// reason, it is a "struct" and members are accessed directly instead of
/// through methods.

namespace isc {
namespace log {

struct OutputOption {

    /// Destinations.  Prefixed "DEST_" to avoid problems with the C stdio.h
    /// FILE type.
    typedef enum {
        DEST_CONSOLE = 0,
        DEST_FILE = 1,
        DEST_SYSLOG = 2
    } Destination;

    /// If console, stream on which messages are output
    typedef enum {
        STR_STDERR = 0,     // Default console stream is stderr
        STR_STDOUT = 1
    } Stream;

    /// Members.  The default sets everything to 0, which why the
    /// stderr/stdout numbers (above) are reversed.

    Destination     destination;        ///< Where the output should go
    Stream          stream;             ///< stdout/stderr if console output
    bool            flush;              ///< true to flush after each message
    std::string     facility;           ///< syslog facility
    std::string     filename;           ///< Filename if file output
    size_t          maxsize;            ///< 0 if no maximum size
    int             maxver;             ///< Maximum versions (none if <= 0)
};

} // namespace log
} // namespace isc

#endif // __OUTPUT_OPTION_H
