// Copyright (C) 2011, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <stdio.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>

#include <gtest/gtest.h>

#include <boost/scoped_array.hpp>
#include <boost/lexical_cast.hpp>

#include <exceptions/exceptions.h>

#include <log/macros.h>
#include <log/log_messages.h>
#include <log/logger.h>
#include <log/logger_level.h>
#include <log/logger_manager.h>
#include <log/logger_specification.h>
#include <log/message_initializer.h>
#include <log/output_option.h>

#include "tempdir.h"

#include <sys/types.h>
#include <regex.h>

using namespace isc;
using namespace isc::log;
using namespace std;

/// \brief LoggerManager Test
class LoggerManagerTest : public ::testing::Test {
public:
    LoggerManagerTest() {
        // Initialization of logging is done in main()
    }

    ~LoggerManagerTest() {
        LoggerManager::reset();
    }
};



// Convenience class to create the specification for the logger "filelogger",
// which, as the name suggests, logs to a file.  It remembers the file name and
// deletes the file when instance of the class is destroyed.
class SpecificationForFileLogger {
public:

    // Constructor - allocate file and create the specification object
    SpecificationForFileLogger() : spec_(), name_(createTempFilename()),
                                   logname_("filelogger") {

        // Set the output to a temporary file.
        OutputOption option;
        option.destination = OutputOption::DEST_FILE;
        option.filename = name_;

        // Set target output to the file logger.  The defaults indicate
        // INFO severity.
        spec_.setName(logname_);
        spec_.addOutputOption(option);
    }

    // Destructor, remove the file.  This is only a test, so ignore failures
    ~SpecificationForFileLogger() {
        if (! name_.empty()) {
            static_cast<void>(remove(name_.c_str()));

            // Depending on the log4cplus version, a lock file may also be
            // created.
            static_cast<void>(remove((name_ + ".lock").c_str()));
        }
    }

    // Return reference to the logging specification for this loggger
    LoggerSpecification& getSpecification() {
        return spec_;
    }

    // Return name of the logger
    string getLoggerName() const {
        return logname_;
    }

    // Return name of the file
    string getFileName() const {
        return name_;
    }

    // Create temporary filename
    //
    // The compiler warns against tmpnam() and suggests mkstemp instead.
    // Unfortunately, this creates the filename and opens it.  So we need to
    // close and delete the file before returning the name.  Also, the name
    // is based on the template supplied and the name of the temporary
    // directory may vary between systems.  So translate TMPDIR and if that
    // does not exist, use /tmp.
    //
    // \return Temporary file name
    static std::string createTempFilename() {
        string filename = TEMP_DIR + "/kea_logger_manager_test_XXXXXX";

        // Copy into writeable storage for the call to mkstemp
        boost::scoped_array<char> tname(new char[filename.size() + 1]);
        strcpy(tname.get(), filename.c_str());

        // Create file, close and delete it, and store the name for later.
        // There is still a race condition here, albeit a small one.
        int filenum = mkstemp(tname.get());
        if (filenum == -1) {
            isc_throw(Exception, "Unable to obtain unique filename");
        }
        close(filenum);

        return (string(tname.get()));
    }


private:
    LoggerSpecification     spec_;      // Specification for this file logger
    string                  name_;      // Name of the output file
    string                  logname_;   // Name of this logger
};


// Convenience function to read an output log file and check that each line
// contains the expected message ID
//
// \param filename Name of the file to check
// \param start Iterator pointing to first expected message ID
// \param finish Iterator pointing to last expected message ID
template <typename T>
void checkFileContents(const std::string& filename, T start, T finish) {

    // Access the file for input
    ifstream infile(filename.c_str());
    if (! infile.good()) {
        FAIL() << "Unable to open the logging file " << filename;
    }

    // Iterate round the expected message IDs and check that they appear in
    // the string.
    string line;    // Line read from the file

    T i = start;    // Iterator
    getline(infile, line);
    int lineno = 1;

    while ((i != finish) && (infile.good())) {

        // Check that the message ID appears in the line.
        EXPECT_TRUE(line.find(string(*i)) != string::npos)
            << "Expected to find " << string(*i) << " on line " << lineno
            << " of logging file " << filename;

        // Go for the next line
        ++i;
        getline(infile, line);
        ++lineno;
    }

    // Why did the loop end?
    EXPECT_TRUE(i == finish) << "Did not reach the end of the message ID list";
    EXPECT_TRUE(infile.eof()) << "Did not reach the end of the logging file";

    // File will close when the instream is deleted at the end of this
    // function.
}

// Check that the logger correctly creates something logging to a file.
TEST_F(LoggerManagerTest, FileLogger) {

    // Create a specification for the file logger and use the manager to
    // connect the "filelogger" logger to it.
    SpecificationForFileLogger file_spec;

    // For the first test, we want to check that the file is created
    // if it does not already exist.  So delete the temporary file before
    // logging the first message.
    static_cast<void>(remove(file_spec.getFileName().c_str()));

    // Set up the file appenders.
    LoggerManager manager;
    manager.process(file_spec.getSpecification());

    // Try logging to the file.  Local scope is set to ensure that the logger
    // is destroyed before we reset the global logging.  We record what we
    // put in the file for a later comparison.
    vector<MessageID> ids;
    {

        // Scope-limit the logger to ensure it is destroyed after the brief
        // check.  This adds weight to the idea that the logger will not
        // keep the file open.
        Logger logger(file_spec.getLoggerName().c_str());

        LOG_FATAL(logger, LOG_DUPLICATE_MESSAGE_ID).arg("test");
        ids.push_back(LOG_DUPLICATE_MESSAGE_ID);

        LOG_FATAL(logger, LOG_DUPLICATE_NAMESPACE).arg("test");
        ids.push_back(LOG_DUPLICATE_NAMESPACE);
    }
    LoggerManager::reset();

    // At this point, the output file should contain two lines with messages
    // LOG_DUPLICATE_MESSAGE_ID and LOG_DUPLICATE_NAMESPACE messages - test this.
    checkFileContents(file_spec.getFileName(), ids.begin(), ids.end());

    // Re-open the file (we have to assume that it was closed when we
    // reset the logger - there is no easy way to check) and check that
    // new messages are appended to it.  We use the alternative
    // invocation of process() here to check it works.
    vector<LoggerSpecification> spec(1, file_spec.getSpecification());
    manager.process(spec.begin(), spec.end());

    // Create a new instance of the logger and log three more messages.
    Logger logger(file_spec.getLoggerName().c_str());

    LOG_FATAL(logger, LOG_NO_SUCH_MESSAGE).arg("test");
    ids.push_back(LOG_NO_SUCH_MESSAGE);

    LOG_FATAL(logger, LOG_INVALID_MESSAGE_ID).arg("test").arg("test2");
    ids.push_back(LOG_INVALID_MESSAGE_ID);

    LOG_FATAL(logger, LOG_NO_MESSAGE_ID).arg("42");
    ids.push_back(LOG_NO_MESSAGE_ID);

    // Close the file and check again
    LoggerManager::reset();
    checkFileContents(file_spec.getFileName(), ids.begin(), ids.end());
}

// Check if the file rolls over when it gets above a certain size.
TEST_F(LoggerManagerTest, FileSizeRollover) {
    // Set to a suitable minimum that log4cplus can copy with
    static const size_t SIZE_LIMIT = 204800;

    // Set up the name of the file.
    SpecificationForFileLogger file_spec;
    LoggerSpecification& spec = file_spec.getSpecification();

    // Expand the option to ensure that a maximum version size is set.
    LoggerSpecification::iterator opt = spec.begin();
    EXPECT_TRUE(opt != spec.end());
    opt->maxsize = SIZE_LIMIT;    // Bytes
    opt->maxver = 2;

    // The current current output file does not exist (the creation of file_spec
    // ensures that.  Check that previous versions don't either.
    vector<string> prev_name;
    for (int i = 0; i < 3; ++i) {
        prev_name.push_back(file_spec.getFileName() + "." +
                            boost::lexical_cast<string>(i + 1));
        (void) remove(prev_name[i].c_str());
    }

    // Generate an argument for a message that ensures that the message when
    // logged will be over that size.
    string big_arg(SIZE_LIMIT, 'x');

    // Set up the file logger
    LoggerManager manager;
    manager.process(spec);

    // Log the message twice using different message IDs.  This should generate
    // three files as for the log4cplus implementation, the files appear to
    // be rolled after the message is logged.
    {
        Logger logger(file_spec.getLoggerName().c_str());
        LOG_FATAL(logger, LOG_NO_SUCH_MESSAGE).arg(big_arg);
        LOG_FATAL(logger, LOG_DUPLICATE_NAMESPACE).arg(big_arg);
    }

    // Check them.
    LoggerManager::reset();     // Ensure files are closed

    vector<MessageID> ids;
    ids.push_back(LOG_NO_SUCH_MESSAGE);
    checkFileContents(prev_name[1], ids.begin(), ids.end());

    ids.clear();
    ids.push_back(LOG_DUPLICATE_NAMESPACE);
    checkFileContents(prev_name[0], ids.begin(), ids.end());

    // Log another message and check that the files have rotated and that
    // a .3 version does not exist.
    manager.process(spec);
    {
        Logger logger(file_spec.getLoggerName().c_str());
        LOG_FATAL(logger, LOG_NO_MESSAGE_TEXT).arg("42").arg(big_arg);
    }

    LoggerManager::reset();     // Ensure files are closed

    // Check that the files have moved.
    ids.clear();
    ids.push_back(LOG_DUPLICATE_NAMESPACE);
    checkFileContents(prev_name[1], ids.begin(), ids.end());

    ids.clear();
    ids.push_back(LOG_NO_MESSAGE_TEXT);
    checkFileContents(prev_name[0], ids.begin(), ids.end());

    // ... and check that the .3 version does not exist.
    ifstream file3(prev_name[2].c_str(), ifstream::in);
    EXPECT_FALSE(file3.good());

    // Tidy up
    for (vector<string>::size_type i = 0; i < prev_name.size(); ++i) {
       (void) remove(prev_name[i].c_str());
    }
}

namespace { // begin unnamed namespace

// When we begin to use C++11, we could replace use of POSIX API with
// <regex>.

class RegexHolder {
public:
    RegexHolder(const char* expr, const int flags = REG_EXTENDED) {
        const int rc = regcomp(&regex_, expr, flags);
        if (rc) {
            regfree(&regex_);
            throw;
        }
    }

    ~RegexHolder() {
        regfree(&regex_);
    }

    regex_t* operator*() {
        return (&regex_);
    }

private:
    regex_t regex_;
};

} // end of unnamed namespace

// Check that the logger correctly outputs the full formatted layout
// pattern.
TEST_F(LoggerManagerTest, checkLayoutPattern) {
    // Create a specification for the file logger and use the manager to
    // connect the "filelogger" logger to it.
    SpecificationForFileLogger file_spec;

    // For the first test, we want to check that the file is created
    // if it does not already exist.  So delete the temporary file before
    // logging the first message.
    static_cast<void>(remove(file_spec.getFileName().c_str()));

    // Set up the file appenders.
    LoggerManager manager;
    manager.process(file_spec.getSpecification());

    // Try logging to the file.  Local scope is set to ensure that the logger
    // is destroyed before we reset the global logging.
    {
        Logger logger(file_spec.getLoggerName().c_str());
        LOG_FATAL(logger, LOG_DUPLICATE_MESSAGE_ID).arg("test");
    }

    LoggerManager::reset();

    // Access the file for input
    const std::string& filename = file_spec.getFileName();
    ifstream infile(filename.c_str());
    if (! infile.good()) {
        FAIL() << "Unable to open the logging file " << filename;
    }

    std::string line;
    std::getline(infile, line);

    RegexHolder regex(// %D{%Y-%m-%d %H:%M:%S.%q}
                      "^[[:digit:]]{4}-[[:digit:]]{2}-[[:digit:]]{2}[[:space:]]"
                      "[[:digit:]]{2}:[[:digit:]]{2}:[[:digit:]]{2}\\.[[:digit:]]+[[:space:]]"
                      // %-5p
                      "[[:alpha:]]{1,5}[[:space:]]"
                      // [%c/%i]
                      "\\[[[:alnum:]\\-\\.]+/[[:digit:]]+\\][[:space:]]"
                      );

    const int re = regexec(*regex, line.c_str(), 0, NULL, 0);
    ASSERT_EQ(0, re)
        << "Logged message does not match expected layout pattern";
}

// Check that after calling the logDuplicatedMessages, the duplicated
// messages are removed.
TEST_F(LoggerManagerTest, logDuplicatedMessages) {
    // Original set should not have duplicates.
    ASSERT_EQ(0, MessageInitializer::getDuplicates().size());

    // This just defines 1, but we'll add it a number of times.
    const char* dupe[] = {
        "DUPE", "dupe",
        NULL
    };
    const MessageInitializer init_message_initializer_1(dupe);
    const MessageInitializer init_message_initializer_2(dupe);

    MessageInitializer::loadDictionary();
    // Should have a duplicate now.
    ASSERT_EQ(1, MessageInitializer::getDuplicates().size());

    // The logDuplicatedMessages, besides logging, should also remove the
    // duplicates.
    LoggerManager::logDuplicatedMessages();
    ASSERT_EQ(0, MessageInitializer::getDuplicates().size());
}
