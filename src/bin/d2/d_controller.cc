// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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


#include <d2/d2_log.h>
#include <d2/d_controller.h>
#include <exceptions/exceptions.h>
#include <log/logger_support.h>

#include <sstream>

namespace isc {
namespace d2 {

DControllerBasePtr DControllerBase::controller_;

// Note that the constructor instantiates the controller's primary IOService.
DControllerBase::DControllerBase(const char* name) 
    : name_(name), stand_alone_(false), verbose_(false), 
    spec_file_name_(""), io_service_(new isc::asiolink::IOService()){
}

void 
DControllerBase::setController(DControllerBase* controller) {
    if (controller_) {
        // This shouldn't happen, but let's make sure it can't be done.
        // It represents a programmatic error.
        isc_throw (DControllerBaseError,
                "Multiple controller instances attempted.");
    }

    controller_ = DControllerBasePtr(controller);
}

int
DControllerBase::launch(int argc, char* argv[]) {
    int ret = EXIT_SUCCESS;

    // Step 1 is to parse the command line arguments.
    try {
        parseArgs(argc, argv);
    } catch (const InvalidUsage& ex) {
        usage(ex.what());
        return (EXIT_FAILURE);
    }

#if 1
    //@TODO During initial development default to max log, no buffer
    isc::log::initLogger(name_, isc::log::DEBUG, 
                         isc::log::MAX_DEBUG_LEVEL, NULL, false);
#else
    // Now that we know what the mode flags are, we can init logging.
    // If standalone is enabled, do not buffer initial log messages
    isc::log::initLogger(name_,
                         ((verbose_ && stand_alone_) 
                          ? isc::log::DEBUG : isc::log::INFO),
                         isc::log::MAX_DEBUG_LEVEL, NULL, !stand_alone_);
#endif

    LOG_DEBUG(d2_logger, DBGLVL_START_SHUT, D2CTL_STARTING).arg(getpid());
    try {
        // Step 2 is to create and init the application process.
        initProcess();

        // Next we connect if we are running integrated.
        if (!stand_alone_) {
            try {
                establishSession();
            } catch (const std::exception& ex) {
                LOG_ERROR(d2_logger, D2CTL_SESSION_FAIL).arg(ex.what());
                return (EXIT_FAILURE);
            }
        } else {
            LOG_DEBUG(d2_logger, DBGLVL_START_SHUT, D2CTL_STANDALONE);
        }

        // Everything is clear for launch, so start the application's
        // event loop.
        runProcess();
    } catch (const std::exception& ex) {
        LOG_FATAL(d2_logger, D2CTL_FAILED).arg(ex.what());
        ret = EXIT_FAILURE;
    }

    // If running integrated, always try to disconnect.
    if (!stand_alone_) {
        try { 
            disconnectSession();
        } catch (const std::exception& ex) {
            LOG_ERROR(d2_logger, D2CTL_DISCONNECT_FAIL).arg(ex.what());
            ret = EXIT_FAILURE;
        }
    }

    // All done, so bail out.
    LOG_INFO(d2_logger, D2CTL_STOPPING);
    return (ret);
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
    std::string opts(":vs" + getCustomOpts());
    while ((ch = getopt(argc, argv, opts.c_str())) != -1) {
        switch (ch) {
        case 'v':
            // Enables verbose logging.
            verbose_ = true;
            break;

        case 's':
            // Enables stand alone or "BINDLESS" operation.
            stand_alone_ = true;
            break;

        case '?': {
            // We hit an invalid option.
            std::stringstream tmp;
            tmp << " unsupported option: [" << (char)optopt << "] "
                << (!optarg ? "" : optarg);

            isc_throw(InvalidUsage,tmp.str());
            break;
            }
            
        default:
            // We hit a valid custom option
            if (!customOption(ch, optarg)) {
                // this would be a programmatic err
                std::stringstream tmp;
                tmp << " Option listed but implemented?: [" << 
                        (char)ch << "] " << (!optarg ? "" : optarg);
                isc_throw(InvalidUsage,tmp.str());
            }
            break;
        }
    }

    // There was too much information on the command line.
    if (argc > optind) {
        std::stringstream tmp;
        tmp << "extraneous command line information"; 
        isc_throw(InvalidUsage,tmp.str());
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
    LOG_DEBUG(d2_logger, DBGLVL_START_SHUT, D2CTL_INIT_PROCESS);
  
    // Invoke virtual method to instantiate the application process. 
    try {
        process_.reset(createProcess()); 
    } catch (const std::exception& ex) {
        isc_throw (DControllerBaseError, std::string("createProcess failed:")
                    + ex.what()); 
    }

    // This is pretty unlikely, but will test for it just to be safe..
    if (!process_) {
        isc_throw (DControllerBaseError, "createProcess returned NULL");
    }  

    // Invoke application's init method
    // @TODO This call may throw DProcessError 
    process_->init();
}

void 
DControllerBase::establishSession() {
    LOG_DEBUG(d2_logger, DBGLVL_START_SHUT, D2CTL_CCSESSION_STARTING)
              .arg(spec_file_name_);

    // Create the BIND10 command control session with the our IOService.
    cc_session_ = SessionPtr(new isc::cc::Session(
                             io_service_->get_io_service()));

    // Create the BIND10 config session with the stub configuration handler.
    // This handler is internally invoked by the constructor and on success 
    // the constructor updates the current session with the configuration that
    // had been committed in the previous session. If we do not install
    // the dummy handler, the previous configuration would be lost. 
    config_session_ = ModuleCCSessionPtr(new isc::config::ModuleCCSession(
                                         spec_file_name_, *cc_session_,
                                         dummyConfigHandler, commandHandler, 
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
        LOG_ERROR(d2_logger, D2CTL_CONFIG_LOAD_FAIL).arg(comment->str());
    }

    // Lastly, call onConnect. This allows deriving class to execute custom 
    // logic predicated by session connect.
    onSessionConnect();
}

void
DControllerBase::runProcess() {
    LOG_DEBUG(d2_logger, DBGLVL_START_SHUT, D2CTL_RUN_PROCESS);
    if (!process_) {
        // This should not be possible.
        isc_throw(DControllerBaseError, "Process not initialized");
    }

    // Invoke the applicatio process's run method. This may throw DProcessError
    process_->run();
}

void DControllerBase::disconnectSession() {
    LOG_DEBUG(d2_logger, DBGLVL_START_SHUT, D2CTL_CCSESSION_ENDING);

    // Call virtual onDisconnect. Allows deriving class to execute custom 
    // logic prior to session loss.
    onSessionDisconnect();

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
DControllerBase::dummyConfigHandler(isc::data::ConstElementPtr) {
    LOG_DEBUG(d2_logger, DBGLVL_START_SHUT, D2CTL_CONFIG_STUB);
    return (isc::config::createAnswer(0, "Configuration accepted."));
}

isc::data::ConstElementPtr
DControllerBase::configHandler(isc::data::ConstElementPtr new_config) {

    LOG_DEBUG(d2_logger, DBGLVL_COMMAND, D2CTL_CONFIG_UPDATE)
            .arg(new_config->str());

    if (!controller_) {
        // This should never happen as we install the handler after we 
        // instantiate the server.
        isc::data::ConstElementPtr answer =
            isc::config::createAnswer(1, "Configuration rejected,"
                                   " Controller has not been initialized.");
        return (answer);
    }

    // Invoke the instance method on the controller singleton.
    return (controller_->updateConfig(new_config));
}

// Static callback which invokes non-static handler on singleton
isc::data::ConstElementPtr
DControllerBase::commandHandler(const std::string& command, 
                            isc::data::ConstElementPtr args) {

    LOG_DEBUG(d2_logger, DBGLVL_COMMAND, D2CTL_COMMAND_RECEIVED)
              .arg(command).arg(args->str());

    if (!controller_ )  {
        // This should never happen as we install the handler after we 
        // instantiate the server.
        isc::data::ConstElementPtr answer =
            isc::config::createAnswer(1, "Command rejected,"
                                   " Controller has not been initialized.");
        return (answer);
    }

    // Invoke the instance method on the controller singleton.
    return (controller_->executeCommand(command, args));
}

isc::data::ConstElementPtr
DControllerBase::updateConfig(isc::data::ConstElementPtr new_config) {
    isc::data::ConstElementPtr full_config;
    if (stand_alone_) { 
        // @TODO Until there is a configuration manager to provide retrieval
        // we'll just assume the incoming config is the full configuration set.
        // It may also make more sense to isolate the controller from the
        // configuration manager entirely. We could do something like
        // process_->getFullConfig() here for stand-alone mode?
        full_config = new_config;
    } else { 
        if (!config_session_) {
            // That should never happen as we install config_handler
            // after we instantiate the server.
            isc::data::ConstElementPtr answer =
                    isc::config::createAnswer(1, "Configuration rejected,"
                                              " Session has not started.");
            return (answer);
        }

        // Let's get the existing configuration.
        full_config = config_session_->getFullConfig();
    }

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
    return (process_->configure(merged_config));
}


isc::data::ConstElementPtr
DControllerBase::executeCommand(const std::string& command, 
                            isc::data::ConstElementPtr args) {
    // Shutdown is univeral.  If its not that, then try it as
    // an custom command supported by the derivation.  If that
    // doesn't pan out either, than send to it the application
    // as it may be supported there.
    isc::data::ConstElementPtr answer;
    if (command.compare(SHUT_DOWN_COMMAND) == 0) {
        answer = shutdown();
    } else {
        // It wasn't shutdown, so may be a custom controller command.
        int rcode = 0;
        answer = customControllerCommand(command, args);
        isc::config::parseAnswer(rcode, answer); 
        if (rcode == COMMAND_INVALID)
        {
            // It wasn't controller command, so may be an application command.
            answer = process_->command(command,args);
        }
    }

    return (answer);
}

isc::data::ConstElementPtr
DControllerBase::customControllerCommand(const std::string& command, 
                                     isc::data::ConstElementPtr /* args */) {

    // Default implementation always returns invalid command.
    return (isc::config::createAnswer(COMMAND_INVALID,
                                      "Unrecognized command:" + command));
}

isc::data::ConstElementPtr 
DControllerBase::shutdown() {
    // @TODO TKM - not sure about io_service_->stop here
    // IF application is using this service for all of its IO, stopping
    // here would mean, no more work by the application.. UNLESS it resets
    // it. People have discussed letting the application finish any in-progress
    // updates before shutting down.  If we don't stop it here, then 
    // application can't use io_service_->run(), it will never "see" the 
    // shutdown.
    io_service_->stop();
    if (process_) {
        process_->shutdown();
    } else {
        // Not really a failure, but this condition is worth noting. In reality
        // it should be pretty hard to cause this.
        LOG_WARN(d2_logger, D2CTL_NOT_RUNNING);
    }

    return (isc::config::createAnswer(0, "Shutting down."));
}

void
DControllerBase::usage(const std::string & text)
{
    if (text != "") {
        std::cerr << "Usage error:" << text << std::endl;
    }

    std::cerr << "Usage: " << name_ <<  std::endl;
    std::cerr << "  -v: verbose output" << std::endl;
    std::cerr << "  -s: stand-alone mode (don't connect to BIND10)" 
              << std::endl;
   
    std::cerr << getUsageText() << std::endl; 

    exit(EXIT_FAILURE);

}

DControllerBase::~DControllerBase() {
}

}; // namespace isc::d2
}; // namespace isc
