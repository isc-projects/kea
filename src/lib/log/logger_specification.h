// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LOGGER_SPECIFICATION_H
#define LOGGER_SPECIFICATION_H

#include <stdint.h>
#include <stdlib.h>

#include <log/logger_level.h>
#include <log/output_option.h>

/// \brief Logger Specification
///
/// The logging configuration options are a list of logger specifications, each
/// of which represents a logger and the options for its appenders.
///
/// Unlike OutputOption (which is a struct), this contains a bit more
/// structure and is concealed in a class.

#include <vector>

namespace isc {
namespace log {

class LoggerSpecification {
public:
    typedef std::vector<OutputOption>::iterator         iterator;
    typedef std::vector<OutputOption>::const_iterator   const_iterator;

    /// \brief Constructor
    ///
    /// \param name Name of the logger.
    /// \param severity Severity at which this logger logs
    /// \param dbglevel Debug level
    /// \param additive true to cause message logged with this logger to be
    ///        passed to the parent for logging.
    LoggerSpecification(const std::string& name = "",
                        isc::log::Severity severity = isc::log::INFO,
                        int dbglevel = 0, bool additive = false) :
        name_(name), severity_(severity), dbglevel_(dbglevel),
        additive_(additive)
    {}

    /// \brief Set the name of the logger.
    ///
    /// \param name Name of the logger.
    void setName(const std::string& name) {
        name_ = name;
    }

    /// \return Return logger name.
    std::string getName() const {
        return name_;
    }

    /// \brief Set the severity.
    ///
    /// \param severity New severity of the logger.
    void setSeverity(isc::log::Severity severity) {
        severity_ = severity;
    }

    /// \return Return logger severity.
    isc::log::Severity getSeverity() const {
        return severity_;
    }

    /// \brief Set the debug level.
    ///
    /// \param dbglevel New debug level of the logger.
    void setDbglevel(int dbglevel) {
        dbglevel_ = dbglevel;
    }

    /// \return Return logger debug level
    int getDbglevel() const {
        return dbglevel_;
    }

    /// \brief Set the additive flag.
    ///
    /// \param additive New value of the additive flag.
    void setAdditive(bool additive) {
        additive_ = additive;
    }

    /// \return Return additive flag.
    bool getAdditive() const {
        return additive_;
    }

    /// \brief Add output option.
    ///
    /// \param option Option to add to the list.
    void addOutputOption(const OutputOption& option) {
        options_.push_back(option);
    }

    /// \return Iterator to start of output options.
    iterator begin() {
        return options_.begin();
    }

    /// \return Iterator to start of output options.
    const_iterator begin() const {
        return options_.begin();
    }

    /// \return Iterator to end of output options.
    iterator end() {
        return options_.end();
    }

    /// \return Iterator to end of output options.
    const_iterator end() const {
        return options_.end();
    }

    /// \return Number of output specification options.
    size_t optionCount() const {
        return options_.size();
    }

    /// \brief Reset back to defaults.
    void reset() {
        name_ = "";
        severity_ = isc::log::INFO;
        dbglevel_ = 0;
        additive_ = false;
        options_.clear();
    }

private:
    std::string                 name_;          ///< Logger name
    isc::log::Severity          severity_;      ///< Severity for this logger
    int                         dbglevel_;      ///< Debug level
    bool                        additive_;      ///< Chaining output
    std::vector<OutputOption>   options_;       ///< Logger options
};

} // namespace log
} // namespace isc

#endif // LOGGER_SPECIFICATION_H
