// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef HOST_MGR_H
#define HOST_MGR_H

#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

namespace isc {
namespace dhcp {

/// @brief Host Manager.
///
/// This is a singleton class which provides access to multiple sources of
/// information about static host reservations. These sources are also referred
/// to as host data sources. Each source derives (directly or indirectly) from
/// the @c BaseHostDataSource.
///
/// The @c HostMgr is a central point for providing information about the host
/// reservations. Internally, it relays the queries (calls to the appropriate
/// methods declared in the @c BaseHostDataSource) to the data sources it is
/// connected to. The @c HostMgr is always connected to the server's
/// configuration, accessible through the @c CfgHosts object in the @c CfgMgr.
/// The @c CfgHosts object holds all reservations specified in the DHCP server
/// configuration file. If a particular reservation is not found in the
/// @c CfgHosts object, the @c HostMgr will try to find it using the alternate
/// host data storage. The alternate host data storage is usually a database
/// (e.g. SQL database), accessible through a dedicated host data source
/// object (a.k.a. database backend). This datasource is responsible for
/// managing the connection with the database and forming appropriate queries
/// to retrieve (or update) the information about the reservations.
///
/// The use of the alternate host data source is optional and usually requires
/// additional configuration to be specified by the server administrator.
/// For example, for the SQL database the user's credentials, database address,
/// and database name are required. The @c HostMgr passes these parameters
/// to an appropriate datasource which is responsible for opening a connection
/// and maintaining it.
///
/// It is possible to switch to a different alternate data source or disable
/// the use of the alternate datasource, e.g. as a result of server's
/// reconfiguration. However, the use of the primary host data source (i.e.
/// reservations specified in the configuration file) can't be disabled.
///
/// @todo Implement alternate host data sources: MySQL, PostgreSQL, etc.
class HostMgr : public boost::noncopyable, BaseHostDataSource {
public:

    /// @brief Creates new instance of the @c HostMgr.
    ///
    /// If an instance of the @c HostMgr already exists, it will be replaced
    /// by the new instance. Thus, any instances of the alternate host data
    /// sources will be dropped.
    ///
    /// @param access Host data source access parameters for the alternate
    /// host data source. It holds "keyword=value" pairs, separated by spaces.
    /// The supported values are specific to the alternate data source in use.
    /// However, the "type" parameter will be common and it will specify which
    /// data source is to be used. Currently, no parameters are supported
    /// and the parameter is ignored.
    static void create(const std::string& access = "");

    /// @brief Returns a sole instance of the @c HostMgr.
    ///
    /// This method should be used to retrieve an instance of the @c HostMgr
    /// to be used to gather/manage host reservations. It returns an instance
    /// of the @c HostMgr created by the @c create method. If such instance
    /// doesn't exist yet, it is created using the @c create method with the
    /// default value of the data access string, which configures the host
    /// manager to not use the alternate host data source.
    static HostMgr& instance();

    /// @brief Returns all hosts for the specified HW address or DUID.
    ///
    /// This method returns all @c Host objects representing reservations for
    /// the specified HW address or/and DUID as documented in the
    /// @c BaseHostDataSource::getAll.
    ///
    /// It retrieves reservations from both primary and alternate host data
    /// source as a single collection of @c Host objects, i.e. if matching
    /// reservations are in both sources, all of them are returned.
    ///
    /// Note that returned collection may contain duplicates. It is the
    /// caller's responsibility to check for duplicates.
    ///
    /// @param hwaddr HW address of the client or NULL if no HW address
    /// available.
    /// @param duid client id or NULL of not available.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAll(const HWAddrPtr& hwaddr, const DuidPtr& duid = DuidPtr()) const;

    /// @brief Returns a collection of hosts using the specified IPv4 address.
    ///
    /// This method may return multiple @c Host objects if they are connected to
    /// different subnets.
    ///
    /// If matching reservations are both in the primary and the alternate
    /// data source, all of them are returned.
    ///
    /// @param address IPv4 address for which the @c Host object is searched.
    ///
    /// @return Collection of const @c Host objects.
    virtual ConstHostCollection
    getAll4(const asiolink::IOAddress& address) const;

    /// @brief Returns a host connected to the IPv4 subnet.
    ///
    /// This method returns a single reservation for the particular host
    /// (identified by the HW address or DUID) as documented in the
    /// @c BaseHostDataSource::get4.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param hwaddr HW address of the client or NULL if no HW address
    /// available.
    /// @param duid client id or NULL if not available.
    ///
    /// @return Const @c Host object using a specified HW address or DUID.
    virtual ConstHostPtr
    get4(const SubnetID& subnet_id, const HWAddrPtr& hwaddr,
         const DuidPtr& duid = DuidPtr()) const;

    /// @brief Returns a host connected to the IPv6 subnet.
    ///
    /// This method returns a host connected to the IPv6 subnet and identified
    /// by the HW address or DUID, as described in the
    /// @c BaseHostDataSource::get6.
    ///
    /// @param subnet_id Subnet identifier.
    /// @param hwaddr HW address of the client or NULL if no HW address
    /// available.
    /// @param duid DUID or NULL if not available.
    ///
    /// @return Const @c Host object using a specified HW address or DUID.
    virtual ConstHostPtr
    get6(const SubnetID& subnet_id, const DuidPtr& duid,
         const HWAddrPtr& hwaddr = HWAddrPtr()) const;

    /// @brief Returns a host using the specified IPv6 prefix.
    ///
    /// This method returns a host using specified IPv6 prefix, as described
    /// in the @c BaseHostDataSource::get6.
    ///
    /// @param prefix IPv6 prefix for which the @c Host object is searched.
    /// @param prefix_len IPv6 prefix length.
    ///
    /// @return Const @c Host object using a specified HW address or DUID.
    virtual ConstHostPtr
    get6(const asiolink::IOAddress& prefix, const uint8_t prefix_len) const;

    /// @brief Adds a new host to the alternate data source.
    ///
    /// This method will throw an exception if no alternate data source is
    /// in use.
    ///
    /// @param host Pointer to the new @c Host object being added.
    virtual void add(const HostPtr& host);

private:

    /// @brief Private default constructor.
    HostMgr() { }

    /// @brief Pointer to an alternate host data source.
    ///
    /// If this pointer is NULL, the source is not in use.
    boost::scoped_ptr<BaseHostDataSource> alternate_source;

    /// @brief Returns a pointer to the currently used instance of the
    /// @c HostMgr.
    static boost::scoped_ptr<HostMgr>& getHostMgrPtr();

};
}
}

#endif // HOST_MGR_H
