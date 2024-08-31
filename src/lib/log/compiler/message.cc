// Copyright (C) 2011-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cctype>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <errno.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <exceptions/exceptions.h>

#include <util/filesystem.h>
#include <util/str.h>

#include <log/log_messages.h>
#include <log/message_dictionary.h>
#include <log/message_exception.h>
#include <log/message_reader.h>

#include <log/logger.h>

using namespace std;
using namespace isc::log;
using namespace isc::util;
using namespace isc::util::file;

/// \file log/compiler/message.cc
/// \brief Message Compiler
///
/// \b Overview<BR>
/// This is the program that takes as input a message file and produces:
///
/// \li A .h file containing message definition
/// \li A .cc file containing code that adds the messages to the program's
/// message dictionary at start-up time.
///
/// \b Invocation<BR>
/// The program is invoked with the command:
///
/// <tt>kea-msg-compiler [-v | -h | -d &lt;dir&gt; | <message-file>]</tt>
///
/// It reads the message file and writes out two files of the same
/// name in the current working directory (unless -d is used) but
/// with extensions of .h and .cc.
///
/// -v causes it to print the version number and exit. -h prints a
/// help message (and exits). -d &lt;dir&gt; will make it write the
/// output file(s) to dir instead of current working directory

/// \brief Print Version
///
/// Prints the program's version number.

void
version() {
    cout << VERSION << "\n";
}

/// \brief Print Usage
///
/// Prints program usage to stdout.

void
usage() {
    cout <<
        "Usage: kea-msg-compiler [-h] [-v] [-d dir] <message-file>\n" <<
        "\n" <<
        "-h       Print this message and exit\n" <<
        "-v       Print the program version and exit\n" <<
        "-d <dir> Place output files in given directory\n" <<
        "\n" <<
        "<message-file> is the name of the input message file.\n";
}

/// \brief Create Header Sentinel
///
/// Given the name of a file, create an \#ifdef sentinel name.  The name is
/// &lt;name&gt;_&lt;ext&gt;, where &lt;name&gt; is the name of the file, and &lt;ext&gt;
/// is the extension less the leading period.  The sentinel will be upper-case.
///
/// \param file path to the file.
///
/// \return Sentinel name

string
sentinel(Path& file) {
    string name = file.stem();
    string ext = file.extension();
    string sentinel_text = name + "_" + ext.substr(1);
    str::uppercase(sentinel_text);
    return (sentinel_text);
}

/// \brief Quote String
///
/// Inserts an escape character (a backslash) prior to any double quote
/// characters.  This is used to handle the fact that the input file does not
/// contain quotes, yet the string will be included in a C++ literal string.

string
quoteString(const string& instring) {

    // Create the output string and reserve the space needed to hold the input
    // string. (Most input strings will not contain quotes, so this single
    // reservation should be all that is needed.)
    string outstring;
    outstring.reserve(instring.size());

    // Iterate through the input string, preceding quotes with a slash.
    for (size_t i = 0; i < instring.size(); ++i) {
        if (instring[i] == '"') {
            outstring += '\\';
        }
        outstring += instring[i];
    }

    return (outstring);
}

/// \brief Sorted Identifiers
///
/// Given a dictionary, return a vector holding the message IDs in sorted
/// order.
///
/// \param dictionary Dictionary to examine
///
/// \return Sorted list of message IDs

vector<string>
sortedIdentifiers(MessageDictionary& dictionary) {
    vector<string> ident;

    for (auto const& i : dictionary) {
        ident.push_back(i.first);
    }
    sort(ident.begin(), ident.end());

    return (ident);
}

/// \brief Split Namespace
///
/// The $NAMESPACE directive may well specify a namespace in the form a::b.
/// Unfortunately, the C++ "namespace" statement can only accept a single
/// string - to set up the namespace of "a::b" requires two statements, one
/// for "namespace a" and the other for "namespace b".
///
/// This function returns the set of namespace components as a vector of
/// strings.  A vector of one element, containing the empty string, is returned
/// if the anonymous namespace is specified.
///
/// \param ns Argument to $NAMESPACE (passed by value, as we will be modifying
/// it.)

vector<string>
splitNamespace(string ns) {

    // Namespaces components are separated by double colon characters -
    // convert to single colons.
    size_t dcolon;
    while ((dcolon = ns.find("::")) != string::npos) {
        ns.replace(dcolon, 2, ":");
    }

    // ... and return the vector of namespace components split on the single
    // colon.
    return (str::tokens(ns, ":"));
}

/// \brief Write Opening Namespace(s)
///
/// Writes the lines listing the namespaces in use.
void
writeOpeningNamespace(ostream& output, const vector<string>& ns) {
    if (!ns.empty()) {

        // Output namespaces in correct order
        for (vector<string>::size_type i = 0; i < ns.size(); ++i) {
            output << "namespace " << ns[i] << " {\n";
        }
        output << "\n";
    }
}

/// \brief Write Closing Namespace(s)
///
/// Writes the lines listing the namespaces in use.
void
writeClosingNamespace(ostream& output, const vector<string>& ns) {
    if (!ns.empty()) {
        for (int i = ns.size() - 1; i >= 0; --i) {
            output << "} // namespace " << ns[i] << "\n";
        }
        output << "\n";
    }
}

/// \brief Write Header File
///
/// Writes the C++ header file containing the symbol definitions.  These are
/// "extern" references to definitions in the .cc file.  As such, they should
/// take up no space in the module in which they are included, and redundant
/// references should be removed by the compiler.
///
/// \param file Name of the message file.  The header file is written to a
/// file of the same name but with a .h suffix.
/// \param ns_components Namespace in which the definitions are to be placed.
/// An empty string indicates no namespace.
/// \param dictionary Dictionary holding the message definitions.
/// \param output_directory if not null NULL, output files are written
///     to the given directory. If NULL, they are written to the current
///     working directory.
void
writeHeaderFile(const string& file,
                const vector<string>& ns_components,
                MessageDictionary& dictionary,
                const char* output_directory) {
    Path message_file(file);
    Path header_file(Path(file).replaceExtension(".h"));
    if (output_directory != NULL) {
        header_file.replaceParentPath(output_directory);
    }

    // Text to use as the sentinels.
    string sentinel_text = sentinel(header_file);

    // zero out the errno to be safe
    errno = 0;

    // Open the output file for writing
    ofstream hfile(header_file.str());

    if (hfile.fail()) {
        isc_throw_4(MessageException, "Failed to open output file",
                    LOG_OPEN_OUTPUT_FAIL, header_file.str(),
                    strerror(errno), 0);
    }

    // Write the header preamble.  If there is an error, we'll pick it up
    // after the last write.

    hfile <<
        "// File created from " << message_file.str() << "\n" <<
         "\n" <<
         "#ifndef " << sentinel_text << "\n" <<
         "#define "  << sentinel_text << "\n" <<
         "\n" <<
         "#include <log/message_types.h>\n" <<
         "\n";

    // Write the message identifiers, bounded by a namespace declaration
    writeOpeningNamespace(hfile, ns_components);

    vector<string> idents = sortedIdentifiers(dictionary);
    for (auto const& j : idents) {
        hfile << "extern const isc::log::MessageID " << j << ";\n";
    }
    hfile << "\n";

    writeClosingNamespace(hfile, ns_components);

    // ... and finally the postamble
    hfile << "#endif // " << sentinel_text << "\n";

    // Report errors (if any) and exit
    if (hfile.fail()) {
        isc_throw_4(MessageException, "Error writing to output file",
                    LOG_WRITE_ERROR, header_file.str(), strerror(errno),
                    0);
    }

    hfile.close();
}

/// \brief Convert Non Alpha-Numeric Characters to Underscores
///
/// Simple function for use in a call to transform
char
replaceNonAlphaNum(char c) {
    return (isalnum(c) ? c : '_');
}

/// \brief Write Program File
///
/// Writes the C++ source code file.  This defines the text of the message
/// symbols, as well as the initializer object that sets the entries in the
/// global dictionary.
///
/// The construction of the initializer object loads the dictionary with the
/// message text.  However, nothing actually references it.  If the initializer
/// were in a file by itself, the lack of things referencing it would cause the
/// linker to ignore it when pulling modules out of the logging library in a
/// static link.  By including it in the file with the symbol definitions, the
/// module will get included in the link process to resolve the symbol
/// definitions, and so the initializer object will be included in the final
/// image. (Note that there are no such problems when the logging library is
/// built as a dynamically-linked library: the whole library - including the
/// initializer module - gets mapped into address space when the library is
/// loaded, after which all the initializing code (including the constructors
/// of objects declared outside functions) gets run.)
///
/// There _may_ be a problem when we come to port this to Windows.  Microsoft
/// Visual Studio contains a "Whole Program Optimization" option, where the
/// optimization is done at link-time, not compiler-time.  In this it _may_
/// decide to remove the initializer object because of a lack of references
/// to it.  But until BIND-10 is ported to Windows, we won't know.
///
/// \param file Name of the message file.  The header file is written to a
/// file of the same name but with a .h suffix.
/// \param ns_components Namespace in which the definitions are to be placed.
/// An empty string indicates no namespace.
/// \param dictionary Dictionary holding the message definitions.
/// \param output_directory if not null NULL, output files are written
///     to the given directory. If NULL, they are written to the current
///     working directory.
void
writeProgramFile(const string& file,
                 const vector<string>& ns_components,
                 MessageDictionary& dictionary,
                 const char* output_directory) {
    Path message_file(file);
    Path program_file(Path(file).replaceExtension(".cc"));
    if (output_directory) {
        program_file.replaceParentPath(output_directory);
    }

    // zero out the errno to be safe
    errno = 0;

    // Open the output file for writing
    ofstream ccfile(program_file.str());

    if (ccfile.fail()) {
        isc_throw_4(MessageException, "Error opening output file",
                    LOG_OPEN_OUTPUT_FAIL, program_file.str(),
                    strerror(errno), 0);
    }

    // Write the preamble.  If there is an error, we'll pick it up after
    // the last write.

    ccfile <<
        "// File created from " << message_file.str() << "\n" <<
         "\n" <<
         "#include <cstddef>\n" <<
         "#include <log/message_types.h>\n" <<
         "#include <log/message_initializer.h>\n" <<
         "\n";

    // Declare the message symbols themselves.

    writeOpeningNamespace(ccfile, ns_components);

    vector<string> idents = sortedIdentifiers(dictionary);
    for (auto const& j : idents) {
        ccfile << "extern const isc::log::MessageID " << j <<
            " = \"" << j << "\";\n";
    }
    ccfile << "\n";

    writeClosingNamespace(ccfile, ns_components);

    // Now the code for the message initialization.

    ccfile <<
         "namespace {\n" <<
         "\n" <<
         "const char* values[] = {\n";

    // Output the identifiers and the associated text.
    idents = sortedIdentifiers(dictionary);
    for (auto const& i : idents) {
        ccfile << "    \"" << i << "\", \"" << quoteString(dictionary.getText(i)) << "\",\n";
    }

    // ... and the postamble
    ccfile <<
        "    NULL\n" <<
        "};\n" <<
        "\n" <<
        "const isc::log::MessageInitializer initializer(values);\n" <<
        "\n" <<
        "} // Anonymous namespace\n" <<
        "\n";

    // Report errors (if any) and exit
    if (ccfile.fail()) {
        isc_throw_4(MessageException, "Error writing to output file",
                    LOG_WRITE_ERROR, program_file.str(), strerror(errno),
                    0);
    }

    ccfile.close();
}

/// \brief Error and exit if there are duplicate entries
///
/// If the input file contained duplicate message IDs, we print an
/// error for each of them, then exit the program with a non-0 value.
///
/// \param reader Message Reader used to read the file
void
errorDuplicates(MessageReader& reader) {

    // Get the duplicates (the overflow) and, if present, sort them into some
    // order and remove those which occur more than once (which mean that they
    // occur more than twice in the input file).
    MessageReader::MessageIDCollection duplicates = reader.getNotAdded();
    if (!duplicates.empty()) {
        cout << "Error: the following duplicate IDs were found:\n";

        sort(duplicates.begin(), duplicates.end());
        MessageReader::MessageIDCollection::iterator new_end =
            unique(duplicates.begin(), duplicates.end());
        duplicates.erase(new_end, duplicates.end());
        for (auto const& i : duplicates) {
            cout << "    " << i << "\n";
        }
        exit(1);
    }
}

/// \brief Main Program
///
/// Parses the options then dispatches to the appropriate function.  See the
/// main file header for the invocation.
int
main(int argc, char* argv[]) {

    const char* soptions = "hvpd:";               // Short options

    optind = 1;             // Ensure we start a new scan
    int  opt;               // Value of the option

    const char *output_directory = NULL;

    while ((opt = getopt(argc, argv, soptions)) != -1) {
        switch (opt) {
            case 'd':
                output_directory = optarg;
                break;

            case 'h':
                usage();
                return (0);

            case 'v':
                version();
                return (0);

            default:
                // A message will have already been output about the error.
                return (1);
        }
    }

    // Do we have the message file?
    if (optind < (argc - 1)) {
        cout << "Error: excess arguments in command line\n";
        usage();
        return (1);
    } else if (optind >= argc) {
        cout << "Error: missing message file\n";
        usage();
        return (1);
    }
    string message_file = argv[optind];

    try {
        // Have identified the file, so process it.  First create a local
        // dictionary into which the data will be put.
        MessageDictionary dictionary;

        // Read the data into it.
        MessageReader reader(&dictionary);
        reader.readFile(message_file);

        // Error (and quit) if there are of any duplicates encountered.
        errorDuplicates(reader);

        // Get the namespace into which the message definitions will be put and
        // split it into components.
        vector<string> ns_components =
            splitNamespace(reader.getNamespace());

        // Write the header file.
        writeHeaderFile(message_file, ns_components, dictionary,
                        output_directory);

        // Write the file that defines the message symbols and text
        writeProgramFile(message_file, ns_components, dictionary,
                         output_directory);

    } catch (const MessageException& e) {
        // Create an error message from the ID and the text
        const MessageDictionaryPtr& global = MessageDictionary::globalDictionary();
        string text = e.id();
        text += ", ";
        text += global->getText(e.id());
        // Format with arguments
        vector<string> args(e.arguments());
        for (size_t i(0); i < args.size(); ++ i) {
            try {
                replacePlaceholder(text, args[i], i + 1);
            } catch (...) {
                // Error in error handling: nothing right to do...
            }
        }

        cerr << text << "\n";

        return (1);
    } catch (const std::exception& ex) {
        cerr << "Fatal error: " << ex.what() << "\n";

        return (1);
    } catch (...) {
        cerr << "Fatal error\n";

        return (1);
    }

    return (0);
}
