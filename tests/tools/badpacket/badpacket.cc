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

#include <unistd.h>
#include <iostream>

#include <config.h>

#include <exceptions/exceptions.h>
#include <log/logger_support.h>
#include "command_options.h"
#include "scan.h"

/// \brief Perform Bad Packet Scan
///
/// Scans the server by sending a sequence of (potentially) bad packets and
/// printing the packet settings and the response received.  The principle
/// raison d'etre for this is to check if a bad packet will cause a crash.
///
/// This particular version of the code allows a set of ranges to be set for:
/// - The flags fields in the message.
/// - The section count fields, regardless of what is in the section.
/// - The message size: the message can be truncated or extended.
///
/// The program then sends a set of packets corresponding to all combinations
/// of values in the ranges selected.

// TODO: Extend to cover:
// - Mangling the QNAME
// - Adding names to the message sections
// - Adding EDNS0 RR and magling the fields there

using namespace isc::badpacket;

/// \brief Main Program
int main(int argc, char* argv[]) {
    isc::log::initLogger("badpacket");

    try {
        // Parse command
        CommandOptions options;
        options.parse(argc, argv);

        // Send the sequence of messages
        Scan scanner;
        scanner.scan(options);
    } catch (isc::Exception& e) {
        std::cout << "ERROR: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
