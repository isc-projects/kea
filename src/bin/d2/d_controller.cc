// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>
#include <d2/d2_log.h>
#include <cc/command_interpreter.h>
#include <d2/d_controller.h>
#include <exceptions/exceptions.h>
#include <log/logger_support.h>
#include <dhcpsrv/cfgmgr.h>
#include <cryptolink/cryptolink.h>
#include <log/logger.h>
#include <cfgrpt/config_report.h>

#ifdef HAVE_MYSQL
#include <dhcpsrv/mysql_lease_mgr.h>
#endif
#ifdef HAVE_PGSQL
#include <dhcpsrv/pgsql_lease_mgr.h>
#endif
#include <dhcpsrv/memfile_lease_mgr.h>

#include <sstream>
#include <unistd.h>

namespace isc {
namespace d2 {

DControllerBasePtr DControllerBase::controller_;

// Note that the constructor instantiates the controller's primary IOService.
DControllerBase::DControllerBase(const char* app_name, const char* bin_name)
    : app_name_(app_name), bin_name_(bin_name),
      verbose_(false), spec_file_name_(""),
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

void
DControllerBase::launch(int argc, char* argv[], const bool test_mode) {

    // Step 1 is to parse the command line arguments.
    try {
        parseArgs(argc, argv);
    } catch (const InvalidUsage& ex) {
        usage(ex.what());
        throw; // rethrow it
    }

    // It is important that we set a default logger name because this name
    // will be used when the user doesn't provide the logging configuration
    // in the Kea configuration file.
    isc::dhcp::CfgMgr::instance().setDefaultLoggerName(bin_name_);

    // Logger's default configuration depends on whether we are in the
    // verbose mode or not. CfgMgr manages the logger configuration so
    // the verbose mode is set for CfgMgr.
    isc::dhcp::CfgMgr::instance().setVerbose(verbose_);

    // Do not initialize logger here if we are running unit tests. It would
    // replace an instance of unit test specific logger.
    if (!test_mode) {
        // Now that we know what the mode flags are, we can init logging.
        Daemon::loggerInit(bin_name_.c_str(), verbose_);
    }

    // Log the starting of the service.  Although this is the controller
    // module, use a "DHCP_DDNS_" prefix to the module (to conform to the
    // principle of least astonishment).
    LOG_INFO(dctl_logger, DHCP_DDNS_STARTING).arg(getpid()).arg(VERSION);
    try {
        // Step 2 is to create and initialize the application process object.
        initProcess();
    } catch (const std::exception& ex) {
        LOG_FATAL(dctl_logger, DCTL_INIT_PROCESS_FAIL)
                  .arg(app_name_).arg(ex.what());
        isc_throw (ProcessInitError,
                   "Application Process initialization failed: " << ex.what());
    }

    LOG_DEBUG(dctl_logger, DBGLVL_START_SHUT, DCTL_STANDALONE).arg(app_name_);

    // Step 3 is to load configuration from file.
    int rcode;
    isc::data::ConstElementPtr comment
        = isc::config::parseAnswer(rcode, configFromFile());
    if (rcode != 0) {
        LOG_FATAL(dctl_logger, DCTL_CONFIG_FILE_LOAD_FAIL)
                  .arg(app_name_).arg(comment->stringValue());
        isc_throw (ProcessInitError, "Could Not load configration file: "
                   << comment->stringValue());
    }

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

    // All done, so bail out.  Log the event (using a DHCP_DDNS_ prefix
    // for the same reason as used for DHCP_DDNS_STARTING).
    LOG_INFO(dctl_logger, DHCP_DDNS_SHUTDOWN);
}

void
DControllerBase::parseArgs(int argc, char* argv[])
{
    // Iterate over the given command line options. If its a stock option
    // ("s" or "v") handle it here.  If its a valid custom option, then
    // invoke customOption.
    int ch;
    opterr = 0;
    optind = 1;
    std::string opts("dvVWc:" + getCustomOpts());
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
            // config file name
            if (optarg == NULL) {
                isc_throw(InvalidUsage, "configuration file name missing");
            }

            Daemon::init(optarg);
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
    LOG_DEBUG(dctl_logger, DBGLVL_START_SHUT, DCTL_INIT_PROCESS).arg(app_name_);

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

isc::data::ConstElementPtr
DControllerBase::configFromFile() {
    // Rollback any previous staging configuration. For D2, only a
    // logger configuration is used here.
    isc::dhcp::CfgMgr::instance().rollback();
    // Will hold configuration.
    isc::data::ConstElementPtr module_config;
    // Will receive configuration result.
    isc::data::ConstElementPtr answer;
    try {
        std::string config_file = getConfigFile();
        if (config_file.empty()) {
            // Basic sanity check: file name must not be empty.
            isc_throw(BadValue, "JSON configuration file not specified. Please "
                                "use -c command line option.");
        }

        // Read contents of the file and parse it as JSON
        isc::data::ConstElementPtr whole_config =
            isc::data::Element::fromJSONFile(config_file, true);

        // Let's configure logging before applying the configuration,
        // so we can log things during configuration process.

        // Temporary storage for logging configuration
        isc::dhcp::SrvConfigPtr storage =
            isc::dhcp::CfgMgr::instance().getStagingCfg();

        // Get 'Logging' element from the config and use it to set up
        // logging. If there's no such element, we'll just pass NULL.
        Daemon::configureLogger(whole_config->get("Logging"), storage);

        // Extract derivation-specific portion of the configuration.
        module_config = whole_config->get(getAppName());
        if (!module_config) {
            isc_throw(BadValue, "Config file " << config_file <<
                                " does not include '" <<
                                 getAppName() << "' entry.");
        }

        answer = updateConfig(module_config);
        int rcode = 0;
        isc::config::parseAnswer(rcode, answer);
        if (!rcode) {
            // Configuration successful, so apply the logging configuration
            // to log4cplus.
            isc::dhcp::CfgMgr::instance().getStagingCfg()->applyLoggingCfg();
            isc::dhcp::CfgMgr::instance().commit();
        }

    } catch (const std::exception& ex) {
        // Rollback logging configuration.
        isc::dhcp::CfgMgr::instance().rollback();
        // build an error result
        isc::data::ConstElementPtr error =
            isc::config::createAnswer(1,
                std::string("Configuration parsing failed: ") + ex.what());
        return (error);
    }

    return (answer);
}


void
DControllerBase::runProcess() {
    LOG_DEBUG(dctl_logger, DBGLVL_START_SHUT, DCTL_RUN_PROCESS).arg(app_name_);
    if (!process_) {
        // This should not be possible.
        isc_throw(DControllerBaseError, "Process not initialized");
    }

    // Invoke the application process's run method. This may throw
    // DProcessBaseError
    process_->run();
}

// Instance method for handling new config
isc::data::ConstElementPtr
DControllerBase::updateConfig(isc::data::ConstElementPtr new_config) {
    return (process_->configure(new_config));
}


// Instance method for executing commands
isc::data::ConstElementPtr
DControllerBase::executeCommand(const std::string& command,
                            isc::data::ConstElementPtr args) {
    // Shutdown is universal.  If its not that, then try it as
    // a custom command supported by the derivation.  If that
    // doesn't pan out either, than send to it the application
    // as it may be supported there.
    isc::data::ConstElementPtr answer;
    if (command.compare(SHUT_DOWN_COMMAND) == 0) {
        answer = shutdownProcess(args);
    } else {
        // It wasn't shutdown, so it may be a custom controller command.
        int rcode = 0;
        answer = customControllerCommand(command, args);
        isc::config::parseAnswer(rcode, answer);
        if (rcode == COMMAND_INVALID)
        {
            // It wasn't a controller command, so it may be an application command.
            answer = process_->command(command, args);
        }
    }

    return (answer);
}

isc::data::ConstElementPtr
DControllerBase::customControllerCommand(const std::string& command,
                                     isc::data::ConstElementPtr /* args */) {

    // Default implementation always returns invalid command.
    return (isc::config::createAnswer(COMMAND_INVALID,
                                      "Unrecognized command: " + command));
}

isc::data::ConstElementPtr
DControllerBase::shutdownProcess(isc::data::ConstElementPtr args) {
    if (process_) {
        return (process_->shutdown(args));
    }

    // Not really a failure, but this condition is worth noting. In reality
    // it should be pretty hard to cause this.
    LOG_WARN(dctl_logger, DCTL_NOT_RUNNING).arg(app_name_);
    return (isc::config::createAnswer(0, "Process has not been initialzed."));
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
            LOG_INFO(dctl_logger, DHCP_DDNS_CFG_FILE_RELOAD_SIGNAL_RECVD)
                     .arg(signum).arg(getConfigFile());
            int rcode;
            isc::data::ConstElementPtr comment = isc::config::
                                                 parseAnswer(rcode,
                                                             configFromFile());
            if (rcode != 0) {
                LOG_ERROR(dctl_logger, DHCP_DDNS_CFG_FILE_RELOAD_ERROR)
                          .arg(comment->stringValue());
            }

            break;
        }

        case SIGINT:
        case SIGTERM:
        {
            LOG_DEBUG(dctl_logger, DBGLVL_START_SHUT,
                      DHCP_DDNS_SHUTDOWN_SIGNAL_RECVD).arg(signum);
            isc::data::ElementPtr arg_set;
            executeCommand(SHUT_DOWN_COMMAND, arg_set);
            break;
        }

        default:
            LOG_WARN(dctl_logger, DHCP_DDNS_UNSUPPORTED_SIGNAL).arg(signum);
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
              <<   " specifies name of configuration file " << std::endl;

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
        tmp << isc::cryptolink::CryptoLink::getVersion() << std::endl;
        tmp << "database:" << std::endl; 
#ifdef HAVE_MYSQL
        tmp << isc::dhcp::MySqlLeaseMgr::getDBVersion() << std::endl;
#endif
#ifdef HAVE_PGSQL
        tmp << isc::dhcp::PgSqlLeaseMgr::getDBVersion() << std::endl;
#endif
        tmp << isc::dhcp::Memfile_LeaseMgr::getDBVersion();

        // @todo: more details about database runtime
    }

    return (tmp.str());
}

}; // namespace isc::d2

}; // namespace isc
