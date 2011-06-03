// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __CCSESSION_H
#define __CCSESSION_H 1

#include <string>

#include <config/config_data.h>
#include <config/module_spec.h>
#include <cc/session.h>
#include <cc/data.h>

namespace isc {
namespace config {

///
/// \brief Creates a standard config/command level success answer message
///        (i.e. of the form { "result": [ 0 ] }
/// \return Standard command/config success answer message
isc::data::ConstElementPtr createAnswer();

///
/// \brief Creates a standard config/command level answer message
///        (i.e. of the form { "result": [ rcode, arg ] }
/// If rcode != 0, arg must be a StringElement
///
/// \param rcode The return code (0 for success)
/// \param arg For rcode == 0, this is an optional argument of any
///            Element type. For rcode == 1, this argument is mandatory,
///            and must be a StringElement containing an error description
/// \return Standard command/config answer message
isc::data::ConstElementPtr createAnswer(const int rcode,
                                        isc::data::ConstElementPtr arg);

///
/// \brief Creates a standard config/command level answer message
/// (i.e. of the form { "result": [ rcode, arg ] }
///
/// \param rcode The return code (0 for success)
/// \param arg A string to put into the StringElement argument
/// \return Standard command/config answer message
isc::data::ConstElementPtr createAnswer(const int rcode,
                                        const std::string& arg);

///
/// Parses a standard config/command level answer message
/// 
/// \param rcode This value will be set to the return code contained in
///              the message
/// \param msg The message to parse
/// \return The optional argument in the message, or an empty ElementPtr
///         if there was no argument. If rcode != 0, this contains a
///         StringElement with the error description.
isc::data::ConstElementPtr parseAnswer(int &rcode,
                                       isc::data::ConstElementPtr msg);

///
/// \brief Creates a standard config/command command message with no
/// argument (of the form { "command": [ "my_command" ] }
/// 
/// \param command The command string
/// \return The created message
isc::data::ConstElementPtr createCommand(const std::string& command);

///
/// \brief Creates a standard config/command command message with the
/// given argument (of the form { "command": [ "my_command", arg ] }
/// 
/// \param command The command string
/// \param arg The optional argument for the command. This can be of 
///        any Element type, but it should conform to the .spec file.
/// \return The created message
isc::data::ConstElementPtr createCommand(const std::string& command,
                                         isc::data::ConstElementPtr arg);

///
/// \brief Parses the given command into a string containing the actual
///        command and an ElementPtr containing the optional argument.
///
/// Raises a CCSessionError if this is not a well-formed command
///
/// Example code: (command_message is a ConstElementPtr that is
/// passed here)
/// \code
/// ElementPtr command_message = Element::fromJSON("{ \"command\": [\"foo\", { \"bar\": 123 } ] }");
/// try {
///     ConstElementPtr args;
///     std::string command_str = parseCommand(args, command_message);
///     if (command_str == "foo") {
///         std::cout << "The command 'foo' was given" << std::endl;
///         if (args->contains("bar")) {
///             std::cout << "It had argument name 'bar' set, which has"
///                       << "value " 
///                       << args->get("bar")->intValue();
///         }
///     } else {
///         std::cout << "Unknown command '" << command_str << std::endl;
///     }
/// } catch (CCSessionError cse) {
///     std::cerr << "Bad command in CC Session: "
///     << cse.what() << std::endl;
/// }
/// \endcode
/// 
/// \param arg This value will be set to the ElementPtr pointing to
///        the argument, or to an empty Map (ElementPtr) if there was none.
/// \param command The command message containing the command (as made
///        by createCommand()
/// \return The command name
std::string parseCommand(isc::data::ConstElementPtr& arg,
                         isc::data::ConstElementPtr command);


///
/// \brief A standard cc session exception that is thrown if a function
/// is there is a problem with one of the messages
///
// todo: include types and called function in the exception
class CCSessionError : public isc::Exception {
public:
    CCSessionError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// \brief This exception is thrown if the constructor fails
///
class CCSessionInitError : public isc::Exception {
public:
    CCSessionInitError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// \brief This module keeps a connection to the command channel,
/// holds configuration information, and handles messages from
/// the command channel
///
class ModuleCCSession : public ConfigData {
public:
    /**
     * Initialize a config/command session
     *
     * @param spec_file_name The name of the file containing the
     *                        module specification.
     * @param session A Session object over which configuration and command
     * data are exchanged.
     * @param config_handler A callback function pointer to be called when
     * configuration of the local module needs to be updated.
     * This must refer to a valid object of a concrete derived class of
     * AbstractSession without establishing the session.
     * @param handle_logging If true, the ModuleCCSession will automatically
     * take care of logging configuration through the virtual Logging config
     * module.
     *
     * Note: the design decision on who is responsible for establishing the
     * session is in flux, and may change in near future.
     *
     * \exception CCSessionInitError when the initialization fails,
     *            either because the file cannot be read or there is
     *            a communication problem with the config manager.
     *
     * @param command_handler A callback function pointer to be called when
     * a control command from a remote agent needs to be performed on the
     * local module.
     * @start_immediately If true (default), start listening to new commands
     * and configuration changes asynchronously at the end of the constructor;
     * if false, it will be delayed until the start() method is explicitly
     * called. (This is a short term workaround for an initialization trouble.
     * We'll need to develop a cleaner solution, and then remove this knob)
     */
    ModuleCCSession(const std::string& spec_file_name,
                    isc::cc::AbstractSession& session,
                    isc::data::ConstElementPtr(*config_handler)(
                        isc::data::ConstElementPtr new_config) = NULL,
                    isc::data::ConstElementPtr(*command_handler)(
                        const std::string& command,
                        isc::data::ConstElementPtr args) = NULL,
                    bool start_immediately = true,
                    bool handle_logging = false
                    );

    /// Start receiving new commands and configuration changes asynchronously.
    ///
    /// This method must be called only once, and only when the ModuleCCSession
    /// was constructed with start_immediately being false.  Otherwise
    /// CCSessionError will be thrown.
    ///
    /// As noted in the constructor, this method should be considered a short
    /// term workaround and will be removed in future.
    void start();

    /**
     * Optional optimization for checkCommand loop; returns true
     * if there are unhandled queued messages in the cc session.
     * (if either this is true or there is data on the socket found
     * by the select() call on getSocket(), run checkCommand())
     * 
     * @return true if there are unhandled queued messages
     */
    bool hasQueuedMsgs() const;

    /**
     * Check if there is a command or config change on the command
     * session. If so, the appropriate handler is called if set.
     * If not set, a default answer is returned.
     * This is a non-blocking read; if there is nothing this function
     * will return 0.
     */
    int checkCommand();

    /**
     * The config handler function should expect an ElementPtr containing
     * the full configuration where non-default values have been set.
     * Later we might want to think about more granular control
     * (i.e. this does not scale to for instance lists containing
     * 100000 zones, where the whole list is passed every time a single
     * thing changes)
     */
    void setConfigHandler(isc::data::ConstElementPtr(*config_handler)(
                              isc::data::ConstElementPtr new_config))
    {
        config_handler_ = config_handler;
    }

    /**
     * Set a command handler; the function that is passed takes an
     * ElementPtr, pointing to a list element, containing
     * [ module_name, command_name, arg1, arg2, ... ]
     * The returned ElementPtr should look like
     * { "result": [ return_value, result_value ] }
     * result value here is optional and depends on the command
     *
     * This protocol is very likely to change.
     */
    void setCommandHandler(isc::data::ConstElementPtr(*command_handler)(
                               const std::string& command,
                               isc::data::ConstElementPtr args))
    {
        command_handler_ = command_handler;
    }

    /**
     * Gives access to the configuration values of a different module
     * Once this function has been called with the name of the specification
     * file or the module you want the configuration of, you can use
     * \c getRemoteConfigValue() to get a specific setting.
     * Changes are automatically updated, and you can specify handlers
     * for those changes. This function will subscribe to the relevant module
     * channel.
     *
     * This method must be called before calling the \c start() method on the
     * ModuleCCSession (it also implies the ModuleCCSession must have been
     * constructed with start_immediately being false).
     *
     * \param spec_name This specifies the module to add. It is either a
     *                  filename of the spec file to use or a name of module
     *                  (in case it's a module name, the spec data is
     *                  downloaded from the configuration manager, therefore
     *                  the configuration manager must know it). If
     *                  spec_is_filename is true (the default), then a
     *                  filename is assumed, otherwise a module name.
     * \param handler The handler function called whenever there's a change.
     *                Called once initally from this function. May be NULL
     *                if you don't want any handler to be called and you're
     *                fine with requesting the data through
     *                getRemoteConfigValue() each time.
     *
     *                The handler should not throw, or it'll fall trough and
     *                the exception will get into strange places, probably
     *                aborting the application.
     * \param spec_is_filename Says if spec_name is filename or module name.
     * \return The name of the module specified in the given specification
     *         file
     */
    std::string addRemoteConfig(const std::string& spec_name,
                                void (*handler)(const std::string& module_name,
                                                isc::data::ConstElementPtr
                                                update) = NULL,
                                bool spec_is_filename = true);

    /**
     * Removes the module with the given name from the remote config
     * settings. If the module was not added with \c addRemoteConfig(),
     * nothing happens. If there was a handler for this config, it is
     * removed as well.
     */
    void removeRemoteConfig(const std::string& module_name);

    /**
     * Returns the current configuration value for the given module
     * name at the given identifier. See \c ConfigData::getValue() for
     * more details.
     * Raises a ModuleCCSessionError if the module name is unknown
     * Raises a DataNotFoundError if the identifier does not exist
     * in the specification.
     *
     * \param module_name The name of the module to get a config value for
     * \param identifier The identifier of the config value
     * \return The configuration setting at the given identifier
     */
    isc::data::ConstElementPtr getRemoteConfigValue(
        const std::string& module_name,
        const std::string& identifier) const;
    
private:
    ModuleSpec readModuleSpecification(const std::string& filename);
    void startCheck();

    bool started_;
    std::string module_name_;
    isc::cc::AbstractSession& session_;
    ModuleSpec module_specification_;
    isc::data::ConstElementPtr handleConfigUpdate(
        isc::data::ConstElementPtr new_config);

    isc::data::ConstElementPtr checkConfigUpdateCommand(
        const std::string& target_module,
        isc::data::ConstElementPtr arg);

    isc::data::ConstElementPtr checkModuleCommand(
        const std::string& cmd_str,
        const std::string& target_module,
        isc::data::ConstElementPtr arg) const;

    isc::data::ConstElementPtr(*config_handler_)(
        isc::data::ConstElementPtr new_config);
    isc::data::ConstElementPtr(*command_handler_)(
        const std::string& command,
        isc::data::ConstElementPtr args);

    typedef void (*RemoteHandler)(const std::string&,
                                  isc::data::ConstElementPtr);
    std::map<std::string, ConfigData> remote_module_configs_;
    std::map<std::string, RemoteHandler> remote_module_handlers_;

    void updateRemoteConfig(const std::string& module_name,
                            isc::data::ConstElementPtr new_config);

    ModuleSpec fetchRemoteSpec(const std::string& module, bool is_filename);
};

}
}
#endif // __CCSESSION_H

// Local Variables:
// mode: c++
// End:
