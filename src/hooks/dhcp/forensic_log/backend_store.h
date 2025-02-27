// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef BACKEND_STORE_H
#define BACKEND_STORE_H

/// @file backend_store.h Defines the abstract class for backend stores.

#include <asiolink/io_service.h>
#include <database/database_connection.h>
#include <eval/token.h>
#include <exceptions/exceptions.h>

#include <boost/shared_ptr.hpp>

#include <fstream>
#include <string>

namespace isc {
namespace legal_log {

/// @brief Thrown if a BackendStore encounters an error.
class BackendStoreError : public isc::Exception {
public:
    BackendStoreError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what)
    {}
};

class BackendStore;

/// @brief Defines a smart pointer to a BackendStore.
typedef boost::shared_ptr<BackendStore> BackendStorePtr;

/// @brief BackendStore abstract class
class BackendStore {
public:
    /// @brief Constructor.
    BackendStore() : timestamp_format_("%Y-%m-%d %H:%M:%S %Z") {
    }

    /// @brief Destructor.
    ///
    /// Derived destructors do call the close method.
    virtual ~BackendStore() = default;

    /// @brief Parse file specification.
    ///
    /// It supports the following parameters via the Hook Library Parameter
    /// mechanism:
    ///
    /// @b path - Directory in which the legal file(s) will be written.
    /// The default value is "<prefix>/var/lib/kea". The directory must exist.
    ///
    /// @b base-name - An arbitrary value which is used in conjunction
    /// with current system date to form the current legal file name.
    /// It defaults to "kea-legal".
    ///
    /// Legal file names will have the form:
    ///
    ///     <path>/<base-name>.<CCYYMMDD>.txt
    ///     <path>/<base-name>.<TXXXXXXXXXXXXXXXXXXXX>.txt
    ///
    /// @param parameters The library parameters.
    static void parseFile(const isc::data::ConstElementPtr& parameters);

    /// @brief Parse database specification.
    ///
    /// Code adapted from isc::dhcp::DbAccessParser::parse
    ///
    /// Parse the configuration and check that the various keywords are
    /// consistent.
    ///
    /// @param parameters The library parameters.
    static void parseDatabase(const isc::data::ConstElementPtr& parameters);

    /// @brief Parse extra parameters which are not related to backend
    /// connection.
    ///
    /// @param parameters The library parameters.
    static void parseExtraParameters(const isc::data::ConstElementPtr& parameters);

    /// @brief Opens the store.
    virtual void open() = 0;

    /// @brief Closes the store.
    virtual void close() = 0;

    /// @brief Appends a string to the store with a timestamp and address.
    ///
    /// @param text String to append
    /// @param addr Address or prefix
    /// @throw BackendStoreError if the write fails
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
    /// @throw BackendStoreError if the result string is larger than 128 bytes.
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
    /// @throw BackendStoreError if the result string is larger than 128 bytes.
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
    /// @throw BackendStoreError if the result string is larger than 128 bytes.
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

    /// @brief Get the hook I/O service.
    ///
    /// @return the hook I/O service.
    static isc::asiolink::IOServicePtr getIOService() {
        return (io_service_);
    }

    /// @brief Set the hook I/O service.
    ///
    /// @param io_service the hook I/O service.
    static void setIOService(isc::asiolink::IOServicePtr io_service) {
        io_service_ = io_service;
    }

    /// @brief Set backend parameters.
    ///
    /// Set the backend parameters.
    ///
    /// @param parameters The backend parameters.
    static void setParameters(const isc::db::DatabaseConnection::ParameterMap& parameters) {
        parameters_ = parameters;
    }

    /// @brief Get backend parameters.
    ///
    /// Get the backend parameters.
    ///
    /// @return The backend parameters.
    static isc::db::DatabaseConnection::ParameterMap getParameters() {
        return (parameters_);
    }

    /// @brief Set hook configuration.
    ///
    /// Set the hook configuration.
    ///
    /// @param config The hook configuration.
    static void setConfig(const isc::data::ConstElementPtr& config) {
        config_ = config;
    }

    /// @brief Get hook configuration.
    ///
    /// Get the hook configuration.
    ///
    /// @return The hook configuration.
    static isc::data::ConstElementPtr getConfig() {
        return (config_);
    }

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

    /// @brief Return the BackendStore instance.
    ///
    /// @return The BackendStore instance.
    static BackendStorePtr& instance() {
        static BackendStorePtr backend_store;
        return (backend_store);
    }

protected:

    /// @brief The hook I/O service.
    static isc::asiolink::IOServicePtr io_service_;

    /// @brief The parameters used to connect to the backend.
    static isc::db::DatabaseConnection::ParameterMap parameters_;

    /// @brief The hook configuration.
    static isc::data::ConstElementPtr config_;

private:

    /// @brief The request custom parsed expression.
    isc::dhcp::ExpressionPtr request_expression_;

    /// @brief The response custom parsed expression.
    isc::dhcp::ExpressionPtr response_expression_;

    /// @brief The strftime format string for timestamps in the log file.
    std::string timestamp_format_;
};

/// @brief Describe what kind of event is being logged.
enum class Action { ASSIGN, RELEASE };

/// @brief Translates an Action into its corresponding verb.
///
/// @param action An Action.
/// @result the verb corresponding to the action.
const std::string actionToVerb(Action action);

} // namespace legal_log
} // namespace isc

#endif
