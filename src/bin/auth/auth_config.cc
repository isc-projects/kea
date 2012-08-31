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

#include <dns/name.h>
#include <dns/rrclass.h>

#include <cc/data.h>

#include <datasrc/memory_datasrc.h>
#include <datasrc/zonetable.h>
#include <datasrc/factory.h>

#include <auth/auth_srv.h>
#include <auth/auth_config.h>
#include <auth/common.h>

#include <server_common/portconfig.h>

#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>

#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;
using namespace isc::dns;
using namespace isc::data;
using namespace isc::datasrc;
using namespace isc::server_common::portconfig;

namespace {

/// A derived \c AuthConfigParser for the version value
/// (which is not used at this moment)
class VersionConfig : public AuthConfigParser {
public:
    VersionConfig() {}
    virtual void build(ConstElementPtr) {};
    virtual void commit() {};
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
} // end of unnamed namespace

AuthConfigParser*
createAuthConfigParser(AuthSrv& server, const std::string& config_id) {
    // For the initial implementation we use a naive if-else blocks for
    // simplicity.  In future we'll probably generalize it using map-like
    // data structure, and may even provide external register interface so
    // that it can be dynamically customized.
    if (config_id == "listen_on") {
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
    } else if (config_id == "datasources") {
        // TODO: Ignored for now, since the value is probably used by
        // other modules. Once they have been removed from there, remove
        // it from here and the spec file.

        // We need to return something. The VersionConfig is empty now,
        // so we may abuse that one, as it is a short-term solution only.
        return (new VersionConfig());
    } else {
        isc_throw(AuthConfigError, "Unknown configuration identifier: " <<
                  config_id);
    }
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
