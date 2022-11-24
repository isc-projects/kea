// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file netconf.cc
/// Contains the Netconf agent methods.

#include <config.h>

#include <cc/command_interpreter.h>
#include <netconf/netconf.h>
#include <netconf/netconf_controller.h>
#include <netconf/netconf_log.h>
#include <yang/translator_config.h>
#include <yang/yang_revisions.h>

#include <sstream>
#include <vector>

using namespace std;
using namespace isc::config;
using namespace isc::data;
using namespace isc::netconf;
using namespace isc::yang;
using namespace libyang;
using namespace sysrepo;

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
    sysrepo::ErrorCode module_change(Session sess,
                                     uint32_t /* subscription_id */,
                                     string_view module_name,
                                     optional<string_view> /* sub_xpath */,
                                     Event event,
                                     uint32_t /* request_id */) {
        ostringstream event_type;
        switch (event) {
        case Event::Update:
            // This could potentially be a hook point for mid-flight
            // configuration changes.
            event_type << "Event::Update";
            break;
        case Event::Change:
            event_type << "Event::Change";
            break;
        case Event::Done:
            event_type << "Event::Done";
            break;
        case Event::Abort:
            event_type << "Event::Abort";
            break;
        case Event::Enabled:
            event_type << "Event::Enabled";
            break;
        case Event::RPC:
            event_type << "Event::RPC";
            break;
        default:
            event_type << "UNKNOWN (" << event << ")";
            break;
        }
        LOG_INFO(netconf_logger, NETCONF_CONFIG_CHANGE_EVENT)
            .arg(event_type.str());
        NetconfAgent::logChanges(sess, module_name);
        switch (event) {
        case Event::Change:
            return (NetconfAgent::change(sess, service_pair_));
        case Event::Done:
            return (NetconfAgent::done(sess, service_pair_));
        default:
            return (sysrepo::ErrorCode::Ok);
        }
    }

    void event_notif(Session /* session */,
                     uint32_t /* subscription_id */,
                     NotificationType const notification_type,
                     optional<DataNode> const notification_tree,
                     NotificationTimeStamp const /* timestamp */) {
        string n;
        switch (notification_type) {
        case NotificationType::Realtime:
            n = "NotificationType::Realtime";
            break;
        case NotificationType::Replay:
            n = "NotificationType::Replay";
            break;
        case NotificationType::ReplayComplete:
            n = "NotificationType::ReplayComplete";
            break;
        case NotificationType::Terminated:
            n = "NotificationType::Terminated";
            break;
        case NotificationType::Modified:
            n = "NotificationType::Modified";
            break;
        case NotificationType::Suspended:
            n = "NotificationType::Suspended";
            break;
        case NotificationType::Resumed:
            n = "NotificationType::Resumed";
            break;
        }

        optional<string> const str(
            notification_tree->printStr(DataFormat::JSON, PrintFlags::WithDefaultsExplicit));
        string const tree(str ? *str : string());
        LOG_INFO(netconf_logger, NETCONF_NOTIFICATION_RECEIVED)
            .arg(n)
            .arg(service_pair_.first)
            .arg(tree);
    }
};  // NetconfAgentCallback

}  //anonymous namespace

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
        subscribeToDataChanges(pair);
        subscribeToNotifications(pair);
    }
}

void
NetconfAgent::clear() {
    subscriptions_.clear();
    running_sess_.reset();
    startup_sess_.reset();
}

void
NetconfAgent::keaConfig(const CfgServersMapPair& service_pair) {
    string const& server(service_pair.first);
    CfgServerPtr const& configuration(service_pair.second);

    // If the boot-update flag is not set.
    if (!configuration->getBootUpdate()) {
        return;
    }
    CfgControlSocketPtr ctrl_sock = configuration->getCfgControlSocket();
    if (!ctrl_sock) {
        return;
    }
    ControlSocketBasePtr comm;
    try {
        comm = controlSocketFactory(ctrl_sock);
    } catch (exception const& ex) {
        ostringstream msg;
        msg << "createControlSocket failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_GET_CONFIG_FAILED)
            .arg(server)
            .arg(msg.str());
        return;
    }
    ConstElementPtr answer;
    int rcode;
    ConstElementPtr config;
    LOG_INFO(netconf_logger, NETCONF_GET_CONFIG_STARTED)
        .arg(server);
    try {
        answer = comm->configGet(server);
        config = parseAnswer(rcode, answer);
    } catch (exception const& ex) {
        ostringstream msg;
        msg << "config-get command failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_GET_CONFIG_FAILED)
            .arg(server)
            .arg(msg.str());
        return;
    }
    if (rcode != CONTROL_RESULT_SUCCESS) {
        ostringstream msg;
        msg << "config-get command returned " << answerToText(answer);
        LOG_ERROR(netconf_logger, NETCONF_GET_CONFIG_FAILED)
            .arg(server)
            .arg(msg.str());
        return;
    }
    if (!config) {
        LOG_ERROR(netconf_logger, NETCONF_GET_CONFIG_FAILED)
            .arg(server)
            .arg("config-get command returned an empty configuration");
        return;
    }
    LOG_DEBUG(netconf_logger, NETCONF_DBG_TRACE_DETAIL_DATA,
              NETCONF_GET_CONFIG)
        .arg(server)
        .arg(prettyPrint(config));
}

void
NetconfAgent::initSysrepo() {
    try {
        running_sess_ = Connection{}.sessionStart();
        running_sess_->switchDatastore(Datastore::Running);
        startup_sess_ = Connection{}.sessionStart();
        startup_sess_->switchDatastore(Datastore::Startup);
    } catch (exception const& ex) {
        isc_throw(Unexpected, "Can't establish a sysrepo session: "
                  << ex.what());
    }

    // Retrieve names and revisions of installed modules from sysrepo.
    getModules();
}

void NetconfAgent::getModules() {
    vector<Module> modules;
    try {
        Context context(running_sess_->getContext());
        modules = context.modules();
    } catch (Error const& ex) {
        isc_throw(Unexpected, "can't retrieve available modules: " << ex.what());
    }

    for (Module const& module : modules) {
        string const name(module.name());
        if (!module.revision()) {
            isc_throw(Unexpected,
                      "could not retrieve module revision for module " << name);
        }
        string const revision(*module.revision());
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
    string const& server(service_pair.first);
    CfgServerPtr const& configuration(service_pair.second);

    // If we're shutting down, or the boot-update flag is not set or the model
    // associated with it is not specified.
    if (!configuration->getBootUpdate() ||
        configuration->getModel().empty()) {
        return;
    }

    // First we need a way to reach the actual servers.
    CfgControlSocketPtr ctrl_sock = configuration->getCfgControlSocket();
    if (!ctrl_sock) {
        return;
    }

    LOG_INFO(netconf_logger, NETCONF_SET_CONFIG_STARTED)
        .arg(server);
    ElementPtr config;
    try {
        // Retrieve configuration from Sysrepo.
        TranslatorConfig tc(*startup_sess_, configuration->getModel());
        config = tc.getConfig();
        if (!config) {
            ostringstream msg;
            msg << "YANG configuration for "
                << configuration->getModel()
                << " is empty";
            LOG_ERROR(netconf_logger, NETCONF_SET_CONFIG_FAILED)
                .arg(server)
                .arg(msg.str());
            return;
        } else {
            LOG_DEBUG(netconf_logger, NETCONF_DBG_TRACE_DETAIL_DATA,
                      NETCONF_SET_CONFIG)
                .arg(server)
                .arg(prettyPrint(config));
        }
    } catch (exception const& ex) {
        ostringstream msg;
        msg << "get YANG configuration for " << server
            << " failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_SET_CONFIG_FAILED)
            .arg(server)
            .arg(msg.str());
        return;
    }
    ControlSocketBasePtr comm;
    try {
        comm = controlSocketFactory(ctrl_sock);
    } catch (exception const& ex) {
        ostringstream msg;
        msg << "control socket creation failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_SET_CONFIG_FAILED)
            .arg(server)
            .arg(msg.str());
        return;
    }
    ConstElementPtr answer;
    int rcode;
    try {
        answer = comm->configSet(config, server);
        parseAnswer(rcode, answer);
    } catch (exception const& ex) {
        ostringstream msg;
        msg << "config-set command failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_SET_CONFIG_FAILED)
            .arg(server)
            .arg(msg.str());
        return;
    }
    if (rcode != CONTROL_RESULT_SUCCESS) {
        ostringstream msg;
        msg << "config-set command returned " << answerToText(answer);
        LOG_ERROR(netconf_logger, NETCONF_SET_CONFIG_FAILED)
            .arg(server)
            .arg(msg.str());
        return;
    }
    LOG_INFO(netconf_logger, NETCONF_BOOT_UPDATE_COMPLETED)
        .arg(server);
}

void
NetconfAgent::subscribeToDataChanges(const CfgServersMapPair& service_pair) {
    string const& server(service_pair.first);
    CfgServerPtr const& configuration(service_pair.second);
    string const& model(configuration->getModel());

    // If we're shutting down, or the subscribe-changes flag is not set or
    // the model is not specified, give up on subscribing.
    if (!configuration->getSubscribeChanges() || model.empty()) {
        return;
    }
    LOG_INFO(netconf_logger, NETCONF_SUBSCRIBE_CONFIG)
        .arg(server)
        .arg(model);
    auto callback = [=](Session session,
                        uint32_t subscription_id,
                        string_view module_name,
                        optional<string_view> sub_xpath,
                        Event event,
                        uint32_t request_id) {
        NetconfAgentCallback agent(service_pair);
        return agent.module_change(session, subscription_id, module_name, sub_xpath, event, request_id);
    };
    try {
        SubscribeOptions options(SubscribeOptions::Default);
        if (!configuration->getValidateChanges()) {
            options = options | SubscribeOptions::DoneOnly;
        }
        Subscription subscription(
            running_sess_->onModuleChange(model, callback, nullopt, 0, options));
        subscriptions_.emplace(server, forward<Subscription>(subscription));
    } catch (exception const& ex) {
        ostringstream msg;
        msg << "module change subscribe failed with " << ex.what();
        msg << "change subscription for model " << model <<
            " failed with: " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_SUBSCRIBE_CONFIG_FAILED)
            .arg(server)
            .arg(configuration->getModel())
            .arg(msg.str());
        return;
    }
}

void
NetconfAgent::subscribeToNotifications(const CfgServersMapPair& service_pair) {
    string const& server(service_pair.first);
    CfgServerPtr const& configuration(service_pair.second);
    string const& model(configuration->getModel());

    // If we're shutting down, or the subscribe-changes flag is not set or
    // the model is not specified, give up on subscribing.
    if (!configuration->getSubscribeNotifications() || model.empty()) {
        return;
    }
    LOG_INFO(netconf_logger, NETCONF_SUBSCRIBE_NOTIFICATIONS)
        .arg(server)
        .arg(model);

    auto callback = [=](Session session,
                        uint32_t subscription_id,
                        NotificationType const notification_type,
                        optional<DataNode> const notification_tree,
                        NotificationTimeStamp const timestamp) {
        NetconfAgentCallback agent(service_pair);
        return agent.event_notif(session, subscription_id, notification_type, notification_tree, timestamp);
    };
    try {
        Subscription subscription(running_sess_->onNotification(model, callback));
        subscriptions_.emplace(server, forward<Subscription>(subscription));
    } catch (exception const& ex) {
        ostringstream msg;
        msg << "event notification subscription for model " << model <<
            " failed with: " << ex.what();
        LOG_WARN(netconf_logger, NETCONF_NOT_SUBSCRIBED_TO_NOTIFICATIONS)
            .arg(server)
            .arg(configuration->getModel())
            .arg(msg.str());
        return;
    }
}

sysrepo::ErrorCode
NetconfAgent::change(Session sess, const CfgServersMapPair& service_pair) {
    string const& server(service_pair.first);
    CfgServerPtr const& configuration(service_pair.second);

    // If we're shutting down, or the subscribe-changes or the
    // validate-changes flag is not set or the model associated with
    // it is not specified.
    if (!configuration->getSubscribeChanges() ||
        !configuration->getValidateChanges() ||
        configuration->getModel().empty()) {
        return (sysrepo::ErrorCode::Ok);
    }
    CfgControlSocketPtr ctrl_sock = configuration->getCfgControlSocket();
    if (!ctrl_sock) {
        return (sysrepo::ErrorCode::Ok);
    }
    LOG_INFO(netconf_logger, NETCONF_VALIDATE_CONFIG_STARTED)
        .arg(server);
    ElementPtr config;
    try {
        TranslatorConfig tc(sess, configuration->getModel());
        config = tc.getConfig();
        if (!config) {
            ostringstream msg;
            msg << "YANG configuration for "
                << configuration->getModel()
                << " is empty";
            LOG_ERROR(netconf_logger, NETCONF_VALIDATE_CONFIG_FAILED)
                .arg(server)
                .arg(msg.str());
            return (sysrepo::ErrorCode::OperationFailed);
        } else {
            LOG_DEBUG(netconf_logger, NETCONF_DBG_TRACE_DETAIL_DATA,
                      NETCONF_VALIDATE_CONFIG)
                .arg(server)
                .arg(prettyPrint(config));
        }
    } catch (exception const& ex) {
        ostringstream msg;
        msg << "get YANG configuration for " << server
            << " failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_VALIDATE_CONFIG_FAILED)
            .arg(server)
            .arg(msg.str());
        return (sysrepo::ErrorCode::ValidationFailed);
    }
    ControlSocketBasePtr comm;
    try {
        comm = controlSocketFactory(ctrl_sock);
    } catch (exception const& ex) {
        ostringstream msg;
        msg << "createControlSocket failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_VALIDATE_CONFIG_FAILED)
            .arg(server)
            .arg(msg.str());
        return (sysrepo::ErrorCode::Ok);
    }
    ConstElementPtr answer;
    int rcode;
    try {
        answer = comm->configTest(config, server);
        parseAnswer(rcode, answer);
    } catch (exception const& ex) {
        stringstream msg;
        msg << "configTest failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_VALIDATE_CONFIG_FAILED)
            .arg(server)
            .arg(msg.str());
        return (sysrepo::ErrorCode::ValidationFailed);
    }
    if (rcode != CONTROL_RESULT_SUCCESS) {
        stringstream msg;
        msg << "configTest returned " << answerToText(answer);
        LOG_ERROR(netconf_logger, NETCONF_VALIDATE_CONFIG_REJECTED)
            .arg(server)
            .arg(msg.str());
        return (sysrepo::ErrorCode::ValidationFailed);
    }
    LOG_INFO(netconf_logger, NETCONF_VALIDATE_CONFIG_COMPLETED)
        .arg(server);
    return (sysrepo::ErrorCode::Ok);
}

sysrepo::ErrorCode
NetconfAgent::done(Session sess, const CfgServersMapPair& service_pair) {
    string const& server(service_pair.first);
    CfgServerPtr const& configuration(service_pair.second);

    // Check if we should and can process this update.
    if (!configuration->getSubscribeChanges() ||
        configuration->getModel().empty()) {
        return (sysrepo::ErrorCode::Ok);
    }
    CfgControlSocketPtr ctrl_sock = configuration->getCfgControlSocket();
    if (!ctrl_sock) {
        return (sysrepo::ErrorCode::Ok);
    }

    // All looks good, let's get started. Print an info that we're about
    // to update the configuration.
    LOG_INFO(netconf_logger, NETCONF_UPDATE_CONFIG_STARTED)
        .arg(server);

    // Retrieve the configuration from SYSREPO first.
    ElementPtr config;
    try {
        TranslatorConfig tc(sess, configuration->getModel());
        config = tc.getConfig();
        if (!config) {
            ostringstream msg;
            msg << "YANG configuration for "
                << configuration->getModel()
                << " is empty";
            LOG_ERROR(netconf_logger, NETCONF_UPDATE_CONFIG_FAILED)
                .arg(server)
                .arg(msg.str());
            return (sysrepo::ErrorCode::ValidationFailed);
        } else {
            LOG_DEBUG(netconf_logger, NETCONF_DBG_TRACE_DETAIL_DATA,
                      NETCONF_UPDATE_CONFIG)
                .arg(server)
                .arg(prettyPrint(config));
        }
    } catch (exception const& ex) {
        ostringstream msg;
        msg << "get YANG configuration for " << server
            << " failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_UPDATE_CONFIG_FAILED)
            .arg(server)
            .arg(msg.str());
        return (sysrepo::ErrorCode::ValidationFailed);
    }

    // Ok, now open the control socket. We need this to send the config to
    // the server.
    ControlSocketBasePtr comm;
    try {
        comm = controlSocketFactory(ctrl_sock);
    } catch (exception const& ex) {
        ostringstream msg;
        msg << "createControlSocket failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_UPDATE_CONFIG_FAILED)
            .arg(server)
            .arg(msg.str());
        return (sysrepo::ErrorCode::Ok);
    }

    // Now apply the config using config-set command.
    ConstElementPtr answer;
    int rcode;
    try {
        answer = comm->configSet(config, server);
        parseAnswer(rcode, answer);
    } catch (exception const& ex) {
        stringstream msg;
        msg << "configSet failed with " << ex.what();
        LOG_ERROR(netconf_logger, NETCONF_UPDATE_CONFIG_FAILED)
            .arg(server)
            .arg(msg.str());
        return (sysrepo::ErrorCode::ValidationFailed);
    }

    // rcode == CONTROL_RESULT_SUCCESS, unless the docs say otherwise :).
    if (rcode != CONTROL_RESULT_SUCCESS) {
        stringstream msg;
        msg << "configSet returned " << answerToText(answer);
        LOG_ERROR(netconf_logger, NETCONF_UPDATE_CONFIG_FAILED)
            .arg(server)
            .arg(msg.str());
        return (sysrepo::ErrorCode::ValidationFailed);
    }
    LOG_INFO(netconf_logger, NETCONF_UPDATE_CONFIG_COMPLETED)
        .arg(server);
    return (sysrepo::ErrorCode::Ok);
}

void
NetconfAgent::logChanges(Session sess, string_view const& model) {
    ostringstream stream;
    stream << "/" << model << ":*//.";
    string const xpath(stream.str());
    ChangeCollection const changes(sess.getChanges(xpath));
    for (Change const& change : changes) {
        ostringstream msg;
        switch (change.operation) {
        case sysrepo::ChangeOperation::Created:
            msg << "created: ";
            break;
        case sysrepo::ChangeOperation::Deleted:
            msg << "deleted: ";
            break;
        case sysrepo::ChangeOperation::Modified:
            msg << "modified: ";
            break;
        case sysrepo::ChangeOperation::Moved:
            msg << "moved: ";
            break;
        default:
            msg << "unknown operation (" << change.operation << "): ";
        }
        string const path(change.node.path());
        msg << path;
        SchemaNode const& schema(change.node.schema());
        NodeType const node_type(schema.nodeType());
        if (node_type == NodeType::Container) {
            msg << " (container)";
        } else if (node_type == NodeType::List) {
            msg << " (list)";
        } else {
            optional<string> const str(
                Translator::translateToYang(Translator::translateFromYang(change.node),
                                            LeafBaseType::Unknown));
            if (str) {
                msg << " = " << *str;
            }
        }

        LOG_DEBUG(netconf_logger, NETCONF_DBG_TRACE_DETAIL_DATA,
                  NETCONF_CONFIG_CHANGED_DETAIL)
            .arg(msg.str());
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

}  // namespace netconf
}  // namespace isc
