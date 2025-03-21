// Copyright (C) 2017-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SUBNET_CMDS_H
#define SUBNET_CMDS_H

#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <dhcpsrv/subnet_id.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace subnet_cmds {

class SubnetCmdsImpl;

/// @brief Implements the logic for processing commands pertaining to
/// subnets manipulation.
///
/// This class is used by the callouts implementing command handlers for
/// subnets manipulations.
class SubnetCmds {
public:

    /// @brief Constructor.
    ///
    /// It creates an instance of the @c SubnetCmdsImpl.
    SubnetCmds();

    /// @brief Returns a response to a 'subnet4-list' command.
    ///
    /// This method retrieves configured IPv4 subnets and returns them within
    /// a command response. The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "2 IPv4 subnets found",
    ///     "arguments": {
    ///         "subnets": [
    ///             {
    ///                 "id": 10,
    ///                 "subnet": "10.0.0.0/8"
    ///             },
    ///             {
    ///                 "id": 100,
    ///                 "subnet": "192.0.2.0/24"
    ///             }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a response to the command.
    data::ConstElementPtr getSubnet4List() const;

    /// @brief Returns a response to a 'subnet6-list' command.
    ///
    /// This method retrieves configured IPv6 subnets and returns them within
    /// a command response. The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "2 IPv6 subnets found",
    ///     "arguments": {
    ///         "subnets": [
    ///             {
    ///                 "id": 11,
    ///                 "subnet": "2001:db8:1::/64"
    ///             },
    ///             {
    ///                 "id": 233,
    ///                 "subnet": "3000::/16"
    ///             }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a response to the command.
    data::ConstElementPtr getSubnet6List() const;

    /// @brief Returns a response to 'subnet4-get' command.
    ///
    /// This function returns an IPv4 subnet by a specified parameter. Currently
    /// supported parameters are:
    /// - subnet, which must be a string specifying subnet prefix, e.g. "10.1.2.0/24".
    /// - id, which must be an integer specifying subnet identifier.
    ///
    /// Only one of those parameters can be specified.
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "Info about IPv4 subnet 10.1.2.0/24 (id 1) returned",
    ///     "arguments": {
    ///         "subnet4": [
    ///             {
    ///                 "subnet": "10.1.2.0/24",
    ///                 "id": 1,
    ///                 ....
    ///             }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a response to the command.
    /// @throw BadValue if the arguments are invalid or if no subnet found.
    data::ConstElementPtr getSubnet4(const data::ConstElementPtr& arguments) const;

    /// @brief Returns a response to 'subnet6-get' command.
    ///
    /// This function returns an IPv6 subnet by a specified parameter. Currently
    /// supported parameters are:
    /// - subnet, which must be a string specifying subnet prefix, e.g. "3000::/16".
    /// - id, which must be an integer specifying subnet identifier.
    ///
    /// Only one of those parameters can be specified.
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "Info about IPv6 subnet 2001:db8:1::/64 (id 1) returned",
    ///     "arguments": {
    ///         "subnet6": [
    ///             {
    ///                 "subnet": "2001:db8:1::/64",
    ///                 "id": 1,
    ///                 ....
    ///             }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a response to the command.
    /// @throw BadValue if the arguments are invalid or if no subnet found.
    data::ConstElementPtr getSubnet6(const data::ConstElementPtr& arguments) const;

    /// @brief Processes and returns a response to 'subnet4-add' command.
    ///
    /// This function processes 'subnet4-add' command by adding it to the
    /// current server configuration and returns a response to the client.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "subnet4-add",
    ///     "arguments": {
    ///         "subnet4": [ {
    ///             "id": 123,
    ///             "subnet": "10.20.30.0/24",
    ///             ...
    ///         } ]
    ///     }
    /// }
    /// @endcode
    ///
    /// Before adding the subnet to the current configuration this method
    /// will check for duplicated subnet, i.e. having the same id or subnet
    /// prefix. If the subnet duplicates an existing subnets an exception
    /// is thrown. The exception is also thrown when any other error occurs.
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "IPv4 subnet added",
    ///     "arguments": {
    ///         "subnet4": [
    ///             {
    ///                 "id": 123,
    ///                 "subnet": "10.20.30.0/24"
    ///             }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a successful response to the command.
    data::ConstElementPtr addSubnet4(const data::ConstElementPtr& arguments);

    /// @brief Processes and returns a response to 'subnet6-add' command.
    ///
    /// This function processes 'subnet6-add' command by adding it to the
    /// current server configuration and returns a response to the client.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "subnet6-add",
    ///     "arguments": {
    ///         "subnet6": [ {
    ///             "id": 123,
    ///             "subnet": "2001:db8:1::/64",
    ///             ...
    ///         } ]
    ///     }
    /// }
    /// @endcode
    ///
    /// Before adding the subnet to the current configuration this method
    /// will check for duplicated subnet, i.e. having the same id or subnet
    /// prefix. If the subnet duplicates an existing subnets an exception
    /// is thrown. The exception is also thrown when any other error occurs.
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "IPv6 subnet added",
    ///     "arguments": {
    ///         "subnet6": [
    ///             {
    ///                 "id": 123,
    ///                 "subnet": "2001:db8:1::/64"
    ///             }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a successful response to the command.
    data::ConstElementPtr addSubnet6(const data::ConstElementPtr& arguments);

    /// @brief Processes and returns a response to 'subnet4-update' command.
    ///
    /// This function processes 'subnet4-update' command by replacing it in
    /// the current server configuration and returns a response to the client.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "subnet4-update",
    ///     "arguments": {
    ///         "subnet4": [ {
    ///             "id": 123,
    ///             "subnet": "10.20.30.0/24",
    ///             ...
    ///         } ]
    ///     }
    /// }
    /// @endcode
    ///
    /// Before replacing the subnet in the current configuration this method
    /// will check for existing subnet with the same id and update it
    /// by this new subnet. The prefix should not be updated but this case
    /// is supported. The operation is atomic: either it succeeds or it
    /// fails leaving the configuration unchanged and throwing an exception.
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "IPv4 subnet updated",
    ///     "arguments": {
    ///         "subnet4": [
    ///             {
    ///                 "id": 123,
    ///                 "subnet": "10.20.30.0/24"
    ///             }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a successful response to the command.
    data::ConstElementPtr updateSubnet4(const data::ConstElementPtr& arguments);

    /// @brief Processes and returns a response to 'subnet6-update' command.
    ///
    /// This function processes 'subnet6-update' command by replacing
    /// existing subnet with a new subnet in the current server configuration
    /// and returns a response to the client.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "subnet6-update",
    ///     "arguments": {
    ///         "subnet6": [ {
    ///             "id": 123,
    ///             "subnet": "2001:db8:1::/64",
    ///             ...
    ///         } ]
    ///     }
    /// }
    /// @endcode
    ///
    /// Before replacing the subnet in the current configuration this method
    /// will check for existing subnet with the same id and update it
    /// by this new subnet. The prefix should not be updated but this case
    /// is supported. The operation is atomic: either it succeeds or it
    /// fails leaving the configuration unchanged and throwing an exception.
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "IPv6 subnet updated",
    ///     "arguments": {
    ///         "subnet6": [
    ///             {
    ///                 "id": 123,
    ///                 "subnet": "2001:db8:1::/64"
    ///             }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a successful response to the command.
    data::ConstElementPtr updateSubnet6(const data::ConstElementPtr& arguments);

    /// @brief Processes and returns a response to 'subnet4-del' command.
    ///
    /// This function processes the 'subnet4-del' command by searching for a
    /// subnet by specified id and deleting this subnet from the server
    /// configuration.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "subnet4-del",
    ///     "arguments": {
    ///         "id": 123
    ///     }
    /// }
    /// @endcode
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "IPv4 subnet 192.0.2.0/24 (id 123) deleted"
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a successful response to the command.
    data::ConstElementPtr delSubnet4(const data::ConstElementPtr& arguments);

    /// @brief Processes and returns a response to 'subnet6-del' command.
    ///
    /// This function processes the 'subnet6-del' command by searching for a
    /// subnet by specified id and deleting this subnet from the server
    /// configuration.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "subnet6-del",
    ///     "arguments": {
    ///         "id": 123
    ///     }
    /// }
    /// @endcode
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "IPv6 subnet 2001:db8:1::/64 (id 123) deleted"
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a successful response to the command.
    data::ConstElementPtr delSubnet6(const data::ConstElementPtr& arguments);

    /// @brief Processes and returns a response to 'subnet4-delta-add' command.
    ///
    /// This function processes 'subnet4-delta-add' command by adding the
    /// specified parameters to the existing subnet already present in
    /// the current server configuration and returns a response to the client.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "subnet4-delta-add",
    ///     "arguments": {
    ///         "subnet4": [ {
    ///             "id": 123,
    ///             "subnet": "10.20.30.0/24",
    ///             ...
    ///         } ]
    ///     }
    /// }
    /// @endcode
    ///
    /// Before updating the subnet in the current configuration this method
    /// will check for existing subnet with the same id and update it by adding
    /// the configuration delta. The operation is atomic: either it succeeds or
    /// it fails leaving the configuration unchanged and throwing an exception.
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "IPv4 subnet updated",
    ///     "arguments": {
    ///         "subnet4": [
    ///             {
    ///                 "id": 123,
    ///                 "subnet": "10.20.30.0/24"
    ///             }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a successful response to the command.
    data::ConstElementPtr addSubnet4Delta(const data::ConstElementPtr& arguments);

    /// @brief Processes and returns a response to 'subnet6-delta-add' command.
    ///
    /// This function processes 'subnet6-delta-add' command by adding the
    /// specified parameters to the existing subnet already present in
    /// the current server configuration and returns a response to the client.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "subnet6-delta-add",
    ///     "arguments": {
    ///         "subnet6": [ {
    ///             "id": 123,
    ///             "subnet": "2001:db8:1::/64",
    ///             ...
    ///         } ]
    ///     }
    /// }
    /// @endcode
    ///
    /// Before updating the subnet in the current configuration this method
    /// will check for existing subnet with the same id and update it by adding
    /// the configuration delta. The operation is atomic: either it succeeds or
    /// it fails leaving the configuration unchanged and throwing an exception.
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "IPv6 subnet updated",
    ///     "arguments": {
    ///         "subnet6": [
    ///             {
    ///                 "id": 123,
    ///                 "subnet": "2001:db8:1::/64"
    ///             }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a successful response to the command.
    data::ConstElementPtr addSubnet6Delta(const data::ConstElementPtr& arguments);

    /// @brief Processes and returns a response to 'subnet4-delta-del' command.
    ///
    /// This function processes 'subnet4-delta-add' command by removing the
    /// specified parameters from the existing subnet already present in
    /// the current server configuration and returns a response to the client.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "subnet4-delta-del",
    ///     "arguments": {
    ///         "subnet4": [ {
    ///             "id": 123,
    ///             "subnet": "10.20.30.0/24",
    ///             ...
    ///         } ]
    ///     }
    /// }
    /// @endcode
    ///
    /// Before updating the subnet in the current configuration this method
    /// will check for existing subnet with the same id and update it by removing
    /// the configuration delta. The operation is atomic: either it succeeds or
    /// it fails leaving the configuration unchanged and throwing an exception.
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "IPv4 subnet updated",
    ///     "arguments": {
    ///         "subnet4": [
    ///             {
    ///                 "id": 123,
    ///                 "subnet": "10.20.30.0/24"
    ///             }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a successful response to the command.
    data::ConstElementPtr delSubnet4Delta(const data::ConstElementPtr& arguments);

    /// @brief Processes and returns a response to 'subnet6-delta-del' command.
    ///
    /// This function processes 'subnet6-delta-del' command by removing the
    /// specified parameters from the existing subnet already present in
    /// the current server configuration and returns a response to the client.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "subnet6-delta-del",
    ///     "arguments": {
    ///         "subnet6": [ {
    ///             "id": 123,
    ///             "subnet": "2001:db8:1::/64",
    ///             ...
    ///         } ]
    ///     }
    /// }
    /// @endcode
    ///
    /// Before updating the subnet in the current configuration this method
    /// will check for existing subnet with the same id and update it by removing
    /// the configuration delta. The operation is atomic: either it succeeds or
    /// it fails leaving the configuration unchanged and throwing an exception.
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "IPv6 subnet updated",
    ///     "arguments": {
    ///         "subnet6": [
    ///             {
    ///                 "id": 123,
    ///                 "subnet": "2001:db8:1::/64"
    ///             }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a successful response to the command.
    data::ConstElementPtr delSubnet6Delta(const data::ConstElementPtr& arguments);

    // --- shared network commands ---------------------------------------------

    /// @brief Returns a response to a 'network4-list' command.
    ///
    /// This method retrieves configured IPv4 shared networks and returns them within
    /// a command response. The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "2 IPv4 shared networks found",
    ///     "arguments": {
    ///         "shared-networks": [
    ///             {
    ///                 "name": "frog"
    ///             },
    ///             {
    ///                 "name": "parrot"
    ///             }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a response to the command.
    data::ConstElementPtr getNetwork4List() const;

    /// @brief Returns a response to a 'network6-list' command.
    ///
    /// This method retrieves configured IPv6 shared networks and returns them within
    /// a command response. The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "2 IPv6 shared networks found",
    ///     "arguments": {
    ///         "shared-networks": [
    ///             {
    ///                 "name": "frog"
    ///             },
    ///             {
    ///                 "name": "parrot"
    ///             }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a response to the command.
    data::ConstElementPtr getNetwork6List() const;

    /// @brief Returns a response to 'network4-get' command.
    ///
    /// This function returns an IPv4 shared network by a specified parameter. Currently
    /// the only supported parameter is:
    /// - name, which must be a string
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "arguments": {
    ///         "shared-networks": [
    ///             {
    ///                 "name": "frog",
    ///                 "interface": "eth1",
    ///                 "subnet4": [,
    ///                     {
    ///                         "subnet": "10.1.2.0/24",
    ///                         "id": 1,
    ///                         ....
    ///                     }
    ///                 ]
    ////            }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a response to the command.
    /// @throw BadValue if the arguments are invalid
    data::ConstElementPtr getNetwork4(const data::ConstElementPtr& arguments) const;

    /// @brief Returns a response to 'network6-get' command.
    ///
    /// This function returns an IPv6 shared network by a specified parameter. Currently
    /// the only supported parameter is:
    /// - name, which must be a string
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "arguments": {
    ///         "shared-networks": [
    ///             {
    ///                 "name": "frog",
    ///                 "interface": "eth1",
    ///                 "subnet6": [,
    ///                     {
    ///                         "subnet": "2001:db8::/48",
    ///                         "id": 1,
    ///                         ....
    ///                     }
    ///                 ]
    ////            }
    ///         ]
    ///     }
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a response to the command.
    /// @throw BadValue if the arguments are invalid
    data::ConstElementPtr getNetwork6(const data::ConstElementPtr& arguments) const;

    /// @brief Processes and returns a response to 'network4-add' command.
    ///
    /// This function processes 'network4-add' command by adding specified shared
    /// network (with zero or more subnets in it) to the
    /// current server configuration and returns a response to the client.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "network4-add",
    ///     "arguments": {
    ///         "shared-networks": [
    ///         {
    ///             "name": "floor13",
    ///             "subnet4": [ {
    ///                 "id": 123,
    ///                 "subnet": "192.0.2.0/24",
    ///                 ...
    ///             } ] // end of subnet4
    ///         } ] // end of shared-networks
    ///     }
    /// }
    /// @endcode
    ///
    /// Before adding the subnet to the current configuration this method
    /// will check for duplicated subnet, i.e. having the same id or subnet
    /// prefix. If the subnet duplicates an existing subnets an exception
    /// is thrown. The exception is also thrown when any other error occurs.
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "A new IPv4 shared network added",
    ///     "shared-networks": [
    ///         {
    ///             "name": "floor13"
    ///         }
    ///      ]
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a successful response to the command.
    data::ConstElementPtr addNetwork4(const data::ConstElementPtr& arguments);

    /// @brief Processes and returns a response to 'network6-add' command.
    ///
    /// This function processes 'network6-add' command by adding specified shared
    /// network (with zero or more subnets in it) to the
    /// current server configuration and returns a response to the client.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "network6-add",
    ///     "arguments": {
    ///         "shared-networks": [
    ///         {
    ///             "name": "floor13",
    ///             "subnet6": [ {
    ///                 "id": 123,
    ///                 "subnet": "2001:db8::/48",
    ///                 ...
    ///             } ] // end of subnet6
    ///         } ] // end of shared-networks
    ///     }
    /// }
    /// @endcode
    ///
    /// Before adding the subnet to the current configuration this method
    /// will check for duplicated subnet, i.e. having the same id or subnet
    /// prefix. If the subnet duplicates an existing subnets an exception
    /// is thrown. The exception is also thrown when any other error occurs.
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "A new IPv6 shared network added",
    ///     "shared-networks": [
    ///         {
    ///             "name": "floor13"
    ///         }
    ///      ]
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a successful response to the command.
    data::ConstElementPtr addNetwork6(const data::ConstElementPtr& arguments);

    /// @brief Processes and returns a response to 'network4-del' command.
    ///
    /// This function processes the 'network4-del' command by searching for a
    /// subnet by specified name and deleting this shared network from the server
    /// configuration. The subnets in this shared network will not be deleted,
    /// but instead will be degraded to regular, plain subnets.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "network4-del",
    ///     "arguments": {
    ///         "name": "frog"
    ///     }
    /// }
    /// @endcode
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "IPv4 shared network 'frog' deleted"
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a successful response to the command.
    data::ConstElementPtr delNetwork4(const data::ConstElementPtr& arguments);

    /// @brief Processes and returns a response to 'network6-del' command.
    ///
    /// This function processes the 'network6-del' command by searching for a
    /// subnet by specified name and deleting this shared network from the server
    /// configuration. The subnets in this shared network will not be deleted,
    /// but instead will be degraded to regular, plain subnets.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "network6-del",
    ///     "arguments": {
    ///         "name": "frog"
    ///     }
    /// }
    /// @endcode
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "IPv6 shared network 'frog' deleted"
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a successful response to the command.
    data::ConstElementPtr delNetwork6(const data::ConstElementPtr& arguments);

    /// @brief Processes and returns a response to 'network4-subnet-add' command.
    ///
    /// This function processes the 'network4-subnet-add' command by searching for a
    /// subnet with specified id and a network with specified name and then adding
    /// the subnet to that network.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "network4-subnet-add",
    ///     "arguments": {
    ///         "name": "floor13"
    ///         "id": 123
    ///     }
    /// }
    /// @endcode
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "IPv4 subnet 10.0.0.0/8 (id 123) is now part of shared network 'floor13'"
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a successful response to the command.
    data::ConstElementPtr addNetwork4Subnet(const data::ConstElementPtr& arguments);

    /// @brief Processes and returns a response to 'network6-subnet-add' command.
    ///
    /// This function processes the 'network6-subnet-add' command by searching for a
    /// subnet with specified id and a network with specified name and then adding
    /// the subnet to that network.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "network6-subnet-add",
    ///     "arguments": {
    ///         "name": "floor13"
    ///         "id": 123
    ///     }
    /// }
    /// @endcode
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "IPv6 subnet 2001:db8::/48 (id 123) is now part of shared network 'floor13'"
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a successful response to the command.
    data::ConstElementPtr addNetwork6Subnet(const data::ConstElementPtr& arguments);

    /// @brief Processes and returns a response to 'network4-subnet-del' command.
    ///
    /// This function processes the 'network4-subnet-del' command by searching for a
    /// subnet with specified id within a network with specified name and then removing
    /// the subnet from that network.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "network4-subnet-add",
    ///     "arguments": {
    ///         "name": "floor13"
    ///         "id": 123
    ///     }
    /// }
    /// @endcode
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "IPv4 subnet 10.0.0.0/8 (id 5) is now removed from shared network 'floor13'"
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a successful response to the command.
    data::ConstElementPtr delNetwork4Subnet(const data::ConstElementPtr& arguments);

    /// @brief Processes and returns a response to 'network6-subnet-del' command.
    ///
    /// This function processes the 'network6-subnet-del' command by searching for a
    /// subnet with specified id within a network with specified name and then removing
    /// the subnet from that network.
    ///
    /// The command has the following structure:
    /// @code
    /// {
    ///     "command": "network4-subnet-del",
    ///     "arguments": {
    ///         "name": "floor13"
    ///         "id": 123
    ///     }
    /// }
    /// @endcode
    ///
    /// The successful response has the following structure:
    /// @code
    /// {
    ///     "result": 0,
    ///     "text": "IPv6 subnet 2001:db8::/32 (id 5) is now removed from shared network 'floor13'"
    /// }
    /// @endcode
    ///
    /// @param arguments Arguments received for the command.
    ///
    /// @return Pointer to the @c isc::data::Element object holding the data
    /// structure reflecting a successful response to the command.
    data::ConstElementPtr delNetwork6Subnet(const data::ConstElementPtr& arguments);

private:

    /// @brief Pointer to the @ref SubnetCmds implementation.
    boost::shared_ptr<SubnetCmdsImpl> impl_;

};

} // end of namespace isc::subnet_cmds
} // end of namespace isc

#endif // SUBNET_CMDS_H
