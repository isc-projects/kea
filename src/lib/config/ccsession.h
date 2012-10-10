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

#include <config/config_data.h>
#include <config/module_spec.h>

#include <cc/session.h>
#include <cc/data.h>

#include <string>
#include <list>
#include <boost/function.hpp>

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
     * @param start_immediately If true (default), start listening to new commands
     * and configuration changes asynchronously at the end of the constructor;
     * if false, it will be delayed until the start() method is explicitly
     * called. (This is a short term workaround for an initialization trouble.
     * We'll need to develop a cleaner solution, and then remove this knob)
     * @param handle_logging If true, the ModuleCCSession will automatically
     * take care of logging configuration through the virtual Logging config
     * module. Defaults to true.
     */
    ModuleCCSession(const std::string& spec_file_name,
                    isc::cc::AbstractSession& session,
                    isc::data::ConstElementPtr(*config_handler)(
                        isc::data::ConstElementPtr new_config) = NULL,
                    isc::data::ConstElementPtr(*command_handler)(
                        const std::string& command,
                        isc::data::ConstElementPtr args) = NULL,
                    bool start_immediately = true,
                    bool handle_logging = true
                    );

    ///
    /// Destructor
    ///
    /// The destructor automatically calls sendStopping(), which sends
    /// a message to the ConfigManager that this module is stopping
    ///
    virtual ~ModuleCCSession();

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
     * \param handler The handler functor called whenever there's a change.
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
    typedef boost::function<void(const std::string&,
                                 isc::data::ConstElementPtr,
                                 const ConfigData&)> RemoteHandler;
    std::string addRemoteConfig(const std::string& spec_name,
                                RemoteHandler handler = RemoteHandler(),
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

    /**
     * Send a message to the underlying CC session.
     * This has the same interface as isc::cc::Session::group_sendmsg()
     *
     * \param msg see isc::cc::Session::group_sendmsg()
     * \param group see isc::cc::Session::group_sendmsg()
     * \param instance see isc::cc::Session::group_sendmsg()
     * \param to see isc::cc::Session::group_sendmsg()
     * \return see isc::cc::Session::group_sendmsg()
     */
    int groupSendMsg(isc::data::ConstElementPtr msg,
                     std::string group,
                     std::string instance = "*",
                     std::string to = "*") {
        return (session_.group_sendmsg(msg, group, instance, to));
    };

    /**
     * Receive a message from the underlying CC session.
     * This has the same interface as isc::cc::Session::group_recvmsg()
     *
     * \param envelope see isc::cc::Session::group_recvmsg()
     * \param msg see isc::cc::Session::group_recvmsg()
     * \param nonblock see isc::cc::Session::group_recvmsg()
     * \param seq see isc::cc::Session::group_recvmsg()
     * \return see isc::cc::Session::group_recvmsg()
     */
    bool groupRecvMsg(isc::data::ConstElementPtr& envelope,
                      isc::data::ConstElementPtr& msg,
                      bool nonblock = true,
                      int seq = -1) {
        return (session_.group_recvmsg(envelope, msg, nonblock, seq));
    };

    /// \brief Forward declaration of internal data structure.
    ///
    /// This holds information about one asynchronous request to receive
    /// a message. It is declared as public to allow declaring other derived
    /// types, but without showing the internal representation.
    class AsyncRecvRequest;

    /// \brief List of all requests for asynchronous reads.
    typedef std::list<AsyncRecvRequest> AsyncRecvRequests;

    /// \brief Identifier of single request for asynchronous read.
    typedef AsyncRecvRequests::iterator AsyncRecvRequestID;

    /// \brief Callback which is called when an asynchronous receive finishes.
    ///
    /// This is the callback used by groupRecvMsgAsync() function. It is called
    /// when a matching message arrives. It receives following parameters when
    /// called:
    /// - The envelope of the message
    /// - The message itself
    /// - The ID of the request, as returned by corresponding groupRecvMsgAsync
    ///   call.
    ///
    /// It is possible to throw exceptions from the callback, but they will not
    /// be caught and they will get propagated out through the checkCommand()
    /// call. This, if not handled on higher level, will likely terminate the
    /// application. However, the ModuleCCSession internals will be in
    /// well-defined state after the call (both the callback and the message
    /// will be removed from the queues as already called).
    typedef boost::function3<void, const isc::data::ConstElementPtr&,
                             const isc::data::ConstElementPtr&,
                             const AsyncRecvRequestID&>
        AsyncRecvCallback;

    /// \brief Receive a message from the CC session asynchronously.
    ///
    /// This registers a callback which is called when a matching message
    /// is received. This message returns immediately.
    ///
    /// Once a matching message arrives, the callback is called with the
    /// envelope of the message, the message itself and the result of this
    /// function call (which might be useful for identifying which of many
    /// events the recipient is waiting for this is). This makes the callback
    /// used and is not called again even if a message that would match
    /// arrives later (this is a single-shot callback).
    ///
    /// The callback is never called from within this function. Even if there
    /// are queued messages, the callback would be called once checkCommand()
    /// is invoked (possibly from start() or the constructor).
    ///
    /// The matching is as follows. If is_reply is true, only replies are
    /// considered. In that case, if seq is -1, any reply is accepted. If
    /// it is something else than -1, only the reply with matching seq is
    /// taken. This may be used to receive replies to commands
    /// asynchronously.
    ///
    /// In case the is_reply is false, the function looks for command messages.
    /// The seq parameter is ignored, but the recipient one is considered. If
    /// it is an empty string, any command is taken. If it is non-empty, only
    /// commands addressed to the recipient channel (eg. group - instance is
    /// ignored for now) are taken. This can be used to receive foreign commands
    /// or notifications. In such case, it might be desirable to call the
    /// groupRecvMsgAsync again from within the callback, to receive any future
    /// commands or events of the same type.
    ///
    /// The interaction with other receiving functions is slightly complicated.
    /// The groupRecvMsg call takes precedence. If the message matches its
    /// parameters, it steals the message and no callback matching it as well
    /// is called. Then, all the queued asynchronous receives are considered,
    /// with the oldest active ones taking precedence (they work as FIFO).
    /// If none of them matches, generic command and config handling takes
    /// place. If it is not handled by that, the message is dropped. However,
    /// it is better if there's just one place that wants to receive each given
    /// message.
    ///
    /// \exception std::bad_alloc if there isn't enough memory to store the
    ///     callback.
    /// \param callback is the function to be called when a matching message
    ///     arrives.
    /// \param is_reply specifies if the desired message should be a reply or
    ///     a command.
    /// \param seq specifies the reply sequence number in case a reply is
    ///     desired. The default -1 means any reply is OK.
    /// \param recipient is the CC channel to which the command should be
    ///     addressed to match (in case is_reply is false). Empty means any
    ///     command is good one.
    /// \return An identifier of the request. This will be passed to the
    ///     callback or can be used to cancel the request by cancelAsyncRecv.
    /// \todo Decide what to do with instance and what was it meant for anyway.
    AsyncRecvRequestID groupRecvMsgAsync(const AsyncRecvCallback& callback,
                                         bool is_reply, int seq = -1,
                                         const std::string& recipient =
                                         std::string());

    /// \brief Removes yet unused request for asynchronous receive.
    ///
    /// This function cancels a request previously queued by
    /// groupRecvMsgAsync(). You may use it only before the callback was
    /// already triggered. If you call it with an ID of callback that
    /// already happened or was already canceled, the behaviour is undefined
    /// (but something like a crash is very likely, as the function removes
    /// an item from a list and this would be removing it from a list that
    /// does not contain the item).
    ///
    /// It is important to cancel requests that are no longer going to happen
    /// for some reason, as the request would occupy memory forever.
    ///
    /// \param id The id of request as returned by groupRecvMsgAsync.
    void cancelAsyncRecv(const AsyncRecvRequestID& id);

private:
    ModuleSpec readModuleSpecification(const std::string& filename);
    void startCheck();
    void sendStopping();
    /// \brief Check if the message is wanted by asynchronous read
    ///
    /// It checks if any of the previously queued requests match
    /// the message. If so, the callback is dispatched and removed.
    ///
    /// \param envelope The envelope of the message.
    /// \param msg The actual message data.
    /// \return True if the message was used for a callback, false
    ///     otherwise.
    bool checkAsyncRecv(const data::ConstElementPtr& envelope,
                        const data::ConstElementPtr& msg);
    /// \brief Checks if a message with this envelope matches the request
    bool requestMatch(const AsyncRecvRequest& request,
                      const data::ConstElementPtr& envelope) const;

    bool started_;
    std::string module_name_;
    isc::cc::AbstractSession& session_;
    ModuleSpec module_specification_;
    AsyncRecvRequests async_recv_requests_;
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

    std::map<std::string, ConfigData> remote_module_configs_;
    std::map<std::string, RemoteHandler> remote_module_handlers_;

    void updateRemoteConfig(const std::string& module_name,
                            isc::data::ConstElementPtr new_config);

    ModuleSpec fetchRemoteSpec(const std::string& module, bool is_filename);
};

/// \brief Default handler for logging config updates
///
/// When CCSession is initialized with handle_logging set to true,
/// this callback will be used to update the logger when a configuration
/// change comes in.
///
/// This function updates the (global) loggers by initializing a
/// LoggerManager and passing the settings as specified in the given
/// configuration update.
///
/// \param module_name The name of the module
/// \param new_config The modified configuration values
/// \param config_data The full config data for the (remote) logging
///                    module.
void
default_logconfig_handler(const std::string& module_name,
                          isc::data::ConstElementPtr new_config,
                          const ConfigData& config_data);


/// \brief Returns the loggers related to this module
///
/// This function does two things;
/// - it drops the configuration parts for loggers for other modules.
/// - it replaces the '*' in the name of the loggers by the name of
///   this module, but *only* if the expanded name is not configured
///   explicitly.
///
/// Examples: if this is the module b10-resolver,
/// For the config names ['*', 'b10-auth']
/// The '*' is replaced with 'b10-resolver', and this logger is used.
/// 'b10-auth' is ignored (of course, it will not be in the b10-auth
/// module).
///
/// For ['*', 'b10-resolver']
/// The '*' is ignored, and only 'b10-resolver' is used.
///
/// For ['*.reslib', 'b10-resolver']
/// Or ['b10-resolver.reslib', '*']
/// Both are used, where the * will be expanded to b10-resolver
///
/// \note This is a public function at this time, but mostly for
/// the purposes of testing. Once we can directly test what loggers
/// are running, this function may be moved to the unnamed namespace
///
/// \param loggers the original 'loggers' config list
/// \return ListElement containing only loggers relevant for this
///         module, where * is replaced by the root logger name
isc::data::ConstElementPtr
getRelatedLoggers(isc::data::ConstElementPtr loggers);

} // namespace config

} // namespace isc
#endif // __CCSESSION_H

// Local Variables:
// mode: c++
// End:
