// Copyright (C) 2013-2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <cc/command_interpreter.h>
#include <d2/d2_log.h>
#include <d2/d2_cfg_mgr.h>
#include <d2/d2_process.h>

#include <asio.hpp>

namespace isc {
namespace d2 {

// Setting to 80% for now. This is an arbitrary choice and should probably
// be configurable.
const unsigned int D2Process::QUEUE_RESTART_PERCENT =  80;

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
    update_mgr_.reset(new D2UpdateMgr(queue_mgr_,  tmp,  getIoService()));
};

void
D2Process::init() {
};

void
D2Process::run() {
    LOG_INFO(dctl_logger, DHCP_DDNS_STARTED).arg(VERSION);
    // Loop forever until we are allowed to shutdown.
    while (!canShutdown()) {
        try {
            // Check on the state of the request queue. Take any
            // actions necessary regarding it.
            checkQueueStatus();

            // Give update manager a time slice to queue new jobs and
            // process finished ones.
            update_mgr_->sweep();

            // Wait on IO event(s)  - block until one or more of the following
            // has occurred:
            //   a. NCR message has been received
            //   b. Transaction IO has completed
            //   c. Interval timer expired
            //   d. Something stopped IO service (runIO returns 0)
            if (runIO() == 0) {
                // Pretty sure this amounts to an unexpected stop and we
                // should bail out now.  Normal shutdowns do not utilize
                // stopping the IOService.
                isc_throw(DProcessBaseError,
                          "Primary IO service stopped unexpectedly");
            }
        } catch (const std::exception& ex) {
            LOG_FATAL(dctl_logger, DHCP_DDNS_FAILED).arg(ex.what());
            isc_throw (DProcessBaseError,
                       "Process run method failed: " << ex.what());
        }
    }

    // @todo - if queue isn't empty, we may need to persist its contents
    // this might be the place to do it, once there is a persistence mgr.
    // This may also be better in checkQueueStatus.

    LOG_DEBUG(dctl_logger, DBGLVL_START_SHUT, DHCP_DDNS_RUN_EXIT);

};

size_t
D2Process::runIO() {
    // We want to block until at least one handler is called.  We'll use
    // asio::io_service directly for two reasons. First off
    // asiolink::IOService::run_one is a void and asio::io_service::stopped
    // is not present in older versions of boost.  We need to know if any
    // handlers ran or if the io_service was stopped.  That latter represents
    // some form of error and the application cannot proceed with a stopped
    // service.  Secondly, asiolink::IOService does not provide the poll
    // method.  This is a handy method which runs all ready handlers without
    // blocking.
    asiolink::IOServicePtr& io = getIoService();
    asio::io_service& asio_io_service  = io->get_io_service();

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
            LOG_DEBUG(dctl_logger, DBGLVL_START_SHUT,
                     DHCP_DDNS_CLEARED_FOR_SHUTDOWN)
                     .arg(getShutdownTypeStr(shutdown_type_));
        }
    }

    return (all_clear);
}

isc::data::ConstElementPtr
D2Process::shutdown(isc::data::ConstElementPtr args) {
    LOG_DEBUG(dctl_logger, DBGLVL_START_SHUT, DHCP_DDNS_SHUTDOWN_COMMAND)
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
                return (isc::config::createAnswer(1, "Invalid Shutdown type: "
                                                  + type_str));
            }
        }
    }

    // Set the base class's shutdown flag.
    setShutdownFlag(true);
    return (isc::config::createAnswer(0, "Shutdown initiated, type is: "
                                      + type_str));
}

isc::data::ConstElementPtr
D2Process::configure(isc::data::ConstElementPtr config_set) {
    LOG_DEBUG(dctl_logger, DBGLVL_TRACE_BASIC,
              DHCP_DDNS_CONFIGURE).arg(config_set->str());

    int rcode = 0;
    isc::data::ConstElementPtr comment;
    isc::data::ConstElementPtr answer = getCfgMgr()->parseConfig(config_set);;
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
    // (@todo NOTE This could be turned into a bitmask of flags if we find other
    // things that need reconfiguration.  It might also be useful if we
    // did some analysis to decide what if anything we need to do.)
    reconf_queue_flag_ = true;

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
            // If we need to reconfigure the queue manager or we have been
            // told to shutdown, then stop listening first.  Stopping entails
            // canceling active listening which may generate an IO event, so
            // instigate the stop and get out.
            try {
                LOG_DEBUG(dctl_logger, DBGLVL_START_SHUT,
                          DHCP_DDNS_QUEUE_MGR_STOPPING)
                         .arg(reconf_queue_flag_ ? "reconfiguration"
                                                 : "shutdown");
                queue_mgr_->stopListening();
            } catch (const isc::Exception& ex) {
                // It is very unlikey that we would experience an error
                // here, but theoretically possible.
                LOG_ERROR(dctl_logger, DHCP_DDNS_QUEUE_MGR_STOP_ERROR)
                          .arg(ex.what());
            }
        }
        break;

    case D2QueueMgr::STOPPED_QUEUE_FULL: {
            // Resume receiving once the queue has decreased by twenty
            // percent.  This is an arbitrary choice. @todo this value should
            // probably be configurable.
            size_t threshold = (((queue_mgr_->getMaxQueueSize()
                                * QUEUE_RESTART_PERCENT)) / 100);
            if (queue_mgr_->getQueueSize() <= threshold) {
                LOG_INFO (dctl_logger, DHCP_DDNS_QUEUE_MGR_RESUMING)
                          .arg(threshold).arg(queue_mgr_->getMaxQueueSize());
                try {
                    queue_mgr_->startListening();
                } catch (const isc::Exception& ex) {
                    LOG_ERROR(dctl_logger, DHCP_DDNS_QUEUE_MGR_RESUME_ERROR)
                              .arg(ex.what());
                }
            }

        break;
        }

    case D2QueueMgr::STOPPED_RECV_ERROR:
        // If the receive error is not due to some fallout from shutting
        // down then we will attempt to recover by reconfiguring the listener.
        // This will close and destruct the current listener and make a new
        // one with new resources.
        // @todo This may need a safety valve such as retry count or a timer
        // to keep from endlessly retrying over and over, with little time
        // in between.
        if (!shouldShutdown()) {
            LOG_INFO (dctl_logger, DHCP_DDNS_QUEUE_MGR_RECOVERING);
            reconfigureQueueMgr();
        }
        break;

    case D2QueueMgr::STOPPING:
        // We are waiting for IO to cancel, so this is a NOP.
        // @todo Possible timer for self-defense?  We could conceivably
        // get into a condition where we never get the event, which would
        // leave us stuck in stopping.  This is hugely unlikely but possible?
        break;

    default:
        // If the reconfigure flag is set, then we are in a state now where
        // we can do the reconfigure. In other words, we aren't RUNNING or
        // STOPPING.
        if (reconf_queue_flag_) {
            LOG_DEBUG(dctl_logger, DBGLVL_TRACE_BASIC,
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
    // @todo This method assumes only 1 type of listener.  This will change
    // to support at least a TCP version, possibly some form of RDBMS listener
    // as well.
    reconf_queue_flag_ = false;
    try {
        // Wipe out the current listener.
        queue_mgr_->removeListener();

        // Get the configuration parameters that affect Queue Manager.
        const D2ParamsPtr& d2_params = getD2CfgMgr()->getD2Params();

        // Warn the user if the server address is not the loopback.
        /// @todo Remove this once we provide a secure mechanism.
        std::string ip_address =  d2_params->getIpAddress().toText();
        if (ip_address != "127.0.0.1" && ip_address != "::1") {
            LOG_WARN(dctl_logger, DHCP_DDNS_NOT_ON_LOOPBACK).arg(ip_address);
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
        // blocking call that executes quickly.  @todo Should that change then
        // we will have to expand the state model to accommodate this.
        queue_mgr_->startListening();
    } catch (const isc::Exception& ex) {
        // Queue manager failed to initialize and therefore not listening.
        // This is most likely due to an unavailable IP address or port,
        // which is a configuration issue.
        LOG_ERROR(dctl_logger, DHCP_DDNS_QUEUE_MGR_START_ERROR).arg(ex.what());
    }
}

isc::data::ConstElementPtr
D2Process::command(const std::string& command,
                   isc::data::ConstElementPtr args) {
    // @todo This is the initial implementation.  If and when D2 is extended
    // to support its own commands, this implementation must change. Otherwise
    // it should reject all commands as it does now.
    LOG_DEBUG(dctl_logger, DBGLVL_TRACE_BASIC, DHCP_DDNS_COMMAND)
        .arg(command).arg(args ? args->str() : "(no args)");

    return (isc::config::createAnswer(COMMAND_INVALID, "Unrecognized command: "
                                      + command));
}

D2Process::~D2Process() {
};

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

}; // namespace isc::d2
}; // namespace isc
