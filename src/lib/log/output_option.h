// Copyright (C) 2011-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OUTPUT_OPTION_H
#define OUTPUT_OPTION_H

#include <stdint.h>
#include <stdlib.h>
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

    /// Default layout pattern for console logs
    static const std::string DEFAULT_CONSOLE_PATTERN;
    /// Default layout pattern for file logs
    static const std::string DEFAULT_FILE_PATTERN;
    /// Default layout pattern for syslog logs
    static const std::string DEFAULT_SYSLOG_PATTERN;

    /// Destinations.  Prefixed "DEST_" to avoid problems with the C stdio.h
    /// FILE type.
    typedef enum {
        DEST_CONSOLE = 0,
        DEST_FILE = 1,
        DEST_SYSLOG = 2
    } Destination;

    /// If console, stream on which messages are output
    typedef enum {
        STR_STDOUT = 1,
        STR_STDERR = 2
    } Stream;

    /// \brief Constructor
    OutputOption() : destination(DEST_CONSOLE), stream(STR_STDERR),
                     flush(true), facility("LOCAL0"), filename(""),
                     maxsize(0), maxver(0), pattern("")
    {}

    /// Members.

    Destination     destination;        ///< Where the output should go
    Stream          stream;             ///< stdout/stderr if console output
    bool            flush;              ///< true to flush after each message
    std::string     facility;           ///< syslog facility
    std::string     filename;           ///< Filename if file output
    uint64_t        maxsize;            ///< 0 if no maximum size
    unsigned int    maxver;             ///< Maximum versions (none if <= 0)
    std::string     pattern;            ///< log content pattern
};

OutputOption::Destination getDestination(const std::string& dest_str);
OutputOption::Stream getStream(const std::string& stream_str);


} // namespace log
} // namespace isc

#endif // OUTPUT_OPTION_H
