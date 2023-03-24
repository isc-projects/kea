// Copyright (C) 2013-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <cc/command_interpreter.h>
#include <config/command_mgr.h>
#include <d2/d2_controller.h>
#include <d2/d2_process.h>
#include <d2srv/d2_cfg_mgr.h>
#include <d2srv/d2_log.h>
#include <d2srv/d2_stats.h>
#include <d2srv/d2_tsig_key.h>
#include <hooks/hooks.h>
#include <hooks/hooks_manager.h>

using namespace isc::config;
using namespace isc::hooks;
using namespace isc::process;

namespace {

/// Structure that holds registered hook indexes.
struct D2ProcessHooks {
    int hooks_index_d2_srv_configured_;

    /// Constructor that registers hook points for the D2 server.
    D2ProcessHooks() {
        hooks_index_d2_srv_configured_ = HooksManager::registerHook("d2_srv_configured");
    }

};

// Declare a Hooks object. As this is outside any function or method, it
// will be instantiated (and the constructor run) when the module is loaded.
// As a result, the hook indexes will be defined before any method in this
// module is called.
D2ProcessHooks Hooks;

}

namespace isc {
namespace d2 {

// Setting to 80% for now. This is an arbitrary choice and should probably
// be configurable.
const unsigned int D2Process::QUEUE_RESTART_PERCENT = 80;

D2Process::D2Process(const char* name, const asiolink::IOServicePtr& io_service)
    : DProcessBase(name, io_service, DCfgMgrBasePtr(new D2CfgMgr())),
      reconf_queue_flag_(false), shutdown_type_(SD_NORMAL) {

    // Instantiate queue manager.  Note that queue manager does not start
    // listening at this point.  That can only occur after configuration has
    // been received.  This means that until we receive the configuration,
    // D2 will neither receive nor process NameChangeRequests.
    // Pass in IOService for NCR IO event processing.
    queue_mgr_.reset(new D2QueueMgr(getIoService()));

    // Instantiate update manager.
    // Pass in both queue manager and configuration manager.
    // Pass in IOService for DNS update transaction IO event processing.
    D2CfgMgrPtr tmp = getD2CfgMgr();
    update_mgr_.reset(new D2UpdateMgr(queue_mgr_, tmp, getIoService()));

    // Initialize stats manager.
    D2Stats::init();
};

void
D2Process::init() {
    // CommandMgr uses IO service to run asynchronous socket operations.
    isc::config::CommandMgr::instance().setIOService(getIoService());
};

void
D2Process::run() {
    LOG_INFO(d2_logger, DHCP_DDNS_STARTED).arg(VERSION);
    D2ControllerPtr controller =
        boost::dynamic_pointer_cast<D2Controller>(D2Controller::instance());
    try {
        // Now logging was initialized so commands can be registered.
        controller->registerCommands();

        // Loop forever until we are allowed to shutdown.
        while (!canShutdown()) {
            // Check on the state of the request queue. Take any
            // actions necessary regarding it.
            checkQueueStatus();

            // Give update manager a time slice to queue new jobs and
            // process finished ones.
            update_mgr_->sweep();

            // Wait on IO event(s) - block until one or more of the following
            // has occurred:
            //   a. NCR message has been received
            //   b. Transaction IO has completed
            //   c. Interval timer expired
            //   d. Control channel event
            //   e. Something stopped IO service (runIO returns 0)
            if (runIO() == 0) {
                // Pretty sure this amounts to an unexpected stop and we
                // should bail out now.  Normal shutdowns do not utilize
                // stopping the IOService.
                isc_throw(DProcessBaseError,
                          "Primary IO service stopped unexpectedly");
            }
        }
    } catch (const std::exception& ex) {
        LOG_FATAL(d2_logger, DHCP_DDNS_FAILED).arg(ex.what());
        controller->deregisterCommands();
        isc_throw (DProcessBaseError,
                   "Process run method failed: " << ex.what());
    }

    /// @todo - if queue isn't empty, we may need to persist its contents
    /// this might be the place to do it, once there is a persistence mgr.
    /// This may also be better in checkQueueStatus.

    controller->deregisterCommands();

    LOG_DEBUG(d2_logger, isc::log::DBGLVL_START_SHUT, DHCP_DDNS_RUN_EXIT);

};

size_t
D2Process::runIO() {
    // We want to block until at least one handler is called.  We'll use
    // boost::asio::io_service directly for two reasons. First off
    // asiolink::IOService::run_one is a void and boost::asio::io_service::stopped
    // is not present in older versions of boost.  We need to know if any
    // handlers ran or if the io_service was stopped.  That latter represents
    // some form of error and the application cannot proceed with a stopped
    // service.  Secondly, asiolink::IOService does not provide the poll
    // method.  This is a handy method which runs all ready handlers without
    // blocking.
    asiolink::IOServicePtr& io = getIoService();
    boost::asio::io_service& asio_io_service = io->get_io_service();

    // Poll runs all that are ready. If none are ready it returns immediately
    // with a count of zero.
    size_t cnt = asio_io_service.poll();
    if (!cnt) {
        // Poll ran no handlers either none are ready or the service has been
        // stopped.  Either way, call run_one to wait for a IO event. If the
        // service is stopped it will return immediately with a cnt of zero.
        cnt = asio_io_service.run_one();
    }

    return (cnt);
}

bool
D2Process::canShutdown() const {
    bool all_clear = false;

    // If we have been told to shutdown, find out if we are ready to do so.
    if (shouldShutdown()) {
        switch (shutdown_type_) {
        case SD_NORMAL:
            // For a normal shutdown we need to stop the queue manager but
            // wait until we have finished all the transactions in progress.
            all_clear = (((queue_mgr_->getMgrState() != D2QueueMgr::RUNNING) &&
                          (queue_mgr_->getMgrState() != D2QueueMgr::STOPPING))
                         && (update_mgr_->getTransactionCount() == 0));
            break;

        case SD_DRAIN_FIRST:
            // For a drain first shutdown we need to stop the queue manager but
            // process all of the requests in the receive queue first.
            all_clear = (((queue_mgr_->getMgrState() != D2QueueMgr::RUNNING) &&
                          (queue_mgr_->getMgrState() != D2QueueMgr::STOPPING))
                          && (queue_mgr_->getQueueSize() == 0)
                          && (update_mgr_->getTransactionCount() == 0));
            break;

        case SD_NOW:
            // Get out right now, no niceties.
            all_clear = true;
            break;

        default:
            // shutdown_type_ is an enum and should only be one of the above.
            // if its getting through to this, something is whacked.
            break;
        }

        if (all_clear) {
            LOG_DEBUG(d2_logger, isc::log::DBGLVL_START_SHUT,
                     DHCP_DDNS_CLEARED_FOR_SHUTDOWN)
                .arg(getShutdownTypeStr(shutdown_type_));
        }
    }

    return (all_clear);
}

isc::data::ConstElementPtr
D2Process::shutdown(isc::data::ConstElementPtr args) {
    LOG_DEBUG(d2_logger, isc::log::DBGLVL_START_SHUT,
              DHCP_DDNS_SHUTDOWN_COMMAND)
        .arg(args ? args->str() : "(no arguments)");

    // Default shutdown type is normal.
    std::string type_str(getShutdownTypeStr(SD_NORMAL));
    shutdown_type_ = SD_NORMAL;

    if (args) {
        if ((args->getType() == isc::data::Element::map) &&
            args->contains("type")) {
            type_str = args->get("type")->stringValue();

            if (type_str == getShutdownTypeStr(SD_NORMAL)) {
                shutdown_type_ = SD_NORMAL;
            } else if (type_str == getShutdownTypeStr(SD_DRAIN_FIRST)) {
                shutdown_type_ = SD_DRAIN_FIRST;
            } else if (type_str == getShutdownTypeStr(SD_NOW)) {
                shutdown_type_ = SD_NOW;
            } else {
                setShutdownFlag(false);
                return (isc::config::createAnswer(CONTROL_RESULT_ERROR,
                                                  "Invalid Shutdown type: " +
                                                  type_str));
            }
        }
    }

    // Set the base class's shutdown flag.
    setShutdownFlag(true);
    return (isc::config::createAnswer(CONTROL_RESULT_SUCCESS,
                                      "Shutdown initiated, type is: " +
                                      type_str));
}

isc::data::ConstElementPtr
D2Process::configure(isc::data::ConstElementPtr config_set, bool check_only) {
    LOG_DEBUG(d2_logger, isc::log::DBGLVL_TRACE_BASIC, DHCP_DDNS_CONFIGURE)
        .arg(check_only ? "check" : "update")
        .arg(getD2CfgMgr()->redactConfig(config_set)->str());

    isc::data::ConstElementPtr answer;
    answer = getCfgMgr()->simpleParseConfig(config_set, check_only,
                std::bind(&D2Process::reconfigureCommandChannel, this));
    if (check_only) {
        return (answer);
    }

    int rcode = 0;
    isc::data::ConstElementPtr comment;
    comment = isc::config::parseAnswer(rcode, answer);

    if (rcode) {
        // Non-zero means we got an invalid configuration, take no further
        // action. In integrated mode, this will send a failed response back
        // to the configuration backend.
        reconf_queue_flag_ = false;
        return (answer);
    }

    // Set the reconf_queue_flag to indicate that we need to reconfigure
    // the queue manager.  Reconfiguring the queue manager may be asynchronous
    // and require one or more events to occur, therefore we set a flag
    // indicating it needs to be done but we cannot do it here.  It must
    // be done over time, while events are being processed.  Remember that
    // the method we are in now is invoked as part of the configuration event
    // callback.  This means you can't wait for events here, you are already
    // in one.
    /// (@todo NOTE This could be turned into a bitmask of flags if we find other
    /// things that need reconfiguration.  It might also be useful if we
    /// did some analysis to decide what if anything we need to do.)
    reconf_queue_flag_ = true;

    // This hook point notifies hooks libraries that the configuration of the
    // D2 server has completed. It provides the hook library with the pointer
    // to the common IO service object, new server configuration in the JSON
    // format and with the pointer to the configuration storage where the
    // parsed configuration is stored.
    std::string error("");
    if (HooksManager::calloutsPresent(Hooks.hooks_index_d2_srv_configured_)) {
        CalloutHandlePtr callout_handle = HooksManager::createCalloutHandle();

        callout_handle->setArgument("io_context", getIoService());
        callout_handle->setArgument("json_config", config_set);
        callout_handle->setArgument("server_config",
                                    getD2CfgMgr()->getD2CfgContext());
        callout_handle->setArgument("error", error);

        HooksManager::callCallouts(Hooks.hooks_index_d2_srv_configured_,
                                   *callout_handle);

        // The config can be rejected by a hook.
        if (callout_handle->getStatus() == CalloutHandle::NEXT_STEP_DROP) {
            callout_handle->getArgument("error", error);
            LOG_ERROR(d2_logger, DHCP_DDNS_CONFIGURED_CALLOUT_DROP)
                .arg(error);
            reconf_queue_flag_ = false;
            answer = isc::config::createAnswer(CONTROL_RESULT_ERROR, error);
            return (answer);
        }
    }

    // If we are here, configuration was valid, at least it parsed correctly
    // and therefore contained no invalid values.
    // Return the success answer from above.
    return (answer);
}

void
D2Process::checkQueueStatus() {
    switch (queue_mgr_->getMgrState()){
    case D2QueueMgr::RUNNING:
        if (reconf_queue_flag_ || shouldShutdown()) {
            /// If we need to reconfigure the queue manager or we have been
            /// told to shutdown, then stop listening first.  Stopping entails
            /// canceling active listening which may generate an IO event, so
            /// instigate the stop and get out.
            try {
                LOG_DEBUG(d2_logger, isc::log::DBGLVL_START_SHUT,
                          DHCP_DDNS_QUEUE_MGR_STOPPING)
                    .arg(reconf_queue_flag_ ? "reconfiguration" : "shutdown");
                queue_mgr_->stopListening();
            } catch (const isc::Exception& ex) {
                // It is very unlikely that we would experience an error
                // here, but theoretically possible.
                LOG_ERROR(d2_logger, DHCP_DDNS_QUEUE_MGR_STOP_ERROR)
                          .arg(ex.what());
            }
        }
        break;

    case D2QueueMgr::STOPPED_QUEUE_FULL: {
            /// Resume receiving once the queue has decreased by twenty
            /// percent.  This is an arbitrary choice.
            /// @todo this value should probably be configurable.
            size_t threshold = (((queue_mgr_->getMaxQueueSize()
                                * QUEUE_RESTART_PERCENT)) / 100);
            if (queue_mgr_->getQueueSize() <= threshold) {
                LOG_INFO (d2_logger, DHCP_DDNS_QUEUE_MGR_RESUMING)
                          .arg(threshold).arg(queue_mgr_->getMaxQueueSize());
                try {
                    queue_mgr_->startListening();
                } catch (const isc::Exception& ex) {
                    LOG_ERROR(d2_logger, DHCP_DDNS_QUEUE_MGR_RESUME_ERROR)
                              .arg(ex.what());
                }
            }

        break;
        }

    case D2QueueMgr::STOPPED_RECV_ERROR:
        /// If the receive error is not due to some fallout from shutting
        /// down then we will attempt to recover by reconfiguring the listener.
        /// This will close and destruct the current listener and make a new
        /// one with new resources.
        /// @todo This may need a safety valve such as retry count or a timer
        /// to keep from endlessly retrying over and over, with little time
        /// in between.
        if (!shouldShutdown()) {
            LOG_INFO (d2_logger, DHCP_DDNS_QUEUE_MGR_RECOVERING);
            reconfigureQueueMgr();
        }
        break;

    case D2QueueMgr::STOPPING:
        /// We are waiting for IO to cancel, so this is a NOP.
        /// @todo Possible timer for self-defense?  We could conceivably
        /// get into a condition where we never get the event, which would
        /// leave us stuck in stopping.  This is hugely unlikely but possible?
        break;

    default:
        // If the reconfigure flag is set, then we are in a state now where
        // we can do the reconfigure. In other words, we aren't RUNNING or
        // STOPPING.
        if (reconf_queue_flag_) {
            LOG_DEBUG(d2_logger, isc::log::DBGLVL_TRACE_BASIC,
                      DHCP_DDNS_QUEUE_MGR_RECONFIGURING);
            reconfigureQueueMgr();
        }
        break;
    }
}

void
D2Process::reconfigureQueueMgr() {
    // Set reconfigure flag to false.  We are only here because we have
    // a valid configuration to work with so if we fail below, it will be
    // an operational issue, such as a busy IP address. That will leave
    // queue manager in INITTED state, which is fine.
    // What we don't want is to continually attempt to reconfigure so set
    // the flag false now.
    /// @todo This method assumes only 1 type of listener.  This will change
    /// to support at least a TCP version, possibly some form of RDBMS listener
    /// as well.
    reconf_queue_flag_ = false;
    try {
        // Wipe out the current listener.
        queue_mgr_->removeListener();

        // Get the configuration parameters that affect Queue Manager.
        const D2ParamsPtr& d2_params = getD2CfgMgr()->getD2Params();

        /// Warn the user if the server address is not the loopback.
        /// @todo Remove this once we provide a secure mechanism.
        std::string ip_address = d2_params->getIpAddress().toText();
        if (ip_address != "127.0.0.1" && ip_address != "::1") {
            LOG_WARN(d2_logger, DHCP_DDNS_NOT_ON_LOOPBACK).arg(ip_address);
        }

        // Instantiate the listener.
        if (d2_params->getNcrProtocol() == dhcp_ddns::NCR_UDP) {
            queue_mgr_->initUDPListener(d2_params->getIpAddress(),
                                        d2_params->getPort(),
                                        d2_params->getNcrFormat(), true);
        } else {
            /// @todo Add TCP/IP once it's supported
            // We should never get this far but if we do deal with it.
            isc_throw(DProcessBaseError, "Unsupported NCR listener protocol:"
                      << dhcp_ddns::ncrProtocolToString(d2_params->
                                                        getNcrProtocol()));
        }

        // Now start it. This assumes that starting is a synchronous,
        // blocking call that executes quickly.
        /// @todo Should that change then we will have to expand the state model
        /// to accommodate this.
        queue_mgr_->startListening();
    } catch (const isc::Exception& ex) {
        // Queue manager failed to initialize and therefore not listening.
        // This is most likely due to an unavailable IP address or port,
        // which is a configuration issue.
        LOG_ERROR(d2_logger, DHCP_DDNS_QUEUE_MGR_START_ERROR).arg(ex.what());
    }
}

D2Process::~D2Process() {
}

D2CfgMgrPtr
D2Process::getD2CfgMgr() {
    // The base class gives a base class pointer to our configuration manager.
    // Since we are D2, and we need D2 specific extensions, we need a pointer
    // to D2CfgMgr for some things.
    return (boost::dynamic_pointer_cast<D2CfgMgr>(getCfgMgr()));
}

const char* D2Process::getShutdownTypeStr(const ShutdownType& type) {
    const char* str = "invalid";
    switch (type) {
    case SD_NORMAL:
        str = "normal";
        break;
    case SD_DRAIN_FIRST:
        str = "drain_first";
        break;
    case SD_NOW:
        str = "now";
        break;
    default:
        break;
    }

    return (str);
}

void
D2Process::reconfigureCommandChannel() {
    // Get new socket configuration.
    isc::data::ConstElementPtr sock_cfg = getD2CfgMgr()->getControlSocketInfo();

    // Determine if the socket configuration has changed. It has if
    // both old and new configuration is specified but respective
    // data elements aren't equal.
    bool sock_changed = (sock_cfg && current_control_socket_ &&
                         !sock_cfg->equals(*current_control_socket_));

    // If the previous or new socket configuration doesn't exist or
    // the new configuration differs from the old configuration we
    // close the existing socket and open a new socket as appropriate.
    // Note that closing an existing socket means the client will not
    // receive the configuration result.
    if (!sock_cfg || !current_control_socket_ || sock_changed) {
        // Close the existing socket.
        if (current_control_socket_) {
            isc::config::CommandMgr::instance().closeCommandSocket();
            current_control_socket_.reset();
        }

        // Open the new socket.
        if (sock_cfg) {
            isc::config::CommandMgr::instance().openCommandSocket(sock_cfg);
        }
    }

    // Commit the new socket configuration.
    current_control_socket_ = sock_cfg;
}

} // namespace isc::d2
} // namespace isc
