// Copyright (C) 2012, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef COMMAND_OPTIONS_HELPER_H
#define COMMAND_OPTIONS_HELPER_H

#include "../command_options.h"
#include <exceptions/exceptions.h>

#include <assert.h>
#include <iterator>
#include <cstring>
#include <string>
#include <vector>


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
        /// Deallocates wrapped array of C-strings.
        ~ArgvPtr() {
            if (argv_ != NULL) {
                for(int i = 0; i < argc_; ++i) {
                    delete[] (argv_[i]);
                    argv_[i] = NULL;
                }
                delete[] (argv_);
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
    /// \return true if program has been run in help or version mode ('h' or 'v' flag).
    static bool process(const std::string& cmdline) {
        CommandOptions& opt = CommandOptions::instance();
        int argc = 0;
        char** argv = tokenizeString(cmdline, argc);
        ArgvPtr args(argv, argc);
        opt.reset();
        return (opt.parse(args.getArgc(), args.getArgv()));
    }

private:

    /// \brief Split string to the array of C-strings.
    ///
    /// \param text_to_split string to be splited.
    /// \param [out] num number of substrings returned.
    /// \param std::bad_alloc if allocation of C-strings failed.
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

        if (!tokens.empty()) {
            // Allocate array of C-strings where we will store tokens
            results = new char*[tokens.size()];
            // Store tokens in C-strings array
            for (size_t i = 0; i < tokens.size(); ++i) {
                size_t cs_size = tokens[i].length() + 1;
                char* cs = new char[cs_size];
                strncpy(cs, tokens[i].c_str(), cs_size);
                assert(cs[cs_size - 1] == '\0');
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

#endif // COMMAND_OPTIONS_HELPER_H
