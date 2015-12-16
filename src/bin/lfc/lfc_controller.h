// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LFC_CONTROLLER_H
#define LFC_CONTROLLER_H

#include <exceptions/exceptions.h>
#include <string>

namespace isc {
namespace lfc {

/// @brief Exception thrown when the command line is invalid.
class InvalidUsage : public isc::Exception {
public:
    InvalidUsage(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exceptions thrown when a method is unable to manipulate
/// (remove or rename) a file.
class RunTimeFail : public isc::Exception {
public:
    RunTimeFail(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Process controller for LFC process
///
/// This class provides the LFC process functions. These are used to:
/// manage the command line, check for already running instances,
/// invoke the code to process the lease files and finally to rename
/// the lease files as necessary.
class LFCController {
public:
    /// @brief Defines the application name, it may be used to locate
    /// configuration data and appears in log statements.
    static const char* lfc_app_name_;

    /// @brief Defines the executable name, by convention this should match
    /// the executable name.
    static const char* lfc_bin_name_;

    /// @brief Constructor
    LFCController();

    /// @brief Destructor
    ~LFCController();

    /// @brief Acts as the primary entry point to start execution
    /// of the process.
    ///
    /// Provides the control logic to combine two lease files and
    /// weed out duplicate and expired leases. A description of
    /// the design can be found at http://kea.isc.org/wiki/LFCDesign
    ///
    /// -# parse command line arguments
    /// -# verify that it is the only instance
    /// -# create pid file
    /// -# read leases files
    /// -# write lease file
    /// -# move leases files
    /// -# cleanup artifacts
    /// -# remove pid file
    /// -# exit to the caller
    ///
    /// @param argc Number of strings in the @c argv array.
    /// @param argv Array of arguments passed in via the program's main function.
    /// @param test_mode is a bool value which indicates if @c launch
    /// should be run in the test mode (if true).  This parameter doesn't
    /// have a default value to force test implementers to enable test
    /// mode explicitly.
    ///
    /// @throw InvalidUsage if the command line parameters are invalid.
    void launch(int argc, char* argv[], const bool test_mode);

    /// @brief Process the command line arguments.
    ///
    /// It is the first step taken after the process has been launched.
    ///
    /// @param argc Number of strings in the @c argv array.
    /// @param argv Array of arguments passed in via the program's main function.
    ///
    /// @throw InvalidUsage if the command line parameters are invalid.
    void parseArgs(int argc, char* argv[]);

    /// @brief Rotate files.
    ///
    /// After we have a finish file, either from doing the cleanup or because
    /// a previous instance was interrupted, delete the work files (previous
    /// & copy) and move the finish file to be the new previous file.
    ///
    /// @throw RunTimeFail if we can't manipulate the files.
    void fileRotate() const;

    /// @name Accessor methods mainly used for testing purposes
    //@{

    /// @brief Gets the protocol version of the leaes files
    ///
    /// @return Returns the value of the DHCP protocol version.
    /// This can be 4 or 6 while in use and 0 before parsing
    /// any arguments.
    int getProtocolVersion() const {
      return (protocol_version_);
    }

    /// @brief Gets the config file name
    ///
    /// @return Returns the path to the config file
    std::string getConfigFile() const {
        return (config_file_);
    }

    /// @brief Gets the previous file name
    ///
    /// @return Returns the path to the previous file
    std::string getPreviousFile() const {
        return (previous_file_);
    }

    /// @brief Gets the copy file name
    ///
    /// @return Returns the path to the copy file
    std::string getCopyFile() const {
        return (copy_file_);
    }

    /// @brief Gets the output file name
    ///
    /// @return Returns the path to the output file
    std::string getOutputFile() const {
        return (output_file_);
    }

    /// @brief Gets the finish file name
    ///
    /// @return Returns the path to the finish file
    std::string getFinishFile() const {
        return (finish_file_);
    }

    /// @brief Gets the pid file name
    ///
    /// @return Returns the path to the pid file
    std::string getPidFile() const {
        return (pid_file_);
    }
    //@}

private:
    /// Version of the DHCP protocol used, i.e. 4 or 6.
    int protocol_version_;
    /// When true output the result of parsing the comamnd line
    bool verbose_;
    std::string config_file_;   ///< The path to the config file
    std::string previous_file_; ///< The path to the previous LFC file (if any)
    std::string copy_file_;     ///< The path to the copy of the lease file
    std::string output_file_;   ///< The path to the output file
    std::string finish_file_;   ///< The path to the finished output file
    std::string pid_file_;      ///< The path to the pid file

    /// @brief Prints the program usage text to std error.
    ///
    /// @param text is a string message which will preceded the usage text.
    /// This is intended to be used for specific usage violation messages.
    void usage(const std::string& text);

    /// @brief Gets the Kea version number for printing
    ///
    /// @param extended is a boolean indicating if the version string
    /// should be short (false) or extended (true)
    std::string getVersion(const bool extended) const;

    /// @brief Process files.
    ///
    /// Read in the leases from any previous & copy files we have and
    /// write the results out to the output file.  Upon completion of
    /// the write move the file to the finish file.
    ///
    /// @tparam LeaseObjectType A @c Lease4 or @c Lease6.
    /// @tparam LeaseFileType A @c CSVLeaseFile4 or @c CSVLeaseFile6.
    /// @tparam StorageType A @c Lease4Storage or @c Lease6Storage.
    ///
    /// @throw RunTimeFail if we can't move the file.
    template<typename LeaseObjectType, typename LeaseFileType, typename StorageType>
    void processLeases() const;

    ///@brief Start up the logging system
    ///
    /// @param test_mode indicates if we have have been started from the test
    /// system (true) or are running normally (false)
    void startLogger(const bool test_mode) const;
};

}; // namespace isc::lfc
}; // namespace isc

#endif // LFC_CONTROLLER_H
