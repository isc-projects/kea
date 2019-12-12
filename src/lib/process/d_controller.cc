// Copyright (C) 2013-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <cc/command_interpreter.h>
#include <cfgrpt/config_report.h>
#include <exceptions/exceptions.h>
#include <log/logger.h>
#include <log/logger_support.h>
#include <process/daemon.h>
#include <process/d_log.h>
#include <process/d_controller.h>
#include <process/config_base.h>
#include <kea_version.h>
#include <boost/bind.hpp>
#include <sstream>
#include <unistd.h>

using namespace isc::data;
using namespace isc::config;

namespace isc {
namespace process {

DControllerBasePtr DControllerBase::controller_;

// Note that the constructor instantiates the controller's primary IOService.
DControllerBase::DControllerBase(const char* app_name, const char* bin_name)
    : app_name_(app_name), bin_name_(bin_name),
      verbose_(false), check_only_(false),
      io_service_(new isc::asiolink::IOService()),
      io_signal_queue_() {
}

void
DControllerBase::setController(const DControllerBasePtr& controller) {
    if (controller_) {
        // This shouldn't happen, but let's make sure it can't be done.
        // It represents a programmatic error.
        isc_throw (DControllerBaseError,
                "Multiple controller instances attempted.");
    }

    controller_ = controller;
}

ConstElementPtr
DControllerBase::parseFile(const std::string&) {
    ConstElementPtr elements;
    return (elements);
}

void
DControllerBase::launch(int argc, char* argv[], const bool test_mode) {

    // Step 1 is to parse the command line arguments.
    try {
        parseArgs(argc, argv);
    } catch (const InvalidUsage& ex) {
        usage(ex.what());
        // rethrow it with an empty message
        isc_throw(InvalidUsage, "");
    }

    setProcName(bin_name_);

    if (isCheckOnly()) {
        checkConfigOnly();
        return;
    }

    // It is important that we set a default logger name because this name
    // will be used when the user doesn't provide the logging configuration
    // in the Kea configuration file.
    Daemon::setDefaultLoggerName(bin_name_);

    // Logger's default configuration depends on whether we are in the
    // verbose mode or not. CfgMgr manages the logger configuration so
    // the verbose mode is set for CfgMgr.
    Daemon::setVerbose(verbose_);

    // Do not initialize logger here if we are running unit tests. It would
    // replace an instance of unit test specific logger.
    if (!test_mode) {
        // Now that we know what the mode flags are, we can init logging.
        Daemon::loggerInit(bin_name_.c_str(), verbose_);
    }

    try {
        checkConfigFile();
    } catch (const std::exception& ex) {
        LOG_FATAL(dctl_logger, DCTL_CONFIG_FILE_LOAD_FAIL)
            .arg(app_name_).arg(ex.what());
        isc_throw (LaunchError, "Launch Failed: " << ex.what());
    }

    try {
        createPIDFile();
    } catch (const DaemonPIDExists& ex) {
        LOG_FATAL(dctl_logger, DCTL_ALREADY_RUNNING)
                  .arg(bin_name_).arg(ex.what());
        isc_throw (LaunchError, "Launch Failed: " << ex.what());
    } catch (const std::exception& ex) {
        LOG_FATAL(dctl_logger, DCTL_PID_FILE_ERROR)
                  .arg(app_name_).arg(ex.what());
        isc_throw (LaunchError, "Launch failed: " << ex.what());
    }

    // Log the starting of the service.
    LOG_INFO(dctl_logger, DCTL_STARTING)
        .arg(app_name_).arg(getpid()).arg(VERSION);
    try {
        // Step 2 is to create and initialize the application process object.
        initProcess();
    } catch (const std::exception& ex) {
        LOG_FATAL(dctl_logger, DCTL_INIT_PROCESS_FAIL)
                  .arg(app_name_).arg(ex.what());
        isc_throw (ProcessInitError,
                   "Application Process initialization failed: " << ex.what());
    }

    LOG_DEBUG(dctl_logger, isc::log::DBGLVL_START_SHUT, DCTL_STANDALONE)
        .arg(app_name_);

    // Step 3 is to load configuration from file.
    int rcode;
    ConstElementPtr comment = parseAnswer(rcode, configFromFile());
    if (rcode != 0) {
        LOG_FATAL(dctl_logger, DCTL_CONFIG_FILE_LOAD_FAIL)
                  .arg(app_name_).arg(comment->stringValue());
        isc_throw (ProcessInitError, "Could Not load configuration file: "
                   << comment->stringValue());
    }

    // Note that the controller was started.
    start_ = boost::posix_time::second_clock::universal_time();

    // Everything is clear for launch, so start the application's
    // event loop.
    try {
        // Now that we have a proces, we can set up signal handling.
        initSignalHandling();
        runProcess();
    } catch (const std::exception& ex) {
        LOG_FATAL(dctl_logger, DCTL_PROCESS_FAILED)
                  .arg(app_name_).arg(ex.what());
        isc_throw (ProcessRunError,
                   "Application process event loop failed: " << ex.what());
    }

    // All done, so bail out.
    LOG_INFO(dctl_logger, DCTL_SHUTDOWN)
        .arg(app_name_).arg(getpid()).arg(VERSION);
}

void
DControllerBase::checkConfigOnly() {
    try {
        // We need to initialize logging, in case any error
        // messages are to be printed.
        // This is just a test, so we don't care about lockfile.
        setenv("KEA_LOCKFILE_DIR", "none", 0);
        Daemon::setDefaultLoggerName(bin_name_);
        Daemon::setVerbose(verbose_);
        Daemon::loggerInit(bin_name_.c_str(), verbose_);

        // Check the syntax first.
        std::string config_file = getConfigFile();
        if (config_file.empty()) {
            // Basic sanity check: file name must not be empty.
            isc_throw(InvalidUsage, "JSON configuration file not specified");
        }
        ConstElementPtr whole_config = parseFile(config_file);
        if (!whole_config) {
            // No fallback to fromJSONFile
            isc_throw(InvalidUsage, "No configuration found");
        }
        if (verbose_) {
            std::cerr << "Syntax check OK" << std::endl;
        }

        // Check the logic next.
        ConstElementPtr module_config;
        module_config = whole_config->get(getAppName());
        if (!module_config) {
            isc_throw(InvalidUsage, "Config file " << config_file <<
                      " does not include '" << getAppName() << "' entry");
        }
        if (module_config->getType() != Element::map) {
            isc_throw(InvalidUsage, "Config file " << config_file <<
                      " include not map '" << getAppName() << "' entry");
        }

        // Handle other (i.e. not application name) objects (e.g. Logging).
        handleOtherObjects(whole_config);

        // Get an application process object.
        initProcess();

        ConstElementPtr answer = checkConfig(module_config);
        int rcode = 0;
        answer = parseAnswer(rcode, answer);
        if (rcode != 0) {
            isc_throw(InvalidUsage, "Error encountered: "
                      << answer->stringValue());
        }
    } catch (const VersionMessage&) {
        throw;
    } catch (const InvalidUsage&) {
        throw;
    } catch (const std::exception& ex) {
        isc_throw(InvalidUsage, "Syntax check failed with: " << ex.what());
    }
    return;
}

void
DControllerBase::parseArgs(int argc, char* argv[])
{

    if (argc == 1) {
        isc_throw(InvalidUsage, "");
    }

    // Iterate over the given command line options. If its a stock option
    // ("c" or "d") handle it here.  If its a valid custom option, then
    // invoke customOption.
    int ch;
    opterr = 0;
    optind = 1;
    std::string opts("dvVWc:t:" + getCustomOpts());
    while ((ch = getopt(argc, argv, opts.c_str())) != -1) {
        switch (ch) {
        case 'd':
            // Enables verbose logging.
            verbose_ = true;
            break;

        case 'v':
            // gather Kea version and throw so main() can catch and return
            // rather than calling exit() here which disrupts gtest.
            isc_throw(VersionMessage, getVersion(false));
            break;

        case 'V':
            // gather Kea version and throw so main() can catch and return
            // rather than calling exit() here which disrupts gtest.
            isc_throw(VersionMessage, getVersion(true));
            break;

        case 'W':
            // gather Kea config report and throw so main() can catch and
            // return rather than calling exit() here which disrupts gtest.
            isc_throw(VersionMessage, isc::detail::getConfigReport());
            break;

        case 'c':
        case 't':
            // config file name
            if (optarg == NULL) {
                isc_throw(InvalidUsage, "configuration file name missing");
            }

            setConfigFile(optarg);

            if (ch == 't') {
                check_only_ = true;
            }
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

bool
DControllerBase::customOption(int /* option */, char* /*optarg*/)
{
    // Default implementation returns false.
    return (false);
}

void
DControllerBase::initProcess() {
    LOG_DEBUG(dctl_logger, isc::log::DBGLVL_START_SHUT, DCTL_INIT_PROCESS)
        .arg(app_name_);

    // Invoke virtual method to instantiate the application process.
    try {
        process_.reset(createProcess());
    } catch (const std::exception& ex) {
        isc_throw(DControllerBaseError, std::string("createProcess failed: ")
                  + ex.what());
    }

    // This is pretty unlikely, but will test for it just to be safe..
    if (!process_) {
        isc_throw(DControllerBaseError, "createProcess returned NULL");
    }

    // Invoke application's init method (Note this call should throw
    // DProcessBaseError if it fails).
    process_->init();
}

ConstElementPtr
DControllerBase::configFromFile() {
    // Rollback any previous staging configuration. For D2, only a
    // logger configuration is used here.
    // We're not using cfgmgr to store logging configuration anymore.
    // isc::dhcp::CfgMgr::instance().rollback();

    // Will hold configuration.
    ConstElementPtr module_config;
    // Will receive configuration result.
    ConstElementPtr answer;
    try {
        std::string config_file = getConfigFile();
        if (config_file.empty()) {
            // Basic sanity check: file name must not be empty.
            isc_throw(BadValue, "JSON configuration file not specified. Please "
                                "use -c command line option.");
        }

        // If parseFile returns an empty pointer, then pass the file onto the
        // original JSON parser.
        ConstElementPtr whole_config = parseFile(config_file);
        if (!whole_config) {
            // Read contents of the file and parse it as JSON
            whole_config = Element::fromJSONFile(config_file, true);
        }

        // Extract derivation-specific portion of the configuration.
        module_config = whole_config->get(getAppName());
        if (!module_config) {
            isc_throw(BadValue, "Config file " << config_file <<
                                " does not include '" <<
                                 getAppName() << "' entry.");
        }
        if (module_config->getType() != Element::map) {
            isc_throw(InvalidUsage, "Config file " << config_file <<
                      " include not map '" << getAppName() << "' entry");
        }

        // Handle other (i.e. not application name) objects (e.g. Logging).
        handleOtherObjects(whole_config);

        // Let's configure logging before applying the configuration,
        // so we can log things during configuration process.

        // Temporary storage for logging configuration
        ConfigPtr storage(new ConfigBase());

        // Configure logging to the tempoary storage.
        Daemon::configureLogger(module_config, storage);

        // Let's apply the new logging. We do it early, so we'll be able
        // to print out what exactly is wrong with the new config in
        // case of problems.
        storage->applyLoggingCfg();

        answer = updateConfig(module_config);
        // In all cases the right logging configuration is in the context.
        process_->getCfgMgr()->getContext()->applyLoggingCfg();
    } catch (const std::exception& ex) {
        // Rollback logging configuration.
        process_->getCfgMgr()->getContext()->applyLoggingCfg();

        // build an error result
        ConstElementPtr error = createAnswer(COMMAND_ERROR,
                 std::string("Configuration parsing failed: ") + ex.what());
        return (error);
    }

    return (answer);
}

void
DControllerBase::runProcess() {
    LOG_DEBUG(dctl_logger, isc::log::DBGLVL_START_SHUT, DCTL_RUN_PROCESS)
        .arg(app_name_);
    if (!process_) {
        // This should not be possible.
        isc_throw(DControllerBaseError, "Process not initialized");
    }

    // Invoke the application process's run method. This may throw
    // DProcessBaseError
    process_->run();
}

// Instance method for handling new config
ConstElementPtr
DControllerBase::updateConfig(ConstElementPtr new_config) {
    return (process_->configure(new_config, false));
}

// Instance method for checking new config
ConstElementPtr
DControllerBase::checkConfig(ConstElementPtr new_config) {
    return (process_->configure(new_config, true));
}

ConstElementPtr
DControllerBase::configGetHandler(const std::string&,
                                  ConstElementPtr /*args*/) {
    ConstElementPtr config = process_->getCfgMgr()->getContext()->toElement();

    return (createAnswer(COMMAND_SUCCESS, config));
}

ConstElementPtr
DControllerBase::configWriteHandler(const std::string&,
                                    ConstElementPtr args) {
    std::string filename;

    if (args) {
        if (args->getType() != Element::map) {
            return (createAnswer(COMMAND_ERROR, "Argument must be a map"));
        }
        ConstElementPtr filename_param = args->get("filename");
        if (filename_param) {
            if (filename_param->getType() != Element::string) {
                return (createAnswer(COMMAND_ERROR,
                                     "passed parameter 'filename' "
                                     "is not a string"));
            }
            filename = filename_param->stringValue();
        }
    }

    if (filename.empty()) {
        // filename parameter was not specified, so let's use
        // whatever we remember
        filename = getConfigFile();
        if (filename.empty()) {
            return (createAnswer(COMMAND_ERROR,
                                 "Unable to determine filename."
                                 "Please specify filename explicitly."));
        }
    }


    // Ok, it's time to write the file.
    size_t size = 0;
    ElementPtr cfg = process_->getCfgMgr()->getContext()->toElement();

    try {
        size = writeConfigFile(filename, cfg);
    } catch (const isc::Exception& ex) {
        return (createAnswer(COMMAND_ERROR,
                             std::string("Error during write-config:")
                             + ex.what()));
    }
    if (size == 0) {
        return (createAnswer(COMMAND_ERROR,
                             "Error writing configuration to " + filename));
    }

    // Ok, it's time to return the successful response.
    ElementPtr params = Element::createMap();
    params->set("size", Element::create(static_cast<long long>(size)));
    params->set("filename", Element::create(filename));

    return (createAnswer(CONTROL_RESULT_SUCCESS, "Configuration written to "
                         + filename + " successful", params));
}

void
DControllerBase::handleOtherObjects(ConstElementPtr args) {
    // Check obsolete or unknown (aka unsupported) objects.
    const std::string& app_name = getAppName();
    for (auto obj : args->mapValue()) {
        const std::string& obj_name = obj.first;
        if (obj_name == app_name) {
            continue;
        }
        if (obj_name == "Logging") {
            LOG_WARN(dctl_logger, DCTL_CONFIG_DEPRECATED)
                .arg("The top level element, 'Logging', has been deprecated."
                     "  Loggers should be defined with the 'loggers[]'"
                     " element within the '" +  app_name + "' scope.");
            continue;
        }
        LOG_WARN(dctl_logger, DCTL_CONFIG_DEPRECATED)
            .arg("'" + obj_name + "', defining anything in global level besides '"
                 + app_name + "' is no longer supported.");
    }

    // Relocate Logging: if there is a global Logging object takes its
    // loggers entry, move the entry to AppName object and remove
    // now empty Logging.
    Daemon::relocateLogging(args, app_name);
}

ConstElementPtr
DControllerBase::configTestHandler(const std::string&, ConstElementPtr args) {
    const int status_code = COMMAND_ERROR; // 1 indicates an error
    ConstElementPtr module_config;
    std::string app_name = getAppName();
    std::string message;

    // Command arguments are expected to be:
    // { "Module": { ... } }
    if (!args) {
        message = "Missing mandatory 'arguments' parameter.";
    } else {
        module_config = args->get(app_name);
        if (!module_config) {
            message = "Missing mandatory '" + app_name + "' parameter.";
        } else if (module_config->getType() != Element::map) {
            message = "'" + app_name + "' parameter expected to be a map.";
        }
    }

    if (!message.empty()) {
        // Something is amiss with arguments, return a failure response.
        ConstElementPtr result = isc::config::createAnswer(status_code,
                                                           message);
        return (result);
    }

    // Handle other (i.e. not application name) objects (e.g. Logging).
    handleOtherObjects(args);

    // We are starting the configuration process so we should remove any
    // staging configuration that has been created during previous
    // configuration attempts.
    // We're not using cfgmgr to store logging information anymore.
    // isc::dhcp::CfgMgr::instance().rollback();

    // Now we check the server proper.
    return (checkConfig(module_config));
}

ConstElementPtr
DControllerBase::configReloadHandler(const std::string&, ConstElementPtr) {
    // Add reload in message?
    return (configFromFile());
}

ConstElementPtr
DControllerBase::configSetHandler(const std::string&, ConstElementPtr args) {
    const int status_code = COMMAND_ERROR; // 1 indicates an error
    ConstElementPtr module_config;
    std::string app_name = getAppName();
    std::string message;

    // Command arguments are expected to be:
    // { "Module": { ... } }
    if (!args) {
        message = "Missing mandatory 'arguments' parameter.";
    } else {
        module_config = args->get(app_name);
        if (!module_config) {
            message = "Missing mandatory '" + app_name + "' parameter.";
        } else if (module_config->getType() != Element::map) {
            message = "'" + app_name + "' parameter expected to be a map.";
        }
    }

    if (!message.empty()) {
        // Something is amiss with arguments, return a failure response.
        ConstElementPtr result = isc::config::createAnswer(status_code,
                                                           message);
        return (result);
    }

    try {

        // Handle other (i.e. not application name) objects (e.g. Logging).
        handleOtherObjects(args);

        // We are starting the configuration process so we should remove any
        // staging configuration that has been created during previous
        // configuration attempts.
        // We're not using cfgmgr to store logging information anymore.
        // isc::dhcp::CfgMgr::instance().rollback();

        // Temporary storage for logging configuration
        ConfigPtr storage(new ConfigBase());

        // Configure logging to the tempoary storage.
        Daemon::configureLogger(module_config, storage);

        // Let's apply the new logging. We do it early, so we'll be able
        // to print out what exactly is wrong with the new config in
        // case of problems.
        storage->applyLoggingCfg();

        ConstElementPtr answer = updateConfig(module_config);
        int rcode = 0;
        parseAnswer(rcode, answer);
        // In all cases the right logging configuration is in the context.
        process_->getCfgMgr()->getContext()->applyLoggingCfg();
        return (answer);
    } catch (const std::exception& ex) {
        // Rollback logging configuration.
        process_->getCfgMgr()->getContext()->applyLoggingCfg();

        // build an error result
        ConstElementPtr error = createAnswer(COMMAND_ERROR,
                 std::string("Configuration parsing failed: ") + ex.what());
        return (error);
    }
}

ConstElementPtr
DControllerBase::serverTagGetHandler(const std::string&, ConstElementPtr) {
    const std::string& tag = process_->getCfgMgr()->getContext()->getServerTag();
    ElementPtr response = Element::createMap();
    response->set("server-tag", Element::create(tag));

    return (createAnswer(COMMAND_SUCCESS, response));
}

ConstElementPtr
DControllerBase::statusGetHandler(const std::string&, ConstElementPtr) {
    ElementPtr status = Element::createMap();
    status->set("pid", Element::create(static_cast<int>(getpid())));

    auto now = boost::posix_time::second_clock::universal_time();
    if (!start_.is_not_a_date_time()) {
        auto uptime = now - start_;
        status->set("uptime", Element::create(uptime.total_seconds()));
    }

    auto last_commit = process_->getCfgMgr()->getContext()->getLastCommitTime();
    if (!last_commit.is_not_a_date_time()) {
        auto reload = now - last_commit;
        status->set("reload", Element::create(reload.total_seconds()));
    }

    return (createAnswer(COMMAND_SUCCESS, status));
}

ConstElementPtr
DControllerBase::versionGetHandler(const std::string&, ConstElementPtr) {
    ConstElementPtr answer;

    // For version-get put the extended version in arguments
    ElementPtr extended = Element::create(getVersion(true));
    ElementPtr arguments = Element::createMap();
    arguments->set("extended", extended);
    answer = createAnswer(COMMAND_SUCCESS, getVersion(false), arguments);
    return (answer);
}

ConstElementPtr
DControllerBase::buildReportHandler(const std::string&, ConstElementPtr) {
    return (createAnswer(COMMAND_SUCCESS, isc::detail::getConfigReport()));
}

ConstElementPtr
DControllerBase::shutdownHandler(const std::string&, ConstElementPtr args) {
    // Shutdown is universal.  If its not that, then try it as
    // a custom command supported by the derivation.  If that
    // doesn't pan out either, than send to it the application
    // as it may be supported there.
    return (shutdownProcess(args));
}

ConstElementPtr
DControllerBase::shutdownProcess(ConstElementPtr args) {
    if (process_) {
        return (process_->shutdown(args));
    }

    // Not really a failure, but this condition is worth noting. In reality
    // it should be pretty hard to cause this.
    LOG_WARN(dctl_logger, DCTL_NOT_RUNNING).arg(app_name_);
    return (createAnswer(COMMAND_SUCCESS, "Process has not been initialized"));
}

void
DControllerBase::initSignalHandling() {
    /// @todo block everything we don't handle

    // Create our signal queue.
    io_signal_queue_.reset(new IOSignalQueue(io_service_));

    // Install the on-receipt handler
    util::SignalSet::setOnReceiptHandler(boost::bind(&DControllerBase::
                                                     osSignalHandler,
                                                     this, _1));
    // Register for the signals we wish to handle.
    signal_set_.reset(new util::SignalSet(SIGHUP,SIGINT,SIGTERM));
}

bool
DControllerBase::osSignalHandler(int signum) {
    // Create a IOSignal to propagate the signal to IOService.
    io_signal_queue_->pushSignal(signum, boost::bind(&DControllerBase::
                                                     ioSignalHandler,
                                                     this, _1));
    return (true);
}

void
DControllerBase::ioSignalHandler(IOSignalId sequence_id) {
    // Pop the signal instance off the queue.  This should make us
    // the only one holding it, so when we leave it should be freed.
    // (note that popSignal will throw if signal is not found, which
    // in turn will caught, logged, and swallowed by IOSignal callback
    // invocation code.)
    IOSignalPtr io_signal = io_signal_queue_->popSignal(sequence_id);

    // Now call virtual signal processing method.
    processSignal(io_signal->getSignum());
}

void
DControllerBase::processSignal(int signum) {
    switch (signum) {
        case SIGHUP:
        {
            LOG_INFO(dctl_logger, DCTL_CFG_FILE_RELOAD_SIGNAL_RECVD)
                     .arg(signum).arg(getConfigFile());
            int rcode;
            ConstElementPtr comment = parseAnswer(rcode, configFromFile());
            if (rcode != 0) {
                LOG_ERROR(dctl_logger, DCTL_CFG_FILE_RELOAD_ERROR)
                          .arg(comment->stringValue());
            }

            break;
        }

        case SIGINT:
        case SIGTERM:
        {
            LOG_DEBUG(dctl_logger, isc::log::DBGLVL_START_SHUT,
                      DCTL_SHUTDOWN_SIGNAL_RECVD).arg(signum);
            ElementPtr arg_set;
            shutdownHandler(SHUT_DOWN_COMMAND, arg_set);
            break;
        }

        default:
            LOG_WARN(dctl_logger, DCTL_UNSUPPORTED_SIGNAL).arg(signum);
            break;
    }
}

void
DControllerBase::usage(const std::string & text)
{
    if (text != "") {
        std::cerr << "Usage error: " << text << std::endl;
    }

    std::cerr << "Usage: " << bin_name_ <<  std::endl
              << "  -v: print version number and exit" << std::endl
              << "  -V: print extended version information and exit"
              << std::endl
              << "  -W: display the configuration report and exit"
              << std::endl
              << "  -d: optional, verbose output " << std::endl
              << "  -c <config file name> : mandatory,"
              << " specify name of configuration file" << std::endl
              << "  -t <config file name> : check the"
              << " configuration file and exit" << std::endl;

    // add any derivation specific usage
    std::cerr << getUsageText() << std::endl;
}

DControllerBase::~DControllerBase() {
}

// Refer to config_report so it will be embedded in the binary
const char* const* d2_config_report = isc::detail::config_report;

std::string
DControllerBase::getVersion(bool extended) {
    std::stringstream tmp;

    tmp << VERSION;
    if (extended) {
        tmp << std::endl << EXTENDED_VERSION << std::endl;
        tmp << "linked with:" << std::endl;
        tmp << isc::log::Logger::getVersion() << std::endl;
        tmp << getVersionAddendum();
    }

    return (tmp.str());
}

}; // namespace isc::process

}; // namespace isc
