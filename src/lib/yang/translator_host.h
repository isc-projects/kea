// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_TRANSLATOR_HOST_H
#define ISC_TRANSLATOR_HOST_H 1

#include <yang/translator_option_data.h>
#include <list>

namespace isc {
namespace yang {

/// Translation between YANG and JSON for a single host reservation.
///
/// JSON syntax for kea-dhcp4 is:
/// @code
/// {
///     "hw-address": <hardware address>,
///     "duid": <duid>,
///     "circuit-id": <circuit id>,
///     "client-id": <client id>,
///     "flex-id": <flex id>,
///     "ip-address": <ipv4 reserved address>,
///     "hostname": <hostname>,
///     "next-server": "<next server>",
///     "server-hostname": "<server hostname>",
///     "boot-file-name": "<boot file name>",
///     "client-classes": "<client class names>",
///     "option-data": [ <list of option data> ],
///     "user-context": { <json map> },
///     "comment": "<comment>"
/// }
/// @endcode
///
/// JSON syntax for kea-dhcp6 is:
/// @code
/// {
///     "hw-address": <hardware address>,
///     "duid": <duid>,
///     "flex-id": <flex id>,
///     "ip-addresses": <ipv6 reserved addresses>,
///     "prefixes": <ipv6 reserved prefixes>,
///     "hostname": <hostname>,
///     "client-classes": "<client class names>",
///     "option-data": [ <list of option data> ],
///     "user-context": { <json map> },
///     "comment": "<comment>"
/// }
/// @endcode
///
/// YANG syntax for kea-dhcp[46] is with identifier-type and identifier
/// as the list keys:
/// @code
/// +--rw identifier-type          enumeration
/// +--rw identifier               string
/// +--rw hostname?                string
/// +--rw option-data*
/// +--rw client-classes*          string
/// +--rw user-context?            string
/// (DHCPv4 only)
/// +--rw ip-address?              inet:ipv4-address
/// +--rw next-server?             inet:ipv4-address
/// +--rw server-hostname?         string
/// +--rw boot-file-name?          string
/// (DHCPv6 only)
/// +--rw ip-addresses*            inet:ipv6-address
/// +--rw prefixes*                inet:ipv6-prefix
/// @endcode
///
/// An example in JSON and YANG formats:
/// @code
/// [
///     {
///         "flex-id": "00:ff",
///         "ip-address": "10.0.0.1",
///         "hostname": "foo"
///     }
/// ]
/// @endcode
/// @code
///  /kea-dhcp4-server:config (container)
///  /kea-dhcp4-server:config/subnet4[id='111'] (list instance)
///  /kea-dhcp4-server:config/subnet4[id='111']/id = 111
///  /kea-dhcp4-server:config/subnet4[id='111']/subnet = 10.0.0.0/24
///  /kea-dhcp4-server:config/subnet4[id='111']/
///     host[identifier-type='flex-id'][identifier='00:ff'] (list instance)
///  /kea-dhcp4-server:config/subnet4[id='111']/
///     host[identifier-type='flex-id'][identifier='00:ff']/
///     identifier-type = flex-id
///  /kea-dhcp4-server:config/subnet4[id='111']/
///     host[identifier-type='flex-id'][identifier='00:ff']/
///     identifier = 00:ff
///  /kea-dhcp4-server:config/subnet4[id='111']/
///     host[identifier-type='flex-id'][identifier='00:ff']/
///     hostname = foo
///  /kea-dhcp4-server:config/subnet4[id='111']/
///     host[identifier-type='flex-id'][identifier='00:ff']/
///     ip-address = 10.0.0.1
/// @endcode

/// @brief A translator class for converting a host reservation between
/// YANG and JSON.
///
/// Currently supported models are:
/// - kea-dhcp4-server
/// - kea-dhcp6-server
///
/// ietf-dhcpv6-server is not supported yet.
class TranslatorHost : virtual public TranslatorOptionDataList {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorHost(sysrepo::S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorHost();

    /// @brief Get and translate a host reservation from YANG to JSON.
    ///
    /// @param xpath The xpath of the host reservation.
    /// @return JSON representation of the host reservation.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getHost(const std::string& xpath);

    /// @brief Translate and set host reservation from JSON to YANG.
    ///
    /// @param xpath The xpath of the host reservation.
    /// @param elem The JSON element.
    void setHost(const std::string& xpath, isc::data::ConstElementPtr elem);

protected:
    /// @brief getHost for kea-dhcp[46]-server models.
    ///
    /// @param xpath The xpath of the host reservation.
    /// @return JSON representation of the host reservation.
    isc::data::ElementPtr getHostKea(const std::string& xpath);

    /// @brief setHost for kea-dhcp[46]-server models.
    ///
    /// @param xpath The xpath of the host reservation.
    /// @param elem The JSON element.
    void setHostKea(const std::string& xpath, isc::data::ConstElementPtr elem);
};

/// @brief A translator class for converting host reservations list between
/// YANG and JSON.
///
/// Currently supports the following models:
/// - kea-dhcp4-server
/// - kea-dhcp6-server
///
/// The ietf-dhcpv6-server model is not yet supported.
class TranslatorHosts : virtual public TranslatorHost {
public:

    /// @brief Constructor.
    ///
    /// @param session Sysrepo session.
    /// @param model Model name.
    TranslatorHosts(sysrepo::S_Session session, const std::string& model);

    /// @brief Destructor.
    virtual ~TranslatorHosts();

    /// @brief Get and translate host reservations from YANG to JSON.
    ///
    /// @param xpath The xpath of the host reservation list.
    /// @throw SysrepoError when sysrepo raises an error.
    isc::data::ElementPtr getHosts(const std::string& xpath);

    /// @brief Translate and set (address) host reservations from JSON to YANG.
    ///
    /// @param xpath The xpath of the host reservation list.
    /// @param elem The JSON element.
    void setHosts(const std::string& xpath, isc::data::ConstElementPtr elem);

protected:
    /// @brief setHosts for kea-dhcp[46].
    ///
    /// @param xpath The xpath of the host reservation list.
    /// @param elem The JSON element.
    /// @throw BadValue on host reservation without known identifier type.
    void setHostsKea(const std::string& xpath,
                     isc::data::ConstElementPtr elem);
};

}  // namespace yang
}  // namespace isc

#endif // ISC_TRANSLATOR_HOST_H
