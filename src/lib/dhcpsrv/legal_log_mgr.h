// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEGAL_LOG_MGR_H
#define LEGAL_LOG_MGR_H

/// @file legal_log_mgr.h Defines the abstract class for backend stores.

#include <asiolink/io_service.h>
#include <database/database_connection.h>
#include <eval/token.h>
#include <exceptions/exceptions.h>

#include <boost/shared_ptr.hpp>

#include <fstream>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Thrown if a LegalLogMgr encounters an error.
class LegalLogMgrError : public isc::Exception {
public:
    LegalLogMgrError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what)
    {}
};

class LegalLogMgr;

/// @brief Defines a smart pointer to a LegalLogMgr.
typedef boost::shared_ptr<LegalLogMgr> LegalLogMgrPtr;

/// @brief Manger ID used by hook libraries to retrieve respective LegalLogMgr instance.
typedef uint64_t ManagerID;

/// @brief LegalLogMgr abstract class
class LegalLogMgr {
public:
    /// @brief Constructor.
    LegalLogMgr(const isc::db::DatabaseConnection::ParameterMap parameters) :
        timestamp_format_("%Y-%m-%d %H:%M:%S %Z"),
        parameters_(parameters) {
    }

    /// @brief Destructor.
    ///
    /// Derived destructors do call the close method.
    virtual ~LegalLogMgr() = default;

    /// @brief Parse database specification.
    ///
    /// Parse the configuration and check that the various keywords are
    /// consistent.
    ///
    /// @param parameters The library parameters.
    /// @param map The parameter map used by LegalLogMgr objects.
    static void parseConfig(const isc::data::ConstElementPtr& parameters, isc::db::DatabaseConnection::ParameterMap& map);

    /// @brief Parse database specification.
    ///
    /// Code adapted from isc::dhcp::DbAccessParser::parse
    ///
    /// Parse the configuration and check that the various keywords are
    /// consistent.
    ///
    /// @param parameters The library parameters.
    /// @param map The parameter map used by LegalLogMgr objects.
    static void parseDatabase(const isc::data::ConstElementPtr& parameters, isc::db::DatabaseConnection::ParameterMap& map);

    /// @brief Parse file specification.
    ///
    /// Parse the configuration and check that the various keywords are
    /// consistent.
    ///
    /// @param parameters The library parameters.
    static void parseFile(const isc::data::ConstElementPtr& parameters, isc::db::DatabaseConnection::ParameterMap& map);

    /// @brief Parse extra parameters which are not related to backend
    /// connection.
    ///
    /// @param parameters The library parameters.
    static void parseExtraParameters(const isc::data::ConstElementPtr& parameters, isc::db::DatabaseConnection::ParameterMap& map);

    /// @brief Opens the store.
    ///
    /// @param id the forensic backend manager ID.
    virtual void open(ManagerID id = 0) = 0;

    /// @brief Closes the store.
    virtual void close() = 0;

    /// @brief Appends a string to the store with a timestamp and address.
    ///
    /// @param text String to append
    /// @param addr Address or prefix
    /// @throw LegalLogMgrError if the write fails
    virtual void writeln(const std::string& text, const std::string& addr) = 0;

    /// @brief Return backend type
    ///
    /// Returns the type of the backend (e.g. "mysql", "logfile" etc.)
    ///
    /// @return Type of the backend.
    virtual std::string getType() const = 0;

    /// @brief Returns the current local date and time.
    ///
    /// This is exposed primarily to simplify testing.
    virtual struct tm currentTimeInfo() const;

    /// @brief Returns the current system time.
    ///
    /// This is exposed primarily to simplify testing.
    virtual struct timespec now() const;

    /// @brief Returns the current date and time as string.
    ///
    /// Returns the current local date and time as a string. The date and time
    /// is formatted according to the hook's timestamp_format parameter, or
    /// "%Y-%m-%d %H:%M:%S %Z" by default if not configured otherwise. The
    /// maximum length of the result is 128 bytes.
    ///
    /// @return std::string containing the formatted current date and time.
    /// @throw LegalLogMgrError if the result string is larger than 128 bytes.
    virtual std::string getNowString() const;

    /// @brief Returns the current date and time as a string using a specific
    /// strftime format string.
    ///
    /// Returns the current local date and time as a string based on the
    /// given format. Maximum length of the result is 128 bytes.
    ///
    /// @param format Desired format for the string. Permissible formatting is
    /// that supported by strftime plus the '%Q' extra format which adds the
    /// microseconds subunits. The default is: "%Y-%m-%d %H:%M:%S %Z".
    ///
    /// @return std::string containing the formatted current date and time.
    /// @throw LegalLogMgrError if the result string is larger than 128 bytes.
    virtual std::string getNowString(const std::string& format) const;

    /// @brief Returns a time as string.
    ///
    /// Returns the time as a string based on the given format.
    /// Maximum length of the result is 128 bytes.
    ///
    /// @param time Time to format.
    /// @param format Desired format for the string. Permissible formatting is
    /// that supported by strftime plus the '%Q' extra format which adds the
    /// microseconds subunits. The default is: "%Y-%m-%d %H:%M:%S %Z".
    ///
    /// @return std::string containing the formatted current date and time
    /// @throw LegalLogMgrError if the result string is larger than 128 bytes.
    static std::string getTimeString(const struct timespec& time, const std::string& format);

    /// @brief Translates seconds into a text string of days, hours, minutes
    /// and seconds.
    ///
    /// The output string will have the following format:
    ///
    ///    "{<d> day(s) }<h> hrs <m> min <s> secs"
    /// Examples:
    ///
    ///     0 hrs 0 min 30 secs
    ///     2 hrs 11 min 50 secs
    ///     1 day 1 hrs 0 min 0 secs
    ///     60 days 0 hrs 0 min 10 secs
    ///
    /// @param secs Number of seconds to convert
    /// @return String containing the duration text
    static std::string genDurationString(const uint32_t secs);

    /// @brief Creates a string of hex digit pairs from a vector of bytes.
    ///
    /// @param bytes Vector of bytes to convert
    /// @param delimiter String to use a delimiter, defaults to ":"
    ///
    /// @return std::string containing the hex output
    static std::string vectorHexDump(const std::vector<uint8_t>& bytes,
                                     const std::string& delimiter = ":");

    /// @brief Creates a string from a vector of printable bytes.
    ///
    /// This assumes that str::isPrintable was called and returned true.
    ///
    /// @param bytes Vector of bytes to convert
    static std::string vectorDump(const std::vector<uint8_t>& bytes);

    /// @brief Sets request extended format expression for custom logging.
    ///
    /// @param extended_format The request extended format expression.
    void setRequestFormatExpression(const std::string& extended_format);

    /// @brief Gets request extended format expression for custom logging.
    ///
    /// @return The request extended format expression.
    isc::dhcp::ExpressionPtr getRequestFormatExpression() {
        return (request_expression_);
    }

    /// @brief Sets response extended format expression for custom logging.
    ///
    /// @param extended_format The response extended format expression.
    void setResponseFormatExpression(const std::string& extended_format);

    /// @brief Gets response extended format expression for custom logging.
    ///
    /// @return The response extended format expression.
    isc::dhcp::ExpressionPtr getResponseFormatExpression() {
        return (response_expression_);
    }

    /// @brief Sets the timestamp format used for logging.
    ///
    /// @param format Desired format for the string. Permissible formatting is
    /// the one supported by strftime plus the '%Q' extra format which adds the
    /// microseconds subunits. The default is: "%Y-%m-%d %H:%M:%S %Z".
    void setTimestampFormat(const std::string& timestamp_format);

    /// @brief Gets the timestamp format used for logging.
    ///
    /// @return The format for the string. Permissible formatting is the one
    /// supported by strftime plus the '%Q' extra format which adds the
    /// microseconds subunits.
    std::string getTimestampFormat() {
        return (timestamp_format_);
    }

    /// @brief Return backend parameters
    ///
    /// Returns the backend parameters
    ///
    /// @return Parameters of the backend.
    virtual isc::db::DatabaseConnection::ParameterMap getParameters() const {
        return (parameters_);
    }

    /// @brief Sets backend parameters
    ///
    /// Sets the backend parameters
    ///
    /// @param parameter Parameters of the backend.
    virtual void setParameters(isc::db::DatabaseConnection::ParameterMap parameters) {
        parameters_ = parameters;
    }

    /// @brief Flag which indicates if the forensic log backend has at least one
    /// unusable connection.
    ///
    /// @return true if there is at least one unusable connection, false
    /// otherwise
    virtual bool isUnusable() {
        return (false);
    }

private:

    /// @brief The request custom parsed expression.
    isc::dhcp::ExpressionPtr request_expression_;

    /// @brief The response custom parsed expression.
    isc::dhcp::ExpressionPtr response_expression_;

    /// @brief The strftime format string for timestamps in the log file.
    std::string timestamp_format_;

    /// @brief The configuration parameters.
    isc::db::DatabaseConnection::ParameterMap parameters_;
};

/// @brief LegalLogMgr pool
typedef std::map<ManagerID, std::pair<isc::db::DatabaseConnection::ParameterMap, LegalLogMgrPtr>> LegalLogMgrPool;

/// @brief Describe what kind of event is being logged.
enum class Action { ASSIGN, RELEASE };

/// @brief Translates an Action into its corresponding verb.
///
/// @param action An Action.
/// @result the verb corresponding to the action.
const std::string actionToVerb(Action action);

} // namespace dhcp
} // namespace isc

#endif // LEGAL_LOG_MGR_H
