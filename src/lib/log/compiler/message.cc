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

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include <errno.h>
#include <getopt.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include <log/filename.h>
#include <log/message_dictionary.h>
#include <log/message_exception.h>
#include <log/message_reader.h>
#include <log/messagedef.h>
#include <log/strutil.h>

#include <log/logger.h>

using namespace std;
using namespace isc::log;

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


/// \brief Create Time
///
/// Returns the current time as a suitably-formatted string.
///
/// \return Current time

static string currentTime() {

    // Get the current time.
    time_t curtime;
    time(&curtime);

    // Format it
    char buffer[32];
    ctime_r(&curtime, buffer);

    // Convert to string and strip out the trailing newline
    string current_time = buffer;
    return isc::strutil::trim(current_time);
}




/// \brief Create Header Sentinel
///
/// Given the name of a file, create an #ifdef sentinel name.  The name is
/// __<name>_<ext>, where <name> is the name of the file, and <ext> is the
/// extension less the leading period.  The sentinel will be upper-case.
///
/// \param file Filename object representing the file.
///
/// \return Sentinel name

static string sentinel(Filename& file) {

    string name = file.name();
    string ext = file.extension();
    string sentinel_text = "__" + name + "_" + ext.substr(1);
    isc::strutil::uppercase(sentinel_text);
    return sentinel_text;
}


/// \brief Quote String
///
/// Inserts an escape character (a backslash) prior to any double quote
/// characters.  This is used to handle the fact that the input file does not
/// contain quotes, yet the string will be included in a C++ literal string.

string quoteString(const string& instring) {

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

    return outstring;
}


/// \brief Sorted Identifiers
///
/// Given a dictionary, return a vector holding the message IDs in sorted
/// order.
///
/// \param dictionary Dictionary to examine
///
/// \return Sorted list of message IDs

vector<MessageID> sortedIdentifiers(MessageDictionary* dictionary) {
    vector<MessageID> ident;

    for (MessageDictionary::const_iterator i = dictionary->begin();
         i != dictionary->end(); ++i) {
        ident.push_back(i->first);
    }
    sort(ident.begin(), ident.end());

    return ident;
}


/// \brief Write Header File
///
/// Writes the C++ header file containing the symbol definitions.
///
/// \param file Name of the message file.  The header file is written to a
/// file of the same name but with a .h suffix.
/// \param prefix Prefix string to use in symbols
/// \param dictionary Dictionary holding the message definitions.

void writeHeaderFile(const string& file, const string& prefix,
    MessageDictionary* dictionary)
{
    Filename message_file(file);
    Filename header_file(message_file.useAsDefault(".h"));

    // Text to use as the sentinels.
    string sentinel_text = sentinel(header_file);

    // Open the output file for writing
    ofstream hfile(header_file.fullName().c_str());

    try {
        if (hfile.fail()) {
            throw MessageException(MSG_OPENOUT, header_file.fullName(),
                strerror(errno));
        }

        // Write the header preamble.  If there is an error, we'll pick it up
        // after the last write.

        hfile <<
            "// File created from " << message_file.fullName() << " on " <<
                currentTime() << "\n" <<
             "\n" <<
             "#ifndef " << sentinel_text << "\n" <<
             "#define "  << sentinel_text << "\n" <<
             "\n" <<
             "#include <log/message_types.h>\n" <<
             "\n" <<
             "namespace {\n" <<
             "\n";

        vector<MessageID> idents = sortedIdentifiers(dictionary);
        for (vector<MessageID>::const_iterator j = idents.begin();
            j != idents.end(); ++j) {
            hfile << "isc::log::MessageID " << prefix << *j <<
                " = \"" << *j << "\";\n";
        }

        // ... and finally the postamble
        hfile <<
            "\n" <<
            "} // Anonymous namespace\n" <<
            "\n" <<
            "#endif // " << sentinel_text << "\n";

        // Report errors (if any) and exit
        if (hfile.fail()) {
            throw MessageException(MSG_WRITERR, header_file.fullName(),
                strerror(errno));
        }

        hfile.close();
    }
    catch (MessageException&) {
        hfile.close();
        throw;
    }
}


/// \brief Convert Non Alpha-Numeric Characters to Underscores
///
/// Simple function for use in a call to transform

char replaceNonAlphaNum(char c) {
    return (isalnum(c) ? c : '_');
}


/// \brief Write Program File
///
/// Writes the C++ source code file.  This defines an external objects whose
/// constructor is run at initialization time.  The constructor adds the message
/// definitions to the main global dictionary.

void writeProgramFile(const string& file, MessageDictionary* dictionary)
{
    Filename message_file(file);
    Filename program_file(message_file.useAsDefault(".cc"));

    // Open the output file for writing
    ofstream ccfile(program_file.fullName().c_str());
    try {
        if (ccfile.fail()) {
            throw MessageException(MSG_OPENOUT, program_file.fullName(),
                strerror(errno));
        }

        // Write the preamble.  If there is an error, we'll pick it up after
        // the last write.

        ccfile <<
            "// File created from " << message_file.fullName() << " on " <<
                currentTime() << "\n" <<
             "\n" <<
             "#include <cstddef>\n" <<
             "#include <log/message_initializer.h>\n" <<
             "\n" <<
             "using namespace isc::log;\n" <<
             "\n" <<
             "namespace {\n" <<
             "\n" <<
             "const char* values[] = {\n";

        // Output the identifiers and the associated text.
        vector<MessageID> idents = sortedIdentifiers(dictionary);
        for (vector<MessageID>::const_iterator i = idents.begin();
            i != idents.end(); ++i) {
                ccfile << "    \"" << *i << "\", \"" <<
                    quoteString(dictionary->getText(*i)) << "\",\n";
        }

        // ... and the postamble
        ccfile <<
            "    NULL\n" <<
            "};\n" <<
            "\n" <<
            "} // Anonymous namespace\n" <<
            "\n";

        // Now construct a unique name.  We don't put the message initializer as
        // a static variable or in an anonymous namespace lest the C++
        // compiler's optimizer decides it can optimise it away.
        string unique_name = program_file.name() + program_file.extension() +
            "_" + currentTime();
        transform(unique_name.begin(), unique_name.end(), unique_name.begin(),
            replaceNonAlphaNum);

        // ... and write the initialization code
        ccfile <<
            "MessageInitializer " << unique_name << "(values);\n";

        // Report errors (if any) and exit
        if (ccfile.fail()) {
            throw MessageException(MSG_WRITERR, program_file.fullName(),
                strerror(errno));
        }

        ccfile.close();
    }
    catch (MessageException&) {
        ccfile.close();
        throw;
    }
}


/// \brief Warn of Duplicate Entries
///
/// If the input file contained duplicate message IDs, only the first will be
/// processed.  However, we should warn about it.
///
/// \param reader Message Reader used to read the file

static void warnDuplicates(MessageReader& reader) {

    // Get the duplicates (the overflow) and, if present, sort them into some
    // order and remove those which occur more than once (which mean that they
    // occur more than twice in the input file).
    MessageReader::MessageIDCollection duplicates = reader.getNotAdded();
    if (duplicates.size() > 0) {
        cout << "Warning: the following duplicate IDs were found:\n";

        sort(duplicates.begin(), duplicates.end());
        MessageReader::MessageIDCollection::iterator new_end =
            unique(duplicates.begin(), duplicates.end());
        for (MessageReader::MessageIDCollection::iterator i = duplicates.begin();
            i != new_end; ++i) {
            cout << "    " << *i << "\n";
        }
    }
}


/// \brief Main Program
///
/// Parses the options then dispatches to the appropriate function.  See the
/// main file header for the invocation.

int main(int argc, char** argv) {
    
    const struct option loptions[] = {          // Long options
        {"help",    no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
        {NULL,      0,           NULL, 0  }
    };
    const char* soptions = "hv";               // Short options

    optind = 1;             // Ensure we start a new scan
    int  opt;               // Value of the option

    while ((opt = getopt_long(argc, argv, soptions, loptions, NULL)) != -1) {
        switch (opt) {
            case 'h':
                usage();
                return 0;

            case 'v':
                version();
                return 0;

            default:
                // A message will have already been output about the error.
                return 1;
        }
    }

    // Do we have the message file?
    if (optind < (argc - 1)) {
        cout << "Error: excess arguments in command line\n";
        usage();
        return 1;
    } else if (optind >= argc) {
        cout << "Error: missing message file\n";
        usage();
        return 1;
    }
    string message_file = argv[optind];

    try {
        // Have identified the file, so process it.  First create a local
        // dictionary into which the data will be put.
        MessageDictionary dictionary;

        // Read the data into it.
        MessageReader reader(&dictionary);
        reader.readFile(message_file);

        // Now write the header file.
        writeHeaderFile(message_file, reader.getPrefix(), &dictionary);

        // ... and the message text file.
        writeProgramFile(message_file, &dictionary);

        // Finally, warn of any duplicates encountered.
        warnDuplicates(reader);
    }
    catch (MessageException& e) {
        // Create an error message from the ID and the text
        MessageDictionary* global = MessageDictionary::globalDictionary();
        string text = e.id() + ", " + global->getText(e.id());

        // Format with arguments
        text = isc::strutil::format(text, e.arguments());
        cerr << text << "\n";

        return 1;
    }

    return 0;

}
