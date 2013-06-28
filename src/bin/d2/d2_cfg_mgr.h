// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef D2_CFG_MGR_H
#define D2_CFG_MGR_H

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <d2/d_cfg_mgr.h>
#include <d2/d2_config.h>

#include <stdint.h>
#include <string>

namespace isc {
namespace d2 {

/// @brief  DHCP-DDNS Configuration Context
///
/// Implements the storage container for configuration context.
/// It provides a single enclosure for the storage of configuration parameters
/// and any other DHCP-DDNS specific information that needs to be accessible
/// during configuration parsing as well as to the application as a whole.
/// It is derived from the context base class, DCfgContextBase.
class D2CfgContext : public DCfgContextBase {
public:
    /// @brief Constructor
    D2CfgContext();

    /// @brief Destructor
    virtual ~D2CfgContext();

    /// @brief Creates a clone of this context object.
    ///
    /// @return returns a raw pointer to the new clone.
    virtual D2CfgContext* clone() {
        return (new D2CfgContext(*this));
    }

    /// @brief Fetches the forward DNS domain list manager.
    ///
    /// @return returns a pointer to the forward manager.
    DdnsDomainListMgrPtr getForwardMgr() {
        return (forward_mgr_);
    }

    /// @brief Fetches the reverse DNS domain list manager.
    ///
    /// @return returns a pointer to the reverse manager.
    DdnsDomainListMgrPtr getReverseMgr() {
        return (reverse_mgr_);
    }

    /// @brief Fetches the map of TSIG keys.
    ///
    /// @return returns a pointer to the key map.
    TSIGKeyInfoMapPtr getKeys() {
        return (keys_);
    }

protected:
    /// @brief Copy constructor for use by derivations in clone().
    D2CfgContext(const D2CfgContext& rhs);

private:
    /// @brief Private assignment operator to avoid potential for slicing.
    D2CfgContext& operator=(const D2CfgContext& rhs);

    /// @brief Forward domain list manager.
    DdnsDomainListMgrPtr forward_mgr_;

    /// @brief Reverse domain list manager.
    DdnsDomainListMgrPtr reverse_mgr_;

    /// @brief Storage for the map of TSIGKeyInfos
    TSIGKeyInfoMapPtr keys_;
};

/// @brief Defines a pointer for DdnsDomain instances.
typedef boost::shared_ptr<DdnsDomainListMgr> DdnsDomainListMgrPtr;


/// @brief Pointer to a configuration context.
typedef boost::shared_ptr<D2CfgContext> D2CfgContextPtr;

/// @brief DHCP-DDNS Configuration Manager
///
/// Provides the mechanisms for managing the DHCP-DDNS application's
/// configuration.  This includes services for parsing sets of configuration
/// values, storing the parsed information in its converted form,
/// and retrieving the information on demand.
class D2CfgMgr : public DCfgMgrBase {
public:
    /// @brief Constructor
    ///
    /// @param context is a pointer to the configuration context the manager
    D2CfgMgr();

    /// @brief Destructor
    virtual ~D2CfgMgr();

    /// @brief Convenience method that returns the D2 configuration context.
    ///
    /// @return returns a pointer to the configuration context.
    D2CfgContextPtr getD2CfgContext() {
        return (boost::dynamic_pointer_cast<D2CfgContext>(getContext()));
    }

    /// @brief Matches a given FQDN to a forward domain.
    /// 
    /// This calls the matchDomain method of the forward domain manager to
    /// match the given FQDN to a forward domain.  
    ///
    /// @param fqdn is the name for which to look.
    /// @param domain receives the matching domain. Note that it will be reset
    /// upon entry and only set if a match is subsequently found.
    ///
    /// @return returns true if a match is found, false otherwise.
    /// @throw throws D2CfgError if given an invalid fqdn. 
    bool matchForward(const std::string& fdqn, DdnsDomainPtr &domain);

    /// @brief Matches a given FQDN to a reverse domain.
    ///
    /// This calls the matchDomain method of the reverse domain manager to
    /// match the given FQDN to a forward domain.  
    ///
    /// @param fqdn is the name for which to look.
    /// @param domain receives the matching domain. Note that it will be reset
    /// upon entry and only set if a match is subsequently found.
    ///
    /// @return returns true if a match is found, false otherwise.
    /// @throw throws D2CfgError if given an invalid fqdn. 
    bool matchReverse(const std::string& fdqn, DdnsDomainPtr &domain);

protected:
    /// @brief Given an element_id returns an instance of the appropriate
    /// parser.
    ///
    /// It is responsible for top-level or outermost DHCP-DDNS configuration
    /// elements (see dhcp-ddns.spec):
    ///     1. interface
    ///     2. ip_address
    ///     3. port
    ///     4. forward_ddns
    ///     5. reverse_ddns
    ///
    /// @param element_id is the string name of the element as it will appear
    /// in the configuration set.
    ///
    /// @return returns a ParserPtr to the parser instance.
    /// @throw throws DCfgMgrBaseError if an error occurs.
    virtual isc::dhcp::ParserPtr
    createConfigParser(const std::string& element_id);
};

/// @brief Defines a shared pointer to D2CfgMgr.
typedef boost::shared_ptr<D2CfgMgr> D2CfgMgrPtr;


}; // end of isc::d2 namespace
}; // end of isc namespace

#endif // D2_CFG_MGR_H
