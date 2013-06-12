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

#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <d2/d_cfg_mgr.h>

#include <stdint.h>
#include <string>

#ifndef D2_CFG_MGR_H
#define D2_CFG_MGR_H

namespace isc {
namespace d2 {

/// @brief  DHCP-DDNS Configuration Context
/// Implements the storage container for configuration context.
/// It provides a single enclosure for the storage of configuration parameters
/// and any other context specific information that needs to be accessible
/// during configuration parsing as well as to the application as a whole.
/// @TODO - add in storage of D2 specific storage like domain-to-dns_server
/// mapping.  This is the initial implementation necessary to integrate
/// configuration management into D2.
class D2CfgContext : public DCfgContextBase {
public:
    /// @brief Constructor
    D2CfgContext();

    /// @brief Destructor
    virtual ~D2CfgContext();

    /// @brief Creates a clone of this context object.
    /// @return returns a raw pointer to the new clone.
    virtual D2CfgContext* clone() {
            return (new D2CfgContext(*this));
    }

protected:
    /// @brief Copy constructor for use by derivations in clone().
    D2CfgContext(const D2CfgContext& rhs);

private:
    /// @brief Private assignment operator to avoid potential for slicing.
    D2CfgContext& operator=(const D2CfgContext& rhs);

    /// @TODO storage for DNS domain-server mapping will be added here
};

/// @brief Pointer to a configuration context.
typedef boost::shared_ptr<D2CfgContext> D2CfgContextPtr;

/// @brief DHCP-DDNS Configuration Manager
///
/// Provides the mechanisms for managing the DHCP-DDNS application's
/// configuration.  This includes services for parsing sets of configuration
/// values, storing the parsed information in its converted form,
/// and retrieving the information on demand.
/// @TODO add in D2 specific parsing
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

protected:
    /// @brief Given an element_id returns an instance of the appropriate
    /// parser.
    /// @TODO The initial implementation simply returns a DebugParser for any
    /// element_id value.  This is sufficient to integrate configuration
    /// management into D2. Specific parsers will be added as the DHCP-DDNS
    /// specific configuration is constructed.
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
