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

#ifndef IFACE_MGR_TEST_CONFIG_H
#define IFACE_MGR_TEST_CONFIG_H

#include <asiolink/io_address.h>
#include <dhcp/iface_mgr.h>
#include <boost/noncopyable.hpp>

namespace isc {
namespace dhcp {
namespace test {

///
/// @name Set of structures describing interface flags.
///
/// These flags encapsulate the boolean type to pass the flags values
/// to @c IfaceMgrTestConfig methods. If the values passed to these methods
/// were not encapsulated by the types defined here, the API would become
/// prone to errors like swapping parameters being passed to specific functions.
/// For example, in the call to @c IfaceMgrTestConfig::setIfaceFlags:
/// @code
///     IfaceMgrTestConfig test_config(true);
///     test_config.setIfaceFlags("eth1", false, false, true, false, false);
/// @endcode
///
/// it is quite likely that the developer by mistake swaps the values and
/// assigns them to wrong flags. When the flags are encapsulated with dedicated
/// structs, the compiler will return an error if values are swapped. For
/// example:
/// @code
///     IfaceMgrTestConfig test_config(true);
///     test_config.setIfaceFlags("eth1", FlagLoopback(false), FlagUp(false),
///                               FlagRunning(true), FlagInactive4(false),
///                               FlagInactive6(false));
/// @endcode
/// will succeed, but the following code will result in the compilation error
/// and thus protect a developer from making an error:
/// @code
///     IfaceMgrTestConfig test_config(true);
///     test_config.setIfaceFlags("eth1", FlagLoopback(false),
///                               FlagRunning(true), FlagUp(false),
///                               FlagInactive4(false), FlagInactive6(false));
/// @endcode
///
//@{
/// @brief Structure describing the loopback interface flag.
struct FlagLoopback {
    explicit FlagLoopback(bool flag) : flag_(flag) { }
    bool flag_;
};

/// @brief Structure describing the up interface flag.
struct FlagUp {
    explicit FlagUp(bool flag) : flag_(flag) { }
    bool flag_;
};

/// @brief Structure describing the running interface flag.
struct FlagRunning {
    explicit FlagRunning(bool flag) : flag_(flag) { }
    bool flag_;
};

/// @brief Structure describing the inactive4 interface flag.
struct FlagInactive4 {
    explicit FlagInactive4(bool flag) : flag_(flag) { }
    bool flag_;
};

/// @brief Structure describing the inactive6 interface flag.
struct FlagInactive6 {
    explicit FlagInactive6(bool flag) : flag_(flag) { }
    bool flag_;
};
//@}

/// @brief Convenience class for configuring @c IfaceMgr for unit testing.
///
/// This class is used by various unit tests which test the code relaying
/// on IfaceMgr. The use of this class is not limited to libdhcp++ validation.
/// There are other libraries and applications (e.g. DHCP servers) which
/// depend on @c IfaceMgr.
///
/// During the normal operation, the @c IfaceMgr detects interfaces present
/// on the machine where it is running. It also provides the means for
/// applications to open sockets on these interfaces and perform other
/// IO operations. This however creates dependency of the applications
/// using @c IfaceMgr on the physical properties of the system and effectively
/// makes it very hard to unit test the dependent code.
///
/// Unit tests usually require that @c IfaceMgr holds a list of well known
/// interfaces with the well known set of IP addresses and other properties
/// (a.k.a. interface flags). The solution which works for many test scenarios
/// is to provide a set of well known fake interfaces, by bypassing the
/// standard interface detection procedure and manually adding @c Iface objects
/// which encapsulate the fake interfaces. As a consequence, it becomes
/// impossible to test IO operations (e.g. sending packets) because real sockets
/// can't be opened on these interfaces. The @c PktFilterTestStub class
/// is used by this class to mimic behavior of IO operations on fake sockets.
///
/// This class provides a set of convenience functions that should be called
/// by unit tests to configure the @c IfaceMgr with fake interfaces.
///
/// The class allows the caller to create custom fake interfaces (with custom
/// IPv4 and IPv6 addresses, flags etc.), but it also provides a default
/// test configuration for interfaces as follows:
/// - lo
///   - 127.0.0.1
///   - ::1
/// - eth0
///   - 10.0.0.1
///   - fe80::3a60:77ff:fed5:cdef
///   - 2001:db8:1::1
/// - eth1
///   - 192.0.2.3
///   - fe80::3a60:77ff:fed5:abcd
///
/// For all interfaces the following flags are set:
/// - multicast
/// - up
/// - running
class IfaceMgrTestConfig : public boost::noncopyable {
public:

    /// @brief Constructor.
    ///
    /// It closes all sockets opened by @c IfaceMgr and removes all interfaces
    /// being used by @c IfaceMgr.
    IfaceMgrTestConfig(const bool default_config = false);

    /// @brief Destructor.
    ///
    /// Closes all currently opened sockets, removes current interfaces and
    /// sets the default packet filtering classes. The default packet filtering
    /// classes are used for IO operations on real sockets/interfaces.
    ///
    /// Destructor also re-detects real interfaces.
    ~IfaceMgrTestConfig();

    /// @brief Adds new IPv4 or IPv6 address to the interface.
    ///
    /// @param iface_name Name of the interface on which new address should
    /// be configured.
    /// @param address IPv4 or IPv6 address to be configured on the interface.
    void addAddress(const std::string& iface_name,
                    const asiolink::IOAddress& address);

    /// @brief Configures new interface for the @c IfaceMgr.
    ///
    /// @param iface Object encapsulating interface to be added.
    void addIface(const IfacePtr& iface);

    /// @brief Configures new interface for the @c IfaceMgr.
    ///
    /// @param name Name of the new interface.
    /// @param ifindex Index for a new interface.
    void addIface(const std::string& name, const int ifindex);

    /// @brief Create an object representing interface.
    ///
    /// Apart from creating an interface, this function also sets the
    /// interface flags:
    /// - loopback flag if interface name is "lo"
    /// - up always true
    /// - running always true
    /// - inactive4 set to false for non-loopback interface
    /// - inactive6 set to false for non-loopback interface
    /// - multicast always to true
    /// - broadcast always to false
    ///
    /// If one needs to modify the default flag settings, the setIfaceFlags
    /// function should be used.
    ///
    /// @param name A name of the interface to be created.
    /// @param ifindex An index of the interface to be created.
    ///
    /// @return An object representing interface.
    static IfacePtr createIface(const std::string& name, const int ifindex);

    /// @brief Creates a default (example) set of fake interfaces.
    void createIfaces();

    /// @brief Returns currently used packet filter for DHCPv4.
    PktFilterPtr getPacketFilter4() const {
        return (packet_filter4_);
    }

    /// @brief Sets the direct response capability for current packet filter.
    ///
    /// The test uses stub implementation of packet filter object. It is
    /// possible to configure that object to report having a capability
    /// to directly repond to clients which don't have an address yet.
    /// This function sets this property for packet filter object.
    ///
    /// @param direct_resp Value to be set.
    ///
    /// @throw isc::Unexpected if unable to set the property.
    void setDirectResponse(const bool direct_resp);

    /// @brief Sets various flags on the specified interface.
    ///
    /// This function configures interface with new values for flags.
    ///
    /// @param name Interface name.
    /// @param loopback Specifies if interface is a loopback interface.
    /// @param up Specifies if the interface is up.
    /// @param running Specifies if the interface is running.
    /// @param inactive4 Specifies if the interface is inactive for V4
    /// traffic, i.e. @c IfaceMgr opens V4 sockets on this interface.
    /// @param inactive6 Specifies if the interface is inactive for V6
    /// traffic, i.e. @c IfaceMgr opens V6 sockets on this interface.
    void setIfaceFlags(const std::string& name,
                       const FlagLoopback& loopback,
                       const FlagUp& up,
                       const FlagRunning& running,
                       const FlagInactive4& inactive4,
                       const FlagInactive6& inactive6);

    /// @brief Checks if socket of the specified family is opened on interface.
    ///
    /// @param iface_name Interface name.
    /// @param family One of: AF_INET or AF_INET6
    bool socketOpen(const std::string& iface_name, const int family) const;

    /// @brief Checks is socket is opened on the interface and bound to a
    /// specified address.
    ///
    /// @param iface_name Interface name.
    /// @param address Address to which the socket is bound.
    bool socketOpen(const std::string& iface_name,
                    const std::string& address) const;

    /// @brief Checks if unicast socket is opened on interface.
    ///
    /// @param iface_name Interface name.
    bool unicastOpen(const std::string& iface_name) const;


private:
    /// @brief Currently used packet filter for DHCPv4.
    PktFilterPtr packet_filter4_;

    /// @brief Currently used packet filter for DHCPv6.
    PktFilter6Ptr packet_filter6_;
};

};
};
};

#endif // IFACE_MGR_TEST_CONFIG_H
