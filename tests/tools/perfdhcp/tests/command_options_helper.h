// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __COMMAND_OPTIONS_HELPER_H
#define __COMMAND_OPTIONS_HELPER_H

#include <string>
#include <vector>

#include <exceptions/exceptions.h>
#include "../command_options.h"

namespace isc {
namespace perfdhcp {

/// \brief Command Options Helper class.
///
/// This helper class can be shared between unit tests that
/// need to initialize CommandOptions objects and feed it with
/// specific command line. The command line can be given as a
/// string representing program name, options and arguments.
/// The static method exposed by this class can be used to
/// tokenize this string into array of C-strings that are later
/// consumed by \ref CommandOptions::parse. The state of the
/// CommandOptions object is reset every time the process
/// function is invoked. Also, when command line parsing is
/// ended the array of C-string is freed from the memory.
class CommandOptionsHelper {
public:

    /// \brief Wrapper class for allocated argv[] array.
    ///
    /// This class wraps allocated char** array and ensures that memory
    /// allocated for this array is freed at the end o the scope.
    class ArgvPtr {
    public:
        /// \brief Constructor.
        ///
        /// \param argv array of C-strings.
        /// \param number of C-strings in the array.
        ArgvPtr(char** argv, int argc) : argv_(argv), argc_(argc) { }

        /// \brief Destructor.
        ///
        /// Dealocates wrapped array of C-strings.
        ~ArgvPtr() {
            if (argv_ != NULL) {
                for(int i = 0; i < argc_; ++i) {
                    free(argv_[i]);
                    argv_[i] = NULL;
                }
                free(argv_);
            }
        }

        /// \brief Return the array of C-strings.
        ///
        /// \return array of C-strings.
        char** getArgv() const { return (argv_); }

        /// \brief Return C-strings counter.
        ///
        /// \return C-strings counter.
        int getArgc() const { return(argc_); }

    public:
        char** argv_; ///< array of C-strings being wrapped.
        int argc_;    ///< number of C-strings.
    };

    /// \brief Parse command line provided as string.
    ///
    /// Method transforms the string representing command line
    /// to the array of C-strings consumed by the
    /// \ref CommandOptions::parse function and performs
    /// parsing.
    ///
    /// \param cmdline command line provided as single string.
    static void process(const std::string& cmdline) {
        CommandOptions& opt = CommandOptions::instance();
        int argc = 0;
        char** argv = tokenizeString(cmdline, argc);
        ArgvPtr args(argv, argc);
        opt.reset();
        opt.parse(args.getArgc(), args.getArgv());
    }

private:

    /// \brief Split string to the array of C-strings.
    ///
    /// \param text_to_split string to be splited.
    /// \param [out] num number of substrings returned.
    /// \return array of C-strings created from split.
    static char** tokenizeString(const std::string& text_to_split, int& num) {
        char** results = NULL;
        // Tokenization with std streams
        std::stringstream text_stream(text_to_split);
        // Iterators to be used for tokenization
        std::istream_iterator<std::string> text_iterator(text_stream);
        std::istream_iterator<std::string> text_end;
        // Tokenize string (space is a separator) using begin and end iteratos
        std::vector<std::string> tokens(text_iterator, text_end);

        if (tokens.size() > 0) {
            // Allocate array of C-strings where we will store tokens
            results = static_cast<char**>(malloc(tokens.size() * sizeof(char*)));
            if (results == NULL) {
                isc_throw(Unexpected, "unable to allocate array of c-strings");
            }
            // Store tokens in C-strings array
            for (int i = 0; i < tokens.size(); ++i) {
                char* cs = static_cast<char*>(malloc(tokens[i].length() + 1));
                strcpy(cs, tokens[i].c_str());
                results[i] = cs;
            }
            // Return number of tokens to calling function
            num = tokens.size();
        }
        return results;
    }
};

} // namespace isc::perfdhcp
} // namespace isc

#endif // __COMMAND_OPTIONS_HELPER_H
