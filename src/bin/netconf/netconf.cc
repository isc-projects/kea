// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file netconf.cc
/// Contains the Netconf agent methods.

#include <config.h>

#include <netconf/netconf.h>
#include <netconf/netconf_controller.h>
#include <netconf/netconf_log.h>
#include <cc/command_interpreter.h>
#include <yang/translator_config.h>
#include <boost/algorithm/string.hpp>
#include <sstream>

using namespace std;
using namespace isc::config;
using namespace isc::data;
using namespace isc::netconf;
using namespace isc::yang;

namespace {

/// @brief Subscription callback.
class NetconfAgentCallback : public Callback {
public:
    /// @brief Constructor.
    ///
    /// @param service_pair The service name and configuration pair.
    NetconfAgentCallback(const CfgServersMapPair& service_pair)
        : service_pair_(service_pair) {
    }

    /// @brief Server name and configuration pair.
    CfgServersMapPair service_pair_;

    /// @brief Module configuration change callback.
    ///
    /// This callback is called by sysrepo when there is a change to
    /// module configuration.
    ///
    /// @param sess The running datastore session.
    /// @param module_name The module name.
    /// @param event The event.
    /// @param private_ctx The private context.
    /// @return the sysrepo return code.
    int module_change(S_Session sess,
                      const char* /*module_name*/,
                      sr_notif_event_t event,
                      void* /*private_ctx*/) {
        if (NetconfProcess::shut_down) {
            return (SR_ERR_DISCONNECT);
        }
        ostringstream event_type;
        switch (event) {
        case SR_EV_VERIFY:
            event_type << "VERIFY";
            break;
        case SR_EV_APPLY:
            event_type << "APPLY";
            break;
        case SR_EV_ABORT:
            event_type << "ABORT";
            break;
        case SR_EV_ENABLED:
            event_type << "ENABLED";
            break;
        default:
            event_type << "UNKNOWN (" << event << ")";
            break;
        }
        LOG_INFO(netconf_logger, NETCONF_CONFIG_CHANGE_EVENT)
            .arg(event_type.str());
        string xpath = "/" + service_pair_.second->getModel() + ":";
        NetconfAgent::logChanges(sess, xpath + "config");
        if (NetconfProcess::shut_down) {
            return (SR_ERR_DISCONNECT);
        }
        NetconfAgent::logChanges(sess, xpath + "logging");
        if (NetconfProcess::shut_down) {
            return (SR_ERR_DISCONNECT);
        }
        switch (event) {
        case SR_EV_VERIFY:
            return (NetconfAgent::validate(sess, service_pair_));
        case SR_EV_APPLY:
            return (NetconfAgent::update(sess, service_pair_));
        default:
            return (SR_ERR_OK);
        }
    }
};

} // end of anonymous namespace

namespace isc {
namespace netconf {

NetconfAgent::NetconfAgent() {
}

NetconfAgent::~NetconfAgent() {
    clear();
}

void
NetconfAgent::init(NetconfCfgMgrPtr cfg_mgr) {
    if (NetconfProcess::shut_down || !cfg_mgr) {
        return;
    }
    const CfgServersMapPtr& servers =
        cfg_mgr->getNetconfConfig()->getCfgServersMap();
    for (auto pair : *servers) {
        if (NetconfProcess::shut_down) {
            return;
        }

        // Retrieve configuration from existing running DHCP daemons.
        keaConfig(pair);
        if (NetconfProcess::shut_down) {
            return;
        }
    }
    if (NetconfProcess::shut_down) {
        return;
    }

    // Initialize sysrepo interface.
    initSysrepo();
    if (NetconfProcess::shut_down) {
        return;
    }

    for (auto pair : *servers) {
        if (NetconfProcess::shut_down) {
            return;
        }
        yangConfig(pair);
        if (NetconfProcess::shut_down) {
            return;
        }
        subscribeConfig(pair);
        if (NetconfProcess::shut_down) {
            return;
        }
    }
}

void
NetconfAgent::clear() {
    // Should be already set to true but in case...
    NetconfProcess::shut_down = true;
    for (auto subs : subscriptions_) {
        subs.second.reset();
    }
    subscriptions_.clear();
    running_sess_.reset();
    startup_sess_.reset();
    conn_.reset();
}

void
NetconfAgent::keaConfig(const CfgServersMapPair& service_pair) {
    if (!service_pair.second->getBootUpdate()) {
        return;
    }
    CfgControlSocketPtr ctrl_sock = service_pair.second->getCfgControlSocket();
    if (!ctrl_sock) {
        return;
    }
    ControlSocketBasePtr comm;
    try {
        comm = createControlSocket(ctrl_sock);
    } catch (const std::exception& ex) {
        ostringstream msg;
        msg << "createControlSocket failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_GET_CONFIG_FAILED)
            .arg(service_pair.first)
            .arg(msg.str());
        return;
    }
    ConstElementPtr answer;
    int rcode;
    ConstElementPtr config;
    LOG_DEBUG(netconf_logger, NETCONF_DBG_TRACE, NETCONF_GET_CONFIG)
        .arg(service_pair.first);
    try {
        answer = comm->configGet(service_pair.first);
        config = parseAnswer(rcode, answer);
    } catch (const std::exception& ex) {
        ostringstream msg;
        msg << "config-get command failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_GET_CONFIG_FAILED)
            .arg(service_pair.first)
            .arg(msg.str());
        return;
    }
    if (NetconfProcess::shut_down) {
        return;
    }
    if (rcode != CONTROL_RESULT_SUCCESS) {
        ostringstream msg;
        msg << "config-get command returned " << answerToText(answer);
        LOG_ERROR(netconf_logger, NETCONF_GET_CONFIG_FAILED)
            .arg(service_pair.first)
            .arg(msg.str());
        return;
    }
    if (!config) {
        LOG_ERROR(netconf_logger, NETCONF_GET_CONFIG_FAILED)
            .arg(service_pair.first)
            .arg("config-get command returned an empty configuration");
        return;
    }
    LOG_INFO(netconf_logger, NETCONF_BOOT_UPDATE_COMPLETE)
        .arg(service_pair.first);

    LOG_DEBUG(netconf_logger, NETCONF_DBG_TRACE_DETAIL_DATA,
              NETCONF_GET_CONFIG_CONFIG)
        .arg(service_pair.first)
        .arg(prettyPrint(config));
}

void
NetconfAgent::initSysrepo() {
    try {
        conn_.reset(new Connection(NetconfController::netconf_app_name_,
                                   SR_CONN_DAEMON_REQUIRED));
    } catch (const std::exception& ex) {
        isc_throw(Unexpected, "Can't connect to sysrepo: " << ex.what());
    }

    try {
        startup_sess_.reset(new Session(conn_, SR_DS_STARTUP));
        running_sess_.reset(new Session(conn_, SR_DS_RUNNING));
    } catch (const std::exception& ex) {
        isc_throw(Unexpected,  "Can't establish a sysrepo session: "
                  << ex.what());
    }
}

void
NetconfAgent::yangConfig(const CfgServersMapPair& service_pair) {
    // If we're shutting down, or the boot-update flag is not set or the model
    // associated with it is not specified.
    if (NetconfProcess::shut_down ||
        !service_pair.second->getBootUpdate() ||
        service_pair.second->getModel().empty()) {
        return;
    }

    // First we need a way to reach the actual servers.
    CfgControlSocketPtr ctrl_sock = service_pair.second->getCfgControlSocket();
    if (!ctrl_sock) {
        return;
    }

    LOG_DEBUG(netconf_logger, NETCONF_DBG_TRACE, NETCONF_SET_CONFIG)
        .arg(service_pair.first);
    ConstElementPtr config;
    try {
        // Retrieve configuration from Sysrepo.
        TranslatorConfig tc(startup_sess_, service_pair.second->getModel());
        config = tc.getConfig();
        if (!config) {
            ostringstream msg;
            msg << "YANG configuration for "
                << service_pair.second->getModel()
                << " is empty";
            LOG_ERROR(netconf_logger, NETCONF_SET_CONFIG_FAILED)
                .arg(service_pair.first)
                .arg(msg.str());
            return;
        } else {
            LOG_DEBUG(netconf_logger, NETCONF_DBG_TRACE_DETAIL_DATA,
                      NETCONF_SET_CONFIG_CONFIG)
                .arg(service_pair.first)
                .arg(prettyPrint(config));
        }
    } catch (const std::exception& ex) {
        ostringstream msg;
        msg << "get YANG configuration for " << service_pair.first
            << " failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_SET_CONFIG_FAILED)
            .arg(service_pair.first)
            .arg(msg.str());
        return;
    }
    if (NetconfProcess::shut_down) {
        return;
    }
    ControlSocketBasePtr comm;
    try {
        comm = createControlSocket(ctrl_sock);
    } catch (const std::exception& ex) {
        ostringstream msg;
        msg << "control socket creation failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_SET_CONFIG_FAILED)
            .arg(service_pair.first)
            .arg(msg.str());
        return;
    }
    if (NetconfProcess::shut_down) {
        return;
    }
    ConstElementPtr answer;
    int rcode;
    try {
        answer = comm->configSet(config, service_pair.first);
        parseAnswer(rcode, answer);
    } catch (const std::exception& ex) {
        ostringstream msg;
        msg << "config-set command failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_SET_CONFIG_FAILED)
            .arg(service_pair.first)
            .arg(msg.str());
        return;
    }
    if (rcode != CONTROL_RESULT_SUCCESS) {
        ostringstream msg;
        msg << "config-set command returned " << answerToText(answer);
        LOG_ERROR(netconf_logger, NETCONF_SET_CONFIG_FAILED)
            .arg(service_pair.first)
            .arg(msg.str());
    }
}

void
NetconfAgent::subscribeConfig(const CfgServersMapPair& service_pair) {
    if (NetconfProcess::shut_down ||
        !service_pair.second->getSubscribeChanges() ||
        service_pair.second->getModel().empty()) {
        return;
    }
    LOG_INFO(netconf_logger, NETCONF_SUBSCRIBE_CONFIG)
        .arg(service_pair.first)
        .arg(service_pair.second->getModel());
    S_Subscribe subs(new Subscribe(running_sess_));
    S_Callback cb(new NetconfAgentCallback(service_pair));
    try {
        sr_subscr_options_t options = SR_SUBSCR_DEFAULT;
        if (!service_pair.second->getValidateChanges()) {
            options |= SR_SUBSCR_APPLY_ONLY;
        }
        // Note the API stores the module name so do not put it
        // in a short lifetime variable!
        subs->module_change_subscribe(service_pair.second->getModel().c_str(),
                                      cb, 0, 0, options);
    } catch (const std::exception& ex) {
        ostringstream msg;
        msg << "module change subscribe failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_SUBSCRIBE_CONFIG_FAILED)
            .arg(service_pair.first)
            .arg(service_pair.second->getModel())
            .arg(msg.str());
        subs.reset();
        return;
    }
    subscriptions_.insert(make_pair(service_pair.first, subs));
}

int
NetconfAgent::validate(S_Session sess, const CfgServersMapPair& service_pair) {
    if (NetconfProcess::shut_down ||
        !service_pair.second->getSubscribeChanges() ||
        !service_pair.second->getValidateChanges()) {
        return (SR_ERR_OK);
    }
    CfgControlSocketPtr ctrl_sock = service_pair.second->getCfgControlSocket();
    if (!ctrl_sock) {
        return (SR_ERR_OK);
    }
    LOG_DEBUG(netconf_logger, NETCONF_DBG_TRACE,
              NETCONF_VALIDATE_CONFIG_STARTED)
        .arg(service_pair.first);
    ConstElementPtr config;
    try {
        TranslatorConfig tc(sess, service_pair.second->getModel());
        config = tc.getConfig();
        if (!config) {
            ostringstream msg;
            msg << "YANG configuration for "
                << service_pair.second->getModel()
                << " is empty";
            LOG_ERROR(netconf_logger, NETCONF_VALIDATE_CONFIG_FAILED)
                .arg(service_pair.first)
                .arg(msg.str());
            return (SR_ERR_DISCONNECT);
        } else {
            LOG_DEBUG(netconf_logger, NETCONF_DBG_TRACE_DETAIL_DATA,
                      NETCONF_VALIDATE_CONFIG)
                .arg(service_pair.first)
                .arg(prettyPrint(config));
        }
    } catch (const std::exception& ex) {
        ostringstream msg;
        msg << "get YANG configuration for " << service_pair.first
            << " failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_VALIDATE_CONFIG_FAILED)
            .arg(service_pair.first)
            .arg(msg.str());
        return (SR_ERR_VALIDATION_FAILED);;
    }
    if (NetconfProcess::shut_down) {
        return (SR_ERR_DISCONNECT);
    }
    ControlSocketBasePtr comm;
    try {
        comm = createControlSocket(ctrl_sock);
    } catch (const std::exception& ex) {
        ostringstream msg;
        msg << "createControlSocket failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_VALIDATE_CONFIG_FAILED)
            .arg(service_pair.first)
            .arg(msg.str());
        return (SR_ERR_OK);
    }
    ConstElementPtr answer;
    int rcode;
    try {
        answer = comm->configTest(config, service_pair.first);
        parseAnswer(rcode, answer);
    } catch (const std::exception& ex) {
        stringstream msg;
        msg << "configTest failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_VALIDATE_CONFIG_FAILED)
            .arg(service_pair.first)
            .arg(msg.str());
        return (SR_ERR_VALIDATION_FAILED);
    }
    if (rcode != CONTROL_RESULT_SUCCESS) {
        stringstream msg;
        msg << "configTest returned " << answerToText(answer);
        LOG_ERROR(netconf_logger, NETCONF_VALIDATE_CONFIG_REJECTED)
            .arg(service_pair.first)
            .arg(msg.str());
        return (SR_ERR_VALIDATION_FAILED);
    }
    return (SR_ERR_OK);
}

int
NetconfAgent::update(S_Session sess, const CfgServersMapPair& service_pair) {
    // Check if we should and can process this update.
    if (NetconfProcess::shut_down ||
        !service_pair.second->getSubscribeChanges()) {
        return (SR_ERR_OK);
    }
    CfgControlSocketPtr ctrl_sock = service_pair.second->getCfgControlSocket();
    if (!ctrl_sock) {
        return (SR_ERR_OK);
    }

    // All looks good, let's get started. Print an info that we're about
    // to update the configuration.
    LOG_DEBUG(netconf_logger, NETCONF_DBG_TRACE, NETCONF_UPDATE_CONFIG_STARTED)
        .arg(service_pair.first);

    // Retrieve the configuration from SYSREPO first.
    ConstElementPtr config;
    try {
        TranslatorConfig tc(sess, service_pair.second->getModel());
        config = tc.getConfig();
        if (!config) {
            ostringstream msg;
            msg << "YANG configuration for "
                << service_pair.second->getModel()
                << " is empty";
            LOG_ERROR(netconf_logger, NETCONF_UPDATE_CONFIG_FAILED)
                .arg(service_pair.first)
                .arg(msg.str());
            return (SR_ERR_VALIDATION_FAILED);
        } else {
            LOG_DEBUG(netconf_logger, NETCONF_DBG_TRACE_DETAIL_DATA,
                      NETCONF_UPDATE_CONFIG)
                .arg(service_pair.first)
                .arg(prettyPrint(config));
        }
    } catch (const std::exception& ex) {
        ostringstream msg;
        msg << "get YANG configuration for " << service_pair.first
            << " failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_UPDATE_CONFIG_FAILED)
            .arg(service_pair.first)
            .arg(msg.str());
        return (SR_ERR_VALIDATION_FAILED);
    }
    if (NetconfProcess::shut_down) {
        return (SR_ERR_OK);
    }

    // Ok, now open the control socket. We need this to send the config to
    // the server.
    ControlSocketBasePtr comm;
    try {
        comm = createControlSocket(ctrl_sock);
    } catch (const std::exception& ex) {
        ostringstream msg;
        msg << "createControlSocket failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_UPDATE_CONFIG_FAILED)
            .arg(service_pair.first)
            .arg(msg.str());
        return (SR_ERR_OK);
    }

    // Now apply the config using config-set command.
    ConstElementPtr answer;
    int rcode;
    try {
        answer = comm->configSet(config, service_pair.first);
        parseAnswer(rcode, answer);
    } catch (const std::exception& ex) {
        stringstream msg;
        msg << "configSet failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_UPDATE_CONFIG_FAILED)
            .arg(service_pair.first)
            .arg(msg.str());
        return (SR_ERR_VALIDATION_FAILED);
    }

    // rcode == CONTROL_RESULT_SUCCESS, unless the docs say otherwise :).
    if (rcode != CONTROL_RESULT_SUCCESS) {
        stringstream msg;
        msg << "configSet returned " << answerToText(answer);
        LOG_ERROR(netconf_logger, NETCONF_UPDATE_CONFIG_FAILED)
            .arg(service_pair.first)
            .arg(msg.str());
        return (SR_ERR_VALIDATION_FAILED);
    }
    return (SR_ERR_OK);
}

void
NetconfAgent::logChanges(S_Session sess, const string& model) {
    if (NetconfProcess::shut_down) {
        return;
    }
    S_Iter_Change iter = sess->get_changes_iter(model.c_str());
    if (!iter) {
        LOG_WARN(netconf_logger, NETCONF_LOG_CHANGE_FAIL)
            .arg("no iterator");
        return;
    }
    for (;;) {
        if (NetconfProcess::shut_down) {
            return;
        }
        S_Change change;
        ostringstream msg;
        try {
            change = sess->get_change_next(iter);
        } catch (const sysrepo_exception& ex) {
            msg << "get change iterator next failed: " << ex.what();
            LOG_WARN(netconf_logger, NETCONF_LOG_CHANGE_FAIL)
                .arg(msg.str());
            return;
        }
        if (!change) {
            // End of changes, not an error.
            return;
        }
        if (NetconfProcess::shut_down) {
            return;
        }
        S_Val new_val = change->new_val();
        S_Val old_val = change->old_val();
        string report;
        switch (change->oper()) {
        case SR_OP_CREATED:
            if (!new_val) {
                LOG_WARN(netconf_logger, NETCONF_LOG_CHANGE_FAIL)
                    .arg("created but without a new value");
                break;
            }
            msg << "created: " << new_val->to_string();
            report = msg.str();
            boost::erase_all(report, "\n");
            LOG_DEBUG(netconf_logger, NETCONF_DBG_TRACE_DETAIL_DATA,
                      NETCONF_CONFIG_CHANGED_DETAIL)
                .arg(report);
            break;
        case SR_OP_MODIFIED:
            if (!old_val || !new_val) {
                LOG_WARN(netconf_logger, NETCONF_LOG_CHANGE_FAIL)
                    .arg("modified but without an old or new value");
                break;
            }
            msg << "modified: " << old_val->to_string()
                << " => " << new_val->to_string();
            report = msg.str();
            boost::erase_all(report, "\n");
            LOG_DEBUG(netconf_logger, NETCONF_DBG_TRACE_DETAIL_DATA,
                      NETCONF_CONFIG_CHANGED_DETAIL)
                .arg(report);
            break;
        case SR_OP_DELETED:
            if (!old_val) {
                LOG_WARN(netconf_logger, NETCONF_LOG_CHANGE_FAIL)
                    .arg("deleted but without an old value");
                break;
            }
            msg << "deleted: " << old_val->to_string();
            report = msg.str();
            boost::erase_all(report, "\n");
            LOG_DEBUG(netconf_logger, NETCONF_DBG_TRACE_DETAIL_DATA,
                      NETCONF_CONFIG_CHANGED_DETAIL)
                .arg(report);
            break;
        case SR_OP_MOVED:
            if (!new_val) {
                LOG_WARN(netconf_logger, NETCONF_LOG_CHANGE_FAIL)
                    .arg("moved but without a new value");
                break;
            }
            msg << "moved: " << new_val->xpath();
            if (!old_val) {
                msg << " first";
            } else {
                msg << " after " << old_val->xpath();
            }
            report = msg.str();
            boost::erase_all(report, "\n");
            LOG_DEBUG(netconf_logger, NETCONF_DBG_TRACE_DETAIL_DATA,
                      NETCONF_CONFIG_CHANGED_DETAIL)
                .arg(report);
            break;
        default:
            msg << "unknown operation (" << change->oper() << ")";
            LOG_WARN(netconf_logger, NETCONF_LOG_CHANGE_FAIL)
                .arg(msg.str());
        }
    }
}

} // namespace netconf
} // namespace isc
