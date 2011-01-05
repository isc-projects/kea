// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <iostream>
#include <unistd.h>
#include <getopt.h>

using namespace std;

static const char* VERSION = "1.0-0";

/// \brief Message Compiler
///
/// \b Overview<BR>
/// This is the program that takes as input a message file and produces:
///
/// \li A .h file containing message definition
/// \li A .cc file containing code that adds the messages to the program's
/// message disctionary at start-up time.
///
/// Alternatively, the program can produce a .py file that contains the
/// message definitions.
///

/// \b Invocation<BR>
/// The program is invoked with the command:
///
/// <tt>message [-p] \<message-file\></tt>
///
/// It reads the message file and writes out two files of the same name but with
/// extensions of .h and .cc.
///
/// If \c -p is specified, the C++ files are not written; instead a Python file
/// of the same name (but with the file extension .py) is written.


/// \brief Print Version
///
/// Prints the program's version number.

static void version() {
    cout << VERSION << "\n";
}

/// \brief Print Usage
///
/// Prints program usage to stdout.

static void usage() {
    cout <<
        "Usage: message [-h] [-p] [-v] <message-file>\n" <<
        "\n" <<
        "-h       Print this message and exit\n" <<
        "-p       Output a Python module holding the message definitions.\n" <<
        "         By default a C++ header file and implementation file are\n" <<
        "         written.\n" <<
        "-v       Print the program version and exit\n" <<
        "\n" <<
        "<message-file> is the name of the input message file.\n";
}

/// \brief Main Program
///
/// Parses the options then dispatches to the appropriate function.  See the
/// main file header for the invocation.

int main(int argc, char** argv) {
    
    const struct option loptions[] = {          // Long options
        {"help",    no_argument, NULL, 'h'},
        {"python",  no_argument, NULL, 'p'},
        {"version", no_argument, NULL, 'v'},
        {NULL,      0,           NULL, 0  }
    };
    const char* soptions = "hpv";               // Short options

    optind = 1;             // Ensure we start a new scan
    int  opt;               // Value of the option
    bool python = false;    // Set true if the -p flag is detected

    while ((opt = getopt_long(argc, argv, soptions, loptions, NULL)) != -1) {
        switch (opt) {
            case 'h':
                usage();
                return 0;

            case 'v':
                version();
                return 0;

            case 'p':
                python = true;
                break;

            default:
                // A message will have already been output about the error.
                return 1;
        }
    }

    // Do we have the message file?
    if (optind < (argc - 1)) {
        std::cout << "Error: excess arguments in command line\n";
        usage();
        return 1;
    }
    else if (optind >= argc) {
        std::cout << "Error: missing message file\n";
        usage();
        return 1;
    }

    // Have identified the file, so process it.
    MessageFileProcessor fileProcessor();
    return fileProcessor.process(argv[argc - 1], python);

}
