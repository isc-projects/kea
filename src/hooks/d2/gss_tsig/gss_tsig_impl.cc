// Copyright (C) 2021-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/command_interpreter.h>
#include <stats/stats_mgr.h>
#include <gss_tsig_impl.h>
#include <gss_tsig_log.h>
#include <boost/foreach.hpp>
#include <cstdlib>
#include <list>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::d2;
using namespace isc::data;
using namespace isc::hooks;
using namespace isc::log;
using namespace isc::stats;
using namespace std;
using namespace std::chrono;

namespace isc {
namespace gss_tsig {

GssTsigImpl::GssTsigImpl() : cfg_(), keys_(), io_service_(new IOService()),
    krb5_client_ktname_prev_(), krb5ccname_prev_(), purge_timer_() {
}

GssTsigImpl::~GssTsigImpl() {
    stop();
    io_service_->stopAndPoll();
}

void
GssTsigImpl::configure(ConstElementPtr config) {
    cfg_.configure(config);
    if (!cfg_.getClientKeyTab().empty()) {
        char* krb5_client_ktname = getenv("KRB5_CLIENT_KTNAME");
        if (krb5_client_ktname) {
            krb5_client_ktname_prev_.reset(new string(krb5_client_ktname));
        } else {
            krb5_client_ktname_prev_.reset();
        }
        setenv("KRB5_CLIENT_KTNAME", cfg_.getClientKeyTab().c_str(), 1);
    }
    if (!cfg_.getCredsCache().empty()) {
        char* krb5ccname = getenv("KRB5CCNAME");
        if (krb5ccname) {
            krb5ccname_prev_.reset(new string(krb5ccname));
        } else {
            krb5ccname_prev_.reset();
        }
        setenv("KRB5CCNAME", cfg_.getCredsCache().c_str(), 1);
    }
    StatsMgr& stats_mgr = StatsMgr::instance();
    for (auto const& name : DnsServer::STAT_NAMES) {
        stats_mgr.setValue(name, static_cast<int64_t>(0));
    }
}

void
GssTsigImpl::finishConfigure(D2CfgContextPtr d2_config) {
    cfg_.buildServerRevMap(d2_config);
}

void
GssTsigImpl::start() {
    LOG_DEBUG(gss_tsig_logger, DBGLVL_TRACE_BASIC, GSS_TSIG_MANAGER_STARTED);
    for (auto const& server : cfg_.getServerList()) {
        if (!server) {
            continue;
        }
        server->getTimer().reset(new IntervalTimer(io_service_));
    }
    processAllServersKeys();
    uint32_t max_tkey_lifetime = cfg_.getMaxKeyLifetime();
    if (max_tkey_lifetime > 0) {
        purge_timer_.reset(new IntervalTimer(io_service_));
        purge_timer_->setup([this]() { purgeKeys(); },
                            max_tkey_lifetime * 1000,
                            IntervalTimer::REPEATING);
    }
}

void
GssTsigImpl::stop() {
    LOG_DEBUG(gss_tsig_logger, DBGLVL_TRACE_BASIC, GSS_TSIG_MANAGER_STOPPED);
    if (purge_timer_) {
        purge_timer_->cancel();
        purge_timer_.reset();
    }
    for (auto const& server : cfg_.getServerList()) {
        if (!server) {
            continue;
        }
        if (server->getTimer()) {
            server->getTimer()->cancel();
            server->getTimer().reset();
        }
    }
    for (auto const& key : keys_) {
        key->getTKeyExchange().reset();
    }
    keys_.clear();
    cfg_.clearServers();
    // Run cancelled callbacks.
    if (io_service_) {
        try {
            io_service_->poll();
        } catch (const std::exception& ex) {
            LOG_ERROR(gss_tsig_logger, GSS_TSIG_MANAGER_STOP_ERROR)
                .arg(ex.what());
        } catch (...) {
            LOG_ERROR(gss_tsig_logger, GSS_TSIG_MANAGER_STOP_GENERAL_ERROR);
        }
    }
    // Remove statistics.
    StatsMgr& stats_mgr = StatsMgr::instance();
    for (auto const& name : DnsServer::STAT_NAMES) {
        stats_mgr.del(name);
    }
    // Restore environment variables.
    if (!cfg_.getClientKeyTab().empty()) {
        if (krb5_client_ktname_prev_) {
            setenv("KRB5_CLIENT_KTNAME", krb5_client_ktname_prev_->c_str(), 1);
        } else {
            unsetenv("KRB5_CLIENT_KTNAME");
        }
    }
    if (!cfg_.getCredsCache().empty()) {
        if (krb5ccname_prev_) {
            setenv("KRB5CCNAME", krb5ccname_prev_->c_str(), 1);
        } else {
            unsetenv("KRB5CCNAME");
        }
    }
}

void
GssTsigImpl::createKey(DnsServerPtr server,
                       time_point<std::chrono::system_clock> now) {
    StatsMgr& stats_mgr = StatsMgr::instance();
    stats_mgr.addValue("gss-tsig-key-created",
                       static_cast<int64_t>(1));
    stats_mgr.addValue(StatsMgr::generateName("server",
                                              server->getID(),
                                              "gss-tsig-key-created"),
                       static_cast<int64_t>(1));
    string name;
    for (;;) {
        name = ManagedKey::genName(server->getKeyNameSuffix());
        if (keys_.count(name) == 0) {
            break;
        }
        // Very unlikely but possible name collision.
        // Try another name.
    }
    LOG_INFO(gss_tsig_logger, GSS_TSIG_NEW_KEY).arg(name);
    ManagedKeyPtr mkey(new ManagedKey(name));
    mkey->setParentID(server->getID());
    mkey->setInception(now);
    mkey->setExpire(now + seconds(server->getKeyLifetime()));
    static_cast<void>(keys_.insert(mkey));
    OM_uint32 flags = TKeyExchange::TKEY_EXCHANGE_FLAGS;
    if (!server->getGssReplayFlag()) {
        flags &= ~GSS_C_REPLAY_FLAG;
    }
    if (server->getGssSequenceFlag()) {
        flags |= GSS_C_SEQUENCE_FLAG;
    }
    mkey->getTKeyExchange().reset(new TKeyExchange(io_service_, server, mkey,
                                                   mkey.get(),
                                                   server->getExchangeTimeout(),
                                                   flags));

    io_service_->post([mkey]() {
            if (mkey->getTKeyExchange()) {
                mkey->getTKeyExchange()->doExchange();
            }
        });
}

void
GssTsigImpl::processAllServersKeys(bool rekey) {
    for (auto const& server : cfg_.getServerList()) {
        processServerKeys(server, rekey);
    }
}

void
GssTsigImpl::processServerKeys(DnsServerPtr server, bool rekey) {
    if (!server) {
        return;
    }
    bool retry = false;
    ManagedKeyPtr newest;
    auto const now = system_clock::now();
    const std::chrono::seconds retry_dur(server->getRetryInterval());
    const std::chrono::seconds rekey_dur(server->getRekeyInterval());
    auto const& idx = keys_.get<GssTsigKeyServerTag>();
    auto const& range = idx.equal_range(server->getID());
    try {
        BOOST_FOREACH(auto const& key, range) {
            lock_guard<mutex> lock(*key->mutex_);
            if (!newest || (newest->getInception() < key->getInception())) {
                newest = key;
            }
            if (key->getStatus() == ManagedKey::USABLE) {
                if (now >= key->getExpire()) {
                    key->setStatus(ManagedKey::EXPIRED);
                }
            }
        }
        // Rekey if no key or the newest key is not usable but ready.
        if (!newest) {
            rekey = true;
        } else {
            switch (newest->getStatus()) {
            case ManagedKey::NOT_READY:
                // Lost some race, check again later.
                retry = true;
                break;
            case ManagedKey::USABLE:
                break;
            default:
                rekey = true;
                break;
            }
        }
        // Rekey too if the newest key is usable but soon to expire.
        if (!rekey &&
            ((now + retry_dur >= newest->getExpire()) ||
             (now >= newest->getInception() + rekey_dur))) {
            rekey = true;
        }
        // Create and setup a new GSS-TSIG key.
        if (rekey) {
            createKey(server, now);
            retry = true;
        }
    } catch (const std::exception& ex) {
        retry = true;
        LOG_ERROR(gss_tsig_logger, KEY_PROCESSING_FAILED)
            .arg(server->getID())
            .arg(ex.what());
    } catch (...) {
        retry = true;
        LOG_ERROR(gss_tsig_logger, KEY_PROCESSING_FAILED_UNSPECIFIED_ERROR)
            .arg(server->getID());
    }
    auto timer = server->getTimer();
    if (!timer) {
        return;
    }
    timer->cancel();
    // Schedule a retry.
    if (retry || !newest) {
        timer->setup([this, server]() { processServerKeys(server); },
                     server->getRetryInterval() * 1000,
                     IntervalTimer::ONE_SHOT);
        LOG_DEBUG(gss_tsig_logger, DBGLVL_TRACE_BASIC, START_RETRY_TIMER)
            .arg(server->getID())
            .arg(server->getRetryInterval());
        return;
    }
    // Schedule a rekey.
    auto const rekey_date = newest->getInception() + rekey_dur;
    const std::chrono::system_clock::duration rekey_interval(rekey_date - now);
    auto interval =
        (duration_cast<nanoseconds>(rekey_interval).count() + 999999) / 1000000;
    if (interval < server->getRetryInterval()) {
        interval = server->getRetryInterval();
    }
    timer->setup([this, server]() { processServerKeys(server); },
                 interval, IntervalTimer::ONE_SHOT);
    LOG_DEBUG(gss_tsig_logger, DBGLVL_TRACE_BASIC, START_REKEY_TIMER)
        .arg(server->getID())
        .arg(interval / 1000);
}

DnsServerPtr
GssTsigImpl::getServer(const std::string& id) const {
    return (cfg_.getServer(id));
}

ManagedKeyPtr
GssTsigImpl::findKey(const d2::DnsServerInfoPtr& server_info,
                     bool& useGssTsig, bool& fallback) {
    DnsServerPtr server = cfg_.getServer(server_info);
    if (!server) {
        LOG_DEBUG(gss_tsig_logger, DBGLVL_TRACE_BASIC, KEY_LOOKUP_DISABLED);
        useGssTsig = false;
        fallback = false;
        return (ManagedKeyPtr());
    }
    useGssTsig = true;
    fallback = server->getFallback();
    auto now = system_clock::now();
    auto const& idx = keys_.get<GssTsigKeyServerTag>();
    auto const& range = idx.equal_range(server->getID());
    ManagedKeyPtr candidate;
    BOOST_FOREACH(auto const& key, range) {
        lock_guard<mutex> lock(*key->mutex_);
        if (key->getStatus() == ManagedKey::USABLE) {
            if (now >= key->getExpire()) {
                key->setStatus(ManagedKey::EXPIRED);
                continue;
            }
            candidate = key;
        }
    }
    if (candidate) {
        LOG_DEBUG(gss_tsig_logger, DBGLVL_TRACE_BASIC, KEY_LOOKUP_FOUND)
            .arg(candidate->getKeyNameStr());
        return (candidate);
    }
    LOG_DEBUG(gss_tsig_logger, DBGLVL_TRACE_BASIC, KEY_LOOKUP_NONE);
    return (ManagedKeyPtr());
}

ManagedKeyPtr
GssTsigImpl::findKey(const std::string& name) const {
    auto const& it = keys_.find(name);
    if (it == keys_.cend()) {
        return (ManagedKeyPtr());
    }
    return (*it);
}

void
GssTsigImpl::purgeKeys() {
    // Build the list of keys to remove.
    auto now = system_clock::now();
    std::chrono::seconds max_age(cfg_.getMaxKeyLifetime() * 3);
    list<ManagedKeyPtr> to_purge;
    for (auto const& key : keys_) {
        lock_guard<mutex> lock(*key->mutex_);
        if (key->getExpire() + max_age < now) {
            to_purge.push_back(key);
        }
    }

    // Return now if there is no key to remove.
    if (to_purge.empty()) {
        return;
    }

    // Remove all elements of the list.
    for (auto const& key : to_purge) {
        auto it = keys_.find(key->getKeyNameStr());
        if (it != keys_.end()) {
            key->getTKeyExchange().reset();
            keys_.erase(it);
        }
    }

    /// log a message with the count.
    LOG_DEBUG(gss_tsig_logger, DBGLVL_TRACE_BASIC, GSS_TSIG_OLD_KEY_REMOVED)
        .arg(to_purge.size());
}

void
GssTsigImpl::getHandler(CalloutHandle& handle) const {
    ConstElementPtr response;
    string id;
    DnsServerPtr server;
    try {
        // Command is always provided.
        ConstElementPtr command;
        handle.getArgument("command", command);

        // Retrieve arguments.
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        // Arguments are required.
        if (!args) {
            isc_throw(BadValue, "arguments not found in the '"
                      << command->str() << "' command");
        }

        // Arguments must be a map.
        if (args->getType() != Element::map) {
            isc_throw(BadValue, "arguments in the '" << command->str()
                      << "' command are not a map");
        }

        // server-id is mandatory.
        ConstElementPtr server_id = args->get("server-id");
        if (!server_id) {
            isc_throw(BadValue, "'server-id' is mandatory for the '"
                      << command->str() << "' command");
        }

        // server-id must be a string.
        if (server_id->getType() != Element::string) {
            isc_throw(BadValue, "'server-id' must be a string in the '"
                      << command->str() << "' command");
        }

        id = server_id->stringValue();
        server = cfg_.getServer(id);
    } catch (const std::exception& ex) {
        // There was an error while parsing command arguments.
        // Return an error status code to notify the user.
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        handle.setArgument("response", response);
        return;
    }

    ostringstream msg;
    msg << "GSS-TSIG server[" << id << "] ";

    // No server.
    if (!server) {
        msg << "not found";
        response = createAnswer(CONTROL_RESULT_EMPTY, msg.str());
    } else {
        msg << "found";
        ElementPtr desc = server->toElement();
        ElementPtr keys = Element::createList();
        auto const& idx = keys_.get<GssTsigKeyServerTag>();
        auto const& range = idx.equal_range(server->getID());
        BOOST_FOREACH(auto const& key, range) {
            keys->add(key->toElement());
        }
        desc->set("keys", keys);
        response = createAnswer(CONTROL_RESULT_SUCCESS, msg.str(), desc);
    }
    handle.setArgument("response", response);
}

void
GssTsigImpl::getAllHandler(CalloutHandle& handle) const {
    ConstElementPtr response;
    // Create a list where we're going to store servers' information.
    ElementPtr servers = Element::createList();
    // Create arguments map and add server list.
    ElementPtr args = Element::createMap();
    args->set("gss-tsig-servers", servers);
    auto const& idx = keys_.get<GssTsigKeyServerTag>();
    size_t key_count(0);

    // Iterate over servers.
    for (auto const& server : cfg_.getServerList()) {
        ElementPtr desc = server->toElement();
        ElementPtr keys = Element::createList();
        auto const& range = idx.equal_range(server->getID());
        BOOST_FOREACH(auto const& key, range) {
            keys->add(key->toElement());
        }
        desc->set("keys", keys);
        key_count += keys->size();
        servers->add(desc);
    }

    ostringstream msg;
    msg << servers->size() << " GSS-TSIG servers";

    if (servers->empty()) {
        response = createAnswer(CONTROL_RESULT_EMPTY, msg.str(), args);
    } else {
        msg << " and " << key_count << " keys";
        response = createAnswer(CONTROL_RESULT_SUCCESS, msg.str(), args);
    }
    handle.setArgument("response", response);
}

void
GssTsigImpl::listHandler(CalloutHandle& handle) const {
    ConstElementPtr response;
    // Create a list where we're going to store servers' ID.
    ElementPtr servers = Element::createList();
    // Create a list where we're going to store keys' name.
    ElementPtr keys = Element::createList();
    // Create arguments map and add server and key lists.
    ElementPtr args = Element::createMap();
    args->set("gss-tsig-servers", servers);
    args->set("gss-tsig-keys", keys);

    // Iterate over servers.
    for (auto const& server : cfg_.getServerList()) {
        servers->add(Element::create(server->getID()));
    }

    // Iterate over keys.
    for (auto const& key : keys_) {
        keys->add(Element::create(key->getKeyNameStr()));
    }

    ostringstream msg;
    msg << servers->size() << " GSS-TSIG servers and "
        << keys->size() << " keys";

    if (servers->empty() && keys->empty()) {
        response = createAnswer(CONTROL_RESULT_EMPTY, msg.str(), args);
    } else {
        response = createAnswer(CONTROL_RESULT_SUCCESS, msg.str(), args);
    }
    handle.setArgument("response", response);
}

void
GssTsigImpl::keyGetHandler(CalloutHandle& handle) const {
    ConstElementPtr response;
    string name;
    ManagedKeyPtr key;
    try {
        // Command is always provided.
        ConstElementPtr command;
        handle.getArgument("command", command);

        // Retrieve arguments.
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        // Arguments are required.
        if (!args) {
            isc_throw(BadValue, "arguments not found in the '"
                      << command->str() << "' command");
        }

        // Arguments must be a map.
        if (args->getType() != Element::map) {
            isc_throw(BadValue, "arguments in the '" << command->str()
                      << "' command are not a map");
        }

        // key-name is mandatory.
        ConstElementPtr key_name = args->get("key-name");
        if (!key_name) {
            isc_throw(BadValue, "'key-name' is mandatory for the '"
                      << command->str() << "' command");
        }

        // key-name must be a string.
        if (key_name->getType() != Element::string) {
            isc_throw(BadValue, "'key-name' must be a string in the '"
                      << command->str() << "' command");
        }

        name = key_name->stringValue();
        key = findKey(name);
    } catch (const std::exception& ex) {
        // There was an error while parsing command arguments.
        // Return an error status code to notify the user.
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        handle.setArgument("response", response);
        return;
    }

    ostringstream msg;
    msg << "GSS-TSIG key '" << name << "' ";

    // No key.
    if (!key) {
        msg << "not found";
        response = createAnswer(CONTROL_RESULT_EMPTY, msg.str());
    } else {
        msg << "found";
        ConstElementPtr desc = key->toElement();
        response = createAnswer(CONTROL_RESULT_SUCCESS, msg.str(), desc);
    }
    handle.setArgument("response", response);
}

void
GssTsigImpl::keyExpireHandler(CalloutHandle& handle) {
    ConstElementPtr response;
    string name;
    ManagedKeyPtr key;
    try {
        // Command is always provided.
        ConstElementPtr command;
        handle.getArgument("command", command);

        // Retrieve arguments.
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        // Arguments are required.
        if (!args) {
            isc_throw(BadValue, "arguments not found in the '"
                      << command->str() << "' command");
        }

        // Arguments must be a map.
        if (args->getType() != Element::map) {
            isc_throw(BadValue, "arguments in the '" << command->str()
                      << "' command are not a map");
        }

        // key-name is mandatory.
        ConstElementPtr key_name = args->get("key-name");
        if (!key_name) {
            isc_throw(BadValue, "'key-name' is mandatory for the '"
                      << command->str() << "' command");
        }

        // key-name must be a string.
        if (key_name->getType() != Element::string) {
            isc_throw(BadValue, "'key-name' must be a string in the '"
                      << command->str() << "' command");
        }

        name = key_name->stringValue();
        key = findKey(name);
    } catch (const std::exception& ex) {
        // There was an error while parsing command arguments.
        // Return an error status code to notify the user.
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        handle.setArgument("response", response);
        return;
    }

    ostringstream msg;
    msg << "GSS-TSIG key '" << name << "' ";

    // No key.
    if (!key) {
        msg << "not found";
        response = createAnswer(CONTROL_RESULT_EMPTY, msg.str());
    } else {
        bool can_expire = true;
        {
            lock_guard<mutex> lock(*key->mutex_);
            if (key->getStatus() >= ManagedKey::EXPIRED) {
                can_expire = false;
            } else {
                key->setStatus(ManagedKey::EXPIRED);
            }
        }
        if (!can_expire) {
            msg << "can't be expired";
            response = createAnswer(CONTROL_RESULT_EMPTY, msg.str());
        } else {
            msg << "expired";
            response = createAnswer(CONTROL_RESULT_SUCCESS, msg.str());
        }
    }
    handle.setArgument("response", response);
}

void
GssTsigImpl::keyDelHandler(CalloutHandle& handle) {
    ConstElementPtr response;
    string name;
    ManagedKeyPtr key;
    try {
        // Command is always provided.
        ConstElementPtr command;
        handle.getArgument("command", command);

        // Retrieve arguments.
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        // Arguments are required.
        if (!args) {
            isc_throw(BadValue, "arguments not found in the '"
                      << command->str() << "' command");
        }

        // Arguments must be a map.
        if (args->getType() != Element::map) {
            isc_throw(BadValue, "arguments in the '" << command->str()
                      << "' command are not a map");
        }

        // key-name is mandatory.
        ConstElementPtr key_name = args->get("key-name");
        if (!key_name) {
            isc_throw(BadValue, "'key-name' is mandatory for the '"
                      << command->str() << "' command");
        }

        // key-name must be a string.
        if (key_name->getType() != Element::string) {
            isc_throw(BadValue, "'key-name' must be a string in the '"
                      << command->str() << "' command");
        }

        name = key_name->stringValue();
        key = findKey(name);
    } catch (const std::exception& ex) {
        // There was an error while parsing command arguments.
        // Return an error status code to notify the user.
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        handle.setArgument("response", response);
        return;
    }

    ostringstream msg;
    msg << "GSS-TSIG key '" << name << "' ";

    // No key.
    if (!key) {
        msg << "not found";
        response = createAnswer(CONTROL_RESULT_EMPTY, msg.str());
    } else {
        msg << "deleted";
        auto it = keys_.find(name);
        if (it != keys_.end()) {
            key->getTKeyExchange().reset();
            keys_.erase(it);
        }
        response = createAnswer(CONTROL_RESULT_SUCCESS, msg.str());
    }
    handle.setArgument("response", response);
}

void
GssTsigImpl::purgeHandler(CalloutHandle& handle) {
    ConstElementPtr response;
    string id;
    try {
        // Command is always provided.
        ConstElementPtr command;
        handle.getArgument("command", command);

        // Retrieve arguments.
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        // Arguments are required.
        if (!args) {
            isc_throw(BadValue, "arguments not found in the '"
                      << command->str() << "' command");
        }

        // Arguments must be a map.
        if (args->getType() != Element::map) {
            isc_throw(BadValue, "arguments in the '" << command->str()
                      << "' command are not a map");
        }

        // server-id is mandatory.
        ConstElementPtr server_id = args->get("server-id");
        if (!server_id) {
            isc_throw(BadValue, "'server-id' is mandatory for the '"
                      << command->str() << "' command");
        }

        // server-id must be a string.
        if (server_id->getType() != Element::string) {
            isc_throw(BadValue, "'server-id' must be a string in the '"
                      << command->str() << "' command");
        }

        id = server_id->stringValue();
    } catch (const std::exception& ex) {
        // There was an error while parsing command arguments.
        // Return an error status code to notify the user.
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        handle.setArgument("response", response);
        return;
    }

    // Build the list of keys to remove.
    auto now = system_clock::now();
    list<ManagedKeyPtr> to_purge;
    auto const& idx = keys_.get<GssTsigKeyServerTag>();
    auto const& range = idx.equal_range(id);
    BOOST_FOREACH(auto const& key, range) {
        lock_guard<mutex> lock(*key->mutex_);
        auto status = key->getStatus();
        switch (status) {
        case ManagedKey::NOT_READY:
            // skip
            break;
        case ManagedKey::USABLE:
            if (now < key->getExpire()) {
                // skip
                break;
            }
            key->setStatus(ManagedKey::EXPIRED);
            to_purge.push_back(key);
            break;
        default:
            to_purge.push_back(key);
            break;
        }
    }

    // Remove all elements of the list.
    for (auto const& key : to_purge) {
        auto it = keys_.find(key->getKeyNameStr());
        if (it != keys_.end()) {
            key->getTKeyExchange().reset();
            keys_.erase(it);
        }
    }

    ostringstream msg;
    msg << to_purge.size() << " purged keys for GSS-TSIG server[" << id << "]";

    if (to_purge.empty()) {
        response = createAnswer(CONTROL_RESULT_EMPTY, msg.str());
    } else {
        response = createAnswer(CONTROL_RESULT_SUCCESS, msg.str());
    }
    handle.setArgument("response", response);
}

void
GssTsigImpl::purgeAllHandler(CalloutHandle& handle) {
    ConstElementPtr response;

    // Build the list of keys to remove.
    auto now = system_clock::now();
    list<ManagedKeyPtr> to_purge;
    for (auto const& key : keys_) {
        lock_guard<mutex> lock(*key->mutex_);
        auto status = key->getStatus();
        switch (status) {
        case ManagedKey::NOT_READY:
            // skip
            break;
        case ManagedKey::USABLE:
            if (now < key->getExpire()) {
                // skip
                break;
            }
            key->setStatus(ManagedKey::EXPIRED);
            to_purge.push_back(key);
            break;
        default:
            to_purge.push_back(key);
            break;
        }
    }

    // Remove all elements of the list.
    for (auto const& key : to_purge) {
        auto it = keys_.find(key->getKeyNameStr());
        if (it != keys_.end()) {
            key->getTKeyExchange().reset();
            keys_.erase(it);
        }
    }

    ostringstream msg;
    msg << to_purge.size() << " purged GSS-TSIG keys";

    if (to_purge.empty()) {
        response = createAnswer(CONTROL_RESULT_EMPTY, msg.str());
    } else {
        response = createAnswer(CONTROL_RESULT_SUCCESS, msg.str());
    }
    handle.setArgument("response", response);
}

void
GssTsigImpl::rekeyHandler(CalloutHandle& handle) {
    ConstElementPtr response;
    string id;
    DnsServerPtr server;
    try {
        // Command is always provided.
        ConstElementPtr command;
        handle.getArgument("command", command);

        // Retrieve arguments.
        ConstElementPtr args;
        static_cast<void>(parseCommand(args, command));

        // Arguments are required.
        if (!args) {
            isc_throw(BadValue, "arguments not found in the '"
                      << command->str() << "' command");
        }

        // Arguments must be a map.
        if (args->getType() != Element::map) {
            isc_throw(BadValue, "arguments in the '" << command->str()
                      << "' command are not a map");
        }

        // server-id is mandatory.
        ConstElementPtr server_id = args->get("server-id");
        if (!server_id) {
            isc_throw(BadValue, "'server-id' is mandatory for the '"
                      << command->str() << "' command");
        }

        // server-id must be a string.
        if (server_id->getType() != Element::string) {
            isc_throw(BadValue, "'server-id' must be a string in the '"
                      << command->str() << "' command");
        }

        id = server_id->stringValue();
        server = cfg_.getServer(id);
    } catch (const std::exception& ex) {
        // There was an error while parsing command arguments.
        // Return an error status code to notify the user.
        response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        handle.setArgument("response", response);
        return;
    }

    ostringstream msg;
    msg << "GSS-TSIG server[" << id << "] ";

    // No server.
    if (!server) {
        msg << "not found";
        response = createAnswer(CONTROL_RESULT_EMPTY, msg.str());
    } else {
        auto now = system_clock::now();
        createKey(server, now);
        msg << "rekeyed";
        response = createAnswer(CONTROL_RESULT_SUCCESS, msg.str());
    }
    handle.setArgument("response", response);
}

void
GssTsigImpl::rekeyAllHandler(CalloutHandle& handle) {
    io_service_->post([this]() { processAllServersKeys(true); });
    ConstElementPtr response = createAnswer(CONTROL_RESULT_SUCCESS, "rekeyed");
    handle.setArgument("response", response);
}

void
GssTsigImpl::commandProcessed(CalloutHandle& handle) {
    // Filter command names.
    string command_name;
    handle.getArgument("name", command_name);
    if (command_name != "status-get") {
        return;
    }
    // Get the response.
    ConstElementPtr response;
    handle.getArgument("response", response);
    if (!response || (response->getType() != Element::map)) {
        return;
    }
    // Get the arguments item from the response.
    ConstElementPtr resp_args = response->get("arguments");
    if (!resp_args || (resp_args->getType() != Element::map)) {
        return;
    }
    // Add the gss-tsig entry.
    ElementPtr mutable_resp_args = boost::const_pointer_cast<Element>(resp_args);
    mutable_resp_args->set("gss-tsig", Element::create(true));
}

} // end of namespace isc::gss_tsig
} // end of namespace isc
