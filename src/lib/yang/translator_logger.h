// Copyright (C) 2018-2019,2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TRANSLATOR_LOGGER_H
#define ISC_TRANSLATOR_LOGGER_H 1

#include <yang/translator.h>
#include <list>

namespace isc {
namespace yang {

/// Logger translation between YANG and JSON
///
/// JSON syntax for all Kea servers with loggers is:
/// @code
/// {
///     "name": <name>,
///     "output_options": [ <output options> ],
///     "severity": <severity>,
///     "debuglevel": <debug level>,
///     "user-context": { <json map> },
///     "comment": <comment>
/// }
/// @endcode
///
/// JSON syntax for all Kea server for output options is:
/// @code
/// {
///    "output": <output, e.g. log file name>,
///    "maxver": <maximum file version>,
///    "maxsize": <maximum file size>,
///    "flush": <flush flag>,
///    "pattern": <custom layout>
/// }
/// @endcode
///
/// YANG syntax for loggers is:
/// @code
/// +--rw logger* [name]
///    +--rw name             string
///    +--rw output-option* [output]
///    |  +--rw output        string
///    |  +--rw flush?        boolean
///    |  +--rw maxsize?      uint32
///    |  +--rw maxver?       uint32
///    |  +--rw pattern?      string
///    +--rw debuglevel?      uint8
///    +--rw severity?        enumeration
///    +--rw user-context?    user-context
/// @endcode
///
/// An example in JSON and YANG formats:
/// @code
/// [
///     {
///         "name": "foo",
///         "severity": "WARN",
///         "output_options":
///             [
///                 {
///                     "output": "/bar",
///                     "maxver": 10
///                 }
///             ]
///     }
/// ]
/// @endcode
/// @code
///  /kea-dhcp4-server:config (container)
///  /kea-dhcp4-server:config/...
///  /kea-dhcp4-server:config/logger[name='foo'] (list instance)
///  /kea-dhcp4-server:config/logger[name='foo']/name = foo
///  /kea-dhcp4-server:config/logger[name='foo']/
///     option[output='/bar'] (list instance)
///  /kea-dhcp4-server:config/logger[name='foo']/
///     option[output='/bar']/option = /bar
///  /kea-dhcp4-server:config/logger[name='foo']/
///     option[output='/bar']/maxver = 10
///  /kea-dhcp4-server:config/logger[name='foo']/severity = WARN
/// @endcode

/// @brief A translator class for converting a logger between
/// YANG and JSON.
///
/// Currently supports all kea models:
/// - kea-dhcp4-server
/// - kea-dhcp6-server
/// - kea-dhcp-ddns
/// - kea-ctrl-agent
class TranslatorLogger : virtual public TranslatorBasic {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorLogger(sysrepo::S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorLogger();

    /// @brief Get and translate a logger from YANG to JSON.
    ///
    /// @param xpath The xpath of the logger.
    /// @return JSON representation of the logger.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getLogger(const std::string& xpath);

    /// @brief Translate and set logger from JSON to YANG.
    ///
    /// @param xpath The xpath of the logger.
    /// @param elem The JSON element.
    void setLogger(const std::string& xpath, isc::data::ConstElementPtr elem);

protected:
    /// @brief Get and translate an output option from YANG to JSON.
    ///
    /// @param xpath The xpath of the output option.
    /// @return JSON representation of the output option.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getOutputOption(const std::string& xpath);

    /// @brief Get and translate output options from YANG to JSON.
    ///
    /// @param xpath The xpath of output options.
    /// @return JSON representation of output options.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getOutputOptions(const std::string& xpath);

    /// @brief Translate and set an output option from JSON to YANG.
    ///
    /// @param xpath The xpath of the output option.
    /// @param elem The JSON element.
    void setOutputOption(const std::string& xpath,
                         isc::data::ConstElementPtr elem);

    /// @brief Translate and set output options from JSON to YANG.
    ///
    /// @param xpath The xpath of the output options.
    /// @param elem The JSON element.
    /// @throw BadValue on an output option without output.
    void setOutputOptions(const std::string& xpath,
                          isc::data::ConstElementPtr elem);

    /// @brief getLogger JSON for loggers.
    ///
    /// @param xpath The xpath of the logger.
    /// @return JSON representation of the logger.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getLoggerKea(const std::string& xpath);

    /// @brief setLogger for loggers.
    ///
    /// @param xpath The xpath of the logger.
    /// @param elem The JSON element.
    void setLoggerKea(const std::string& xpath,
                      isc::data::ConstElementPtr elem);
};

/// @brief A translator class for converting a logger list between
/// YANG and JSON.
///
/// Currently supports all kea servers and agents. Specific to Kea.
class TranslatorLoggers : virtual public TranslatorLogger {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorLoggers(sysrepo::S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorLoggers();

    /// @brief Get and translate loggeres from YANG to JSON.
    ///
    /// @param xpath The xpath of loggers.
    /// @return JSON representation of loggers.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ConstElementPtr getLoggers(const std::string& xpath);

    /// @brief Translate and set loggeres from JSON to YANG.
    ///
    /// @param xpath The xpath of loggers.
    /// @param elem The JSON element.
    void setLoggers(const std::string& xpath,
                      isc::data::ConstElementPtr elem);

protected:
    /// @brief getLoggers JSON for loggers.
    ///
    /// @param xpath The xpath of loggers.
    /// @return JSON representation of  loggers.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getLoggersKea(const std::string& xpath);

    /// @brief setLoggers for loggers.
    ///
    /// @param xpath The xpath of loggers.
    /// @param elem The JSON element.
    /// @throw BadValue on a logger without name.
    void setLoggersKea(const std::string& xpath,
                       isc::data::ConstElementPtr elem);
};

}  // namespace yang
}  // namespace isc

#endif // ISC_TRANSLATOR_LOGGER_H
