// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <host_cache.h>
#include <host_cache_impl.h>
#include <host_cache_parsers.h>
#include <host_cache_log.h>
#include <database/db_exceptions.h>
#include <dhcpsrv/cfgmgr.h>
#include <util/encode/encode.h>
#include <util/multi_threading_mgr.h>
#include <util/str.h>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;
using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::util;

namespace isc {
namespace host_cache {

HostCache::HostCache() : impl_(new HostCacheImpl()), mutex_(new std::mutex) {
}

HostCache::~HostCache() {
    impl_.reset();
}

void HostCache::configure(const ConstElementPtr&config) {
    HCConfigParser parser;
    parser.parse(*this, config);
}

void HostCache::setMaximum(size_t maximum) {
    MultiThreadingLock lock(*mutex_);
    impl_->setMaximum(maximum);
}

size_t HostCache::getMaximum() const {
    MultiThreadingLock lock(*mutex_);
    return (impl_->getMaximum());
}

ConstHostCollection
HostCache::getAll(const Host::IdentifierType& /*identifier_type*/,
                  const uint8_t* /*identifier_begin*/,
                  const size_t /*identifier_len*/) const {
    return (ConstHostCollection());
}

ConstHostCollection
HostCache::getAll4(const dhcp::SubnetID& /*subnet_id*/) const {
    return (ConstHostCollection());
}

ConstHostCollection
HostCache::getAll6(const dhcp::SubnetID& /*subnet_id*/) const {
    return (ConstHostCollection());
}

ConstHostCollection
HostCache::getAllbyHostname(const std::string& /*hostname*/) const {
    return (ConstHostCollection());
}

ConstHostCollection
HostCache::getAllbyHostname4(const std::string& /*hostname*/,
                             const dhcp::SubnetID& /*subnet_id*/) const {
    return (ConstHostCollection());
}

ConstHostCollection
HostCache::getAllbyHostname6(const std::string& /*hostname*/,
                             const dhcp::SubnetID& /*subnet_id*/) const {
    return (ConstHostCollection());
}

dhcp::ConstHostCollection
HostCache::getPage4(const dhcp::SubnetID& /*subnet_id*/,
                    size_t& /*source_index*/,
                    uint64_t /*lower_host_id*/,
                    const dhcp::HostPageSize& /*page_size*/) const {
    return (ConstHostCollection());
}

dhcp::ConstHostCollection
HostCache::getPage6(const dhcp::SubnetID& /*subnet_id*/,
                    size_t& /*source_index*/,
                    uint64_t /*lower_host_id*/,
                    const dhcp::HostPageSize& /*page_size*/) const {
    return (ConstHostCollection());
}

dhcp::ConstHostCollection
HostCache::getPage4(size_t& /*source_index*/,
                    uint64_t /*lower_host_id*/,
                    const dhcp:: HostPageSize& /*page_size*/) const {
    return (ConstHostCollection());
}

dhcp::ConstHostCollection
HostCache::getPage6(size_t& /*source_index*/,
                    uint64_t /*lower_host_id*/,
                    const dhcp::HostPageSize& /*page_size*/) const {
    return (ConstHostCollection());
}

ConstHostCollection
HostCache::getAll4(const asiolink::IOAddress& /*address*/) const {
    return (ConstHostCollection());
}

ConstHostPtr
HostCache::get4(const dhcp::SubnetID& subnet_id,
                const dhcp::Host::IdentifierType& identifier_type,
                const uint8_t* identifier_begin,
                const size_t identifier_len) const {
    LOG_DEBUG(host_cache_logger, HOST_CACHE_DBG_TRACE,
              HOST_CACHE_GET_ONE_SUBNET_ID_IDENTIFIER)
        .arg("IPv4")
        .arg(subnet_id)
        .arg(Host::getIdentifierAsText(identifier_type, identifier_begin,
                                       identifier_len));

    ConstHostPtr host;
    {
        MultiThreadingLock lock(*mutex_);
        host = impl_->get4(subnet_id, identifier_type,
                           identifier_begin, identifier_len);
    }
    if (host) {
        LOG_DEBUG(host_cache_logger, HOST_CACHE_DBG_RESULTS,
                  HOST_CACHE_GET_ONE_SUBNET_ID_IDENTIFIER_HOST)
            .arg(subnet_id)
            .arg(Host::getIdentifierAsText(identifier_type, identifier_begin,
                                           identifier_len))
            .arg(host->toText());
    }
    return (host);
}

ConstHostPtr
HostCache::get4(const dhcp::SubnetID& subnet_id,
                const asiolink::IOAddress& address) const {
    LOG_DEBUG(host_cache_logger, HOST_CACHE_DBG_TRACE,
              HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS4)
        .arg(subnet_id)
        .arg(address.toText());

    // Must not specify address other than IPv4.
    if (!address.isV4()) {
        return (ConstHostPtr());
    }
    ConstHostPtr host;
    {
        MultiThreadingLock lock(*mutex_);
        host = impl_->get4(subnet_id, address);
    }
    if (host) {
        LOG_DEBUG(host_cache_logger, HOST_CACHE_DBG_RESULTS,
                  HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS4_HOST)
            .arg(subnet_id)
            .arg(address.toText())
            .arg(host->toText());
    }
    return (host);
}

ConstHostCollection
HostCache::getAll4(const dhcp::SubnetID& /*subnet_id*/,
                   const asiolink::IOAddress& /*address*/) const {
    return (ConstHostCollection());
}

ConstHostPtr
HostCache::get6(const dhcp::SubnetID& subnet_id,
                const dhcp::Host::IdentifierType& identifier_type,
                const uint8_t* identifier_begin,
                const size_t identifier_len) const {
    LOG_DEBUG(host_cache_logger, HOST_CACHE_DBG_TRACE,
              HOST_CACHE_GET_ONE_SUBNET_ID_IDENTIFIER)
        .arg("IPv6")
        .arg(subnet_id)
        .arg(Host::getIdentifierAsText(identifier_type, identifier_begin,
                                       identifier_len));

    ConstHostPtr host;
    {
        MultiThreadingLock lock(*mutex_);
        host = impl_->get6(subnet_id, identifier_type,
                           identifier_begin, identifier_len);
    }
    if (host) {
        LOG_DEBUG(host_cache_logger, HOST_CACHE_DBG_RESULTS,
                  HOST_CACHE_GET_ONE_SUBNET_ID_IDENTIFIER_HOST)
            .arg(subnet_id)
            .arg(Host::getIdentifierAsText(identifier_type, identifier_begin,
                                           identifier_len))
            .arg(host->toText());
    }
    return (host);
}

ConstHostPtr
HostCache::get6(const asiolink::IOAddress& prefix,
                const uint8_t prefix_len) const {
    LOG_DEBUG(host_cache_logger, HOST_CACHE_DBG_TRACE,
              HOST_CACHE_GET_ONE_PREFIX)
        .arg(prefix.toText())
        .arg(static_cast<int>(prefix_len));

    ConstHostPtr host;
    {
        MultiThreadingLock lock(*mutex_);
        host = impl_->get6(prefix, prefix_len);
    }
    if (host) {
        LOG_DEBUG(host_cache_logger, HOST_CACHE_DBG_RESULTS,
                  HOST_CACHE_GET_ONE_PREFIX_HOST)
            .arg(prefix.toText())
            .arg(static_cast<int>(prefix_len))
            .arg(host->toText());
    }
    return (host);
}

ConstHostPtr
HostCache::get6(const dhcp::SubnetID& subnet_id,
                const asiolink::IOAddress& address) const {
    LOG_DEBUG(host_cache_logger, HOST_CACHE_DBG_TRACE,
              HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS6)
        .arg(subnet_id)
        .arg(address.toText());

    // Must not specify address other than IPv6.
    if (!address.isV6()) {
        return (ConstHostPtr());
    }

    ConstHostPtr host;
    {
        MultiThreadingLock lock(*mutex_);
        host = impl_->get6(subnet_id, address);
    }
    if (host) {
        LOG_DEBUG(host_cache_logger, HOST_CACHE_DBG_RESULTS,
                  HOST_CACHE_GET_ONE_SUBNET_ID_ADDRESS6_HOST)
            .arg(subnet_id)
            .arg(address.toText())
            .arg(host->toText());
    }
    return (host);
}

ConstHostCollection
HostCache::getAll6(const dhcp::SubnetID& /*subnet_id*/,
                   const asiolink::IOAddress& /*address*/) const {
    return (ConstHostCollection());
}

ConstHostCollection
HostCache::getAll6(const IOAddress& /*address*/) const {
    return (ConstHostCollection());
}

void
HostCache::add(const HostPtr& host) {
    if (!host) {
        return;
    }

    // At least one subnet ID must be used.
    if (host->getIPv4SubnetID() == SUBNET_ID_UNUSED &&
        host->getIPv6SubnetID() == SUBNET_ID_UNUSED) {
        return;
    }

    bool ret;
    {
        MultiThreadingLock lock(*mutex_);
        ret = impl_->add(host);
    }
    if (ret) {
        LOG_DEBUG(host_cache_logger, HOST_CACHE_DBG_RESULTS, HOST_CACHE_ADD)
            .arg(host->toText());
    } else {
        LOG_DEBUG(host_cache_logger, HOST_CACHE_DBG_RESULTS,
                  HOST_CACHE_ADD_DUPLICATE)
            .arg(host->toText());
        isc_throw(DuplicateEntry, "Host cache duplicate entry error");
    }
}

bool
HostCache::del(const SubnetID& subnet_id, const IOAddress& addr) {
    string txt;
    if (addr.isV4()) {
        {
            MultiThreadingLock lock(*mutex_);
            txt = impl_->del4(subnet_id, addr);
        }
        if (!txt.empty()) {
            LOG_DEBUG(host_cache_logger, HOST_CACHE_DBG_RESULTS,
                      HOST_CACHE_DEL_SUBNET_ID_ADDRESS4)
                .arg(subnet_id)
                .arg(addr.toText())
                .arg(txt);
        }
    } else if (addr.isV6()) {
        {
            MultiThreadingLock lock(*mutex_);
            txt = impl_->del6(subnet_id, addr);
        }
        if (!txt.empty()) {
            LOG_DEBUG(host_cache_logger, HOST_CACHE_DBG_RESULTS,
                      HOST_CACHE_DEL_SUBNET_ID_ADDRESS6)
                .arg(subnet_id)
                .arg(addr.toText())
                .arg(txt);
        }
    }
    return (false);
}

bool
HostCache::del4(const SubnetID& subnet_id,
                const Host::IdentifierType& identifier_type,
                const uint8_t* identifier_begin,
                const size_t identifier_len) {
    string txt;
    {
        MultiThreadingLock lock(*mutex_);
        txt = impl_->del4(subnet_id, identifier_type,
                          identifier_begin, identifier_len);
    }
    if (!txt.empty()) {
        LOG_DEBUG(host_cache_logger, HOST_CACHE_DBG_RESULTS,
                  HOST_CACHE_DEL_SUBNET_ID_IDENTIFIER4)
            .arg(subnet_id)
            .arg(Host::getIdentifierAsText(identifier_type,
                                           identifier_begin,
                                           identifier_len))
            .arg(txt);
    }
    return (false);
}

bool
HostCache::del6(const SubnetID& subnet_id,
                const Host::IdentifierType& identifier_type,
                const uint8_t* identifier_begin,
                const size_t identifier_len) {
    string txt;
    {
        MultiThreadingLock lock(*mutex_);
        txt = impl_->del6(subnet_id, identifier_type,
                          identifier_begin, identifier_len);
    }
    if (!txt.empty()) {
        LOG_DEBUG(host_cache_logger, HOST_CACHE_DBG_RESULTS,
                  HOST_CACHE_DEL_SUBNET_ID_IDENTIFIER6)
            .arg(subnet_id)
            .arg(Host::getIdentifierAsText(identifier_type,
                                           identifier_begin,
                                           identifier_len))
            .arg(txt);
    }
    return (false);
}

void
HostCache::update(HostPtr const& host) {
    MultiThreadingLock lock(*mutex_);
    impl_->update(host);
}

bool
HostCache::setIPReservationsUnique(const bool unique) {
    // This backend does not support the mode in which multiple reservations
    // for the same IP address are created. If selecting this mode is
    // attempted this function returns false to indicate that this is
    // not allowed.
    return (unique);
}

ElementPtr
HostCache::toElement() const {
    MultiThreadingLock lock(*mutex_);
    return (impl_->toElement());
}

size_t
HostCache::insert(const ConstHostPtr& host, bool overwrite) {
    MultiThreadingLock lock(*mutex_);
    return (impl_->insert(host, overwrite));
}

bool
HostCache::remove(const HostPtr& host) {
    MultiThreadingLock lock(*mutex_);
    return (impl_->remove(host));
}

void
HostCache::flush(size_t count) {
    MultiThreadingLock lock(*mutex_);
    if (count == 0) {
        impl_->clear();
    } else {
        impl_->flush(count);
    }
}

size_t
HostCache::size() const {
    MultiThreadingLock lock(*mutex_);
    return (impl_->size());
}

size_t
HostCache::capacity() const {
    MultiThreadingLock lock(*mutex_);
    return (impl_->capacity());
}

ConstHostCollection
HostCache::get(const Host::IdentifierType& identifier_type,
               const uint8_t* identifier_begin,
               const size_t identifier_len) const {
    MultiThreadingLock lock(*mutex_);
    return (impl_->get(identifier_type, identifier_begin, identifier_len));
}

int
HostCache::cacheSizeHandler(hooks::CalloutHandle& handle) {
    size_t count;
    try {
        extractCommand(handle);

        MultiThreadingLock lock(*mutex_);
        count = impl_->size();
    } catch (const std::exception& ex) {
        LOG_ERROR(host_cache_logger, HOST_CACHE_COMMAND_SIZE_FAILED)
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(host_cache_logger, HOST_CACHE_COMMAND_SIZE)
        .arg(count);
    ostringstream msg;
    msg << count << " entries.";
    ElementPtr result = Element::createMap();
    result->set("size", Element::create(static_cast<int64_t>(count)));
    ConstElementPtr response =
        createAnswer(CONTROL_RESULT_SUCCESS, msg.str(), result);
    setResponse(handle, response);
    return (0);
}

int
HostCache::cacheClearHandler(hooks::CalloutHandle& handle) {
    MultiThreadingCriticalSection cs;

    try {
        extractCommand(handle);

        impl_->clear();
    } catch (const std::exception& ex) {
        LOG_ERROR(host_cache_logger, HOST_CACHE_COMMAND_CLEAR_FAILED)
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(host_cache_logger, HOST_CACHE_COMMAND_CLEAR);
    setSuccessResponse(handle, "Cache cleared.");
    return (0);
}

int
HostCache::cacheFlushHandler(hooks::CalloutHandle& handle) {
    MultiThreadingCriticalSection cs;

    size_t how_many = 0;
    size_t before = impl_->size();
    string txt = "(missing parameters)";
    try {
        extractCommand(handle);
        if (cmd_args_) {
            txt = cmd_args_->str();
        }

        if (!cmd_args_) {
            isc_throw(BadValue, "no parameters specified for the command");
        }

        int64_t val = cmd_args_->intValue();

        if (val == 0) {
            isc_throw(BadValue, "invalid (0) parameter: "
                      "please use cache-clear command");
        }

        if (val < 0) {
            isc_throw(BadValue, "invalid (<0) parameter");
        }

        if (val > HCConfigParser::MAXIMUM) {
            val = HCConfigParser::MAXIMUM + 1;
        }

        how_many = static_cast<size_t>(val);
        impl_->flush(how_many);
    } catch (const std::exception& ex) {
        LOG_ERROR(host_cache_logger, HOST_CACHE_COMMAND_FLUSH_FAILED)
            .arg(txt)
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(host_cache_logger, HOST_CACHE_COMMAND_FLUSH);
    ostringstream msg;
    msg << "Cache flushed (" << before - impl_->size() << " entries removed).";
    setSuccessResponse(handle, msg.str());
    return (0);
}

int
HostCache::cacheGetHandler(hooks::CalloutHandle& handle) {
    MultiThreadingCriticalSection cs;

    ConstElementPtr dump;
    size_t count = 0;
    try {
        extractCommand(handle);

        dump = impl_->toElement();
        count = dump->size();
    } catch (const std::exception& ex) {
        LOG_ERROR(host_cache_logger, HOST_CACHE_COMMAND_GET_FAILED)
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(host_cache_logger, HOST_CACHE_COMMAND_GET)
        .arg(count);
    ostringstream msg;
    msg << count << " entries returned.";
    ConstElementPtr response =
        createAnswer(count > 0 ? CONTROL_RESULT_SUCCESS : CONTROL_RESULT_EMPTY,
                     msg.str(), dump);
    setResponse(handle, response);
    return (0);
}

int
HostCache::cacheGetByIdHandler(hooks::CalloutHandle& handle) {
    Host::IdentifierType id_type;
    vector<uint8_t> ident;
    string txt = "(missing parameters)";
    ElementPtr result = Element::createList();
    size_t count = 0;
    try {
        extractCommand(handle);
        if (cmd_args_) {
            txt = cmd_args_->str();
        }

        if (!cmd_args_) {
            isc_throw(BadValue, "no parameters specified for the command");
        }

        if (cmd_args_->getType() != Element::map) {
            isc_throw(BadValue, "invalid (not a map) parameter");
        }

        // Take parameters.
        string ident_txt;
        unsigned have_ident = 0;
        auto& map = cmd_args_->mapValue();
        for (auto const& cfg : map) {
            if (cfg.first == "hw-address") {
                id_type = Host::IDENT_HWADDR;
                ++have_ident;
                ident_txt = cfg.second->stringValue();
            } else if (cfg.first == "duid") {
                id_type= Host::IDENT_DUID;
                ++have_ident;
                ident_txt = cfg.second->stringValue();
            } else if (cfg.first == "circuit-id") {
                id_type= Host::IDENT_CIRCUIT_ID;
                ++have_ident;
                ident_txt = cfg.second->stringValue();
            } else if (cfg.first == "client-id") {
                id_type= Host::IDENT_CLIENT_ID;
                ++have_ident;
                ident_txt = cfg.second->stringValue();
            } else if (cfg.first == "flex-id") {
                id_type= Host::IDENT_FLEX;
                ++have_ident;
                ident_txt = cfg.second->stringValue();
            } else {
                isc_throw(BadValue,
                          "unknown parameter '" << cfg.first << "'");
            }
        }

        // Decode parameters.
        if (have_ident == 0) {
            isc_throw(BadValue, "an identifier is required");
        }
        if (have_ident > 1) {
            isc_throw(BadValue, "only one identifier can be specified");
        }
        if (ident_txt.empty()) {
            isc_throw(BadValue, "invalid (empty) identifier");
        }
        try {
            ident = util::str::quotedStringToBinary(ident_txt);
            if (ident.empty()) {
                util::str::decodeFormattedHexString(ident_txt, ident);
            }
        } catch (...) {
            isc_throw(BadValue, "invalid identifier '" << ident_txt << "'");
        }

        // Get the entry list and build the result.
        ConstHostCollection hosts;
        {
            MultiThreadingLock lock(*mutex_);
            hosts = impl_->get(id_type, &ident[0], ident.size());
        }
        for (auto const& host : hosts) {
            result->add(host_cache::toElement(host));
        }
        count = result->size();
    } catch (const std::exception& ex) {
        LOG_ERROR(host_cache_logger, HOST_CACHE_COMMAND_GET_BY_ID_FAILED)
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(host_cache_logger, HOST_CACHE_COMMAND_GET_BY_ID)
        .arg(count);
    ostringstream msg;
    msg << count << " entries returned.";
    ConstElementPtr response =
        createAnswer(count ? CONTROL_RESULT_SUCCESS : CONTROL_RESULT_EMPTY,
                     msg.str(), result);
    setResponse(handle, response);
    return (0);
}

int
HostCache::cacheInsertHandler(hooks::CalloutHandle& handle) {
    string filename;
    size_t count = 0;
    size_t overwritten = 0;
    string txt = "(missing parameters)";
    try {
        extractCommand(handle);
        if (cmd_args_) {
            txt = cmd_args_->str();
        }

        if (!cmd_args_) {
            isc_throw(BadValue, "no parameters specified for the command");
        }

        if (cmd_args_->getType() == Element::map) {
            HCEntryParser parser;
            HostPtr entry = parser.parse(cmd_args_);

            ++count;
            try {
                MultiThreadingLock lock(*mutex_);
                overwritten += impl_->insert(entry, true);
            } catch (const std::exception& ex) {
                isc_throw(BadValue,
                          "Insert host (" << entry->toText()
                          << ") failed: " << ex.what());
            }
        } else {
            HCEntryListParser parser;
            HostCollection entries = parser.parse(cmd_args_);

            for (auto const& entry : entries) {
                ++count;
                try {
                    MultiThreadingLock lock(*mutex_);
                    overwritten += impl_->insert(entry, true);
                } catch (const std::exception& ex) {
                    isc_throw(BadValue, "Insert failed at " << count
                              << " host (" << entry->toText()
                              << "): " << ex.what());
                }
            }
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(host_cache_logger, HOST_CACHE_COMMAND_INSERT_FAILED)
            .arg(txt)
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(host_cache_logger, HOST_CACHE_COMMAND_INSERT)
        .arg(count)
        .arg(overwritten);
    ostringstream msg;
    msg << count << " entries inserted (" << overwritten
        << " overwritten by more recent entries).";
    setSuccessResponse(handle, msg.str());
    return (0);
}

int
HostCache::cacheWriteHandler(hooks::CalloutHandle& handle) {
    MultiThreadingCriticalSection cs;

    ConstElementPtr dump;
    string filename;
    size_t count = 0;
    string txt = "(missing parameters)";
    try {
        extractCommand(handle);
        if (cmd_args_) {
            txt = cmd_args_->str();
        }

        if (!cmd_args_) {
            isc_throw(BadValue, "no parameters specified for the command");
        }

        if (cmd_args_->getType() != Element::string) {
            isc_throw(BadValue, "invalid (not a string) parameter");
        }

        try {
            filename = CfgMgr::instance().validatePath(cmd_args_->stringValue());
        } catch (const std::exception& ex) {
            isc_throw(BadValue, "parameter is invalid: " << ex.what());
        }

        ofstream out(filename, ios::trunc);
        if (!out.good()) {
            isc_throw(Unexpected, "Unable to open file '" << filename
                      << "' for writing.");
        }

        dump = impl_->toElement();
        count = dump->size();
        prettyPrint(dump, out);
        out.close();
    } catch (const std::exception& ex) {
        LOG_ERROR(host_cache_logger, HOST_CACHE_COMMAND_WRITE_FAILED)
            .arg(txt)
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(host_cache_logger, HOST_CACHE_COMMAND_WRITE)
        .arg(count);
    ostringstream msg;
    msg << count << " entries dumped to '" << filename << "'.";
    setSuccessResponse(handle, msg.str());
    return (0);
}

int
HostCache::cacheLoadHandler(hooks::CalloutHandle& handle) {
    MultiThreadingCriticalSection cs;

    string filename;
    size_t count = 0;
    size_t overwritten = 0;
    string txt = "(missing parameters)";
    try {
        extractCommand(handle);
        if (cmd_args_) {
            txt = cmd_args_->str();
        }

        if (!cmd_args_) {
            isc_throw(BadValue, "no parameters specified for the command");
        }

        if (cmd_args_->getType() != Element::string) {
            isc_throw(BadValue, "invalid (not a string) parameter");
        }

        filename = cmd_args_->stringValue();
        if (filename.empty()) {
            isc_throw(BadValue, "invalid (empty string) parameter");
        }

        ConstElementPtr json = Element::fromJSONFile(filename);
        if (!json) {
            isc_throw(Unexpected, "No entries found.");
        }
        HCEntryListParser parser;
        HostCollection entries = parser.parse(json);

        for (auto const& entry : entries) {
            ++count;
            try {
                overwritten += impl_->insert(entry, true);
            } catch (const std::exception& ex) {
                isc_throw(BadValue, "Insert failed at " << count
                          << " host ( " << entry->toText()
                          << "): " << ex.what());
            }
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(host_cache_logger, HOST_CACHE_COMMAND_LOAD_FAILED)
            .arg(txt)
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(host_cache_logger, HOST_CACHE_COMMAND_LOAD)
        .arg(count)
        .arg(overwritten);
    ostringstream msg;
    msg << count << " entries loaded from '" << filename << "' ("
        << overwritten << " overwritten by more recent entries).";
    setSuccessResponse(handle, msg.str());
    return (0);
}

int
HostCache::cacheRemoveHandler(hooks::CalloutHandle& handle) {
    uint16_t family = AF_UNIX;
    SubnetID subnet_id;
    string addr_txt;
    Host::IdentifierType id_type;
    vector<uint8_t> ident;
    string txt = "(missing parameters)";
    string del_txt;
    try {
        extractCommand(handle);
        if (cmd_args_) {
            txt = cmd_args_->str();
        }

        if (!cmd_args_) {
            isc_throw(BadValue, "no parameters specified for the command");
        }

        if (cmd_args_->getType() != Element::map) {
            isc_throw(BadValue, "invalid (not a map) parameter");
        }

        // Take parameters.
        string ident_txt;
        bool have_ident = false;
        bool valid = true;
        auto& map = cmd_args_->mapValue();
        for (auto const& cfg : map) {
            if (cfg.first == "subnet-id") {
                if (family != AF_UNIX) {
                    valid = false;
                }
                family = AF_UNSPEC;
                subnet_id = static_cast<uint32_t>(cfg.second->intValue());
            } else if (cfg.first == "subnet-id4") {
                if (family != AF_UNIX) {
                    valid = false;
                }
                family = AF_INET;
                subnet_id = static_cast<uint32_t>(cfg.second->intValue());
            } else if (cfg.first == "subnet-id6") {
                if (family != AF_UNIX) {
                    valid = false;
                }
                family = AF_INET6;
                subnet_id = static_cast<uint32_t>(cfg.second->intValue());
            } else if (cfg.first == "ip-address") {
                addr_txt = cfg.second->stringValue();
            } else if (cfg.first == "hw-address") {
                id_type = Host::IDENT_HWADDR;
                if (have_ident) {
                    valid = false;
                }
                have_ident = true;
                ident_txt = cfg.second->stringValue();
            } else if (cfg.first == "duid") {
                id_type= Host::IDENT_DUID;
                if (have_ident) {
                    valid = false;
                }
                have_ident = true;
                ident_txt = cfg.second->stringValue();
            } else if (cfg.first == "circuit-id") {
                id_type= Host::IDENT_CIRCUIT_ID;
                if (have_ident) {
                    valid = false;
                }
                have_ident = true;
                ident_txt = cfg.second->stringValue();
            } else if (cfg.first == "client-id") {
                id_type= Host::IDENT_CLIENT_ID;
                if (have_ident) {
                    valid = false;
                }
                have_ident = true;
                ident_txt = cfg.second->stringValue();
            } else if (cfg.first == "flex-id") {
                id_type= Host::IDENT_FLEX;
                if (have_ident) {
                    valid = false;
                }
                have_ident = true;
                ident_txt = cfg.second->stringValue();
            } else {
                isc_throw(BadValue,
                          "unknown parameter '" << cfg.first << "'");
            }
        }

        // Decode parameters.
        IOAddress addr(0);
        if (valid && !addr_txt.empty()) {
            if (have_ident) {
                valid = false;
            }
            if (family == AF_UNIX) {
                isc_throw(BadValue, "subnet-id is required");
            }
            addr = IOAddress(addr_txt);
            if (addr.isV4()) {
                if (family == AF_INET6) {
                    valid = false;
                }
                if (addr.isV4Zero()) {
                    isc_throw(BadValue, "invalid ip-address '0.0.0.0'");
                }
                family = AF_INET;
            } else if (addr.isV6()) {
                if (family == AF_INET) {
                    valid = false;
                }
                if (addr.isV6Zero()) {
                    isc_throw(BadValue, "invalid ip-address '::'");
                }
                family = AF_INET6;
            } else {
                isc_throw(Unexpected,
                          "invalid ip-address '" << addr_txt << "'");
            }
        } else if (valid) {
            if (!have_ident) {
                isc_throw(BadValue,
                          "either ip-address or an identifier is required");
            }
            if (ident_txt.empty()) {
                isc_throw(BadValue, "invalid (empty) identifier");
            }
            if ((family != AF_INET) && (family != AF_INET6)) {
                isc_throw(BadValue,
                          "either subnet-id4 or subnet-id6 is required");
            }
            try {
                ident = util::str::quotedStringToBinary(ident_txt);
                if (ident.empty()) {
                    util::str::decodeFormattedHexString(ident_txt, ident);
                }
            } catch (...) {
                isc_throw(BadValue,
                          "invalid identifier '" << ident_txt << "'");
            }
        }

        // Something is wrong?
        if (!valid) {
            isc_throw(BadValue, "inconsistent parameters");
        }

        // Call del*().
        MultiThreadingLock lock(*mutex_);
        if (!addr_txt.empty()) {
            if (family == AF_INET) {
                del_txt = impl_->del4(subnet_id, addr);
            } else {
                del_txt = impl_->del6(subnet_id, addr);
            }
        } else if (family == AF_INET) {
            del_txt = impl_->del4(subnet_id, id_type, &ident[0], ident.size());
        } else {
            del_txt = impl_->del6(subnet_id, id_type, &ident[0], ident.size());
        }
    } catch (const std::exception& ex) {
        LOG_ERROR(host_cache_logger, HOST_CACHE_COMMAND_REMOVE_FAILED)
            .arg(txt)
            .arg(ex.what());
        setErrorResponse(handle, ex.what());
        return (1);
    }

    LOG_INFO(host_cache_logger, HOST_CACHE_COMMAND_REMOVE)
        .arg(txt);
    if (!del_txt.empty()) {
        setSuccessResponse(handle, "Host removed.");
    } else {
        setErrorResponse(handle, "Host not removed (not found).",
                         CONTROL_RESULT_EMPTY);
    }
    return (0);
}

} // end of namespace isc::host_cache
} // end of namespace isc
