// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
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

#include <d2/bundy_d2_controller.h>
#include <d2/d2_process.h>
#include <d2/spec_config.h>

#include <sstream>

namespace isc {
namespace d2 {

/// @brief Defines the application name, this is passed into base class
/// it may be used to locate configuration data and appears in log statement.
const char* D2Controller::d2_app_name_ = "DHCP-DDNS";

/// @brief Defines the executable name. This is passed into the base class
const char* D2Controller::d2_bin_name_ = "b10-dhcp-ddns";

DControllerBasePtr&
D2Controller::instance() {
    // If the instance hasn't been created yet, create it.  Note this method
    // must use the base class singleton instance methods.  The base class
    // must have access to the singleton in order to use it within BUNDY
    // static function callbacks.
    if (!getController()) {
        DControllerBasePtr controller_ptr(new D2Controller());
        setController(controller_ptr);
    }

    return (getController());
}

DProcessBase* D2Controller::createProcess() {
    // Instantiate and return an instance of the D2 application process. Note
    // that the process is passed the controller's io_service.
    return (new D2Process(getAppName().c_str(), getIOService()));
}

D2Controller::D2Controller()
    : DControllerBase(d2_app_name_, d2_bin_name_) {
    // set the spec file either from the environment or
    // use the production value.
    if (getenv("B10_FROM_BUILD")) {
        setSpecFileName(std::string(getenv("B10_FROM_BUILD")) +
            "/src/bin/d2/dhcp-ddns.spec");
    } else {
        setSpecFileName(D2_SPECFILE_LOCATION);
    }
}

D2Controller::~D2Controller() {
}

void
D2Controller::launch(int argc, char* argv[], const bool test_mode) {
    // Step 1 is to parse the command line arguments.
    try {
        parseArgs(argc, argv);
    } catch (const InvalidUsage& ex) {
        usage(ex.what());
        throw; // rethrow it
    }

    // Do not initialize logger here if we are running unit tests. It would
    // replace an instance of unit test specific logger.
    if (!test_mode) {
        // Now that we know what the mode flags are, we can init logging.
        // If standalone is enabled, do not buffer initial log messages
        isc::log::initLogger(getBinName(),
                             (isVerbose() ? isc::log::DEBUG : isc::log::INFO),
                             isc::log::MAX_DEBUG_LEVEL, NULL, true);
    }

    LOG_DEBUG(dctl_logger, DBGLVL_START_SHUT, DCTL_STARTING)
              .arg(getAppName()).arg(getpid());
    try {
        // Step 2 is to create and initialize the application process object.
        initProcess();
    } catch (const std::exception& ex) {
        LOG_FATAL(dctl_logger, DCTL_INIT_PROCESS_FAIL)
                  .arg(getAppName()).arg(ex.what());
        isc_throw (ProcessInitError,
                   "Application Process initialization failed: " << ex.what());
    }

    // Next we connect to Bundy.
    try {
        establishSession();
    } catch (const std::exception& ex) {
        LOG_FATAL(dctl_logger, DCTL_SESSION_FAIL).arg(ex.what());
        isc_throw (SessionStartError,
                   "Session start up failed: " << ex.what());
    }

    // Everything is clear for launch, so start the application's
    // event loop.
    try {
        runProcess();
    } catch (const std::exception& ex) {
        LOG_FATAL(dctl_logger, DCTL_PROCESS_FAILED)
                  .arg(getAppName()).arg(ex.what());
        isc_throw (ProcessRunError,
                   "Application process event loop failed: " << ex.what());
    }

    // Disconnect from Bundy.
    try {
        disconnectSession();
    } catch (const std::exception& ex) {
        LOG_ERROR(dctl_logger, DCTL_DISCONNECT_FAIL)
                  .arg(getAppName()).arg(ex.what());
        isc_throw (SessionEndError, "Session end failed: " << ex.what());
    }

    // All done, so bail out.
    LOG_INFO(dctl_logger, DCTL_STOPPING).arg(getAppName());
}

void
D2Controller::parseArgs(int argc, char* argv[])
{
    // Iterate over the given command line options. If its a stock option
    // ("s" or "v") handle it here.  If its a valid custom option, then
    // invoke customOption.
    int ch;
    opterr = 0;
    optind = 1;
    std::string opts(":v" + getCustomOpts());
    while ((ch = getopt(argc, argv, opts.c_str())) != -1) {
        switch (ch) {
        case 'v':
            // Enables verbose logging.
            setVerbose(true);
            break;

        case '?': {
            // We hit an invalid option.
            isc_throw(InvalidUsage, "unsupported option: ["
                      << static_cast<char>(optopt) << "] "
                      << (!optarg ? "" : optarg));

            break;
            }

        default:
            // We hit a valid custom option
            if (!customOption(ch, optarg)) {
                // This would be a programmatic error.
                isc_throw(InvalidUsage, " Option listed but implemented?: ["
                          << static_cast<char>(ch) << "] "
                          << (!optarg ? "" : optarg));
            }
            break;
        }
    }

    // There was too much information on the command line.
    if (argc > optind) {
        isc_throw(InvalidUsage, "extraneous command line information");
    }
}

void
D2Controller::establishSession() {
    LOG_DEBUG(dctl_logger, DBGLVL_START_SHUT, DCTL_CCSESSION_STARTING)
              .arg(getAppName()).arg(getSpecFileName());

    // Create the BIND10 command control session with the our IOService.
    cc_session_ = SessionPtr(new isc::cc::Session(
                             getIOService()->get_io_service()));

    // Create the BIND10 config session with the stub configuration handler.
    // This handler is internally invoked by the constructor and on success
    // the constructor updates the current session with the configuration that
    // had been committed in the previous session. If we do not install
    // the dummy handler, the previous configuration would be lost.
    config_session_ = ModuleCCSessionPtr(new isc::config::ModuleCCSession(
                                         getSpecFileName(), *cc_session_,
                                         dummyConfigHandler, 
                                         commandHandler,
                                         false));
    // Enable configuration even processing.
    config_session_->start();

    // We initially create ModuleCCSession() with a dummy configHandler, as
    // the session module is too eager to send partial configuration.
    // Replace the dummy config handler with the real handler.
    config_session_->setConfigHandler(configHandler);

    // Call the real configHandler with the full configuration retrieved
    // from the config session.
    isc::data::ConstElementPtr answer = configHandler(
                                            config_session_->getFullConfig());

    // Parse the answer returned from the configHandler.  Log the error but
    // keep running. This provides an opportunity for the user to correct
    // the configuration dynamically.
    int ret = 0;
    isc::data::ConstElementPtr comment = isc::config::parseAnswer(ret, answer);
    if (ret) {
        LOG_ERROR(dctl_logger, DCTL_CONFIG_LOAD_FAIL)
                  .arg(getAppName()).arg(comment->str());
    }
}

void D2Controller::disconnectSession() {
    LOG_DEBUG(dctl_logger, DBGLVL_START_SHUT, DCTL_CCSESSION_ENDING)
              .arg(getAppName());

    // Destroy the BIND10 config session.
    if (config_session_) {
        config_session_.reset();
    }

    // Destroy the BIND10 command and control session.
    if (cc_session_) {
        cc_session_->disconnect();
        cc_session_.reset();
    }
}

isc::data::ConstElementPtr
D2Controller::dummyConfigHandler(isc::data::ConstElementPtr) {
    LOG_DEBUG(dctl_logger, DBGLVL_START_SHUT, DCTL_CONFIG_STUB)
             .arg(getController()->getAppName());
    return (isc::config::createAnswer(0, "Configuration accepted."));
}

isc::data::ConstElementPtr
D2Controller::configHandler(isc::data::ConstElementPtr new_config) {

    LOG_DEBUG(dctl_logger, DBGLVL_COMMAND, DCTL_CONFIG_UPDATE)
              .arg(getController()->getAppName()).arg(new_config->str());

    // Invoke the instance method on the controller singleton.
    return (getController()->updateConfig(new_config));
}

// Static callback which invokes non-static handler on singleton
isc::data::ConstElementPtr
D2Controller::commandHandler(const std::string& command,
                                isc::data::ConstElementPtr args) {

    LOG_DEBUG(dctl_logger, DBGLVL_COMMAND, DCTL_COMMAND_RECEIVED)
        .arg(getController()->getAppName()).arg(command)
        .arg(args ? args->str() : "(no args)");

    // Invoke the instance method on the controller singleton.
    return (getController()->executeCommand(command, args));
}

isc::data::ConstElementPtr
D2Controller::updateConfig(isc::data::ConstElementPtr new_config) {
    if (!config_session_) {
        // That should never happen as we install config_handler
        // after we instantiate the server.
        isc::data::ConstElementPtr answer =
            isc::config::createAnswer(1, "Configuration rejected,"
                                              " Session has not started.");
        return (answer);
    }

    // Let's get the existing configuration.
    isc::data::ConstElementPtr full_config = config_session_->getFullConfig();

    // The configuration passed to this handler function is partial.
    // In other words, it just includes the values being modified.
    // In the same time, there may be dependencies between various
    // configuration parsers. For example: the option value can
    // be set if the definition of this option is set. If someone removes
    // an existing option definition then the partial configuration that
    // removes that definition is triggered while a relevant option value
    // may remain configured. This eventually results in the
    // configuration being in the inconsistent state.
    // In order to work around this problem we need to merge the new
    // configuration with the existing (full) configuration.

    // Let's create a new object that will hold the merged configuration.
    boost::shared_ptr<isc::data::MapElement>
                            merged_config(new isc::data::MapElement());

    // Merge an existing and new configuration.
    merged_config->setValue(full_config->mapValue());
    isc::data::merge(merged_config, new_config);

    // Send the merged configuration to the application.
    return (getProcess()->configure(merged_config));
}


void
D2Controller::usage(const std::string & text)
{
    if (text != "") {
        std::cerr << "Usage error: " << text << std::endl;
    }

    std::cerr << "Usage: " << getBinName() <<  std::endl;
    std::cerr << "  -v: verbose output" << std::endl;
    std::cerr << getUsageText() << std::endl;
}


}; // namespace isc::d2
}; // namespace isc
