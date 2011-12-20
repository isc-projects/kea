// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#include <set>
#include <string>
#include <utility>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>

#include <dns/name.h>
#include <dns/rrclass.h>

#include <cc/data.h>

#include <datasrc/memory_datasrc.h>
#include <datasrc/zonetable.h>

#include <auth/auth_srv.h>
#include <auth/auth_config.h>
#include <auth/common.h>

#include <server_common/portconfig.h>

using namespace std;
using namespace isc::dns;
using namespace isc::data;
using namespace isc::datasrc;
using namespace isc::server_common::portconfig;

namespace {
// Forward declaration
AuthConfigParser*
createAuthConfigParser(AuthSrv& server, const std::string& config_id,
                       bool internal);

/// A derived \c AuthConfigParser class for the "datasources" configuration
/// identifier.
class DatasourcesConfig : public AuthConfigParser {
public:
    DatasourcesConfig(AuthSrv& server) : server_(server) {}
    virtual void build(ConstElementPtr config_value);
    virtual void commit();
private:
    AuthSrv& server_;
    vector<boost::shared_ptr<AuthConfigParser> > datasources_;
    set<string> configured_sources_;
};

/// A derived \c AuthConfigParser for the version value
/// (which is not used at this moment)
class VersionConfig : public AuthConfigParser {
public:
    VersionConfig() {}
    virtual void build(ConstElementPtr) {};
    virtual void commit() {};
};

void
DatasourcesConfig::build(ConstElementPtr config_value) {
    BOOST_FOREACH(ConstElementPtr datasrc_elem, config_value->listValue()) {
        // The caller is supposed to perform syntax-level checks, but we'll
        // do minimum level of validation ourselves so that we won't crash due
        // to a buggy application.
        ConstElementPtr datasrc_type = datasrc_elem->get("type");
        if (!datasrc_type) {
            isc_throw(AuthConfigError, "Missing data source type");
        }

        if (configured_sources_.find(datasrc_type->stringValue()) !=
            configured_sources_.end()) {
            isc_throw(AuthConfigError, "Data source type '" <<
                      datasrc_type->stringValue() << "' already configured");
        }
        
        boost::shared_ptr<AuthConfigParser> datasrc_config =
            boost::shared_ptr<AuthConfigParser>(
                createAuthConfigParser(server_, string("datasources/") +
                                       datasrc_type->stringValue(),
                                       true));
        datasrc_config->build(datasrc_elem);
        datasources_.push_back(datasrc_config);

        configured_sources_.insert(datasrc_type->stringValue());
    }
}

void
DatasourcesConfig::commit() {
    // XXX a short term workaround: clear all data sources and then reset
    // to new ones so that we can remove data sources that don't exist in
    // the new configuration and have been used in the server.
    // This could be inefficient and requires knowledge about
    // server implementation details, and isn't scalable wrt the number of
    // data source types, and should eventually be improved.
    // Currently memory data source for class IN is the only possibility.
    server_.setInMemoryClient(RRClass::IN(), AuthSrv::InMemoryClientPtr());

    BOOST_FOREACH(boost::shared_ptr<AuthConfigParser> datasrc_config,
                  datasources_) {
        datasrc_config->commit();
    }
}

/// A derived \c AuthConfigParser class for the memory type datasource
/// configuration.  It does not correspond to the configuration syntax;
/// it's instantiated for internal use.
class MemoryDatasourceConfig : public AuthConfigParser {
public:
    MemoryDatasourceConfig(AuthSrv& server) :
        server_(server),
        rrclass_(0)              // XXX: dummy initial value
    {}
    virtual void build(ConstElementPtr config_value);
    virtual void commit() {
        server_.setInMemoryClient(rrclass_, memory_client_);
    }
private:
    AuthSrv& server_;
    RRClass rrclass_;
    AuthSrv::InMemoryClientPtr memory_client_;
};

void
MemoryDatasourceConfig::build(ConstElementPtr config_value) {
    // XXX: apparently we cannot retrieve the default RR class from the
    // module spec.  As a temporary workaround we hardcode the default value.
    ConstElementPtr rrclass_elem = config_value->get("class");
    rrclass_ = RRClass(rrclass_elem ? rrclass_elem->stringValue() : "IN");

    // We'd eventually optimize building zones (in case of reloading) by
    // selectively loading fresh zones.  Right now we simply check the
    // RR class is supported by the server implementation.
    server_.getInMemoryClient(rrclass_);
    memory_client_ = AuthSrv::InMemoryClientPtr(new InMemoryClient());

    ConstElementPtr zones_config = config_value->get("zones");
    if (!zones_config) {
        // XXX: Like the RR class, we cannot retrieve the default value here,
        // so we assume an empty zone list in this case.
        return;
    }

    BOOST_FOREACH(ConstElementPtr zone_config, zones_config->listValue()) {
        ConstElementPtr origin = zone_config->get("origin");
        if (!origin) {
            isc_throw(AuthConfigError, "Missing zone origin");
        }
        ConstElementPtr file = zone_config->get("file");
        if (!file) {
            isc_throw(AuthConfigError, "Missing zone file for zone: "
                      << origin->str());
        }
        boost::shared_ptr<InMemoryZoneFinder> zone_finder(new
                                                   InMemoryZoneFinder(rrclass_,
            Name(origin->stringValue())));
        const result::Result result = memory_client_->addZone(zone_finder);
        if (result == result::EXIST) {
            isc_throw(AuthConfigError, "zone "<< origin->str()
                      << " already exists");
        }

        /*
         * TODO: Once we have better reloading of configuration (something
         * else than throwing everything away and loading it again), we will
         * need the load method to be split into some kind of build and
         * commit/abort parts.
         */
        zone_finder->load(file->stringValue());
    }
}

/// A derived \c AuthConfigParser class for the "statistics-internal"
/// configuration identifier.
class StatisticsIntervalConfig : public AuthConfigParser {
public:
    StatisticsIntervalConfig(AuthSrv& server) :
        server_(server), interval_(0)
    {}
    virtual void build(ConstElementPtr config_value) {
        const int32_t config_interval = config_value->intValue();
        if (config_interval < 0) {
            isc_throw(AuthConfigError, "Negative statistics interval value: "
                      << config_interval);
        }
        if (config_interval > 86400) {
            isc_throw(AuthConfigError, "Statistics interval value "
                      << config_interval
                      << " must be equal to or shorter than 86400");
        }
        interval_ = config_interval;
    }
    virtual void commit() {
        // setStatisticsTimerInterval() is not 100% exception free.  But
        // exceptions should happen only in a very rare situation, so we
        // let them be thrown and subsequently regard them as a fatal error.
        server_.setStatisticsTimerInterval(interval_);
    }
private:
    AuthSrv& server_;
    uint32_t interval_;
};

/// A special parser for testing: it throws from commit() despite the
/// suggested convention of the class interface.
class ThrowerCommitConfig : public AuthConfigParser {
public:
    virtual void build(ConstElementPtr) {} // ignore param, do nothing
    virtual void commit() {
        throw 10;
    }
};

/**
 * \brief Configuration parser for listen_on.
 *
 * It parses and sets the listening addresses of the server.
 *
 * It acts in unusual way. Since actually binding (changing) the sockets
 * is an operation that is expected to throw often, it shouldn't happen
 * in commit. Thefere we do it in build. But if the config is not committed
 * then, we would have it wrong. So we store the old addresses and if
 * commit is not called before destruction of the object, we return the
 * old addresses (which is the same kind of dangerous operation, but it is
 * expected that if we just managed to bind some and had the old ones binded
 * before, it should work).
 *
 * We might do something better in future (like open only the ports that are
 * extra, put them in in commit and close the old ones), but that's left out
 * for now.
 */
class ListenAddressConfig : public AuthConfigParser {
public:
    ListenAddressConfig(AuthSrv& server) :
        server_(server)
    { }
    ~ ListenAddressConfig() {
        if (rollbackAddresses_.get() != NULL) {
            server_.setListenAddresses(*rollbackAddresses_);
        }
    }
private:
    typedef auto_ptr<AddressList> AddrListPtr;
public:
    virtual void build(ConstElementPtr config) {
        AddressList newAddresses = parseAddresses(config, "listen_on");
        AddrListPtr old(new AddressList(server_.getListenAddresses()));
        server_.setListenAddresses(newAddresses);
        /*
         * Set the rollback addresses only after successful setting of the
         * new addresses, so we don't try to rollback if the setup is
         * unsuccessful (the above can easily throw).
         */
        rollbackAddresses_ = old;
    }
    virtual void commit() {
        rollbackAddresses_.release();
    }
private:
    AuthSrv& server_;
    /**
     * This is the old address list, if we expect to roll back. When we commit,
     * this is set to NULL.
     */
    AddrListPtr rollbackAddresses_;
};

// This is a generalized version of create function that can create
// an AuthConfigParser object for "internal" use.
AuthConfigParser*
createAuthConfigParser(AuthSrv& server, const std::string& config_id,
                       bool internal)
{
    // For the initial implementation we use a naive if-else blocks for
    // simplicity.  In future we'll probably generalize it using map-like
    // data structure, and may even provide external register interface so
    // that it can be dynamically customized.
    if (config_id == "datasources") {
        return (new DatasourcesConfig(server));
    } else if (config_id == "statistics-interval") {
        return (new StatisticsIntervalConfig(server));
    } else if (internal && config_id == "datasources/memory") {
        return (new MemoryDatasourceConfig(server));
    } else if (config_id == "listen_on") {
        return (new ListenAddressConfig(server));
    } else if (config_id == "_commit_throw") {
        // This is for testing purpose only and should not appear in the
        // actual configuration syntax.  While this could crash the caller
        // as a result, the server implementation is expected to perform
        // syntax level validation and should be safe in practice.  In future,
        // we may introduce dynamic registration of configuration parsers,
        // and then this test can be done in a cleaner and safer way.
        return (new ThrowerCommitConfig());
    } else if (config_id == "version") {
        // Currently, the version identifier is ignored, but it should
        // later be used to mark backwards incompatible changes in the
        // config data
        return (new VersionConfig());
    } else {
        isc_throw(AuthConfigError, "Unknown configuration identifier: " <<
                  config_id);
    }
}
} // end of unnamed namespace

AuthConfigParser*
createAuthConfigParser(AuthSrv& server, const std::string& config_id) {
    return (createAuthConfigParser(server, config_id, false));
}

void
configureAuthServer(AuthSrv& server, ConstElementPtr config_set) {
    if (!config_set) {
        isc_throw(AuthConfigError,
                  "Null pointer is passed to configuration parser");
    }

    typedef boost::shared_ptr<AuthConfigParser> ParserPtr;
    vector<ParserPtr> parsers;
    typedef pair<string, ConstElementPtr> ConfigPair;
    try {
        BOOST_FOREACH(ConfigPair config_pair, config_set->mapValue()) {
            // We should eventually integrate the sqlite3 DB configuration to
            // this framework, but to minimize diff we begin with skipping that
            // part.
            if (config_pair.first == "database_file") {
                continue;
            }

            ParserPtr parser(createAuthConfigParser(server,
                                                    config_pair.first));
            parser->build(config_pair.second);
            parsers.push_back(parser);
        }
    } catch (const AuthConfigError& ex) {
        throw;                  // simply rethrowing it
    } catch (const isc::Exception& ex) {
        isc_throw(AuthConfigError, "Server configuration failed: " <<
                  ex.what());
    }

    try {
        BOOST_FOREACH(ParserPtr parser, parsers) {
            parser->commit();
        }
    } catch (...) {
        throw FatalError("Unrecoverable error: "
                         "a configuration parser threw in commit");
    }
}
