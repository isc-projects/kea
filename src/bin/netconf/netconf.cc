// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
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
#include <yang/yang_revisions.h>

#include <boost/algorithm/string.hpp>

#include <sstream>

using namespace std;
using namespace isc::config;
using namespace isc::data;
using namespace isc::netconf;
using namespace isc::yang;
using namespace sysrepo;

using libyang::S_Context;
using libyang::S_Module;

namespace {

/// @brief Module change subscription callback.
class NetconfAgentCallback {
public:
    /// @brief Constructor.
    ///
    /// @param service_pair The service name and configuration pair.
    NetconfAgentCallback(const CfgServersMapPair& service_pair)
        : service_pair_(service_pair) {
    }

    /// @brief Server name and configuration pair.
    CfgServersMapPair const service_pair_;

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
    sr_error_t module_change(S_Session sess,
                             const char* module_name,
                             const char* /* xpath */,
                             sr_event_t event,
                             void* /* private_ctx */) {
        ostringstream event_type;
        switch (event) {
        case SR_EV_UPDATE:
            // This could potentially be a hook point for mid-flight
            // configuration changes.
            event_type << "SR_EV_UPDATE";
            break;
        case SR_EV_CHANGE:
            event_type << "SR_EV_CHANGE";
            break;
        case SR_EV_DONE:
            event_type << "SR_EV_DONE";
            break;
        case SR_EV_ABORT:
            event_type << "SR_EV_ABORT";
            break;
        case SR_EV_ENABLED:
            event_type << "SR_EV_ENABLED";
            break;
        case SR_EV_RPC:
            event_type << "SR_EV_RPC";
            break;
        default:
            event_type << "UNKNOWN (" << event << ")";
            break;
        }
        LOG_INFO(netconf_logger, NETCONF_CONFIG_CHANGE_EVENT)
            .arg(event_type.str());
        NetconfAgent::logChanges(sess, module_name);
        switch (event) {
        case SR_EV_CHANGE:
            return (NetconfAgent::change(sess, service_pair_));
        case SR_EV_DONE:
            return (NetconfAgent::done(sess, service_pair_));
        default:
            return (SR_ERR_OK);
        }
    }

    void event_notif(sysrepo::S_Session /* session */,
                     sr_ev_notif_type_t const notification_type,
                     char const* /* path */,
                     sysrepo::S_Vals const vals,
                     time_t /* timestamp */,
                     void* /* private_data */) {
        string n;
        switch (notification_type) {
        case SR_EV_NOTIF_REALTIME:
            n = "SR_EV_NOTIF_REALTIME";
            break;
        case SR_EV_NOTIF_REPLAY:
            n = "SR_EV_NOTIF_REPLAY";
            break;
        case SR_EV_NOTIF_REPLAY_COMPLETE:
            n = "SR_EV_NOTIF_REPLAY_COMPLETE";
            break;
        case SR_EV_NOTIF_STOP:
            n = "SR_EV_NOTIF_STOP";
            break;
        case SR_EV_NOTIF_SUSPENDED:
            n = "SR_EV_NOTIF_SUSPENDED";
            break;
        case SR_EV_NOTIF_RESUMED:
            n = "SR_EV_NOTIF_RESUMED";
            break;
        }

        stringstream s;
        for (size_t i(0); i < vals->val_cnt(); ++i) {
            if (i != 0) {
                s << ", ";
            }
            s << vals->val(i)->to_string();
        }

        LOG_INFO(netconf_logger, NETCONF_NOTIFICATION_RECEIVED)
            .arg(n)
            .arg(service_pair_.first)
            .arg(s.str());
    }
};

} // end of anonymous namespace

namespace isc {
namespace netconf {

NetconfAgent::~NetconfAgent() {
    clear();
}

void
NetconfAgent::init(NetconfCfgMgrPtr cfg_mgr) {
    // Check for a configuration manager.
    if (!cfg_mgr) {
        isc_throw(Unexpected, "missing configuration manager");
        return;
    }

    // Retrieve configuration from existing running DHCP daemons.
    const CfgServersMapPtr& servers =
        cfg_mgr->getNetconfConfig()->getCfgServersMap();
    for (auto const& pair : *servers) {
        keaConfig(pair);
    }

    // Initialize sysrepo.
    initSysrepo();

    // Check modules / revisions.
    checkModules(servers);

    for (auto const& pair : *servers) {
        yangConfig(pair);
        subscribeConfig(pair);
        subscribeToNotifications(pair);
    }
}

void
NetconfAgent::clear() {
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
    // If the boot-update flag is not set.
    if (!service_pair.second->getBootUpdate()) {
        return;
    }
    CfgControlSocketPtr ctrl_sock = service_pair.second->getCfgControlSocket();
    if (!ctrl_sock) {
        return;
    }
    ControlSocketBasePtr comm;
    try {
        comm = controlSocketFactory(ctrl_sock);
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
    LOG_INFO(netconf_logger, NETCONF_GET_CONFIG_STARTED)
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
    LOG_DEBUG(netconf_logger, NETCONF_DBG_TRACE_DETAIL_DATA,
              NETCONF_GET_CONFIG)
        .arg(service_pair.first)
        .arg(prettyPrint(config));
}

void
NetconfAgent::initSysrepo() {
    try {
        conn_ = make_shared<Connection>();
    } catch (const std::exception& ex) {
        isc_throw(Unexpected, "Can't connect to sysrepo: " << ex.what());
    }

    try {
        startup_sess_.reset(new Session(conn_, SR_DS_STARTUP));
        running_sess_.reset(new Session(conn_, SR_DS_RUNNING));
    } catch (const std::exception& ex) {
        isc_throw(Unexpected, "Can't establish a sysrepo session: "
                  << ex.what());
    }

    // Retrieve names and revisions of installed modules from sysrepo.
    getModules();
}

void NetconfAgent::getModules() {
    vector<S_Module> modules;
    try {
        S_Context context(running_sess_->get_context());
        modules = context->get_module_iter();
    } catch (const sysrepo_exception& ex) {
        isc_throw(Unexpected, "can't retrieve available modules: " << ex.what());
    }

    for (S_Module const& module : modules) {
        if (!module->name()) {
            isc_throw(Unexpected, "could not retrieve module name");
        }
        string const name(module->name());
        if (!module->rev() || !module->rev()->date()) {
            isc_throw(Unexpected,
                      "could not retrieve module revision for module " << name);
        }
        string const revision(module->rev()->date());
        modules_.emplace(name, revision);
    }
}

bool
NetconfAgent::checkModule(const string& module_name) const {
    auto module = modules_.find(module_name);
    if (module == modules_.end()) {
        LOG_ERROR(netconf_logger, NETCONF_MODULE_MISSING_ERR)
            .arg(module_name);
        return (false);
    }
    auto modrev = YANG_REVISIONS.find(module_name);
    if (modrev == YANG_REVISIONS.end()) {
        // Can't check revision?!
        // It can happen only with a module which is not in
        // YANG_REVISIONS but installed so likely on purpose.
        return (true);
    }
    if (modrev->second != module->second) {
        LOG_ERROR(netconf_logger, NETCONF_MODULE_REVISION_ERR)
            .arg(module_name)
            .arg(modrev->second)
            .arg(module->second);
        return (false);
    }
    return (true);
}

void
NetconfAgent::checkModules(CfgServersMapPtr const& servers /* = {} */) const {
    bool faulty_model(false);
    if (servers) {
        for (auto pair : *servers) {
            if (!checkModule(pair.second->getModel())) {
                faulty_model = true;
            }
        }
    }

    if (faulty_model) {
        isc_throw(Unexpected, "YANG module is missing or its revision is not "
                              "supported. Check logs for details.");
    }

    for (auto modrev : YANG_REVISIONS) {
        auto module = modules_.find(modrev.first);
        if (module == modules_.end()) {
            LOG_WARN(netconf_logger, NETCONF_MODULE_MISSING_WARN)
                .arg(modrev.first);
            continue;
        }
        if (modrev.second != module->second) {
            LOG_WARN(netconf_logger, NETCONF_MODULE_REVISION_WARN)
                .arg(modrev.first)
                .arg(modrev.second)
                .arg(module->second);
        }
    }
}

void
NetconfAgent::yangConfig(const CfgServersMapPair& service_pair) {
    // If we're shutting down, or the boot-update flag is not set or the model
    // associated with it is not specified.
    if (!service_pair.second->getBootUpdate() ||
        service_pair.second->getModel().empty()) {
        return;
    }

    // First we need a way to reach the actual servers.
    CfgControlSocketPtr ctrl_sock = service_pair.second->getCfgControlSocket();
    if (!ctrl_sock) {
        return;
    }

    LOG_INFO(netconf_logger, NETCONF_SET_CONFIG_STARTED)
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
                      NETCONF_SET_CONFIG)
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
    ControlSocketBasePtr comm;
    try {
        comm = controlSocketFactory(ctrl_sock);
    } catch (const std::exception& ex) {
        ostringstream msg;
        msg << "control socket creation failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_SET_CONFIG_FAILED)
            .arg(service_pair.first)
            .arg(msg.str());
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
        return;
    }
    LOG_INFO(netconf_logger, NETCONF_BOOT_UPDATE_COMPLETED)
        .arg(service_pair.first);
}

void
NetconfAgent::subscribeConfig(const CfgServersMapPair& service_pair) {
    std::string const& model(service_pair.second->getModel());

    // If we're shutting down, or the subscribe-changes flag is not set or
    // the model associated with it is not specified.
    if (!service_pair.second->getSubscribeChanges() ||
        model.empty()) {
        return;
    }
    LOG_INFO(netconf_logger, NETCONF_SUBSCRIBE_CONFIG)
        .arg(service_pair.first)
        .arg(model);
    S_Subscribe subs(new Subscribe(running_sess_));
    auto callback = [=](sysrepo::S_Session sess, const char* module_name,
                        const char* xpath, sr_event_t event,
                        uint32_t /* request_id */) {
        NetconfAgentCallback agent(service_pair);
        return agent.module_change(sess, module_name, xpath, event, nullptr);
    };
    try {
        sr_subscr_options_t options = SR_SUBSCR_DEFAULT;
        if (!service_pair.second->getValidateChanges()) {
            options |= SR_SUBSCR_DONE_ONLY;
        }
        // Note the API stores the module name so do not put it
        // in a short lifetime variable!
        subs->module_change_subscribe(model.c_str(), callback, nullptr, 0,
                                      options);
    } catch (const std::exception& ex) {
        ostringstream msg;
        msg << "module change subscribe failed with " << ex.what();
        msg << "change subscription for model " << model <<
            " failed with: " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_SUBSCRIBE_CONFIG_FAILED)
            .arg(service_pair.first)
            .arg(service_pair.second->getModel())
            .arg(msg.str());
        return;
    }
    subscriptions_.insert(make_pair(service_pair.first, subs));
}


void
NetconfAgent::subscribeToNotifications(const CfgServersMapPair& service_pair) {
    std::string const& model(service_pair.second->getModel());
    // If we're shutting down, or the subscribe-changes flag is not set or
    // the model associated with it is not specified.
    if (!service_pair.second->getSubscribeNotifications() ||
        model.empty()) {
        return;
    }
    LOG_INFO(netconf_logger, NETCONF_SUBSCRIBE_NOTIFICATIONS)
        .arg(service_pair.first)
        .arg(model);

    S_Subscribe subscription(std::make_shared<Subscribe>(running_sess_));
    auto callback = [=](sysrepo::S_Session session,
                        sr_ev_notif_type_t const notification_type,
                        char const* path,
                        sysrepo::S_Vals const vals,
                        time_t timestamp) {
        NetconfAgentCallback agent(service_pair);
        return agent.event_notif(session, notification_type, path, vals, timestamp, nullptr);
    };
    try {
        subscription->event_notif_subscribe(model.c_str(), callback);
    } catch (const std::exception& ex) {
        ostringstream msg;
        msg << "event notification subscription for model " << model <<
            " failed with: " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_SUBSCRIBE_NOTIFICATIONS_FAILED)
            .arg(service_pair.first)
            .arg(service_pair.second->getModel())
            .arg(msg.str());
        return;
    }
    subscriptions_.emplace(service_pair.first, subscription);
}

sr_error_t
NetconfAgent::change(S_Session sess, const CfgServersMapPair& service_pair) {
    // If we're shutting down, or the subscribe-changes or the
    // validate-changes flag is not set or the model associated with
    // it is not specified.
    if (!service_pair.second->getSubscribeChanges() ||
        !service_pair.second->getValidateChanges() ||
        service_pair.second->getModel().empty()) {
        return (SR_ERR_OK);
    }
    CfgControlSocketPtr ctrl_sock = service_pair.second->getCfgControlSocket();
    if (!ctrl_sock) {
        return (SR_ERR_OK);
    }
    LOG_INFO(netconf_logger, NETCONF_VALIDATE_CONFIG_STARTED)
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
            return (SR_ERR_OPERATION_FAILED);
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
    ControlSocketBasePtr comm;
    try {
        comm = controlSocketFactory(ctrl_sock);
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
    LOG_INFO(netconf_logger, NETCONF_VALIDATE_CONFIG_COMPLETED)
        .arg(service_pair.first);
    return (SR_ERR_OK);
}

sr_error_t
NetconfAgent::done(S_Session sess, const CfgServersMapPair& service_pair) {
    // Check if we should and can process this update.
    if (!service_pair.second->getSubscribeChanges() ||
        service_pair.second->getModel().empty()) {
        return (SR_ERR_OK);
    }
    CfgControlSocketPtr ctrl_sock = service_pair.second->getCfgControlSocket();
    if (!ctrl_sock) {
        return (SR_ERR_OK);
    }

    // All looks good, let's get started. Print an info that we're about
    // to update the configuration.
    LOG_INFO(netconf_logger, NETCONF_UPDATE_CONFIG_STARTED)
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

    // Ok, now open the control socket. We need this to send the config to
    // the server.
    ControlSocketBasePtr comm;
    try {
        comm = controlSocketFactory(ctrl_sock);
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
    LOG_INFO(netconf_logger, NETCONF_UPDATE_CONFIG_COMPLETED)
        .arg(service_pair.first);
    return (SR_ERR_OK);
}

void
NetconfAgent::logChanges(S_Session sess, const string& model) {
    ostringstream stream;
    stream << "/" << model << ":*//.";
    std::string const xpath(stream.str());
    S_Iter_Change iter = sess->get_changes_iter(xpath.c_str());
    if (!iter) {
        LOG_WARN(netconf_logger, NETCONF_LOG_CHANGE_FAIL)
            .arg("no iterator");
        return;
    }
    for (;;) {
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

void
NetconfAgent::announceShutdown() const {
    isc::process::DControllerBasePtr& controller(NetconfController::instance());
    if (controller) {
        boost::dynamic_pointer_cast<NetconfController>(controller)
            ->getNetconfProcess()
            ->setShutdownFlag(true);
    }
}

bool NetconfAgent::shouldShutdown() const {
    return boost::dynamic_pointer_cast<NetconfController>(NetconfController::instance())
        ->getNetconfProcess()
        ->shouldShutdown();
}

} // namespace netconf
} // namespace isc
