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

#include <stdio.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>

#include <gtest/gtest.h>

#include <boost/scoped_array.hpp>

#include <exceptions/exceptions.h>

#include <log/macros.h>
#include <log/messagedef.h>
#include <log/logger.h>
#include <log/logger_level.h>
#include <log/logger_manager.h>
#include <log/logger_specification.h>
#include <log/output_option.h>

using namespace isc;
using namespace isc::log;
using namespace std;

/// \brief Derived logger
///
/// Only exists to make the protected static methods in Logger public for
/// test purposes.

class DerivedLogger : public isc::log::Logger {
public:
    DerivedLogger(std::string name) : isc::log::Logger(name)
    {}

    static void reset() {
        isc::log::Logger::reset();
    }
};

/// \brief LoggerManager Test
class LoggerManagerTest : public ::testing::Test {
public:
    LoggerManagerTest()
    {}
    ~LoggerManagerTest()
    {
        DerivedLogger::reset();
    }
};



// Convenience class to create the specification for the logger "filelogger",
// which, as the name suggests, logs to a file.  It remembers the file name and
// deletes the file when instance of the class is destroyed.
class SpecificationForFileLogger {
public:

    // Constructor - allocate file and create the specification object
    SpecificationForFileLogger() : spec_(), name_(""), logname_("filelogger") {

        // Set the output to a temporary file.
        OutputOption option;
        option.destination = OutputOption::DEST_FILE;
        option.filename = name_ = createTempFilename();

        // Set target output to the file logger.  The defauls indicate
        // INFO severity.
        spec_.setName(logname_);
        spec_.addOutputOption(option);
    }

    // Destructor, remove the file.  This is only a test, so ignore failures
    ~SpecificationForFileLogger() {
        if (! name_.empty()) {
            (void) unlink(name_.c_str());
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
    std::string createTempFilename() {

        // Get prefix.  Note that in all copies, strncpy does not guarantee
        // a null-terminated string, hence the explict setting of the last
        // character to NULL.
        ostringstream filename;

        if (getenv("TMPDIR") != NULL) {
            filename << getenv("TMPDIR");
        } else {
            filename << "/tmp";
        }
        filename << "/bind10_logger_manager_test_XXXXXX";

        cout << "*** file name before call is " << filename.str() << "\n";

        // Copy into writeable storage for the call to mkstemp
        boost::scoped_array<char> tname(new char[filename.str().size() + 1]);
        strcpy(tname.get(), filename.str().c_str());

        // Create file, close and delete it, and store the name for later.
        int filenum = mkstemp(tname.get());
        cout << "*** file name after call is " << tname.get() << "\n";
        if (filenum == -1) {
            isc_throw(Exception, "Unable to obtain unique filename");
        }
        close(filenum);
        unlink(tname.get());

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
    vector<LoggerSpecification> specVector(1, file_spec.getSpecification());
    LoggerManager manager;
    manager.process(specVector.begin(), specVector.end());

    // Try logging to the file.  Local scope is set to ensure that the logger
    // is destroyed before we reset the global logging.  We record what we
    // put in the file for a later comparison.
    vector<MessageID> ids;
    {
        Logger logger(file_spec.getLoggerName());

        LOG_FATAL(logger, MSG_DUPMSGID).arg("test");
        ids.push_back(MSG_DUPMSGID);

        LOG_FATAL(logger, MSG_DUPLNS).arg("test");
        ids.push_back(MSG_DUPLNS);
    }
    DerivedLogger::reset();

    // At this point, the output file should contain two lines with messages
    // LOGTEST_TEST1 and LOGTEST_TEST2 messages - test this.
    checkFileContents(file_spec.getFileName(), ids.begin(), ids.end());
}
